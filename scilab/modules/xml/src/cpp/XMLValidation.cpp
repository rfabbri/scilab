/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Calixte DENIZET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#include "XMLObject.hxx"
#include "XMLValidation.hxx"

extern "C" {
#include "expandPathVariable.h"
#include "MALLOC.h"
}

#define BUFFER_SIZE 1024

namespace org_modules_xml
{

    std::string * XMLValidation::errorBuffer = 0;
    std::list<XMLValidation *> & XMLValidation::openValidationFiles = *new std::list<XMLValidation *>();

    XMLValidation::XMLValidation() : XMLObject()
    {
        scilabType = XMLVALID;
    }

    void XMLValidation::errorFunction(void * ctx, const char * msg, ...)
    {
        char str[BUFFER_SIZE];
        va_list args;

        va_start(args, msg);
#ifdef _MSC_VER
        _vsnprintf(str, BUFFER_SIZE, msg, args);
#else
        std::vsnprintf(str, BUFFER_SIZE, msg, args);
#endif
        va_end(args);
        errorBuffer->append(str);
    }

    bool XMLValidation::validate(const std::string & xmlCode, std::string * error) const
    {
        xmlParserInputBuffer * buffer = xmlParserInputBufferCreateMem(xmlCode.c_str(), (int)xmlCode.size(), (xmlCharEncoding)0);
        bool valid = validate(xmlNewTextReader(buffer, 0), error);
        xmlFreeParserInputBuffer(buffer);

        return valid;
    }

    bool XMLValidation::validate(const char * path, std::string * error) const
    {
        char * expandedPath = expandPathVariable(const_cast<char *>(path));
        xmlTextReader * reader = xmlNewTextReaderFilename(expandedPath);
        FREE(expandedPath);
        return validate(reader, error);
    }

    const std::list<XMLValidation *> & XMLValidation::getOpenValidationFiles()
    {
        return openValidationFiles;
    }

    void XMLValidation::closeAllValidationFiles()
    {
        int size = (int)openValidationFiles.size();
        XMLValidation ** arr = new XMLValidation*[size];
        int j = 0;
        for (std::list<XMLValidation *>::iterator i = openValidationFiles.begin(); i != openValidationFiles.end(); i++, j++)
        {
            arr[j] = *i;
        }
        for (j = 0; j < size; j++)
        {
            delete arr[j];
        }
        delete [] arr;
    }
}