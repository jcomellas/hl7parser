#!/usr/bin/python

import os, stat, string, sys, time

from xml.sax import make_parser, handler


class AccessorDefHandler ( handler.ContentHandler ):

    indexCount      = { "field"         : 1, \
                        "repetition"    : 2, \
                        "component"     : 2, \
                        "subcomponent"  : 3 }

    # Constructor
    def __init__( self ):
        self.segmentId_         = ""
        self.headerFileName_    = ""
        self.headerFile_        = None
        self.sourceFileName_    = ""
        self.sourceFile_        = None
        self.comment_           = ""
        self.tabLength_         = 4


    def startDocument( self ):
        print "Creating accessors for segments:\n"

    # Handler for the "startElement" SAX event.
    def startElement( self, elementType, attrs ):
        elementType = string.lower( elementType )

        if elementType == "segment":

            self.segmentId_ = string.lower( attrs["id"] )
            self.comment_   = attrs["comment"]

            self.headerPath_ = "include/hl7parser/"
            self.headerFileName_ = "seg_" + self.segmentId_ + ".h"
            self.createHeader()
            self.sourcePath_ = "src/"
            self.sourceFileName_ = "seg_" + self.segmentId_ + ".c"
            self.createSource()

            print string.upper( self.segmentId_ ) + ": " + self.headerFileName_ + " / " + self.sourceFileName_

        elif elementType == "field" \
             or elementType == "repetition" \
             or elementType == "component" \
             or elementType == "subcomponent":

            name        = ""
            index       = ""
            dataType    = "string"
            length      = ""

            for attrName in attrs.keys():

                attrValue = attrs[attrName]

                if attrName == "name":
                    name = attrValue
                elif attrName == "index":
                    # 'index' is a sequence of numbers separated by dots ('.').
                    indexList = string.split( attrValue, "." )
                elif attrName == "data_type":
                    dataType = attrValue
                elif attrName == "length":
                    length = attrValue
                else:
                    print "WARNING: Unknown attribute " + attrName + " in " + elementType + " " + name + "."

            elementLength = int( length )
            self.writeAccessorDecl( elementType, name, indexList, dataType, elementLength )
            self.writeAccessorDef( elementType, name, indexList, dataType, elementLength )


    # Handler for the "endElement" SAX event.
    def endElement( self, elementType ):

        elementType = string.lower( elementType )

        if elementType == "segment":
            self.closeHeader( );
            self.closeSource();


    # Creates the header file for the accessors of the HL7 segment.
    def createHeader( self ):
        self.headerFile_ = os.open( self.headerPath_ + self.headerFileName_, os.O_CREAT | os.O_TRUNC | os.O_WRONLY, \
                                    stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IWGRP )

        self.writeHeaderGuardBegin()
        self.writeFileTitle( self.headerFile_, self.headerFileName_ )
        self.writeHeaderBegin()


    # Creates the header file for the accessors of the HL7 segment.
    def closeHeader( self ):
        self.writeHeaderEnd()
        self.writeHeaderGuardEnd()

        os.close( self.headerFile_ )
        self.headerFile_ = None


    # Creates the header file for the accessors of the HL7 segment.
    def createSource( self ):
        self.sourceFile_ = os.open( self.sourcePath_ + self.sourceFileName_, os.O_CREAT | os.O_TRUNC | os.O_WRONLY, \
                                    stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IWGRP )

        self.writeFileTitle( self.sourceFile_, self.sourceFileName_ )
        self.writeSourceBegin()


    # Closes the source file for the accessors of the HL7 segment.
    def closeSource( self ):
        self.writeSourceEnd()

        os.close( self.sourceFile_ )
        self.sourceFile_ = None


    def writeHeaderGuardBegin( self ):
        headerId = "HL7PARSER_SEG_" + string.upper( self.segmentId_ ) + "_H"

        os.write( self.headerFile_, \
                  "#ifndef " + headerId + "\n" \
                  "#define " + headerId + "\n\n" )


    def writeHeaderGuardEnd( self ):
        headerId = "HL7_SEG_" + string.upper( self.segmentId_ ) + "_H"

        os.write( self.headerFile_, \
                  "\n" \
                  "#endif /* " + headerId + " */\n" )


    def writeFileTitle( self, file, fileName ):
        today = time.localtime( time.time() )

        os.write( file, "/**\n" \
                        "* \\file " + fileName + "\n" \
                        "*\n" \
                        "* " + self.comment_ + " segment (" + string.upper( self.segmentId_ ) + ") accessors for the HL7 parser.\n" \
                        "*\n" \
                        "* \\internal\n" \
                        "* Copyright (c) " + str( today.tm_year ) + " \\b Erlar (http://erlar.com)\n" \
                        "*\n" \
                        "* \\warning DO NOT MODIFY THIS FILE.\n" \
                        "*\n"
                        "* Autogenerated by the " + sys.argv[0] + " script on " + time.ctime( time.time() ) + "\n" \
                        "*/\n\n" )

    def writeHeaderBegin( self ):
        os.write( self.headerFile_,
                  "/* ------------------------------------------------------------------------\n" \
                  "   Headers\n" \
                  "   ------------------------------------------------------------------------ */\n\n" \
                  "#include <hl7parser/config.h>\n" \
                  "#include <hl7parser/element.h>\n" \
                  "#include <hl7parser/export.h>\n" \
                  "#include <hl7parser/segment.h>\n\n" \
                  "BEGIN_C_DECL()\n\n" \
                  "/* ------------------------------------------------------------------------\n" \
                  "   Function prototypes\n" \
                  "   ------------------------------------------------------------------------ */\n\n" )

    def writeHeaderEnd( self ):
        os.write( self.headerFile_, \
                  "\n" \
                  "END_C_DECL()\n" )

    def writeSourceBegin( self):
        os.write( self.sourceFile_,
                  "/* ------------------------------------------------------------------------\n"
                  "   Headers\n"
                  "   ------------------------------------------------------------------------ */\n\n"
                  "#include <hl7parser/config.h>\n"
                  "#include <hl7parser/element.h>\n"
                  "#include <hl7parser/export.h>\n"
                  "#include <hl7parser/segment.h>\n"
                  "#include <hl7parser/" + self.headerFileName_ + ">\n\n"
                  "BEGIN_C_DECL()\n\n" )

    def writeSourceEnd( self ):
        os.write( self.sourceFile_, \
                  "END_C_DECL()\n" )

    # Writes the accessor declaration to the header file.
    def writeAccessorDecl( self, elementType, name, indexList, dataType, length ):

        if dataType == "integer":
            elementGetType      = "int "
            elementSetType      = "int "
            typedSetterSuffix   = "_int"
            typedSetterDesc     = "an integer"
            paramName           = "value"

        elif dataType       == "date":
            elementGetType      = "time_t "
            elementSetType      = "time_t "
            typedSetterSuffix   = "_time"
            typedSetterDesc     = "a time_t"
            paramName           = "value"

        else:
            elementGetType      = "HL7_Element *"
            elementSetType      = "char *"
            typedSetterSuffix   = "_str"
            typedSetterDesc     = "a string"
            paramName           = "element"

        elementCoord = " (" + string.upper( self.segmentId_ )
        for i in indexList:
            elementCoord += "."
            elementCoord += str( int( i ) + 1 )
        elementCoord += ") "

        accessorDecl    = "/**\n" \
                          "* Get the " + name + elementCoord + elementType + ".\n" \
                          "*/\n" \
                          "HL7_EXPORT " + elementGetType + "hl7_" + self.segmentId_ + "_" + name + "( HL7_Segment *segment );\n"

        accessorDecl   += "/**\n" \
                          "* Set the " + name + elementCoord + elementType + ".\n" \
                          "*/\n" + \
                          "HL7_EXPORT int hl7_" + self.segmentId_ + "_set_" + name + "( HL7_Segment *segment, HL7_Element *element );\n"

        accessorDecl   += "/**\n" \
                          "* Set the " + name + elementCoord + elementType + " as " + typedSetterDesc + ".\n" \
                          "*/\n" + \
                          "HL7_EXPORT int hl7_" + self.segmentId_ + "_set_" + name + typedSetterSuffix + "( HL7_Segment *segment, const " + elementSetType + "value );\n"

        os.write( self.headerFile_, accessorDecl )

    # Writes a standard accessor definition to the source file.
    def writeAccessorDef( self, elementType, name, indexList, dataType, length ):

        if dataType == "string":
            elementGetType          = "HL7_Element *"
            elementGetPrefix        = ""
            elementGetSuffix        = ""
            elementSetType          = "char *"
            elementSetPrefix        = "hl7_element_copy_str( "
            elementSetSuffix        = ", segment->allocator )"
            typedSetterSuffix       = "_str"

        elif dataType == "integer":
            elementGetType          = "int "
            elementGetPrefix        = "hl7_element_int( "
            elementGetSuffix        = " )"
            elementSetType          = "int "
            elementSetPrefix        = "hl7_element_set_int( "
            elementSetSuffix        = ", segment->allocator )"
            typedSetterSuffix       = "_int"

        elif dataType == "date":
            elementGetType          = "time_t "
            elementGetPrefix        = "hl7_element_date( "
            elementGetSuffix        = " )"
            elementSetType          = "time_t "
            elementSetPrefix        = "hl7_element_set_date( "
            # Include time?
            elementSetSuffix        = ", "
            if length >= 12:
                elementSetSuffix   += "true"
            else:
                elementSetSuffix   += "false"
            # Include seconds?
            elementSetSuffix       += ", "
            if length >= 14:
                elementSetSuffix   += "true"
            else:
                elementSetSuffix   += "false"
            elementSetSuffix       += ", segment->allocator )"
            typedSetterSuffix       = "_time"

        else:
            print "ERROR: Unknown data type \"" + dataType + "\" in segment " + string.upper( self.segmentId_ ) + ", " + elementType + " " + name + "."
            sys.exit( 1 )

        segmentAccessorSuffix = self.accessorSuffix( elementType, name, indexList, dataType, length )

        indexStr = ""
        for i in indexList:
            indexStr += ", " + i

        indent = self.tab( 1 )

        accessorDef = "/* ------------------------------------------------------------------------ */\n" \
                      "HL7_EXPORT " + elementGetType + "hl7_" + self.segmentId_ + "_" + name + "( HL7_Segment *segment )\n" \
                      + "{\n" \
                      + indent + "return " + elementGetPrefix + "hl7_segment_" + elementType + segmentAccessorSuffix + \
                      "( segment" + indexStr + " )" + elementGetSuffix + ";\n}\n\n"

        accessorDef += "/* ------------------------------------------------------------------------ */\n" \
                       "HL7_EXPORT int hl7_" + self.segmentId_ + "_set_" + name + "( HL7_Segment *segment, HL7_Element *element )\n" \
                       + "{\n" \
                       + indent + "return hl7_segment_set_" + elementType + segmentAccessorSuffix \
                       + "( segment" + indexStr + ", element );\n}\n\n"

        accessorDef += "/* ------------------------------------------------------------------------ */\n" \
                       "HL7_EXPORT int hl7_" + self.segmentId_ + "_set_" + name + typedSetterSuffix + "( HL7_Segment *segment, const " + elementSetType + "value )\n" \
                       + "{\n" \
                       + indent + "int         rc;\n" \
                       + indent + "HL7_Element element;\n\n" \
                       + indent + "rc = " + elementSetPrefix + "&element, value" + elementSetSuffix  + ";\n\n" \
                       + indent + "return ( rc == 0 ? hl7_segment_set_" + elementType + segmentAccessorSuffix \
                       + "( segment" + indexStr + ", &element ) : rc );\n}\n\n"

        os.write( self.sourceFile_, accessorDef )


    def accessorSuffix( self, elementType, name, indexList, dataType, length ):

        suffix = ""
        if self.indexCount.has_key( elementType ):
            correctIndexCount = self.indexCount[elementType]

            if correctIndexCount != len( indexList ):
                if correctIndexCount + 1 == len( indexList ):
                    suffix = "_rep"
                else:
                    print "WARNING: segment " + string.upper( self.segmentId_ ) + ", " + elementType + " " + name + " has " \
                          + str( len( indexList ) ) + " elements and should have " + str( correctIndexCount )

        return suffix


    def tab( self, level ):
        return ' ' * ( self.tabLength_ * level )


def usage():
    print "\nUsage: python " + sys.argv[0] + " <file name>\n" \
          "\n" \
          "Generates the source files for the HL7 segment accessor functions\n" \
          "described in the XML file passed as argument.\n\n"
    sys.exit( 1 )

try:
    xmlFile = sys.argv[1]
except:
    usage()

parser = make_parser()
parser.setContentHandler( AccessorDefHandler() )

try:
    parser.parse( xmlFile )
except IOError, e:
    print "\nERROR: " + xmlFile + ": " + str( e )
except saxlib.SAXException, e:
    print "\nERROR: " + str( e )

