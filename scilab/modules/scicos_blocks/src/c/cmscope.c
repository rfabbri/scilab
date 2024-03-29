/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2011-2012 - Scilab Enterprises - Clement DAVID
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

#include <string.h>

#include "dynlib_scicos_blocks.h"
#include "scoUtils.h"

#include "MALLOC.h"
#include "elementary_functions.h"

#include "getGraphicObjectProperty.h"
#include "setGraphicObjectProperty.h"
#include "graphicObjectProperties.h"
#include "createGraphicObject.h"
#include "deleteGraphicObject.h"

#include "CurrentFigure.h"
#include "CurrentObject.h"

#include "scicos_block4.h"
#include "scicos.h"

#include "localization.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif

#include "FigureList.h"
#include "BuildObjects.h"
#include "AxesModel.h"

// #include <stdio.h>

// #define LOG(...) printf(__VA_ARGS__)
#define LOG(...)
// #define PUSH_LOG(...) printf(__VA_ARGS__)
#define PUSH_LOG(...)


#define HISTORY_POINTS_THRESHOLD 4096

/*****************************************************************************
 * Internal container structure
 ****************************************************************************/

/**
 * Container structure
 */
typedef struct
{
    struct
    {
        int *numberOfPoints;
        double ***bufferCoordinates;
        int *maxNumberOfPoints;
        double ***historyCoordinates;
    } internal;

    struct
    {
        int *periodCounter;

        BOOL *disableBufferUpdate;
        int *historyUpdateCounter;

        char const* cachedFigureUID;
        char **cachedAxeUID;
        char ***cachedBufferPolylinesUIDs;
        char ***cachedHistoryPolylinesUIDs;
    } scope;
} sco_data;

/**
 * Get (and allocate on demand) the internal data used on this scope
 * \param block the block
 * \return the scope data
 */
static sco_data *getScoData(scicos_block * block);

/**
 * Release any internal data
 *
 * \param block the block
 */
static void freeScoData(scicos_block * block);

/**
 * Realloc the history buffer data
 *
 * \param block the block
 * \param input the selected input
 * \param numberOfPoints realloc to store this number of points
 */
static sco_data *reallocHistoryBuffer(scicos_block * block, int input, int numberOfPoints);

/**
 * Set values into the coordinates buffer.
 *
 * \param block the block
 * \param input the selected input
 * \param coordinates the buffer
 * \param numberOfPoints the number of points to set (actual)
 * \param bufferPoints the buffer size (max)
 * \param t the time to set
 * \param value the value to set
 */
static void setBuffersCoordinates(scicos_block * block, int input, double* coordinates, const int numberOfPoints,
                                  const int bufferPoints, const double t, const double value);

/**
 * Append the data to the current data
 *
 * \param block the block
 * \param input the input (0-indexed)
 * \param t the current time
 * \param data the data to append
 */
static void appendData(scicos_block * block, int input, double t, double *data);

/**
 * Push the block data to the polyline
 *
 * \param block the block
 * \param input the selected input
 * \param row the selected row
 * \param pPolylineUID the polyline uid
 *
 */
static BOOL pushData(scicos_block * block, int input, int row);

/*****************************************************************************
 * Graphics utils
 ****************************************************************************/

/**
 * Get (and allocate on demand) the figure associated with the block
 * \param block the block
 * \return a valid figure UID or NULL on error
 */
static char const* getFigure(scicos_block * block);

/**
 * Get (and allocate on demand) the axe associated with the input
 *
 * \param pFigureUID the parent figure UID
 * \param block the block
 * \param input the current input index (0-indexed)
 * \return a valid axe UID or NULL on error
 */
static char *getAxe(char const* pFigureUID, scicos_block * block, int input);

/**
 * Get (and allocate on demand) the polyline associated with the row
 *
 * \param pAxeUID the parent axe UID
 * \param block the block
 * \param input the current input index (0-indexed)
 * \param row the current row index (0-indexed)
 * \param history get the history polyline
 * \return a valid polyline UID or NULL on error
 */
static char *getPolyline(char *pAxeUID, scicos_block * block, int input, int row, BOOL history);

/**
 * Delete all the buffer polylines.
 *
 * \param block the block
 */
