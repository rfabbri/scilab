/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Antoine ELIAS
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.xcos.io.scicos;

import java.util.ArrayList;
import java.util.EnumMap;
import java.util.List;
import java.util.Map;

import org.scilab.modules.types.scilabTypes.ScilabDouble;
import org.scilab.modules.xcos.block.BasicBlock;
import org.scilab.modules.xcos.port.BasicPort;
import org.scilab.modules.xcos.port.Orientation;

import com.mxgraph.model.mxICell;

/**
 * Convert BasicBlock pure objects to a mixed BasicBlock objects (update the
 * scicos informations)
 */
public final class BasicBlockInfo {
	/**
	 * This class is a static singleton.
	 */
	private BasicBlockInfo() { }

	/**
	 * Get all the ids.
	 * 
	 * @param ports
	 *            the ports
	 * @return array of links id
	 */
	protected static ScilabDouble getAllLinkId(List< ? extends BasicPort> ports) {
		if (ports.isEmpty()) {
			return new ScilabDouble();
		}

		double[][] data = new double[ports.size()][1];
		for (int i = 0; i < ports.size(); ++i) {
			data[i][0] = ((BasicPort) ports.get(i)).getConnectedLinkId();
		}

		return new ScilabDouble(data);
	}

	/**
	 * Get all the port data lines.
	 * 
	 * @param ports
	 *            the ports
	 * @return array of ports data lines
	 */
	protected static ScilabDouble getAllPortsDataLines(
			List< ? extends BasicPort> ports) {
		if (ports.isEmpty()) {
			return new ScilabDouble();
		}
		double[][] data = new double[ports.size()][1];
		for (int i = 0; i < ports.size(); ++i) {
			data[i][0] = ((BasicPort) ports.get(i)).getDataLines();
		}

		return new ScilabDouble(data);
	}

	/**
	 * @param block
	 *            the block we are working on
	 * @param revert
	 *            True if the returned list have to be in a reversed order or
	 * @param type
	 *            the class instance to search for
	 * @param <T>
	 *            The type to search for.
	 * @return control ports of given block
	 */
	public static <T extends BasicPort> List<T> getAllTypedPorts(
			BasicBlock block, boolean revert, Class<T> type) {
		List<T> data = new ArrayList<T>();
		int childrenCount = block.getChildCount();

		for (int i = 0; i < childrenCount; ++i) {
			mxICell cell = block.getChildAt(i);
			if (type.isInstance(cell)) {
				// There we are sure that the cell is an instance of the type
				// class. Thus we can safely cast it and add it to the result
				// vector.
				if (revert) {
					data.add(0, (T) cell);
				} else {
					data.add((T) cell);
				}
			}
		}

		return data;
	}

	/**
	 * Get the associated port ordered by orientation.
	 * 
	 * @param block
	 *            The block we are working on
	 * @return Lists of ports where key are BasicPort.Orientation
	 */
	public static Map<Orientation, List<BasicPort>> getAllOrientedPorts(
			BasicBlock block) {
		EnumMap<Orientation, List<BasicPort>> map = new EnumMap<Orientation, List<BasicPort>>(
				Orientation.class);
		List<BasicPort> northPorts = new ArrayList<BasicPort>();
		List<BasicPort> southPorts = new ArrayList<BasicPort>();
		List<BasicPort> eastPorts = new ArrayList<BasicPort>();
		List<BasicPort> westPorts = new ArrayList<BasicPort>();

		final int childrenCount = block.getChildCount();
		for (int i = 0; i < childrenCount; ++i) {
			BasicPort port = (BasicPort) block.getChildAt(i);
			switch (port.getOrientation()) {
			case NORTH:
				northPorts.add(port);
				break;
			case SOUTH:
				southPorts.add(port);
				break;
			case EAST:
				eastPorts.add(port);
				break;
			case WEST:
				westPorts.add(port);
				break;
			default:
				break;
			}
		}

		map.put(Orientation.NORTH, northPorts);
		map.put(Orientation.SOUTH, southPorts);
		map.put(Orientation.EAST, eastPorts);
		map.put(Orientation.WEST, westPorts);

		return map;
	}
}