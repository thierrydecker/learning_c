# Process management

Processes are, after files, the most fundamental abstraction in a Nix system.

As object code in execution (active, alive, running programs), processes are more than just assembly language.

They consist of data, resouces, state and a virtualized computer.

## Program vs Process vs Threads

A _**binary**_ is compiled, executable code lying dormant on a storage medium such as a disk (we may also user the term 
_**program**_)

A _**process**_ is a **running** program.

A process includes the binary image, loaded into memory, but also much more:

- an instance of virtualized memory,
- kernel resources such as open files,
- a security context such as an associated user,
- and one or more threads.

A _**thread**_ is the unit of activity inside of a process.

Each thread has its own virtualized processor, which includes: 

- a stack, 
- processor state (such as registers),
- and an instruction pointer.

In a single threaded process, the process is the thread.

There is one instance of virtualized memory and one virtualized processor.

As the virtualization of memory is associated with the process, the threads all share the same memory address space.

## The Process ID

Each process is represented by a unique identifier, the **_process ID_** (frequently shortened to **_pid_**).

The pid is guaranteed to be unique at **_any single point in time_**.

That is, while at time t+0 there can be only one process with the pid 770 (if any process at all exists with such a 
value). 

There is no guarantee that at time t+1 a different process won't exist with pid 770.

Essentially, however, most programs presume that the kernel does not reissue process identifiers (an assumption that, 
as you will see shortly, is fairly safe).

An, of course, from the view of a process, it's pid never changes. 

### Process ID allocation

### The Process Hierarchy

### pid_t

### Obtaining the Process ID and Parent Process ID

## Running a New Process

### The Exec Family of Calls

### The fork() System Call

## Terminating a Process

### Other Ways to Terminate

### atexit()

### on_exit()

### SIGHLD

### Waiting for Terminated Child Processes

### Waiting for a Specific Process

### Even More Waiting Versatility

### BSD Wants to Play: wait3() and wait4()

### Launching and Waiting for a New Process

### Zombies

## Users and Groups

### Real, Effective and Saved Users and Group IDs

### Changing the Real or Saved User or Group ID

### Changing the Effective User or Group ID

### Changing the Effective User or Group ID, BSD Style

### Changing the Effective User or Group ID, HP-UX Style

### Preferred User/Group ID Manipulation

### Support for Saved Users IDs

### Obtaining the User and Group IDs

## Sessions and Process Groups

### Session System Calls

### Process Group System Calls

### Obsolete Process Group Functions

## Daemons

## Conclusion