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

```
Set-group-ID and set-user-ID programs (processes that run as the group or user of their binary’s owner and not the 
group or user of their invoker, respectively) should never invoke the shell or operations that in turn invoke the 
shell. 

Doing so opens a security hole as the invoking user may set environment variables to manipulate the behavior of the
shell. 

The most common form of this attack is path injection, in which the attacker sets the PATH variable to cause the 
process to execlp() a binary of the attacker’s choosing, effectively allowing the attacker to run any program with 
the credentials of the set-group-ID or set-user-ID program.
```

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

#### Error values

On success, the exec system calls do not return. On failure, the calls return −1 and set errno to one of the following 
values:

- E2BIG

The total number of bytes in the provided arguments list ( arg ) or environment (envp) is too large.

- EACCES

The process lacks search permission for a component in path ; path is not a regular file; the target file is not marked 
executable; or the filesystem on which path or file resides is mounted noexec.
- EFAULT

A given pointer is invalid.
- EIO

A low-level I/O error occurred (this is bad).

- EISDIR

The final component in path , or the interpreter, is a directory.

- ELOOP

The system encountered too many symbolic links in resolving path .

- EMFILE

The invoking process has reached its limit on open files.
- ENFILE

The system-wide limit on open files has been reached.

- ENOENT

The target of path or file does not exist, or a needed shared library does not exist.

- ENOEXEC

The target of path or file is an invalid binary or is intended for a different machine architecture.

- ENOMEM

There is insufficient kernel memory available to execute a new program.

- ENOTDIR

A nonfinal component in path is not a directory.

- EPERM

The filesystem on which path or file resides is mounted nosuid , the user is not root, and path or file has the suid or 
sgid bit set.

- ETXTBSY

The target of path or file is open for writing by another process.

### The fork() System Call

A new process running the same image as the current one can be created via the fork() system call:

```
#include <sys/types.h>
#include <unistd.h>

pid_t fork (void);
```

A successful call to **_fork()_** creates a new process, identical in almost all aspects to the invoking process. 

Both processes continue to run, returning from fork() as if nothing special had happened.

The new process is called the “child” of the original process, which in turn is called the “parent". 

In the child, a successful invocation of fork() returns 0.

In the parent, fork() returns the pid of the child. 

The child and the parent process are identical in nearly every facet, except for a few necessary differences:

- The pid of the child is, of course, newly allocated and different from that of the parent.

- The child’s parent pid is set to the pid of its parent process.

- Resource statistics are reset to zero in the child.

- Any pending signals are cleared and not inherited by the child.

- Any acquired file locks are not inherited by the child.

On error, a child process is not created, **_fork() returns −1_**, and errno is set appropriately.

There are two possible errno values, with three possible meanings:

- EAGAIN

The kernel failed to allocate certain resources, such as a new pid, or the **_RLIMIT_NPROC_** resource limit 
(**_rlimit_**) has been reached.

- ENOMEM

Insufficient kernel memory was available to complete the request.

Use is simple:

```
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "processes.h"

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        pid_t forked_pid = fork ();

        if (forked_pid > 0) {
                printf ("I am the parent!\n");
        } else if (forked_pid == 0) {
                printf ("I am the child!\n");
        } else if (forked_pid < 0) {
                perror ("fork");
                return EXIT_FAILURE;
        }
        process_print ();
        return EXIT_SUCCESS;
}
```

The above snippet could produce:

```
I am the parent!
My pid is: 3096
My parent's pid is: 1089
I am the child!
My pid is: 3097
My parent's pid is: 3096
```

But could also produce:

```
I am the parent!
I am the child!
My pid is: 3310
My parent's pid is: 3309
My pid is: 3309
My parent's pid is: 906
```

Or even:

```
I am the parent!
My pid is: 3340
My parent's pid is: 906
I am the child!
My pid is: 3344
My parent's pid is: 1
```

In this last case, Child's parent doesn't seem to be the process that forked... more on this later.

One common usage of fork() is to create a new process in which a new binary image is then loaded—think a shell running 
a new program for the user or a process spawning a helper program. 

First the process forks a new process, and then the child executes a new binary image. This “fork plus exec” combination 
is frequent and simple.

The following example spawns a new process running the binary /usr/bin/cat:

