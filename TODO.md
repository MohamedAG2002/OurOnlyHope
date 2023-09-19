# Game
- Set up the metadata for all of the shop items
- Weapon functionality
- Make the zombies die 
- Make the player die
- Better player 
- Better sword 
- Get a better sprite for the wall and the houses
- Better camera
- Fade in screen before the menu

# Problems to fix later
- The tiles are not supposed to be bodies. Or at least I think. The outer walls of the map need to be solid/rigid in order for the player and the zombies to stop when colliding with them. The houses need to be like that too. But the grass tiles need to kinematic/transperant since they are supposed to be invisible. Maybe make a better tile system. 

- The rotations aren't great with joystick controls as the player does reset his rotations when the left analog has been let go. The player should instead remember his last rotaion and continue from there rather than resetting every time the player lets go of the analog, which can be annoying. 

- The zombie sounds get sampled together which create an ear-raping symphony. FIX THAT!

- The player will have 4 directions he can go to: up, down, left, and right. If the player has 4 different sprites depecting the 4 directions, then the player will not have to rotate; only the sword needs to know which direction the mouse is pointing not the player. Perhaps the zombie is the same too. However, that might be more difficult since the zombie will need 8 different sprites depecting the 8 directions he can face (up, down, left, right, upper-right, upper-left, bottom-right, and bottom-left). But the zombie doesn't neccassarily have to rotate either. 

- Make the pause key the ESC key and not the P key
