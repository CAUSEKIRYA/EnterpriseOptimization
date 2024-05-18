cmake_minimum_required(VERSION 3.5)

project(EnterpriseOptimization VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql)

file(GLOB_RECURSE TS_FILES "${PROJECT_SOURCE_DIR}/locales/${CMAKE_PROJECT_NAME}_*.ts")

set(PROJECT_SOURCES
        main.cpp
        program_defs.h

        matrix.h matrix.cpp
        matrixview.h matrixview.cpp
        appsettings.h appsettings.cpp

        optmethods/optimizationthread.h optmethods/optimizationthread.cpp
        optmethods/optimizationobjectstorage.h optmethods/optimizationobjectstorage.cpp

        optmethods/lsm.h optmethods/lsm.cpp
        optmethods/simplex.h optmethods/simplex.cpp
        optmethods/truncate.h optmethods/truncate.cpp
        optmethods/branchandbound.h optmethods/branchandbound.cpp

        mainwindow.h mainwindow.cpp mainwindow.ui
        dbviewwidget.h dbviewwidget.cpp dbviewwidget.ui
        settingsdialog.h settingsdialog.cpp settingsdialog.ui
        dbconnectiondialog.h dbconnectiondialog.cpp dbconnectiondialog.ui
        optimizationresultsdialog.h optimizationresultsdialog.cpp optimizationresultsdialog.ui
        aboutprogramdialog.h aboutprogramdialog.cpp aboutprogramdialog.ui
        helpwindow.h helpwindow.cpp helpwindow.ui

        ${TS_FILES}
)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/locales")
    add_custom_target(COMPILED_LOCALES_DIR ALL COMMAND ${CMAKE_COMMAND} -E make_directory "locales")
endif()

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
get_filename_component(QM_NAMES ${QM_FILES} NAME)

if(ANDROID)
    add_library(EnterpriseOptimization SHARED
        ${PROJECT_SOURCES}
        ${QM_FILES}
    )
else()
    add_executable(EnterpriseOptimization
        ${PROJECT_SOURCES}
        ${QM_FILES}
    )
endif()

target_link_libraries(EnterpriseOptimization PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(EnterpriseOptimization PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if (EXISTS "${CMAKE_BINARY_DIR}/locales/${QM_NAMES}")
    file(REMOVE "${CMAKE_BINARY_DIR}/locales/${QM_NAMES}")
endif()
add_custom_target(MOVE_QM_FILES ALL COMMAND ${CMAKE_COMMAND} -E rename ${QM_FILES} "${CMAKE_BINARY_DIR}/locales/${QM_NAMES}")
add_dependencies(MOVE_QM_FILES EnterpriseOptimization)
