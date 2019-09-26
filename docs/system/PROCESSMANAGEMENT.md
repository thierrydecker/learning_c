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

The process that spawns a new process is known as the ***parent***.

The new process is known as the ***child***.

Every process is spawned from another process (except, of course, the init process).

Therefore, every child has a parent.

This relationship is recorded in each process's ***parent process ID*** (ppid), which is the pid of the child's parent.

Each process is owned by a ***user*** and a ***group***.

This ownership is used to control access rights to resources.

To the kernel, users and groups are mere integer values.

Through the files ***/etc/paswd*** and ***/etc/group***, these integers are mapped to human-readable strings which Linux 
sers are familiar, such as the user ***root*** or the group ***wheel*** (generally speaking, the Linux kernel has no 
interest in human-readable strings, and prefers to identify objects with integers.)

Each child process inherits its parent's user and group ownership.

Each process is also part of a ***process group***, which simply expresses its relationship to other processes and 
should not be confused with the aforementioned user/group concept.

Children normally belong to the same process group as their parents.

In addition, when a shell starts up a pipeline (e.g., when a user enters ***ls | less***), all the commands in the 
pipeline go into the same process group.

The notion of process group makes it easy to send signals or get information on an entire pipeline, as well as all 
children of the process in the pipeline.

From the perspective of a user, a process group is closely related to a ***job***.

### pid_t

Programmatically, the process ID is represented by the pid_type, which is defined in the header file ***<sys/types.h>***.

The exact backing C type is architecture specific and not defined by any C standard.

On Linux, however, ***pid_t*** a typedef to the C int type.

### Obtaining the Process ID and Parent Process ID

The ***getpid()*** system call returns the process ID of the invoking process:

```
\#include <unistd.h>

pid_t getpid (void);
```

The ***getppid()*** system call returns the process ID of the invoking process's parent:

```
\#include <unistd.h>

pid_t getppid (void);
```

Neither call will return an error and consequently, their usage is trivial.

***process.h:***

```
#ifndef PROCESSES_H
#define PROCESSES_H

void process_print (void);
void pid_print ();
void ppid_print ();

#endif
```

***process.c:***

```
#include "processes.h"

#include <stdio.h>
#include <unistd.h>

/*
 * Print process related values
 * */
void process_print (void)
{
        pid_print ();
        ppid_print ();
}

/*
 * Print the Process ID
 * */
void pid_print (void)
{
        printf ("My pid is: %d\n", getpid ());
}

/*
 * Print the Parent's Process ID
 * */
void ppid_print (void)
{
        printf ("My parent's pid is: %d\n", getppid ());
}
```

***mainc.c:***

```
#include <stdlib.h>

#include "processes.h"

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        process_print ();
        return EXIT_SUCCESS;
}
```

## Running a New Process

In Linux, the act of loading into memory and executing a program image is separate from the act of creating a new 
process.

One system call loads a binary program into memory, replacing the previous content of the address space, and begins 
execution of the new program.

This is called executing a new program, and the functionality is provided by the ***exec*** family of call.

A different system call is used to create a new process, which initially is near-duplicate of its parent process.

Often, the new process immediatly executes a new program.

The act of creating a new process is called forking, and this functionality is provided by the fork() system call.

Two acts (first a fork to create a new process, and then an exec to load a new binary into that process) are thus 
required to execute a new program in a new process.

We will cover the exec call first, then fork().

### The Exec Family of Calls

There is no single exec function.

Instead, there is a family of exec functions built on a single system call.

#### execl

Let's first look at the simplest of these calls, _**execl()**_:

```
#include <unistd.h>

int execl (
        const char *path,
        const char *arg,
        ...
);
```

A call to execl() replaces the current process image with a new one by loading into memory the programm pointed at by 
path.

The parameter arg is the first argument to this program.

The ellipsis signifies a variable number of arguments (the execl() function is variadic, which means that additional
arguments may optionally follow, one by one).

The list of arguments must be NULL-terminated.

```
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        int ret;
        ret = execl ("/bin/vi", "vi", NULL);
        if (ret == -1) {
                perror ("execl");
        }
        return EXIT_SUCCESS;
}
``` 

Note that we follow the Unix convention and pass "vi" as the program's first argument.

The shell puts the last component into the first argument, so a program can examine its first argument, **_argv[0]_** to
discover its binary image.

