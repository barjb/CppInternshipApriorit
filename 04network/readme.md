# Client
Works on two threads. First thread is used to communicate with the user, second one is to exchange messages with server.

Client exchanges messages with server in synchronous manner. Ability to send asynchronous messages would be useful in more advanced tasks.

# Server
Server side is abstraced into couple classes. Server is a class running an acceptor socket. AcceptorSocket is a class running passive socket, which spawn active sockets (clients). Server can handle mutliple clients at once in parallel manner. 

# To do
Due to poor time managment I did not have time to finish task completely. 
Project is lacking:
- data encapsulation/decapsulation
- threading, clients are handled parallely on server side
- proper resource managment
- server doesn't close

# Testing
There is provided Makefile. Use following commands:
- compile server and client: **make compile**
- compile server **make server**
- compile client **make client**
- run client **make runclient**
- run client **make runserver**
