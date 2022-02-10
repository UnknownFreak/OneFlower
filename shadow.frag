uniform sampler2D texture;
uniform float alpha;
const vec2 res = vec2(1920.0, 1080.0);
void main(void)
{
    vec2 position = ( gl_FragCoord.xy / res.xy );
    vec4 color = texture2D(texture, position);
    //if (color.r < t && color.g < t && color.b < t)
    //{
    //    color. a = 1;//0.0588235294117647
    //}
    //else
    //{
    //     color.rgb = 1;
    //     //wcolor.a = alpha;
    //} 
    if (color.r == 1.0 && color.g == 1.0 && color.b == 1.0)
        color.a = 0;
    else
        color.a = alpha;
    gl_FragColor = color;
}