# Storage classes

A storage class defines the scope (visibility) and life-time of variables and/or functions within a C Program. They 
precede the type that they modify.

We have four different storage classes in a C program:

- auto
- register
- static
- extern

## The auto Storage Class

The auto storage class is the default storage class for all local variables.

```
{
  int mount;
  auto int month;
}
```

The example above defines two variables with in the same storage class. 'auto' can only be used within functions, i.e., 
local variables.

## The register Storage Class

The register storage class is used to define local variables that should be stored in a register instead of RAM. 
This means that the variable has a maximum size equal to the register size (usually one word) and can't have the unary 
'&' operator applied to it (as it does not have a memory location).

```
{
  register int  miles;
}
```

The register should only be used for variables that require quick access such as counters. 

It should also be noted that defining 'register' does not mean that the variable will be stored in a register. 
It means that it MIGHT be stored in a register depending on hardware and implementation restrictions.

## The static Storage Class

The static storage class instructs the compiler to keep a local variable in existence during the life-time of the 
program instead of creating and destroying it each time it comes into and goes out of scope. Therefore, making local 
variables static allows them to maintain their values between function calls.

The static modifier may also be applied to global variables. When this is done, it causes that variable's scope to be 
restricted to the file in which it is declared.

In C programming, when static is used on a global variable, it causes only one copy of that member to be shared by all 
the objects of its class.

```
#include <stdio.h>
 
/* function declaration */
void func(void);
 
static int count = 5; /* global variable */
 
main() 
{

  while(count--) 
  {
    func();
  }

   return 0;
}

/* function definition */
void func( void ) {

  static int i = 5; /* local static variable */
  i++;

  printf("i is %d and count is %d\n", i, count);
}
```

When the above code is compiled and executed, it produces the following result −

```
i is 6 and count is 4
i is 7 and count is 3
i is 8 and count is 2
i is 9 and count is 1
i is 10 and count is 0
```

## The extern Storage Class

The extern storage class is used to give a reference of a global variable that is visible to ALL the program files. 
When you use 'extern', the variable cannot be initialized however, it points the variable name at a storage location 
that has been previously defined.

When you have multiple files and you define a global variable or function, which will also be used in other files, 
then extern will be used in another file to provide the reference of defined variable or function. Just for 
understanding, extern is used to declare a global variable or function in another file.

The extern modifier is most commonly used when there are two or more files sharing the same global variables or 
functions as explained below.

_**First File: main.c**_

```
#include <stdio.h>
 
int count ;
extern void write_extern();
 
main() 
{
  count = 5;
  write_extern();
}
```

_**Second File: support.c**_

```
#include <stdio.h>
 
extern int count;
 
void write_extern(void) 
{
  printf("count is %d\n", count);
}
```

Here, extern is being used to declare count in the second file, where as it has its definition in the first file, main.c. Now, compile these two files as follows −

```
$gcc main.c support.c
```

It will produce the executable program a.out. When this program is executed, it produces the following result −

```
count is 5
```

## A guideline for extern declaration/definition

_**First File: main.c**_

```
#include <stdlib.h>
#include <stdio.h>
#include "src/extvars.h"

/*
 * Main function
 * */
int main (int argv, char *args[])
{
  printf("counter: %d", counter);
  return EXIT_SUCCESS;
}
```

_**Second File: extevars.h**_

```
#ifndef EXTVARS_H
#define EXTVARS_H
// counter declaration
extern int counter;
#endif
```

_**Third File: extvars.c**_

```
#include "extvars.h"

// counter definition
int counter = 10;
```