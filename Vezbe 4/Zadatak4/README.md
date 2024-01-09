# Project "Advanced TCP Communication System"

## Project Description

This project enhances a TCP communication system using the provided example of TCP client and server implementation. The goal is to implement various functionalities, including the use of a polling model for non-blocking operations on both the server-side connection handling and message reception from clients.

## Features

### 1. TCP Server Connection Handling

1.1 **Dual Client Connection**: The TCP server actively accepts connections from two clients using a non-blocking polling model.

1.2 **Non-blocking Server Connection Handling**: The server employs a non-blocking mode for executing operations on the socket listening for connection requests on port 19010.

1.3 **Optimized Processor Time Consumption**: To reduce processor time consumption during connection waiting, the server waits for 2 seconds before the next connection attempt using the `Sleep` function.

1.4 **Connection Information Display**: Upon accepting a connection, the server prints the address information of the connected client.

### 2. Non-blocking Message Reception

2.1 **Non-blocking Server Operation**: The server implements a polling model for non-blocking message reception from clients.

2.2 **Optimized Processor Time Consumption**: The server reduces processor time consumption during message waiting by introducing a 1-second wait between attempts using the `Sleep` function.

2.3 **Message Content Display**: When a message is received, the server prints the content of the message and the socket that received it.

### 3. Multiple Messages and Client Termination

3.1 **Multiple Message Support**: Clients can send multiple messages to the server.

3.2 **Client Termination**: If the client inputs "kraj," the server stops the client.

### 4. Array Transmission and Processing

4.1 **Array Transmission**: Clients can send an array of three integers within a single message.

4.2 **Array Processing on Server**: The server displays the received array of integers.

### 5. Maximum Value Response

5.1 **Maximum Value Calculation**: The server calculates the maximum value from the received array.

5.2 **Response to Client**: The server sends a response to the client, stating the maximum value in the format: "The largest sent number is 100," in the example where the server received an array of values 50, 99, and 100.

## How to Run the Project

1. Open Visual Studio and create an empty project.

2. Create a file named "AdvancedTCPServer.cpp" in the source section and copy the advanced server code into it.

3. In the same solution, create another empty project.

4. Create a file named "AdvancedTCPClient.cpp" in the source section and copy the advanced client code into it.

5. Right-click on the solution, choose "Configure Startup Projects..."

6. Set both projects to start.

7. Run the project and experience the advanced TCP communication system!

This project enhances the TCP communication system with non-blocking connection handling, optimized processor usage, and additional features for better functionality.
