/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - Calixte DENIZET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.xpad;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.Shape;

import javax.swing.text.JTextComponent;
import javax.swing.text.DefaultHighlighter;
import javax.swing.text.Highlighter;
import javax.swing.text.Element;
import javax.swing.text.Position;
import javax.swing.text.View;
import javax.swing.text.BadLocationException;

import org.scilab.modules.xpad.utils.ConfigXpadManager;

/**
 * Useful to match opening and closing keywords from left to right or from right to left
 * @author Calixte DENIZET
 */
public class MatchingBlockManager {

    private ScilabDocument doc;
    private ScilabEditorPane pane;
    private MatchingBlockScanner scanner;
    private Highlighter highlighter;
    private MatchingBlockScanner.MatchingPositions smpos;
    private Highlighter.HighlightPainter kwPainter;
    private Highlighter.HighlightPainter ocPainter;
    private Object first;
    private Object second;
    private boolean insideOc;
    private boolean insideKw;
    private boolean lr;
    private MouseOverMatcher mouseover;

    /**
     * Constructor
     * @param doc the doc to highlight
     * @param pane the ScilabEditorPane associated with this Manager
     * @param lr if true the matching is from left to right
     * @param highlighter the highlighter to use
     */
    public MatchingBlockManager(ScilabDocument doc, ScilabEditorPane pane, boolean lr, Highlighter highlighter) {
        this.doc = doc;
        this.pane = pane;
        this.scanner = new MatchingBlockScanner(doc);
        this.highlighter = highlighter;
        this.lr = lr;
        setPainterForOpenClose(true, Color.orange);
        setPainterForKeywords(true, Color.orange);
    }

    /**
     * Set the painter for the matching open/close keywords (such as '('/')' or '['/']').
     * The contents between the matchings is highlighted.
     * @param filled true if a filled rectangle must be used to highlight
     * @param color the color of the painter
     **/
    public void setPainterForOpenClose(boolean filled, Color color) {
        this.insideOc = true;
        update();
        ocPainter = new InsideLinePainter(filled, color);
    }

    /**
     * Set the painter for the matching open/close keywords (such as '('/')' or '['/']').
     * The matchings are highlighted.
     * @param type one of the three values : ScilabKeywordsPainter.FILLED
     *                                       ScilabKeywordsPainter.UNDERLINED
     *                                       ScilabKeywordsPainter.FRAMED
     * @param color the color of the painter
     **/
    public void setPainterForOpenClose(int type, Color color) {
        this.insideOc = false;
        update();
        ocPainter = new ScilabKeywordsPainter(color, type);
    }

    /**
     * Set the painter for the matching open/close keywords (such as '('/')' or '['/']').
     * Properties are found in the file xpadConfiguration.xml
     * The contents between the matchings is highlighted.
     **/
    public void setPainterForOpenClose() {
        Parameters param = ConfigXpadManager.getDefaultForMatcher("OpenCloseHighlighter");
        if (param.inside) {
            boolean b = param.type == ScilabKeywordsPainter.FILLED;
            setPainterForOpenClose(b, param.color);
        } else {
            setPainterForOpenClose(param.type, param.color);
        }
	if (param.onmouseover) {
	    activateMouseOver();
	}
    }

    /**
     * Set the painter for the matching keywords (such as 'function' and 'endfunction').
     * The contents between the matchings is highlighted.
     * @param filled true if a filled rectangle must be used to highlight
     * @param color the color of the painter
     **/
    public void setPainterForKeywords(boolean filled, Color color) {
        this.insideKw = true;
        update();
        kwPainter = new InsideLinePainter(filled, color);
    }

    /**
     * Set the painter for the matching keywords (such as 'function' and 'endfunction').
     * The matchings are highlighted.
     * @param type one of the three values : ScilabKeywordsPainter.FILLED
     *                                       ScilabKeywordsPainter.UNDERLINED
     *                                       ScilabKeywordsPainter.FRAMED
     * @param color the color of the painter
     **/
    public void setPainterForKeywords(int type, Color color) {
        this.insideKw = false;
        update();
        kwPainter = new ScilabKeywordsPainter(color, type);
    }

    /**
     * Set the painter for the matching keywords.
     * Properties are found in the file xpadConfiguration.xml
     * The contents between the matchings is highlighted.
     **/
    public void setPainterForKeywords() {
        Parameters param = ConfigXpadManager.getDefaultForMatcher("KeywordsHighlighter");
        if (param.inside) {
            boolean b = param.type == ScilabKeywordsPainter.FILLED;
            setPainterForKeywords(b, param.color);
        } else {
            setPainterForKeywords(param.type, param.color);
        }
	if (param.onmouseover) {
	    activateMouseOver();
	}
    }