static void deleteBufferPolylines(scicos_block * block);

/**
 * Set the polylines history size and push the history buffer
 *
 * \param block the block
 * \param input the input port index
 * \param maxNumberOfPoints the size of the buffer
 */
static BOOL pushHistory(scicos_block * block, int input, int maxNumberOfPoints);

/**
 * Set the polylines bounds
 *
 * \param block the block
 * \param input the input port index
 * \param periodCounter number of past periods since startup
 */
static BOOL setPolylinesBounds(scicos_block * block, int input, int periodCounter);

/*****************************************************************************
 * Simulation function
 ****************************************************************************/

/** \fn void cmscope(scicos_block * block,int flag)
    \brief the computational function
    \param block A pointer to a scicos_block
    \param flag An int which indicates the state of the block (init, update, ending)
*/
SCICOS_BLOCKS_IMPEXP void cmscope(scicos_block * block, scicos_flag flag)
{
    char const* pFigureUID;

    double t;
    double *u;
    sco_data *sco;

    int i, j;
    BOOL result;

    switch (flag)
    {

        case Initialization:
            sco = getScoData(block);
            if (sco == NULL)
            {
                set_block_error(-5);
                break;
            }
            pFigureUID = getFigure(block);
            if (pFigureUID == NULL)
            {
                // allocation error
                set_block_error(-5);
                break;
            }
            break;

        case StateUpdate:
            pFigureUID = getFigure(block);
            if (pFigureUID == NULL)
            {
                // allocation error
                set_block_error(-5);
                break;
            }

            t = get_scicos_time();
            for (i = 0; i < block->nin; i++)
            {
                u = (double *)block->inptr[i];

                appendData(block, i, t, u);
                for (j = 0; j < block->insz[i]; j++)
                {
                    result = pushData(block, i, j);
                    if (result == FALSE)
                    {
                        Coserror("%s: unable to push some data.", "cmscope");
                        break;
                    }
                }
            }
            break;

        case Ending:
            sco = getScoData(block);
            for (i = 0; i < block->nin; i++)
            {
                sco = reallocHistoryBuffer(block, i, sco->internal.maxNumberOfPoints[i] + sco->internal.numberOfPoints[i]);
                sco->scope.disableBufferUpdate[i] = FALSE;
                sco->scope.historyUpdateCounter[i] = 0;
                pushHistory(block, i, sco->internal.maxNumberOfPoints[i]);
            }
            deleteBufferPolylines(block);
            freeScoData(block);
            break;

        default:
            break;
    }
}

/*-------------------------------------------------------------------------*/

/*****************************************************************************
 *
 * Container management
 *
 ****************************************************************************/

