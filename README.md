# packrect -- Optimal solutions to the rectangle packing problem

Reads a list of rectangle sizes from standard input, and output the packed rectangle area on
standard output. It also draws the packed rectangles in ASCII on standard error.

The input format is:

    <number of rectangles in the file>
    <1st recangle width> <1st recangle height>
    <2nd recangle width> <2nd recangle height>
    etc.

Since this problem is computationally hard, The number of rectangle has to be quite small. Most
optimization ideas are from
[Huang, Eric, and Richard E. Korf. "New Improvements in Optimal Rectangle Packing." IJCAI. 2009.](http://ijcai.org/papers09/Papers/IJCAI09-092.pdf‎).

## Pre-requisite

Cmake is the only dependency, it is needed to generate makefiles.

## Building

    cd build
    cmake ..
    make

## Example usage:

    $ cat > inputs/5_squares.txt 
    5
    1 1
    2 2
    3 3
    4 4
    5 5

    $ src/packrect < input/5_squares.txt
    Testing box 11*5
    Testing box 8*7
    Testing box 12*5
    60
    5x12:
    + - - - + + - - + + - +
    |       | |     | |   |
    |       | |     | + - +
    |       | + - - + + + +
    + - - - +         + +  
    $
