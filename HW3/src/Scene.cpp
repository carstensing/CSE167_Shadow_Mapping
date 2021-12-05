/**************************************************
Scene.cpp contains the implementation of the draw command
*****************************************************/
#include "Scene.h"
#include "Cube.h"
#include "Obj.h"

// The scene init definition 
#include "Scene.inl"


using namespace glm;
void Scene::drawDepth(DepthShader* depth_shader) {
    glUseProgram(depth_shader->program);
    light["sun"]->light_camera->computeMatrices();
    depth_shader->projection = light["sun"]->light_camera->proj;

    // Define stacks for depth-first search (DFS)
    std::stack < Node* > dfs_stack;
    std::stack < mat4 >  matrix_stack;

    // Initialize the current state variable for DFS
    Node* cur = node["world"]; // root of the tree
    mat4 cur_VM = light["sun"]->light_camera->view;

    dfs_stack.push(cur);
    matrix_stack.push(cur_VM);

    while (!dfs_stack.empty()) {
        // Detect whether the search runs into infinite loop by checking whether the stack is longer than the size of the graph.
        // Note that, at any time, the stack does not contain repeated element.
        if (dfs_stack.size() > node.size()) {
            std::cerr << "Error: The scene graph has a closed loop." << std::endl;
            exit(-1);
        }

        // top-pop the stacks
        cur = dfs_stack.top();        dfs_stack.pop();
        cur_VM = matrix_stack.top();     matrix_stack.pop();

        // draw all the models at the current node
        for (unsigned int i = 0; i < cur->models.size(); i++) {
            // Prepare to draw the geometry. Assign the modelview and the material.

            depth_shader->modelview = cur_VM * cur->modeltransforms[i]; // HW3: Without updating cur_VM, modelview would just be camera's view matrix.

            // The draw command
            depth_shader->setUniforms();
            (cur->models[i])->geometry->draw();
        }

        // Continue the DFS: put all the child nodes of the current node in the stack
        for (unsigned int i = 0; i < cur->childnodes.size(); i++) {
            dfs_stack.push(cur->childnodes[i]);
            // (HW3 hint: you should do something here)
            matrix_stack.push(cur_VM * cur->childtransforms[i]);
        }

    } // End of DFS while loop.
}


void Scene::drawSurface(void){
    glUseProgram(surface_shader->program);
    // Pre-draw sequence: assign uniforms that are the same for all Geometry::draw call.  These uniforms include the camera view, proj, and the lights.  These uniform do not include modelview and material parameters.
    camera->computeMatrices();
    surface_shader-> view = camera->view;
    surface_shader->projection = camera->proj;

    // do this?
    // light["sun"]->light_camera ->computeMatrices();
    // surface_shader->viewLight = light["sun"]->light_camera->view;
    // surface_shader->projectionLight = light["sun"]->light_camera->view;

    surface_shader->nlights = light.size();
    surface_shader->lightpositions.resize( surface_shader->nlights );
    surface_shader->lightcolors.resize( surface_shader->nlights );
    int count = 0;
    for ( std::pair<std::string,Light*> entry : light ){
        surface_shader->lightpositions[ count ] = (entry.second)->position;
        surface_shader->lightcolors[ count ] = (entry.second)->color;
        count++;
    }
    
    // Define stacks for depth-first search (DFS)
    std::stack < Node* > dfs_stack;
    std::stack < mat4 >  matrix_stack;
    
    // Initialize the current state variable for DFS
    Node* cur = node["world"]; // root of the tree
    mat4 cur_VM = camera->view; 
    
    dfs_stack.push( cur );
    matrix_stack.push( cur_VM );
    
    while( ! dfs_stack.empty() ){
        // Detect whether the search runs into infinite loop by checking whether the stack is longer than the size of the graph.
        // Note that, at any time, the stack does not contain repeated element.
        if (dfs_stack.size() > node.size() ){
            std::cerr << "Error: The scene graph has a closed loop." << std::endl;
            exit(-1);
        }
        
        // top-pop the stacks
        cur = dfs_stack.top();        dfs_stack.pop();
        cur_VM = matrix_stack.top();     matrix_stack.pop();
        
        // draw all the models at the current node
        for ( unsigned int i = 0; i < cur->models.size(); i++ ){
            // Prepare to draw the geometry. Assign the modelview and the material.
            
            surface_shader->modelview = cur_VM * cur->modeltransforms[i]; // HW3: Without updating cur_VM, modelview would just be camera's view matrix.
            surface_shader->material  = ( cur->models[i] )->material;
            
            // The draw command
            surface_shader->setUniforms();
            ( cur->models[i] )->geometry->draw();
        }
        
        // Continue the DFS: put all the child nodes of the current node in the stack
        for ( unsigned int i = 0; i < cur->childnodes.size(); i++ ){
            dfs_stack.push( cur->childnodes[i] );
            // (HW3 hint: you should do something here)
            matrix_stack.push( cur_VM * cur->childtransforms[i] );
        }
        
    } // End of DFS while loop.
    
}



