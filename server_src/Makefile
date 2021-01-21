#OBJS specifies which files to compile as part of the project
OBJS = helper.cpp server.cpp ThClient.cpp ThServer.cpp GameHandler.cpp GamePlay.cpp ../common_src/*.cpp ../editor_src/ConfigManager/*.cpp
#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Werror

COMPILER_FLAGS += -Wall -Werror -pedantic -pedantic-errors

# Para optimizar el binario resultante lo mejor posible
COMPILER_FLAGS += -O3

# Para valgrind o debug
COMPILER_FLAGS += -ggdb -DDEBUG -fno-inline -lyaml-cpp

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -pthread

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = server

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
