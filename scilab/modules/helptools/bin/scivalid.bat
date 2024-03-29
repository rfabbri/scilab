rem Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
rem Copyright (C) 2008 - INRIA
rem 
rem This file must be used under the terms of the CeCILL.
rem This source file is licensed as described in the file COPYING, which
rem you should have received as part of this distribution.  The terms
rem are also available at
rem http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt

@echo off
setlocal

if "%1"=="" goto usage

set binDir=%~dp0
set libDir=%binDir%\..\..\..\thirdparty
set schemaDir=%binDir%\..\schema

java -jar "%libDir%\jing.jar" "%schemaDir%\scilab.rng" %*

goto end
endlocal

:usage
echo Usage: scivalid xml_file ... xml_file
echo Validates specified XML files against the scilab.rng schema.

:end

