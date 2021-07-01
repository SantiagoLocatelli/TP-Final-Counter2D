#OBJS specifies which files to compile as part of the project
OBJS = test_main.cpp ../Player.cpp ../World.cpp ../Weapon.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lbox2d -lcppunit

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = test.exe

#This is the target that compiles our executable
run: build
	./$(OBJ_NAME)

build: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
