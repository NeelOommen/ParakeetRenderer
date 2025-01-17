#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinate;
layout (location = 2) in vec3 norm;
layout (location = 3) in vec3 col;

//out vec4 vCol;
out vec2 textureCoord;
out vec3 normalVector;
out vec3 fragPos;
out vec4 directionalLightSpacePos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform vec4 directionalLightTransform;

void main(){
    gl_Position = projection * view  *model * vec4(position, 1.0f);
    //gl_Position = vec4(position.x * 0.4, position.y * 0.4, position.z, 1.0f);
    directionalLightSpacePos = directionalLightTransform * model * vec4(position, 1.0f);

    textureCoord = textureCoordinate;
    normalVector = mat3(transpose(inverse(model))) * norm;
    fragPos = (model * vec4(position, 1.0)).xyz;
}