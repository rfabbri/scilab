/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2011 - Scilab Enterprises - Clément DAVID
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

extern "C"
{
#include "machine.h"
#include "MALLOC.h"
#include "BOOL.h"

#include "getGraphicObjectProperty.h"
#include "setGraphicObjectProperty.h"
#include "graphicObjectProperties.h"

#include "scoUtils.h"
#include "scicos_block4.h"
#include "scicos.h"

#include <string.h>

    // #include <stdio.h>
    // #define LOG(...) printf(__VA_ARGS__)
#define LOG(...)
}

char *findChildWithKindAt(char const* parent, int type, const int position)
{
    char *child = NULL;

    int childrenCount;
    char **children;

    int i;
    int iChildType = -1;
    int *piChildType = &iChildType;
    int typeCount;

    int *pChildrenCount = &childrenCount;
    getGraphicObjectProperty(parent, __GO_CHILDREN_COUNT__, jni_int, (void **)&pChildrenCount);
    getGraphicObjectProperty(parent, __GO_CHILDREN__, jni_string_vector, (void **)&children);

    for (typeCount = 0, i = childrenCount - 1; i >= 0; i--)
    {
        getGraphicObjectProperty(children[i], __GO_TYPE__, jni_int, (void **)&piChildType);

        if (iChildType == type)
        {
            typeCount++;
        }

        if (typeCount == (position + 1))
        {
            /*
             * Use a C++ allocation, to allow a future delete char* . Using strdup there will perform a malloc allocation instead of a new allocation.
             */
            int len = (int) strlen(children[i]);
            child = new char[len + 1];
            strcpy(child, children[i]);

            LOG("%s: found %s at %d : %s\n", "findChildWithKindAt", type, position, child);
            break;
        }
    }

    releaseGraphicObjectProperty(__GO_CHILDREN__, children, jni_string_vector, childrenCount);
    return child;
};

BOOL setLabel(char const* pAxeUID, int _iName, char const* label)
{
    char *pLabelUID;
    int dimensions[2];

    BOOL result = TRUE;

    getGraphicObjectProperty(pAxeUID, _iName, jni_string, (void **)&pLabelUID);

    if (pLabelUID != NULL && strcmp(pLabelUID, "") != 0)
    {
        dimensions[0] = 1;
        dimensions[1] = 1;

        result = setGraphicObjectProperty(pLabelUID, __GO_TEXT_ARRAY_DIMENSIONS__, &dimensions, jni_int_vector, 2);
    }

    if (pLabelUID != NULL && result == TRUE)
    {
        result = setGraphicObjectProperty(pLabelUID, __GO_TEXT_STRINGS__, &label, jni_string_vector, 1);
    }

    releaseGraphicObjectProperty(_iName, pLabelUID, jni_string, 1);

    return (BOOL) (result && pLabelUID != NULL);
}
