// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) DIGITEO - 2011  - Allan CORNET
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//=============================================================================
function dlwGenerateCleaner(fd, makename)
  make_command = dlwGetMakefileCmdCleaner(makename);
  mfprintf(fd,"if fileinfo(''%s%s'') <> [] then\n", makename, dlwGetMakefileExt());
  mfprintf(fd,"  unix_s(''%s'');\n", make_command);
  mfprintf(fd,"  mdelete(''%s%s'');\n", makename, dlwGetMakefileExt());
  mfprintf(fd,"end\n");
  mfprintf(fd,"// ------------------------------------------------------\n");
endfunction
//=============================================================================