/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Vincent COUVERT
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

package org.scilab.modules.history_browser.actions;

import java.lang.reflect.InvocationTargetException;

import javax.swing.ImageIcon;

import org.scilab.modules.commons.gui.ScilabKeyStroke;
import org.scilab.modules.gui.bridge.menuitem.SwingScilabMenuItem;
import org.scilab.modules.gui.events.callback.CommonCallBack;
import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.gui.menuitem.ScilabMenuItem;
import org.scilab.modules.gui.pushbutton.PushButton;
import org.scilab.modules.gui.pushbutton.ScilabPushButton;
import org.scilab.modules.gui.utils.ScilabSwingUtilities;
import org.scilab.modules.history_browser.CommandHistory;
import org.scilab.modules.history_browser.CommandHistoryMessages;

/**
 * Manage Cut Actions
 * @author Vincent COUVERT
 */
public final class CutAction extends CommonCallBack {

    private static final long serialVersionUID = 1L;

    private static final String LABEL = CommandHistoryMessages.CUT;
    private static final String ICON = ScilabSwingUtilities.findIcon("edit-cut");
    private static final char MNEMONIC = 'U';

    private static final String KEY = "OSSCKEY X";
    private static final String CUT = "Cut";

    /**
     * Constructor
     */
    public CutAction() {
        super("");
    }

    /**
     * Register the key for the action
     */
    public static void registerKeyAction() {
        CommandHistory.getTree().getActionMap().put(CUT, new CutAction());
        CommandHistory.getTree().getInputMap().put(ScilabKeyStroke.getKeyStroke(KEY), CUT);
    }

    /**
     * Create the associated menu
     * @return the menu
     */
    public static MenuItem createMenuItem() {
        MenuItem menuItem = ScilabMenuItem.createMenuItem();
        menuItem.setText(LABEL);
        menuItem.setMnemonic(MNEMONIC);
        menuItem.setCallback(getCallBack());
        ((SwingScilabMenuItem) menuItem.getAsSimpleMenuItem()).setIcon(new ImageIcon(ICON));
        return menuItem;
    }

    /**
     * Create the associated button
     * @return the button
     */
    public static PushButton createPushButton() {
        PushButton pushButton = ScilabPushButton.createPushButton();
        pushButton.setIcon(ICON);
        pushButton.setToolTipText(LABEL);
        pushButton.setCallback(getCallBack());
        return pushButton;
    }

    /**
     * Create a new class instance
     * @return the instance
     */
    private static CommonCallBack getCallBack() {
        CommonCallBack callback = null;
        try {
            callback = CutAction.class.getConstructor().newInstance();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        } catch (SecurityException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
        return callback;
    }

    /**
     * Action!
     * @see org.scilab.modules.gui.events.callback.CallBack#callBack()
     */
    @Override
    public void callBack() {
        CommonCallBack copyAction = new CopyAction();
        copyAction.callBack();
        CommonCallBack deleteAction = new DeleteAction();
        deleteAction.callBack();
    }
}
