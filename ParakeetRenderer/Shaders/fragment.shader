#version 330

//in vec4 vCol;
in vec2 textureCoord;
in vec3 normalVector;
in vec3 fragPos;

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

uniform DirectionalLight ambientLight;
uniform Material material;
uniform vec3 eyePos;

vec4 calcLightByDirection(Light light, vec3 direction){
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

    return (ambientColour + (diffuseColour + specColour));
}

vec4 calcDirectionalLight(){
    return calcLightByDirection(ambientLight.base, ambientLight.direction);
}

void main(){
    vec4 finalLightEffect = calcDirectionalLight();
    frag_colour = texture(baseTextureSampler, textureCoord) * finalLightEffect;
}