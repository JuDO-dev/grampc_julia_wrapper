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

#ifndef GRAMPCJL_ERROR_HANDLING_H_
#define GRAMPCJL_ERROR_HANDLING_H_

#include <julia.h>

/*
 * Julia-specific error handling functions.
 */

/**
 * Get the last warning message.
 *
 * Returns 0 if no warning, 1 if a warning.
 */
int grampcjl_get_last_warning( char* message );

/**
 * Clear the last warning in the library.
 *
 */
void grampcjl_clear_last_warning();

/*
 * GRAMPC-internal error handling functions.
 *
 * We need to override these so that we can throw the error to the Julia REPL
 */
inline void printError( const char* x )
{
    // Throw a Julia ErrorException with the provided message
    jl_error( x );
}

inline void printErrorAddString( const char* mess, const char* addstring )
{
    // Throw a Julia ErrorException with the provided message
    jl_errorf( "%s: %s", mess, addstring );
}


void printWarningAddString( const char* mess, const char* addstring );

// Keep this the same definition as the normal grampc code
#define myPrint( x, y ) printf( (x), (y) )


#endif // GRAMPCJL_ERROR_HANDLING_H_