```
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Main function
 * */
int main (int argv, char *args[])
{
        pid_t forked_pid;
        forked_pid = fork ();
        if (forked_pid == -1) {
                perror ("fork");
                return EXIT_FAILURE;
        }
        /* the child ... */
        if (forked_pid == 0) {
                char *const arguments[] = {"cat", "/etc/network/interfaces", NULL};
                int ret;
                ret = execv ("/usr/bin/cat", arguments);
                if (ret == -1) {
                        perror ("execv");
                        return EXIT_FAILURE;
                }
        }
        return EXIT_SUCCESS;
}
```

The parent process continues running with no change, other than that it now has a new child. 

The call to execv() changes the child to running the /usr/bin/cat program.

## Terminating a Process

POSIX and C89 both define a standard function for terminating the current process:

```
#include <stdlib.h>
void exit (int status);
```
A call to exit() performs some basic shutdown steps, then instructs the kernel to terminate the process. 

This function has no way of returning an error—in fact, it never returns at all. 

Therefore, it does not make sense for any instructions to follow the exit() call.

The status parameter is used to denote the process’s exit status. 
Other programs (as well as the user at the shell) can check this value. 

Specifically, status & 0377 is returned to the parent. 

We will look at retrieving the return value later in this chapter.

EXIT_SUCCESS and EXIT_FAILURE are defined as portable ways to represent success and failure. 

On Linux, 0 typically represents success; a nonzero value, such as 1 or −1 , corresponds to failure.

Consequently, a successful exit is as simple as this one-liner:

```
exit (EXIT_SUCCESS);
```

Before terminating the process, the C library performs the following shutdown steps, in order:

- Call any functions registered with **_atexit()_** or **_on_exit()_** , in the reverse order of their registration. (We will 
discuss these functions later in this chapter).

- Flush all open standard I/O streams.

- Remove any temporary files created with the **_tmpfile()_** function.

These steps finish all the work the process needs to do in user space, so exit() invokes the system call _exit() to let 
the kernel handle the rest of the termination process:

```
#include <unistd.h>
void _exit (int status);
```

When a process exits, the kernel cleans up all of the resources that it created on the process’s behalf that are no 
longer in use. 

This includes, but is not limited to, allocated memory, open files, and System V semaphores. 

After cleanup, the kernel destroys the process and notifies the parent of its child’s demise.

Applications can call _exit() directly, but such a move seldom makes sense: most applications need to do some of the 
cleanup provided by a full exit, such as flushing the stdout stream. 

In a redundant stroke of redundancy, the ISO C99 standard added the **__Exit()_** function, which has identical behavior
to **__exit()_** :

```
#include <stdlib.h>
void _Exit (int status);
```

### Other Ways to Terminate

The classic way to end a program is not via an explicit system call, but by simply “falling off the end” of the program. 

In the case of C, this happens when the main() function returns. 

The “falling off the end” approach, however, still invokes a system call:

The compiler simply inserts an implicit call to exit() after its own shutdown code. 

It is good coding practice to explicitly return an exit status, either via exit(), or by returning a value from main(). 

The shell uses the exit value for evaluating the success or failure of commands. 

Note that a successful return is exit(0), or a return from main() of 0.

A process can also terminate if it is sent a signal whose default action is to terminate the process. 

Such signals include SIGTERM and SIGKILL.

A final way to end a program’s execution is by incurring the wrath of the kernel. 

The kernel can kill a process for executing an illegal instruction, causing a segmentation violation, running out of 
memory, consuming more resources that allowed, and so on.

### atexit()

Linux implements, the **_atexit()_** library call, used to register functions to be invoked upon process termination:

```
#include <stdlib.h>
int atexit (void (*function)(void));
```

A successful invocation of **_atexit()_** registers the given function to run during normal process termination, that 
is, when a process is terminated via either exit() or a return from main(). 

If a process invokes an exec function, the list of registered functions is cleared (as the functions no longer exist 
in the new process’s address space). 

If a process terminates via a signal, the registered functions are not called.

The given function takes no parameters, and returns no value. A prototype has the form:

```
void my_function (void);
```

Functions are invoked in the reverse order that they are registered.

That is, the functions are stored in a stack, and the last in is the first out (LIFO). 

Registered functions must not call exit() lest they begin an endless recursion. 

If a function needs to end the termination process early, it should call _exit() . 

Such behavior is not recommended, however, as a potentially important shutdown function may then not run.

The POSIX standard requires that atexit() support at least ATEXIT_MAX registered functions and that this value be at 
least 32. 

The exact maximum may be obtained via sysconf() and the value of _SC_ATEXIT_MAX :

```
long atexit_max;
atexit_max = sysconf (_SC_ATEXIT_MAX);
printf ("atexit_max=%ld\n", atexit_max);
```

