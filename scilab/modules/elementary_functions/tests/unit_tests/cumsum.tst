// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 - INRIA - Serge Steer
// Copyright (C) 2012 - Scilab Enterprises - Cedric Delamarre
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->

//empty matrices
T=list(list(),list('native'),list('double'));
for typ=T
    assert_checkequal(cumsum([],typ(:)), []);
    assert_checkequal(cumsum([],'*',typ(:)), []);
    assert_checkequal(cumsum([],1,typ(:)), []);
    assert_checkequal(cumsum([],2,typ(:)), []);
    assert_checkequal(cumsum([],3,typ(:)), []);
end

//=======================================================================
//float matrices
d=[1 10;254 9];
T=list(list(),list('native'),list('double'));
for typ=T
    assert_checkequal(cumsum(d,typ(:)), [1,265;255,274]);
    assert_checkequal(cumsum(d,'*',typ(:)), [1,265;255,274]);
    assert_checkequal(cumsum(d,1,typ(:)), [1,10;255,19]);
    assert_checkequal(cumsum(d,2,typ(:)), [1,11;254,263]);
    assert_checkequal(cumsum(d,3,typ(:)), d);
end

//hypermatrices of floats
d=[1 10;254 9];d(1,1,2)=1;
T=list(list(),list('native'),list('double'));
for typ=T
    assert_checkequal(cumsum(d,typ(:)), hypermat([2,2,2],[1;255;265;274;275;275;275;275]));
    assert_checkequal(cumsum(d,'*',typ(:)), hypermat([2,2,2],[1;255;265;274;275;275;275;275]));
    assert_checkequal(cumsum(d,1,typ(:)), hypermat([2,2,2],[1;255;10;19;1;1;0;0]));
    assert_checkequal(cumsum(d,2,typ(:)), hypermat([2,2,2],[1;254;11;263;1;0;1;0]));
    assert_checkequal(cumsum(d,3,typ(:)), hypermat([2,2,2],[1;254;10;9;2;254;10;9]));
    assert_checkequal(cumsum(d,5,typ(:)), d);
end

//=======================================================================
//Integers
i=uint8([1 10;254 9]);
for typ=list(list(),list('native'));
    assert_checkequal(cumsum(i,typ(:)), uint8([1,9;255,18]));
    assert_checkequal(cumsum(i,'*',typ(:)), uint8([1,9;255,18]));
    assert_checkequal(cumsum(i,1,typ(:)), uint8([1,10;255,19]));
    assert_checkequal(cumsum(i,2,typ(:)), uint8([1,11;254,7]));
    assert_checkequal(cumsum(i,3,typ(:)), double(i));
end

assert_checkequal(cumsum(i,'double'), [1,265;255,274]);
assert_checkequal(cumsum(i,'*','double'), [1,265;255,274]);
assert_checkequal(cumsum(i,1,'double'), [1,10;255,19]);
assert_checkequal(cumsum(i,2,'double'), [1,11;254,263]);
assert_checkequal(cumsum(i,3,'double'), double(i));

//with hypermatrices
i=uint8([1 10;254 9]);i(1,1,2)=uint8(1);
for typ=list(list(),list('native'));
    assert_checkequal(cumsum(i,typ(:)), hypermat([2,2,2],[1;255;9;18;19;19;19;19]));
    assert_checkequal(cumsum(i,'*',typ(:)), hypermat([2,2,2],[1;255;9;18;19;19;19;19]));
    assert_checkequal(cumsum(i,1,typ(:)), hypermat([2,2,2],[1;255;10;19;1;1;0;0]));
    assert_checkequal(cumsum(i,2,typ(:)), hypermat([2,2,2],[1;254;11;7;1;0;1;0]));
    assert_checkequal(cumsum(i,3,typ(:)), hypermat([2,2,2],[1;254;10;9;2;254;10;9]));
    assert_checkequal(cumsum(i,5,typ(:)), double(i));
end


