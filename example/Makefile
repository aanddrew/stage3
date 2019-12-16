#the files to compile as part of project
OBJS = example.cpp ../stage3/graphics/*cpp ../stage3/graphics/stbi/stb_image.c CameraController.cpp ../stage3/Window.cpp

#the compiler we will use
CC = g++

# the flags for the compiler 
#-w surpresses all warnings
COMPILER_FLAGS = -std=c11 -w

#the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lGL -lglut -lGLEW -lm

#the name of our executable
OBJ_NAME = a.out

all:
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
