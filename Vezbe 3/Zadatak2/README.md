# Project "Word Chain Game"

## Project Description

This project implements the "Word Chain Game" using a simple TCP client and TCP server implementation. The game is designed for two players who compete in guessing words that start with a specified letter. The server manages the game and determines the winner based on the provided rules.

## Features

The project includes the following features:

1. **Two Players**: The game involves exactly two players (clients). Both players need to establish a connection with the server before the game can start.

2. **Letter Selection**: After both players are connected, the server selects a letter for the game and informs the players about the start of the game.

3. **Word Input**: Each player has the opportunity to input a word that starts with the chosen letter and sends their choice to the server.

4. **Word Validation**: The server checks if the words submitted by the players indeed start with the specified letter and displays the results on the server's screen.

5. **Game Completion**: The game continues until one of the players makes a mistake or decides to quit. A player can quit by sending the word "End."

6. **Resumption After Mistake**: If both players make a mistake simultaneously, the game continues.

7. **Result Display**: At the end of the game, the server sends the game result to the players. The result includes the number of correct words for both players and the name of the game winner.

8. **Word Acceptance**: The server accepts words regardless of whether they are sent with uppercase or lowercase letters for the chosen letter.

9. **Winner Based on Word Length**: If both players decide to quit simultaneously, the winner is the one with the greater total length of correctly submitted words.

10. **Error Handling**: The project handles errors that might occur during message transmission or reception and terminates the game in case of an error.

## How to Run the Project

1. Open Visual Studio and create an empty project.

2. Create a file named "Client.cpp" in the source section and copy the client code into it.

3. In the same solution, create another empty project.

4. Create a file named "Server.cpp" in the source section and copy the server code into it.

5. Right-click on the solution, choose "Configure Startup Projects..."

6. Set both projects to start.

7. If you want to add an additional player, right-click on the "Client" project, then select Debug, and Start New Instance.

8. Run the project and enjoy the game!

This project implements the "Word Chain Game" using a simple TCP server and client, allowing two players to compete in guessing words that start with a specified letter. The project includes all the mentioned features and provides a unique gaming experience. Good luck and enjoy the game!
