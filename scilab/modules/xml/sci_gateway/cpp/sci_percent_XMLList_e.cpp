/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Calixte DENIZET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#include "XMLObject.hxx"
#include "XMLNodeList.hxx"

extern "C"
{
#include <stdio.h>
#include "gw_xml.h"
#include "stack-c.h"
#include "Scierror.h"
#include "api_scilab.h"
#include "xml_mlist.h"
#include "localization.h"
}

using namespace org_modules_xml;

int sci_percent_XMLList_e(char * fname, unsigned long fname_len)
{
    XMLList * list = 0;
    const XMLObject * elem;
    int id;
    SciErr err;
    double * dvalue = 0;
    int * mlistaddr = 0;
    int * daddr = 0;
    int typ = 0;
    int row;
    int col;
    int index;
    double d;
    char * field = 0;

    CheckLhs(1, 1);
    CheckRhs(2, 2);

    err = getVarAddressFromPosition(pvApiCtx, 1, &daddr);
    if (err.iErr)
    {
        printError(&err, 0);
        return 0;
    }

    err = getVarDimension(pvApiCtx, daddr, &row, &col);
    if (err.iErr)
    {
        printError(&err, 0);
        return 0;
    }

    err = getVarType(pvApiCtx, daddr, &typ);
    if (err.iErr)
    {
        printError(&err, 0);
        return 0;
    }

    if (typ == sci_strings)
    {
        if (row != 1 || col != 1)
        {
            Scierror(999, gettext("%s: Wrong dimension for input argument #%i: A string or a double expected.\n"), fname, 1);
            return 0;
        }

        getAllocatedSingleString(pvApiCtx, daddr, &field);
        if (!strcmp(field, "size"))
        {
            err = getVarAddressFromPosition(pvApiCtx, 2, &mlistaddr);
            if (err.iErr)
            {
                freeAllocatedSingleString(field);
                printError(&err, 0);
                return 0;
            }

            id = getXMLObjectId(mlistaddr, pvApiCtx);
            list = XMLObject::getFromId<XMLList>(id);
            if (!list)
            {
                freeAllocatedSingleString(field);
                Scierror(999, gettext("%s: XML object does not exist.\n"), fname);
                return 0;
            }

            d = (double)list->getSize();
            createScalarDouble(pvApiCtx, Rhs + 1, d);

            LhsVar(1) = Rhs + 1;
            PutLhsVar();
        }
        else
        {
            Scierror(999, gettext("%s: Unknown field: %s\n"), fname, field);
        }
        freeAllocatedSingleString(field);

        return 0;
    }

    if (row != 1 || col != 1 || typ != sci_matrix)
    {
        Scierror(999, gettext("%s: Wrong dimension for input argument #%i: Single double expected.\n"), fname, 1);
        return 0;
    }

    if (isVarComplex(pvApiCtx, daddr))
    {
        Scierror(999, gettext("%s: Wrong type for input argument #%i: Double expected.\n"), fname, 1);
        return 0;
    }

    err = getMatrixOfDouble(pvApiCtx, daddr, &row, &col, &dvalue);
    if (err.iErr)
    {
        printError(&err, 0);
        return 0;
    }

    err = getVarAddressFromPosition(pvApiCtx, 2, &mlistaddr);
    if (err.iErr)
    {
        printError(&err, 0);
        return 0;
    }

    id = getXMLObjectId(mlistaddr, pvApiCtx);
    list = XMLObject::getFromId<XMLList>(id);
    if (!list)
    {
        Scierror(999, gettext("%s: XML object does not exist.\n"), fname);
        return 0;
    }

    index = (int)(*dvalue);
    elem = list->getListElement(index);
    if (!elem)
    {
        Scierror(999, gettext("%s: Wrong index in the XMLList.\n"), fname);
        return 0;
    }

    if (!elem->createOnStack(Rhs + 1, pvApiCtx))
    {
        return 0;
    }

    LhsVar(1) = Rhs + 1;
    PutLhsVar();

    return 0;
}