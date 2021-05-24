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

#include <grampcjl_wrapper.h>

#include <stdlib.h>

void grampcjl_init( typeGRAMPC** grampc, grampcjl_callbacks* callbacks, jl_value_t* jlModel )
{
    grampcjl_wrapper* wrap = malloc( sizeof( grampcjl_wrapper ) );

    if( wrap == NULL )
        jl_error( "Error creating internal wrapper structure" );

    wrap->funcs = callbacks;
    wrap->user_param = ( typeUSERPARAM* ) jlModel;

    grampc_init( grampc, ( typeUSERPARAM* ) wrap );
}


void grampcjl_free( typeGRAMPC* grampc )
{
    if( grampc )
        free( grampc->userparam );

    // The free function wants a double pointer but Julia only gives us a single pointer,
    // so use this local variable as a temp for the library to work with and then just
    // update Julia's pointer.
    typeGRAMPC* tempGrampc = grampc;

    grampc_free( &tempGrampc );

    grampc = tempGrampc;
}
