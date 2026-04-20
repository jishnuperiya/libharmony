# harmony-lib

## Goals

Library for Symbolic Domain Modeling

## Project Layout

To get up and running quickly, and without knowing more about just what actual libraries and executables we will need, I have made some arbitrary choices, all of which can be changed later as needed:

- *harmony-lib*: a static link library that contains the bulk of the code we will write together.

- *harmony-test*: a doctest-based harness that links against *jishnu-lib*.

- *harmony*: an executable that links against _jishnu-lib_.

The test harnesses implements a rich command line interface, and is RapidCheck enabled.

## Prerequisites

### MacOS:

    sudo port -N install clang-20 cmake doxygen

## Building

    mkdir .bld
    cd .bld
    cmake ..
    make -j

Also:

    make help

to see a list of possible of build targets.

## Running

To run the _harmony_ test harness:

    ./harmony-test

To run the _harmony_ executable:

    ./harmony

# Contributors

- jishnuperiya@gmail.com
- jonathon.bell@gmail.com
