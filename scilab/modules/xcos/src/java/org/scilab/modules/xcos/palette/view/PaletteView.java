/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Clément DAVID
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.xcos.palette.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Rectangle;

import javax.swing.JPanel;
import javax.swing.Scrollable;
import javax.swing.SwingConstants;

import org.scilab.modules.xcos.palette.Palette;
import org.scilab.modules.xcos.utils.XcosConstants;

/**
 * Implement a view of a block category.
 * 
 * As the JScrollPane doesn't allow a to specify it's associated layout, we have
 * to use a {@link #mainArea} to perform what we want there. Never use the
 * {@link JScrollPane#add(java.awt.Component)} on this class but use
 * {@link #getMainArea()} then {@link JPanel#add(java.awt.Component)} instead.
 */
public class PaletteView extends JPanel implements Scrollable {
	private Palette controller;
	private boolean isLoaded;

	/**
	 * Default constructor
	 * 
	 * @param controller
	 *            The associated controller
	 */
	public PaletteView(Palette controller) {
		this.controller = controller;
		initComponents();
	}

	/** Setup component */
	private void initComponents() {
		setBackground(Color.WHITE);
		setLayout(new ModifiedFlowLayout(FlowLayout.LEADING,
				XcosConstants.PALETTE_HMARGIN, XcosConstants.PALETTE_VMARGIN));
		setMinimumSize(new Dimension(
				(XcosConstants.PALETTE_BLOCK_WIDTH + XcosConstants.PALETTE_HMARGIN),
				XcosConstants.PALETTE_BLOCK_HEIGHT
						+ XcosConstants.PALETTE_VMARGIN));
	}

	/**
	 * @return true if the view is already loaded
	 */
	public boolean isLoaded() {
		return isLoaded;
	}

	/**
	 * This class update the status of the view. If you want to save memory,
	 * unload the view when hidden.
	 * 
	 * @param b
	 *            the load status
	 */
	public void setLoaded(boolean b) {
		if (!b) {
			removeAll();
		}

		isLoaded = b;
	}

	/**
	 * @return the localized message
	 * @see java.awt.Component#toString()
	 */
	@Override
	public String toString() {
		return controller.getModel().toString();
	}

	/**
	 * @return The prefered Scrollable dimension
	 * @see javax.swing.Scrollable#getPreferredScrollableViewportSize()
	 */
	public Dimension getPreferredScrollableViewportSize() {
		return getPreferredSize();
	}

	/**
	 * @param visibleRect
	 *            The view area visible within the viewport
	 * @param orientation
	 *            Either SwingConstants.VERTICAL or SwingConstants.HORIZONTAL.
	 * @param direction
	 *            Less than zero to scroll up/left, greater than zero for
	 *            down/right.
	 * @return The "block" increment for scrolling in the specified direction.
	 *         This value should always be positive.
	 * @see javax.swing.Scrollable#getScrollableBlockIncrement(java.awt.Rectangle,
	 *      int, int)
	 */
	public int getScrollableBlockIncrement(Rectangle visibleRect,
			int orientation, int direction) {
		if (orientation == SwingConstants.VERTICAL) {
			return XcosConstants.PALETTE_BLOCK_HEIGHT
					+ XcosConstants.PALETTE_VMARGIN;
		} else {
			return XcosConstants.PALETTE_BLOCK_WIDTH
					+ XcosConstants.PALETTE_HMARGIN;
		}
	}

	/**
	 * @return always false
	 * @see javax.swing.Scrollable#getScrollableTracksViewportHeight()
	 */
	public boolean getScrollableTracksViewportHeight() {
		return false;
	}

	/**
	 * @return always true
	 * @see javax.swing.Scrollable#getScrollableTracksViewportWidth()
	 */
	public boolean getScrollableTracksViewportWidth() {
		return true;
	}

	/**
	 * @param visibleRect
	 *            The view area visible within the viewport
	 * @param orientation
	 *            Either SwingConstants.VERTICAL or SwingConstants.HORIZONTAL.
	 * @param direction
	 *            Less than zero to scroll up/left, greater than zero for
	 *            down/right.
	 * @return PALETTE_BLOCK_HEIGHT or PALETTE_BLOCK_WIDTH depending on
	 *         direction.
	 * @see javax.swing.Scrollable#getScrollableUnitIncrement(java.awt.Rectangle,
	 *      int, int)
	 */
	public int getScrollableUnitIncrement(Rectangle visibleRect,
			int orientation, int direction) {
		if (orientation == SwingConstants.VERTICAL) {
			return XcosConstants.PALETTE_BLOCK_HEIGHT;
		} else {
			return XcosConstants.PALETTE_BLOCK_WIDTH;
		}
	}
}