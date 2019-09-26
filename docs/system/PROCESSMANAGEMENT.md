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

And, of course, from the view of a process, it's pid never changes.

The **_idle_** process, which is the process the kernel "runs" when there are no other runnable processes, has the pid 0.

The first process that the kernel executes after booting the system, called the **_init process_**, has the pid 1.

Normally, the init process on the Linux system is the **_init_** program.

We use the term "init" to refer to both the initial process that the kernel runs, and the specific program used for that
purpose.

Unless the user explicitly tells the kernel what process to run (through the **_init_** kernel command-line parameter),
the kernel has to identify a suitable init process on ts own.

The Linux kernel tries four executables, in the following order:

**_1) /sbin/init:_** The preferred and most likely location for the init process.

**_2) /etc/init:_** Another likely location for the init process.

**_3) /bin/init:_** A fallback location for the init process.

**_4) /bin/sh:_** The location of the Bourne Shell, which the kernel tries to run if it fails to find an init process.

**_Note:_** This list may vary, depending on the implementations.

The first of these processes that exists is executed as the init process.

If all four processes fail to execute; the Linux kernel halts the system with a panic.

After the handoff from the kernel, the init process handles the remainder of the boot process.

Typically, this includes initializing the system, starting various services, and launching a login program.

### Process ID allocation

By default, the kernel imposes a maximum process ID value of 32768.

This is for compatibility with older Unix systems, which used signed 16-bi types of process IDs.

System administrators can set the value higher via /proc/sys/kernel/pid_max, trading a larger pid space for reduced
compatibility.

The kernel allocates process IDs to processes in a strictly linear fashion.

If pid 17 is the highest number currently allocated, pid 18 will be allocated next, even if the process last assigned
pid 17 is no longer running when the new process starts.

The kernel does not reuse process ID values until it wraps around the top (hat is, earlier values will not be reused 
until the value in /proc/sys/kernel/pid_max is allocated).

Therefore, while Linux makes no garantee of the uniqueness of process IDs over a long period, its allocation behavior 
does provide at least short-term comfort is the statbility and uniqueness of pid values.

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