In many cases, several several system utilities that appear as different names to the user are in fact a single program
with hard links for their multiple names.

The program uses this first argument to determine its behavior.

As another example, if you wanted to edit the file /etc/network/interfaces, you could execute the following code:

```
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        int ret;
        ret = execl ("/bin/nano", "nano", "/etc/network/interfaces", NULL);
        if (ret == -1) {
                perror ("execl");
        }
        return EXIT_SUCCESS;
}
``` 

Normally, execl() does not return.

A successful invocation ends by jumping to the entry point of the new program, the just-executed code no longer exists
in the process's address space.

On error, however, **_execl()_** returns -1 end set **_errno_** to indicate the problem.

We will look at the possible **_errno_** values later in this section.

A successful execl() call changes not only the address space and process image, but certain other attributes of the
process.

- Any pending signals are lost.

- Any signal that the process is catching are returned to their default behavior, as the signal handler no longer exist
in the process's address space.

- Memory locks are dropped.

- Most thread attributes are returned to their default value.

- Anything related to the process's memory address space, including any mapped files, is cleared.

- Anything that exists solely in user space, including features of the C library, such as atexit() behavior, is cleared.

Some properties of the process, however, do not change.

For example, the pid, priority, and owning user and group all remain the same.

Normally, open files are inherited across an exec.

This means the newly executed program has full access to all of the files open in the original process, assuming it 
knows the file descriptor values.

However, this is often not the desired behavior.

The usual practice is to close files before the exec, althoug it is also possible to instruct the kernel to do so 
automatically via the **_fcntl()_** function. 

#### The rest of the family

In addition to execl(), here are five other members of the exec family:

```
#include <unistd.h>

int execlp (const char *file,
            const char *arg,
            ...);

int execle (const char *path,
            const char *arg,
            ...,
            char * const envp[]);

int execv (const char *path, char *const argv[]);

int execvp (const char *file, char *const argv[]);

int execve (const char *filename,
            char *const argv[],
            char *const envp[]);
```

The mnemonics are simple:

The **_l_** and **_v_** delineate whether the arguments are provided via a list or an array (vector).

The **_p_** denotes that the user's full path is searched for the given file.

Commands using the p variant ca nspecify just a filename, so long as it is located in the user's path.

Finally, the **_e_** notes that a new environment is also supplied for the new process. 

Curiously, although there is no technical reason for the omission, the exec family contains no member that both searches 
the path and takes a new environment. 

This is probably because the p variants were implemented for use by shells, and shell-executed processes generally 
inherit their environments from the shell.

The following snippet uses execvp() to execute nano, as we did previously, relying on the fact that nano is in the 
user’s path:

```
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        int ret;
        ret = execvp ("nano", "nano", "/etc/network/interfaces", NULL);
        if (ret == -1) {
                perror ("execvp");
        }
        return EXIT_SUCCESS;
}
```

#### Security Risk with execlp() and execvp()

    Set-group-ID and set-user-ID programs (processes that run as the group or user of their binary’s owner and not the 
    group or user of their invoker, respectively) should never invoke the shell or operations that in turn invoke the 
    shell. 

    Doing so opens a security hole as the invoking user may set environment variables to manipulate the behavior of the
    shell. 

    The most common form of this attack is path injection, in which the attacker sets the PATH variable to cause the 
    process to execlp() a binary of the attacker’s choosing, effectively allowing the attacker to run any program with 
    the credentials of the set-group-ID or set-user-ID program.

The members of the exec family that accept an array work about the same, except that an array is constructed and passed 
in instead of a list. 

The use of an array allows the arguments to be determined at runtime. 

As with the variadic list of arguments, the array must be NULL-terminated.

The following snippet uses execv() to execute nano, as we did previously:

```
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        char *const arguments[] = {"nano", "/etc/network/interfaces", NULL};
        int ret;
        ret = execv ("/bin/nano", arguments);
        if (ret == -1) {
                perror ("execv");
        }
        return EXIT_SUCCESS;
}
```

In Linux, only one member of the exec family is a system call. 

The rest are wrappers in the C library around the system call. 

Because variadic system calls would be difficult to implement and because the concept of the user’s path exists solely 
in user space, the only option for the lone system call is execve(). 

The system call prototype is identical to the user call.

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