-- Text.VS

in uint Character;
uniform int GlyphWidth = 32;

void main()
{
    vec2 p;
    p.x = float(gl_VertexID) * GlyphWidth;
    p.y = 0;
    gl_Position = vec4(p, 0, 1);
}


-- Text.GS

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform vec2 SpriteSize;
uniform vec2 HalfViewport;
uniform vec2 InverseViewport;

out vec2 TexCoord;

void main()
{
    vec4 P = gl_in[0].gl_Position;
    vec4 U = vec4(SpriteSize.x, 0, 0, 0) * InverseViewport.x;
    vec4 V = vec4(0, SpriteSize.y, 0, 0) * InverseViewport.y;

    TexCoord = vec2(0, 0);
    gl_Position = P - U - V;
    EmitVertex();

    TexCoord = vec2(1, 0);
    gl_Position = P + U - V;
    EmitVertex();

    TexCoord = vec2(0, 1);
    gl_Position = P - U + V;
    EmitVertex();

    TexCoord = vec2(1, 1);
    gl_Position = P + U + V;
    EmitVertex();

    EndPrimitive();
}

-- Text.FS

out vec4 FragColor;
in vec2 TexCoord;

uniform vec2 SpriteSize;
uniform sampler2D Sampler;

void main()
{
    FragColor = texture(Sampler, TexCoord);
}

----------------------------------------------------------------

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
out vec4 FragColor;

uniform vec3 LightPosition = vec3(0.25, 0.25, 1.0);
uniform vec3 AmbientMaterial = vec3(0.04, 0.04, 0.04);
uniform vec3 SpecularMaterial = vec3(0.5, 0.5, 0.5);
uniform vec3 FrontMaterial = vec3(0.75, 0.75, 0.5);
uniform vec3 BackMaterial = vec3(0.5, 0.5, 0.75);
uniform float Shininess = 50;

const float A = 0.1;
const float B = 0.3;
const float C = 0.6;
const float D = 1.0;

void main()
{
    vec3 N = normalize(vNormal);
    if (!gl_FrontFacing)
       N = -N;

    vec3 L = normalize(LightPosition);
    vec3 Eye = vec3(0, 0, 1);
    vec3 H = normalize(L + Eye);
    
    float df = max(0.0, dot(N, L));
    float E = fwidth(df);
    if (df > A - E && df < A + E)
        df = mix(A, B, smoothstep(A - E, A + E, df));
    else if (df > B - E && df < B + E)
        df = mix(B, C, smoothstep(B - E, B + E, df));
    else if (df > C - E && df < C + E)
        df = mix(C, D, smoothstep(C - E, C + E, df));
    else if (df < A) df = 0.0;
    else if (df < B) df = B;
    else if (df < C) df = C;
    else df = D;

    float sf = max(0.0, dot(N, H));
    sf = pow(sf, Shininess);
    E = fwidth(sf);
    if (sf > 0.5 - E && sf < 0.5 + E)
        sf = clamp(0.5 * (sf - 0.5 + E) / E, 0.0, 1.0);
    else
        sf = step(0.5, sf);

    vec3 color = gl_FrontFacing ? FrontMaterial : BackMaterial;
    vec3 lighting = AmbientMaterial + df * color;
    if (gl_FrontFacing)
        lighting += sf * SpecularMaterial;

    FragColor = vec4(lighting, 1);
}
