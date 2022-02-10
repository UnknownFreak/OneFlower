uniform sampler2D texture;
uniform vec4 color;
void main(void)
{
    vec2 position = gl_TexCoord[0].xy;
    vec4 tex_color = texture2D(texture, position);
    
    if(tex_color.a > 0.3)
        tex_color.rgb = color;
    gl_FragColor = tex_color;
}