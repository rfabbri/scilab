/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Vincent COUVERT
 * Copyright (C) 2009 - DIGITEO - Clément DAVID
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.xcos.block.actions;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;

import org.scilab.modules.graph.ScilabGraph;
import org.scilab.modules.graph.actions.DefaultAction;
import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.hdf5.scilabTypes.ScilabDouble;
import org.scilab.modules.hdf5.scilabTypes.ScilabList;
import org.scilab.modules.hdf5.scilabTypes.ScilabString;
import org.scilab.modules.hdf5.scilabTypes.ScilabType;
import org.scilab.modules.xcos.block.SuperBlock;
import org.scilab.modules.xcos.graph.XcosDiagram;
import org.scilab.modules.xcos.utils.XcosMessages;

public final class SuperblockMaskCustomizeAction extends DefaultAction {

	/**
	 * Private constructor
	 * 
	 * @param scilabGraph
	 *            the associated graph
	 */
	private SuperblockMaskCustomizeAction(ScilabGraph scilabGraph) {
		super(XcosMessages.CUSTOMIZE, scilabGraph);
	}

	/**
	 * Create the menu associated with this action
	 * 
	 * @param scilabGraph
	 *            the associated graph
	 * @return the newly created menu
	 */
	public static MenuItem createMenu(ScilabGraph scilabGraph) {
		return createMenu(XcosMessages.CUSTOMIZE, null,
				new SuperblockMaskCustomizeAction(scilabGraph), null);
	}

	/**
	 * Function to be performed by this action.
	 * 
	 * @param e
	 *            The associated event
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		SuperBlock block = (SuperBlock) ((XcosDiagram) getGraph(e))
				.getSelectionCell();

		CustomizeFrame frame = new CustomizeFrame();
		CustomizeFrame.CustomizeFrameModel model = frame.getController()
				.getModel();
		model.setBlock(block);
		model.importFromBlock();
		frame.setVisible(true);
	}

	/**
	 * Frame used to customize fields and variables default values. DAC: this
	 * class is tightly coupled to Swing
	 */
	private static class CustomizeFrame extends JFrame {
		private CustomizeFrameControler controler;

		private javax.swing.JPanel buttonBlob;
		private javax.swing.JButton cancelButton;
		private javax.swing.JPanel customizeMainPanel;
		private javax.swing.JScrollPane customizeScrollPane;
		private javax.swing.JTabbedPane tabbedPane;
		private javax.swing.JTable defaultValueTable;
		private javax.swing.JPanel defaultValues;
		private javax.swing.JScrollPane defaultValuesScrollPane;
		private javax.swing.JButton delete;
		private javax.swing.JButton insert;
		private javax.swing.JPanel mainPanel;
		private javax.swing.JButton moveDown;
		private javax.swing.JButton moveUp;
		private javax.swing.JButton okButton;
		private javax.swing.JLabel rowLabel;
		private javax.swing.JPanel rowManagement;
		private javax.swing.JSpinner rowSpinner;
		private javax.swing.JPanel tableManagement;
		private javax.swing.JPanel validationPanel;
		private javax.swing.JTable varCustomizeTable;
		private javax.swing.JPanel varSettings;

		/**
		 * Constructor
		 */
		public CustomizeFrame() {
			setTitle(XcosMessages.MASK_TITLE);
			setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
			controler = new CustomizeFrameControler();
			initComponents();
		}

		/**
		 * @return The associated controller
		 */
		public CustomizeFrameControler getController() {
			return controler;
		}

		/**
		 * Construct the UI and install the listeners. NCSS: this is the UI
		 * constructor
		 */
		private void initComponents() {

			mainPanel = new javax.swing.JPanel();
			tabbedPane = new javax.swing.JTabbedPane();
			varSettings = new javax.swing.JPanel();
			customizeMainPanel = new javax.swing.JPanel();
			customizeScrollPane = new javax.swing.JScrollPane();
			varCustomizeTable = new javax.swing.JTable();
			tableManagement = new javax.swing.JPanel();
			insert = new javax.swing.JButton();
			delete = new javax.swing.JButton();
			buttonBlob = new javax.swing.JPanel();
			moveUp = new javax.swing.JButton();
			moveDown = new javax.swing.JButton();
			rowManagement = new javax.swing.JPanel();
			rowLabel = new javax.swing.JLabel();
			rowSpinner = new javax.swing.JSpinner();
			defaultValues = new javax.swing.JPanel();
			defaultValuesScrollPane = new javax.swing.JScrollPane();
			defaultValueTable = new javax.swing.JTable();
			validationPanel = new javax.swing.JPanel();
			okButton = new javax.swing.JButton();
			cancelButton = new javax.swing.JButton();

			setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);

