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
#include "XMLList.hxx"

extern "C"
{
#include "gw_xml.h"
#include "stack-c.h"
#include "Scierror.h"
#include "api_scilab.h"
#include "xml_mlist.h"
#include "localization.h"
}

using namespace org_modules_xml;

/*--------------------------------------------------------------------------*/
int sci_percent_XMLList_size(char * fname, unsigned long fname_len)
{
    int id;
    SciErr err;
    double d[2] = {1, 0};
    int * addr = 0;
    XMLList * list;

    CheckLhs(1, 1);
    CheckRhs(1, 1);

    err = getVarAddressFromPosition(pvApiCtx, 1, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        return 0;
    }

    if (!isXMLList(addr, pvApiCtx) && !isXMLSet(addr, pvApiCtx))
    {
        Scierror(999, gettext("%s: Wrong type for input argument #%i: XMLList or XMLSet expected.\n"), fname, 1);
        return 0;

    }

    id = getXMLObjectId(addr, pvApiCtx);
    list = XMLObject::getFromId<XMLList>(id);
    if (!list)
    {
        Scierror(999, gettext("%s: XMLList does not exist.\n"), fname);
        return 0;
    }

    d[1] = (double)list->getSize();
    err = createMatrixOfDouble(pvApiCtx, Rhs + 1, 1, 2, d);
    if (err.iErr)
    {
        printError(&err, 0);
        return 0;
    }

    LhsVar(1) = Rhs + 1;
    PutLhsVar();
    return 0;
}
/*--------------------------------------------------------------------------*/