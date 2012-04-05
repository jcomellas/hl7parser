#
# Project file for the test program.
#

TEMPLATE                        = app
CONFIG                         -= qt
CONFIG                         += thread console warn_on release

# --- Options common to all platforms/compilers.
DEFINES                         = HL7PARSER_DLL
INCLUDEPATH                    += ../../include
DEPENDPATH                     += ../../include
QMAKE_LIBDIR                   += ../../lib
DESTDIR                         = ../../bin
VERSION                         = 1.0

QMAKE_LIBS                      = -lhl7parser

# --- Options for the dynamic library (DLL).
dll:DEFINES                    += HL7PARSER_DLL

# --- Options for the release version.
release:DEFINES                += NDEBUG

# Options for the debug version.
debug {
    OBJECTS_DIR                 = .obj/debug
}
release {
    # Options for the release version.
    DEFINES                    += NDEBUG
    OBJECTS_DIR                 = .obj/release
    # Don't remove debug symbols in release mode
    QMAKE_CXXFLAGS_RELEASE     += -g
    QMAKE_CFLAGS_RELEASE       += -g
    QMAKE_LFLAGS_RELEASE        =
    QMAKE_STRIP                 =
}

SOURCES                         = $$files(*.c)
# HEADERS                         = $$files(*.h)

# Avoid stripping debug symbols from release builds
QMAKE_STRIP                     = echo