static sco_data *getScoData(scicos_block * block)
{
    sco_data *sco = (sco_data *) * (block->work);
    int i, j, k, l;

    if (sco == NULL)
    {
        /*
         * Data allocation
         */

        sco = (sco_data *) MALLOC(sizeof(sco_data));
        if (sco == NULL)
        {
            goto error_handler_sco;
        }

        sco->internal.numberOfPoints = (int *) MALLOC(block->nin * sizeof(int));
        if (sco->internal.numberOfPoints == NULL)
        {
            goto error_handler_numberOfPoints;
        }
        sco->internal.maxNumberOfPoints = (int *) MALLOC(block->nin * sizeof(int));
        if (sco->internal.maxNumberOfPoints == NULL)
        {
            goto error_handler_maxNumberOfPoints;
        }

        for (i = 0; i < block->nin; i++)
        {
            // 0 points out of a block->ipar[2] points buffer
            sco->internal.numberOfPoints[i] = 0;
            // 0 points out of a 0 points history
            sco->internal.maxNumberOfPoints[i] = 0;
        }

        sco->internal.bufferCoordinates = (double ***)CALLOC(block->nin, sizeof(double **));
        if (sco->internal.bufferCoordinates == NULL)
        {
            goto error_handler_bufferCoordinates;
        }

        for (i = 0; i < block->nin; i++)
        {
            sco->internal.bufferCoordinates[i] = (double **)CALLOC(block->insz[i], sizeof(double *));
            if (sco->internal.bufferCoordinates[i] == NULL)
            {
                goto error_handler_bufferCoordinates_i;
            }
        }
        for (i = 0; i < block->nin; i++)
        {
            for (j = 0; j < block->insz[i]; j++)
            {
                sco->internal.bufferCoordinates[i][j] = (double *)CALLOC(3 * block->ipar[2], sizeof(double));

                if (sco->internal.bufferCoordinates[i][j] == NULL)
                {
                    goto error_handler_bufferCoordinates_ij;
                }
            }
        }

        sco->internal.historyCoordinates = (double ***)CALLOC(block->nin, sizeof(double **));
        if (sco->internal.historyCoordinates == NULL)
        {
            goto error_handler_historyCoordinates;
        }

        for (i = 0; i < block->nin; i++)
        {
            sco->internal.historyCoordinates[i] = (double **)CALLOC(block->insz[i], sizeof(double *));
            if (sco->internal.historyCoordinates[i] == NULL)
            {
                goto error_handler_historyCoordinates_i;
            }
        }

        sco->scope.periodCounter = (int *) CALLOC(block->nin, sizeof(int));
        if (sco->scope.periodCounter == NULL)
        {
            goto error_handler_periodCounter;
        }

        sco->scope.disableBufferUpdate = (int *) CALLOC(block->nin, sizeof(BOOL));
        if (sco->scope.disableBufferUpdate == NULL)
        {
            goto error_handler_disableBufferUpdate;
        }
        sco->scope.historyUpdateCounter = (int *) CALLOC(block->nin, sizeof(int));
        if (sco->scope.historyUpdateCounter == NULL)
        {
            goto error_handler_historyUpdateCounter;
        }

        sco->scope.cachedFigureUID = NULL;
        sco->scope.cachedAxeUID = (char **)CALLOC(block->nin, sizeof(char *));

        sco->scope.cachedBufferPolylinesUIDs = (char ***)CALLOC(block->nin, sizeof(char **));
        sco->scope.cachedHistoryPolylinesUIDs = (char ***)CALLOC(block->nin, sizeof(char **));
        for (i = 0; i < block->nin; i++)
        {
            sco->scope.cachedBufferPolylinesUIDs[i] = (char **)CALLOC(block->insz[i], sizeof(char *));
            sco->scope.cachedHistoryPolylinesUIDs[i] = (char **)CALLOC(block->insz[i], sizeof(char *));
        }

        *(block->work) = sco;
    }

    return sco;

    /*
     * Error management (out of normal flow)
     */

error_handler_historyUpdateCounter:
    FREE(sco->scope.disableBufferUpdate);
error_handler_disableBufferUpdate:
    FREE(sco->scope.periodCounter);
error_handler_periodCounter:
    i = block->nin;
error_handler_historyCoordinates_i:
    for (j = 0; j < i; j++)
    {
        FREE(sco->internal.historyCoordinates[i]);
    }
    FREE(sco->internal.historyCoordinates);
error_handler_historyCoordinates:
    i = block->nin - 1;
    j = block->insz[i] - 1;
error_handler_bufferCoordinates_ij:
    for (k = 0; k < i; k++)
    {
        for (l = 0; l < j; l++)
        {
            FREE(sco->internal.bufferCoordinates[k][l]);
        }
    }
    i = block->nin - 1;
error_handler_bufferCoordinates_i:
    for (j = 0; j < i; j++)
    {
        FREE(sco->internal.bufferCoordinates[i]);
    }
    FREE(sco->internal.bufferCoordinates);
error_handler_bufferCoordinates:
    FREE(sco->internal.maxNumberOfPoints);
error_handler_maxNumberOfPoints:
    FREE(sco->internal.numberOfPoints);
error_handler_numberOfPoints:
    FREE(sco);
error_handler_sco:
    // allocation error
    set_block_error(-5);
    return NULL;
}

