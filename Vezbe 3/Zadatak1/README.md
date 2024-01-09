# TCP Server-Client Project

## Project Description

This project represents the implementation of a TCP server and client within a single Visual Studio solution. TCP (Transmission Control Protocol) is one of the transport protocols for data transmission over a network. The server and client use TCP for communication, exchanging messages with specific content.

## Project Structure

The project consists of two parts:

1. **Server**: A TCP server that listens for connection requests from clients, processes them, and sends responses back to the clients.

2. **Client**: A TCP client that allows users to send messages to the server.

## Features

The project has been implemented to fulfill the following functional requirements:

1. **Server Socket Settings**: The server is configured to listen on a specific address and port (IPv4 and a specified port).

2. **Display Client Information**: The server displays information about the connected clients.

3. **Multiple Messages**: The client can send multiple messages to the server without the need to restart the client.

4. **Multiple Clients**: Multiple clients can be created, and each of them can send messages to the server.

5. **Server Response**: The server can respond to any client that sends a message, providing a reply.

## Running the Project

1. Open Visual Studio and create an empty project.

2. Create a Client.cpp file in the source section and copy the provided Client.cpp code into it.

3. In the same solution, create another empty project.

4. Create a Server.cpp file in the source section and copy the provided Server.cpp code into it.

5. Right-click on the solution and choose "Configure Startup Projects..."

6. Select "Multiple Startup Projects" and set both of them to "Start."

7. If you want to create another client, right-click on the Client project, then go to Debug, and select Start New Instance.

8. Run the project and enjoy!
