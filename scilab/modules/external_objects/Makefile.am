#
# Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
# Copyright (C) 2012 - Scilab Enterprises - Calixte DENIZET
#
# This file must be used under the terms of the CeCILL.
# This source file is licensed as described in the file COPYING, which
# you should have received as part of this distribution. The terms
# are also available at
# http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
#

#### Target ######
modulename=external_objects


#### external_objects : Conf files ####
libsciexternal_objects_la_rootdir = $(mydatadir)
libsciexternal_objects_la_root_DATA =  license.txt 


#### external_objects : init scripts & configuration files ####
libsciexternal_objects_la_etcdir = $(mydatadir)/etc
libsciexternal_objects_la_etc_DATA = etc/external_objects.quit \
									 etc/external_objects.start

include $(top_srcdir)/Makefile.incl.am

EXTERNAL_OBJECTS_JNI_SOURCES = 

EXTERNAL_OBJECTS_C_SOURCES = 

EXTERNAL_OBJECTS_CPP_SOURCES = src/cpp/ScilabEnvironments.cpp \
			       src/cpp/ScilabObjects.cpp \
			       src/cpp/OptionsHelper.cpp \
			       src/cpp/addToClasspath.cpp \
			       src/cpp/getClasspath.cpp \
			       src/cpp/getsetOptions.cpp \
			       src/cpp/getEnvironmentInfos.cpp \
			       src/cpp/array.cpp \
			       src/cpp/operation.cpp \
			       src/cpp/cast.cpp \
			       src/cpp/compile.cpp \
			       src/cpp/convMatrixMethod.cpp \
			       src/cpp/deff.cpp \
			       src/cpp/display.cpp \
			       src/cpp/doubleExclam_invoke.cpp \
			       src/cpp/classExtract.cpp \
			       src/cpp/objectExtract.cpp \
			       src/cpp/objectInsert.cpp \
			       src/cpp/objectPrint.cpp \
			       src/cpp/exists.cpp \
			       src/cpp/getClassName.cpp \
			       src/cpp/getEnvironmentName.cpp \
			       src/cpp/getField.cpp \
			       src/cpp/getFields.cpp \
			       src/cpp/getMethods.cpp \
			       src/cpp/getRepresentation.cpp \
			       src/cpp/import.cpp \
			       src/cpp/invoke.cpp \
			       src/cpp/invoke_asref.cpp \
			       src/cpp/invoke_lu.cpp \
			       src/cpp/trace.cpp \
			       src/cpp/newInstance.cpp \
			       src/cpp/remove.cpp \
			       src/cpp/setField.cpp \
			       src/cpp/evalString.cpp \
			       src/cpp/addNamedVariable.cpp \
			       src/cpp/getNamedVariable.cpp \
			       src/cpp/unwrap.cpp \
			       src/cpp/wrap.cpp \
			       src/cpp/unwrapremove.cpp \
			       src/cpp/wrapAsRef.cpp \
			       src/cpp/invoker.cpp \
			       src/cpp/getEnvId.cpp \
			       src/cpp/ScilabOptionsSetter.cpp \
			       src/cpp/ScilabAutoCleaner.cpp \
			       src/cpp/ExternalObjectsFunction.cpp \
			       src/cpp/wrapInFloat.cpp

GATEWAY_C_SOURCES = sci_gateway/c/gw_external_objects.c

GATEWAY_CPP_SOURCES = sci_gateway/cpp/sci_percent_EObj_e.cpp \
	sci_gateway/cpp/sci_percent_EObj_p.cpp \
	sci_gateway/cpp/sci_percent_foo_i_EObj.cpp \
	sci_gateway/cpp/sci_percent_EClass_e.cpp \
	sci_gateway/cpp/sci_percent_EObj_a_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_d_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_g_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_h_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_j_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_k_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_l_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_m_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_n_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_o_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_p_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_q_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_r_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_s_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_x_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_y_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_z_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_1_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_2_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_3_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_4_foo.cpp \
	sci_gateway/cpp/sci_percent_EObj_0.cpp \
	sci_gateway/cpp/sci_percent_EObj_5.cpp \
	sci_gateway/cpp/sci_percent_EObj_t.cpp \
	sci_gateway/cpp/sci_doubleExclam_invoke_.cpp \
	sci_gateway/cpp/sci_invoke_lu.cpp \
	sci_gateway/cpp/sci_percent_EObj_disp.cpp

