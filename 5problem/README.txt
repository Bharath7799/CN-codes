===========================================================
                All In One (Popen, fifo, pipe and signal)
 Author: Bharath Kumar
 CSE 3rd Year, 6th Semester, NITW
===========================================================
Problem Statment -> create a server which is connected by each
process with each one of these methods(popen, fifo, pipe). and
gives output on stdout of server. if any process made a SIGUSR1
signal it redirects output to another process.

fifo -> ssfifo (communication b/w fifo process and server)
fifo -> out.dat (communication b/w output process and server)

fifofile.c -> fifo communicated process.
pipe.c -> popen communicated process.
signal.c -> to signal the process.
output.c -> process which displays output of server after signal
Inside server a child process is created for pipe communication.

Compile:
gcc server.c -o server
gcc pipe.c -o sopen
gcc fifofile.c fifo
gcc output.c -o out
gcc signal.c -o signal

RUN:( execute each command in a new terminal )

./server
./fifo
./out
./signal


NOTE:
if found any problem with it. do debug by yourself.

mail: bharath.manthati@gmail.com
