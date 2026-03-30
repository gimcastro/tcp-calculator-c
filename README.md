TCP Client-Server Calculator (C)

This project implements a simple client-server calculator using TCP sockets in C.

The client sends arithmetic expressions (e.g., 5+3=) to the server, which evaluates the expression and returns the result.

Features
	•	TCP socket communication
	•	Supports operations: +, -, *, /
	•	Real-time request/response between client and server

Technologies
	•	C (POSIX sockets)

How to Run
gcc -o server server.c
gcc -o client client.c

./server
./client