    /** 
     * Set the defaults from xpadConfiguration.xml
     */
    public void setDefaults() {
	setPainterForKeywords();
	setPainterForOpenClose();
    }

    /**
     * Activate this MatchingBlockManager to listen to the KeywordEvent generate by a MouseOver.
     */
    public void activateMouseOver() {
        if (mouseover == null) {
            mouseover = new MouseOverMatcher();
        }
        pane.addKeywordListener(mouseover);
    }

    /**
     * Desactivate this MatchingBlockManager to listen to the KeywordEvent generate by a MouseOver.
     */
    public void desactivateMouseOver() {
        if (mouseover != null) {
            pane.removeKeywordListener(mouseover);
            mouseover = null;
        }
    }

    /**
     * Remove the highlights if they exist.
     */
    private void update() {
        if (first != null) {
            highlighter.removeHighlight(first);
            first = null;
        }
        if (second != null) {
            highlighter.removeHighlight(second);
            second = null;
        }
    }

    /**
     * Search the matching keywords
     * @param tok the type of the token at the position pos in the document
     * @param pos the positon in the doc
     */
    public void searchMatchingBlock(int tok, int pos) {
        MatchingBlockScanner.MatchingPositions mpos = null;
        if (ScilabLexerConstants.isMatchable(tok)) {
            mpos = scanner.getMatchingBlock(pos, lr);
        }
        if (mpos != this.smpos) {
            this.smpos = mpos;
            if (first != null) {
                highlighter.removeHighlight(first);
                if (second != null) {
                    highlighter.removeHighlight(second);
                }
            }
            if (mpos != null && ScilabLexerConstants.isOpenClose(tok)) {
                createHighlights(mpos, insideOc, ocPainter);
            } else if (mpos != null) {
                createHighlights(mpos, insideKw, kwPainter);
            }
        }
    }

    /**
     * Create the highlights
     * @param mpos the position of the matching keywords
     * @param inside true if we look at the contents between the keywords
     * @param hp the painter to use
     */
    private void createHighlights(MatchingBlockScanner.MatchingPositions mpos,
                                  boolean inside, Highlighter.HighlightPainter hp) {
        try {
            if (!inside) {
                first = highlighter.addHighlight(mpos.firstB, mpos.firstE, hp);
                second = highlighter.addHighlight(mpos.secondB, mpos.secondE, hp);
            } else {
                if (lr) {
                    first = highlighter.addHighlight(mpos.firstE, mpos.secondB + 1, hp);
                } else {
                    first = highlighter.addHighlight(mpos.secondE, mpos.firstB + 1, hp);
                }
            }
        } catch (BadLocationException e) {
            System.err.println(e);
        }
    }

    /**
     * Inner class used to retriev infos from xpadConfiguration.xml
     */
    public static class Parameters {

        /**
         * The color
         */
        public Color color;

        /**
         * Inside or not
         */
        public boolean inside;

        /**
         * The type
         */
        public int type;

        /**
         * The onmouseover
         */
        public boolean onmouseover;

        /**
         * Constructor
         * @param color the color
         * @param inside inside or not
         * @param type the type
	 * @param onmouseover a boolean
         */
        public Parameters(Color color, boolean inside, int type, boolean onmouseover) {
            this.color = color;
            this.inside = inside;
            this.type = type;
	    this.onmouseover = onmouseover;
        }
    }

    /**
     * Inner class to highlight matching keywords
     */
    public class ScilabKeywordsPainter extends DefaultHighlighter.DefaultHighlightPainter {

        /**
         * FILLED
         */
        public static final int FILLED = 0;

        /**
         * UNDERLINED
         */
        public static final int UNDERLINED = 1;

        /**
         * FRAMED
         */
        public static final int FRAMED = 2;

        private Color color;
        private int type;

        /**
         * Constructor
         * @param color the color to paint
         * @param type must be FILLED, UNDERLINED or FRAMED
         */
        public ScilabKeywordsPainter(Color color, int type) {
            super(color);
            this.color = color;
            this.type = type;
        }

