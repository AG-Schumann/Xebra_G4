# --------------------------------------------
# GNUmakefile - Based on the XENON MC code
# Updated: Wed Mar 07 2018
# --------------------------------------------

#USENEST := true # Comment out to disable NEST
# WARNING: Do not uncomment this, use instead e.g. command "make -j4 USENEST=true"

name := xebra_G4

#GEANTVERSION    = $(shell geant4-config --version | cut -d'.' -f1)

G4TARGET := $(name)
G4EXLIB := true
MYEXEPATH :=$(G4WORKDIR)/bin/$(G4SYSTEM)
#CPPVERBOSE := true

G4DEBUG := 0

GEANTLIBS       = $(shell geant4-config --libs)
ROOTCFLAGS      = $(shell root-config --cflags)
ROOTGLIBS       = $(shell root-config --glibs)

EXTRALIBS +=$(ROOTGLIBS) $(GEANTLIBS)

CPPFLAGS += $(ROOTCFLAGS)

.PHONY: all

all: check_vers lib bin

check_vers: 

include config/binmake.gmk
