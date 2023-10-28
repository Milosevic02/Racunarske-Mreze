# UDP Server-Client Project

## Project Description

This project represents the implementation of a UDP server and client within a single Visual Studio solution. UDP (User Datagram Protocol) is one of the transport protocols for data transmission over a network. The server and client communicate using UDP, exchanging messages with specific content.

## Project Structure

The project consists of two parts:

1. **Server**: A UDP server that receives messages from clients, processes them, and sends responses back to the clients.

2. **Client**: A UDP client that allows users to send messages to the server.

## Features

The project has been implemented to fulfill the following functional requirements:

1. **Server Socket Settings**: The server is configured to listen on a specific address and port (IPv4 and port 15001).

2. **Multiple Messages**: The client can send multiple messages to the server without the need to restart the client.

## Running the Project

1. Open Visual Studio and create an empty project.

2. Create a Client.cpp file in the source section and copy my Client.cpp code into it.

3. In the same solution, create another empty project.

4. Create a Server.cpp file in the source section and copy my Server.cpp code into it.

5. Right-click on the solution and choose "Configure Startup Projects..."

6. Select "Multiple Startup Projects" and set both of them to "Start."

7. Run the project and enjoy!



