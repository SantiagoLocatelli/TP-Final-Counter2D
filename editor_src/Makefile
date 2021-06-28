#OBJS specifies which files to compile as part of the project
OBJS = main.cpp ../Sdl/sdl_texture.cpp ../Sdl/sdl_mixer.cpp ../Sdl/sdl_window.cpp ../Sdl/sdl_renderer.cpp ../Sdl/button.cpp ../Sdl/dot.cpp ../Sdl/draggable.cpp editor.cpp TextureFactory.cpp TextureMap.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lyaml-cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
