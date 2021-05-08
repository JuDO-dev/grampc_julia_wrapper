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

#ifndef _GRAMPCJL_ERROR_HANDLING_H_
#define _GRAMPCJL_ERROR_HANDLING_H_

/*
 * Julia-specific error handling functions.
 */

/**
 * Get the last error message.
 *
 * Returns 0 if no error, 1 if a warning, and 2 if an error.
 */
int grampcjl_get_last_error( char* message );

/**
 * Clear the error fields in the library.
 *
 */
void grampcjl_clear_last_error();


/*
 * GRAMPC-internal error handling functions.
 *
 * We need to override these so that we can store the error as appropriate.
 */
void printError( const char* x );
void printErrorAddString( const char* mess, const char* addstring );
void printWarningAddString( const char* mess, const char* addstring );

// Keep this the same definition as the normal grampc code
#define myPrint( x, y ) printf( (x), (y) )


#endif // _GRAMPCJL_ERROR_HANDLING_H_
