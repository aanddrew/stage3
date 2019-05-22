~ReadMe for the example~

--------------------Building----------------------
===LINUX===
To build, just type make if you are on linux.
The executable is a.out - so type ./a.out to run it.

Dependencies:
SDL2: libsdl2-dev
OpenGl: libglew-dev
OpenGL mathematics (glm): libglm-dev 

If you are on a debian based distro just type this to install them:

sudo apt-get install libsdl2-dev libglew-dev libglm-dev

===WINDOWS===
I actually don't really know.
Look up how to install the three libraries above.
And then the linking should be done in the fashion of the Makefile.

Anything that ends in .cpp or .c should be compiled and linked.

--------------------------------------------------

--------------------Tinkering---------------------

To change width and height of your screen, change the #define macros in example.cpp

To change which textures and meshes are used for each object, edit lines 35-45
of example.cpp. It should be pretty self explanatory.

Try creating you own uniforms for the shader. Make some wacky transformations.

--------------------------------------------------

That's about it.
Have fun!