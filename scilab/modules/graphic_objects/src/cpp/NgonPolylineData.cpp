/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2010 - DIGITEO - Manuel Juliachs
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

#include <iostream>

#include "NgonPolylineData.hxx"
#include "DataProperties.hxx"

extern "C" {
#include "BOOL.h"

#include <string.h>

#include "graphicObjectProperties.h"
}

NgonPolylineData::NgonPolylineData(void)
{
    xShift = NULL;
    yShift = NULL;
    zShift = NULL;

    xShiftSet = 0;
    yShiftSet = 0;
    zShiftSet = 0;

    coordinatesShift = NULL;

    zCoordinatesSet = 0;
}

NgonPolylineData::~NgonPolylineData(void)
{
    if (xShiftSet)
    {
        delete [] xShift;
    }

    if (yShiftSet)
    {
        delete [] yShift;
    }

    if (zShiftSet)
    {
        delete [] zShift;
    }
}

int NgonPolylineData::getPropertyFromName(int propertyName)
{
    switch (propertyName)
    {
        case __GO_DATA_MODEL_NUM_ELEMENTS_ARRAY__ :
            return NUM_ELEMENTS_ARRAY;
        case __GO_DATA_MODEL_X_COORDINATES_SHIFT__ :
            return X_COORDINATES_SHIFT;
        case __GO_DATA_MODEL_Y_COORDINATES_SHIFT__ :
            return Y_COORDINATES_SHIFT;
        case __GO_DATA_MODEL_Z_COORDINATES_SHIFT__ :
            return Z_COORDINATES_SHIFT;
        case __GO_DATA_MODEL_NUM_ELEMENTS__ :
            return NUM_ELEMENTS;
        case __GO_DATA_MODEL_X_COORDINATES_SHIFT_SET__ :
            return X_COORDINATES_SHIFT_SET;
        case __GO_DATA_MODEL_Y_COORDINATES_SHIFT_SET__ :
            return Y_COORDINATES_SHIFT_SET;
        case __GO_DATA_MODEL_Z_COORDINATES_SHIFT_SET__ :
            return Z_COORDINATES_SHIFT_SET;
        case __GO_DATA_MODEL_Z_COORDINATES_SET__ :
            return Z_COORDINATES_SET;
        default :
            return NgonGeneralData::getPropertyFromName(propertyName);
    }

}


int NgonPolylineData::setDataProperty(int property, void const* value, int numElements)
{
    if (property == NUM_ELEMENTS_ARRAY)
    {
        return setNumElementsArray((int const*) value);
    }
    else if (property == X_COORDINATES_SHIFT)
    {
        return setXCoordinatesShift((double const*) value, numElements);
    }
    else if (property == Y_COORDINATES_SHIFT)
    {
        return setYCoordinatesShift((double const*) value, numElements);
    }
    else if (property == Z_COORDINATES_SHIFT)
    {
        return setZCoordinatesShift((double const*) value, numElements);
    }
    else if (property == X_COORDINATES_SHIFT_SET)
    {
        setXCoordinatesShiftSet(*((int const*) value));
    }
    else if (property == Y_COORDINATES_SHIFT_SET)
    {
        setYCoordinatesShiftSet(*((int const*) value));
    }
    else if (property == Z_COORDINATES_SHIFT_SET)
    {
        setZCoordinatesShiftSet(*((int const*) value));
    }
    else if (property == Z_COORDINATES_SET)
    {
        setZCoordinatesSet(*((int const*) value));
    }
    else
    {
        return NgonGeneralData::setDataProperty(property, value, numElements);
    }

    return 1;
}

