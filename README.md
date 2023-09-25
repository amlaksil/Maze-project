# Maze

Maze is a 2D game developed using raycasting in C and the SDL2 library. It offers an immersive gameplay experience similar to Wolfenstein 3D, where players navigate through a maze-like environment.

![Image not found](images/maze-game.gif)

## Introduction

My inspiration to undertake the Maze game project was driven by the challenge presented to me - the requirement to implement raycasting algorithms using the C programming language and the SDL2 library. While initially daunting, this challenge ignited a curiosity within me to explore the inner workings of raycasting and understand its fundamental principles.

Admittedly, comprehending raycasting algorithms proved to be a formidable task. The intricacies and mathematical concepts involved pushed me beyond my comfort zone. Yet, I was determined to conquer this hurdle and gain a deep understanding of how raycasting brings a 2D world to life, creating dynamic and immersive gameplay.

Throughout the process, I sought out various resources, tutorials, and documentation to unravel the mysteries of raycasting. I delved into the underlying mathematics and absorbed the intricacies of casting rays, calculating intersections, and generating the visual representation of the game world. It was a challenging journey that demanded patience, persistence, and a willingness to learn.

There were moments of frustration and confusion, where the complexities of raycasting seemed insurmountable. However, with each obstacle I encountered, I dedicated myself to thorough research and sought guidance from experienced developers. Through their insights and support, I gradually gained a clearer understanding of the algorithms and their practical implementation.

As my comprehension of raycasting grew, so did my excitement. Witnessing the transformation of abstract concepts into tangible visuals was awe-inspiring. The ability to simulate depth, create immersive environments, and bring the maze to life was a testament to the power of raycasting.

This project has not only deepened my understanding of raycasting algorithms but has also sparked a profound appreciation for their potential in game development. It has been a journey of growth and discovery, where I have embraced the challenges and emerged with newfound knowledge and skills.

In conclusion, the Maze game project, driven by the requirement to implement raycasting algorithms using the C programming language and the SDL2 library, presented me with an opportunity for personal and technical growth. Despite the initial difficulties in understanding raycasting, my determination and commitment to learning have propelled me forward. This project has allowed me to expand my understanding of raycasting and witness its transformative impact on creating an immersive gaming experience.

For more detailed information and insights about the development process and challenges please check out my accompanying blog article on medium: [Portfolio Project Blog Article](https://medium.com/@amlasil/embarking-on-an-exhilarating-journey-developing-an-immersive-raycasting-game-5c60fbb466ca).

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
$ cd Maze-project
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

## Author

- [Silamlak Desye](https://www.linkedin.com/in/silamlakdesye)

Feel free to connect with me on LinkedIn for any questions, collaboration opportunities, or to learn more about my professional background.

## License

This project is licensed under the [MIT License](https://mit-license.org/amlaksil). See the [LICENSE](LICENSE) file for more details.
