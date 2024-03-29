// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Sylvestre Ledru
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

jautoUnwrap(%f);
myString=jwrap("foo");
assert_checkequal(jgetclassname(myString),"java.lang.String");
assert_checkequal("foo",junwrap(myString));

a=jwrap(2);
assert_checkequal(typeof(a),"_EObj");
assert_checkequal(jgetclassname(a),"double");
b=junwrap(a);
assert_checkequal(typeof(b),"constant");


c = jcompile("Test", ["public class Test {";
    "public int[] returnArrayInt() {";
    "    return new int[]{1,2,3,4};";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(int32([1,2,3,4]), junwrap(t.returnArrayInt()));

c = jcompile("Test", ["public class Test {";
    "public int returnInt() {";
    "    return 32;";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(int32(32), junwrap(t.returnInt()));

//////////////////////////////////////////////

c = jcompile("Test", ["public class Test {";
    "public double[] returnDouble() {";
    "    return new double[]{1,2,3,4};";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal([1,2,3,4], junwrap(t.returnDouble()));

c = jcompile("Test", ["public class Test {";
    "public double returnDouble() {";
    "    return 32;";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(32, junwrap(t.returnDouble()));

//////////////////////////////////////////////

c = jcompile("Test", ["public class Test {";
    "public byte[] returnByte() {";
    "    return new byte[]{1,2,3,4};";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(int8([1,2,3,4]), junwrap(t.returnByte()));

c = jcompile("Test", ["public class Test {";
    "public byte returnByte() {";
    "    return 32;";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(int8(32), junwrap(t.returnByte()));

//////////////////////////////////////////////

c = jcompile("Test", ["public class Test {";
    "public short[] returnShort() {";
    "    return new short[]{1,2,3,4};";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(int16([1,2,3,4]), junwrap(t.returnShort()));

c = jcompile("Test", ["public class Test {";
    "public short returnShort() {";
    "    return 32;";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(int16(32), junwrap(t.returnShort()));


//////////////////////////////////////////////

c = jcompile("Test", ["public class Test {";
    "public long[] returnLong() {";
    "    return new long[]{1L,2L,3L,4L};";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(int32([1,2,3,4]), junwrap(t.returnLong()));

c = jcompile("Test", ["public class Test {";
    "public long returnLong() {";
    "    return 32L;";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(int32(32), junwrap(t.returnLong()));

//////////////////////////////////////////////

c = jcompile("Test", ["public class Test {";
    "public float[] returnFloat() {";
    "    return new float[]{1f,2f,3f,4f};";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal([1,2,3,4], junwrap(t.returnFloat()));

c = jcompile("Test", ["public class Test {";
    "public float returnFloat() {";
    "    return 32f;";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(32, junwrap(t.returnFloat()));


//////////////////////////////////////////////

// c = jcompile("Test", ["public class Test {";
//     "public char[] returnChar() {";
//     "    return new char[]{''a'',''b'',''c'',''d''};";
//     "}";
//     "}";]);
// t = c.new();
// assert_checkequal(jgetclassname(c),"Test");
// assert_checkequal(['a','b','c','d'], t.returnChar());

// c = jcompile("Test", ["public class Test {";
//     "public char returnChar() {";
//     "    return ''a'';";
//     "}";
//     "}";]);
// t = c.new();
// assert_checkequal(jgetclassname(c),"Test");
// assert_checkequal(int16(32), t.returnChar());



//////////////////////////////////////////////

c = jcompile("Test", ["public class Test {";
    "public boolean[] returnBoolean() {";
    "    return new boolean[]{true,true,false,false};";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal([%t,%t,%f,%f], junwrap(t.returnBoolean()));

c = jcompile("Test", ["public class Test {";
    "public boolean returnBoolean() {";
    "    return true;";
    "}";
    "}";]);
t = c.new();
assert_checkequal(jgetclassname(c),"Test");
assert_checkequal(%t, junwrap(t.returnBoolean()));

jautoUnwrap(%t);

c = jcompile("Test", ["public class Test {";
  "public static Double[][] foo(double d) {";
  "Double[][] dd = new Double[][]{{d, d+1},{d+2,d+3}};";
  "return dd;"
  "}";
  "}"]);

assert_checkequal( [123,125;124,126], c.foo(123));
