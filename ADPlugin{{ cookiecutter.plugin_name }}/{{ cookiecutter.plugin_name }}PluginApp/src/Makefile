TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

DBD += NDPlugin{{ cookiecutter.plugin_name }}.dbd

INC += NDPlugin{{ cookiecutter.plugin_name }}.h
INC += NDPlugin{{ cookiecutter.plugin_name }}ParamDefs.h

LIBRARY_IOC += NDPlugin{{ cookiecutter.plugin_name }}

NDPlugin{{ cookiecutter.plugin_name }}_SRCS += NDPlugin{{ cookiecutter.plugin_name }}.cpp
NDPlugin{{ cookiecutter.plugin_name }}_SRCS += NDPlugin{{ cookiecutter.plugin_name }}ParamDefs.cpp

include $(AREA_DETECTOR)/ADCore/ADApp/commonLibraryMakefile

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
