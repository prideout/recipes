-- VS

in vec4 Position;
out vec3 vPosition;
out float gl_ClipDistance[1];

uniform mat4 Projection;
uniform mat4 Modelview;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform vec4 ClipPlane;

void main()
{
    vPosition = Position.xyz;
    gl_Position = Projection * Modelview * Position;
    gl_ClipDistance[0] = dot(ModelMatrix * Position, ClipPlane);
}

-- GS

out vec2 gDistance;
out vec3 gNormal;
in vec3 vPosition[3];

uniform mat3 NormalMatrix;
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

void main()
{
    vec3 A = vPosition[0];
    vec3 B = vPosition[1];
    vec3 C = vPosition[2];
    
    gNormal = NormalMatrix * normalize(cross(B - A, C - A));
    
    gDistance = vec2(1, 0);
    gl_Position = gl_in[0].gl_Position;
    gl_ClipDistance[0] = gl_in[0].gl_ClipDistance[0];
    EmitVertex();

    gDistance = vec2(0, 0);
    gl_Position = gl_in[1].gl_Position;
    gl_ClipDistance[0] = gl_in[1].gl_ClipDistance[0];
    EmitVertex();

    gDistance = vec2(0, 1);
    gl_Position = gl_in[2].gl_Position;
    gl_ClipDistance[0] = gl_in[2].gl_ClipDistance[0];
    EmitVertex();

    EndPrimitive();
}

-- FS

in vec2 gDistance;
in vec3 gNormal;
out vec4 FragColor;

const float Scale = 20.0;
const float Offset = -1.0;

uniform vec3 LightPosition = vec3(0.25, 0.25, 1.0);
uniform vec3 AmbientMaterial = vec3(0.04, 0.04, 0.04);
uniform vec3 SpecularMaterial = vec3(0.5, 0.5, 0.5);
uniform vec3 FrontMaterial = vec3(0.75, 0.75, 0.5);
uniform vec3 BackMaterial = vec3(0.5, 0.5, 0.75);
uniform float Shininess = 50;

vec4 amplify(float d, vec3 color)
{
    d = Scale * d + Offset + gl_FragCoord.z;
    d = clamp(d, 0, 1);
    d = 1 - exp2(-2*d*d);
    return vec4(d*color, 1);
}

void main()
{
    vec3 N = normalize(gNormal);
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

    float d = min(gDistance.x, gDistance.y);
    FragColor = amplify(d, lighting);
}
