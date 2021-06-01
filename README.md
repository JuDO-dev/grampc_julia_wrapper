# GRAMPC Wrapper for Julia

This repository contains the source code for the C part of the Julia wrapper of the [GRAMPC](https://sourceforge.net/projects/grampc/) optimal control library.
This is meant to be built using the BinaryBuilder platform and be included in the [Yggdrasil](https://github.com/JuliaPackaging/Yggdrasil) repository for adding to the general registry as a `jll` package.


# Contents

## CMakeModules

This directory contains the various files needed for CMake to properly build the library.
The `FindJulia.cmake` file was taken from the [libcxxwrap-julia](https://github.com/JuliaInterop/libcxxwrap-julia/blob/master/FindJulia.cmake) package.
This file has been modified slightly to fix an issue with include directories that was noticed on Yggdrasil.


## src_GRAMPC

This directory contains the upstream GRAMPC source code (extracted from their release tarball).
The library source code has had several changes to it to support the Julia interface, including:
* Removal of inline arrays from structs and instead using a malloc'd pointer
* Replacement of the error handling defines with inline functions to throw Julia exceptions


## inc_wrapper

This directory contains the include files for the Julia-specific parts of the wrapper library.
These header files contain the structs that hold the function pointers used by the trampoline functions, as well as the main wrapper that is passed as the user parameter.


## src_wrapper

This directory contains the source files for the Julia-specific parts of the wrapper library.
It includes three major parts:
* Error handling routines to track the warnings thrown by the code
* Function trampolines to redirect calls to the problem functions to the Julia callbacks
* Initialization code to create the needed wrapper structs for the callbacks
