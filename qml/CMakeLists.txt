cmake_minimum_required(VERSION 3.5)

project(snake-game-qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Test Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Test Multimedia)

file(GLOB_RECURSE files ../src/*.cpp ../include/*.h ../*.qrc ../*.rc)

# TODO: DELETE
list(FILTER files EXCLUDE REGEX "\/*[a-z]*_[a-z]*.cpp")
list(FILTER files EXCLUDE REGEX "\/*[a-z]*_[a-z]*.h")
message(${files})

set(PROJECT_SOURCES
        main.cpp
        ${files}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(snake-game-qml
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(snake-game-qml SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(snake-game-qml
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(snake-game-qml PRIVATE Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Multimedia)
target_include_directories(snake-game-qml PRIVATE ../include)

set_target_properties(snake-game-qml PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS snake-game-qml
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(snake-game-qml)
endif()
