// Copyright (C) 2008 - INRIA - Michael Baudin
// Copyright (C) 2010 - DIGITEO - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

// <-- JVM NOT MANDATORY -->
// <-- ENGLISH IMPOSED -->

function flag = MY_assert_equal ( computed , expected )
  if computed==expected then
    flag = 1;
  else
    flag = 0;
  end
  if flag <> 1 then pause,end
endfunction

format("v",10);

//
dmax = -log10(2^(-53));
//
computed = assert_computedigits ( 1 , 1 );
MY_assert_equal ( computed , dmax );
//
computed = assert_computedigits ( 0 , 0 );
MY_assert_equal ( computed , dmax );
//
computed = assert_computedigits ( 1 , 0 );
MY_assert_equal ( computed , 0 );
//
computed = assert_computedigits ( 0 , 1 );
MY_assert_equal ( computed , 0 );
//
computed = assert_computedigits ( 3.1415926 , %pi );
MY_assert_equal ( computed , 7.76806779280040160 );
//
computed = assert_computedigits ( 3.1415926 , %pi , 2 );
MY_assert_equal ( computed , 25.80496264389331884 );
//
computed = assert_computedigits ( [0 0 1 1] , [0 1 0 1] );
MY_assert_equal ( computed , [dmax 0 0 dmax] );
//
computed = assert_computedigits(ones(3,2),ones(3,2));
MY_assert_equal ( computed , dmax * ones(3,2) );
//
computed = assert_computedigits([%nan %nan %nan %nan],[%nan %inf -%inf 0]);
MY_assert_equal ( computed , [dmax 0 0 0] );
//
computed = assert_computedigits([%inf %inf %inf %inf],[%nan %inf -%inf 0]);
MY_assert_equal ( computed , [0 dmax 0 0] );
//
computed = assert_computedigits([-%inf -%inf -%inf -%inf],[%nan %inf -%inf 0]);
MY_assert_equal ( computed , [0 0 dmax 0] );
//
computed = assert_computedigits([0 0 0 0],[%nan %inf -%inf 0]);
MY_assert_equal ( computed , [0 0 0 dmax] );
//
computed = assert_computedigits(1.224646799D-16,8.462643383D-18);
MY_assert_equal ( computed , 0 );
//
computed = assert_computedigits ( 1.2345 + %i*6.7891 , 1.23456789 + %i*6.789123456 );
MY_assert_equal ( computed , 4.259709168495138698 );
//
// The sign bit of the number of digits may be wrong because
// ieee(2); z=max(-0,0); 1/z is -%inf
back = ieee();
ieee(2);
computed = assert_computedigits ( 1.e-305 , 0 );
MY_assert_equal ( 1/computed , %inf );
//
computed = assert_computedigits ( 0 , 1.e-305 );
MY_assert_equal ( 1/computed , %inf );
ieee(back);
