// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA -
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt

function X = sylv(A,B,C,flag)
    //  solve  A*X+X*B=C if flag=='c' or  A*X*B-X=C if flag=='d'
    if argn(2)<>4 then error(39),end
    if size(A,1)<> size(A,2) then error(20,1),end
    if size(B,1)<> size(B,2) then error(20,2),end
    if size(C,1)<> size(A,1) then
        error(msprintf(gettext("%s: Incompatible input arguments #%d and #%d: Same row dimensions expected.\n"),"sylv",1,3))
    end
    if size(C,2)<> size(B,2) then
        error(msprintf(gettext("%s: Incompatible input arguments #%d and #%d: Same column dimensions expected.\n"),"sylv",2,3))
    end

    if flag=="c" then
        flag=[0 0 0],
    elseif flag=="d" then
        flag=[1 0 0],
    else
        error(36,3)
    end
    X=linmeq(1,A,B,C,flag)
endfunction
