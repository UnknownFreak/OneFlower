#version 120

uniform sampler2D texture;
uniform float threshold;

void main(void){
    vec3 current_color = texture2D(texture, gl_TexCoord[0].xy).rgb;
    vec4 pixel =  vec4(0.0, 0.0, 0.0, 1.0);
    float brightness = dot(current_color.rgb, vec3(0.2126, 0.7152, 0.0722));
    if (brightness >= threshold){
        pixel = texture2D(texture, gl_TexCoord[0].xy);
    }
    gl_FragColor = pixel;
}