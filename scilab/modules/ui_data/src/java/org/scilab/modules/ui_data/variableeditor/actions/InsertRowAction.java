/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Calixte DENIZET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

package org.scilab.modules.ui_data.variableeditor.actions;

import javax.swing.ImageIcon;
import javax.swing.JMenuItem;
import javax.swing.JTable;

import org.scilab.modules.gui.bridge.pushbutton.SwingScilabPushButton;
import org.scilab.modules.gui.events.callback.CommonCallBack;
import org.scilab.modules.gui.pushbutton.PushButton;
import org.scilab.modules.gui.pushbutton.ScilabPushButton;
import org.scilab.modules.gui.utils.ScilabSwingUtilities;
import org.scilab.modules.ui_data.datatable.SwingEditvarTableModel;
import org.scilab.modules.ui_data.variableeditor.TableVariableEditor;

/**
 * Set Precision Action class
 * @author Calixte DENIZET
 */
@SuppressWarnings(value = { "serial" })
public final class InsertRowAction extends CommonCallBack {

    private final JTable table;

    /**
     * Constructor
     * @param editor the editor
     * @param name the name of the action
     */
    public InsertRowAction(JTable table, String name) {
        super(name);
        this.table = table;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void callBack() {
        int row = ((TableVariableEditor) table).getPopupRow();
        SwingEditvarTableModel model = (SwingEditvarTableModel) table.getModel();
        model.insertRow(row);
        table.setRowSelectionInterval(row, row);
    }

    /**
     * Create a button for a tool bar
     * @param editor the associated editor
     * @param title tooltip for the button
     * @return the button
     */
    public static PushButton createButton(JTable table, String title) {
        PushButton button = ScilabPushButton.createPushButton();
        ((SwingScilabPushButton) button.getAsSimplePushButton()).addActionListener(new InsertRowAction(table, title));
        button.setToolTipText(title);
        ImageIcon imageIcon = new ImageIcon(ScilabSwingUtilities.findIcon("short"));
        ((SwingScilabPushButton) button.getAsSimplePushButton()).setIcon(imageIcon);

        return button;
    }

    /**
     * Create a menu item
     * @param editor the associated editor
     * @param title the menu title
     * @return the menu item
     */
    public static JMenuItem createMenuItem(JTable table, String title) {
        JMenuItem mi = new JMenuItem(title);
        mi.addActionListener(new InsertRowAction(table, title));

        return mi;
    }
}
