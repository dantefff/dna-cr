#################################################
# QMake project for academias:                  #
# Logistic control system using RFID technology #
#                                               #
#################################################

# default values
include(defaults.pri)

# executable name
TARGET = dna_complementary_reverse

# version
VERSION = TRUNK

#############################################################################################
# begin of external libs to link
# if we would need the ltkcpp library, and the xml2 as it depends on it we would write
# LIBS=-Lltkcpp/lib -lltkcpp -lxml2

# non standard include paths
# INCLUDEPATH += ltkcpp/include
# end of external libs to link
#############################################################################################

# qt modules used
#QT += sql

# to access qt help module
#CONFIG += help

# list of source files (no class source files)
MYSOURCES = main.cpp 
#            utils/MessageHandler.cpp

#external libs
#unix:LIBS += -Llib/unix -lxls
#win32:LIBS += -Llib/win -lxls -liconv

INCLUDEPATH += include

# list of classes (the 'extended' script will search for their files)
CLASSES = MainWindow \
	  MessageHandler
# forms, in src/view
MYFORMS = MainWindow 
#          AlumnosWidget \

# resources
######### In case we need enbedded resources
RESOURCES = src/dna_complementary_reverse.qrc

######### Variables to make the instalation
target.path = /usr/local/bin

#splash.files = splash/*
#splash.path = /usr/share/plymouth/themes/acore
#INSTALLS += target splash
INSTALLS += target

# extended rules for extra actions
######### There is the black magic to complete .h .cpp and .iu
######### in FORMS SOURCES and HEADERS
include(extended.pri)
