/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Vincent COUVERT
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

package org.scilab.modules.graphic_objects.uicontrol.checkbox;

import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_UI_CHECKBOX__;

import org.scilab.modules.graphic_objects.uicontrol.Uicontrol;

/**
 * @author Vincent COUVERT
 */
public class CheckBox extends Uicontrol {

    /**
     * Constructor
     */
    public CheckBox() {
        super();
        setStyle(__GO_UI_CHECKBOX__);
        setRelief(FLAT_RELIEF);

        // Default value is the min value (not checked)
        Double[] value = new Double[1];
        value[0] = getMin();
        setUiValue(value);
    }

}
