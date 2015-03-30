varying vec2 v_texCoords;
uniform sampler2D u_texture;
uniform sampler2D u_mask;

void main()
{
    vec4 colour = texture2D(u_texture, v_texCoords);
    vec4 mask = texture2D(u_mask, v_texCoords);

    if (mask.a > 0)
        discard;
    else {
        gl_FragColor = colour;
    }
}