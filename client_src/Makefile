#OBJS specifies which files to compile as part of the project
OBJS = *.cpp ./../common_src/SDLWrappers/*.cpp ./Map/*.cpp ../common_src/*.cpp

#CC specifies which compiler we're using
CC = g++ -g

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Werror

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -pthread -lyaml-cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = client

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	$(RM) -f ./common_src/*.o ./client_src/*.o client
