# Project "Enhanced UDP Messaging System"

## Project Description

This project enhances a simple UDP messaging system by implementing a non-blocking UDP server and client. The server is designed to receive messages on port 15001, employing a non-blocking polling model to optimize processor time consumption during wait periods. Additionally, the server displays the number of attempts during waiting and can interrupt message reception after 30 seconds of inactivity. The project focuses on improving the server-side functionality, allowing for efficient communication between clients without blocking operations.

## Features

The enhanced project includes the following features:

1. **Port 15001 Reception**: The server can receive messages on port 15001.

2. **Non-blocking Server Operation**: The server implements a polling model for non-blocking message reception, ensuring it does not block the processor while waiting for messages.

3. **Optimized Processor Time Consumption**: The server reduces processor time consumption during wait periods by introducing a 1-second wait between attempts using the `Sleep` function.

4. **Attempt Number Display**: While waiting for messages, the server displays the number of the current attempt.

5. **Interrupted Reception**: The server is capable of interrupting message reception if no message is received within a 30-second period.

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
