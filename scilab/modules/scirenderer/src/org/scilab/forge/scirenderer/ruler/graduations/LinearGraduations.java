/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009-2011 - DIGITEO - Pierre Lando
 * Copyright (C) 2013 - Scilab Enterprises - Calixte DENIZET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 */

package org.scilab.forge.scirenderer.ruler.graduations;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

/**
 * A linear graduation is a graduation with regular spaces mark.
 * The mark distance is called "Step" and have for value {@code mantissa x 10^exponent}.
 * Where mantissa is 1, 2 or 5.
 * Exponent is an integer.
 *
 * @author Pierre Lando
 */
public final class LinearGraduations extends AbstractGraduations implements Graduations {

    /**
     * The step exponent.
     */
    protected final int stepExponent;

    /**
     * The step mantissa.
     */
    protected final int stepMantissa;

    private LinearGraduations moreGraduation;
    private LinearGraduations alternativeGraduation;
    private Graduations subGraduation;
    private Double stepValue;
    private List<Double> allValues;
    private List<Double> newValues;

    /**
     * Private constructor.
     * Use creates methods.
     */
    private LinearGraduations() {
        super(null);
        stepExponent = 0;
        stepMantissa = 0;
    }

    private LinearGraduations(Graduations parentGraduations, int stepExponent, int stepMantissa) {
        super(parentGraduations);
        this.stepExponent = stepExponent;
        this.stepMantissa = stepMantissa;
    }

    private LinearGraduations(Graduations parentGraduations, double lowerBound, boolean lowerBoundIncluded, double upperBound, boolean upperBoundIncluded) {
        super(parentGraduations, lowerBound, lowerBoundIncluded, upperBound, upperBoundIncluded);
        if (lowerBound != upperBound) {
            double size = upperBound - lowerBound;
            stepExponent = (int) Math.ceil(Math.log10(size));
            stepMantissa = 1;
        } else {
            stepExponent = 0;
            stepMantissa = 0;
            newValues = new LinkedList<Double>();
            allValues = new LinkedList<Double>();
            allValues.add(lowerBound);
        }
    }

    public static LinearGraduations create(double lowerBound, double upperBound) {
        return create(lowerBound, true, upperBound, true);
    }

    public static LinearGraduations create(
        Graduations parentGraduations,
        double lowerBound, boolean lowerBoundIncluded,
        double upperBound, boolean upperBoundIncluded
    ) {
        if (lowerBound < upperBound) {
            return new LinearGraduations(parentGraduations, lowerBound, lowerBoundIncluded, upperBound, upperBoundIncluded);
        } else {
            return new LinearGraduations(parentGraduations, upperBound, upperBoundIncluded, lowerBound, lowerBoundIncluded);
        }
    }

    public static LinearGraduations create(double lowerBound, boolean lowerBoundIncluded, double upperBound, boolean upperBoundIncluded) {
        if (lowerBound < upperBound) {
            return new LinearGraduations(null, lowerBound, lowerBoundIncluded, upperBound, upperBoundIncluded);
        } else {
            return new LinearGraduations(null, upperBound, upperBoundIncluded, lowerBound, lowerBoundIncluded);
        }
    }

    private Double getStepValue() {
        if (stepValue == null) {
            stepValue = stepMantissa * Math.pow(10, stepExponent);
        }
        return stepValue;
    }

    private boolean isNewIndex(long index) {
        /* We are now searching for value look like
         * index * (stepMantissa * 10^n) and we don't want (previousStrepMantissa * 10^k) value.
         */

        if (stepMantissa == 1) {
            // (5 * index * stepMantissa) % 10 != 0
            return (index % 2 != 0);
        } else if (stepMantissa == 2) {
            // (2 * index * stepMantissa) % 10 != 0
            return (index % 5 != 0);
        } else {
            // (5 * index * stepMantissa) % 10 != 0
            return ((index * stepMantissa) % 2 != 0);
        }
    }

    @Override
    public List<Double> getNewValues() {
        if (getParentGraduations() == null) {
            return getAllValues();
        }

        if (newValues == null) {
            newValues = new LinkedList<Double>();
            final double lb = getLowerBound();

            long currentIndex = (long) Math.ceil(lb / getStepValue());
            double currentValue = getStepValue() * currentIndex;
            double value = currentValue - lb;

            if (value == 0 && (!containRelative(value))) {
                value += getStepValue();
                currentIndex++;
            }

            while (containRelative(value) && !Double.isInfinite(lb + value)) {
                if (isNewIndex(currentIndex)) {
                    newValues.add(lb + value);
                }
                value += getStepValue();
                currentIndex++;
            }
        }

        return newValues;
    }

    @Override
    public List<Double> getAllValues() {
        if (allValues == null) {
            final double lb = getLowerBound();
            allValues = new LinkedList<Double>();
            double currentValue = getStepValue() * Math.ceil(lb / getStepValue());
            double value = currentValue - lb;

            if (value == 0 && !containRelative(value)) {
                value += getStepValue();
            }

            while (containRelative(value) && !Double.isInfinite(lb + value)) {
                allValues.add(lb + value);
                value += getStepValue();
            }
        }
        return allValues;
    }

    @Override
    public LinearGraduations getMore() {
        if (stepMantissa != 5) {
            if (moreGraduation == null) {
                if (stepMantissa == 1) {
                    moreGraduation = new LinearGraduations(this, stepExponent - 1, 2);
                } else {
                    moreGraduation = new LinearGraduations(this, stepExponent, 1);
                }
            }
            return moreGraduation;
        } else {
            return null;
        }
    }

    @Override
    public LinearGraduations getAlternative() {
        if (stepMantissa == 2) {
            if (alternativeGraduation == null) {
                if (getParentGraduations() == null) {
                    alternativeGraduation =  new LinearGraduations(null, getLowerBound(), true, getLowerBound(), true);
                } else {
                    alternativeGraduation = new LinearGraduations(getParentGraduations(), stepExponent, 5);
                }
            }
            return alternativeGraduation;
        } else {
            return null;
        }
    }

    @Override
    public Graduations getSubGraduations() {
        if (subGraduation == null) {
            switch (stepMantissa) {
                case 1:
                    subGraduation = new LinearGraduations(this, stepExponent - 1, 5);
                    break;
                case 2:
                    subGraduation = new LinearGraduations(this, stepExponent, 1);
                    break;
                case 5:
                    subGraduation = new LinearGraduations(getParentGraduations(), stepExponent, 1);
                    break;
                default:
                    subGraduation = null;
                    break;
            }
        }
        return subGraduation;
    }

    @Override
    public int getSubDensity() {
        if (stepMantissa == 5) {
            return 5;
        } else {
            return 2;
        }
    }
}
