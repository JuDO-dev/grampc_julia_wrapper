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

#include "grampcjl_problem_functions.h"
#include "grampcjl_wrapper.h"

/** OCP dimensions: states (Nx), controls (Nu), parameters (Np), equalities (Ng),
    inequalities (Nh), terminal equalities (NgT), terminal inequalities (NhT) **/
void ocp_dim( typeInt *Nx, typeInt *Nu, typeInt *Np, typeInt *Ng, typeInt *Nh, typeInt *NgT, typeInt *NhT, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->ocp_dim( Nx, Nu, Np, Ng, Nh, NgT, NhT, wrapper->user_param );
}


/** System function f(t,x,u,p,userparam )
    ------------------------------------ **/
void ffct( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->ffct( out, t, x, u, p, wrapper->user_param );
}


/** Jacobian df/dx multiplied by vector vec, i.e. (df/dx)^T*vec or vec^T*(df/dx) **/
void dfdx_vec( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *vec, ctypeRNum *u, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dfdx_vec( out, t, x, vec, u, p, wrapper->user_param );
}


/** Jacobian df/du multiplied by vector vec, i.e. (df/du)^T*vec or vec^T*(df/du) **/
void dfdu_vec( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *vec, ctypeRNum *u, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dfdu_vec( out, t, x, vec, u, p, wrapper->user_param );
}


/** Jacobian df/dp multiplied by vector vec, i.e. (df/dp)^T*vec or vec^T*(df/dp) **/
void dfdp_vec( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *vec, ctypeRNum *u, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dfdp_vec( out, t, x, vec, u, p, wrapper->user_param );
}


/** Integral cost l(t,x(t),u(t),p,xdes,udes,userparam )
    -------------------------------------------------- **/
void lfct( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *xdes, ctypeRNum *udes, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->lfct( out, t, x, u, p, xdes, udes, wrapper->user_param );
}


/** Gradient dl/dx **/
void dldx( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *xdes, ctypeRNum *udes, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dldx( out, t, x, u, p, xdes, udes, wrapper->user_param );
}


/** Gradient dl/du **/
void dldu( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *xdes, ctypeRNum *udes, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dldu( out, t, x, u, p, xdes, udes, wrapper->user_param );
}


/** Gradient dl/dp **/
void dldp( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *xdes, ctypeRNum *udes, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dldp( out, t, x, u, p, xdes, udes, wrapper->user_param );
}


/** Terminal cost V(T,x(T),p,xdes,userparam )
    ---------------------------------------- **/
void Vfct( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *xdes, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->Vfct( out, T, x, p, xdes, wrapper->user_param );
}


/** Gradient dV/dx **/
void dVdx( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *xdes, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dVdx( out, T, x, p, xdes, wrapper->user_param );
}


/** Gradient dV/dp **/
void dVdp( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *xdes, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dVdp( out, T, x, p, xdes, wrapper->user_param );
}


/** Gradient dV/dT **/
void dVdT( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *xdes, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dVdT( out, T, x, p, xdes, wrapper->user_param );
}


/** Equality constraints g(t,x(t),u(t),p,userparam ) = 0
    --------------------------------------------------- **/
void gfct( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->gfct( out, t, x, u, p, wrapper->user_param );
}


/** Jacobian dg/dx multiplied by vector vec, i.e. (dg/dx)^T*vec or vec^T*(dg/dx) **/
void dgdx_vec( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dgdx_vec( out, t, x, u, p, vec, wrapper->user_param );
}


/** Jacobian dg/du multiplied by vector vec, i.e. (dg/du)^T*vec or vec^T*(dg/du) **/
void dgdu_vec( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dgdu_vec( out, t, x, u, p, vec, wrapper->user_param );
}


/** Jacobian dg/dp multiplied by vector vec, i.e. (dg/dp)^T*vec or vec^T*(dg/dp) **/
void dgdp_vec( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dgdp_vec( out, t, x, u, p, vec, wrapper->user_param );
}


/** Inequality constraints h(t,x(t),u(t),p,userparam ) <= 0
    ------------------------------------------------------ **/
void hfct( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->hfct( out, t, x, u, p, wrapper->user_param );
}


