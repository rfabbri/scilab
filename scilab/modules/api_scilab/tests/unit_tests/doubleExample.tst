// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009-2010 - DIGITEO - Scilab Consortium Operational Team
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- JVM NOT MANDATORY -->
ilib_verbose(0);
mkdir(pathconvert(TMPDIR+"/doubleExample"));
cd(pathconvert(TMPDIR+"/doubleExample"));
copyfile(SCI+"/modules/api_scilab/tests/unit_tests/doubleExample.c",pathconvert(TMPDIR+"/doubleExample/doubleExample.c",%F));
cflags = "-I"+SCI+"/modules/localization/includes";
ilib_build("doubleExample",["doubleExample","doubleExample"],"doubleExample.c",[],"","",cflags);
exec("loader.sce");

a = 1;
b = %i;
c = [1,2,3;4,5,6];
d = c(1:$) + c($:-1:1) * %i;
doubleExample(a) == a
doubleExample(b) == b
doubleExample(c) == c
doubleExample(d) == d