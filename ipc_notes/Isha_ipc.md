INTER-PROCESS COMMUNICATION (IPC)

Part: Pipes 

Written by: Safiyath Isha 


1. Pipes in Interprocess Communication: 
Interprocess Communication (IPC) allows processes to communicate and exchange data with each other. Since processes normally have separate memory spaces, IPC provides different methods for them to share information. Pipes are one of the simplest and commonly used techniques for IPC.

2. What is a Pipe?
A pipe is a communication channel that allows one process to send data to another process.
The data is written into one end of the pipe and read from the other end.

* Basic flow: Process A → Pipe → Process B

3. Working of Pipes:
A pipe has two ends-
*  Write end: Used by a process to send data.
*  Read end: Used by a process to receive data.

One process writes data into the pipe, and the operating system temporarily stores the data. Another process can then read the data from the pipe. This allows processes to communicate without directly accessing each other's memory.

4. Types of Pipes:
* Anonymous Pipe : An anonymous pipe is mainly used for communication between related processes, such as a parent process and its child process.

* Example:- Parent Process → Pipe → Child Process

* Anonymous pipes are usually temporary and are mainly used for simple communication.

* Named Pipe (FIFO) : A named pipe has a name in the file system and can be used by unrelated processes.

* FIFO stands for “First In, First Out”, meaning the data that enters the pipe first is generally read first.

* Named pipes are useful when independent processes need to communicate with each other.

5. Real-World Example:
Example 1:- Linux Commands
Pipes are commonly used in Linux commands using the `|` symbol.
 ``text
ls | grep ".txt"
* Flow: ls → Pipe → grep

Example 2:- Producer and Consumer.
In a data-processing system, one process can produce data while another process processes it.
* Producer Process → Pipe → Consumer Process
The producer sends data through the pipe, and the consumer receives and processes it.

6. Advantages:
* Simple to use
* Easy to implement
* Fast for communication between local processes
* Useful for transferring data between processes
* Supported by major operating systems

7. Disadvantages:
* Anonymous pipes are mainly used between related processes
* Limited buffer capacity
* Not suitable for complex communication
* Synchronization may be required
* Mainly designed for processes running on the same system

Example:-
Process A
   ↓
Writes data
   ↓
  PIPE
   ↓
Reads data
   ↓
Process B

For example - Process A can send "Hello" through the pipe, and Process B can receive and read "Hello".
Python Implementation: 

Python provides the Pipe() function through the multiprocessing module for communication between processes.
* from multiprocessing import Pipe
  conn1, conn2 = Pipe()
  conn1.send("Hello from Process 1")
  print(conn2.recv())

Output: Hello from Process 1
Here:
* send() sends data through the pipe.
* recv() receives the data.
* Pipe() creates the communication channel.

8. Conclusion: 
Pipes provide a simple and efficient way for processes to exchange data. They are especially useful for straightforward communication between processes running on the same computer.
Anonymous pipes are mainly used between related processes, while named pipes can also be used by unrelated processes.
