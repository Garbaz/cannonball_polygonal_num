# Exhaustive search of numbers which are polygonal and a cannon ball number

In [a Numberphile video](https://www.youtube.com/watch?v=q6L06pyt9CA) Matt Parker presented [his results](https://www.numberphile.com/cannon-ball-numbers) from a search he conducted for numbers which are [polygonal](https://en.wikipedia.org/wiki/Polygonal_number) and a cannon ball number (Can't find a wiki article about those). This is a C implementation for Linux (Should be easy to port to Windows C++) of a mostly "dumb" exhaustive search for more of these numbers.

I can't promise that the code is correct, but it does spit out all the examples from the video, so it seems to be working.

## The Math

### Polygonal numbers

Polygonal numbers are numbers which, taken their number in circles, can be aranged into a polygon of given side count **s**.

The formula for a given side count **s** and a given side length **n** is:

![POLYGONAL NUMBER FORMULA 1](https://wikimedia.org/api/rest_v1/media/math/render/svg/0fc8bcb639d6709efa53b39bc4fcd8e57da65999)

or slightly rearranged:

![POLYGONAL NUMBER FORMULA 2](https://wikimedia.org/api/rest_v1/media/math/render/svg/3bd958e84a96b2601be5d9b758c169f88a44863b)

To make the search slightly faster, we can use the first of the following formula to calculate **P(s,n+1)** from **P(s,n)**:

![POLYGONAL NUMBER FORMULA 3](https://wikimedia.org/api/rest_v1/media/math/render/svg/cc5297af8722449c5805acc848b9dbce25b8e0d4)
 
### Cannonball numbers

Cannonball numbers are numbers which, taken their number in spheres, can be stacked into a "cannon ball stack" with a polygonal base of given side count. More mathematically a cannon ball number is the sum of the first **n** polygonal numbers for a given side count **s**.

## The Code

### Overview

In [src/](src/) is the C source code of the normal implementation.

In [other_impl/](other_impl/) are two alternative implementations, which use [gmplib](https://gmplib.org) to allow for arbitrarily big numbers. For now they are pretty much pointless, since we haven't reached the limits of 64 bit unsigned integers yet.

One of these two alternative implementations uses gmp for all numbers, the other for some, using unsigned long for numbers which are expected to only grow slowly compared to others.

### Build

Since it's only one source file, the compilation is straightforward to do "manually". Still, if you have `make` and `gcc`, you can just run

```
make
```

to compile. The resulting binary should be in a new folder build/.

### Run/Configure

To configure from where to where the program should search, you have to change the constants at the top of the source file. See the comment above them for what the different constants mean.

### Improvements

Currently the code only uses some very obvious optimizations and there might be mathematical tricks to speed up the search.

One option would be reduce the search space by ruling out logically that certain configurations are impossible to give us a result.

### Contributing

Feel free to fork and do your own thing or improve my code. I don't know how to merge and stuff, so I probably won't be able to respond to pull requests. If you find an error in my code, feel free to tell me!
