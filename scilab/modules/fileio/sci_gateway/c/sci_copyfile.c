/*
* Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
* Copyright (C) 2009-2012 - DIGITEO - Allan CORNET
*
* This file must be used under the terms of the CeCILL.
* This source file is licensed as described in the file COPYING, which
* you should have received as part of this distribution.  The terms
* are also available at
* http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
*
*/
/*--------------------------------------------------------------------------*/
#if defined(__linux__)
#undef _FORTIFY_SOURCE /* Avoid dependency on GLIBC_2.4 (__wcscat_chk/__wcscpy_chk) */
#endif
#ifndef _MSC_VER
#include <errno.h>
#else
#include <windows.h>
#endif
#include "gw_fileio.h"
#include "MALLOC.h"
#include "localization.h"
#include "api_scilab.h"
#include "Scierror.h"
#include "copyfile.h"
#include "FileExist.h"
#include "isdir.h"
#include "splitpath.h"
#include "freeArrayOfString.h"
#include "charEncoding.h"
#include "expandPathVariable.h"
/*--------------------------------------------------------------------------*/
static wchar_t *getFilenameWithExtension(wchar_t * wcFullFilename);
static int returnCopyFileResultOnStack(int ierr, char *fname);
/*--------------------------------------------------------------------------*/
int sci_copyfile(char *fname, unsigned long fname_len)
{
    SciErr sciErr;
    int *piAddressVarOne = NULL;
    wchar_t *pStVarOne = NULL;
    wchar_t *pStVarOneExpanded = NULL;

    int *piAddressVarTwo = NULL;
    wchar_t *pStVarTwo = NULL;
    wchar_t *pStVarTwoExpanded = NULL;

    /* Check Input & Output parameters */
    CheckRhs(2, 2);
    CheckLhs(1, 2);

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        Scierror(999, _("%s: Can not read input argument #%d.\n"), fname, 1);
        return 0;
    }

    if (!isStringType(pvApiCtx, piAddressVarOne))
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 1);
        return 0;
    }

    if (!isScalar(pvApiCtx, piAddressVarOne))
    {
        Scierror(999, _("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 1);
        return 0;
    }

    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressVarTwo);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        Scierror(999, _("%s: Can not read input argument #%d.\n"), fname, 2);
        return 0;
    }

    if (!isStringType(pvApiCtx, piAddressVarTwo))
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 2);
        return 0;
    }

    if (!isScalar(pvApiCtx, piAddressVarTwo))
    {
        Scierror(999, _("%s: Wrong size for input argument #%d: A string expected.\n"), fname, 2);
        return 0;
    }

    if (getAllocatedSingleWideString(pvApiCtx, piAddressVarOne, &pStVarOne))
    {
        Scierror(999, _("%s: Memory allocation error.\n"), fname);
        return 0;
    }

    if (getAllocatedSingleWideString(pvApiCtx, piAddressVarTwo, &pStVarTwo))
    {
        if (pStVarOne)
        {
            freeAllocatedSingleWideString(pStVarOne);
            pStVarOne = NULL;
        }
        Scierror(999, _("%s: Memory allocation error.\n"), fname);
        return 0;
    }

    if (pStVarOne == NULL)
    {
        if (pStVarTwo)
        {
            freeAllocatedSingleWideString(pStVarTwo);
            pStVarTwo = NULL;
        }
        Scierror(999, _("%s: Wrong value for input argument #%d: A string expected.\n"), fname, 1);
        return 0;
    }

    if (pStVarTwo == NULL)
    {
        if (pStVarOne)
        {
            freeAllocatedSingleWideString(pStVarOne);
            pStVarOne = NULL;
        }
        Scierror(999, _("%s: Wrong value for input argument #%d: A string expected.\n"), fname, 2);
        return 0;
    }

    pStVarOneExpanded = expandPathVariableW(pStVarOne);
    pStVarTwoExpanded = expandPathVariableW(pStVarTwo);

    freeAllocatedSingleWideString(pStVarTwo);
    pStVarTwo = NULL;

    freeAllocatedSingleWideString(pStVarOne);
    pStVarOne = NULL;


    if (isdirW(pStVarOneExpanded) || FileExistW(pStVarOneExpanded))
    {
        int ierrCopy = 0;

        if (isdirW(pStVarOneExpanded) || FileExistW(pStVarOneExpanded))
        {
            if (isdirW(pStVarOneExpanded))
            {
                /* copy a directory into a directory */
                ierrCopy = CopyDirectoryFunction(pStVarTwoExpanded, pStVarOneExpanded);
            }
            else if (FileExistW(pStVarOneExpanded))
            {
                if (isdirW(pStVarTwoExpanded))
                {
                    /* copy file into a existing directory */
                    wchar_t *filename = getFilenameWithExtension(pStVarOneExpanded);

                    if (filename)
                    {
#define FORMAT_FULLFILENAME "%s/%s"
                        wchar_t *destFullFilename = NULL;

                        /* remove last file separator if it exists */
                        if ((pStVarTwoExpanded[wcslen(pStVarTwoExpanded) - 1] == L'\\') || (pStVarTwoExpanded[wcslen(pStVarTwoExpanded) - 1] == L'/'))
                        {
                            pStVarTwoExpanded[wcslen(pStVarTwoExpanded) - 1] = L'\0';
                        }

                        destFullFilename = (wchar_t *) MALLOC(sizeof(wchar_t) * ((int)wcslen(pStVarTwoExpanded) +
                                                              (int)wcslen(filename) + (int)wcslen(L"/") + 1));
                        wcscpy(destFullFilename, pStVarTwoExpanded);
                        wcscat(destFullFilename, L"/");
                        wcscat(destFullFilename, filename);

                        ierrCopy = CopyFileFunction(destFullFilename, pStVarOneExpanded);

                        FREE(filename);
                        filename = NULL;

                        FREE(destFullFilename);
                        destFullFilename = NULL;
                    }
                    else
                    {
                        if (pStVarOneExpanded)
                        {
                            FREE(pStVarOneExpanded);
                            pStVarOneExpanded = NULL;
                        }

                        if (pStVarTwoExpanded)
                        {
                            FREE(pStVarTwoExpanded);
                            pStVarTwo = NULL;
                        }

                        Scierror(999, _("%s: Memory allocation error.\n"), fname);
                        return 0;
                    }
                }
                else
                {
                    /* copy a file into a file */
                    ierrCopy = CopyFileFunction(pStVarTwoExpanded, pStVarOneExpanded);
                }
            }
            else
            {
                if (pStVarOneExpanded)
                {
                    FREE(pStVarOneExpanded);
                    pStVarOneExpanded = NULL;
                }

                if (pStVarTwoExpanded)
                {
                    FREE(pStVarTwoExpanded);
                    pStVarTwoExpanded = NULL;
                }
                Scierror(999, _("%s: Wrong value for input argument #%d: A valid filename or directory expected.\n"), fname, 1);
            }
        }
        else
        {
            if (pStVarOneExpanded)
            {
                FREE(pStVarOneExpanded);
                pStVarOneExpanded = NULL;
            }

            if (pStVarTwoExpanded)
            {
                FREE(pStVarTwoExpanded);
                pStVarTwoExpanded = NULL;
            }

            Scierror(999, _("%s: Wrong value(s) for input argument(s).\n"), fname);
            return 0;
        }

        returnCopyFileResultOnStack(ierrCopy, fname);
    }
    else
    {
        Scierror(999, _("%s: Wrong value for input argument #%d: A valid filename or directory expected.\n"), fname, 1);
    }

    if (pStVarOneExpanded)
    {
        FREE(pStVarOneExpanded);
        pStVarOneExpanded = NULL;
    }

    if (pStVarTwoExpanded)
    {
        FREE(pStVarTwoExpanded);
        pStVarTwoExpanded = NULL;
    }

    return 0;
}

