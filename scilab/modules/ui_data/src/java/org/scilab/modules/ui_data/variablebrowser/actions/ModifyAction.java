/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Vincent COUVERT
 * Copyright (C) 2013 - S/E - Sylvestre Ledru
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

package org.scilab.modules.ui_data.variablebrowser.actions;

import org.scilab.modules.ui_data.variablebrowser.SwingScilabVariableBrowser;
import java.lang.reflect.InvocationTargetException;
import java.awt.event.ActionEvent;
import javax.swing.ImageIcon;
import javax.swing.KeyStroke;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import javax.swing.JTable;

import org.scilab.modules.ui_data.utils.UiDataMessages;
import org.scilab.modules.ui_data.BrowseVar;

import static org.scilab.modules.action_binding.highlevel.ScilabInterpreterManagement.asynchronousScilabExec;

import org.scilab.modules.action_binding.highlevel.ScilabInterpreterManagement.InterpreterException;

import org.scilab.modules.gui.bridge.pushbutton.SwingScilabPushButton;
import org.scilab.modules.gui.bridge.menuitem.SwingScilabMenuItem;
import org.scilab.modules.gui.events.callback.CommonCallBack;
import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.gui.menuitem.ScilabMenuItem;
import org.scilab.modules.gui.pushbutton.PushButton;
import org.scilab.modules.gui.pushbutton.ScilabPushButton;
import org.scilab.modules.gui.utils.ScilabSwingUtilities;

/**
 * Manage Modify Actions
 * @author Vincent COUVERT
 */
public final class ModifyAction extends CommonCallBack {

    private static final long serialVersionUID = 1L;

    private static ImageIcon icon = new ImageIcon(ScilabSwingUtilities.findIcon("rrze_table"));

    private static final char MNEMONIC = 'M';

    private static final String KEY = "MODIFY";
    //    private static final String SUPPR = "Suppr";

    private final SwingScilabVariableBrowser variableBrowser;

    /**
     * Constructor
     */
    public ModifyAction(SwingScilabVariableBrowser variableBrowser) {
        super("");
        this.variableBrowser = variableBrowser;
    }

    /**
     * Create a button for a tool bar
     * @param title tooltip for the button
     * @return the button
     */
    public static PushButton createButton(SwingScilabVariableBrowser variableBrowser, String title) {
        PushButton button = ScilabPushButton.createPushButton();
        ((SwingScilabPushButton) button.getAsSimplePushButton()).addActionListener(new ModifyAction(variableBrowser));
        button.setToolTipText(title);
        ((SwingScilabPushButton) button.getAsSimplePushButton()).setIcon(icon);

        return button;
    }

    /**
     * Create the associated menu
     * @return the menu
     */
    public MenuItem createMenuItem() {
        MenuItem menuItem = ScilabMenuItem.createMenuItem();
        menuItem.setText(UiDataMessages.MODIFY + " '" + getSelectedVariable() + "'");
        menuItem.setMnemonic(MNEMONIC);
        menuItem.setCallback(this);
        ((SwingScilabMenuItem) menuItem.getAsSimpleMenuItem()).setIcon(icon);
        return menuItem;
    }


    /**
     * Action!
     * @see org.scilab.modules.gui.events.callback.CallBack#callBack()
     */
    @Override
    public void callBack() {
        variableBrowser.startEditVar(getSelectedVariableVisibility(), getSelectedVariable());

    }

    private String getSelectedVariable() {

        int clickedRow = variableBrowser.getTable().getSelectedRow();
        // Does nothing if no variable selected
        if (clickedRow != -1) {
            return variableBrowser.getTable().getValueAt(clickedRow, BrowseVar.NAME_COLUMN_INDEX).toString();
        }
        return "";
    }

    private String getSelectedVariableVisibility() {

        int clickedRow = variableBrowser.getTable().getSelectedRow();
        // Does nothing if no variable selected
        if (clickedRow != -1) {
            return variableBrowser.getTable().getValueAt(clickedRow, BrowseVar.VISIBILITY_COLUMN_INDEX).toString();
        }
        return "";
    }
}
