dnl
dnl Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
dnl Copyright (C) DIGITEO - 2010 - Sylvestre Ledru
dnl 
dnl This file must be used under the terms of the CeCILL.
dnl This source file is licensed as described in the file COPYING, which
dnl you should have received as part of this distribution.  The terms
dnl are also available at    
dnl http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
dnl

#------------------------------------------------------------------------
# AC_JAVA_CHECK_VERSION_PACKAGE(NAME, IMPORTS, JAR, MIN_VERSION, CURRENT_VERSION)
#
# Check if the minimal version of a software/package is available or not.
# Note that since java does not provide an universal mechanism to detect
# the version of a package, some work is left to the user.
# I will update this work when OSGI is more supported.
#
# Arguments:
#	1. The name of the package (only used in the display of feedbacks)
#	2. Which imports are necessary in the check
#	3. The name of the jar files used to build against
#	4. What is the minimal version expected
#	5. The Java code to get the version ... This can be a serie of java
#	   instructions
#
#------------------------------------------------------------------------

AC_DEFUN([AC_JAVA_CHECK_VERSION_PACKAGE], [
    AC_MSG_CHECKING([minimal version ($4) of $1])
   saved_ac_java_classpath=$ac_java_classpath
   export ac_java_classpath="$3:$ac_java_classpath"
   AC_JAVA_TRY_COMPILE($2, [String minVersion="$4";
   						   	if (minVersion.compareTo($5) > 0) {
							   	System.exit(-1); 
								}
							], echo "yes" , AC_MSG_ERROR([Wrong version of $1. Expected at least $4]))
   ac_java_classpath=$saved_ac_java_classpath
])