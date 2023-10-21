build-web:
	em++ ../src/*.cpp ../src/Managers/*.cpp ../src/Scenes/*.cpp ../src/Entities/*.cpp ../src/Listeners/*.cpp ../src/Utils/*.cpp ../src/UI/*.cpp ../src/Components/*.cpp -Wall -I../libs/include/ -Llibs/ -lraylib -lbox2d -lyaml-cpp -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 --preload-file ../assets --preload-file ../data -o index.html
