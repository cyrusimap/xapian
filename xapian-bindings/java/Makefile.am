## Process this file with automake to produce Makefile.in

include ../generic/generic.mk

# Disable parallel build for this make invocation; javac seems to write
# .class files in place, and it also reads existing .class files - the
# combination means that in a parallel build it can read partial .class
# and then fail with various odd errors.
.NOTPARALLEL:

## Test programs to be run
TESTS = SmokeTest.class
AM_TESTS_ENVIRONMENT = \
	LIBTOOL="$(LIBTOOL)" ;\
	JAVA="$(JAVA) $(JAVA_CHECK_JNI_OPTION)" ;\
	PATHSEP="$(JAVA_PATHSEP)" ;\
	_libs="$(_libs)" ;\
	export LIBTOOL ;\
	export JAVA ;\
	export PATHSEP ;\
	export _libs ;
LOG_COMPILER = $(srcdir)/run-java-test

CLEANFILES = SmokeTest.class MyMatchDecider.class MyExpandDecider.class\
	MyFieldProcessor.class\
	built/xapian.jar\
	$(XAPIAN_SWIG_JAVA_CLASS) $(XAPIAN_SWIG_JAVA_EXTRA_CLASSES)

SmokeTest: SmokeTest.class

# To get debug symbols, use: make JAVACFLAGS=-g
.java.class:
	$(JAVAC) $(JAVACFLAGS) -classpath .$(JAVA_PATHSEP)$(srcdir) -d . $<

XAPIAN_SWIG_JAVA_SRCS=\
	org/xapian/BB2Weight.java\
	org/xapian/BM25PlusWeight.java\
	org/xapian/BM25Weight.java\
	org/xapian/BoolWeight.java\
	org/xapian/Compactor.java\
	org/xapian/CoordWeight.java\
	org/xapian/Database.java\
	org/xapian/DateRangeProcessor.java\
	org/xapian/DecreasingValueWeightPostingSource.java\
	org/xapian/DiceCoeffWeight.java\
	org/xapian/DLHWeight.java\
	org/xapian/DPHWeight.java\
	org/xapian/Document.java\
	org/xapian/Enquire.java\
	org/xapian/ESet.java\
	org/xapian/ESetIterator.java\
	org/xapian/ExpandDecider.java\
	org/xapian/ExpandDeciderAnd.java\
	org/xapian/ExpandDeciderFilterPrefix.java\
	org/xapian/FieldProcessor.java\
	org/xapian/FixedWeightPostingSource.java\
	org/xapian/GreatCircleMetric.java\
	org/xapian/IfB2Weight.java\
	org/xapian/IneB2Weight.java\
	org/xapian/InL2Weight.java\
	org/xapian/KeyMaker.java\
	org/xapian/LM2StageWeight.java\
	org/xapian/LMAbsDiscountWeight.java\
	org/xapian/LMDirichletWeight.java\
	org/xapian/LMJMWeight.java\
	org/xapian/LatLongCoord.java\
	org/xapian/LatLongCoords.java\
	org/xapian/LatLongCoordsIterator.java\
	org/xapian/LatLongDistanceKeyMaker.java\
	org/xapian/LatLongDistancePostingSource.java\
	org/xapian/LatLongMetric.java\
	org/xapian/MatchDecider.java\
	org/xapian/MatchSpy.java\
	org/xapian/MSet.java\
	org/xapian/MSetIterator.java\
	org/xapian/MultiValueKeyMaker.java\
	org/xapian/NumberRangeProcessor.java\
	org/xapian/PL2PlusWeight.java\
	org/xapian/PL2Weight.java\
	org/xapian/PositionIterator.java\
	org/xapian/PostingIterator.java\
	org/xapian/PostingSource.java\
	org/xapian/Query.java\
	org/xapian/QueryParser.java\
	org/xapian/RangeProcessor.java\
	org/xapian/Registry.java\
	org/xapian/Remote.java\
	org/xapian/RSet.java\
	org/xapian/SimpleStopper.java\
	org/xapian/Stem.java\
	org/xapian/StemImplementation.java\
	org/xapian/Stopper.java\
	org/xapian/SWIGTYPE_p_std__string.java\
	org/xapian/TermGenerator.java\
	org/xapian/TermIterator.java\
	org/xapian/TfIdfWeight.java\
	org/xapian/TradWeight.java\
	org/xapian/UnitRangeProcessor.java\
	org/xapian/ValueCountMatchSpy.java\
	org/xapian/ValueIterator.java\
	org/xapian/ValueMapPostingSource.java\
	org/xapian/ValuePostingSource.java\
	org/xapian/ValueSetMatchDecider.java\
	org/xapian/ValueWeightPostingSource.java\
	org/xapian/Version.java\
	org/xapian/Weight.java\
	org/xapian/WritableDatabase.java\
	org/xapian/Xapian.java\
	org/xapian/XapianConstants.java\
	org/xapian/XapianJNI.java