/** Jacobian dh/dx multiplied by vector vec, i.e. (dh/dx)^T*vec or vec^T*(dg/dx) **/
void dhdx_vec( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dhdx_vec( out, t, x, u, p, vec, wrapper->user_param );
}


/** Jacobian dh/du multiplied by vector vec, i.e. (dh/du)^T*vec or vec^T*(dg/du) **/
void dhdu_vec( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dhdu_vec( out, t, x, u, p, vec, wrapper->user_param );
}


/** Jacobian dh/dp multiplied by vector vec, i.e. (dh/dp)^T*vec or vec^T*(dg/dp) **/
void dhdp_vec( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dhdp_vec( out, t, x, u, p, vec, wrapper->user_param );
}


/** Terminal equality constraints gT(T,x(T),p,userparam ) = 0
    -------------------------------------------------------- **/
void gTfct( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->gTfct( out, T, x, p, wrapper->user_param );
}


/** Jacobian dgT/dx multiplied by vector vec, i.e. (dgT/dx)^T*vec or vec^T*(dgT/dx) **/
void dgTdx_vec( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dgTdx_vec( out, T, x, p, vec, wrapper->user_param );
}


/** Jacobian dgT/dp multiplied by vector vec, i.e. (dgT/dp)^T*vec or vec^T*(dgT/dp) **/
void dgTdp_vec( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dgTdp_vec( out, T, x, p, vec, wrapper->user_param );
}


/** Jacobian dgT/dT multiplied by vector vec, i.e. (dgT/dT)^T*vec or vec^T*(dgT/dT) **/
void dgTdT_vec( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dgTdT_vec( out, T, x, p, vec, wrapper->user_param );
}


/** Terminal inequality constraints hT(T,x(T),p,userparam ) <= 0
    ----------------------------------------------------------- **/
void hTfct( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->hTfct( out, T, x, p, wrapper->user_param );
}


/** Jacobian dhT/dx multiplied by vector vec, i.e. (dhT/dx)^T*vec or vec^T*(dhT/dx) **/
void dhTdx_vec( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dhTdx_vec( out, T, x, p, vec, wrapper->user_param );
}


/** Jacobian dhT/dp multiplied by vector vec, i.e. (dhT/dp)^T*vec or vec^T*(dhT/dp) **/
void dhTdp_vec( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dhTdp_vec( out, T, x, p, vec, wrapper->user_param );
}


/** Jacobian dhT/dT multiplied by vector vec, i.e. (dhT/dT)^T*vec or vec^T*(dhT/dT) **/
void dhTdT_vec( typeRNum *out, ctypeRNum T, ctypeRNum *x, ctypeRNum *p, ctypeRNum *vec, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dhTdT_vec( out, T, x, p, vec, wrapper->user_param );
}


/** Additional functions required for semi-implicit systems
    M*dx/dt(t) = f(t0+t,x(t),u(t),p) using the solver RODAS,
    see GRAMPC docu for more information
    ------------------------------------------------------- **/
/** Jacobian df/dx in vector form (column-wise) **/
void dfdx( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dfdx( out, t, x, u, p, wrapper->user_param );
}


/** Jacobian df/dx in vector form (column-wise) **/
void dfdxtrans( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dfdxtrans( out, t, x, u, p, wrapper->user_param );
}


/** Jacobian df/dt **/
void dfdt( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dfdt( out, t, x, u, p, wrapper->user_param );
}


/** Jacobian d(dH/dx)/dt  **/
void dHdxdt( typeRNum *out, ctypeRNum t, ctypeRNum *x, ctypeRNum *u, ctypeRNum *vec, ctypeRNum *p, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->dHdxdt( out, t, x, u, vec, p, wrapper->user_param );
}


/** Mass matrix in vector form (column-wise, either banded or full matrix) **/
void Mfct( typeRNum *out, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->Mfct( out, wrapper->user_param );
}


/** Transposed mass matrix in vector form (column-wise, either banded or full matrix) **/
void Mtrans( typeRNum *out, typeUSERPARAM *userparam )
{
    grampcjl_wrapper* wrapper = ( grampcjl_wrapper* ) userparam;
    wrapper->funcs->Mtrans( out, wrapper->user_param );
}