			mainPanel.setLayout(new java.awt.BorderLayout());
			mainPanel.setBorder(BorderFactory.createEmptyBorder(2, 2, 2, 2));

			varSettings.setLayout(new javax.swing.BoxLayout(varSettings,
					javax.swing.BoxLayout.PAGE_AXIS));

			varCustomizeTable
					.setModel(controler.getModel().customizeTableModel);
			customizeScrollPane.setViewportView(varCustomizeTable);
			// setAutoCreateRowSorter is java 1.6
			// varCustomizeTable.setAutoCreateRowSorter(true);

			/* Update the default value table */
			varCustomizeTable.getModel().addTableModelListener(
					controler.updateValuesTable);

			/*
			 * Activate and deactivate insertion/deletion sensible
			 * buttons/spinner
			 */
			varCustomizeTable.getModel().addTableModelListener(
					controler.updateButtonsSensibleForModifications);

			/* Activate and deactivate selection sensible buttons */
			varCustomizeTable.getSelectionModel().addListSelectionListener(
					controler.updateButtonsSensibleForSelectionChange);

			customizeMainPanel.add(customizeScrollPane);

			tableManagement.setBorder(javax.swing.BorderFactory
					.createEmptyBorder(2, 2, 2, 2));
			tableManagement.setLayout(new java.awt.GridLayout(5, 1));

			insert.setMnemonic('n');
			insert.setText(XcosMessages.MASK_INSERT);
			tableManagement.add(insert);
			insert.addActionListener(controler.insertActionListener);

			delete.setMnemonic('l');
			delete.setText(XcosMessages.MASK_DELETE);
			tableManagement.add(delete);
			delete.addActionListener(controler.deleteActionListener);

			tableManagement.add(buttonBlob);

			moveUp.setMnemonic('u');
			moveUp.setText(XcosMessages.MASK_MOVEUP);
			tableManagement.add(moveUp);
			moveUp.addActionListener(controler.moveUpActionListener);

			moveDown.setMnemonic('w');
			moveDown.setText(XcosMessages.MASK_MOVEDOWN);
			tableManagement.add(moveDown);
			moveDown.addActionListener(controler.moveDownActionListener);

			customizeMainPanel.add(tableManagement);

			varSettings.add(customizeMainPanel);

			rowLabel.setText(XcosMessages.MASK_ROWS + " :");
			rowManagement.add(rowLabel);

			rowSpinner.setModel(new javax.swing.SpinnerNumberModel(1, 1,
					Integer.MAX_VALUE, 1));
			rowSpinner.setEditor(new javax.swing.JSpinner.NumberEditor(
					rowSpinner, "######0"));
			rowSpinner.setValue(varCustomizeTable.getModel().getRowCount());
			rowManagement.add(rowSpinner);
			rowSpinner.addChangeListener(controler.rowSpinnerChangeListener);

			varSettings.add(rowManagement);

			tabbedPane.addTab(XcosMessages.MASK_VARSETTINGS, varSettings);

			defaultValueTable.setModel(controler.getModel().valuesTableModel);
			defaultValuesScrollPane.setViewportView(defaultValueTable);

			// setAutoCreateRowSorter is java 1.6
			// defaultValueTable.setAutoCreateRowSorter(false);

			defaultValues.add(defaultValuesScrollPane);

			tabbedPane.addTab(XcosMessages.MASK_DEFAULTVALUES, defaultValues);

			mainPanel.add(tabbedPane, java.awt.BorderLayout.CENTER);

			okButton.setText(XcosMessages.OK);
			validationPanel.add(okButton);
			okButton.addActionListener(controler.okActionListener);

			cancelButton.setText(XcosMessages.CANCEL);
			validationPanel.add(cancelButton);
			cancelButton.addActionListener(controler.cancelActionListener);

			mainPanel.add(validationPanel, java.awt.BorderLayout.PAGE_END);

			add(mainPanel);

			pack();

			cancelButton.requestFocusInWindow();
			setResizable(false);
		}

		/**
		 * Implements the models used on the frame.
		 */
		private class CustomizeFrameModel {
			private SuperBlock block;

