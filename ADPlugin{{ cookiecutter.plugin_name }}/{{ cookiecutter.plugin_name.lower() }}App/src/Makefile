TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

# The following gets rid of the -fno-implicit-templates flag on vxWorks, 
# so we get automatic template instantiation.
# This is what we want for the source files that define template functions.
ifeq (vxWorks,$(findstring vxWorks, $(T_A)))
    CODE_CXXFLAGS=
endif

DBD += NDPlugin{{ cookiecutter.plugin_name }}.dbd

INC += NDPlugin{{ cookiecutter.plugin_name }}.h

LIBRARY_IOC += NDPlugin{{ cookiecutter.plugin_name }}

NDPlugin{{ cookiecutter.plugin_name }}_SRCS += NDPlugin{{ cookiecutter.plugin_name }}.cpp

include $(AREA_DETECTOR)/ADCore/ADApp/commonLibraryMakefile

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
