INTER - PROCESSING COMMUNICATION(IPC)
Part: Message Passing
Written by: Ayman Khan

Message Passing is an Inter-Process Communication (IPC):
It is technique in which processes communicate and exchange data by sending and receiving messages. Unlike shared memory, processes do not need to access the same memory space. The operating system provides mechanisms for transferring messages between processes.


Message passing is commonly used when processes need to coordinate their activities or exchange information.


 Send and Receive:


Message passing mainly uses two basic operations:


- Send: A process sends a message containing data or information to another process.
- Receive: A process receives a message sent by another process.


The basic communication can be represented as:


Process A → Send(Message) → Process B → Receive(Message)


For example, Process A can send the message ""Hello"" to Process B, and Process B receives and processes the message.


Direct and Indirect Communication:


In direct communication, the sender and receiver processes communicate with each other by explicitly identifying one another.


For example:


Process A → Process B


Process A directly sends a message to Process B.




Indirect Communication:


In indirect communication, messages are sent through an intermediate communication mechanism such as a mailbox or message queue.


For example:


Process A → Mailbox → Process B


Process A sends a message to the mailbox, and Process B receives the message from the mailbox.




Synchronous Message Passing:


In synchronous communication, the sender or receiver waits until the required communication operation is completed.


For example, a sender may wait until the receiver is ready to receive the message.


Example:


«Process A sends a message → waits → Process B receives the message.»






Asynchronous Message Passing:


In asynchronous communication, the sender does not have to wait for the receiver to receive the message. The message can be stored temporarily in a buffer or queue.


Example:


«Process A sends a message → continues execution → Process B receives it later.»








Advantages of Message Passing:


1. Easy communication: Provides a simple way for processes to exchange information.
2. Process synchronization: Helps coordinate the execution of different processes.
3. No shared memory required: Processes can communicate without directly sharing their memory.
4. Suitable for distributed systems: Processes can communicate even when running on different computers using suitable communication mechanisms.
5. Better isolation: Each process maintains its own memory space, improving process independence.
6. Flexible: Supports both synchronous and asynchronous communication.












 Simple Example:


Consider two processes, Process A and Process B, where Process A needs to send a number to Process B.


1. Process A creates a message containing the number 10.
2. Process A uses the send() operation to send the message.
3. The operating system transfers the message to Process B.
4. Process B uses the receive() operation to obtain the message.
5. Process B receives the value 10 and processes it.


The communication can be represented as:


Process A
↓
send(10)
↓
Message Queue / Communication Channel
↓
receive(10)
↓
Process B

---

Message Queues in Inter-Process Communication (IPC)

1. Definition

A message queue is an IPC mechanism that allows processes to exchange data by sending and receiving messages through a queue managed by the operating system.

Messages remain in the queue until a receiving process retrieves them. Unlike shared memory, processes do not need to access the same memory space.

Message queues are useful when processes need to communicate without executing at exactly the same time.

2. How Message Queues Work

1. A process creates or accesses a message queue.
2. The sender places a message into the queue.
3. The operating system manages the queued messages.
4. The receiver retrieves a message from the queue.
5. The message is processed by the receiving process.

Communication Flow

+----------------+
| Process A      |
| Sender         |
+----------------+
        |
        | Send Message
        v
+----------------+
| Message Queue  |
| [Message 1]    |
| [Message 2]    |
| [Message 3]    |
+----------------+
        |
        | Receive Message
        v
+----------------+
| Process B      |
| Receiver       |
+----------------+

3. Sending and Receiving Messages

Message queues mainly use two operations:

- Send: Adds a message to the queue.
- Receive: Retrieves a message from the queue.

For example, Process A sends the message ""Hello"" to the queue. Process B retrieves ""Hello"" from the queue and processes it.

4. Blocking and Non-Blocking Operations

Blocking Operations

- A process waits until the requested operation can be completed.
- For example, a receiver may wait until a message becomes available.

Non-Blocking Operations

- A process continues execution without waiting for the operation to complete.
- For example, a receiver can check the queue and continue if no message is available.

Note: The exact behavior depends on the operating system and the queue API.

5. Advantages of Message Queues

1. Asynchronous communication: Processes can send and receive messages at different times.
2. No shared memory required: Processes communicate through the queue.
3. Message buffering: Messages can wait in the queue until retrieved.
4. Process synchronization: Helps coordinate communication between processes.
5. Message organization: Messages can be managed according to queue rules or message types.
6. Process independence: The sender and receiver do not need to execute simultaneously.

6. Disadvantages of Message Queues

1. Limited capacity: Queues may become full if messages are not retrieved.
2. Operating system overhead: Managing queues and transferring messages consumes resources.
3. Message size limits: Operating systems may restrict the size of individual messages.
4. Synchronization issues: Processes must handle empty or full queues appropriately.
5. Additional management: Queues may require creation, permissions, and cleanup.

7. Simple Example

Scenario: Process A sends a message to Process B using a message queue.

Process A
    |
    | Sends "Hello"
    v
Message Queue
    |
    | Stores the message
    v
Process B
    |
    | Receives "Hello"
    v
Displays: Hello

Working

1. Process A sends ""Hello"" to the message queue.
2. The operating system stores the message in the queue.
3. Process B retrieves the message when it is ready.
4. Process B displays the received message.

8. Real-Life Applications

- Communication between background processes
- Task queues in web applications
- Job scheduling systems
- Operating system services
- Producer-consumer applications
- Distributed applications using message-brokering systems

9. Conclusion

Message queues provide a structured way for processes to exchange messages through an operating-system-managed queue. They support asynchronous communication, message buffering, and process coordination without requiring shared memory.
