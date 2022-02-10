uniform vec2 lightPos;
uniform vec3 lightColor;
uniform float intensity;

out vec4 color;

void main()
{
        vec3 lAtt = vec3(0.01, 0.1, 0.00001);
        
        float dist = distance(gl_FragCoord.xy, lightPos.xy);
        float att = 1.0 / (lAtt.x + lAtt.y * dist + lAtt.z * dist * dist);
        vec4 finLight = vec4(vec3(att) * lightColor, 1.0) * intensity;
        
        color = finLight;
}