assert_checkequal(cumsum(i,'double'), hypermat([2,2,2],[1;255;265;274;275;275;275;275]));
assert_checkequal(cumsum(i,'*','double'), hypermat([2,2,2],[1;255;265;274;275;275;275;275]));
assert_checkequal(cumsum(i,1,'double'), hypermat([2,2,2],[1;255;10;19;1;1;0;0]));
assert_checkequal(cumsum(i,2,'double'), hypermat([2,2,2],[1;254;11;263;1;0;1;0]));
assert_checkequal(cumsum(i,3,'double'), hypermat([2,2,2],[1;254;10;9;2;254;10;9]));
assert_checkequal(cumsum(i,5,'double'), double(i));

//=======================================================================
//Matrices of Polynomials
s=%s;p=[s s+1;s^2 0];
T=list(list(),list('native'),list('double'));
for typ=T
  assert_checkequal(cumsum(p,typ(:)), [s,1+2*s+s^2;s+s^2,1+2*s+s^2]);
  assert_checkequal(cumsum(p,'*',typ(:)), [s,1+2*s+s^2;s+s^2,1+2*s+s^2]);
  assert_checkequal(cumsum(p,1,typ(:)), [s,1+s;s+s^2,1+s]);
  assert_checkequal(cumsum(p,2,typ(:)), [s,1+2*s;s^2,s^2]);
  assert_checkequal(cumsum(p,3,typ(:)), p);
end

//with hypermatrices
s=%s;p=[s s+1;s^2 0];p(1,1,2)=-1;
T=list(list(),list('native'),list('double'));
for typ=T
  assert_checkequal(cumsum(p,typ(:)), hypermat([2,2,2],[s;s+s^2;1+2*s+s^2;1+2*s+s^2;2*s+s^2;2*s+s^2;2*s+s^2;2*s+s^2]));
  assert_checkequal(cumsum(p,'*',typ(:)), hypermat([2,2,2],[s;s+s^2;1+2*s+s^2;1+2*s+s^2;2*s+s^2;2*s+s^2;2*s+s^2;2*s+s^2]));
  assert_checkequal(cumsum(p,1,typ(:)), hypermat([2,2,2],[s;s+s^2;1+s;1+s;-1;-1;0*s;0*s]));
  assert_checkequal(cumsum(p,2,typ(:)), hypermat([2,2,2],[s;s^2;1+2*s;s^2;-1;0*s;-1;0*s]));
  assert_checkequal(cumsum(p,3,typ(:)), hypermat([2,2,2],[s;s^2;1+s;0*s;-1+s;s^2;1+s;0*s]));
  assert_checkequal(cumsum(p,5,typ(:)), p);
end

//=======================================================================
//Matrices of rationals
s=%s;r=1.0 ./[s s+1;s^2 1];
T=list(list(),list('native'),list('double'));
for typ=T
  assert_checkequal(cumsum(r,typ(:)), [1,1+2*s+2*s^2;1+s,1+2*s+3*s^2+s^3]./[s,s^2+s^3;s^2,s^2+s^3]);
  assert_checkequal(cumsum(r,'*',typ(:)), [1,1+2*s+2*s^2;1+s,1+2*s+3*s^2+s^3]./[s,s^2+s^3;s^2,s^2+s^3]);
  assert_checkequal(cumsum(r,1,typ(:)), [1,1;1+s,2+s]./[s,1+s;s^2,1+s]);
  assert_checkequal(cumsum(r,2,typ(:)), [1,1+2*s;1,1+s^2]./[s,s+s^2;s^2,s^2]);
  assert_checkequal(cumsum(r,3,typ(:)), r);
end

//=======================================================================
///Matrices of boolean

b=[%t %t;%f %t];
for typ=list(list(),list('double'));
  assert_checkequal(cumsum(b,typ(:)), [1,2;1,3]);
  assert_checkequal(cumsum(b,'*',typ(:)), [1,2;1,3]);
  assert_checkequal(cumsum(b,1,typ(:)), [1,1;1,2]);
  assert_checkequal(cumsum(b,2,typ(:)), [1,2;0,1]);
  assert_checkequal(cumsum(b,3,typ(:)), double(b));
end
assert_checkequal(cumsum(b,'native'), [%t %t;%t %t]);
assert_checkequal(cumsum(b,'*','native'), [%t %t;%t %t]);
assert_checkequal(cumsum(b,1,'native'), [%t %t;%t %t]);
assert_checkequal(cumsum(b,2,'native'), [%t %t;%f %t]);
assert_checkequal(cumsum(b,3,'native'), b);