libsciexternal_objects_la_CFLAGS= -I$(srcdir)/includes/ \
             -I$(top_srcdir)/modules/core/includes \
             -I$(top_srcdir)/modules/api_scilab/includes \
             -I$(top_srcdir)/modules/output_stream/includes \
             -I$(top_srcdir)/modules/string/includes \
             -I$(top_srcdir)/modules/fileio/includes


libsciexternal_objects_la_CPPFLAGS = -I$(srcdir)/includes/ \
    -I$(srcdir)/src/cpp/ \
    -I$(srcdir)/src/c/ \
    -I$(top_srcdir)/modules/localization/includes \
    -I$(top_srcdir)/modules/api_scilab/includes \
    -I$(top_srcdir)/modules/output_stream/includes \
    -I$(top_srcdir)/modules/string/includes \
    -I$(top_srcdir)/modules/fileio/includes \
    -I$(top_srcdir)/modules/core/src/c \
    $(EXTERNAL_OBJECTS_FLAGS)


pkglib_LTLIBRARIES = libsciexternal_objects.la 
noinst_LTLIBRARIES = libsciexternal_objects-algo.la 

libsciexternal_objects_la_LDFLAGS = -version-number $(SCILAB_LIBRARY_VERSION) $(LD_FLAGS)  $(X_LIBS) $(X_EXTRA_LIBS)

libsciexternal_objects_algo_la_SOURCES = $(EXTERNAL_OBJECTS_C_SOURCES) $(EXTERNAL_OBJECTS_JNI_SOURCES) $(EXTERNAL_OBJECTS_CPP_SOURCES)
libsciexternal_objects_la_SOURCES = $(GATEWAY_C_SOURCES) $(GATEWAY_CPP_SOURCES) 
libsciexternal_objects_algo_la_CFLAGS = $(libsciexternal_objects_la_CFLAGS)
libsciexternal_objects_algo_la_CPPFLAGS = $(libsciexternal_objects_la_CPPFLAGS)

libsciexternal_objects_la_LIBADD = libsciexternal_objects-algo.la

# For the code check (splint)
CHECK_SRC= $(EXTERNAL_OBJECTS_C_SOURCES) $(GATEWAY_C_SOURCES)
INCLUDE_FLAGS = $(libsciexternal_objects_la_CFLAGS)

#### external_objects : gateway declaration ####
libsciexternal_objects_la_sci_gatewaydir = $(mydatadir)/sci_gateway
libsciexternal_objects_la_sci_gateway_DATA = sci_gateway/external_objects_gateway.xml

#### external_objects : include files ####
libsciexternal_objects_la_includedir=$(pkgincludedir)
libsciexternal_objects_la_include_HEADERS = includes/ExternalObjects.h \
includes/dynlib_external_objects_scilab.h \
includes/OptionsHelper.hxx \
includes/ScilabAbstractEnvironmentException.hxx \
includes/ScilabAbstractInvoker.hxx \
includes/ScilabAbstractOptionsSetter.hxx \
includes/ScilabEnvironments.hxx \
includes/ScilabGatewayOptions.hxx \
includes/ScilabOptionsSetter.hxx \
includes/ScilabAbstractEnvironment.hxx \
includes/ScilabAbstractEnvironmentWrapper.hxx \
includes/ScilabAbstractMemoryAllocator.hxx \
includes/ScilabAutoCleaner.hxx \
includes/ScilabGateway.hxx \
includes/ScilabObjects.hxx \
includes/ScilabStream.hxx
