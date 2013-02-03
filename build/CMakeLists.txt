#############################################################################
# Menaan by Interima.x2 team
# Copyright (C) 2012 Tadej Novak <tadej@tano.si>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>./
#############################################################################

CMake_Minimum_Required(VERSION 2.8.9)

Set(PROJECT Menaan)

Project(${PROJECT})

Set(INFO_PATH "${CMAKE_BINARY_DIR}/../info")

Message("\nStarting...\n")

################################################
    # Read version, about, authors

    File(READ "${INFO_PATH}/Version.txt" APP_VERSION)
    File(READ "${INFO_PATH}/About.txt"   APP_ABOUT)
    File(READ "${INFO_PATH}/Authors.txt" APP_AUTHORS)

    Message("Version section\n" "${APP_VERSION}\n")
    Message("About section\n"   "${APP_ABOUT}\n")
    Message("Authors section\n" "${APP_AUTHORS}\n")
################################################

################################################
    # Compiler options

    # Verbose makefile
    Set(CMAKE_VERBOSE_MAKEFILE ON)

    # Make final release build smaller
    IF(CMAKE_COMPILER_IS_GNUCXX)
        Set(CMAKE_CXX_FLAGS "-Wall -fPIC")
        SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}
            -s")
    EndIf(CMAKE_COMPILER_IS_GNUCXX)

    If(MINGW)
        Set(CMAKE_CXX_FLAGS "-fPIC")
         #Windows compatibility
        Set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}
            -Wl,-subsystem,windows")
         #Statically link with libgcc
        Set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}
            -static-libgcc -static-libstdc++")
    EndIf(MINGW)

    If(MSVC)
        Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -nologo -Zc:wchar_t
            -w34100 -w34189")
        Set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NOLOGO
            /DYNAMICBASE /NXCOMPAT /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    EndIf(MSVC)
################################################

################################################
    # Qt options
    Set(QT_MIN_VERSION "5.0")

    Set(CMAKE_AUTOMOC ON)

    # uncomment if debug no need
    Add_Definitions(-DQT_NO_DEBUG_OUTPUT)

    Find_Package(Qt5Xml REQUIRED)
    Find_Package(Qt5LinguistTools REQUIRED)
    Find_Package(Qt5Widgets REQUIRED)
    Find_Package(Qt5Quick REQUIRED)
    Find_Package(Qt5Qml REQUIRED)

################################################

################################################
    # set directories

    Set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/..")

    Set(CMAKE_INCLUDE_CURRENT_DIR ON)
    Include_Directories( "../headers"  "../sources")

################################################

################################################
    # set project's path, files

    File(GLOB HEADERS "../headers/*.h")

    File(GLOB SOURCES "../sources/*.cpp")

    Set(QMLS "../resources/qml/AboutTab.qml")

    Set(LANGUAGES en de ru fr)
	
    Set(RESOURCE_PATH "../resources")

    Set(RESOURCES "${RESOURCE_PATH}/resources.qrc")

    Set(TRANSLATIONS_PATH "../resources/translations")

    Set(SPECIAL_PATH "../spec")

    Set(SL "${SPECIAL_PATH}/plugins")
    File(GLOB TS "${TRANSLATIONS_PATH}/*.ts")
    File(GLOB SP "${SPECIAL_PATH}/*.xml")
    File(GLOB IN "${INFO_PATH}/*.txt")
    File(GLOB QM "${CMAKE_BINARY_DIR}/*.qm")
################################################

################################################
    # Tranalstions' options

    SET(TRANSLATION_SRCS ${HEADERS} ${SOURCES})

    #QT5_CREATE_TRANSLATION(TRANSLATIONS ${TRANSLATION_SRCS} ${TS})
    QT5_ADD_TRANSLATION(TRANSLATIONS ${TS})
    ADD_CUSTOM_TARGET(translations ALL DEPENDS ${TRANSLATIONS})

    #FILE(COPY ${TRANSLATIONS} DESTINATION ${TRANSLATIONS_PATH})

################################################
    # Compile

    Qt5_Add_Resources(QRC_SOURCES ${RESOURCES})

    Add_Executable(${PROJECT} ${HEADERS} ${SOURCES}
                   ${QRC_SOURCES} ${TRANSLATIONS})

    Qt5_Use_Modules(${PROJECT} Widgets Quick Qml Xml)
################################################

################################################
    # Install

    Install(FILES ${PROJECT} DESTINATION "${CMAKE_INSTALL_PREFIX}/app")
    Install(FILES ${SP} DESTINATION "${CMAKE_INSTALL_PREFIX}/app")
    Install(FILES ${IN} DESTINATION "${CMAKE_INSTALL_PREFIX}/app/info")
    Install(FILES ${QM} DESTINATION "${CMAKE_INSTALL_PREFIX}/app/translations")
    Install(DIRECTORY ${SL} DESTINATION "${CMAKE_INSTALL_PREFIX}/app")
