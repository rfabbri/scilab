// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - Digiteo - Pierre Lando
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH GRAPHIC -->
// <-- NO CHECK ERROR OUTPUT -->

// <-- Non-regression test for bug 4812 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=4812
//
// <-- Short Description -->
// xs2... function doesn't work if the first argument is a handle
// 

//scf(0);
plot3d();
hd=gcf();

file_a=pathconvert(TMPDIR+'/nonreg_test_bug4812a.png',%f);
file_b=pathconvert(TMPDIR+'/nonreg_test_bug4812b.png',%f);

//PNG export for exemple
xs2png(0,file_a);
xs2png(hd,file_b); // this now work ....

if getmd5(file_a) <> getmd5(file_b) then pause; end
