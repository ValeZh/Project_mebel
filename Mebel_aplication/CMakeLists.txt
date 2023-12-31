cmake_minimum_required(VERSION 3.5)

project(Mebel_aplication VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS core quick sql)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Mebel_aplication
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        vitalikSign_up/signupwindow.h
        vitalikSign_up/signupwindow.cpp
        vitalikSign_up/signupwindow.ui
        maratCart/cart.h
        maratCart/cart.cpp
        addprod.h addprod.cpp addprod.ui
        addshop.h addshop.cpp addshop.ui
        vitalikLog_in/loginwindow.cpp vitalikLog_in/loginwindow.h vitalikLog_in/loginwindow.ui
        mycash.h
        mycash.cpp
        resources.qrc
        vitalicAcount/acountwindow.cpp vitalicAcount/acountwindow.h vitalicAcount/acountwindow.ui

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Mebel_aplication APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Mebel_aplication SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Mebel_aplication
            ${PROJECT_SOURCES}
        )
    endif()
endif()

find_package(Qt6 REQUIRED COMPONENTS Sql)
target_link_libraries(Mebel_aplication PRIVATE Qt${QT_VERSION_MAJOR}::Widgets )
target_link_libraries(Mebel_aplication PRIVATE Qt6::Sql)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Mebel_aplication)
endif()
set_target_properties(Mebel_aplication PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Mebel_aplication
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Mebel_aplication)
endif()
