AMREX_HOME ?= ../../..
FFTW_DIR = /usr/users/cbehren2/local_libs/lib
DIM = 3

USE_MPI = TRUE

DEBUG = FALSE

COMP = Intel

include $(AMREX_HOME)/Tools/GNUMake/Make.defs

include ./Make.package
include $(AMREX_HOME)/Src/Base/Make.package
include $(AMREX_HOME)/Src/Boundary/Make.package

include $(AMREX_HOME)/Src/Extern/SWFFT/Make.package
INCLUDE_LOCATIONS	+= $(AMREX_HOME)/Src/Extern/SWFFT
INCLUDE_LOCATIONS	+= $(FFTW_DIR)/../include
VPATH_LOCATIONS		+= $(AMREX_HOME)/Src/Extern/SWFFT

LIBRARIES += -L$(FFTW_DIR) -lfftw3_mpi -lfftw3_omp -lfftw3
include $(AMREX_HOME)/Tools/GNUMake/Make.rules
