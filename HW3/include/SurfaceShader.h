/**************************************************
SurfaceShader is a shader that has the uniform
 variables for model, projection, the
 parameters for the materials, and a list of lights.
*****************************************************/
#include "Shader.h"
#include "Material.h"
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#ifndef __SURFACESHADER_H__
#define __SURFACESHADER_H__

struct SurfaceShader : Shader {
    // model and projection
    glm::mat4 view = glm::mat4(1.0f); GLuint view_loc;
    glm::mat4 model = glm::mat4(1.0f); GLuint model_loc;
    glm::mat4 projection = glm::mat4(1.0f); GLuint projection_loc;

    // light 
    glm::mat4 viewLS = glm::mat4(1.0f); GLuint viewLS_loc;
    glm::mat4 projLS = glm::mat4(1.0f); GLuint projLS_loc;

    //Textures
    GLuint depthMap;
    GLuint depthMap_loc;

    // material parameters
    Material* material;
    GLuint ambient_loc;
    GLuint diffuse_loc;
    GLuint specular_loc;
    GLuint emision_loc;
    GLuint shininess_loc;
    
    // lights
    GLboolean enablelighting = GL_FALSE; // are we lighting at all (global).
    GLint nlights = 0;               // number of lights used
    std::vector<glm::vec4> lightpositions; // positions of lights
    std::vector<glm::vec4> lightcolors; // colors of lights
    GLuint enablelighting_loc;
    GLuint nlights_loc;
    GLuint lightpositions_loc;
    GLuint lightcolors_loc;
    
    
    void initUniforms(){
        depthMap_loc = glGetUniformLocation(program, "depthMap");
        view_loc  = glGetUniformLocation( program, "view" );
        model_loc  = glGetUniformLocation( program, "model" );
        projection_loc = glGetUniformLocation( program, "projection" );
        viewLS_loc = glGetUniformLocation(program, "viewLS");
        projLS_loc = glGetUniformLocation(program, "projLS");
        ambient_loc    = glGetUniformLocation( program, "ambient" );
        diffuse_loc    = glGetUniformLocation( program, "diffuse" );
        specular_loc   = glGetUniformLocation( program, "specular" );
        emision_loc    = glGetUniformLocation( program, "emision" );
        shininess_loc  = glGetUniformLocation( program, "shininess" );
        enablelighting_loc = glGetUniformLocation( program, "enablelighting" );
        nlights_loc = glGetUniformLocation( program, "nlights" );
        lightpositions_loc = glGetUniformLocation( program, "lightpositions" );
        lightcolors_loc = glGetUniformLocation( program, "lightcolors" );
        
    }
    void setUniforms(){
        glUniform1f(depthMap_loc, depthMap);
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(viewLS_loc, 1, GL_FALSE, &viewLS[0][0]);
        glUniformMatrix4fv(projLS_loc, 1, GL_FALSE, &projLS[0][0]);
        glUniform4fv( ambient_loc  , 1, &(material->ambient[0])  );
        glUniform4fv( diffuse_loc  , 1, &(material->diffuse[0])  );
        glUniform4fv( specular_loc , 1, &(material->specular[0]) );
        glUniform4fv( emision_loc  , 1, &(material->emision[0])  );
        glUniform1fv( shininess_loc, 1, &(material->shininess)   );
        glUniform1i( enablelighting_loc, enablelighting );
        glUniform1i( nlights_loc, nlights );
        glUniform4fv( lightpositions_loc, GLsizei(nlights), &lightpositions[0][0] );
        glUniform4fv( lightcolors_loc, GLsizei(nlights), &lightcolors[0][0] );
    }
};

#endif 
