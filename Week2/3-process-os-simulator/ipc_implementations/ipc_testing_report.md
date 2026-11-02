# INTER-PROCESS COMMUNICATION (IPC)
## Testing and Execution Report

**Project:** Operating Systems PBL – Week 2  
**Environment:** Ubuntu Linux (WSL2)  
**Programming Language:** C  
**Compiler:** GCC

---

## 1. Objective

The objective of this practical implementation is to understand and demonstrate different Inter-Process Communication (IPC) mechanisms in an operating system.

Seven IPC mechanisms were implemented and tested to observe how processes exchange information and synchronize their execution.

## 2. Testing and Execution

### 2.1 Ordinary Pipes

**Objective:** To demonstrate communication between a parent process and a child process using an unnamed pipe.

**Observed Output:**

```text
Parent: Sending message to child
Child: Received message: Hello from parent
```

**Observation:**

The parent process successfully sent a message through the pipe, and the child process received it.

**Result:** Passed.

---

### 2.2 Named Pipes (FIFO)

**Objective:** To demonstrate communication between the UI, Core and Logger processes using named pipes.

**Observed Output:**

```text
========================================
   3-PROCESS OS SIMULATOR LAUNCHER
========================================

====================================
         LOGGER PROCESS
====================================

====================================
          CORE PROCESS
====================================

====================================
     3-PROCESS OS SIMULATOR
====================================

Enter commands for the simulator.
Type 'exit' to stop.

Enter command: start

[CORE] Received command: start
[CORE] Executing: start
[CORE] CPU execution started.
[CORE RESPONSE] CPU execution started.

[LOGGER] Core executed command: start

Enter command: stop

[CORE] Received command: stop
[CORE] Executing: stop
[CORE] CPU execution stopped.
[CORE RESPONSE] CPU execution stopped.

[LOGGER] Core executed command: stop

Enter command: status

[CORE] Received command: status
[CORE] Executing: status
[CORE] CPU Status: RUNNING
[CORE] Memory Status: ACTIVE
[CORE] Stack Status: ACTIVE
[CORE] Queue Status: ACTIVE
[CORE RESPONSE] CPU: RUNNING | Memory: ACTIVE | Stack: ACTIVE | Queue: ACTIVE

[LOGGER] Core executed command: status

Enter command: exit

[CORE] Received command: exit
[CORE] Executing: exit
[CORE] Shutting down...
[CORE RESPONSE] Core Process shutting down.

UI Process terminated.
Core Process terminated.
[LOGGER] Core executed command: exit

Logger Process terminated.

All processes terminated successfully.
```

**Observation:**

The UI process successfully sent commands to the Core process. The Core process executed the commands and returned responses. The Logger process received and recorded the executed commands.

**Result:** Passed.

---

### 2.3 Message Queues

**Objective:** To demonstrate message exchange between processes using a System V message queue.

**Observed Output:**

```text
Waiting for message...
Received message: hello from isha
Message queue deleted.
```

**Observation:**

The receiver successfully retrieved the message sent through the message queue. The queue was subsequently deleted.

**Result:** Passed.

---

### 2.4 Shared Memory

**Objective:** To demonstrate data sharing between processes using POSIX shared memory.

**Observed Output:**

```text
Reader: Data received successfully.
Reader received: Hello from Shared Memory!
```

**Observation:**

The writer stored data in the shared memory region, and the reader successfully accessed and retrieved the stored message.

**Result:** Passed.

---

### 2.5 Semaphores

**Objective:** To demonstrate process synchronization using semaphores.

**Observed Output:**

```text
Child: Waiting for semaphore...
Parent: Sending semaphore signal.
Child: Semaphore received!
Child: Critical operation completed.
Parent: Child process completed.
```

**Observation:**

The child process waited for the semaphore signal. The parent process released the semaphore, allowing the child to continue and complete its critical operation.

**Result:** Passed.

---

### 2.6 Signals

**Objective:** To demonstrate process notification using signals.

**Observed Output:**

```text
[1] 11697
Receiver PID: 11697
Receiver: Waiting for signal...
Receiver PID: 11697

Receiver: Signal received successfully!
Sender: Signal sent successfully!

[1]+ Done ./ipc_implementations/signals/signal_reciever
```

**Observation:**

The receiver process waited for a signal. The sender used the receiver's process ID to send the signal. The receiver successfully handled the received signal.

**Result:** Passed.

---

### 2.7 Sockets

**Objective:** To demonstrate two-way communication between a client and server using TCP sockets.

**Client Output:**

```text
Client: Message sent!
Client received: Hello from server!
```

**Server Output:**

```text
Server: Waiting for client...
Server received: Hello from client!
Server: Response sent!
```

**Observation:**

The client successfully connected to the server and sent a message. The server received the message and sent a response, which was successfully received by the client.

**Result:** Passed.

---

## 3. Summary of Results

| No. | IPC Mechanism | Testing Result |
|---|---|---|
| 1 | Ordinary Pipes | Passed |
| 2 | Named Pipes (FIFO) | Passed |
| 3 | Message Queues | Passed |
| 4 | Shared Memory | Passed |
| 5 | Semaphores | Passed |
| 6 | Signals | Passed |
| 7 | Sockets | Passed |

**Overall Result: 7 out of 7 IPC mechanisms passed their basic functional tests.**

## 4. Conclusion

All seven IPC implementations were successfully compiled and executed in the Ubuntu Linux environment.

The practical tests demonstrated:

- Data transfer between related processes using ordinary pipes.
- Communication between independent processes using named pipes.
- Message exchange using message queues.
- Data sharing using shared memory.
- Process synchronization using semaphores.
- Process notification using signals.
- Client-server communication using sockets.

The practical implementation helped in understanding the working principles, system calls and applications of different IPC mechanisms in operating systems.

**Final Status: All seven IPC mechanisms successfully tested.**
