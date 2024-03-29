# Environment setup

If you want to set up your environment for C programming language, you need the following two software 
tools available on your computer, (a) Text Editor and (b) The C Compiler.

## Text Editor

This will be used to type your program. Examples of few a editors include Windows Notepad, OS Edit 
command, Brief, Epsilon, EMACS, and vim or vi.

The name and version of text editors can vary on different operating systems. For example, Notepad will 
be used on Windows, and vim or vi can be used on windows as well as on Linux or UNIX.

The files you create with your editor are called the source files and they contain the program source 
codes. The source files for C programs are typically named with the extension ".c".

Before starting your programming, make sure you have one text editor in place and you have enough 
experience to write a computer program, save it in a file, compile it and finally execute it.

## The C Compiler

The source code written in source file is the human readable source for your program. It needs to be 
"compiled", into machine language so that your CPU can actually execute the program as per the instructions given.

The compiler compiles the source codes into final executable programs. The most frequently used and free available 
compiler is the GNU C/C++ compiler, otherwise you can have compilers either from HP or Solaris if you have the 
respective operating systems.

The following section explains how to install GNU C/C++ compiler on various OS. We keep mentioning C/C++ together 
because GNU gcc compiler works for both C and C++ programming languages.

### Installation on UNIX/Linux

If you are using Linux or UNIX, then check whether GCC is installed on your system by entering the following command 
from the command line −

```
$ gcc -v
```

If you have GNU compiler installed on your machine, then it should print a message as follows:

```
Using built-in specs.
Target: i386-redhat-linux
Configured with: ../configure --prefix=/usr .......
Thread model: posix
gcc version 4.1.2 20080704 (Red Hat 4.1.2-46)
```

If GCC is not installed, then you will have to install it yourself using the detailed instructions available at 
https://gcc.gnu.org/install/

This tutorial has been written based on Linux and all the given examples have been compiled on the Cent OS flavor of 
the Linux system.

### Installation on Mac OS

If you use Mac OS X, the easiest way to obtain GCC is to download the Xcode development environment from Apple's web 
site and follow the simple installation instructions. Once you have Xcode setup, you will be able to use GNU compiler 
for C/C++.

Xcode is currently available at developer.apple.com/technologies/tools/.

### Installation on Windows

To install GCC on Windows, you need to install MinGW. To install MinGW, go to the MinGW homepage, www.mingw.org, and 
follow the link to the MinGW download page. Download the latest version of the MinGW installation program, which should 
be named MinGW-<version>.exe.

While installing Min GW, at a minimum, you must install gcc-core, gcc-g++, binutils, and the MinGW runtime, but you may 
wish to install more.

Add the bin subdirectory of your MinGW installation to your PATH environment variable, so that you can specify these 
tools on the command line by their simple names.

After the installation is complete, you will be able to run gcc, g++, ar, ranlib, dlltool, and several other GNU tools 
from the Windows command line.