			/**
			 * Model used on the customize table.
			 */
			private final DefaultTableModel customizeTableModel = new javax.swing.table.DefaultTableModel(
					new Object[][] {new Object[] { 1,
							XcosMessages.MASK_WINTITLEVAR,
							XcosMessages.MASK_WINTITLE, false } },
					new String[] {XcosMessages.MASK_ROWS,
							XcosMessages.MASK_VARNAME,
							XcosMessages.MASK_VARDESC,
							XcosMessages.MASK_EDITABLE }) {
				private final Class[] types = new Class[] {
						java.lang.Integer.class, java.lang.String.class,
						java.lang.String.class, java.lang.Boolean.class };
				private final boolean[] canEdit = new boolean[] {false, true,
						true, true };

				public Class getColumnClass(int columnIndex) {
					return types[columnIndex];
				}

				public boolean isCellEditable(int rowIndex, int columnIndex) {
					if (rowIndex != 0) {
						return canEdit[columnIndex];
					}
					return false;
				}
			};

			/**
			 * Model used for the values table
			 */
			private final DefaultTableModel valuesTableModel = new javax.swing.table.DefaultTableModel(
					new Object[][] {new Object[] {XcosMessages.MASK_WINTITLE,
							"" } }, new String[] {XcosMessages.MASK_VARNAME,
							XcosMessages.MASK_VARVALUES }) {
				private final Class[] types = new Class[] {
						java.lang.String.class, java.lang.String.class };
				private final boolean[] canEdit = new boolean[] {false, true};

				public Class getColumnClass(int columnIndex) {
					return types[columnIndex];
				}

				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return canEdit[columnIndex];
				}
			};

			/**
			 * Default constructor
			 */
			protected CustomizeFrameModel() {
				// Does nothing as the fields are final.
			}

			/**
			 * @param block
			 *            This model associated block.
			 */
			public void setBlock(SuperBlock block) {
				this.block = block;
			}

			/**
			 * @return This model associated block.
			 */
			public SuperBlock getBlock() {
				return block;
			}

			/**
			 * Export the table models to the block exprs.
			 */
			public void exportToBlock() {
				/** Data vectors are typed when parsing */
				final Vector customModel = customizeTableModel.getDataVector();
				final Vector valuesModel = valuesTableModel.getDataVector();

				/* We have one content that is not a variable : Window Title */
				final int nbOfVar = valuesModel.size() - 1;

				final String[][] values = new String[nbOfVar][1];
				final String[][] varNames = new String[nbOfVar][1];
				final String[][] varDesc = new String[nbOfVar + 1][1];
				final ScilabList polFields = new ScilabList();

				/* Title */
				varDesc[0][0] = (String) ((Vector) valuesModel.get(0)).get(1);

				/* Other fields */
				for (int i = 0; i < nbOfVar; i++) {
					values[i][0] = (String) ((Vector) valuesModel.get(i + 1))
							.get(1);
					varNames[i][0] = (String) ((Vector) customModel.get(i + 1))
							.get(1);
					varDesc[i + 1][0] = (String) ((Vector) customModel
							.get(i + 1)).get(2);

					/*
					 * reconstruct pol fields TODO: what are these fields ?
					 */
					polFields.add(new ScilabString("pol"));
					polFields.add(new ScilabDouble(-1.0));
				}

				/* Construct fields from data */
				ScilabList exprs = new ScilabList() {
					{
						add(new ScilabString(values));
						add(new ScilabList() {
							{
								add(new ScilabString(varNames));
								add(new ScilabString(varDesc));
								add(polFields);
							}
						});
					}
				};

				getBlock().setExprs(exprs);
			}

