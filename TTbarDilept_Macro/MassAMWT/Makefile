ObjSuf        = o
SrcSuf        = cc
ExeSuf        = 
DllSuf        = so
OutPutOpt     = -o

PWD           = $(shell pwd)
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs) -lGenVector -lMinuit -lMinuit2 -lTMVA

# CXX flags
DEFINES       = -DNO_ORCA_CLASSES
CXXFLAGS      = -O -Wall -fPIC $(DEFINES)
CXXFLAGS     += $(ROOTCFLAGS) -I./
# Libs

LDFLAGS       = -g -O -Wall -fPIC
LIBS          = $(ROOTLIBS) -lEG
LIBS         += -L$(PWD)/../../LHAPDF/lhapdf-5.8.9/lib/ -lLHAPDF -lyaml-cpp  -L JetMETObjects -l:../JetMETObjects/lib/libJetMETObjects.so
#LIBS         += -L$(PWD)/JetCorrections/ -lJetCorrections
SOFLAGS       = -shared


# Compiler and linker
CXX           = g++
LD            = g++

#------------------------------------------------------------------------------
SOURCES       = $(wildcard src/MassSolver.cc src/AMWT.cc src/TopMassVariables.cc)
HEADERS       = $(wildcard interface/Constants.h interface/MassSolver.h interface/TopMassVariables.h interface/AMWT.h)
OBJECTS       = $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS       = $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS      = $(SOURCES:.$(SrcSuf)=.$(DllSuf))

all:  libAMWT.so
	@mkdir -p .lib


libAMWT.so: $(OBJECTS)
	@echo "Building libAMWT..."
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $(OBJECTS) -o $@
	
clean:
	@echo "Cleaning..."
	@rm -f libAMWT.so src/*.o
	
	
	
	
	
	
	
	
	
	
	
	
