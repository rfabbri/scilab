// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2009 - INRIA - Michael Baudin
// Copyright (C) 2011 - DIGITEO - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt

// <-- CLI SHELL MODE -->
// <-- ENGLISH IMPOSED -->


function [ y , index ] = squarefun ( x , index )
  y = x(1)^2+x(2)^2;
endfunction
//
// Test simplex regular
//
nm = neldermead_new ();
nm = neldermead_configure(nm,"-numberofvariables",2);
nm = neldermead_configure(nm,"-x0",[1.0 2.0]');
nm = neldermead_configure(nm,"-simplex0method","spendley");
nm = neldermead_configure(nm,"-simplex0length",1.0);
nm = neldermead_configure(nm,"-function",squarefun);
nm = neldermead_search(nm);
simplex0 = neldermead_get(nm,"-simplex0");
computed = optimsimplex_getallx ( simplex0 );
expected = [
1.    2.
1.96592582628907    2.25881904510252
1.25881904510252    2.96592582628907
];
assert_checkalmostequal ( computed, expected, 10 * %eps );
nm = neldermead_destroy(nm);
//
// Test simplex axes
//
nm = neldermead_new ();
nm = neldermead_configure(nm,"-numberofvariables",2);
nm = neldermead_configure(nm,"-x0",[1.0 2.0]');
nm = neldermead_configure(nm,"-simplex0method","axes");
nm = neldermead_configure(nm,"-simplex0length",1.0);
nm = neldermead_configure(nm,"-function",squarefun);
nm = neldermead_search(nm);
simplex0 = neldermead_get(nm,"-simplex0");
computed = optimsimplex_getallx ( simplex0 );
expected = [
    1.    2.  
    2.    2.  
    1.    3.  
];
assert_checkalmostequal ( computed, expected, 10 * %eps );
nm = neldermead_destroy(nm);
//
// Test simplex axesrelative
//
nm = neldermead_new ();
nm = neldermead_configure(nm,"-numberofvariables",2);
nm = neldermead_configure(nm,"-x0",[1.0 2.0]');
nm = neldermead_configure(nm,"-simplex0method","pfeffer");
nm = neldermead_configure(nm,"-simplex0deltausual",0.05);
nm = neldermead_configure(nm,"-simplex0deltazero",0.0075);
nm = neldermead_configure(nm,"-function",squarefun);
nm = neldermead_search(nm);
simplex0 = neldermead_get(nm,"-simplex0");
computed = optimsimplex_getallx ( simplex0 );
expected = [
    1.                          2.                        
    1.05                        2.                        
    1.                          2.1
];
assert_checkalmostequal ( computed, expected, 10 * %eps );
nm = neldermead_destroy(nm);
//
// Test simplex given
//
lambda1 = (1.0 + sqrt(33.0))/8.0;
lambda2 = (1.0 - sqrt(33.0))/8.0;
coords0 = [
1.0 1.0
0.0 0.0
lambda1 lambda2
];
nm = neldermead_new ();
nm = neldermead_configure(nm,"-numberofvariables",2);
nm = neldermead_configure(nm,"-x0",[1.0 2.0]');
nm = neldermead_configure(nm,"-simplex0method","given");
nm = neldermead_configure(nm,"-coords0",coords0);
nm = neldermead_configure(nm,"-simplex0deltazero",0.0075);
nm = neldermead_configure(nm,"-function",squarefun);
nm = neldermead_search(nm);
simplex0 = neldermead_get(nm,"-simplex0");
computed = optimsimplex_getallx ( simplex0 );
expected = [
1.    1.      
0.    0.   
0.8430703308172535770382 -0.5930703308172535770382
];
assert_checkalmostequal ( computed, expected, 10 * %eps );
nm = neldermead_destroy(nm);
//
// Test simplex axes with a vector of lengths
//
nm = neldermead_new ();
nm = neldermead_configure(nm,"-numberofvariables",2);
nm = neldermead_configure(nm,"-x0",[1.0 2.0]');
nm = neldermead_configure(nm,"-simplex0method","axes");
nm = neldermead_configure(nm,"-simplex0length",[1.0 2.0]);
nm = neldermead_configure(nm,"-function",squarefun);
nm = neldermead_search(nm);
simplex0 = neldermead_get(nm,"-simplex0");
computed = optimsimplex_getallx ( simplex0 );
expected = [
    1.    2.  
    2.    2.  
    1.    4.  
];
assert_checkalmostequal ( computed, expected, 10 * %eps );
nm = neldermead_destroy(nm);

//
// Test simplex axes when there are bounds constraints
//
nm = neldermead_new ();
nm = neldermead_configure(nm,"-numberofvariables",2);
nm = neldermead_configure(nm,"-function",squarefun);
nm = neldermead_configure(nm,"-maxiter",10);
nm = neldermead_configure(nm,"-x0",[0.0 0.0]');
nm = neldermead_configure(nm,"-simplex0method","axes");
nm = neldermead_configure(nm,"-method","box");
nm = neldermead_configure(nm,"-boundsmin",[-10.0 -10.0]);
nm = neldermead_configure(nm,"-boundsmax",[10.0 10.0]);
nm = neldermead_configure(nm,"-simplex0length",20.0);
nm = neldermead_search(nm);
simplex0 = neldermead_get(nm,"-simplex0");
computed = optimsimplex_getallx ( simplex0 );
expected = [
    0.    0.  
    10.    0.  
    0.    10.  
];
assert_checkalmostequal ( computed, expected, 10 * %eps );
nm = neldermead_destroy(nm);

