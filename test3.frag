uniform sampler2D texture;
uniform sampler2D lightmap;

uniform vec4 ambient;
uniform vec2 resolution;
uniform int theta;

float PI_180 = 3.141592653589793f / 180.0f;

vec3 ToGlColour3(in vec3 colour)
{
    float dv = (1.0f/255.0f);
    return vec3
    (
        dv * colour.r,
        dv * colour.g,
        dv * colour.b
    );
}

vec4 ToGlColour4(in vec4 colour)
{
    return vec4
    (
        ToGlColour3(colour.rgb),
        (1.0f/255.0f) * colour.a
    );
}

void main()
{
    vec4 diffuse = texture2D(texture, gl_TexCoord[0].xy);

    vec2 lightcoord = (gl_FragCoord.xy / resolution.xy);
    vec4 light = texture2D(lightmap, lightcoord);
	
    vec4 ambientLight = ToGlColour4(ambient);

    float ambientIntensity = ambientLight.a * (sin(theta * PI_180) + 1);
    vec3 ambientColour = ambientLight.rgb * ambientIntensity;
    vec3 intensity = (ambientColour + light.rgb);

    vec3 result = (ambientLight.rgb + 1.5*(sin(theta * PI_180)*0.5+0.5)*light.rgb;

    gl_FragColor = vec4(result, diffuse.a);

}