//with hypermatrices
b=[%t %t;%f %t];b(1,1,2)=%f;
for typ=list(list(),list('double'));
  assert_checkequal(cumsum(b,typ(:)), hypermat([2,2,2],[1;1;2;3;3;3;3;3]));
  assert_checkequal(cumsum(b,'*',typ(:)), hypermat([2,2,2],[1;1;2;3;3;3;3;3]));
  assert_checkequal(cumsum(b,1,typ(:)), hypermat([2,2,2],[1;1;1;2;0;0;0;0]));
  assert_checkequal(cumsum(b,2,typ(:)), hypermat([2,2,2],[1;0;2;1;0;0;0;0]));
  assert_checkequal(cumsum(b,3,typ(:)), hypermat([2,2,2],[1;0;1;1;1;0;1;1]));
  assert_checkequal(cumsum(b,5,typ(:)), double(b));
end

assert_checkequal(cumsum(b,'native'), hypermat([2,2,2],[%t;%t;%t;%t;%t;%t;%t;%t]));
assert_checkequal(cumsum(b,'*','native'), hypermat([2,2,2],[%t;%t;%t;%t;%t;%t;%t;%t]));
assert_checkequal(cumsum(b,1,'native'), hypermat([2,2,2],[%t;%t;%t;%t;%f;%f;%f;%f]));
assert_checkequal(cumsum(b,2,'native'), hypermat([2,2,2],[%t;%f;%t;%t;%f;%f;%f;%f]));
assert_checkequal(cumsum(b,3,'native'), hypermat([2,2,2],[%t;%f;%t;%t;%t;%f;%t;%t]));
assert_checkequal(cumsum(b,5,'native'), b);

//=======================================================================
//sparse matrices of floats
s=sparse([0 10 0;0 254 9]);
T=list(list(),list('native'),list('double'));
for typ=T
  assert_checkequal(cumsum(s,typ(:)), sparse([1,2;1,3;2,2;2,3],[10;264;264;273],[2,3]));
  assert_checkequal(cumsum(s,'*',typ(:)), sparse([1,2;1,3;2,2;2,3],[10;264;264;273],[2,3]));
  assert_checkequal(cumsum(s,1,typ(:)), sparse([1,2;2,2;2,3],[10;264;9],[2,3]));
  assert_checkequal(cumsum(s,2,typ(:)), sparse([1,2;1,3;2,2;2,3],[10;10;254;263],[2,3]));
  assert_checkequal(cumsum(s,3,typ(:)), s);
end

//=======================================================================
//sparse  matrices of boolean
bs=sparse([0 10 0;0 254 9])<>0;
for typ=list(list(),list('double'));
  assert_checkequal(cumsum(bs,typ(:)), sparse([1,2;1,3;2,2;2,3],[1;2;2;3],[2,3]));
  assert_checkequal(cumsum(bs,'*',typ(:)), sparse([1,2;1,3;2,2;2,3],[1;2;2;3],[2,3]));
  assert_checkequal(cumsum(bs,1,typ(:)), sparse([1,2;2,2;2,3],[1;2;1],[2,3]));
  assert_checkequal(cumsum(bs,2,typ(:)), sparse([1,2;1,3;2,2;2,3],[1;1;1;2],[2,3]));
  assert_checkequal(cumsum(bs,3,typ(:)), bool2s(bs));
end

assert_checkequal(cumsum(bs,'native'),  sparse([1,2;1,3;2,2;2,3],[%t;%t;%t;%t],[2,3]));
assert_checkequal(cumsum(bs,'*','native'),  sparse([1,2;1,3;2,2;2,3],[%t;%t;%t;%t],[2,3]));
assert_checkequal(cumsum(bs,1,'native'), sparse([1,2;2,2;2,3],[%t;%t;%t],[2,3]));
assert_checkequal(cumsum(bs,2,'native'), sparse([1,2;1,3;2,2;2,3],[%t;%t;%t;%t],[2,3]));
assert_checkequal(cumsum(bs,3,'native'), bs);

// TODO : test the "m" option
