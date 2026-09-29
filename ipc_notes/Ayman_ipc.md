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