XAPIAN_SWIG_JAVA_CLASS = $(XAPIAN_SWIG_JAVA_SRCS:.java=.class)

# Java generates nested classes with filenames containing a $ (smart move) so
# we pick them up with a wildcard and omit them from dependencies to avoid
# escaping hell.  The lack of a dependency shouldn't really be an issue since
# these classes are always generated along with the containing class which
# is listed in the dependencies.
XAPIAN_SWIG_JAVA_EXTRA_CLASSES=\
	org/xapian/Compactor*compaction_level.class\
	org/xapian/Enquire*docid_order.class\
	org/xapian/Query*1.class\
	org/xapian/Query*op.class\
	org/xapian/QueryParser*feature_flag.class\
	org/xapian/QueryParser*stem_strategy.class\
	org/xapian/TermGenerator*flags.class\
	org/xapian/TermGenerator*stem_strategy.class\
	org/xapian/TermGenerator*stop_strategy.class\
	org/xapian/Weight*type_smoothing.class

noinst_DATA = built/xapian.jar

built/xapian.jar: $(XAPIAN_SWIG_JAVA_CLASS)
	$(MKDIR_P) built
	$(JAR) -cf built/xapian.jar org/xapian/*.class
##$(XAPIAN_SWIG_JAVA_CLASS) $(XAPIAN_SWIG_JAVA_EXTRA_CLASSES)

jnidir = $(abs_builddir)/built

jni_LTLIBRARIES = libxapian_jni.la

# Remove the .la file - libxapian_jni.la is never linked against (it's a
# module) and JVMs don't use libltdl.  Note that the library gets installed by
# install-data, so that's where we need to hook.
install-data-hook:
	rm -f $(DESTDIR)$(jnidir)/libxapian_jni.la

# Because we don't install the .la file, "make uninstall" doesn't work and
# we need to remove the file ourselves.
uninstall-local:
if NEED_JNILIB_EXT
	rm -f $(DESTDIR)$(jnidir)/libxapian_jni.jnilib
else
	eval `grep '^dlname=' $(jni_LTLIBRARIES)` ; \
	  rm -f $(DESTDIR)$(jnidir)/"$$dlname"
endif

if NEED_JNILIB_EXT
SHREXT=-shrext .jnilib
else
SHREXT=
endif
AM_CXXFLAGS = $(SWIG_CXXFLAGS) $(XAPIAN_CXXFLAGS)
AM_CPPFLAGS = $(JAVA_CPPFLAGS)
libxapian_jni_la_LDFLAGS = -avoid-version -module $(SHREXT) $(NO_UNDEFINED)
libxapian_jni_la_LIBADD = $(XAPIAN_LIBS)
libxapian_jni_la_SOURCES = xapian_wrap.cc

SWIG_GENERATED = xapian_wrap.cc xapian_wrap.h $(XAPIAN_SWIG_JAVA_SRCS)

BUILT_SOURCES = $(SWIG_GENERATED)

EXTRA_DIST = java.i run-java-test SmokeTest.java docs/index.rst $(SWIG_GENERATED)

if MAINTAINER_MODE
stamp = xapian_wrap.stamp
SWIG_FLAGS += -MD -MP -MT $(stamp)

xapian_wrap.cc xapian_wrap.h $(XAPIAN_SWIG_JAVA_SRCS): $(stamp)
	$(make_many_locked)
$(stamp):
	$(multitarget_begin)
	: # Make sure that we don't package stale generated sources in the
	: # case where SWIG changes its mind as to which files it generates.
	-rm -f org/xapian/*
	$(MKDIR_P) org/xapian
	$(SWIG) $(SWIG_WERROR) -I'$(srcdir)' $(SWIG_FLAGS) -c++ \
	    -java -module Xapian -package org.xapian -outdir org/xapian \
	    -o xapian_wrap.cc '$(srcdir)/'java.i
	: # Check that exactly the sources we expected were generated.
	$(PERL) -e 'print "$$_\n" for sort @ARGV' org/xapian/*.java > org/xapian/list
	$(PERL) -e 'print "$$_\n" for sort @ARGV' $(XAPIAN_SWIG_JAVA_SRCS)|diff -c - org/xapian/list
	$(multitarget_end)

-include xapian_wrap.d

CLEANFILES += $(stamp)
endif
MAINTAINERCLEANFILES = $(BUILT_SOURCES)

maintainer-clean-local:
	rm -rf built org

exampledatadir = $(docdir)/java/examples
dist_exampledata_DATA =\
	docs/examples/SimpleSearch.java\
	docs/examples/SimpleIndex.java

docdatadir = $(docdir)/java
dist_docdata_DATA = docs/index.html

if DOCUMENTATION_RULES
BUILT_SOURCES += docs/index.html

.rst.html:
	-case "$@" in */*) d=`echo "$@"|sed 's,/[^/]*$$,,'`; $(MKDIR_P) "$$d" ;; esac
	$(RST2HTML) --exit-status=warning $< $@
endif
