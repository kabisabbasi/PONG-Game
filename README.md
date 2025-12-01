# Pong Game

## Description

This is a simple implementation of the classic Pong game built using C++ and the Raylib library. The game supports both single-player (against CPU) and multi-player (two players) modes. Players control paddles to hit a ball back and forth, scoring points when the opponent misses the ball. The game includes basic graphics, collision detection, scoring, and name input for players. Scores are appended to a file named `Score.txt` after the game ends.

The game window is 800x600 pixels, with a divided court, a central circle, and score displays. The ball bounces off the top and bottom walls, and scores are updated when it hits the left or right boundaries.

## Features

- **Single-Player Mode**: Play against a CPU-controlled paddle.
- **Multi-Player Mode**: Two players can play on the same keyboard.
- **Player Name Input**: Enter names before starting the game in a separate window.
- **Scoring System**: Scores are displayed on screen and saved to `Score.txt`.
- **Basic AI for CPU**: The CPU paddle tracks the ball's y-position.
- **Collision Detection**: Using Raylib's built-in functions for ball-paddle interactions.
- **Custom Colors and Graphics**: Simple color scheme with a divided field and central circle.

## Requirements

- **Compiler**: A C++ compiler (e.g., g++).
- **Raylib Library**: Raylib must be installed and linked properly. Download from [raylib.com](https://www.raylib.com/).
- **Operating System**: Tested on systems supporting Raylib (Windows, Linux, macOS).

## Installation

1. Install Raylib:
   - Follow the instructions on the [Raylib GitHub repository](https://github.com/raysan5/raylib) for your platform.
   - Ensure Raylib headers and libraries are in your include and library paths.

2. Clone or download the project code into a directory.

3. Compile the code:
   - Use a command like:  
     ```
     g++ main.cpp -o pong -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
     ```
     (Adjust flags based on your OS and Raylib installation.)

## How to Run

1. Run the compiled executable:  
   ```
   ./pong
   ```

2. At the prompt, enter 'S' for single-player or 'M' for multi-player.

3. Enter player names in the pop-up windows (Player 1 first, then Player 2 in multi-player mode).

4. The game window will open. Play until you close the window.

5. Scores will be appended to `Score.txt` in the same directory.

## Controls

- **Single-Player Mode**:
  - Right Paddle (Player): UP arrow (move up), DOWN arrow (move down).
  - Left Paddle: Controlled by CPU.

- **Multi-Player Mode**:
  - Right Paddle (Player 1): UP arrow (move up), DOWN arrow (move down).
  - Left Paddle (Player 2): W (move up), S (move down).

- Close the game window to exit and save scores.

## Known Issues

- The ball does not reset to the center after a score; it simply reverses direction.
- In single-player mode, only one name is entered, but the score file attempts to write two names (the second may be empty).
- Screen height is set to 600, but some drawing functions reference 800 (potential overflow).
- No win condition; the game runs indefinitely until closed.
- Paddle width for players and CPU may differ slightly in code.

## Credits

- Developed by Kabis and Shaban.
- Built with [Raylib](https://www.raylib.com/) for graphics and input handling.

## License

This project is open-source and available under the MIT License. Feel free to modify and distribute.