static void freeScoData(scicos_block * block)
{
    sco_data *sco = (sco_data *) * (block->work);
    int i, j;

    if (sco != NULL)
    {
        for (i = 0; i < block->nin; i++)
        {
            for (j = 0; j < block->insz[i]; j++)
            {
                if (sco->internal.historyCoordinates[i][j] != NULL)
                {
                    FREE(sco->internal.historyCoordinates[i][j]);
                }
                FREE(sco->internal.bufferCoordinates[i][j]);
            }
            FREE(sco->internal.historyCoordinates[i]);
            FREE(sco->internal.bufferCoordinates[i]);
        }
        FREE(sco->internal.historyCoordinates);
        FREE(sco->internal.bufferCoordinates);

        FREE(sco->scope.periodCounter);

        FREE(sco->scope.disableBufferUpdate);
        FREE(sco->scope.historyUpdateCounter);

        for (i = 0; i < block->nin; i++)
        {
            FREE(sco->scope.cachedHistoryPolylinesUIDs[i]);
            FREE(sco->scope.cachedBufferPolylinesUIDs[i]);
        }
        FREE(sco->scope.cachedAxeUID);

        FREE(sco);
        *(block->work) = NULL;
    }
}

static sco_data *reallocHistoryBuffer(scicos_block * block, int input, int numberOfPoints)
{
    sco_data *sco = (sco_data *) * (block->work);
    int i;

    double *ptr;
    int allocatedNumberOfPoints;

    int previousNumberOfPoints = sco->internal.maxNumberOfPoints[input];
    int numberOfCopiedPoints = numberOfPoints - sco->internal.maxNumberOfPoints[input];

    double *buffer;
    int bufferNumberOfPoints = block->ipar[2];
    int bufferNewPointInc;

    if (previousNumberOfPoints == 0)
    {
        allocatedNumberOfPoints = numberOfPoints;
        bufferNewPointInc = 0;
    }
    else
    {
        allocatedNumberOfPoints = numberOfPoints - 1;
        bufferNewPointInc = 1;
    }

    if (sco->scope.historyUpdateCounter[input] <= 0)
    {
        if (numberOfPoints > HISTORY_POINTS_THRESHOLD)
        {
            sco->scope.disableBufferUpdate[input] = TRUE;
            sco->scope.historyUpdateCounter[input] = numberOfPoints / HISTORY_POINTS_THRESHOLD;
        }
        else
        {
            sco->scope.disableBufferUpdate[input] = FALSE;
            sco->scope.historyUpdateCounter[input] = 0;
        }
    }

    for (i = 0; i < block->insz[input]; i++)
    {
        ptr = (double *)MALLOC(3 * allocatedNumberOfPoints * sizeof(double));
        if (ptr == NULL)
        {
            goto error_handler;
        }

        // memcpy existing X-axis values from the history
        memcpy(ptr, sco->internal.historyCoordinates[input][i], previousNumberOfPoints * sizeof(double));
        // memcpy existing Y-axis values from the history
        memcpy(ptr + allocatedNumberOfPoints, sco->internal.historyCoordinates[input][i] + previousNumberOfPoints, previousNumberOfPoints * sizeof(double));
        // clear the last points, the Z-axis values
        memset(ptr + 2 * allocatedNumberOfPoints, 0, allocatedNumberOfPoints * sizeof(double));

        // then set the last points to the last values for X-axis and Y-axis values from the buffer points
        buffer = sco->internal.bufferCoordinates[input][i];
        memcpy(ptr + previousNumberOfPoints, buffer + bufferNewPointInc, (numberOfCopiedPoints - bufferNewPointInc) * sizeof(double));
        memcpy(ptr + allocatedNumberOfPoints + previousNumberOfPoints, buffer + bufferNumberOfPoints + bufferNewPointInc, (numberOfCopiedPoints - bufferNewPointInc) * sizeof(double));

        FREE(sco->internal.historyCoordinates[input][i]);
        sco->internal.historyCoordinates[input][i] = ptr;
    }

    sco->internal.maxNumberOfPoints[input] = allocatedNumberOfPoints;
    return sco;

error_handler:
    freeScoData(block);
    // allocation error
    set_block_error(-5);
    return NULL;
}

