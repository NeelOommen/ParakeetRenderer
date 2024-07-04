#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {
    direction = glm::vec3(0.0f, -1.0f, 0.0f);

    lightProjection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 20.0f);
}

DirectionalLight::DirectionalLight(GLfloat r, GLfloat g, GLfloat b,
    GLfloat aIntensity, GLfloat dIntensity,
    GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(r,g,b,aIntensity,dIntensity)
{
    direction = glm::vec3(xDir, yDir, zDir);

    lightProjection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 20.0f);
}

DirectionalLight::~DirectionalLight() {

}

glm::mat4 DirectionalLight::calculateLightTransform() {
    return lightProjection * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void DirectionalLight::useLight(Shader* shader) {
    glUniform3f(shader->getShaderUniformLocation("ambientLight.base.colour"), lightColour.x, lightColour.y, lightColour.z);
    glUniform1f(shader->getShaderUniformLocation("ambientLight.base.ambientIntensity"), ambientIntensity);

    glUniform3f(shader->getShaderUniformLocation("ambientLight.direction"), direction.x, direction.y, direction.z);
    glUniform1f(shader->getShaderUniformLocation("ambientLight.base.diffuseIntensity"), diffuseIntensity);
}