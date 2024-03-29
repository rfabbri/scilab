# Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
# Copyright (C) 2006-2008 - INRIA - Sylvestre LEDRU
#
# This file must be used under the terms of the CeCILL.
# This source file is licensed as described in the file COPYING, which
# you should have received as part of this distribution.  The terms
# are also available at
# http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt


LOCALIZATION_C_SOURCES = \
src/c/InitializeLocalization.c \
src/c/setgetlanguage.c \
src/c/getLcidString.c \
src/c/charEncoding.c \
src/c/setdefaultlanguage.c

if NEED_JAVA
LOCALIZATION_C_SOURCES+=src/jni/Messages_wrap.c \
src/jni/LocaleToLCID_wrap.c \
src/jni/setdefaultlanguage_wrap.c
endif

if IS_MACOSX
LOCALIZATION_C_SOURCES += src/c/getLocaleInfo_Apple.c
endif

GATEWAY_C_SOURCES = sci_gateway/c/gw_localization.c \
sci_gateway/c/sci_gettext.c \
sci_gateway/c/sci_dgettext.c \
sci_gateway/c/sci_setlanguage.c \
sci_gateway/c/sci_getdefaultlanguage.c \
sci_gateway/c/sci_getlanguage.c \
sci_gateway/c/sci_setdefaultlanguage.c

libscilocalization_la_CPPFLAGS = $(JAVA_JNI_INCLUDE) \
				-I$(srcdir)/includes/ \
				-I$(srcdir)/src/c/ \
				-I$(top_srcdir)/modules/string/includes/ \
				-I$(top_srcdir)/modules/fileio/includes/ \
				-I$(top_srcdir)/modules/api_scilab/includes/ \
				-I$(top_srcdir)/modules/output_stream/includes \
				$(AM_CPPFLAGS)

pkglib_LTLIBRARIES = libscilocalization.la
noinst_LTLIBRARIES = libscilocalization-algo.la

libscilocalization_la_LDFLAGS = $(AM_LDFLAGS)
libscilocalization_la_CFLAGS = $(AM_CFLAGS)

# FIXME: platform dependent things should be in configure.ac
if IS_MACOSX
libscilocalization_la_LDFLAGS += -lintl -framework Cocoa
libscilocalization_la_CFLAGS += -lintl -framework Cocoa
endif

libscilocalization_algo_la_SOURCES = $(LOCALIZATION_C_SOURCES)
libscilocalization_la_SOURCES = $(GATEWAY_C_SOURCES)
libscilocalization_algo_la_CPPFLAGS = $(libscilocalization_la_CPPFLAGS)
libscilocalization_algo_la_CFLAGS = $(libscilocalization_la_CFLAGS)
libscilocalization_algo_la_LDFLAGS = $(libscilocalization_la_LDFLAGS)

# For the code check (splint)
CHECK_SRC= $(libscilocalization_la_SOURCES)
INCLUDE_FLAGS = $(libscilocalization_la_CPPFLAGS)

libscilocalization_la_LIBADD = libscilocalization-algo.la

# $(top_builddir)/modules/io/libsciio.la
#### Target ######
modulename=localization

#### localization : Conf files ####
libscilocalization_la_rootdir = $(mydatadir)
libscilocalization_la_root_DATA =  license.txt


####localization : init scripts ####
libscilocalization_la_etcdir = $(mydatadir)/etc
libscilocalization_la_etc_DATA = etc/localization.quit etc/localization.start

####�localization : gateway declaration ####
libscilocalization_la_sci_gatewaydir = $(mydatadir)/sci_gateway
libscilocalization_la_sci_gateway_DATA = sci_gateway/localization_gateway.xml


####localization : include files ####
libscilocalization_la_includedir=$(pkgincludedir)
libscilocalization_la_include_HEADERS = includes/localization.h \
includes/setgetlanguage.h \
includes/charEncoding.h

if GUI
USEANT=1
endif

#### SWIG Declaration ####
SWIG_WRAPPERS = src/jni/Messages.i \
src/jni/LocaleToLCID.i

if SWIG
BUILT_SOURCES=swig
endif


include $(top_srcdir)/Makefile.incl.am
