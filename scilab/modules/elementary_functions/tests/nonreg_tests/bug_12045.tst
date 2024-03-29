// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Charlotte HECQUET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for bug 12045 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=12045
//
// <-- Short Description -->
// repmat function returns wrong result if numbers of input matrix are not double
//

A= [1 7 31 127; 3 15 63 55];
A_int8=int8(A);
A_uint8=uint8(A);
A_int16=int16(A);
A_uint16=uint16(A);
A_int32=int32(A);
A_uint32=uint32(A);

assert_checkequal(repmat(A_int8,1,1,2),repmat(A,1,1,2));
assert_checkequal(repmat(A_uint8,1,1,2),repmat(A,1,1,2));
assert_checkequal(repmat(A_int16,1,1,2),repmat(A,1,1,2));
assert_checkequal(repmat(A_uint16,1,1,2),repmat(A,1,1,2));
assert_checkequal(repmat(A_int32,1,1,2),repmat(A,1,1,2));
assert_checkequal(repmat(A_uint32,1,1,2),repmat(A,1,1,2));