static void setBuffersCoordinates(scicos_block * block, int input, double* coordinates, const int numberOfPoints,
                                  const int bufferPoints, const double t, const double value)
{
    int setLen;
    sco_data *sco = (sco_data *) * (block->work);

    if (sco->scope.disableBufferUpdate[input] == TRUE)
    {
        coordinates[numberOfPoints] = t;
        coordinates[bufferPoints + numberOfPoints] = value;
        return;
    }

    // X-axis values first
    for (setLen = numberOfPoints; setLen < bufferPoints; setLen++)
    {
        coordinates[setLen] = t;
    }
    // then Y-axis values
    for (setLen = numberOfPoints; setLen < bufferPoints; setLen++)
    {
        coordinates[bufferPoints + setLen] = value;
    }
    // then Z-axis values (always clear'ed)
}

static void appendData(scicos_block * block, int input, double t, double *data)
{
    int i;

    sco_data *sco = (sco_data *) * (block->work);

    /*
     * Handle the case where the t is greater than the data_bounds
     */
    if (t > ((sco->scope.periodCounter[input] + 1) * block->rpar[1 + input]))
    {
        sco->scope.periodCounter[input]++;

        // set the buffer coordinates to the last point
        for (i = 0; i < block->insz[input]; i++)
        {
            sco->internal.bufferCoordinates[input][i][0] = sco->internal.bufferCoordinates[input][i][sco->internal.numberOfPoints[input] - 1];
            sco->internal.bufferCoordinates[input][i][block->ipar[2]] = sco->internal.bufferCoordinates[input][i][block->ipar[2] + sco->internal.numberOfPoints[input] - 1];
        }
        sco->internal.numberOfPoints[input] = 1;

        // clear the history coordinates
        sco->internal.maxNumberOfPoints[input] = 0;
        for (i = 0; i < block->insz[input]; i++)
        {
            if (sco->internal.historyCoordinates[input][i] != NULL)
            {
                FREE(sco->internal.historyCoordinates[input][i]);
                sco->internal.historyCoordinates[input][i] = NULL;
            }
        }

        // configure scope setting
        if (setPolylinesBounds(block, input, sco->scope.periodCounter[input]) == FALSE)
        {
            set_block_error(-5);
            freeScoData(block);
            sco = NULL;
        }
    }

    /*
     * Handle the case where the scope has more points than maxNumberOfPoints
     */
    if (sco != NULL && sco->internal.numberOfPoints[input] >= block->ipar[2])
    {
        int maxNumberOfPoints = sco->internal.maxNumberOfPoints[input];

        // on a full scope, re-alloc history coordinates
        maxNumberOfPoints = maxNumberOfPoints + block->ipar[2];
        sco = reallocHistoryBuffer(block, input, maxNumberOfPoints);

        // set the buffer coordinates to the last point
        for (i = 0; i < block->insz[input]; i++)
        {
            sco->internal.bufferCoordinates[input][i][0] = sco->internal.bufferCoordinates[input][i][block->ipar[2] - 1];
            sco->internal.bufferCoordinates[input][i][block->ipar[2]] = sco->internal.bufferCoordinates[input][i][2 * block->ipar[2] - 1];
        }
        sco->internal.numberOfPoints[input] = 1;

        // reconfigure related graphic objects
        if (pushHistory(block, input, sco->internal.maxNumberOfPoints[input]) == FALSE)
        {
            set_block_error(-5);
            freeScoData(block);
            sco = NULL;
        }
    }

    /*
     * Update data
     */
    if (sco != NULL)
    {
        for (i = 0; i < block->insz[input]; i++)
        {
            const double value = data[i];
            setBuffersCoordinates(block, input, sco->internal.bufferCoordinates[input][i], sco->internal.numberOfPoints[input], block->ipar[2], t, value);
        }

        sco->internal.numberOfPoints[input]++;
    }
}

static BOOL pushData(scicos_block * block, int input, int row)
{
    char const* pFigureUID;
    char *pAxeUID;
    char *pPolylineUID;

    double *data;
    sco_data *sco;

    pFigureUID = getFigure(block);
    pAxeUID = getAxe(pFigureUID, block, input);
    pPolylineUID = getPolyline(pAxeUID, block, input, row, FALSE);

    sco = getScoData(block);
    if (sco == NULL)
    {
        return FALSE;
    }

    // do not push any data if disabled
    if (sco->scope.disableBufferUpdate[input] == TRUE)
    {
        return TRUE;
    }

    // select the right input and row
    data = sco->internal.bufferCoordinates[input][row];

    PUSH_LOG("%s: %d\n", "pushData", block->ipar[2]);
    return setGraphicObjectProperty(pPolylineUID, __GO_DATA_MODEL_COORDINATES__, data, jni_double_vector, block->ipar[2]);
}

