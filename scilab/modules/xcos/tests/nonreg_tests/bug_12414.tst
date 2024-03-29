// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Alexandre HERISSE
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- XCOS TEST -->
//
// <-- Non-regression test for bug 12414 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=12414
//
// <-- Short Description -->
// SWITCH_m block had different behaviors for different types of inputs.

assert_checktrue(importXcosDiagram(SCI + "/modules/xcos/tests/nonreg_tests/bug_12414.xcos"));
Info = scicos_simulate(scs_m, list());

assert_checkequal(A.values($), uint16(1));
assert_checkequal(B.values($), 1.0);

