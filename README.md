# GRAMPC Wrapper for Julia

This repository contains the source code for the C part of the Julia wrapper of the [GRAMPC](https://sourceforge.net/projects/grampc/) optimal control library.
This is meant to be built using the BinaryBuilder platform and be included in the [Yggdrasil] (https://github.com/JuliaPackaging/Yggdrasil) repository.


# Contents

## CMakeModules

This directory contains the various files needed for CMake to properly build the library.
The `FindJulia.cmake` file was taken from the [libcxxwrap-julia](https://github.com/JuliaInterop/libcxxwrap-julia/blob/master/FindJulia.cmake) package.
This file has been modified slightly to fix an issue with include directories that was noticed on Yggdrasil.

## inc_wrapper


## src_GRAMPC

This directory contains the upstream GRAMPC source code (extracted from their release tarball).


## src_wrapper
