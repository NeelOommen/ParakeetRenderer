#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinate;
layout (location = 2) in vec3 norm;

out vec4 vCol;
out vec2 textureCoord;
out vec3 normalVector;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main(){
    gl_Position = projection * view * model * vec4(position, 1.0);
    vCol = vec4(clamp(position, 0.0, 1.0), 1.0);

    textureCoord = textureCoordinate;

    normalVector = mat3(transpose(inverse(model))) * norm;

    fragPos = (model * vec4(position, 1.0)).xyz;
}