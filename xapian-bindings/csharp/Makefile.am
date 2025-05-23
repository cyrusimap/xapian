## Process this file with automake to produce Makefile.in

include ../generic/generic.mk

## Test programs to be run
TESTS = SmokeTest.exe
LOG_COMPILER = $(MACOS_SIP_HACK_ENV) $(RUN_CSHARP)

ASSEMBLY=XapianSharp

XAPIAN_SWIG_CS_SRCS=\
	generated-csharp/BB2Weight.cs \
	generated-csharp/BM25PlusWeight.cs\
	generated-csharp/BM25Weight.cs \
	generated-csharp/BoolWeight.cs \
	generated-csharp/Compactor.cs \
	generated-csharp/CoordWeight.cs \
	generated-csharp/Database.cs \
	generated-csharp/DateRangeProcessor.cs \
	generated-csharp/DecreasingValueWeightPostingSource.cs \
	generated-csharp/DiceCoeffWeight.cs \
	generated-csharp/DLHWeight.cs \
	generated-csharp/DPHWeight.cs \
	generated-csharp/Document.cs \
	generated-csharp/ESet.cs \
	generated-csharp/ESetIterator.cs \
	generated-csharp/Enquire.cs \
	generated-csharp/ExpandDecider.cs \
	generated-csharp/ExpandDeciderAnd.cs \
	generated-csharp/ExpandDeciderFilterPrefix.cs \
	generated-csharp/FieldProcessor.cs \
	generated-csharp/FixedWeightPostingSource.cs \
	generated-csharp/GreatCircleMetric.cs \
	generated-csharp/IfB2Weight.cs \
	generated-csharp/IneB2Weight.cs \
	generated-csharp/InL2Weight.cs \
	generated-csharp/KeyMaker.cs \
	generated-csharp/LM2StageWeight.cs \
	generated-csharp/LMAbsDiscountWeight.cs \
	generated-csharp/LMDirichletWeight.cs \
	generated-csharp/LMJMWeight.cs \
	generated-csharp/LatLongCoord.cs \
	generated-csharp/LatLongCoords.cs \
	generated-csharp/LatLongCoordsIterator.cs \
	generated-csharp/LatLongDistanceKeyMaker.cs \
	generated-csharp/LatLongDistancePostingSource.cs \
	generated-csharp/LatLongMetric.cs \
	generated-csharp/MatchDecider.cs \
	generated-csharp/MatchSpy.cs \
	generated-csharp/MSet.cs \
	generated-csharp/MSetIterator.cs \
	generated-csharp/MultiValueKeyMaker.cs \
	generated-csharp/NumberRangeProcessor.cs \
	generated-csharp/PL2PlusWeight.cs \
	generated-csharp/PL2Weight.cs \
	generated-csharp/PositionIterator.cs \
	generated-csharp/PostingIterator.cs \
	generated-csharp/PostingSource.cs \
	generated-csharp/Query.cs \
	generated-csharp/QueryParser.cs \
	generated-csharp/Remote.cs \
	generated-csharp/RSet.cs \
	generated-csharp/SWIGTYPE_p_std__string.cs \
	generated-csharp/RangeProcessor.cs \
	generated-csharp/Registry.cs \
	generated-csharp/SimpleStopper.cs \
	generated-csharp/Stem.cs \
	generated-csharp/StemImplementation.cs \
	generated-csharp/Stopper.cs \
	generated-csharp/TermGenerator.cs \
	generated-csharp/TermIterator.cs \
	generated-csharp/TfIdfWeight.cs \
	generated-csharp/TradWeight.cs \
	generated-csharp/UnitRangeProcessor.cs \
	generated-csharp/ValueCountMatchSpy.cs \
	generated-csharp/ValueIterator.cs \
	generated-csharp/ValueMapPostingSource.cs \
	generated-csharp/ValuePostingSource.cs \
	generated-csharp/ValueSetMatchDecider.cs \
	generated-csharp/ValueWeightPostingSource.cs \
	generated-csharp/Version.cs \
	generated-csharp/Weight.cs \
	generated-csharp/WritableDatabase.cs \
	generated-csharp/Xapian.cs \
	generated-csharp/XapianPINVOKE.cs

XapianSharp.snk:
## Older cli-sn fails with certain TERM setting (e.g. xterm-256color) due to:
## https://github.com/mono/mono/issues/6752
## Seen on Kubuntu 18.10.
	TERM= $(SN) -k $@

