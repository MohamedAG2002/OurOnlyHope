# Our Only Hope
As the only capable man left in your village, you--a medieval peasant--are supposed to defend your hometown from the oncoming horde of zombies. They are angry and will not stop until everyone in the village is eaten. You are only armed with a spear and, with the help of a local doctor, you are allowed to choose between 4 potions that will help in your zombie-slaying journey. Be brave, peasant. You our only hope.

# Build
The project uses cmake as the build system. You would have to install it and configure it before doing anything. Remember, if you have any issues with building this project, you can either contact me or make a new issue on this GitHub page. Also, make sure to delete the already existing build and libs folders if you are on Windows or Mac. However, if you are on Linux, you can keep these folders and run the commands below to quickly and easily build the project. 

## Linux:
For Linux, you can do:

~~~
git clone --recursive https://github.com/MohamedAG2002/OutOnlyHope.git
cd OurOnlyHope
mkdir build && cd build 
cmake ..
~~~

After that, you can use your favorite IDE to traverse the project and even build it from source if you want.

## Windows
For windows, things are a little bit different. You need to download the binaries for Raylib, Box2D, and yaml-cpp. You can go to the GitHub page for each one, go to the release section, and download the binaries for windows x64. You have to put the binaries you just downloaded into a folder in the project and name it "libs". Put the include stuff (.hpp/.h files) in a folder called "include" inside of the "libs" directory. And make sure to put the library files into a "lib" folder inside of the "libs" directory. It should look something like this:

~~~
- libs 
    -include
        -raylib-includes
        -box2d-includes
        -yaml-cpp-includes
    -lib
        -raylib.dll/.a 
        -box2d.dll/.a 
        -yaml-cpp.dll/.a 
~~~

Then, you can run the commands below to finally build the project.

~~~
git clone --recursive https://github.com/MohamedAG2002/OurOnlyHope.git
cd OurOnlyHope
mkdir build 
cd build 
cmake ..
~~~

# Play
If you only want to play the game, however, without going through the build process, there is a web build available here: 

# Credits
Thanks to all of these amazing artists for making me "borrow" their fantastic pieces of art: 

Tiles: https://cainos.itch.io/
Shop items: https://joecreates.co.uk
Zombie: https://opengameart.org/users/cornerlord
Player: Seth Koukol
Spear: https://opengameart.org/users/lordneo

Menu Hymn: https://www.marcelofernandezmusic.com/
Combat Hymn: https://opengameart.org/users/cethiel
Over Hymn: https://opengameart.org/users/otto-halm%C3%A9n

Sword swings: https://opengameart.org/users/qubodup
Spear sounds: https://www.aurelienmontero.com/
Zombie killing sounds: https://www.706gaming.org/
Player death/hurting sounds: apollo-music.de or Michel Baradari on opengameart.org
