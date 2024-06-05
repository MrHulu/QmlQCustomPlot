cmake_minimum_required(VERSION 3.14)

project(QmlQCusomPlotDemo LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Quick REQUIRED)


add_executable(QmlQCusomPlotDemo)
target_sources(QmlQCusomPlotDemo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qml.qrc
)
set_target_properties(QmlQCusomPlotDemo PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON
    OUTPUT_NAME ${PROJECT_NAME})
target_include_directories(QmlQCusomPlotDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(QmlQCusomPlotDemo PRIVATE Qt5::Core Qt5::Quick 
    QmlQCustomPlot # add QmlQCustomPlot 
)


if(QT_VERSION_MAJOR EQUAL 6)
qt_import_qml_plugins(QmlQCusomPlotDemo)
qt_finalize_executable(QmlQCusomPlotDemo)
endif()


add_subdirectory(src)