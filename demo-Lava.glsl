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

-- TheGameMaker.VS

in vec4 Position;
in vec2 TexCoord;

uniform mat4 Projection;
uniform mat4 Modelview;

out vec2 vTexCoord;

void main()
{
    vTexCoord = vec2( 3.0, 1.0 ) * TexCoord;
    gl_Position = Projection * Modelview * Position;

}

-- TheGameMaker.FS

uniform float time;
			
uniform float fogDensity = 0.45;
uniform vec3 fogColor = vec3(0, 0, 0);

layout(binding=0) uniform sampler2D texture1; // CLOUD (REPEAT  WRAPPING)
layout(binding=1) uniform sampler2D texture2; // LAVATILE (REPEAT  WRAPPING)

in vec2 vTexCoord;
out vec4 FragColor;

void main( void ) {

    vec2 position = -1.0 + 2.0 * vTexCoord;

    vec4 noise = texture2D( texture1, vTexCoord );
    vec2 T1 = vTexCoord + vec2( 1.5, -1.5 ) * time * 0.02;
    vec2 T2 = vTexCoord + vec2( -0.5, 2.0 ) * time * 0.01;
				
    T1.x += noise.x * 2.0;
    T1.y += noise.y * 2.0;
    T2.x -= noise.y * 0.2;
    T2.y += noise.z * 0.2;
				
    float p = texture( texture1, T1 * 2.0 ).a;
				
    vec4 color = texture( texture2, T2 * 2.0 );
    vec4 temp = color * ( vec4( p, p, p, p ) * 2.0 ) + ( color * color - 0.1 );
				
    if( temp.r > 1.0 ){ temp.bg += clamp( temp.r - 2.0, 0.0, 100.0 ); }
    if( temp.g > 1.0 ){ temp.rb += temp.g - 1.0; }
    if( temp.b > 1.0 ){ temp.rg += temp.b - 1.0; }
				
    FragColor = temp;

    float depth = gl_FragCoord.z / gl_FragCoord.w;
    const float LOG2 = 1.442695;
    float fogFactor = exp2( - fogDensity * fogDensity * depth * depth * LOG2 );
    fogFactor = 1.0 - clamp( fogFactor, 0.0, 1.0 );
				
    FragColor = mix( FragColor, vec4( fogColor, FragColor.w ), fogFactor );
}
