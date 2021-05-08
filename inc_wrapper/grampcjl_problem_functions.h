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

#ifndef GRAMPCJL_PROBLEM_FUNCTIONS_H_
#define GRAMPCJL_PROBLEM_FUNCTIONS_H_

#include "grampc.h"

/// Function pointer for the OCP dimension retrieval function
typedef void( *ocp_dim_func )( typeInt*, typeInt*, typeInt*, typeInt*, typeInt*, typeInt*, typeInt*,
                               typeUSERPARAM* );


/// Function pointer type for the system evaluation functions
typedef void( *sys_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*, typeUSERPARAM* );


///
typedef void( *sys_vec_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*, ctypeRNum*,
                               typeUSERPARAM* );


/// Function pointer type for all the cost L term functions
typedef void( *l_cost_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*, ctypeRNum*,
                              ctypeRNum*, typeUSERPARAM* );


/// Function pointer type for all the terminal cost functions
typedef void( *term_cost_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*,
                                 typeUSERPARAM* );


/// Function pointer type for the stage equality/inequality constraint evaluation function
typedef void( *stage_con_eval_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*,
                                      typeUSERPARAM* );


/// Function pointer type for the stage equality/inequality constraint Jacobian evaluation function
typedef void( *stage_con_vec_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*,
                                     ctypeRNum*, typeUSERPARAM* );


/// Function pointer type for the terminal equality/inequality constraint evaluation function
typedef void( *term_con_eval_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, typeUSERPARAM* );


/// Function pointer type for the terminal equality/inequality constraint Jacobian evaluation function
typedef void( *term_con_vec_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*,
                                    typeUSERPARAM* );

/*
 * Additional functions required for semi-implicit systems
 */
/// Function pointer for the Jacobian df/dx in vector form (column-wise)
typedef void( *dfdx_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*, typeUSERPARAM* );


/// Function pointer for the Jacobian df/dx in vector form (column-wise)
typedef void( *dfdxtrans_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*,
                                 typeUSERPARAM* );


/// Function pointer for the Jacobian df/dt
typedef void( *dfdt_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*,
                            typeUSERPARAM* );


/// Function pointer for the Jacobian d(dH/dx)/dt
typedef void( *dHdxdt_func )( typeRNum*, ctypeRNum, ctypeRNum*, ctypeRNum*, ctypeRNum*, ctypeRNum*,
                              typeUSERPARAM* );


/// Function pointer for the mass matrix in vector form (column-wise, either banded or full matrix)
typedef void( *Mfct_func )( typeRNum*, typeUSERPARAM* );


/// Function pointer for the transposed mass matrix in vector form (column-wise, either banded or full matrix)
typedef void( *Mtrans_func )(typeRNum*, typeUSERPARAM* );


/**
 * Struct to hold function pointers to the Julia functions implementing the optimal control problem.
 */
typedef struct
{
    ocp_dim_func        ocp_dim;

    sys_func            ffct;
    sys_vec_func        dfdx_vec;
    sys_vec_func        dfdu_vec;
    sys_vec_func        dfdp_vec;

    l_cost_func         lfct;
    l_cost_func         dldx;
    l_cost_func         dldu;
    l_cost_func         dldp;

    term_cost_func      Vfct;
    term_cost_func      dVdx;
    term_cost_func      dVdp;
    term_cost_func      dVdT;

    stage_con_eval_func gfct;
    stage_con_vec_func  dgdx_vec;
    stage_con_vec_func  dgdu_vec;
    stage_con_vec_func  dgdp_vec;

    stage_con_eval_func hfct;
    stage_con_vec_func  dhdx_vec;
    stage_con_vec_func  dhdu_vec;
    stage_con_vec_func  dhdp_vec;

    term_con_eval_func  gTfct;
    term_con_vec_func   dgTdx_vec;
    term_con_vec_func   dgTdp_vec;
    term_con_vec_func   dgTdT_vec;

    term_con_eval_func  hTfct;
    term_con_vec_func   dhTdx_vec;
    term_con_vec_func   dhTdp_vec;
    term_con_vec_func   dhTdT_vec;

    dfdx_func           dfdx;
    dfdxtrans_func      dfdxtrans;
    dfdt_func           dfdt;
    dHdxdt_func         dHdxdt;
    Mfct_func           Mfct;
    Mtrans_func         Mtrans;
} julia_funcs_wrapper;


/**
 * Struct to wrap the user parmaeters with the wrapper function pointers.
 */
typedef struct
{
    julia_funcs_wrapper funcs;
    typeUSERPARAM*      user_param;
} julia_user_wrapper;


#endif //  GRAMPCJL_PROBLEM_FUNCTIONS_H_
