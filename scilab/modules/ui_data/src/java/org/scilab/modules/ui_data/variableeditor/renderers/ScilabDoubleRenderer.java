/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Allan SIMON
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.ui_data.variableeditor.renderers;

/**
 * CellRenderer for double type
 * @author Allan SIMON
 */
public class ScilabDoubleRenderer extends ScilabComplexRenderer {
	
    /**
     * Constructor
     */
    public ScilabDoubleRenderer() {
	super();
    }
    
    /**
     * {@inheritDoc}
     */
    protected void setValue(Object value) {
	if (value == null) {
	    super.setValue("");
	} else if (value instanceof String) {
	    super.setValue(value);
	} else {
	    super.setValue(convertDouble((Double) value));
	}
    }
}