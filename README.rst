Fixed point filters
============================
The design goals of this library are::

* Provide correct, optimized, and flexible fixed point FIR and IIR filters
* Make client interface simple and intuitive
* Minimize run-time cost of filter usage
* Emit no floating point machine instructions

Clients of the class must provide::

* Filter coefficents (as doubles) and filter depth (as an unsigned integer)
* Scale factor (as an unsigned integer)
* Integer type to use for intermediate calculations (default is std::int32_t)
* Integer type to use for input and output of filter (default is std::int16_t)

If the filter coefficients are provided as an array of literal doubles,
instances of the class will have all the integer coefficients of the filter
computed at *compile time* and no there will be no run time cost associated with
the construction of the filter. The scale factor should generally be a power of
2 so that the compiler can generate right bit shift instructions instead of
integer division instruction when performing the scaling at the end of the
filter step.

Compiling and running tests
===========================
To obtain zero run-time cost of construction and ensure no floating point
instructions are emitted, I am making use of C++14's constexpr constructors.
This means you will need a shiny new compiler to build this library. I use CMake
and Googletest. Here are the clone and build steps::

    $ git clone https://github.com/hazelnusse/fixed_point_filters.git
    $ cd fixed_point_filters
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ make test

Notes
=====
To check the generated assembly, you can do::

    $ objdump -d -S <executable or object file with debugging symbols>

This will interleave the original source with the assembly so you can see what
instructions are emitted for each line of code. For x86_64, I have verified that
the generated assembly only contains the scaled and integer casted form of the
filter coefficients that are passed to constructor. No floating point
instructions or floating point variables exist in the final object file.

