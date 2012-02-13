
-- Vertex

attribute vec4 Position;
attribute vec3 Normal;

varying vec3 vNormal;
varying vec3 vPosition;

uniform mat4 Projection;
uniform mat4 Modelview;
uniform mat3 NormalMatrix;

void main()
{
    vPosition = (Modelview * Position).xyz;
    vNormal = NormalMatrix * Normal;
    gl_Position = Projection * Modelview * Position;
}

-- Vertex.Quad

attribute vec4 Position;

void main()
{
    gl_Position = Position;
}

-- Fragment.Depth

uniform float DepthScale;
varying vec3 vNormal;
varying vec3 vPosition;

void main()
{
    vec3 N = normalize(vNormal);
    vec3 P = vPosition;
    vec3 I = normalize(P);
    float cosTheta = abs(dot(I, N));
    float fresnel = pow(1.0 - cosTheta, 4.0);

    float depth = DepthScale * gl_FragCoord.z;

    gl_FragColor = vec4(depth, fresnel, 0, 0);
}

-- Fragment.Depth.ES2

uniform highp float DepthScale;
varying highp vec3 vNormal;
varying highp vec3 vPosition;

void main()
{
    highp vec3 N = normalize(vNormal);
    highp vec3 P = vPosition;
    highp vec3 I = normalize(P);
    highp float cosTheta = abs(dot(I, N));
    highp float fresnel = pow(1.0 - cosTheta, 4.0);

    highp float depth = DepthScale * gl_FragCoord.z;

    gl_FragColor = vec4(depth, fresnel, 0, 0);
}

-- Fragment.Absorption

uniform sampler2D Sampler;
uniform vec2 Size;
uniform vec3 DiffuseMaterial;

void main()
{
    vec2 texCoord = gl_FragCoord.xy / Size;
    float thickness = abs(texture2D(Sampler, texCoord).r);
    if (thickness <= 0.0)
    {
        discard;
    }
    float sigma = 30.0;
    float fresnel = 1.0 - texture2D(Sampler, texCoord).g;
    float intensity = fresnel * exp(-sigma * thickness);
    gl_FragColor = vec4(intensity * DiffuseMaterial, 1);
}

-- Fragment.Blit

uniform sampler2D Sampler;
uniform vec2 Size;

void main()
{
    vec2 texCoord = gl_FragCoord.xy / Size;
    gl_FragColor = texture2D(Sampler, texCoord);
}

-- Fragment.Blit.ES2

precision highp float;

uniform sampler2D Sampler;
uniform vec2 Size;

void main()
{
    vec2 texCoord = gl_FragCoord.xy / Size;
    gl_FragColor = texture2D(Sampler, texCoord);
}

-- Fragment.Absorption.ES2

uniform sampler2D Sampler;
uniform highp vec2 Size;

void main()
{
    highp vec2 texCoord = gl_FragCoord.xy / Size;
    gl_FragColor = texture2D(Sampler, texCoord);
}

-- Fragment.Lighting

varying vec3 vNormal;

uniform vec3 LightPosition;
uniform vec3 DiffuseMaterial;
uniform vec3 AmbientMaterial;
uniform vec3 SpecularMaterial;
uniform float Shininess;

void main()
{
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightPosition);
    vec3 E = vec3(0, 0, 1);
    vec3 H = normalize(L + E);

    float df = max(0.0, dot(N, L));
    float sf = max(0.0, dot(N, H));
    sf = pow(sf, Shininess);
    vec3 color = AmbientMaterial + df * DiffuseMaterial + sf * SpecularMaterial;

    gl_FragColor = vec4(color, 1.0);
}

-- Fragment.Lighting.ES2

precision highp float;

varying vec3 vNormal;

uniform vec3 LightPosition;
uniform vec3 DiffuseMaterial;
uniform vec3 AmbientMaterial;
uniform vec3 SpecularMaterial;
uniform float Shininess;

void main()
{
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightPosition);
    vec3 E = vec3(0, 0, 1);
    vec3 H = normalize(L + E);

    float df = max(0.0, dot(N, L));
    float sf = max(0.0, dot(N, H));
    sf = pow(sf, Shininess);
    vec3 color = AmbientMaterial + df * DiffuseMaterial + sf * SpecularMaterial;

    gl_FragColor = vec4(color, 1.0);
}
