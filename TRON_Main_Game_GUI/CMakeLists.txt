cmake_minimum_required(VERSION 3.5)

project(Tron VERSION 0.1 LANGUAGES CXX)

include_directories(include/)
include_directories(resources/)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network OpenGLWidgets)
find_package(OpenGL REQUIRED)

qt_add_executable(Tron
    MANUAL_FINALIZATION
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h # for moc
    src/mainwindow.ui
    src/config_handler.cpp
    include/config_handler.h # for moc
    src/game.cpp
    include/game.h # for moc
    src/game_graphic.cpp
    include/game_graphic.h # for moc
    src/network.cpp
    include/network.h # for moc
)

target_link_libraries(Tron PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::OpenGLWidgets)

set_target_properties(Tron PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Tron
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(Tron)
