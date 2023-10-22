SRC_FILES = ../src/*.cpp ../src/Managers/*.cpp ../src/Scenes/*.cpp ../src/Entities/*.cpp ../src/Listeners/*.cpp ../src/Utils/*.cpp ../src/UI/*.cpp ../src/Components/*.cpp

COMPILER = em++
LIB_PATH = -Llibs/
LIBS = -lraylib -lbox2d -lyaml-cpp
INCLUDE_PATH = -I../libs/include/
FLAGS = -Wall -Wreorder-ctor -std=c++20 -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 --preload-file ../assets --preload-file ../data
NAME = index

build:
	${COMPILER} ${SRC_FILES} ${INCLUDE_PATH} ${LIB_PATH} ${LIBS} ${FLAGS} -o ${NAME}.html

run:
	python3 -m http.server