On success, atexit() returns 0. On error, it returns −1 .

Here’s a simple example:

```
#include <stdio.h>
#include <stdlib.h>

void out (void)
{
        printf ("atexit() succeeded!\n");
}

int main (void)
{
        if (atexit (out)) {
                fprintf (stderr, "atexit() failed!\n");
        }
        return 0;
}
```

### on_exit()

SunOS 4 defined its own equivalent to atexit() , and Linux’s glibc supports it:

```
#include <stdlib.h>

int on_exit (void (*function)(int, void *), void *arg);
```

This function works the same as atexit(), but the registered function’s prototype is different:

```
void my_function (int status, void *arg);
```

The status argument is the value passed to exit() or returned from main(). The arg argument is the second parameter 
passed to on_exit().

Care must be taken to ensure that the memory pointed at by arg is valid when the function is ultimately invoked.

The latest version of Solaris no longer supports this function. You should use the standards-compliant atexit() instead.

### SIGHLD

When a process terminates, the kernel sends the signal SIGCHLD to the parent. By default, this signal is ignored, and 
no action is taken by the parent.

Processes can elect to handle this signal, however, via the signal() or sigaction() system calls. 

These calls, and the rest of the wonderful world of signals, are covered in a later chapter.

The SIGCHLD signal may be generated and dispatched at any time, as a child’s termination is asynchronous with respect 
to its parent. But often, the parent wants to learn more about its child’s termination or even explicitly wait for 
the event’s occurrence. 

This is possible with the system calls discussed next.

### Waiting for Terminated Child Processes

Receiving notification via a signal is nice, but many parents want to obtain more information when one of their child 
processes terminates (for example, the child’s return value).

If a child process were to entirely disappear when terminated, as one might expect, no remnants would remain for the 
parent to investigate. 

Consequently, the original designers of Unix decided that when a child dies before its parent, the kernel should put
the child into a special process state. A process in this state is known as a zombie. 

Only a minimal skeleton of what was once the process (some basic kernel data structures containing potentially useful 
data) is retained. 

A process in this state waits for its parent to inquire about its status (a procedure known as waiting on the zombie 
process). 

Only after the parent obtains the information preserved about the terminated child does the process formally exit and 
cease to exist even as a zombie.

The Linux kernel provides several interfaces for obtaining information about terminated children. 

The simplest such interface, defined by POSIX, is wait():

```
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait (int *status);
```

A call to wait() returns the pid of a terminated child or −1 on error. 

If no child has terminated, the call blocks until a child terminates. 

If a child has already terminated, the call returns immediately. 

Consequently, a call to wait() in response to news of a child’s demise—say, upon receipt of a SIGCHLD —will always 
return without blocking.

On error, there are two possible errno values:

- **_ECHILD_**

    The calling process does not have any children.
    
- **_EINTR_**

    A signal was received while waiting, and the call returned early.

If not NULL , the status pointer contains additional information about the child. 

Because POSIX allows implementations to define the bits in status as they see fit, the standard provides a family of 
macros for interpreting the parameter:

```
#include <sys/wait.h>

int WIFEXITED (status);
int WIFSIGNALED (status);
int WIFSTOPPED (status);
int WIFCONTINUED (status);

int WEXITSTATUS (status);
int WTERMSIG (status);
int WSTOPSIG (status);
int WCOREDUMP (status);
```

Either of the first two macros may return true (a nonzero value), depending on how the process terminated. The first, 
WIFEXITED , returns true if the process terminated normally; that is, if the process called _exit(). 

In this case, the macro WEXITSTATUS provides the low-order eight bits that were passed to _exit().

WIFSIGNALED returns true if a signal caused the process’s termination. 

In this case, WTERMSIG returns the number of the signal that caused the termination, and WCOREDUMP returns true if the 
process dumped core in response to receipt of the signal. WCOREDUMP is not defined by POSIX, although many Unix systems, 
Linux included, support it.

WIFSTOPPED and WIFCONTINUED return true if the process was stopped or continued, respectively, and is currently being 
traced via the ptrace() system call. 

These conditions are generally applicable only when implementing a debugger, although when used with waitpid() (see the 
following subsection), they are used to implement job control, too.

Normally, wait() is used only to communicate information about a process’s termination. 

If WIFSTOPPED is true, WSTOPSIG provides the number of the signal that stopped the process. 

WIFCONTINUED is not defined by POSIX, although future standards define it for waitpid(). 

As of the 2.6.10 Linux kernel, Linux provides this macro for wait(), too.

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