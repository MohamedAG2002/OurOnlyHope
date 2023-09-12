# Engine
- Physics:
    - Contact Listener 

# Game
- Basic zombie
- Zombie manager
- Rotations
- Basic sword
- JoyStick controls
- Better player 
- Better sword 
- Better zombie 
- Fade in screen before the menu

# Problems to fix later
- The buttons don't change their color instantly when the mouse is hovering over them

- Make the pause key the ESC key and not the P key

- The Render() in the Sprite class can be a problem since it can cause circular dependecy. Perhaps remove it later and just make it take in a position, rotation, and scale which will look bad but won't have any problems in the future

- Perhaps remove the SDL_FreeSurface() from the ChangeText()
