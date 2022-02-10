uniform sampler2D texture;
uniform float intensity;
uniform vec4 color;
void main(void)
{
    vec2 position = gl_TexCoord[0].xy;
    vec4 tex_color = texture2D(texture, position);
    color.a = tex_color.a;
    tex_color = color * intensity;
    gl_FragColor = tex_color;
}