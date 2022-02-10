//#version 330 

uniform sampler2D texture;
uniform vec3 frag_LightOrigin;	// The light's position
uniform vec4 frag_LightColor; 	// Its colour
uniform float frag_LightAttenuation;	// We could call this its luminosity
//uniform vec2 frag_ScreenResolution; // We need this because SFML reverses the Y axis. Note: we could just be using a single float for the Y resolution. 

//out vec4 FragColor;

void main()
{		
	//vec4 diffuse = texture2D(texture, gl_TexCoord[0].xy);
	//vec2 baseDistance =  gl_FragCoord.xy; // Storing our pixel's position
	
	//baseDistance.y = frag_ScreenResolution.y-baseDistance.y; // Fixing the reversed Y axis
	
	//vec2 distance=frag_LightOrigin - baseDistance; // Getting the distance between our light and the pixel, as a 2D vector
	
	//float linear_distance = length(distance); // Getting the linear distance through a normalization 
	//float attenuation=1.0/( frag_LightAttenuation*linear_distance + frag_LightAttenuation*linear_distance);	// The closer our pixel is to the light source, the smaller the light attenuation will be. 
	
	//vec4 lightColor = vec4(frag_LightColor, 1.0);
	//vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * lightColor; // We multiply our light's colour with the attenuation vector, which will give us the final 'luminosity' of our pixel. 
	
	//color = color * diffuse;
	//gl_FragColor = color; // We give our pixel its final colour. 

	
	vec3 light = frag_LightOrigin;
	float distance = sqrt(pow(gl_FragCoord.x - light.x, 2) + pow(gl_FragCoord.y - light.y, 2));

    if (floor(light.x) == floor(gl_FragCoord.x) && floor(light.y) == floor (gl_FragCoord.y)) 
        distance = 0.1;

    if (distance > light.z) 
        distance = light.z;

	float attenuation=1.0/( frag_LightAttenuation*distance);

    vec2 pos = gl_TexCoord[0].xy ; 
	vec4 diffuse = texture2D(texture,pos);
	
	frag_LightColor = vec4(attenuation, attenuation, attenuation, attenuation) * frag_LightColor;
    gl_FragColor = mix(diffuse, frag_LightColor, 1.0-(distance/light.z)); 
}
