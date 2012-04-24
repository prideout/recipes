
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

layout(binding=0) uniform sampler2D cloud;
layout(binding=1) uniform sampler2D lava;

in vec2 vTexCoord;
out vec4 FragColor;

void main( void ) {

    vec2 position = -1.0 + 2.0 * vTexCoord;

    vec4 noise = texture( cloud, vTexCoord );
    vec2 T1 = vTexCoord + vec2( 1.5, -1.5 ) * time * 0.02;
    vec2 T2 = vTexCoord + vec2( -0.5, 2.0 ) * time * 0.01;
				
    T1.x += noise.x * 2.0;
    T1.y += noise.y * 2.0;
    T2.x -= noise.y * 0.2;
    T2.y += noise.z * 0.2;
				
    float p = texture( cloud, T1 * 2.0 ).a;
				
    vec4 color = texture( lava, T2 * 2.0 );
    vec4 temp = color * ( vec4( p, p, p, p ) * 2.0 ) + ( color * color - 0.1 );
				
    if( temp.r > 1.0 ){ temp.bg += clamp( temp.r - 2.0, 0.0, 100.0 ); }
    if( temp.g > 1.0 ){ temp.rb += temp.g - 1.0; }
    if( temp.b > 1.0 ){ temp.rg += temp.b - 1.0; }
				
    FragColor = temp;

    float depth = gl_FragCoord.z * 4; // TODO some sort of auto-normalization?
    const float LOG2 = 1.442695;
    float fogFactor = exp2( - fogDensity * fogDensity * depth * depth * LOG2 );
    fogFactor = 1.0 - clamp( fogFactor, 0.0, 1.0 );
				
    FragColor = mix( FragColor, vec4( fogColor, temp.a ), fogFactor );
}

-- Quad.VS

out vec2 vTexCoord;

void main()
{
    int i = gl_VertexID;
    vTexCoord = vec2(i%2,i/2);
    gl_Position = vec4(2*vTexCoord-1,0,1);
}

-- Blur.FS

in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
uniform sampler2D Sampler;
uniform vec2 Offsets[5];
uniform float Weights[5];

void main()
{
    FragColor = vec4(0);
    for (int i = 0; i < 5; i++) {
        float w = Weights[i];
        vec2 o = Offsets[i];
        FragColor += w * texture(Sampler, vTexCoord + o);
    }
}

-- Quad.FS

in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
uniform sampler2D Sampler;
uniform float Alpha = 1.0;

void main()
{
    FragColor = texture(Sampler, vTexCoord);
    if (gl_FragCoord.x < 1 || gl_FragCoord.x > 1279 || gl_FragCoord.y < 1 || gl_FragCoord.y > 799) {
        FragColor.rgb = vec3(0.5);
    }
    FragColor.a *= Alpha;
}

-- Hipass.FS

in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
uniform sampler2D Sampler;
uniform float Threshold = 1.0;
const vec3 Black = vec3(0, 0, 0);

void main()
{
    vec3 c = texture(Sampler, vTexCoord).rgb;
    float gray = dot(c,c);
    FragColor = vec4(gray > Threshold ? c : Black, 1);
}
