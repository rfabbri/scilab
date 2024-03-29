/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2004-2006 - INRIA - Fabrice Leray
 * Copyright (C) 2006 - INRIA - Allan Cornet
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
 * Copyright (C) 2009 - DIGITEO - Pierre Lando
 * Copyright (C) 2010 - DIGITEO - Manuel Juliachs
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

/*------------------------------------------------------------------------*/
/* file: set_axes_size_property.c                                         */
/* desc : function to modify in Scilab the axes_size field of             */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "Scierror.h"
#include "sciprint.h"
#include "localization.h"
#include "SetPropertyStatus.h"
#include "Interaction.h"

#include "setGraphicObjectProperty.h"
#include "graphicObjectProperties.h"

/*------------------------------------------------------------------------*/
int set_axes_size_property(void* _pvCtx, char* pobjUID, void* _pvData, int valueType, int nbRow, int nbCol)
{
    double* newWindowSize = (double*)_pvData;
    BOOL status = FALSE;
    int intValues[2];

    if (valueType != sci_matrix)
    {
        Scierror(999, _("Wrong type for '%s' property: Real matrix expected.\n"), "axes_size");
        return SET_PROPERTY_ERROR;
    }

    intValues[0] = (int) newWindowSize[0];
    intValues[1] = (int) newWindowSize[1];

    status = setGraphicObjectProperty(pobjUID, __GO_AXES_SIZE__, intValues, jni_int_vector, 2);

    if (status == TRUE)
    {
        return SET_PROPERTY_SUCCEED;
    }
    else
    {
        Scierror(999, _("'%s' property does not exist for this handle.\n"), "axes_size");
        return SET_PROPERTY_ERROR;
    }
}
/*------------------------------------------------------------------------*/
