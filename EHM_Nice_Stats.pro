QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++latest

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Enable as many compiler warnings as possible
CONFIG += warn_on

# Enable parallel building
*msvc* { # visual studio spec filter
     QMAKE_CXXFLAGS += -MP
}

# Application version
VERSION = 1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Resources
RC_FILE = EHM_Nice_Stats.rc

#QXlsx library
Debug:LIBS += -L"$$_PRO_FILE_PWD_/stats/qxlsx/lib" -lQXlsx_debug
Release:LIBS += -L"$$_PRO_FILE_PWD_/stats/qxlsx/lib" -lQXlsx
INCLUDEPATH += $$_PRO_FILE_PWD_/stats/qxlsx/include

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    stats/base_class/player.cpp \
    stats/base_class/schema_base_class.cpp \
    stats/club.cpp \
    stats/container/club_container.cpp \
    stats/container/column_data.cpp \
    stats/container/container_base_class.cpp \
    stats/container/skater_container.cpp \
    stats/ice_time.cpp \
    stats/skater.cpp \
    stats/stats_manager.cpp \
    stats/totals/skater_totals.cpp

HEADERS += \
    mainwindow.h \
    settings.h \
    stats/base_class/player.h \
    stats/base_class/schema_base_class.h \
    stats/club.h \
    stats/container/club_container.h \
    stats/container/column_data.h \
    stats/container/container_base_class.h \
    stats/container/skater_container.h \
    stats/ice_time.h \
    stats/qxlsx/include/xlsxabstractooxmlfile.h \
    stats/qxlsx/include/xlsxabstractooxmlfile_p.h \
    stats/qxlsx/include/xlsxabstractsheet.h \
    stats/qxlsx/include/xlsxabstractsheet_p.h \
    stats/qxlsx/include/xlsxcell.h \
    stats/qxlsx/include/xlsxcell_p.h \
    stats/qxlsx/include/xlsxcellformula.h \
    stats/qxlsx/include/xlsxcellformula_p.h \
    stats/qxlsx/include/xlsxcelllocation.h \
    stats/qxlsx/include/xlsxcellrange.h \
    stats/qxlsx/include/xlsxcellreference.h \
    stats/qxlsx/include/xlsxchart.h \
    stats/qxlsx/include/xlsxchart_p.h \
    stats/qxlsx/include/xlsxchartsheet.h \
    stats/qxlsx/include/xlsxchartsheet_p.h \
    stats/qxlsx/include/xlsxcolor_p.h \
    stats/qxlsx/include/xlsxconditionalformatting.h \
    stats/qxlsx/include/xlsxconditionalformatting_p.h \
    stats/qxlsx/include/xlsxcontenttypes_p.h \
    stats/qxlsx/include/xlsxdatavalidation.h \
    stats/qxlsx/include/xlsxdatavalidation_p.h \
    stats/qxlsx/include/xlsxdatetype.h \
    stats/qxlsx/include/xlsxdocpropsapp_p.h \
    stats/qxlsx/include/xlsxdocpropscore_p.h \
    stats/qxlsx/include/xlsxdocument.h \
    stats/qxlsx/include/xlsxdocument_p.h \
    stats/qxlsx/include/xlsxdrawing_p.h \
    stats/qxlsx/include/xlsxdrawinganchor_p.h \
    stats/qxlsx/include/xlsxformat.h \
    stats/qxlsx/include/xlsxformat_p.h \
    stats/qxlsx/include/xlsxglobal.h \
    stats/qxlsx/include/xlsxmediafile_p.h \
    stats/qxlsx/include/xlsxnumformatparser_p.h \
    stats/qxlsx/include/xlsxrelationships_p.h \
    stats/qxlsx/include/xlsxrichstring.h \
    stats/qxlsx/include/xlsxrichstring_p.h \
    stats/qxlsx/include/xlsxsharedstrings_p.h \
    stats/qxlsx/include/xlsxsimpleooxmlfile_p.h \
    stats/qxlsx/include/xlsxstyles_p.h \
    stats/qxlsx/include/xlsxtheme_p.h \
    stats/qxlsx/include/xlsxutility_p.h \
    stats/qxlsx/include/xlsxworkbook.h \
    stats/qxlsx/include/xlsxworkbook_p.h \
    stats/qxlsx/include/xlsxworksheet.h \
    stats/qxlsx/include/xlsxworksheet_p.h \
    stats/qxlsx/include/xlsxzipreader_p.h \
    stats/qxlsx/include/xlsxzipwriter_p.h \
    stats/skater.h \
    stats/stats_manager.h \
    stats/totals/skater_totals.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    res/ehm_nice_stats_example.png \
    stats/qxlsx/lib/QXlsx.lib \
    stats/qxlsx/lib/QXlsx_debug.lib
