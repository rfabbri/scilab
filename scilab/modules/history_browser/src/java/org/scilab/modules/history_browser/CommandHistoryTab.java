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

package org.scilab.modules.history_browser;

import org.scilab.modules.gui.bridge.tab.SwingScilabTab;
import org.scilab.modules.gui.tabfactory.ScilabTabFactory;
import org.scilab.modules.gui.utils.ClosingOperationsManager;
import org.scilab.modules.gui.utils.WindowsConfigurationManager;

/**
 * Class to create Command History tab
 * @author Calixte DENIZET
 */
public class CommandHistoryTab {

    /**
     * @param uuid the uuid to restore
     * @return a new Command History tab
     */
    public static SwingScilabTab getCommandHistoryInstance(String uuid) {
        SwingScilabTab cmdh = CommandHistory.createCommandHistoryTab();
        ScilabTabFactory.getInstance().addToCache(cmdh);

        ClosingOperationsManager.registerClosingOperation(cmdh, new ClosingOperationsManager.ClosingOperation() {

                public boolean canClose() {
                    return true;
                }

                public void destroy() {
                    CommandHistory.close();
                }

                public String askForClosing() {
                    return null;
                }
            });

        ClosingOperationsManager.addDependencyWithRoot(cmdh);

        return cmdh;
    }
}