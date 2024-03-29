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

#include "CallClipboard.hxx"

using namespace org_scilab_modules_gui_bridge;

char *getClipboardContents(void)
{
    return CallScilabBridge::getClipboardContents(getScilabJavaVM());
}

void pasteClipboardIntoConsole(void)
{
    CallScilabBridge::pasteClipboardIntoConsole(getScilabJavaVM());
}

void copyConsoleSelection(void)
{
    CallScilabBridge::copyConsoleSelection(getScilabJavaVM());
}

void emptyClipboard(void)
{
    CallScilabBridge::emptyClipboard(getScilabJavaVM());
}

void setClipboardContents(char *text)
{
    CallScilabBridge::setClipboardContents(getScilabJavaVM(), text);
}

void copyFigureToClipBoard(char * figID)
{
    CallScilabBridge::copyFigureToClipBoard(getScilabJavaVM(), figID);
}


