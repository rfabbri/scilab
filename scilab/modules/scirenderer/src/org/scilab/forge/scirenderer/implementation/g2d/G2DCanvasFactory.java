/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009-2011 - DIGITEO - Pierre Lando
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 */

package org.scilab.forge.scirenderer.implementation.g2d;

import java.awt.Graphics2D;

import org.scilab.forge.scirenderer.Canvas;

/**
 * @author Pierre Lando
 */
public final class G2DCanvasFactory {

    /**
     * Private constructor.
     * This is an utility class.
     */
    private G2DCanvasFactory() {

    }

    /**
     * Create a canvas from an auto drawable object.
     * @param autoDrawable the auto drawable object.
     * @return a canvas based on the given auto drawable object.
     */
    public static G2DCanvas createCanvas(Graphics2D g2d, int width, int height) {
        return new G2DCanvas(g2d, width, height);
    }
}