        /**
         * paintLayer
         * @param g Graphics
         * @param offs0 the beginning
         * @param offs1 the end
         * @param bounds the bounds
         * @param c the text component where to paint
         * @param view the view to use
         * @return the shape containg the highlighted text
         */
        public Shape paintLayer(Graphics g, int offs0, int offs1,
                                Shape bounds, JTextComponent c, View view) {
            try {
                Rectangle r = (Rectangle) view.modelToView(offs0, Position.Bias.Forward,
                                                           offs1, Position.Bias.Backward, bounds);
                g.setColor(color);

                switch (type) {
                case FILLED :
                    g.fillRect(r.x, r.y, r.width, r.height);
                    return r;
                case UNDERLINED :
                    g.drawLine(r.x, r.y + r.height - 1, r.x + r.width - 1, r.y + r.height - 1);
                    return r;
                case FRAMED :
                    g.drawRect(r.x, r.y, r.width - 1, r.height - 1);
                    return r;
                default :
                    g.fillRect(r.x, r.y, r.width, r.height);
                    return r;
                }
            } catch (BadLocationException e) {
                return null;
            }
        }
    }

    /**
     * Inner class to highlight the content inside two keywords.
     * The highlight depends on the position of the content.
     */
    class InsideLinePainter implements Highlighter.HighlightPainter {

        private boolean filled;
        private Color color;

        /**
         * Constructor
         * @param filled if the highlighted rectangle must be filled
         * @param color the color to paint
         */
        protected InsideLinePainter(boolean filled, Color color) {
            this.filled = filled;
            this.color = color;
        }

        /**
         * Implements a strategy to render contents depending on the position of these
         * @param g Graphics
         * @param pos0 the beginning
         * @param pos1 the end
         * @param bounds the bounds
         * @param c the text component where to paint
         */
        public void paint(Graphics g, int pos0, int pos1, Shape bounds, JTextComponent c) {
            try {
                Rectangle alloc = bounds.getBounds();
                Rectangle p0 = c.modelToView(pos0);
                Rectangle p1 = c.modelToView(pos1 - 1);

                g.setColor(color);

                if (p0.y == p1.y) {
                    Rectangle r = p0.union(p1);
                    if (filled) {
                        g.fillRect(r.x, r.y, r.width, r.height);
                    } else {
                        g.drawRect(r.x, r.y, r.width - 1, r.height - 1);
                    }
                } else {
                    Element root = doc.getDefaultRootElement();
                    int line0 = root.getElementIndex(pos0);
                    int line1 = root.getElementIndex(pos1);
                    int offs0 = pos0;
                    int offs1 = pos1;
                    if (line0 != line1) {
                        Element line = root.getElement(line0 + 1);
                        offs0 = line.getStartOffset();
                        line = root.getElement(line1 - 1);
                        offs1 = line.getEndOffset();
                        p0 = c.modelToView(offs0);
                        p1 = c.modelToView(offs1);
                        if (filled) {
                            g.fillRect(alloc.x, p0.y, alloc.width, p1.y - p0.y);
                        } else {
                            g.drawRect(alloc.x, p0.y, alloc.width - 1, p1.y - p0.y - 1);
                        }
                    } else {
                        /* This part of the code has been copied (for the filling) from DefaultHighlighter.java */
                        int w = alloc.x + alloc.width - p0.x;
                        if (filled) {
                            g.fillRect(p0.x, p0.y, w, p0.height);
                            if ((p0.y + p0.height) != p1.y) {
                                g.fillRect(alloc.x, p0.y + p0.height, alloc.width,
                                           p1.y - (p0.y + p0.height));
                            }
                            g.fillRect(alloc.x, p1.y, (p1.x - alloc.x), p1.height);
                        } else {
                            g.drawRect(p0.x, p0.y, w - 1, p0.height - 1);
                            if ((p0.y + p0.height) != p1.y) {
                                g.drawRect(alloc.x, p0.y + p0.height, alloc.width - 1,
                                           p1.y - (p0.y + p0.height) - 1);
                            }
                            g.drawRect(alloc.x, p1.y, (p1.x - alloc.x) - 1, p1.height - 1);
                        }
                    }
                }
            } catch (BadLocationException e) { }
        }
    }

    /**
     * Inner class to highlight on a KeywordEvent generated by a ONMOUSEOVER
     */
    class MouseOverMatcher extends KeywordAdaptater.MouseOverAdaptater {

        /**
         * What to do when the event occured
         * @param e the event
         */
        public void caughtKeyword(KeywordEvent e) {
            if (lr) {
                searchMatchingBlock(e.getType(), e.getStart());
            } else {
                searchMatchingBlock(e.getType(), e.getStart() + e.getLength());
            }
        }
    }
}