// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Michael Baudin
// Copyright (C) 2011 - DIGITEO - Michael Baudin
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->

// <-- NO CHECK REF -->
// <-- Non-regression test for bug 415 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=415
//
// <-- Short Description -->
//Bug Report Id: 12703200082791817
// There is no convergence problem, but the roots given by Scilab are false.
//
//With Pari and Maple, I find
//
//-1.991414471058644760261615564 + 0.E-28*I
//-1.895889044296221748848819128 + 0.E-28*I
//-1.692382605570622810325758964 + 0.E-28*I
//-1.481546143424463443623878009 + 0.E-28*I
//-1.130257610083694441233635997 + 0.E-28*I
//1.346891063469017079426003177 + 0.E-28*I
//1.504013628510203282791611562 + 0.E-28*I
//1.846667981457346134709529025 + 0.E-28*I
//0.3354022818049053224733928984 - 0.1602901760665646683439370449*I
//0.3354022818049053224733928984 + 0.1602901760665646683439370449*I
//-0.5652255834927430850816775162 - 0.06550796263368989842265750483*I
//-0.5652255834927430850816775162 + 0.06550796263368989842265750483*I
//1.976781902186378116291566567 - 0.03475891968883585523494112251*I
//1.976781902186378116291566567 + 0.03475891968883585523494112251*I   
//
//
//With Scilab, I find
//
//!   0.3354023 + 0.1602902i !
//!   0.3354023 - 0.1602902i !
//! - 0.5652256 + 0.0655080i !
//! - 0.5652256 - 0.0655080i !
//! - 1.1302576              !
//!   1.3468911              !
//!   1.5040136              !
//! - 1.4815461              !
//! - 1.6923826              !
//!   1.846668               !
//! - 1.895889               !
//!   1.9736772              !
//! - 1.9914145              !
//!   1.9798866              !
//
//
//So, Scilab forget two roots, and give two others which are not roots of p.
//
//
//On Scilab 2.5-0 with " roots " function
//The Error Messages are:
//  No error message, but the roots are false
//Commands: t=poly(0,"t");
//p=t^14 - 15*t^12 - t^11 + 89*t^10 + 12*t^9 - 263*t^8 - 53*t^7 + 397*t^6 + 103*t^5 - 275*t^4 - 78*t^3 + 62*t^2 + 8*t - 7
//roots(p)
//
//
//Jean-Marc Sac-Epée on Linux PC version Linux distribution Mandrake 7.1 with  KDE as window manager
//France  September 27, 2000 at 9:18:17

// 
// sort_merge_comparison --
//   Returns -1 if x < y, 
//   returns 0 if x==y,
//   returns +1 if x > y
//
function order = sort_merge_comparison ( x , y )
  if x < y then
    order = -1
  elseif x==y then
    order = 0
  else 
    order = 1
  end
endfunction

//
// sort_merge --
//   Returns the sorted array x.
// Arguments
//   x : the array to sort
//   compfun : the comparison function
//   data : an optionnal data to pass to the comparison function
// Bruno Pincon
// "quelques tests de rapidité entre différents logiciels matriciels"
// Modified by Michael Baudin to manage a comparison function
//
function [x] = sort_merge ( varargin )
  [lhs,rhs]=argn();
  if ( ( rhs<>1 ) & ( rhs<>2 ) & ( rhs<>3 ) ) then
    errmsg = sprintf("Unexpected number of arguments : %d provided while 1, 2 or 3 are expected.",rhs);
    error(errmsg)
  end
  // Get the array x
  x = varargin(1);
  // Get the comparison function compfun
  if rhs==1 then
    compfun = sort_merge_comparison;
  else
    compfun = varargin(2);
    if ( rhs == 3 ) then
	data = varargin(3);
    end
  end
  // Proceed...
  n = length(x)
  if n > 1 then
    m = floor(n/2); 
    p = n-m
    if ( rhs == 3 ) then
      x1 = sort_merge ( x(1:m) , compfun , data )
      x2 = sort_merge ( x(m+1:n) , compfun , data )
    else
      x1 = sort_merge ( x(1:m) , compfun )
      x2 = sort_merge ( x(m+1:n) , compfun )
    end
    i = 1; 
    i1 = 1;
    i2 = 1;
    for i = 1:n
      if ( rhs == 3 ) then
        order = compfun ( x1(i1) , x2(i2) , data );
      else
        order = compfun ( x1(i1) , x2(i2) );
      end
      if order<=0 then
        x(i) = x1(i1)
        i1 = i1+1
        if (i1 > m) then
          x(i+1:n) = x2(i2:p)
          break
        end
      else
        x(i) = x2(i2)
        i2 = i2+1
        if (i2 > p) then
          x(i+1:n) = x1(i1:m)
          break
        end
      end
    end
  end
endfunction


function order = mycomparison ( x , y , data )
  order = assert_comparecomplex(x,y,data(1),data(2))
endfunction


// There is no problem in this test: only the order of the 
// eigenvalues change.
t=poly(0,"t");
p=t^14 - 15*t^12 - t^11 + 89*t^10 + 12*t^9 - 263*t^8 - 53*t^7 + 397*t^6 + 103*t^5 - 275*t^4 - 78*t^3 + 62*t^2 + 8*t - 7;
myroots=roots(p);
//computedroots = sort(myroots);
computed = sort_merge ( myroots , mycomparison , [%eps,0] );
expected  = [ 
- 1.9914144710587742270747  
- 1.89588904429592775003 
- 1.6923826055708985904857  
- 1.4815461434243473171080  
- 1.1302576100836980721454  
- 0.5652255834927423228109 - 0.0655079626336916437390*%i  
- 0.5652255834927423228109 + 0.0655079626336916437390*%i  
0.3354022818049053333844 - 0.1602901760665648156490*%i 
0.3354022818049053333844 + 0.1602901760665648156490*%i  
1.346891063468121929603  
1.5040136285121223913563  
1.8466679814523012659322  
1.9767819021883872299128 - 0.0347589196932355307124*%i  
1.9767819021883872299128 + 0.0347589196932355307124*%i  
];
// Precision measured with experiments
assert_checkalmostequal ( computed , expected , 10^6*%eps );
