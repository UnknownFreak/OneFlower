uniform sampler2D tex;
uniform vec4 color;

void main()
{

	vec4 col = texture2D(tex,gl_TexCoord[0].xy);
	if(col.a > 0)
		gl_FragColor =color;
	else
	discard;
		
}