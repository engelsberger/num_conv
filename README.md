# Description

A basic converter to convert numbers between number systems. Works for all number systems starting from binary all the way up to a 36-based number system (starts like hexadecimal and continues on like F=15, G=16, H=17 and so forth).

Takes two or three arguments:
- Number: (mandatory) The number to convert. Make sure it is a valid number from the given input number system.
- Input number system: (optional) The number system the given number is part of (2-36). Set to decimal by default.
- Output number system: (mandatory) The number system the given number should get converted to (2-36).

Writes the converted number directly to stdout without any extra letters or descriptions.

Returns:
- 0 if the program got executed successfully
- -1 if an input error was detected

# Examples

"num_conv 3F 16 2" -> Converts "3F" from hexadecimal to binary and writes "111111" to stdout (returns 0)

"num_conv 46 16" -> Converts "46" from decimal to hexadecimal and writes "2E" to stdout (returns 0)

"num_conv Z 36 10" -> Converts "Z" from a 36-based number system to decimal and writes "35" to stdout (returns 0)

"num_conv 15 2 10" -> Returns an error message, since 15 is not a valid binary number (returns -1)

# Install

Clone the Github repository with:

`git clone https://github.com/engelsberger/num_conv`

Change into the cloned folder and build the program with:

`make`
