/**************************************************
Scene.inl contains the definition of the scene graph
*****************************************************/
#include "Scene.h"
#include "Cube.h"
#include "Obj.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace glm;
void Scene::init(void){
    // Create a geometry palette
    geometry["cube"] = new Cube;
    geometry["teapot"] = new Obj;
    geometry["bunny"] = new Obj;
    geometry["cube"] -> init();
    geometry["teapot"] -> init("models/teapot.obj");
    geometry["bunny"] -> init("models/bunny.obj");
    
    // Create a material palette
    material["wood"] = new Material;
    material["wood"] -> ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["wood"] -> diffuse = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> specular = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> shininess = 100.0f;
    
    material["ceramic"] = new Material;
    material["ceramic"] -> ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["ceramic"] -> diffuse = vec4(0.95f, 0.95f, 0.95f, 1.0f);
    material["ceramic"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["ceramic"] -> shininess = 150.0f;
 
    material["silver"] = new Material;
    material["silver"] -> ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["silver"] -> diffuse = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    material["silver"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["silver"] -> shininess = 50.0f;

    material["gold"] = new Material;
    material["gold"] -> ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["gold"] -> diffuse = vec4(0.99f, 0.8f, 0.0f, 1.0f);
    material["gold"] -> specular = vec4(0.99f, 0.99f, 0.99f, 1.0f);
    material["gold"] -> shininess = 50.0f;
    
    material["turquoise"] = new Material;
    material["turquoise"] -> ambient = vec4(0.1f, 0.2f, 0.17f, 1.0f);
    material["turquoise"] -> diffuse = vec4(0.2f, 0.375f, 0.35f, 1.0f);
    material["turquoise"] -> specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    material["turquoise"] -> shininess = 100.0f;

    material["bulb"] = new Material;
    material["bulb"] -> ambient = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    material["bulb"] -> emision = vec4(1.0f, 0.2f, 0.1f, 1.0f);
    material["bulb"] -> shininess = 200.0f;

    material["concrete"] = new Material;
    material["concrete"]->ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["concrete"]->diffuse = vec4(0.4f, 0.4f, 0.4f, 1.0f);
    material["concrete"]->specular = vec4(0.01f, 0.01f, 0.01f, 1.0f);
    material["concrete"]->shininess = 100.0f;
    
    // Create a model palette
    model["teapot1"] = new Model;
    model["teapot1"] -> geometry = geometry["teapot"];
    model["teapot1"] -> material = material["silver"];
    model["teapot2"] = new Model;
    model["teapot2"] -> geometry = geometry["teapot"];
    model["teapot2"] -> material = material["turquoise"];
    model["throne piece"] = new Model;
    model["throne piece"] -> geometry = geometry["cube"];
    model["throne piece"] -> material = material["gold"];
    model["bunny"] = new Model;
    model["bunny"] -> geometry = geometry["bunny"];
    model["bunny"] -> material = material["ceramic"];
    model["concrete block"] = new Model;
    model["concrete block"]->geometry = geometry["cube"];
    model["concrete block"]->material = material["concrete"];
    model["bulb"] = new Model;
    model["bulb"] -> geometry = geometry["teapot"];
    model["bulb"] -> material = material["bulb"];
    
    // Create a light palette
    light["sun"] = new Light;
    light["sun"]->position = vec4(3.0f, 2.0f, 1.0f, 0.0f);
    light["sun"]->color = 1.0f * vec4(1.0f, 1.0f, 1.0f, 1.0f);
    light["sun"]->light_camera->target_default = vec3(0.0f, 1.0f, 0.0f);
    light["sun"]->light_camera->eye_default = vec3(light["sun"]->position) * 10.0f;
    light["sun"]->light_camera->up_default = vec3(0.0f, 1.0f, 0.0f);
    light["sun"]->light_camera->reset();
    
    // Build the scene graph
    node["throne"] = new Node;
    node["throne seat"] = new Node;
    node["throne arm"] = new Node;
    node["throne back"] = new Node;
    node["teapot1"] = new Node;
    node["teapot2"] = new Node;
    node["bunny"] = new Node;
    node["floor"] = new Node;
    
    node["throne"] -> childnodes.push_back( node["throne seat"] );
    node["throne"] -> childtransforms.push_back( translate(vec3(0.0f,0.0f,0.0f)) );
    node["throne"] -> childnodes.push_back( node["throne arm"] );
    node["throne"] -> childtransforms.push_back( translate(vec3(0.6f,0.0f,0.4f)) );
    node["throne"] -> childnodes.push_back( node["throne arm"] );
    node["throne"] -> childtransforms.push_back( translate(vec3(-0.6f,0.0f,0.4f)) );
    node["throne"] -> childnodes.push_back(node["throne back"]);
    node["throne"] -> childtransforms.push_back(translate(vec3(0.0f, 0.0f, 0.0f)));
    
    node["throne arm"] -> models.push_back( model["throne piece"] );
    node["throne arm"] -> modeltransforms.push_back( translate(vec3(0.0f,0.37f,-0.3f)) * scale(vec3(0.2f,0.75f, 1.4f)) );
    
    node["throne seat"] -> models.push_back( model["throne piece"] );
    node["throne seat"] -> modeltransforms.push_back( translate(vec3(0.0f,0.25f,0.05f)) * scale(vec3(1.0f,0.5f,1.25f)) );

    node["throne seat"] -> childnodes.push_back(node["bunny"]);
    node["throne seat"] -> childtransforms.push_back(translate(vec3(0.0f, 0.7f, 0.0f)) * rotate(45.0f * float(M_PI) / 180.0f, vec3(0.0f, 1.0f, 0.0f)));

    node["bunny"]->models.push_back(model["bunny"]);
    node["bunny"]->modeltransforms.push_back(scale(vec3(1.0f, 1.0f, 1.0f))* scale(vec3(0.2f)));

    node["throne back"] -> models.push_back(model["throne piece"]);
    node["throne back"] -> modeltransforms.push_back(translate(vec3(0.0f, 1.0f, -0.45f)) * scale(vec3(1.25f, 2.0f, 0.3f)));

    node["floor"]->models.push_back(model["concrete block"]);
    node["floor"]->modeltransforms.push_back(scale(vec3(10.0f, 0.1f, 10.0f)));
    
    node["world"] -> childnodes.push_back( node["throne"] );
    node["world"] -> childtransforms.push_back( mat4(1.0f) );
    node["world"]->childnodes.push_back(node["floor"]);
    node["world"]->childtransforms.push_back(translate(vec3(0.0f, 0.0f, 0.0f)));
    node["world"]->models.push_back(model["bulb"]);
    node["world"]->modeltransforms.push_back(translate(vec3(0.0f, 2.0f, 0.0f))* scale(vec3(0.2f)));

    
    // Put a camera
    camera = new Camera;
    camera -> target_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> eye_default = vec3( 0.0f, 1.0f, 5.0f );
    camera -> up_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> reset();
    
    // Initialize shader
    surface_shader = new SurfaceShader;
    surface_shader->read_source("shaders/projective.vert", "shaders/lighting.frag");
    surface_shader->compile();
    surface_shader->initUniforms();
}
