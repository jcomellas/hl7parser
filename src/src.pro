#
# Project file for the HL7 Parser library.
#

TEMPLATE                        = lib
CONFIG                         -= qt
CONFIG                         += dll thread console warn_on release

# Options common to all platforms/compilers.
DEFINES                        += INSIDE_HL7PARSER
INCLUDEPATH                    += ../include
DEPENDPATH                     += ../src ../include
DESTDIR                         = ../lib
VERSION                         = 2.2.0

# Options for the dynamic library (DLL).
dll:DEFINES                    += HL7PARSER_DLL
# Options for the static library (DLL).
static:DEFINES                 += HL7PARSER_STATIC
# Options for Win32.
win32:DEFINES                  += -D_DLL

# Options for Unix
unix {
    target.path                += /usr/local/lib
    INSTALLS                   += target
    headers.path                = /usr/local/include/hl7parser
    headers.files               = ../include/hl7parser/*.h
    INSTALLS                   += headers
    # Avoid stripping debug symbols from release builds
    QMAKE_STRIP                 = echo
}

# Options for the debug version.
debug {
    TARGET                      = hl7parserd
    OBJECTS_DIR                 = .obj/debug
}
release {
    # Options for the release version.
    DEFINES                    += NDEBUG
    TARGET                      = hl7parser
    OBJECTS_DIR                 = .obj/release
    # Don't remove debug symbols in release mode
    QMAKE_CXXFLAGS_RELEASE     += -g
    QMAKE_CFLAGS_RELEASE       += -g
    QMAKE_LFLAGS_RELEASE        =
    QMAKE_STRIP                 =
}

SOURCES                         = $$files(*.c)
HEADERS                         = $$files(../include/hl7parser/*.h)

