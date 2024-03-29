// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2011 - DIGITEO - Allan CORNET
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt


function strs = pol2str(p)
    // polynomial to character string
    //
    // p : polynomial (real)
    // str : chracter string
    //!

    if type(p) <> 2 then
        error(msprintf(gettext("%s: Wrong type for input argument #%d: Polynomial expected.\n"), "pol2str", 1));
    end

    dimp2D = size(p);
    dimp1D = size(p, "*");

    for i = 1:dimp1D
        _p = p(i);
        n = degree(_p);
        var = varn(_p);
        nv = length(var);

        while part(var,nv) == " " then
            nv = nv - 1;
        end;

        var = part(var, 1:nv);

        _p = coeff(_p);
        if _p(1) <>0 then
            if _p(1) < 0 then
                str = string(_p(1));
            else
                str = " " + string(_p(1));
            end
        else
            if n == 0 then
                str = "0";
            else
                str = " ";
            end
        end

        for k = 1:n
            if _p(k + 1) <> 0 then
                if _p(k + 1) < 0 then
                    str = str + "-";
                else
                    str = str + "+";
                end
                if abs(_p(k + 1)) <> 1 then
                    str = str + string(abs(_p(k+1))) + "*" + var;
                else
                    str = str + var;
                end
                if k > 1 then
                    str = str + "^" + string(k);
                end
            end
        end

        strs(i) = str;
    end
    strs = matrix(strs, dimp2D);

endfunction
