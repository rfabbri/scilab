/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Marouane BEN JELLOUL
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

package org.scilab.modules.gui.radiogroup;

import org.scilab.modules.gui.bridge.radiogroup.SwingScilabRadioGroup;

/**
 * Bridge for Scilab RadioGroup in GUIs
 * @author Marouane BEN JELLOUL
 */
public class ScilabRadioGroupBridge {

    /**
     * Constructor
     */
    protected ScilabRadioGroupBridge() {
        throw new UnsupportedOperationException(); /* Prevents calls from subclass */
    }

    /**
     * Creates a Scilab RadioGroup
     * @return the created RadioGroup
     */
    public static RadioGroup createRadioGroup() {
        return new SwingScilabRadioGroup();
    }
}
