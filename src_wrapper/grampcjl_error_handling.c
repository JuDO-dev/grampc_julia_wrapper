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

#include "grampcjl_error_handling.h"

#include "julia.h"

#include "stdio.h"
#include "string.h"

// Static variables to hold the last error information
// We really should never have very long messages, so just make the buffer very long
// to not have any that are cutoff.
static int  last_err_type = 0;
static char last_err_msg[1024];

void grampcjl_clear_last_error()
{
    last_err_type   = 0;
    last_err_msg[0] = 0;
}


int grampcjl_get_last_error( char* message )
{
    int retVal = last_err_type;
    strcpy( message, last_err_msg );

    // Zero out the last error
    grampcjl_clear_last_error();

    return retVal;
}


void printError( const char* x )
{
    strcpy( last_err_msg, x );

    // Say it was an error
    last_err_type = 2;

    jl_error( x );
}


void printErrorAddString( const char* mess, const char* addstring )
{
    sprintf( last_err_msg, "%s: %s", mess, addstring );

    // Say it was an error
    last_err_type = 2;

    jl_error( last_err_msg );
}


void printWarningAddString( const char* mess, const char* addstring )
{
    sprintf( last_err_msg, "%s: %s", mess, addstring );

    // Say it was a warning
    last_err_type = 1;
}
