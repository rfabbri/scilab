/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2009 - DIGITEO - Vincent COUVERT
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.graph.actions;

import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

import javax.swing.JComponent;
import javax.swing.KeyStroke;

import org.scilab.modules.graph.ScilabGraph;
import org.scilab.modules.graph.actions.base.DefaultAction;
import org.scilab.modules.graph.utils.ScilabGraphMessages;
import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.gui.pushbutton.PushButton;

/**
 * Zoom management
 */
public class ZoomInAction extends DefaultAction {
	/** Name of the action */
	public static final String NAME = ScilabGraphMessages.ZOOM_IN;
	/** Icon name of the action */
	public static final String SMALL_ICON = "list-add.png";
	/** Mnemonic key of the action */
	public static final int MNEMONIC_KEY = KeyEvent.VK_PLUS;
	/** Accelerator key for the action */
	public static final int ACCELERATOR_KEY = Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();
	
	/**
	 * Implement custom mouse handling for the zoom
	 */
	private static final class CustomMouseWheelListener implements MouseWheelListener {
		private final ScilabGraph scilabGraph;
		
		/**
		 * Default constructor
		 * @param scilabGraph the current graph
		 */
		public CustomMouseWheelListener(ScilabGraph scilabGraph) {
			this.scilabGraph = scilabGraph;
		}
		
		/**
		 * When the wheel is used
		 * @param e the parameters
		 * @see java.awt.event.MouseWheelListener#mouseWheelMoved(java.awt.event.MouseWheelEvent)
		 */
		public void mouseWheelMoved(MouseWheelEvent e) {
			if ((e.getModifiers() & ACCELERATOR_KEY) != 0) {
				if (e.getWheelRotation() < 0) {
					scilabGraph.getAsComponent().zoomIn();
				}
			}
		}
	}
	
	/**
	 * Constructor
	 * @param scilabGraph corresponding Scilab Graph
	 */
	public ZoomInAction(ScilabGraph scilabGraph) {
		super(scilabGraph);
		
		MouseWheelListener mouseListener = new CustomMouseWheelListener(scilabGraph);
		scilabGraph.getAsComponent().getViewport().addMouseWheelListener(mouseListener);
		
		// On the KeyPad
		scilabGraph.getAsComponent().registerKeyboardAction(
				this, "zoomIn", KeyStroke.getKeyStroke(KeyEvent.VK_ADD, ACCELERATOR_KEY),
				JComponent.WHEN_IN_FOCUSED_WINDOW);
		
		// When the PLUS key is accessible with the shift key.
		scilabGraph.getAsComponent().registerKeyboardAction(
				this, "zoomIn", KeyStroke.getKeyStroke(KeyEvent.VK_PLUS, ACCELERATOR_KEY | InputEvent.SHIFT_DOWN_MASK), 
				JComponent.WHEN_IN_FOCUSED_WINDOW);
	}

	/**
	 * Create a button for a graph toolbar
	 * @param scilabGraph corresponding Scilab Graph
	 * @return the button
	 */
	public static PushButton zoominButton(ScilabGraph scilabGraph) {
		return createButton(scilabGraph, ZoomInAction.class);
	}

	/**
	 * Create a menu for a graph menubar
	 * @param scilabGraph corresponding Scilab Graph
	 * @return the menu
	 */
	public static MenuItem zoominMenu(ScilabGraph scilabGraph) {		
		return createMenu(scilabGraph, ZoomInAction.class);
	}

	/**
	 * Action associated
	 * @param e the event
	 * @see org.scilab.modules.gui.events.callback.CallBack#actionPerformed(java.awt.event.ActionEvent)
	 */
	public void actionPerformed(ActionEvent e) {
		getGraph(e).getAsComponent().zoomIn();
	}
}