/*****************************************************************************
 *
 * Graphic utils
 *
 ****************************************************************************/

/**
 * Set properties on the figure.
 *
 * \param pFigureUID the figure uid
 * \param block the current block
 */
static void setFigureSettings(char const* pFigureUID, scicos_block * block)
{
    int win_pos[2];
    int win_dim[2];
    char* label;

    int *ipar = block->ipar;

    win_pos[0] = ipar[3];
    win_pos[1] = ipar[4];
    win_dim[0] = ipar[5];
    win_dim[1] = ipar[6];

    if (win_pos[0] > 0 && win_pos[1] > 0)
    {
        setGraphicObjectProperty(pFigureUID, __GO_POSITION__, &win_pos, jni_int_vector, 2);
    }

    if (win_dim[0] > 0 && win_dim[1] > 0)
    {
        setGraphicObjectProperty(pFigureUID, __GO_SIZE__, &win_dim, jni_int_vector, 2);
    }

    label = GetLabelPtrs(block);
    if (label != NULL)
    {
        if (strlen(label) > 0)
        {
            setGraphicObjectProperty(pFigureUID, __GO_NAME__, label, jni_string, 1);
        }
    }
}

/**
 * Set properties on the axes.
 *
 * \param pAxeUID the axe uid
 * \param block the current block
 * \param index axe index (0-indexed)
 */
static void setAxesSettings(char *pAxeUID, scicos_block * block, int index)
{
    double axesBounds[4];
    double margins[4];

    double nin = (double) block->nin;

    axesBounds[0] = 0;              // x
    axesBounds[1] = index / nin;    // y
    axesBounds[2] = 1.0;            // w
    axesBounds[3] = 1 / nin;        // h
    setGraphicObjectProperty(pAxeUID, __GO_AXES_BOUNDS__, axesBounds, jni_double_vector, 4);

    margins[0] = 0.125;
    margins[1] = 0.125;
    margins[2] = 0.125;
    margins[3] = 0.125;
    setGraphicObjectProperty(pAxeUID, __GO_MARGINS__, margins, jni_double_vector, 4);

};

/*****************************************************************************
 *
 * Graphic
 *
 ****************************************************************************/

static char const* getFigure(scicos_block * block)
{
    signed int figNum;
    char const* pFigureUID = NULL;
    char *pAxe = NULL;
    int i__1 = 1;
    sco_data *sco = (sco_data *) * (block->work);

    int i;

    // assert the sco is not NULL
    if (sco == NULL)
    {
        return NULL;
    }

    // fast path for an existing object
    if (sco->scope.cachedFigureUID != NULL)
    {
        return sco->scope.cachedFigureUID;
    }

    figNum = block->ipar[0];

    // with a negative id, use the block number indexed from a constant.
    if (figNum < 0)
    {
        figNum = 20000 + get_block_number();
    }

    pFigureUID = getFigureFromIndex(figNum);
    // create on demand
    if (pFigureUID == NULL)
    {
        pFigureUID = createNewFigureWithAxes();
        setGraphicObjectProperty(pFigureUID, __GO_ID__, &figNum, jni_int, 1);

        // the stored uid is a reference to the figure map, not to the current figure
        pFigureUID = getFigureFromIndex(figNum);
        sco->scope.cachedFigureUID = pFigureUID;

        // set configured parameters
        setFigureSettings(pFigureUID, block);

        // allocate the axes through the getter
        for (i = 0; i < GetNin(block); i++)
        {
            pAxe = getAxe(pFigureUID, block, i);

            /*
             * Setup according to block settings
             */
            setLabel(pAxe, __GO_X_AXIS_LABEL__, "t");
            setLabel(pAxe, __GO_Y_AXIS_LABEL__, "y");

            setGraphicObjectProperty(pAxe, __GO_X_AXIS_VISIBLE__, &i__1, jni_bool, 1);
            setGraphicObjectProperty(pAxe, __GO_Y_AXIS_VISIBLE__, &i__1, jni_bool, 1);

            setPolylinesBounds(block, i, 0);
        }
    }

    if (sco->scope.cachedFigureUID == NULL)
    {
        sco->scope.cachedFigureUID = pFigureUID;
    }
    return pFigureUID;
}

