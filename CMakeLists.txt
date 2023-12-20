cmake_minimum_required(VERSION 3.5)

project(Task_Qt_Trein)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        UdpServer.h
        UdpServer.cpp

        UdpClient.h
        UdpClient.cpp

        HeightIndicatorWidget.h
        HeightIndicatorWidget.cpp

        MainWindow.hpp
        MainWindow.cpp

        main.cpp
)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

add_executable(Task_Qt_Trein ${PROJECT_SOURCES})

target_link_libraries(Task_Qt_Trein Qt${QT_VERSION_MAJOR}::Widgets Qt5::Network)

#set_target_properties(Task_Qt_Trein PROPERTIES
#        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#        MACOSX_BUNDLE TRUE
#        WIN32_EXECUTABLE TRUE
#)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Drone)
endif()
