#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../stage3/stage3.h"
#include "CameraController.h"
#include <cassert>

//program begins here
#define fov 70.0f
#define nearZ 0.1f
#define farZ 200.0f

#define WIDTH 1600
#define HEIGHT 900

glm::mat4 Projection = glm::perspective(fov, (float)(WIDTH*1.0/HEIGHT), nearZ, farZ);

int main()
{
  //window creation
  s3::Window window("stage3 rules", WIDTH, HEIGHT);
  SDL_Window* sdlWindow = window.getSDLWindow();

  //==============END OF WINDOW CREATION==============

  //=========creation of shader, texture, mesh========

  Shader shader("res/shaders/basicVertexShader.GLSL", 
    "res/shaders/basicFragmentShader.GLSL");
  shader.bind();


  Texture tex("res/textures/earth_squished.png");
  tex.bind();

  Mesh mesh("res/models/normalSphere.obj");
  mesh.bind();


  Texture tex2("res/textures/cobbles01.png");
  tex2.bind();

  Mesh mesh2("res/models/normalCube.obj");

  //===========END TEXTURE & SHADER STUFF=============

  //uniforms for our shader

  shader.createUniform("perspective");
  shader.setUniform("perspective", Projection);

  Camera camera;
  CameraController camControl(&camera);

  shader.createUniform("view");
  shader.setUniform("view", camera.getMatrix());

  //create a model matrix to translate our objects

  shader.createUniform("model");
  shader.setUniform("model", glm::translate(glm::mat4(1.0), glm::vec3(1.0f, 0.0f, 0.0f)));


  //MAIN LOOP STUFF
  bool running = true;
  SDL_Event e;

  bool mouseClicked = false;
  while(running)
  {
  	while(SDL_PollEvent(&e))
  	{
      switch(e.type)
      {
        case SDL_QUIT:
          running = false;
        break;

        //keyboard inputs
        case SDL_KEYDOWN:
          camControl.keyInput(e.key.keysym.sym, true);
        break;
        case SDL_KEYUP:
          camControl.keyInput(e.key.keysym.sym, false);
        break;

        //mouse inputs
        case SDL_MOUSEBUTTONDOWN:
          mouseClicked = true;
        break;
        case SDL_MOUSEBUTTONUP:
          mouseClicked = false;
        break;
        case SDL_MOUSEMOTION:
          if (mouseClicked)
            camControl.mouseInput(e.motion.xrel, e.motion.yrel);
        break;
      }
  	}
    camControl.update();
    //update the view uniform because our camera moved when we just updated it
    shader.setUniform("view", camera.getMatrix());

    //we have to clear the window (clear the color & depth bits)
    window.clear();

  	//drawing takes place here
    shader.bind();

    //drawing first mesh
    texture.bind();
    //in order to have the objects in different places, 
    //we must translate them with a different model vector
    shader.setUniform("model", glm::translate(glm::mat4(1.0), glm::vec3(2.0f, 0.0f, 0.0f)));
    mesh.bind();
    mesh.draw();

    //drawing second mesh
    tex2.bind();
    shader.setUniform("model", glm::translate(glm::mat4(1.0), glm::vec3(-2.0f, 0.0f, 0.0f)));
    mesh2.bind();
    mesh2.draw();

    //then we have to render (swap the buffer)
    window.render();
  }
	return 0;
}