// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 - DIGITEO - Clément DAVID
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH XCOS -->
//
// <-- Non-regression test for bug 7639 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=7639
//
// <-- Short Description -->
// When I try to generate some code for a superblock containing a scilab 
// function, it produce an error message.

// overwrite message
prot = funcprot();
funcprot(0);
function num=message(strings ,buttons, modal)
    num = 1;
endfunction
funcprot(prot);

status = importXcosDiagram(SCI + "/modules/xcos/tests/nonreg_tests/bug_7639.xcos");
if ~status then pause, end

hdf5FileToLoad = TMPDIR + "/in.h5";
hdf5FileToSave = TMPDIR + "/out.h5";

// export the Superblock to the file
scs_m = scs_m.objs(3);
export_to_hdf5(hdf5FileToLoad, "scs_m");

// call and check for a message error (the out file will not be created on error)
xcosCodeGeneration(hdf5FileToLoad, hdf5FileToSave)
if isfile(hdf5FileToSave) then pause, end

deletefile(hdf5FileToLoad);
