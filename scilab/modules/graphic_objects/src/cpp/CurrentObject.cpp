/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2011-2011 - DIGITEO - Bruno JOFRET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

#include "ScilabView.hxx"

extern "C"
{
#include <string.h>

#include "BOOL.h"
#include "CurrentObject.h"
}


char const* getCurrentObject(void)
{
    return ScilabView::getCurrentObject();
}

void setCurrentObject(char const* UID)
{
    ScilabView::setCurrentObject(UID);
}

BOOL isCurrentObject(char const* UID)
{
    if (strcmp(UID, ScilabView::getCurrentObject()) == 0)
    {
        return TRUE;
    }
    return FALSE;
}
