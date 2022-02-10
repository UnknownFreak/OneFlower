#version 130

uniform sampler2D tex;
uniform float texture_inverse;
uniform int blur_radius;
uniform vec2 blur_direction;

vec4 blur9(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.3846153846) * direction;
  vec2 off2 = vec2(3.2307692308) * direction;
  color += texture2D(image, uv) * 0.2270270270;
  color += texture2D(image, uv + (off1 / resolution)) * 0.3162162162;
  color += texture2D(image, uv - (off1 / resolution)) * 0.3162162162;
  color += texture2D(image, uv + (off2 / resolution)) * 0.0702702703;
  color += texture2D(image, uv - (off2 / resolution)) * 0.0702702703;
  return color;
}

const vec2 resolution = vec2(1920, 1080);

void main(void){
    //vec4 sum = texture2D(tex, gl_TexCoord[0].xy);
    //for (int i = 0; i < blur_radius; ++i){
    //    sum += texture2D(tex, gl_TexCoord[0].xy + (i * texture_inverse) * blur_direction);
    //    sum += texture2D(tex, gl_TexCoord[0].xy - (i * texture_inverse) * blur_direction);
    //}
    //gl_FragColor = sum / (blur_radius * 2 + 1);



    //vec2 tex_offset = 1.0 / textureSize(tex, 0); // gets size of single texel
    //vec3 result = texture(tex, gl_TexCoord[0].xy).rgb * weight[0]; // current fragment's contribution
    //if(horizontal)
    //{
    //    for(int i = 1; i < 5; ++i)
    //    {
    //        result += texture(tex, gl_TexCoord[0].xy + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
    //        result += texture(tex, gl_TexCoord[0].xy - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
    //    }
    //}
    //else
    //{
    //    for(int i = 1; i < 5; ++i)
    //    {
    //        result += texture(tex, gl_TexCoord[0].xy + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
    //        result += texture(tex, gl_TexCoord[0].xy - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
    //    }
    //}
    //gl_FragColor = vec4(result, 1.0);
    //vec2 uv = vec2(gl_FragCoord.xy / resolution);
    //uv.y = 1.0 - uv.y;
    gl_FragColor += blur9(tex,  gl_TexCoord[0].xy, resolution, blur_direction);
}