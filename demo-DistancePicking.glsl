-- Quad.VS

in vec2 Position;
in vec2 TexCoord;
out vec2 vTexCoord;

void main()
{
    vTexCoord = TexCoord;
    gl_Position = vec4(Position, 0, 1);
}

-- Quad.FS

in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
uniform sampler2D Sampler;
uniform vec3 Scale;

void main()
{
    FragColor = vec4(Scale, 1) * texture(Sampler, vTexCoord);
}

-- Erode.FS

layout(location = 1) out vec3 DistanceMap;

in vec2 vTexCoord;

uniform sampler2D Sampler;
uniform float Beta;
uniform vec2 Offset;

void main()
{
    vec3 A3 = texture(Sampler, vTexCoord).xyz;
    vec3 e3 = texture(Sampler, vTexCoord + Offset).xyz;
    vec3 w3 = texture(Sampler, vTexCoord - Offset).xyz;

    float A = A3.z;
    float e = Beta + e3.z;
    float w = Beta + w3.z;
    float B = min(min(A, e), w);

    if (A == B) {
        //DistanceMap = A3;
        //return;
        discard;
    }

    DistanceMap.xy = w3.xy;
    DistanceMap.z = B;

    if (A <= e && e <= w) DistanceMap.xy = A3.xy;
    if (A <= w && w <= e) DistanceMap.xy = A3.xy;
    if (e <= A && A <= w) DistanceMap.xy = e3.xy;
    if (e <= w && w <= A) DistanceMap.xy = e3.xy;
}

-- Lit.VS

in vec4 Position;
in vec3 Normal;

out vec3 vPosition;
out vec3 vNormal;

uniform mat4 Projection;
uniform mat4 Modelview;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

void main()
{
    vPosition = Position.xyz;
    gl_Position = Projection * Modelview * Position;
    vNormal = NormalMatrix * Normal;
}

-- Lit.FS

in vec3 vNormal;

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec3 DistanceMap;

uniform vec3 LightPosition = vec3(0.25, 0.25, 1.0);
uniform vec3 AmbientMaterial = vec3(0.04, 0.04, 0.04);
uniform vec3 SpecularMaterial = vec3(0.5, 0.5, 0.5);
uniform vec3 FrontMaterial = vec3(0.75, 0.75, 0.5);
uniform vec3 BackMaterial = vec3(0.5, 0.5, 0.75);
uniform float Shininess = 50;

void main()
{
    vec3 N = normalize(vNormal);
    if (!gl_FrontFacing)
       N = -N;

    vec3 L = normalize(LightPosition);
    vec3 Eye = vec3(0, 0, 1);
    vec3 H = normalize(L + Eye);
    
    float df = max(0.0, dot(N, L));
    float sf = max(0.0, dot(N, H));
    sf = pow(sf, Shininess);

    vec3 color = gl_FrontFacing ? FrontMaterial : BackMaterial;
    vec3 lighting = AmbientMaterial + df * color;
    if (gl_FrontFacing)
        lighting += sf * SpecularMaterial;

    FragColor = vec4(lighting, 1);
    DistanceMap = vec3(gl_FragCoord.xy, 0);
}

-- Sprite.VS

out vec3 vPosition;
uniform vec2 MouseLocation;
uniform mat4 Projection;
uniform mat4 Modelview;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

uniform sampler2D Sampler;
uniform vec2 InverseViewport;
uniform float Height;

void main()
{
    vec2 distance = texture(Sampler, MouseLocation * InverseViewport).xy;
    vPosition = vec3(distance, 0);
    vPosition.y = Height - vPosition.y;
    gl_Position = Projection * Modelview * vec4(vPosition, 1);
}

-- Sprite.GS

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;
uniform vec2 SpriteSize;
out vec2 gCenterCoord;
uniform vec2 HalfViewport;
uniform vec2 InverseViewport;

vec2 toFragCoord(vec4 v)
{
    return HalfViewport * (1.0 + v.xy / v.w);
}

void main()
{
    vec4 P = gl_in[0].gl_Position;
    vec4 U = vec4(SpriteSize.x, 0, 0, 0) * InverseViewport.x;
    vec4 V = vec4(0, SpriteSize.y, 0, 0) * InverseViewport.y;
    gCenterCoord = toFragCoord(P);

    // Discard the cursor if it's not near anything
    if (gCenterCoord.x < 0.01 && gCenterCoord.y < 0.01) {
        return;
    }

    P.z = 0;
    P.xy /= P.w;
    P.w = 1;

    gl_Position = P - U - V; EmitVertex();
    gl_Position = P + U - V; EmitVertex();
    gl_Position = P - U + V; EmitVertex();
    gl_Position = P + U + V; EmitVertex();
    EndPrimitive();
}

-- Sprite.FS

out vec4 FragColor;
in vec2 gCenterCoord;
uniform vec2 SpriteSize;

void main()
{
    float L = distance(gl_FragCoord.xy, gCenterCoord);
    float D = 2.0 * L / SpriteSize.x;

    // Draw a circular mouse cursor
    float t = 0.125;     // Border thickness
    float r = 0.75;      // Inner radius
    float w = fwidth(D); // Antialiasing constant
    if (D < r - t) {
        float A = 1.0 - smoothstep(r-t-w, r-t, D);
        FragColor = vec4(A, A, A, 1);
    } else if (D < r + t) {
        FragColor = vec4(0, 0, 0, 1);
    } else {
        float A = 1.0 - smoothstep(r+t, r+t+w, D);
        FragColor = vec4(0, 0, 0, A);
    }
}
