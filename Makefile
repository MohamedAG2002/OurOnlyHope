build-web:
	em++ src/*.cpp src/Managers/*.cpp src/Scenes/*.cpp src/Entities/*.cpp src/Listeners/*.cpp src/Utils/*.cpp src/UI/*.cpp src/Components/*.cpp -Wall -std=c++20 -Ilibs/include/ -Llibs/lib/ -lraylib -lbox2d -lyaml-cpp -s USE_GLFW=3 --preload-file assets --preload-file data -o ooh.html
