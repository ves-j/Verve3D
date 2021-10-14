#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the current position of the mesh from the Vertex Shader
in vec3 crntPos;

// Imports the normal from the Vertex Shader
in vec3 Normal;

// Inputs the color from the Vertex Shader
//in vec3 color;

// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;



// Gets the Texture Unit from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;

// Imgui uniforms
uniform int textureOn;
uniform vec4 color;


// Gets the color of the light from the main function
uniform vec4 lightColor;

// Gets the position of the light from the main function
uniform vec3 lightPos;

// Gets the recent position of the camera
uniform vec3 camPos;

// Type of light selected
uniform int lightType;



vec4 pointLight()
{
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);						// quadratic equation for point light in computer graphics


	// ambient
	float ambient = 0.4f;

	// diffuse lighting
	vec3 normal = normalize(Normal);													// normalize() gives you the direction of a vector whereas length() gives you length of a vector
	vec3 lightDirection = normalize(lightVec);											// normalize() — calculates the unit vector (length 1) in the same direction as the original vector
	float diffuse = max(dot(normal, lightDirection), 0.0f);								// dot product (multiplying vectors) is to get normal numbers (scalar) instead of vectors
																						// dot product gives you the angle (space) between two vectors


	// specular lighting (depended on camera angle)
	float specularLight = 0.50f;														// intensity of specular light
	vec3 viewDirection = normalize(camPos - crntPos);									// view from camera to mesh (camera -> mesh)
	vec3 reflectionDirection = reflect(-lightDirection, normal);						// This is how we reflect the light on the surface of the mesh
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);		// *Calculating how much specular light we have at a certain angle of the
																						// camera (larger angle between view direction = weaker specular)
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}




// Directional light always has static light direction light sun rays
vec4 directionalLight()
{
	// ambient
	float ambient = 0.4f;

	// diffuse lighting
	vec3 normal = normalize(Normal);													// normalize() gives you the direction of a vector whereas length() gives you length of a vector
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));							// normalize() — calculates the unit vector (length 1) in the same direction as the original vector
	float diffuse = max(dot(normal, lightDirection), 0.0f);								// dot product (multiplying vectors) is to get normal numbers (scalar) instead of vectors


	// specular lighting (depended on camera angle)
	float specularLight = 0.50f;														// intensity of specular light
	vec3 viewDirection = normalize(camPos - crntPos);									// view from camera to mesh (camera -> mesh)
	vec3 reflectionDirection = reflect(-lightDirection, normal);						// This is how we reflect the light on the surface of the mesh
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);		// *Calculating how much specular light we have at a certain angle of the
																						// camera (larger angle between view direction = weaker specular)
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}



// for spot light, you need two cones to make the rounds smooth
vec4 spotLight()
{
	float outerCone = 0.90f;															// this is the cosine value of the angles to cut off extra calculations
	float innerCone = 0.95f;


	// ambient
	float ambient = 0.4f;


	// diffuse lighting
	vec3 normal = normalize(Normal);													// normalize() gives you the direction of a vector whereas length() gives you length of a vector
	vec3 lightDirection = normalize(lightPos - crntPos);								// normalize() — calculates the unit vector (length 1) in the same direction as the original vector
	float diffuse = max(dot(normal, lightDirection), 0.0f);								// dot product (multiplying vectors) is to get normal numbers (scalar) instead of vectors


	// specular lighting (depended on camera angle)
	float specularLight = 0.50f;														// intensity of specular light
	vec3 viewDirection = normalize(camPos - crntPos);									// view from camera to mesh (camera -> mesh)
	vec3 reflectionDirection = reflect(-lightDirection, normal);						// This is how we reflect the light on the surface of the mesh
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);		// *Calculating how much specular light we have at a certain angle of the
																						// camera (larger angle between view direction = weaker specular)
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);						// calculating the central angle using dot product

	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);	// how intense the light will be based on the position of the mesh

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}


void main()
{
	if (textureOn == 1)
	{
		FragColor = pointLight();

		if (lightType == 0)
		{
			FragColor = pointLight();
		}
		
		if (lightType == 1)
		{
			FragColor = directionalLight();
		}

		if (lightType == 2)
		{
			FragColor = spotLight();
		}
		
	}
	
	if (textureOn != 1)
	{
		FragColor = color;
	}
	
}