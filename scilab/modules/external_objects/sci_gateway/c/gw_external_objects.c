/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Calixte DENIZET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */
/*--------------------------------------------------------------------------*/
#include "gw_external_objects.h"
#include "api_scilab.h"
#include "callFunctionFromGateway.h"
#include "MALLOC.h"
/*--------------------------------------------------------------------------*/
/*  interface function */
/*--------------------------------------------------------------------------*/
static gw_generic_table Tab[] =
{
    {sci_percent_EObj_e, "%_EObj_e"},
    {sci_percent_EObj_e, "%_EObj_6"},
    {sci_percent_EClass_e, "%_EClass_6"},
    {sci_percent_EObj_p, "%_EObj_p"},
    {sci_percent_EClass_e, "%_EClass_e"},
    {sci_percent_EObj_p, "%_EClass_p"},
    {sci_percent_foo_i_EObj, "%c_i__EObj"},
    {sci_percent_foo_i_EObj, "%s_i__EObj"},
    {sci_percent_foo_i_EObj, "%b_i__EObj"},
    {sci_percent_foo_i_EObj, "%i_i__EObj"},
    {sci_percent_EObj_a_foo, "%_EObj_a_c"},
    {sci_percent_EObj_a_foo, "%_EObj_a_s"},
    {sci_percent_EObj_a_foo, "%_EObj_a_b"},
    {sci_percent_EObj_a_foo, "%_EObj_a_i"},
    {sci_percent_EObj_a_foo, "%_EObj_a__EObj"},
    {sci_percent_EObj_a_foo, "%c_a__EObj"},
    {sci_percent_EObj_a_foo, "%s_a__EObj"},
    {sci_percent_EObj_a_foo, "%b_a__EObj"},
    {sci_percent_EObj_a_foo, "%i_a__EObj"},
    {sci_percent_EObj_d_foo, "%_EObj_d_c"},
    {sci_percent_EObj_d_foo, "%_EObj_d_s"},
    {sci_percent_EObj_d_foo, "%_EObj_d_b"},
    {sci_percent_EObj_d_foo, "%_EObj_d_i"},
    {sci_percent_EObj_d_foo, "%_EObj_d__EObj"},
    {sci_percent_EObj_d_foo, "%c_d__EObj"},
    {sci_percent_EObj_d_foo, "%s_d__EObj"},
    {sci_percent_EObj_d_foo, "%b_d__EObj"},
    {sci_percent_EObj_d_foo, "%i_d__EObj"},
    {sci_percent_EObj_g_foo, "%_EObj_g_c"},
    {sci_percent_EObj_g_foo, "%_EObj_g_s"},
    {sci_percent_EObj_g_foo, "%_EObj_g_b"},
    {sci_percent_EObj_g_foo, "%_EObj_g_i"},
    {sci_percent_EObj_g_foo, "%_EObj_g__EObj"},
    {sci_percent_EObj_g_foo, "%c_g__EObj"},
    {sci_percent_EObj_g_foo, "%s_g__EObj"},
    {sci_percent_EObj_g_foo, "%b_g__EObj"},
    {sci_percent_EObj_g_foo, "%i_g__EObj"},
    {sci_percent_EObj_h_foo, "%_EObj_h_c"},
    {sci_percent_EObj_h_foo, "%_EObj_h_s"},
    {sci_percent_EObj_h_foo, "%_EObj_h_b"},
    {sci_percent_EObj_h_foo, "%_EObj_h_i"},
    {sci_percent_EObj_h_foo, "%_EObj_h__EObj"},
    {sci_percent_EObj_h_foo, "%c_h__EObj"},
    {sci_percent_EObj_h_foo, "%s_h__EObj"},
    {sci_percent_EObj_h_foo, "%b_h__EObj"},
    {sci_percent_EObj_h_foo, "%i_h__EObj"},
    {sci_percent_EObj_j_foo, "%_EObj_j_c"},
    {sci_percent_EObj_j_foo, "%_EObj_j_s"},
    {sci_percent_EObj_j_foo, "%_EObj_j_b"},
    {sci_percent_EObj_j_foo, "%_EObj_j_i"},
    {sci_percent_EObj_j_foo, "%_EObj_j__EObj"},
    {sci_percent_EObj_j_foo, "%c_j__EObj"},
    {sci_percent_EObj_j_foo, "%s_j__EObj"},
    {sci_percent_EObj_j_foo, "%b_j__EObj"},
    {sci_percent_EObj_j_foo, "%i_j__EObj"},
    {sci_percent_EObj_k_foo, "%_EObj_k_c"},
    {sci_percent_EObj_k_foo, "%_EObj_k_s"},
    {sci_percent_EObj_k_foo, "%_EObj_k_b"},
    {sci_percent_EObj_k_foo, "%_EObj_k_i"},
    {sci_percent_EObj_k_foo, "%_EObj_k__EObj"},
    {sci_percent_EObj_k_foo, "%c_k__EObj"},
    {sci_percent_EObj_k_foo, "%s_k__EObj"},
    {sci_percent_EObj_k_foo, "%b_k__EObj"},
    {sci_percent_EObj_k_foo, "%i_k__EObj"},
    {sci_percent_EObj_l_foo, "%_EObj_l_c"},
    {sci_percent_EObj_l_foo, "%_EObj_l_s"},
    {sci_percent_EObj_l_foo, "%_EObj_l_b"},
    {sci_percent_EObj_l_foo, "%_EObj_l_i"},
    {sci_percent_EObj_l_foo, "%_EObj_l__EObj"},
    {sci_percent_EObj_l_foo, "%c_l__EObj"},
    {sci_percent_EObj_l_foo, "%s_l__EObj"},
    {sci_percent_EObj_l_foo, "%b_l__EObj"},
    {sci_percent_EObj_l_foo, "%i_l__EObj"},
    {sci_percent_EObj_m_foo, "%_EObj_m_c"},
    {sci_percent_EObj_m_foo, "%_EObj_m_s"},
    {sci_percent_EObj_m_foo, "%_EObj_m_b"},
    {sci_percent_EObj_m_foo, "%_EObj_m_i"},
    {sci_percent_EObj_m_foo, "%_EObj_m__EObj"},
    {sci_percent_EObj_m_foo, "%c_m__EObj"},
    {sci_percent_EObj_m_foo, "%s_m__EObj"},
    {sci_percent_EObj_m_foo, "%b_m__EObj"},
    {sci_percent_EObj_m_foo, "%i_m__EObj"},
    {sci_percent_EObj_n_foo, "%_EObj_n_c"},
    {sci_percent_EObj_n_foo, "%_EObj_n_s"},
    {sci_percent_EObj_n_foo, "%_EObj_n_b"},
    {sci_percent_EObj_n_foo, "%_EObj_n_i"},
    {sci_percent_EObj_n_foo, "%_EObj_n__EObj"},
    {sci_percent_EObj_n_foo, "%c_n__EObj"},
    {sci_percent_EObj_n_foo, "%s_n__EObj"},
    {sci_percent_EObj_n_foo, "%b_n__EObj"},
    {sci_percent_EObj_n_foo, "%i_n__EObj"},
    {sci_percent_EObj_o_foo, "%_EObj_o_c"},
    {sci_percent_EObj_o_foo, "%_EObj_o_s"},
    {sci_percent_EObj_o_foo, "%_EObj_o_b"},
    {sci_percent_EObj_o_foo, "%_EObj_o_i"},
    {sci_percent_EObj_o_foo, "%_EObj_o__EObj"},
    {sci_percent_EObj_o_foo, "%c_o__EObj"},
    {sci_percent_EObj_o_foo, "%s_o__EObj"},
    {sci_percent_EObj_o_foo, "%b_o__EObj"},
    {sci_percent_EObj_o_foo, "%i_o__EObj"},
    {sci_percent_EObj_p_foo, "%_EObj_p_c"},
    {sci_percent_EObj_p_foo, "%_EObj_p_s"},
    {sci_percent_EObj_p_foo, "%_EObj_p_b"},
    {sci_percent_EObj_p_foo, "%_EObj_p_i"},
    {sci_percent_EObj_p_foo, "%_EObj_p__EObj"},
    {sci_percent_EObj_p_foo, "%c_p__EObj"},
    {sci_percent_EObj_p_foo, "%s_p__EObj"},
    {sci_percent_EObj_p_foo, "%b_p__EObj"},
    {sci_percent_EObj_p_foo, "%i_p__EObj"},
    {sci_percent_EObj_q_foo, "%_EObj_q_c"},
    {sci_percent_EObj_q_foo, "%_EObj_q_s"},
    {sci_percent_EObj_q_foo, "%_EObj_q_b"},
    {sci_percent_EObj_q_foo, "%_EObj_q_i"},
    {sci_percent_EObj_q_foo, "%_EObj_q__EObj"},
    {sci_percent_EObj_q_foo, "%c_q__EObj"},
    {sci_percent_EObj_q_foo, "%s_q__EObj"},
    {sci_percent_EObj_q_foo, "%b_q__EObj"},
    {sci_percent_EObj_q_foo, "%i_q__EObj"},
    {sci_percent_EObj_r_foo, "%_EObj_r_c"},
    {sci_percent_EObj_r_foo, "%_EObj_r_s"},
    {sci_percent_EObj_r_foo, "%_EObj_r_b"},
    {sci_percent_EObj_r_foo, "%_EObj_r_i"},
    {sci_percent_EObj_r_foo, "%_EObj_r__EObj"},
    {sci_percent_EObj_r_foo, "%c_r__EObj"},
    {sci_percent_EObj_r_foo, "%s_r__EObj"},
    {sci_percent_EObj_r_foo, "%b_r__EObj"},
    {sci_percent_EObj_r_foo, "%i_r__EObj"},
    {sci_percent_EObj_s_foo, "%_EObj_s_c"},
    {sci_percent_EObj_s_foo, "%_EObj_s_s"},
    {sci_percent_EObj_s_foo, "%_EObj_s_b"},
    {sci_percent_EObj_s_foo, "%_EObj_s_i"},
    {sci_percent_EObj_s_foo, "%_EObj_s__EObj"},
    {sci_percent_EObj_s_foo, "%c_s__EObj"},
    {sci_percent_EObj_s_foo, "%s_s__EObj"},
    {sci_percent_EObj_s_foo, "%b_s__EObj"},
    {sci_percent_EObj_s_foo, "%i_s__EObj"},
    {sci_percent_EObj_x_foo, "%_EObj_x_c"},
    {sci_percent_EObj_x_foo, "%_EObj_x_s"},
    {sci_percent_EObj_x_foo, "%_EObj_x_b"},
    {sci_percent_EObj_x_foo, "%_EObj_x_i"},
    {sci_percent_EObj_x_foo, "%_EObj_x__EObj"},
    {sci_percent_EObj_x_foo, "%c_x__EObj"},
    {sci_percent_EObj_x_foo, "%s_x__EObj"},
    {sci_percent_EObj_x_foo, "%b_x__EObj"},
    {sci_percent_EObj_x_foo, "%i_x__EObj"},
    {sci_percent_EObj_y_foo, "%_EObj_y_c"},
    {sci_percent_EObj_y_foo, "%_EObj_y_s"},
    {sci_percent_EObj_y_foo, "%_EObj_y_b"},
    {sci_percent_EObj_y_foo, "%_EObj_y_i"},
    {sci_percent_EObj_y_foo, "%_EObj_y__EObj"},
    {sci_percent_EObj_y_foo, "%c_y__EObj"},
    {sci_percent_EObj_y_foo, "%s_y__EObj"},
    {sci_percent_EObj_y_foo, "%b_y__EObj"},
    {sci_percent_EObj_y_foo, "%i_y__EObj"},
    {sci_percent_EObj_z_foo, "%_EObj_z_c"},
    {sci_percent_EObj_z_foo, "%_EObj_z_s"},
    {sci_percent_EObj_z_foo, "%_EObj_z_b"},
    {sci_percent_EObj_z_foo, "%_EObj_z_i"},
    {sci_percent_EObj_z_foo, "%_EObj_z__EObj"},
    {sci_percent_EObj_z_foo, "%c_z__EObj"},
    {sci_percent_EObj_z_foo, "%s_z__EObj"},
    {sci_percent_EObj_z_foo, "%b_z__EObj"},
    {sci_percent_EObj_z_foo, "%i_z__EObj"},
    {sci_percent_EObj_1_foo, "%_EObj_1_c"},
    {sci_percent_EObj_1_foo, "%_EObj_1_s"},
    {sci_percent_EObj_1_foo, "%_EObj_1_b"},
    {sci_percent_EObj_1_foo, "%_EObj_1_i"},
    {sci_percent_EObj_1_foo, "%_EObj_1__EObj"},
    {sci_percent_EObj_1_foo, "%c_1__EObj"},
    {sci_percent_EObj_1_foo, "%s_1__EObj"},
    {sci_percent_EObj_1_foo, "%b_1__EObj"},
    {sci_percent_EObj_1_foo, "%i_1__EObj"},
    {sci_percent_EObj_2_foo, "%_EObj_2_c"},
    {sci_percent_EObj_2_foo, "%_EObj_2_s"},
    {sci_percent_EObj_2_foo, "%_EObj_2_b"},
    {sci_percent_EObj_2_foo, "%_EObj_2_i"},
    {sci_percent_EObj_2_foo, "%_EObj_2__EObj"},
    {sci_percent_EObj_2_foo, "%c_2__EObj"},
    {sci_percent_EObj_2_foo, "%s_2__EObj"},
    {sci_percent_EObj_2_foo, "%b_2__EObj"},
    {sci_percent_EObj_2_foo, "%i_2__EObj"},
    {sci_percent_EObj_3_foo, "%_EObj_3_c"},
    {sci_percent_EObj_3_foo, "%_EObj_3_s"},
    {sci_percent_EObj_3_foo, "%_EObj_3_b"},
    {sci_percent_EObj_3_foo, "%_EObj_3_i"},
    {sci_percent_EObj_3_foo, "%_EObj_3__EObj"},
    {sci_percent_EObj_3_foo, "%c_3__EObj"},
    {sci_percent_EObj_3_foo, "%s_3__EObj"},
    {sci_percent_EObj_3_foo, "%b_3__EObj"},
    {sci_percent_EObj_3_foo, "%i_3__EObj"},
    {sci_percent_EObj_4_foo, "%_EObj_4_c"},
    {sci_percent_EObj_4_foo, "%_EObj_4_s"},
    {sci_percent_EObj_4_foo, "%_EObj_4_b"},
    {sci_percent_EObj_4_foo, "%_EObj_4_i"},
    {sci_percent_EObj_4_foo, "%_EObj_4__EObj"},
    {sci_percent_EObj_4_foo, "%c_4__EObj"},
    {sci_percent_EObj_4_foo, "%s_4__EObj"},
    {sci_percent_EObj_4_foo, "%b_4__EObj"},
    {sci_percent_EObj_4_foo, "%i_4__EObj"},
    {sci_percent_EObj_0, "%_EObj_0"},
    {sci_percent_EObj_5, "%_EObj_5"},
    {sci_percent_EObj_t, "%_EObj_t"},
    {sci_invoke_lu, "invoke_lu"},
    {sci_doubleExclam_invoke_, "!!_invoke_"},
    {sci_percent_EObj_disp, "%_EObj_disp"}
};

/*--------------------------------------------------------------------------*/
int gw_external_objects(void)
{
    Rhs = Max(0, Rhs);

    if (pvApiCtx == NULL)
    {
        pvApiCtx = (StrCtx *) MALLOC(sizeof(StrCtx));
    }

    pvApiCtx->pstName = (char *)Tab[Fin - 1].name;
    callFunctionFromGateway(Tab, SIZE_CURRENT_GENERIC_TABLE(Tab));
    return 0;
}

/*--------------------------------------------------------------------------*/