$(ASSEMBLY).dll: $(XAPIAN_SWIG_CS_SRCS) AssemblyInfo.cs XapianSharp.snk
## We specify both -keyfile and -keycontainer - hopefully this means that if
## this is the first time we're signing, the key in the file is used and
## then stored in the key container.  From then on, the key in the container
## is used.
	TERM= $(CSC) -unsafe -target:library -out:$(ASSEMBLY).dll \
	    -keyfile:XapianSharp.snk -keycontainer:"Xapian Signing Key" \
	    `for f in $(XAPIAN_SWIG_CS_SRCS); do if test -f "$$f"; then echo $$f; else echo $(srcdir)/$$f ; fi ; done` \
	    AssemblyInfo.cs

SWIG_GENERATED = xapian_wrap.cc xapian_wrap.h $(XAPIAN_SWIG_CS_SRCS)

BUILT_SOURCES = $(SWIG_GENERATED)

EXTRA_DIST = csharp.i SmokeTest.cs docs/index.rst $(SWIG_GENERATED)

lib_LTLIBRARIES = _XapianSharp.la

# Remove the .la file - _XapianSharp.la is never linked against (it's a module)
# and C# doesn't use libltdl.  Note that the library gets installed by
# install-data, so that's where we need to hook.
install-data-hook:
	rm -f $(DESTDIR)$(libdir)/_XapianSharp.la

# Because we don't install the .la file, "make uninstall" doesn't work and
# we need to remove the file ourselves.
uninstall-local:
	eval `grep '^dlname=' $(lib_LTLIBRARIES)` ; \
	  rm -f $(DESTDIR)$(libdir)/"$$dlname"
	TERM= $(GACUTIL) /u $(ASSEMBLY) /f $(GACUTIL_FLAGS)

AM_CXXFLAGS = @SWIG_CXXFLAGS@ $(XAPIAN_CXXFLAGS)
_XapianSharp_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED)
_XapianSharp_la_SOURCES = xapian_wrap.cc
_XapianSharp_la_LIBADD = $(XAPIAN_LIBS)

install-data-local: $(ASSEMBLY).dll
	TERM= $(GACUTIL) /i $(ASSEMBLY).dll /f $(GACUTIL_FLAGS)

SmokeTest.exe: SmokeTest.cs $(ASSEMBLY).dll
	TERM= $(CSC) -unsafe -target:exe -out:SmokeTest.exe `test -f SmokeTest.cs||echo '$(srcdir)/'`SmokeTest.cs -r:$(ASSEMBLY).dll

all-am: $(ASSEMBLY).dll

CLEANFILES = XapianSharp.snk $(ASSEMBLY).dll SmokeTest.exe

if MAINTAINER_MODE
stamp = xapian_wrap.stamp
SWIG_FLAGS += -MD -MP -MT $(stamp)

xapian_wrap.cc xapian_wrap.h $(XAPIAN_SWIG_CS_SRCS): $(stamp)
	$(make_many_locked)
$(stamp):
	$(multitarget_begin)
	: # Make sure that we don't package stale generated sources in the
	: # case where SWIG changes its mind as to which files it generates.
	-rm -f generated-csharp/*
	$(MKDIR_P) generated-csharp
	$(SWIG) $(SWIG_WERROR) -I'$(srcdir)' $(SWIG_FLAGS) -c++ \
	    -csharp -namespace Xapian -module Xapian -dllimport _XapianSharp \
	    -o xapian_wrap.cc -outdir generated-csharp '$(srcdir)/'csharp.i
	: # Check that exactly the sources we expected were generated.
	$(PERL) -e 'print "$$_\n" for sort @ARGV' generated-csharp/*.cs > generated-csharp/list
	$(PERL) -e 'print "$$_\n" for sort @ARGV' $(XAPIAN_SWIG_CS_SRCS)|diff -c - generated-csharp/list
	$(multitarget_end)

-include xapian_wrap.d

CLEANFILES += $(stamp)
endif
MAINTAINERCLEANFILES = $(BUILT_SOURCES)

maintainer-clean-local:
	rm -rf generated-csharp

exampledatadir = $(docdir)/csharp/examples
dist_exampledata_DATA =\
	docs/examples/SimpleSearch.cs\
	docs/examples/SimpleIndex.cs\
	docs/examples/SimpleExpand.cs

docdatadir = $(docdir)/csharp
dist_docdata_DATA = docs/index.html

if DOCUMENTATION_RULES
BUILT_SOURCES += docs/index.html

.rst.html:
	-case "$@" in */*) d=`echo "$@"|sed 's,/[^/]*$$,,'`; $(MKDIR_P) "$$d" ;; esac
	$(RST2HTML) --exit-status=warning $< $@
endif