/*--------------------------------------------------------------------------*/
static wchar_t *getFilenameWithExtension(wchar_t * wcFullFilename)
{
    wchar_t *wcfilename = NULL;

    if (wcFullFilename)
    {
        wchar_t *wcdrv = MALLOC(sizeof(wchar_t *) * ((int)wcslen(wcFullFilename) + 1));
        wchar_t *wcdir = MALLOC(sizeof(wchar_t *) * ((int)wcslen(wcFullFilename) + 1));
        wchar_t *wcname = MALLOC(sizeof(wchar_t *) * ((int)wcslen(wcFullFilename) + 1));
        wchar_t *wcext = MALLOC(sizeof(wchar_t *) * ((int)wcslen(wcFullFilename) + 1));

        wcfilename = MALLOC(sizeof(wchar_t *) * ((int)wcslen(wcFullFilename) + 1));

        splitpathW(wcFullFilename, FALSE, wcdrv, wcdir, wcname, wcext);

        wcscpy(wcfilename, wcname);
        wcscat(wcfilename, wcext);

        if (wcdrv)
        {
            FREE(wcdrv);
            wcdrv = NULL;
        }

        if (wcdir)
        {
            FREE(wcdir);
            wcdir = NULL;
        }

        if (wcname)
        {
            FREE(wcname);
            wcname = NULL;
        }

        if (wcext)
        {
            FREE(wcext);
            wcext = NULL;
        }
    }
    return wcfilename;
}

