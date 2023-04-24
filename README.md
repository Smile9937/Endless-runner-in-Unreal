# Endless-runner-in-Unreal

This is my endless runner where you dodge obstacles.

Find my binary under the shipping version Windows 10 package under Releases tab as a ZIP

## Part 1

Controls:
Move left/right | reft/right arrow keys or A/D.

The game uses lane based movement with 3 lanes. Obstacles are spawned on the lanes and moves towards the player. The player can move between the 3 lanes to dodge obstacles.

GameData: This is a data asset which stores variables that is used in multiple classes, for example the despawn position of the platforms and obstacles.

EndlessRunnerCharacter: The character script of the game, I made the movemet based on different lanes. The positions of the lanes are stored in an array and when an input is recieved I change an int which holds the index for the array to the correct lane and move the player to that position. I lerp the position between different position vectors along a curve using an unreal timeline.

GroundSpawner: It spawns ground tiles that moves in the direction of the player. When the tiles are spawned they are added to an TArray and when the first tile in the array reaches a set location, a new tile is spawned and the previous one is destroyed. New tiles are spawned behid the last tile in the array.

ObstacleSpawner: It spawns obstacles on random lanes during a set interval.

Obstacle: It moves forwards at a set speed.

Talking about class 2 goes here

## Part 2

Not done yet, write more about this later.
