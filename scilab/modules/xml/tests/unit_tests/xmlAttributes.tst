// ===========================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Sylvestre LEDRU
//
//  This file is distributed under the same license as the Scilab package.
// ===========================================================================

doc = xmlReadStr("<root><a att=""foo"" rib=""bar""><b>Hello</b></a></root>");
xmlWrite(doc, TMPDIR+"/foo.xml");

// Now we open the previous file, modify it and save it
doc1 = xmlRead(TMPDIR+"/foo.xml");
assert_checkequal(doc1.root.children.size,1);
assert_checkequal(doc1.root.children(1).name,"a");
assert_checkequal(doc1.root.children(1).attributes.att,"foo");
assert_checkequal(doc1.root.children(1).attributes.rib,"bar");
a = doc1.root.children(1).attributes;
assert_checkequal(a.att,"foo");
assert_checkequal(a.rib,"bar");
assert_checkequal(a(1),"foo");
assert_checkequal(a(2),"bar");

assert_checkequal(doc1.root.children(1).children(1).name,"b");
assert_checkequal(doc1.root.children(1).children(1).content,"Hello");


XMLStream="<?xml version=""1.0""?>";
XMLStream=XMLStream+"<root attr=""value""><a>hello</a>";
XMLStream=XMLStream+"<b id=""123""> world</b></root>";

fd_w = mopen(TMPDIR+'/plop.xml','w+');
mputl(XMLStream, fd_w);
mclose(fd_w);

doc2 = xmlRead("TMPDIR/plop.xml"); 
a2 = doc2.root.children(2).attributes;
assert_checkequal(a2(1),"123");
assert_checkequal(a2(2),[]);
xmlDelete(doc2);

doc2 = xmlRead("TMPDIR/plop.xml");
doc2.root.children(2).attributes.id="";
a2 = doc2.root.children(2).attributes;
assert_checkequal(a2(1),"");
assert_checkequal(doc2.root.children(2).attributes.id,"");
assert_checkequal(a2(2),[]);
xmlDelete(doc2);

doc2 = xmlRead("TMPDIR/plop.xml");
a2 = doc2.root.children(2).attributes;
a2.id="";
doc2.root.children(2).attributes=a2;
assert_checkequal(doc2.root.children(2).attributes.id,"");
xmlDelete(doc2);



