#version 330

in vec4 vCol;
in vec2 textureCoord;
in vec3 normalVector;
in vec3 fragPos;

out vec4 colour;

void main(){
    colour = vCol;
}