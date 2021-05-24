/*
 * This file is part of the Julia interface to the GRAMPC solver.
 *
 * Copyright (c) 2021 Ian McInerney <ian.s.mcinerney at iee.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef GRAMPCJL_WRAPPER_H_
#define GRAMPCJL_WRAPPER_H_

#include <grampc.h>
#include <julia.h>

#include <grampcjl_problem_functions.h>

/**
 * Struct to wrap the user parmaeters with the wrapper function pointers.
 */
typedef struct
{
    grampcjl_callbacks* funcs;
    typeUSERPARAM*       user_param;
} grampcjl_wrapper;

void grampcjl_init( typeGRAMPC** grampc, grampcjl_callbacks* callbacks, jl_value_t* jlModel );

void grampcjl_free( typeGRAMPC* grampc );

#endif // GRAMPCJL_WRAPPER_H_
