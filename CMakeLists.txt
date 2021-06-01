#
# This file is part of the Julia interface to the GRAMPC solver.
#
# Copyright (c) 2021 Ian McInerney <ian.s.mcinerney at iee.org>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# We need to define our own build system because we want to also export the GRAMPC
# functions in the shared library, and so we can't just link against the static library
# the included Makefile builds.

cmake_minimum_required( VERSION 3.13 )

project( Julia_GRAMPC )

########################################################################
# Get the flags needed to link against libjulia
########################################################################
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules )
find_package(Julia REQUIRED)


########################################################################
# Setup the shared library for building
########################################################################
set( GRAMPC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src_GRAMPC)

# All the GRAMPC sources (list taken from the GRAMPC makefile)
set( SOURCES
     ${GRAMPC_PATH}/src/euler1.c
     ${GRAMPC_PATH}/src/eulermod2.c
     ${GRAMPC_PATH}/src/heun2.c
     ${GRAMPC_PATH}/src/ruku45.c
     ${GRAMPC_PATH}/src/rodas.c
     ${GRAMPC_PATH}/src/trapezodial.c
     ${GRAMPC_PATH}/src/simpson.c
     ${GRAMPC_PATH}/src/grampc_alloc.c
     ${GRAMPC_PATH}/src/grampc_fixedsize.c
     ${GRAMPC_PATH}/src/grampc_init.c
     ${GRAMPC_PATH}/src/grampc_mess.c
     ${GRAMPC_PATH}/src/grampc_run.c
     ${GRAMPC_PATH}/src/grampc_setopt.c
     ${GRAMPC_PATH}/src/grampc_setparam.c
     ${GRAMPC_PATH}/src/grampc_util.c
    )

add_library( grampc_julia SHARED
             ${CMAKE_CURRENT_SOURCE_DIR}/src_wrapper/grampcjl_error_handling.c
             ${CMAKE_CURRENT_SOURCE_DIR}/src_wrapper/grampcjl_problem_functions.c
             ${CMAKE_CURRENT_SOURCE_DIR}/src_wrapper/grampcjl_wrapper.c
             ${SOURCES}
            )

set_property( TARGET grampc_julia PROPERTY C_STANDARD 99 )

target_include_directories( grampc_julia PRIVATE
                            ${CMAKE_CURRENT_SOURCE_DIR}/inc_wrapper
                            ${GRAMPC_PATH}/include
                            ${Julia_INCLUDE_DIRS}
                           )

target_link_libraries( grampc_julia
                       ${Julia_LIBRARY}
                      )

include( GNUInstallDirs )

install( TARGETS grampc_julia )
