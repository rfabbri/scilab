/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - INRIA - Vincent COUVERT
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

#ifndef __WIDGET_H__
#define __WIDGET_H__
#include "dynlib_gui.h"

/**
 * Request the focus for a Scilab Widget
 *
 * @param pObjUID the object UID
 */
GUI_IMPEXP void requestFocus(char *pObjUID);

#endif /* __WIDGET_H__ */
