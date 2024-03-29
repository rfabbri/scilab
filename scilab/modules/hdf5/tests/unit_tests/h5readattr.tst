// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - SCILAB ENTERPRISES - Simon GARESTE
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->

msgerr = msprintf(gettext("%s: Wrong number of input argument(s): %d to %d expected.\n"), "h5readattr", 1, 3);
assert_checkerror("h5readattr()",msgerr,77);
msgerr = msprintf(gettext("%s: Wrong type for input argument #%d: A string expected.\n"), "h5readattr", 1);
assert_checkerror("h5readattr(42)",msgerr,999);
msgerr = msprintf(gettext("%s: Invalid number of argument(s): %d expected.\n"), "h5readattr", 3);
assert_checkerror("h5readattr(""42"")",msgerr,999);
msgerr = msprintf(gettext("%s: Wrong type for input argument #%d: A string expected.\n"), "h5readattr", 2);
assert_checkerror("h5readattr(""42"",42,42)",msgerr,999);
msgerr = msprintf(gettext("%s: Wrong type for input argument #%d: A string expected.\n"), "h5readattr", 3);
assert_checkerror("h5readattr(""42"",""42"",42)",msgerr,999);
msgerr = msprintf(gettext("%s: %s\n"), "h5readattr", msprintf(gettext("Invalid hdf5 file: %s."), "42"));
assert_checkerror("h5readattr(""42"",""42"",""42"")",msgerr,999);

x = int8(matrix(1:80, 10, 8));
save(TMPDIR + "/x.sod", "x");
version = string(getversion('scilab'));
version = getversion()+" "+strcat([version(1),version(2),version(3)],'.');

a = h5open(TMPDIR + "/x.sod");

scilab_version = h5readattr(a, "/", "SCILAB_scilab_version");
assert_checkequal(scilab_version,version);

scilab_class = h5readattr(a.root.x, "SCILAB_Class");
assert_checkequal(scilab_class,"integer");

msgerr = msprintf(gettext("%s: %s\n"), "h5readattr", msprintf(gettext("Cannot open attribute: %s"), "test"));
assert_checkerror("h5readattr(a.root.x, ""test"")",msgerr,999);

msgerr = msprintf(gettext("%s: %s\n"), "h5readattr", msprintf(gettext("Invalid name: %s."), ""));
msgerr($+1) = gettext("HDF5 description") + ": " + "no attribute name.";
assert_checkerror("h5readattr(a.root.x)",msgerr,999);

msgerr = msprintf(gettext("%s: %s\n"), "h5readattr", msprintf(gettext("Cannot open attribute: %s"), "Attributes"));
assert_checkerror("h5readattr(a.root.x,""Attributes"")",msgerr,999);
//After closing, all h5readattr will fail
h5close(a);

msgerr = msprintf(gettext("%s: Invalid H5Object.\n"), "h5readattr");
assert_checkerror("h5readattr(a, ""/"", ""SCILAB_scilab_version"")",msgerr,999);
msgerr = msprintf(gettext("%s: Invalid H5Object.\n"), "%H5Object_e");
assert_checkerror("h5readattr(a.root.x, ""SCILAB_Class"")",msgerr,999);
assert_checkerror("h5readattr(a.root.x, ""test"")",msgerr,999);
assert_checkerror("h5readattr(a.root.x)",msgerr,999);
assert_checkerror("h5readattr(a.root.x,""Attributes"")",msgerr,999);

// non hdf5 variable
b=1;
msgerr = msprintf(gettext("%s: Wrong type for input argument #%d: A string expected.\n"), "h5readattr", 1);
assert_checkerror("h5readattr(b)",msgerr,999);
msgerr = msprintf(gettext("%s: Wrong type for input argument #%d: A string expected.\n"), "h5readattr", 1);
assert_checkerror("h5readattr(b,""/"")",msgerr,999);
b="hello";
msgerr = msprintf(gettext("%s: %s\n"), "h5readattr", msprintf(gettext("Invalid hdf5 file: %s."), b));
assert_checkerror("h5readattr(b,""/"")",msgerr,999);


assert_checkequal(deletefile(TMPDIR+"/x.sod"),%T);
