# Project "Enhanced TCP Communication System"

## Project Description

This project enhances a TCP communication system using the provided example of TCP client and server implementation. The focus is on creating a server that actively listens for connection requests on port 18010 and establishes connections with two clients. Upon connection, the server prints the address information of the connected clients. The server employs a non-blocking polling model to avoid processor blocking during message reception, reduces processor time consumption during wait periods, and allows clients to send multiple messages or arrays of three integers.

## Features

1. **Dual Client Connection**: The server actively listens for connection requests on port 18010 and establishes connections with two clients. Address information of connected clients is printed upon connection.

2. **Non-blocking Server Operation**: The server implements a polling model for non-blocking message reception, preventing processor blocking during wait periods.

3. **Optimized Processor Time Consumption**: The server reduces processor time consumption during wait periods by introducing a 1.5-second wait between attempts using the `Sleep` function.

4. **Multiple Message Support**: Clients can send multiple messages to the server. The client can terminate by entering "kraj."

5. **Array Transmission**: Clients can send an array of three integers within a single message.

6. **Array Sum Response**: After receiving a message containing an array of three numbers, the server calculates and sends back a message containing the sum of the received array values. The client prints the received response.

## How to Run the Project

1. Open Visual Studio and create an empty project.

2. Create a file named "EnhancedTCPServer.cpp" in the source section and copy the enhanced server code into it.

3. In the same solution, create another empty project.

4. Create a file named "EnhancedTCPClient.cpp" in the source section and copy the enhanced client code into it.

5. Right-click on the solution, choose "Configure Startup Projects..."

6. Set both projects to start.

7. Run the project and enjoy the enhanced TCP communication system!

This enhanced project provides an improved TCP communication experience with non-blocking operation, optimized processor usage, and additional features for better functionality.
