/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - Calixte DENIZET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.gui.tabfactory;

import org.scilab.modules.gui.bridge.tab.SwingScilabTab;
import org.scilab.modules.gui.helpbrowser.ScilabHelpBrowser;
import org.scilab.modules.gui.utils.ClosingOperationsManager;
import org.scilab.modules.gui.utils.WindowsConfigurationManager;

/**
 * Class to create SciNotes instances
 * @author Calixte DENIZET
 */
public class HelpBrowserTab {

    /**
     * @param uuid the uuid to restore
     * @return a new SciNotes instance
     */
    public static SwingScilabTab getHelpBrowserInstance() {
        final SwingScilabTab hb = ScilabHelpBrowser.createHelpBrowserTab();
        ScilabTabFactory.getInstance().addToCache(hb);

        ClosingOperationsManager.registerClosingOperation(hb, new ClosingOperationsManager.ClosingOperation() {

                public boolean canClose() {
                    return true;
                }

                public void destroy() {
                    ScilabHelpBrowser.closeHelpBrowser();
                }

                public String askForClosing() {
                    return null;
                }
            });

        ClosingOperationsManager.addDependencyWithRoot(hb);

        return hb;
    }
}