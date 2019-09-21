# Anatomy of a format string

When you make a call to printf, the basic idea is that you are going to provide a string of characters that has some 
literal characters and some elements that are to be replaced. For example, a string like:

    "a b c"

Will be printed literally as it appears. 

While it is sometimes enough to literally write into your code exactly what you want to print, you usually want to do 
something fancier--either introducing special characters using escape sequences or introducing variable values using 
format specifiers.

## Escape Sequences

There are some characters that you cannot directly enter into a string. These are characters like a newline, which must 
be represented using some special syntax. These are called escape sequences and look like this:

    "a\nb\nc"

Here, I've entered the newlines between each letter, a, b and c. Each escape sequence starts with a backslash ('\') 
character. The main escape sequences that you'll use are: \n, to put a newline, and \t, to put in a tab. 

Since a backslash normally indicates the start of an escape sequence, if you want to put in an escape sequence you need to use \\ to display a backslash:

    "C:\\Program Files\\World of Warcraft"

is how you'd write a Windows path in C.

There's one other advanced trick, which is that you can write \<num> to display the ASCII character represented by 
the value num. This is useful if you want to display a character that you can't easily type on your keyboard, such as 
accented letters. 

For example, \130 will print out an character (in some cases, depending on what your machine is set up to do with 
extended ASCII characters.)

## Format Specifiers

If you want to introduce some variance into the output, you do so by indicating that external data is needed:

    "We have %d cats"

In this string, the %d indicates that the value to be displayed at that point in the string needs to be taken from a 
variable. The % sign indicates that we are splicing some data into the string, and the d character indicates that we 
are splicing in a decimal number. 

The part of the string that begins with % is called the format specifier. In order to actually get that number, we need 
to provide that value to printf:

    printf( "We have %d cats", 3 );

which will display:

    "We have 3 cats"

All of the interesting formatting that you can do involves changing the values you put after the % sign, which is the 
actual format.

The format for what appears about a % sign is:

    %[flag][min width][precision][length modifier][conversion specifier]

Most of these fields are optional, other than providing a conversion specifier, which you've already seen (for example, 
using %d to print out a decimal number).

Understanding this formatting is best done by working backward, starting with the conversion specifier and working 
outward. 

So let's begin at the end!

## Conversion Specifier

The conversion specifier is the part of the format specifier that determines the basic formatting of the value that is 
to be printed.

### Conversion specifiers for integers

If you want to print a decimal integer number in base 10, you'd use either d or i (synonyms with printf): %d or %i.

If you want to print an integer in octal or hexadecimal you'd use o for octal, or x for hexadecimal. 

If you want capital letters (A instead of a when printing out decimal 10) then you can use X.

### Conversion specifiers for floating point numbers

Displaying floating point numbers has a ton of different options, best shown in a table:

|Specifier|Description|Example|
|:-------:|:---------:|:-----:|
|f|Display the floating point number using decimal representation|3.1415|
|e|Display the floating point number using scientific notation with e|1.86e6 (same as 1,860,000)|
|E|Like e, but with a capital E in the output|1.86E6|
|g|Use shorter of the two representations: f or e|3.1 or 1.86e6|
|G|Like g, except uses the shorter of f or E|3.1 or 1.86E6|

Okay, that wasn't too bad was it? But that chart is kind of complicated. My recommendation: just use %g, and it will 
usually do what you want:

    printf( "%g", 3.1415926 );

which displays:

    3.1515926

or:

    printf( "%g", 93000000.0 );

which displays

    9.3e+07

Where scientific notation is most appropriate.

## Displaying a Percent Sign

Since the percent sign is used to define format specifiers, there's a special format specifier that means "print the 
percent sign":

    "%%"

to simply print out a percent sign.

Now, let's walk through each of the different components of a format specifier.

