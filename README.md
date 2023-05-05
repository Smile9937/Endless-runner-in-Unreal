# Endless-runner-in-Unreal

This is my endless runner where you dodge obstacles.

Find my binary under the shipping version Windows 10 package under Releases tab as a ZIP

## Part 1

Controls:
Move left/right | left/right arrow keys or A/D.

The game uses lane based movement with 3 lanes. Obstacles are spawned on the lanes and moves towards the player. The player can move between the 3 lanes to dodge obstacles.

GameData: This is a data asset which stores variables that is used in multiple classes, for example the despawn position of the platforms and obstacles.

EndlessRunnerCharacter: The character script of the game, I made the movemet based on different lanes. The positions of the lanes are stored in an array and when an input is recieved I change an int which holds the index for the array to the correct lane and move the player to that position. I lerp the position between different position vectors along a curve using an unreal timeline.

GroundSpawner: It spawns ground tiles that moves in the direction of the player. When the tiles are spawned they are added to an TArray and when the first tile in the array reaches a set location, a new tile is spawned and the previous one is destroyed. New tiles are spawned behid the last tile in the array.

ObstacleSpawner: It spawns obstacles on random lanes during a set interval.

Obstacle: It moves forwards at a set speed.

## Part 2

Controls:
Quit Game | Escape
Restart Game | R
Player 1: Move left/right | left/right arrow keys
Player 2: Move left/right | A/D

I have added local multiplayer to the game. It is played on the same keyboard.

Both payer characters recieve input in the PlayerManager class. I made it this way since 2 different characters can't take input from the same device in unreal, so I had to make one class that takes the input and then passes them onto the player characters.
Another problem with making local multplayer was then, since the PlayerManager needs to be a controlled pawn, it is now taking part in the split screen. To solve this issue, I made a PlayerViewport class, and added the first player character to the viewport for the PlayerManager and added the second caracter to the viewport of the PlayerViewport.

I tried to make a scoreboard and managed to figure out how to read/write to json files. But I ran into some issues and couldn't finish it in time.