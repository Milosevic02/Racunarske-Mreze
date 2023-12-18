Extract the Project.zip file and insert a CPP file into it.

# Capturing and Filtering Packets - WinPcap Example

This program demonstrates the basic functionality of capturing and filtering network packets using the WinPcap library in C. The key parts of the code are outlined here along with instructions on how to make specific modifications.

## Prerequisites

Before compiling and running this program, ensure that you have the WinPcap library installed on your system. You can download it from [WinPcap official website](https://www.winpcap.org/).

## Usage

1. Run the compiled executable.
2. The program will display a list of available network interfaces along with their details, including names and descriptions.
3. Enter the interface number (1 to the total number of interfaces) that you want to use for packet capturing.
4. The program will open the selected capture device and set up a packet filter to capture only packets addressed to the logical address of the computer running the application and using the TCP protocol.
5. The program will then start capturing packets and display their information, including packet number, timestamp, and length.
6. To stop the program, press Ctrl+C in the terminal.
