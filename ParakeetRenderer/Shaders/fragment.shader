#version 330

//in vec4 vCol;
in vec2 textureCoord;
in vec3 normalVector;
in vec3 fragPos;
in vec4 directionalLightSpacePos;

struct Light{
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight{
    Light base;
    vec3 direction;
};

struct Material{
    float specularIntensity;
    float shininess;
};

out vec4 frag_colour;
uniform sampler2D baseTextureSampler;
uniform sampler2D directionalShadowMap;

uniform DirectionalLight ambientLight;
uniform Material material;
uniform vec3 eyePos;

vec4 calcLightByDirection(Light light, vec3 direction, float sFactor){
    vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;

    float diffuseFactor = max(dot(normalize(normalVector), normalize(direction)), 0.0f);
    vec4 diffuseColour = vec4(light.colour, 1.0f) * light.diffuseIntensity * diffuseFactor;

    vec4 specColour = vec4(0,0,0,0);

    if(diffuseFactor > 0.0f){
        vec3 fragToEye = normalize(eyePos - fragPos);
        vec3 reflVertex = normalize(reflect(direction, normalize(normalVector)));

        float specFactor = dot(fragToEye, reflVertex);
        if(specFactor > 0.0f){
            specFactor = pow(specFactor, material.shininess);
            specColour = vec4(light.colour * material.specularIntensity * specFactor, 1.0f);
        }
    }

    return (ambientColour + (1.0f - sFactor) * (diffuseColour + specColour));
}

float calcDirectionalShadowFactor(DirectionalLight light){
    vec3 projCoords = directionalLightSpacePos.xyz / directionalLightSpacePos.w;
    projCoords = (projCoords * 0.5) + 0.5;

    float current = projCoords.z;

    vec3 n = normalize(normalVector);
	vec3 lightDir = normalize(light.direction);

    float bias = max(0.05 * (1 - dot(n, lightDir)), 0.005);

	float shadow = 0.0;

    vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
	for(int i = -1; i<=1; i++){
		for(int j = -1; j<=1; j++){
			float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(i,j) * texelSize).r;
			shadow += current - bias > pcfDepth ? 1.0: 0.0;
		}
	} 

	shadow /= 9.0;

	if(projCoords.z > 1.0){
		shadow = 0.0;
	}

	return shadow;
}

vec4 calcDirectionalLight(){
    float shadowFactor = calcDirectionalShadowFactor(ambientLight);
    return calcLightByDirection(ambientLight.base, ambientLight.direction, shadowFactor);
}

void main(){
    vec4 finalLightEffect = calcDirectionalLight();
    frag_colour = texture(baseTextureSampler, textureCoord) * finalLightEffect;
}