static char *getAxe(char const* pFigureUID, scicos_block * block, int input)
{
    char *pAxe;
    int i;
    sco_data *sco = (sco_data *) * (block->work);

    // assert the sco is not NULL
    if (sco == NULL)
    {
        return NULL;
    }

    // fast path for an existing object
    if (sco->scope.cachedAxeUID != NULL && sco->scope.cachedAxeUID[input] != NULL)
    {
        return sco->scope.cachedAxeUID[input];
    }

    pAxe = findChildWithKindAt(pFigureUID, __GO_AXES__, input);

    /*
     * Allocate if necessary
     */
    if (pAxe == NULL)
    {
        cloneAxesModel(pFigureUID);
        pAxe = findChildWithKindAt(pFigureUID, __GO_AXES__, input);
    }

    /*
     * Setup on first access
     */
    if (pAxe != NULL)
    {
        // allocate the polylines through the getter
        for (i = 0; i < block->insz[input]; i++)
        {
            getPolyline(pAxe, block, input, i, TRUE);
        }
        for (i = 0; i < block->insz[input]; i++)
        {
            getPolyline(pAxe, block, input, i, FALSE);
        }

        setAxesSettings(pAxe, block, input);
    }

    /*
     * then cache with local storage
     */
    if (pAxe != NULL && sco->scope.cachedAxeUID != NULL && sco->scope.cachedAxeUID[input] == NULL)
    {
        sco->scope.cachedAxeUID[input] = strdup(pAxe);
        releaseGraphicObjectProperty(__GO_PARENT__, pAxe, jni_string, 1);
    }
    return sco->scope.cachedAxeUID[input];
}

static char *getPolyline(char *pAxeUID, scicos_block * block, int input, int row, BOOL history)
{
    char *pPolyline;
    BOOL b__true = TRUE;

    int color;

    char*** polylinesUIDs;
    int polylineIndex;
    int polylineDefaultNumElement;

    sco_data *sco = (sco_data *) * (block->work);

    // assert the sco is not NULL
    if (sco == NULL)
    {
        return NULL;
    }

    if (!history)
    {
        polylinesUIDs = sco->scope.cachedBufferPolylinesUIDs;
        polylineIndex = block->insz[input] + row;
        polylineDefaultNumElement = block->ipar[2];
    }
    else
    {
        polylinesUIDs = sco->scope.cachedHistoryPolylinesUIDs;
        polylineIndex = row;
        polylineDefaultNumElement = 0;
    }

    // fast path for an existing object
    if (polylinesUIDs != NULL && polylinesUIDs[input] != NULL && polylinesUIDs[input][row] != NULL)
    {
        return polylinesUIDs[input][row];
    }

    pPolyline = findChildWithKindAt(pAxeUID, __GO_POLYLINE__, polylineIndex);

    /*
     * Allocate if necessary
     */
    if (pPolyline == NULL)
    {
        pPolyline = createGraphicObject(__GO_POLYLINE__);

        if (pPolyline != NULL)
        {
            createDataObject(pPolyline, __GO_POLYLINE__);
            setGraphicObjectRelationship(pAxeUID, pPolyline);
        }
    }

    /*
     * Setup on first access
     */
    if (pPolyline != NULL)
    {

        /*
         * Default setup of the nGons property
         */
        {
            int nGons = 1;
            setGraphicObjectProperty(pPolyline, __GO_DATA_MODEL_NUM_GONS__, &nGons, jni_int, 1);
        }

        // ipar=[win;size(in,'*');N;wpos(:);wdim(:);in(:);clrs(:);heritance]
        //        1     1         1   2       2      nin   nin       1
        color = block->ipar[7 + block->nin + input + row];
        if (color > 0)
        {
            LOG("%s: %s at %d at %d to %d\n", "cmscope", "set lines mode", input, row, color);

            setGraphicObjectProperty(pPolyline, __GO_LINE_MODE__, &b__true, jni_bool, 1);
            setGraphicObjectProperty(pPolyline, __GO_LINE_COLOR__, &color, jni_int, 1);
        }
        else
        {
            int iMarkSize = 4;
            color = -color;

            LOG("%s: %s at %d at %d to %d\n", "cmscope", "set mark mode", input, row, -color);

            setGraphicObjectProperty(pPolyline, __GO_MARK_MODE__, &b__true, jni_bool, 1);
            setGraphicObjectProperty(pPolyline, __GO_MARK_STYLE__, &color, jni_int, 1);
            setGraphicObjectProperty(pPolyline, __GO_MARK_SIZE__, &iMarkSize, jni_int, 1);
        }

        {
            int iClipState = 1; //on
            setGraphicObjectProperty(pPolyline, __GO_CLIP_STATE__, &iClipState, jni_int, 1);
        }
    }

    /*
     * then cache with local storage
     */
    if (pPolyline != NULL && polylinesUIDs != NULL && polylinesUIDs[input] != NULL)
    {
        polylinesUIDs[input][row] = strdup(pPolyline);
        releaseGraphicObjectProperty(__GO_PARENT__, pPolyline, jni_string, 1);
    }
    return polylinesUIDs[input][row];
}

