cmake_minimum_required(VERSION 3.0.0)

project(qt-cmake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

SET(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/fractalgraphicsview.cpp
)

SET(UIS
    src/mainwindow.ui
    )

SET(INCLUDES
    include/mainwindow.h
    include/julia_set_generator.h
    include/fractalgraphicsview.h
    )

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${INCLUDES}
    ${UIS}
    )


target_include_directories(${PROJECT_NAME} PRIVATE
    include
    include/common

    )

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    )


add_executable(julia_test
    src/julia_test.cpp
    )

target_include_directories(julia_test PRIVATE
    include
    include/common
    )
