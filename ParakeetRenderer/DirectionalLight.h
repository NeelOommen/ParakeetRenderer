#pragma once
#include "Light.h"
#include "Shader.h"

class Shader;
class Light;

class DirectionalLight :
    public Light
{
public:
    DirectionalLight();
    DirectionalLight(GLfloat r, GLfloat g, GLfloat b, 
            GLfloat aIntensity, GLfloat dIntensity,
            GLfloat xDir, GLfloat yDir, GLfloat zDir
        );
    ~DirectionalLight();

    void useLight(Shader* shader);

    glm::mat4 calculateLightTransform();
private:
    glm::vec3 direction;
};

