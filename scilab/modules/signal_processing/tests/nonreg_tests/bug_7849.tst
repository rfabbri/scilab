// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- JVM NOT MANDATORY -->
//
// <-- Non-regression test for bug 7849 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=7849
//
// <-- Short Description -->
// eqfir crashs Scilab on MacOS platform

if execstr("hn = eqfir(33, [0 .2; .25 .35; .4 .5], [0 1 0], [1 1 1]);", "errcatch") <> 0 then pause, end
if or(size(hn) <> [1 33]) then pause, end
