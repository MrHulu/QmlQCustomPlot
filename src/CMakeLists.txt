cmake_minimum_required(VERSION 3.18)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Quick Widgets PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Quick Widgets PrintSupport REQUIRED)

add_library(QmlQCustomPlot STATIC)
file(GLOB_RECURSE source_file "*.cc" "*.cpp" "*.h" )
target_sources(QmlQCustomPlot PRIVATE ${source_file})
set_target_properties(QmlQCustomPlot PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(QmlQCustomPlot PUBLIC)
target_link_libraries(QmlQCustomPlot PUBLIC 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Quick 
    Qt5::Widgets
    Qt5::PrintSupport)