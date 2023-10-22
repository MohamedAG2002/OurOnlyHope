SRC_PATH = ../src
INCLUDE_PATH = -I../libs/include/
LIBS_PATH = -L.
COMILER = x86_64-w64-mingw32-g++
FLAGS = -Wall -std=c++20 -Wreorder -Wunused-variable
LIBS = libraylibdll.a -lbox2d -lyaml-cpp -lgdi32 -lwinmm
NAME = ooh

build:
	${COMILER} ${SRC_PATH}/*.cpp ${SRC_PATH}/Managers/*.cpp ${SRC_PATH}/Scenes/*.cpp ${SRC_PATH}/Components/*.cpp ${SRC_PATH}/Entities/*.cpp ${SRC_PATH}/Listeners/*.cpp ${SRC_PATH}/UI/*.cpp ${SRC_PATH}/Utils/*.cpp ${INCLUDE_PATH} ${LIBS_PATH} ${FLAGS} ${LIBS} -o ${NAME}	

run:
	wine ${NAME}.exe
