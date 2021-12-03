/**************************************************
DepthShader is a shader that has the uniform
 variables for modelview, projection, the
 parameters for the materials, and a list of lights.
*****************************************************/
#include "Shader.h"
#include <glm/glm.hpp>
// #include <glm/gtc/type_ptr.hpp>
#ifndef __DEPTHSHADER_H__
#define __DEPTHSHADER_H__

struct DepthShader : Shader {
    // modelview and projection
    glm::mat4 modelview = glm::mat4(1.0f); GLuint modelview_loc;
    glm::mat4 projection = glm::mat4(1.0f); GLuint projection_loc;
    
    void initUniforms(){
        modelview_loc  = glGetUniformLocation( program, "modelview" );
        projection_loc = glGetUniformLocation( program, "projection" );
    }
    void setUniforms(){
        glUniformMatrix4fv(modelview_loc, 1, GL_FALSE, &modelview[0][0]);
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection[0][0]);
    }
};

#endif 
