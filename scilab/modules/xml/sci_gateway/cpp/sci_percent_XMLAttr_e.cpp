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
#include "XMLElement.hxx"
#include "XMLNs.hxx"
#include "XMLAttr.hxx"

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

/*--------------------------------------------------------------------------*/
int sci_percent_XMLAttr_e(char * fname, unsigned long fname_len)
{
    XMLAttr * attr;
    int id;
    SciErr err;
    int * prefixaddr = 0;
    int * nameaddr = 0;
    int * mlistaddr = 0;
    char * name = 0;
    char * prefix = 0;
    const char * value;

    CheckLhs(1, 1);
    CheckRhs(2, 3);

    err = getVarAddressFromPosition(pvApiCtx, 1, &prefixaddr);
    if (err.iErr)
    {
        printError(&err, 0);
        return 0;
    }

    if (!isStringType(pvApiCtx, prefixaddr))
    {
        Scierror(999, gettext("%s: Wrong type for input argument #%i: A string expected.\n"), fname, 1);
        return 0;
    }

    getAllocatedSingleString(pvApiCtx, prefixaddr, &prefix);

    if (Rhs == 3)
    {
        err = getVarAddressFromPosition(pvApiCtx, 2, &nameaddr);
        if (err.iErr)
        {
            freeAllocatedSingleString(prefix);
            printError(&err, 0);
            return 0;
        }

        if (!isStringType(pvApiCtx, nameaddr))
        {
            freeAllocatedSingleString(prefix);
            Scierror(999, gettext("%s: Wrong type for input argument #%i: A string expected.\n"), fname, 1);
            return 0;
        }

        getAllocatedSingleString(pvApiCtx, nameaddr, &name);
    }

    err = getVarAddressFromPosition(pvApiCtx, Rhs, &mlistaddr);
    if (err.iErr)
    {
        freeAllocatedSingleString(prefix);
        if (name)
        {
            freeAllocatedSingleString(name);
        }
        printError(&err, 0);
        return 0;
    }

    id = getXMLObjectId(mlistaddr, pvApiCtx);
    attr = XMLObject::getFromId<XMLAttr>(id);

    if (!attr)
    {
        freeAllocatedSingleString(prefix);
        if (name)
        {
            freeAllocatedSingleString(name);
        }
        Scierror(999, gettext("%s: XML object does not exist.\n"), fname);
        return 0;
    }

    if (Rhs == 3)
    {
        value = attr->getAttributeValue(const_cast<const char *>(prefix), const_cast<const char *>(name));
    }
    else
    {
        value = attr->getAttributeValue(const_cast<const char *>(prefix));
    }

    freeAllocatedSingleString(prefix);
    if (name)
    {
        freeAllocatedSingleString(name);
    }

    if (!value)
    {
        err = createMatrixOfDouble(pvApiCtx, Rhs + 1, 0, 0, 0);
    }
    else
    {
        err = createMatrixOfString(pvApiCtx, Rhs + 1, 1, 1, const_cast<const char * const *>(&value));
    }

    if (err.iErr)
    {
        printError(&err, 0);
        return 0;
    }

    LhsVar(1) = Rhs + 1;
    PutLhsVar();

    return 0;
}