build-windows:
	x86_64-w64-mingw32-g++ ../src/*.cpp ../src/Managers/*.cpp ../src/Scenes/*.cpp ../src/Entities/*.cpp ../src/Listeners/*.cpp ../src/Utils/*.cpp ../src/UI/*.cpp ../src/Components/*.cpp -Wall -static-libgcc -static-libstdc++ -I../libs/include -Llib/ -lraylib -lbox2d -lyaml-cpp -lgdi32 -lwinmm -o ooh

build-web:
	emcc src/*.cpp src/Managers/*.cpp src/Scenes/*.cpp src/Entities/*.cpp src/Listeners/*.cpp src/Utils/*.cpp src/UI/*.cpp src/Components/*.cpp -Wall -std=c++20 -Ilibs/include libs/lib/libraylib.a libs/lib/libbox2d.a libs/lib/libyaml.a -o ooh.html

run:
	wine ooh.exe
