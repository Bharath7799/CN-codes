===============================================================
                    MULTI SERVICE SERVER
 Author: Bharath Kumar
 CSE 3rd Year, 6th Semester, NITW
===============================================================
Problem Statment -> create a multi service server. when a new 
process is created, it creates two fifo file named as first
command line argument, 2st command line arg is service type
In this example it is -> s1.c

s1 -> ls (file and directory listing)
u can create any no.of services you need. 
each client creates two files. 
for reading -> <arg 1>r.dat
for writing -> <arg 1>w.dat
and Server creates main_fifo.dat

Client opens global fifo server and writes cmd <arg 1> and <arg 2>
in the fifo. Server reads global fifo and creates a new service process
from argument 2 .

Compile:
gcc mainserver.c -o server
gcc client.c -o client

gcc s1.c -o s1

RUN:( execute each command in a new terminal )
./server
./client c1 s1
./client c2 s2
./client c3 s3
...

NOTE:
only one service provided at an instance to the client.

if found any problem with it. do debug by yourself.

mail: bharath.manthati@gmail.com