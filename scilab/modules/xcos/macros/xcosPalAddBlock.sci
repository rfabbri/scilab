//
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) DIGITEO - 2010-2010 - Clément DAVID
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
//
//

// Add a block to a palette instance.
//
// @param pal the "Palette" instance
// @param block the block to add
// @param[opt] pal_block_img full path to the block image used in the palette.
// @param[opt] style full path to the block image used in the diagram or block style (jgraphx format)
// @return pal the modified pal instance
function pal = xcosPalAddBlock(pal, block, pal_block_img, style)

    // Checking arguments
    [lhs,rhs] = argn(0)
    if rhs < 2 | rhs > 5 then
        error(msprintf(gettext("%s: Wrong number of input arguments: %d to %d expected.\n"), "xcosPalAddBlock", 2, 5));
    end
    
    if lhs > 1 then
        error(msprintf(gettext("%s: Wrong number of output arguments: %d expected.\n"), "xcosPalAddBlock", 1));
    end
    
    if typeof(pal) <> "palette" then
        error(msprintf(gettext("%s: Wrong type for input argument ""%s"": palette type expected.\n"), "xcosPalAddBlock", "pal"));
    end
    
    // check and tranform block argument
    
    if typeof(block) == "Block" then
        path = TMPDIR + "/" + block.gui + ".h5";
        scs_m = block;
        err = export_to_hdf5(path, "scs_m");
        if err <> %T then
            error(msprintf(gettext("%s: Unable to export ""%s"" to ""%s"".\n"), "xcosPalAddBlock", "block", path));
        end
        
        block = path; // block mute to a full path string.
    end
    
    if typeof(block) == "string" then
        if exists(block) <> 0 & typeof(evstr(block)) == "function" then
            execstr("scs_m = " + block + "(""define"");");
            path = TMPDIR + "/" + block + ".h5";
            err = export_to_hdf5(path, "scs_m");
            if err <> %T then
                error(msprintf(gettext("%s: Unable to export ""%s"" to ""%s"".\n"), "xcosPalAddBlock", "block", path));
            end
            
            block = path; // block mute to a full path string.
        else // assume this is a path
            fd = mopen(block, "rb");
            [err, msg] = merror(fd);
            if err <> 0 then
                error(msg);
            end
            block = fullpath(block);
            mclose(fd);
            
            // store the block instance if not already saved
            if exists("scs_m", 'l') == 0 then
                status = import_from_hdf5(block);
                if ~status then
                    error(msprintf(gettext("%s: Unable to load block from ""%s"": hdf5 file expected.\n"), "xcosPalAddBlock", block));
                end
                
                if exists("scs_m", 'l') == 0 then
                    error(msprintf(gettext("%s: Unable to load block from ""%s"": no `scs_m'' variable found.\n"), "xcosPalAddBlock", block));
                end
            end
        end
    else
        error(msprintf(gettext("%s: Wrong type for input argument ""%s"": function as string or Block type or full path string expected.\n"), "xcosPalAddBlock", "block"));
    end
    
    // at this point we can assert that `block' is a full path string to a 
    // saved block reference instance (hdf5 format) also kept into 
    // `scs_m'.
    // now handle pal_block_img and style arguments
    
    if exists("pal_block_img", 'l') == 0 then
        pal_block_img = TMPDIR + "/" + scs_m.gui + ".gif";
        if isfile(pal_block_img) then
            error(msprintf(gettext("%s: Unable to generate the palette icon : ""%s"" already exists.\n"), "xcosPalAddBlock", pal_block_img));
        end
    else
        if typeof(pal_block_img) <> "string" | ~isfile(pal_block_img) then
            error(msprintf(gettext("%s: Wrong type for input argument ""%s"": path string expected.\n"), "xcosPalAddBlock", "pal_block_img"));
        end
        currentFile = ls(pal_block_img); // evaluate wildcard and path
        if size(currentFile, '*') <> 1 then
            error(msprintf(gettext("%s: Wrong type for input argument ""%s"": path string expected.\n"), "xcosPalAddBlock", "pal_block_img"));
        end
        pal_block_img = fullpath(currentFile);
    end
    
    if exists("style", 'l') == 0 then
        block_img = TMPDIR + "/" + scs_m.gui + ".svg";
        style = "image=file:" + block_img + ";";
        status = generateBlockImage(scs_m, TMPDIR, imageType="svg");
        if ~status then
            error(msprintf(gettext("%s: Unable to generate the image ""%s"".\n"), "xcosPalAddBlock", block_img));
        end
    else
        if typeof(style) <> "st" & typeof(style) <> "string" then
            error(msprintf(gettext("%s: Wrong type for input argument ""%s"": string or struct expected.\n"), "xcosPalAddBlock", "style"));
        elseif typeof(style) == "st" then
            formattedStyle = "";
            fields = fieldnames(style);
            fieldsSize = size(fields, '*');
            for i=1:fieldsSize
                formattedStyle = fields(i) + "=" + ..
                    getfield(fields(i), style) + ";" + formattedStyle;
            end
            style = formattedStyle;
        elseif typeof(style) == "string" then
            currentFile = ls(style); // evaluate wildcard and path
            if size(currentFile, '*') == 1 then
                style = fullpath(currentFile);
                style = "image=file:" + style + ";";
            else
                // assume well formatted string, do nothing
            end
        end
    end
    
    // Store the data into the palette structure
    pal.blockNames($+1) = scs_m.gui // block named class
    pal.blocks($+1) = block; // reference instance full path string
    pal.icons($+1) = pal_block_img; // palette icon full path string
    pal.style($+1) = style; // block style (linked to style definition)
endfunction
