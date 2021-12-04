/**************************************************
Light is a class for a camera object.
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "DepthShader.h"
#include "Camera.h"

#ifndef __LIGHT_H__
#define __LIGHT_H__

#define SHADOW_WIDTH 1024
#define SHADOW_HEIGHT 1024

class Light {
public:
    DepthShader* depth_shader;
    Camera* light_camera;

    GLuint shadowWidth = SHADOW_WIDTH;
    GLuint shadowHeight = SHADOW_HEIGHT;

    glm::vec4 position = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    GLuint depthMap; // texture
    GLuint depthMapFBO; // frame buffer object

    Light();
    
    ~Light() {
        delete depth_shader;
        delete light_camera;
    }
};

#endif 
