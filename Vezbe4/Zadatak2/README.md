# Project "Enhanced UDP Messaging System"

## Project Description

This enhanced UDP messaging system builds upon a simple UDP messaging system by implementing a non-blocking UDP server and client. The server is designed to receive messages on two separate UDP sockets (serverSocket1 and serverSocket2) with specific addresses and ports. The implementation incorporates a non-blocking polling model, optimizing processor time consumption during wait periods. Additionally, the server displays the number of attempts during waiting, interrupts message reception after 30 seconds of inactivity, and awards points to the first client sending a message. The client can specify the server port from the command line and send multiple messages.

## Features

1. **Dual UDP Sockets**: The server utilizes two UDP sockets (serverSocket1 and serverSocket2) with specified IP addresses and ports for message reception.

2. **Non-blocking Server Operation**: The server implements a polling model for non-blocking message reception, preventing processor blocking during wait periods.

3. **Optimized Processor Time Consumption**: The server reduces processor time consumption during wait periods by introducing a 1.5-second wait between attempts using the `Sleep` function.

4. **Attempt Number Display**: While waiting for messages, the server displays the number of the current attempt.

5. **Interrupted Reception**: The server can interrupt message reception if no message is received within a 30-second period.

6. **Client Point System**: The server awards 1 point to the first client sending a message.

7. **Dynamic Server Port**: The client can specify the server port from the command line, allowing messages to be sent to different server ports (17010 and 17011).

8. **Multiple Message Support**: The client can send multiple messages, and the program stops when the client inputs "kraj."

## How to Run the Project

1. Open Visual Studio and create an empty project.

2. Create a file named "EnhancedServer.cpp" in the source section and copy the enhanced server code into it.

3. In the same solution, create another empty project.

4. Create a file named "EnhancedClient.cpp" in the source section and copy the enhanced client code into it.

5. Right-click on the solution, choose "Configure Startup Projects..."

6. Set both projects to start.

7. If you want to add an additional player, right-click on the "EnhancedClient" project, then select Debug, and Start New Instance.

8. Run the project and enjoy the enhanced messaging system!

This enhanced project provides an improved messaging experience with non-blocking communication, optimized processor usage, and additional features for better functionality.
