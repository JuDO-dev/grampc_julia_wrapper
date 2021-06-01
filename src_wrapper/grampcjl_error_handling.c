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

#include "stdio.h"
#include "string.h"

// Declarations for C99 function inlining
extern inline void printError( const char* x );
extern inline void printErrorAddString( const char* mess, const char* addstring );

// Static variables to hold the last warning information
// We really should never have very long messages, so just make the buffer very long
// to not have any that are cutoff.
static int  last_warn_type = 0;
static char last_warn_msg[1024];


void grampcjl_clear_last_warning()
{
    last_warn_type   = 0;
    last_warn_msg[0] = 0;
}


int grampcjl_get_last_warning( char* message )
{
    int retVal = last_warn_type;
    strcpy( message, last_warn_msg );

    // Zero out the last warning after reasing
    grampcjl_clear_last_warning();

    return retVal;
}


void printWarningAddString( const char* mess, const char* addstring )
{
    sprintf( last_warn_msg, "%s: %s", mess, addstring );

    // Say there was a warning
    last_warn_type = 1;
}
