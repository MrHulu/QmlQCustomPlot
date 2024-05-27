cmake_minimum_required(VERSION 3.18)

add_library(QmlQCusomPlot STATIC)
file(GLOB_RECURSE source_file "*.cc" "*.cpp" "*.h" )
target_sources(QmlQCusomPlot PRIVATE ${source_file})
set_target_properties(QmlQCusomPlot PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_link_libraries(QmlQCusomPlot PUBLIC Qt5::Core)