			/**
			 * Import the model exprs to the table models.
			 */
			public void importFromBlock() {
				ScilabString values;
				ScilabString varNames;
				ScilabString varDesc;
				
				ScilabType rawExprs = getBlock().getExprs();
				DefaultTableModel customModel = customizeTableModel;
				DefaultTableModel valuesModel = valuesTableModel;

				/*
				 * rawExprs have to be typed as
				 *     list([],list([],"Set block parameters",list())) or as
				 *     list([""],list([""],"Set block parameters",list([""])))
				 */
				assert rawExprs instanceof ScilabList;
				ScilabList exprs = (ScilabList) rawExprs;
				
				assert (exprs.get(0) instanceof ScilabDouble) || (exprs.get(0) instanceof ScilabString);
				if (exprs.get(0) instanceof ScilabDouble) {
					values = new ScilabString("");
				} else { /* exprs.get(0) instanceof ScilabString) */
					values = (ScilabString) exprs.get(0); 
				}
				
				assert exprs.get(1) instanceof ScilabList;
				ScilabList lvalues = (ScilabList) exprs.get(1);
				
				assert (lvalues.get(0) instanceof ScilabDouble) || (lvalues.get(0) instanceof ScilabString);
				if (lvalues.get(0) instanceof ScilabDouble) {
					varNames = new ScilabString();
				} else { /* exprs.get(0) instanceof ScilabString) */
					varNames = (ScilabString) lvalues.get(0);
				}
				
				assert lvalues.get(1) instanceof ScilabString;
				varDesc = (ScilabString) lvalues.get(1);

				/*
				 * Check if the data are stored as columns or as row.
				 */
				if (varDesc.getHeight() >= varDesc.getWidth()) {

					/* Title */
					valuesModel.setValueAt(varDesc.getData()[0][0], 0, 1);

					/* Loop all over the data */
					for (int i = 1; i < varDesc.getHeight(); i++) {
						customModel.addRow(new Object[] {i + 1,
								varNames.getData()[i - 1][0],
								varDesc.getData()[i][0], true });
						valuesModel
								.setValueAt(values.getData()[i - 1][0], i, 1);
					}
				} else {
					/* Title */
					valuesModel.setValueAt(varDesc.getData()[0][0], 0, 1);

					/* Loop all over the data */
					for (int i = 1; i < varDesc.getHeight(); i++) {
						customModel.addRow(new Object[] {i + 1,
								varNames.getData()[0][i - 1],
								varDesc.getData()[0][i], true });
						valuesModel
								.setValueAt(values.getData()[0][i - 1], i, 1);
					}
				}
			}
		}

		/**
		 * Implement the action listeners for the frame
		 */
		private class CustomizeFrameControler {
			private CustomizeFrameModel model;

			private final ActionListener cancelActionListener = new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					dispose();
				}
			};

			private final ActionListener okActionListener = new ActionListener() {
				public void actionPerformed(ActionEvent arg0) {
					/* TODO: handle ok click when editing a cell. */
					model.exportToBlock();
					dispose();
				}
			};

			private final ChangeListener rowSpinnerChangeListener = new ChangeListener() {
				public void stateChanged(ChangeEvent e) {
					int rowCount = varCustomizeTable.getRowCount();
					int value = (Integer) rowSpinner.getModel().getValue();
					DefaultTableModel tableModel = model.customizeTableModel;

					for (; rowCount < value; rowCount++) {
						tableModel
								.addRow(new Object[] { rowCount + 1, "", true });
					}

					for (; rowCount > value; rowCount--) {
						tableModel.removeRow(rowCount - 1);
					}
				}
			};

			private final ActionListener moveDownActionListener = new ActionListener() {
				public void actionPerformed(ActionEvent arg0) {
					int selectedRow = varCustomizeTable.getSelectedRow();
					/**
					 * doesn't need to be checked as the operation doesn't
					 * depend on it
					 */
					Vector<Vector> data = model.customizeTableModel
							.getDataVector();

					if (selectedRow > 0
							&& selectedRow < varCustomizeTable.getRowCount() - 1) {
						/**
						 * doesn't need to be checked as the operation doesn't
						 * depend on it
						 */
						Vector current = (Vector) data.get(selectedRow);
						Vector next = (Vector) data.get(selectedRow + 1);

						/* Inverting data */
						data.set(selectedRow + 1, current);
						data.set(selectedRow, next);

						/* Update the index field */
						current.set(0, ((Integer) current.get(0)) + 1);
						next.set(0, ((Integer) next.get(0)) - 1);

						/* Keep the same row selected */
						varCustomizeTable.changeSelection(selectedRow + 1,
								varCustomizeTable.getSelectedColumn(), false,
								false);
					}
				}
			};

			private final ActionListener moveUpActionListener = new ActionListener() {
				public void actionPerformed(ActionEvent arg0) {
					int selectedRow = varCustomizeTable.getSelectedRow();
					/**
					 * doesn't need to be checked as the operation doesn't
					 * depend on it
					 */
					final Vector<Vector> data = model.customizeTableModel
							.getDataVector();

					if (selectedRow > 1) {
						/**
						 * doesn't need to be checked as the operation doesn't
						 * depend on it
						 */
						Vector current = (Vector) data.get(selectedRow);
						Vector next = (Vector) data.get(selectedRow - 1);

						/* Inverting data */
						data.set(selectedRow - 1, current);
						data.set(selectedRow, next);

						/* Update the index field */
						current.set(0, ((Integer) current.get(0)) - 1);
						next.set(0, ((Integer) next.get(0)) + 1);

						/* Keep the same row selected */
						varCustomizeTable.changeSelection(selectedRow - 1,
								varCustomizeTable.getSelectedColumn(), false,
								false);
					}
				}
			};

			private final ActionListener deleteActionListener = new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					int selected = varCustomizeTable.getSelectedRow();
					int nbOfRows = varCustomizeTable.getRowCount();
					boolean hasChanged = false;

					if (selected > 1) {
						model.customizeTableModel.removeRow(selected);
						varCustomizeTable.changeSelection(selected - 1, 1,
								false, false);
						hasChanged = true;
					} else if (nbOfRows > 1) {
						model.customizeTableModel.removeRow(nbOfRows - 1);
						varCustomizeTable.changeSelection(nbOfRows - 2, 1,
								false, false);
						hasChanged = true;
					}

					if (hasChanged) {
						if (selected > 1) {
							/* Update the others index */
							nbOfRows--;
							for (int i = selected; i < nbOfRows; i++) {
								model.customizeTableModel.setValueAt(i + 1, i,
										0);
							}
						}
					}
				}
			};

			private final ActionListener insertActionListener = new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					model.customizeTableModel.addRow(new Object[] {
							model.customizeTableModel.getRowCount() + 1, "",
							"", true });
					varCustomizeTable.changeSelection(model.customizeTableModel
							.getRowCount() - 1, 1, false, false);
				}
			};

			/**
			 * Update the buttons on selection change.
			 */
			private final ListSelectionListener updateButtonsSensibleForSelectionChange = new ListSelectionListener() {
				public void valueChanged(ListSelectionEvent e) {
					/* We cannot move up anymore */
					boolean isFirst = false;
					/* We cannot move down anymore */
					boolean isLast = false;

					int selectedRow = varCustomizeTable.getSelectedRow();
					int rowCount = varCustomizeTable.getRowCount();

					isFirst = selectedRow <= 1;
					isLast = selectedRow == rowCount - 1;

					moveUp.setEnabled(!isFirst);
					moveDown.setEnabled(!isLast);
				}
			};

			/**
			 * Update the buttons/spinner on modifications
			 */
			private final TableModelListener updateButtonsSensibleForModifications = new TableModelListener() {
				public void tableChanged(TableModelEvent e) {
					/* We cannot delete anymore */
					boolean canDelete = false;

					int rowCount = model.customizeTableModel.getRowCount();

					canDelete = rowCount > 1;

					delete.setEnabled(canDelete);
					rowSpinner.setValue(rowCount);
				}
			};

			/**
			 * Update the values table on change on the customize table.
			 */
			private final TableModelListener updateValuesTable = new TableModelListener() {
				public void tableChanged(TableModelEvent e) {
					final DefaultTableModel valuesModel = model.valuesTableModel;
					final DefaultTableModel customModel = model.customizeTableModel;
					int row = e.getFirstRow();
					int column = e.getColumn();

					switch (e.getType()) {
					case TableModelEvent.INSERT:
						valuesModel.addRow(new Object[] {
								customModel.getValueAt(row, 1), "" });
						break;

					case TableModelEvent.DELETE:
						valuesModel.removeRow(row);
						break;

					case TableModelEvent.UPDATE:
						if (column == 1) {
							valuesModel.setValueAt(customModel.getValueAt(row,
									1), row, 0);
						}
						break;

					default:
						break;
					}
				}
			};

			/**
			 * Cstr
			 */
			public CustomizeFrameControler() {
				model = new CustomizeFrameModel();
			}

			/**
			 * @return the model
			 */
			public CustomizeFrameModel getModel() {
				return model;
			}
		}
	}

	/**
	 * Ease the development of the UI (debug).
	 * 
	 * @param args
	 *            Unused
	 */
	public static void main(String[] args) {
		java.awt.EventQueue.invokeLater(new Runnable() {
			public void run() {
				new CustomizeFrame().setVisible(true);
			}
		});
	}
}