// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- JVM NOT MANDATORY -->

// <-- Non-regression test for bug 10576 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=10576
//
// <-- Short Description -->
//
// getdate (on Windows) did not manage dates after January 19, 2038
//

if getos() == "Windows" then
 t = 1.327D+09;  // date: [ 2012.    1.    3.    19.    5.    19.    20.    6.    40.    0]
 r = t * 2;
 ref = [  2054.    2.    6.    37.    6.    6.    15.    13.    20.    0.  ];
 assert_checkequal(getdate(r), ref);
end
 