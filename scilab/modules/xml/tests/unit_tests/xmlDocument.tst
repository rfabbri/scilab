// ===========================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Sylvestre LEDRU
//
//  This file is distributed under the same license as the Scilab package.
// ===========================================================================


doc = xmlDocument("TMPDIR/foo.xml");
root = xmlElement(doc, "root");
root.attributes.attr = "value";

root.children(1) = "<a>hello</a>";
root.children(2) = xmlElement(doc, "b");
root.children(2).attributes.id = "123";
root.children(2).content = " world";

doc.root = root;
xmlDump(doc);
assert_checkequal(doc.root.children(1).name,"a");
assert_checkequal(doc.root.children(1).content,"hello");
assert_checkequal(doc.root.children(2).name,"b");
assert_checkequal(doc.root.children(2).content," world");

xmlClose(doc);