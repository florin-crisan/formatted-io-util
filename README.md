# Formatted I/O utilities

These are various formatted I/O (i.e., fancy printing to `std::ostream`) utilities that I have repeatedly written throughout the years but never formally collected into a reusable library.

* A set of `operator <<` to properly print `signed char` and `unsigned char` (numbers) as distinct from plain `char` (printable character).

## Requirements

* A modern machine with 8-bit bytes, 2's complement, no parity bits.
* A C++98 compiler (tested with GCC and Visual C++).
* [CMake](https://cmake.org/) 3.5 or higher (the oldest version that has the modern `Boost::boost` target)
* [Boost](https://www.boost.org/) 1.33 or higher, because that's the oldest that has the current interface of [Boost Test](https://www.boost.org/doc/libs/release/libs/test/doc/html/index.html).

The code can probably bent further so that it only needs a C++98 compiler.
