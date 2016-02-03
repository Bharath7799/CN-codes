===========================================================
                DYNAMIC CHAT SERVER
 Author: Bharath Kumar
 CSE 3rd Year, 6th Semester, NITW
===========================================================
Problem Statment -> create a chat server. when a new process
is created, it creates two fifo file named as cmd argument 1
for reading -> <arg>r.dat
for writing -> <arg>w.dat

Also it opens global fifo server and writes cmd argument 1 in
the fifo. Server opens both file in vice-versa way and stores
into two different array which is struct pollfd array and one
is integer array. pollfd array is used as arguments for poll 
syscall, pollfd array is for monitoring input data in any fifos
integer fd array is used for writing chat messages from one client
to all clients.

Compile:
gcc chatserver2.c -o server
gcc chatclient2.c -o client

RUN:( execute each command in a new terminal )
./server
./client c1 s1
./client c2 s2
./client c3 s3
...

NOTE:
the second argument s1 doesnt has any meaning in this program,
its usd in next program.
if found any problem with it. do debug by yourself.

mail: bharath.manthati@gmail.com