void NgonPolylineData::getDataProperty(int property, void **_pvData)
{
    if (property == X_COORDINATES_SHIFT)
    {
        *_pvData = getXCoordinatesShift();
    }
    else if (property == Y_COORDINATES_SHIFT)
    {
        *_pvData = getYCoordinatesShift();
    }
    else if (property == Z_COORDINATES_SHIFT)
    {
        *_pvData = getZCoordinatesShift();
    }
    else if (property == NUM_ELEMENTS)
    {
        ((int *) *_pvData)[0] = getNumElements();
    }
    else if (property == X_COORDINATES_SHIFT_SET)
    {
        ((int *) *_pvData)[0] = getXCoordinatesShiftSet();
    }
    else if (property == Y_COORDINATES_SHIFT_SET)
    {
        ((int *) *_pvData)[0] = getYCoordinatesShiftSet();
    }
    else if (property == Z_COORDINATES_SHIFT_SET)
    {
        ((int *) *_pvData)[0] = getZCoordinatesShiftSet();
    }
    else if (property == Z_COORDINATES_SET)
    {
        ((int *) *_pvData)[0] = getZCoordinatesSet();
    }
    else
    {
        NgonGeneralData::getDataProperty(property, _pvData);
    }

}

int NgonPolylineData::getNumElements(void)
{
    return numVerticesPerGon;
}

void NgonPolylineData::setZCoordinatesSet(int zCoordinatesSet)
{
    this->zCoordinatesSet = zCoordinatesSet;
}

int NgonPolylineData::getZCoordinatesSet(void)
{
    return this->zCoordinatesSet;
}

double* NgonPolylineData::getXCoordinatesShift(void)
{
    return xShift;
}

int NgonPolylineData::setXCoordinatesShift(double const* data, int numElements)
{
    if (xShiftSet == 0)
    {

        try
        {
            xShift = new double[numVerticesPerGon];
        }
        catch (const std::exception& e)
        {
            e.what();
            return 0;
        }

        xShiftSet = 1;
    }

    for (int i = 0; i < numVerticesPerGon; i++)
    {
        xShift[i] = data[i];
    }

    return 1;
}

double* NgonPolylineData::getYCoordinatesShift()
{
    return yShift;
}

int NgonPolylineData::setYCoordinatesShift(double const* data, int numElements)
{
    if (yShiftSet == 0)
    {

        try
        {
            yShift = new double[numVerticesPerGon];
        }
        catch (const std::exception& e)
        {
            e.what();
            return 0;
        }

        yShiftSet = 1;
    }

    for (int i = 0; i < numVerticesPerGon; i++)
    {
        yShift[i] = data[i];
    }

    return 1;
}

double* NgonPolylineData::getZCoordinatesShift()
{
    return zShift;
}

int NgonPolylineData::getXCoordinatesShiftSet(void)
{
    return xShiftSet;
}

void NgonPolylineData::setXCoordinatesShiftSet(int xShiftSet)
{
    if (xShiftSet == 0 && this->xShiftSet == 1)
    {
        delete [] xShift;
        xShift = NULL;
    }

    this->xShiftSet = xShiftSet;
}

int NgonPolylineData::getYCoordinatesShiftSet(void)
{
    return yShiftSet;
}

void NgonPolylineData::setYCoordinatesShiftSet(int yShiftSet)
{
    if (yShiftSet == 0 && this->yShiftSet == 1)
    {
        delete [] yShift;
        yShift = NULL;
    }

    this->yShiftSet = yShiftSet;
}

int NgonPolylineData::getZCoordinatesShiftSet(void)
{
    return zShiftSet;
}

void NgonPolylineData::setZCoordinatesShiftSet(int zShiftSet)
{
    if (zShiftSet == 0 && this->zShiftSet == 1)
    {
        delete [] zShift;
        zShift = NULL;
    }

    this->zShiftSet = zShiftSet;
}

int NgonPolylineData::setZCoordinatesShift(double const* data, int numElements)
{
    if (zShiftSet == 0)
    {

        try
        {
            zShift = new double[numVerticesPerGon];
        }
        catch (const std::exception& e)
        {
            e.what();
            return 0;
        }

        zShiftSet = 1;
    }

    for (int i = 0; i < numVerticesPerGon; i++)
    {
        zShift[i] = data[i];
    }

    return 1;
}