/*--------------------------------------------------------------------------*/
static int returnCopyFileResultOnStack(int ierr, char *fname)
{
    double dError = 0.;
    wchar_t *sciError = NULL;

#ifdef _MSC_VER
    if (ierr)
    {
#define BUFFER_SIZE 1024
        DWORD dw = GetLastError();
        wchar_t buffer[BUFFER_SIZE];

        if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
                           dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, BUFFER_SIZE, NULL) == 0)
        {
            wcscpy(buffer, L"Unknown Error");
        }

        // Compatibility with previous version , we return 0
        //dError = (double) dw;
        dError = (double)0.;

        sciError = (wchar_t *) MALLOC(sizeof(wchar_t) * ((int)wcslen(buffer) + 1));
        if (sciError == NULL)
        {
            Scierror(999, _("%s: Memory allocation error.\n"), fname);
            return 0;
        }

        wcscpy(sciError, buffer);
    }
    else
    {
        dError = 1.;
        sciError = (wchar_t *) MALLOC(sizeof(wchar_t) * 1);
        if (sciError == NULL)
        {
            Scierror(999, _("%s: Memory allocation error.\n"), fname);
            return 0;
        }
        wcscpy(sciError, L"");
    }
#else
    if (ierr)
    {
        // Compatibility with previous version , we return 0
        //dError = (double) ierr;
        //dError = (double) 0.;
        sciError = to_wide_string(strerror(errno));
        if (sciError == NULL)
        {
            Scierror(999, _("%s: Memory allocation error.\n"), fname);
            return 0;
        }
    }
    else
    {
        dError = 1.;
        sciError = (wchar_t *) MALLOC(sizeof(wchar_t) * 1);
        if (sciError == NULL)
        {
            Scierror(999, _("%s: Memory allocation error.\n"), fname);
            return 0;
        }
        wcscpy(sciError, L"");
    }
#endif

    if (createScalarDouble(pvApiCtx, Rhs + 1, dError))
    {
        if (sciError)
        {
            FREE(sciError);
            sciError = NULL;
        }
        return 0;
    }

    LhsVar(1) = Rhs + 1;

    if (Lhs == 2)
    {
        if (createSingleWideString(pvApiCtx, Rhs + 2, sciError))
        {
            if (sciError)
            {
                FREE(sciError);
                sciError = NULL;
            }
            return 0;
        }
        LhsVar(2) = Rhs + 2;
    }

    if (sciError)
    {
        FREE(sciError);
        sciError = NULL;
    }

    PutLhsVar();
    return 0;
}

/*--------------------------------------------------------------------------*/