static void deleteBufferPolylines(scicos_block * block)
{
    int i, j;

    char *pPolylineUID;

    sco_data *sco;

    sco = getScoData(block);
    for (i = 0; i < block->nin; i++)
    {
        for (j = 0; j < block->insz[i]; j++)
        {
            pPolylineUID = sco->scope.cachedBufferPolylinesUIDs[i][j];
            deleteGraphicObject(pPolylineUID);
        }
    }
}

static BOOL pushHistory(scicos_block * block, int input, int maxNumberOfPoints)
{
    int i;

    char const* pFigureUID;
    char *pAxeUID;
    char *pPolylineUID;

    double *data;
    sco_data *sco;

    BOOL result = TRUE;

    sco = getScoData(block);
    pFigureUID = getFigure(block);
    pAxeUID = getAxe(pFigureUID, block, input);

    // push the data only if the counter == 0, decrement the counter if positive
    if (sco->scope.historyUpdateCounter[input] > 0)
    {
        sco->scope.historyUpdateCounter[input]--;
    }
    if (sco->scope.historyUpdateCounter[input] > 0)
    {
        return result;
    }

    for (i = 0; i < block->insz[input]; i++)
    {
        pPolylineUID = getPolyline(pAxeUID, block, input, i, TRUE);

        data = sco->internal.historyCoordinates[input][i];

        PUSH_LOG("%s: %d\n", "pushHistory", maxNumberOfPoints);
        result &= setGraphicObjectProperty(pPolylineUID, __GO_DATA_MODEL_COORDINATES__, data, jni_double_vector, maxNumberOfPoints);
    }

    return result;
}

static BOOL setPolylinesBounds(scicos_block * block, int input, int periodCounter)
{
    char const* pFigureUID;
    char *pAxeUID;

    double dataBounds[6];
    int nin = block->nin;
    double period = block->rpar[block->nrpar - 3 * nin + input];

    dataBounds[0] = periodCounter * period; // xMin
    dataBounds[1] = (periodCounter + 1) * period;   // xMax
    dataBounds[2] = block->rpar[block->nrpar - 2 * nin + 2 * input];    // yMin
    dataBounds[3] = block->rpar[block->nrpar - 2 * nin + 2 * input + 1];    // yMax
    dataBounds[4] = -1.0;       // zMin
    dataBounds[5] = 1.0;        // zMax

    LOG("%s: %s at %d to %f\n", "cmscope", "setPolylinesBounds", input, dataBounds[1]);

    pFigureUID = getFigure(block);
    pAxeUID = getAxe(pFigureUID, block, input);
    return setGraphicObjectProperty(pAxeUID, __GO_DATA_BOUNDS__, dataBounds, jni_double_vector, 6);
}