int NgonPolylineData::setNumElementsArray(int const* numElementsArray)
{
    int newNumElements = 0;
    int previousNumElements = 0;
    int result = 1;

    if (numElementsArray[0] != 1)
    {
        return 0;
    }

    newNumElements = numElementsArray[0] * numElementsArray[1];
    previousNumElements = numGons * numVerticesPerGon;

    if (newNumElements == 0 && previousNumElements > 0)
    {
        numVerticesPerGon = 0;

        deleteCoordinatesArrays();

        return 1;
    }

    if (numGons*numVerticesPerGon != newNumElements)
    {
        double* newCoordinates = NULL;
        double* xShiftNew = NULL;
        double* yShiftNew = NULL;
        double* zShiftNew = NULL;

        result = 1;

        try
        {
            newCoordinates = new double[3 * newNumElements];
        }
        catch (const std::exception& e)
        {
            e.what();
            return 0;
        }

        if (xShiftSet)
        {
            try
            {
                xShiftNew = new double[newNumElements];
            }
            catch (const std::exception& e)
            {
                e.what();
                result = 0;
            }
        }

        if (yShiftSet)
        {
            try
            {
                yShiftNew = new double[newNumElements];
            }
            catch (const std::exception& e)
            {
                e.what();
                result = 0;
            }
        }

        if (zShiftSet)
        {
            try
            {
                zShiftNew = new double[newNumElements];
            }
            catch (const std::exception& e)
            {
                e.what();
                result = 0;
            }
        }

        if (result)
        {
            if (numGons * numVerticesPerGon > 0)
            {
                delete [] coordinates;
            }

            /*
             * Initialize the new coordinates' z values to 0 in case
             * they are not set afterwards.
             */
            for (int i = 0; i < newNumElements; i++)
            {
                newCoordinates[2 * newNumElements + i] = 0.0;
            }

            coordinates = newCoordinates;

            if (xShiftSet)
            {
                copyShiftCoordinatesArray(xShiftNew, xShift, newNumElements);
                delete [] xShift;
                xShift = xShiftNew;
            }

            if (yShiftSet)
            {
                copyShiftCoordinatesArray(yShiftNew, yShift, newNumElements);
                delete [] yShift;
                yShift = yShiftNew;
            }

            if (zShiftSet)
            {
                copyShiftCoordinatesArray(zShiftNew, zShift, newNumElements);
                delete [] zShift;
                zShift = zShiftNew;
            }

            numGons = numElementsArray[0];
            numVerticesPerGon = numElementsArray[1];
        }
        else
        {
            /* Delete the temporary arrays and don't set anything */
            if (newCoordinates != NULL)
            {
                delete [] newCoordinates;
            }

            if (xShiftNew != NULL)
            {
                delete [] xShiftNew;
            }

            if (yShiftNew != NULL)
            {
                delete [] yShiftNew;
            }

            if (zShiftNew != NULL)
            {
                delete [] zShiftNew;
            }

        }

    }

    return result;
}

void NgonPolylineData::copyShiftCoordinatesArray(double * newShift, double const* oldShift, int numElementsNew)
{
    int numElementsCopied = 0;

    if (numElementsNew < numVerticesPerGon)
    {
        numElementsCopied = numElementsNew;
    }
    else
    {
        numElementsCopied = numVerticesPerGon;
    }

    for (int i = 0; i < numElementsCopied; i++)
    {
        newShift[i] = oldShift[i];
    }

    for (int i = numElementsCopied; i < numElementsNew; i++)
    {
        newShift[i] = 0.0;
    }
}

void NgonPolylineData::deleteCoordinatesArrays(void)
{
    if (coordinates != NULL)
    {
        delete [] coordinates;
        coordinates = NULL;
    }

    if (xShiftSet)
    {
        delete [] xShift;
        xShift = NULL;
        xShiftSet = 0;
    }

    if (yShiftSet)
    {
        delete [] yShift;
        yShift = NULL;
        yShiftSet = 0;
    }

    if (zShiftSet)
    {
        delete [] zShift;
        zShift = NULL;
        zShiftSet = 0;
    }
}

