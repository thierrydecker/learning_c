
# Compiling a C program (Behind the Scenes)

C is a high-level language and it needs a compiler to convert it into an executable code so that the program can be
run on our machine.

How do we compile and run a C program?

Below are the steps we use on an Ubuntu machine with gcc compiler.

## Compilation

We first create a C program using an editor and save the file as hello.c.
    
```
/* Compilation test
 **/

#include <stdio.h>

// The main function
int main()
{
  // Print hello world!
  printf("Hello world!\n");
}
```

Then compile it using below command:

```
$ gcc –Wall hello.c –o hello
```

The option -Wall enables all compiler’s warning messages. This option is recommended to generate better code.

The option -o is used to specify the output file name. If we do not use this option, then an output file with 
name a.out is generated. 

After compilation executable is generated and we run the generated executable using below command.

```
 $ ./filename
``` 

What goes inside the compilation process?

Compiler converts a C program into an executable. There are four phases for a C program to become an executable:

- Pre-processing
- Compilation
- Assembly
- Linking

By executing below command, We get the all intermediate files in the current directory along with the executable.

``` 
$gcc –Wall –save-temps hello.c –o hello
``` 

The following screenshot shows all generated intermediate files.

``` 
-rwxr-xr-x 1 tdecker tdecker 16608 sept. 17 13:25 hello
-rw-r--r-- 1 tdecker tdecker   134 sept. 17 13:04 hello.c
-rw-r--r-- 1 tdecker tdecker 16152 sept. 17 13:25 hello.i
-rw-r--r-- 1 tdecker tdecker  1536 sept. 17 13:25 hello.o
-rw-r--r-- 1 tdecker tdecker   448 sept. 17 13:25 hello.s
```

### Pre-processing

This is the first phase through which source code is passed. This phase include:

- Removal of Comments
- Expansion of Macros
- Expansion of the included files.
- Conditional compilation

The preprocessed output is stored in the hello.i. Let’s see what’s inside hello.i:

``` 
``` 