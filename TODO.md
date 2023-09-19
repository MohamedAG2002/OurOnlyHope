# Engine
- Rotations
- Debug draw
- Contact Listener 
- Camera 
- Tiles

# Game
- Basic zombie
- Zombie manager
- Set up the metadata for all of the shop items
- Weapon functionality
- Better player 
- Better sword 
- Fade in screen before the menu

# Problems to fix later
- The rotations aren't great with joystick controls as the player does reset his rotations when the left analog has been let go. The player should instead remeber his last rotaion and continue from there rather than resetting every time the player lets go of the analog, which can be annoying. Also the up and down rotaions are inverted. Perhaps it's a problem with the sprite itself of the analog controls.
    
- The sword is completely fucked

- The player does forget that he's rotation when he starts moving. Read more about Box2D's rotation system

- The player will have 4 directions he can go to: up, down, left, and right. If the player has 4 different sprites depecting the 4 directions, then the player will not have to rotate; only the sword needs to know which direction the mouse is pointing not the player. Perhaps the zombie is the same too. However, that might be more difficult since the zombie will need 8 different sprites depecting the 8 directions he can face (up, down, left, right, upper-right, upper-left, bottom-right, and bottom-left). But the zombie doesn't neccassarily have to rotate either. 

- Make the pause key the ESC key and not the P key
