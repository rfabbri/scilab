/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Vincent COUVERT
 * Copyright (C) 2011-2012 - DIGITEO - Vincent COUVERT
 * Get the max property of an uicontrol
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

#include "GetUicontrolMin.hxx"

int GetUicontrolMin(void* _pvCtx, char *sciObjUID)
{
    double minValue = 0;
    double* pdblMinValue = &minValue;

    getGraphicObjectProperty(sciObjUID, __GO_UI_MIN__, jni_double, (void**) &pdblMinValue);

    if (pdblMinValue == NULL)
    {
        Scierror(999, const_cast<char*>(_("'%s' property does not exist for this handle.\n")), "Min");
        return FALSE;
    }
    else
    {
        return sciReturnDouble(_pvCtx, minValue);
    }
}
