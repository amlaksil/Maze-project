# Maze

Maze is a 2D game developed using raycasting in C and the SDL2 library. It offers an immersive gameplay experience similar to Wolfenstein 3D, where players navigate through a maze-like environment.

## Features

- 3D Raycasting: The game utilizes raycasting techniques to create a pseudo-3D effect, allowing players to explore the maze.

- Player Movement: Players can rotate their view using the left and right keys or the A and D keys, allowing them to look around the environment.

- Wall Sliding: Collision detection has been implemented to prevent players from entering walls. Instead, players can slide along the walls, enhancing the fluidity of movement.

- Minimap: A minimap feature is available, which can be enabled or disabled by modifying the `resources.enable_minimap` flag in the main function.

- Map Parser: A parser is implemented to read the maze map from a file. This allows you to define custom maze layouts and easily modify the game environment.

- Textures: The game includes textures for walls, ceiling, and floor. To load textures onto the screen, you will need the SDL2 image library installed.

- Simultaneous Movement: The game supports simultaneous movement and rotation, allowing players to move in multiple directions while rotating their view.

- Compiler Compatibility: The code has been developed and tested with `ubuntu 20.04 LTS` and the GNU Compiler Collection (GCC) using the following flags: `-Wall, -Werror, -Wextra, and -pedantic`.

## Requirements

- SDL2 Library: Make sure you have the SDL2 library installed on your system. You can find installation instructions on the SDL website (https://www.libsdl.org/).

- SDL2 Image Library: Additionally, you will need the SDL2 image library. You can find installation instructions on the SDL website mentioned above.

## Installation

1. Clone the repository to your local machine.
```
$ https://github.com/amlaksil/Maze-project
```
2. Navigate to the project directory.
```
$ cd maze-project
```
3. Compile the code using the provided Makefile.
```
$ make
```
4. Run the game.
```
$ make run
```
## Controls

- Left/Right Keys or A/D Keys: Rotate the player's view left or right.
- Up/Down Keys or W/S Keys: Move the player forward or backward.
- ESC Key: Quit the game.

## Gameplay

- Your objective is to navigate through the maze.
- Use the rotation keys to look around and plan your path.
- Avoid colliding with walls, as the player will slide along them instead of stopping.
- Utilize the minimap to get an overview of the maze layout and find the exit.

## Development

- If you'd like to contribute to the project, feel free to fork the repository and submit pull requests with your changes.
- Make sure to follow the coding style and conventions used in the existing codebase.

## Troubleshooting

- If you encounter any issues or have questions, please open an issue on the project's GitHub repository (https://github.com/amlaksil/maze-project/issues).

## License

This project is licensed under the [MIT License](https://mit-license.org/amlaksil).
