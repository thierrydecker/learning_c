
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

#define add(a,b) (a+b) // Using macros

// The main function
int main()
{
  int a=5;
  int b=4;
  // Sum of a and b
  printf("Sum of %d and %d is %d\n", a, b, add(a,b));
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
# 1 "hello.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "hello.c"



# 1 "/usr/include/stdio.h" 1 3 4
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 33 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 424 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 1 3 4
# 442 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 443 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 444 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 425 "/usr/include/features.h" 2 3 4
# 448 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 2 3 4
# 449 "/usr/include/features.h" 2 3 4
# 34 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 2 3 4
# 28 "/usr/include/stdio.h" 2 3 4
[...]
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
[...]
# 9 "hello.c"
int main()
{
  int a=5;
  int b=4;

  printf("Sum of %d and %d is %d\n", a, b, (a+b));
}
```

In the above output, source file is filled with lots and lots of info, but at the end our code is preserved.
Analysis:

- printf contains now a + b rather than add(a, b) that’s because macros have expanded.
- Comments are stripped off.
- \#include<stdio.h> is missing instead we see lots of code. So header files has been expanded and included in our 
source file.
