cmake_minimum_required(VERSION 3.5)

project(ToooDo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QXORM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../QxOrm)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Svg)
find_package(KF6WidgetsAddons REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow/mainwindow.cpp src/mainwindow/mainwindow.h src/mainwindow/mainwindow.ui
    src/quickadd/quickadd.cpp src/quickadd/quickadd.h src/quickadd/quickadd.ui
    src/taskitem/taskitem.cpp src/taskitem/taskitem.h src/taskitem/taskitem.ui
    src/taskmanager/taskmanager.cpp src/taskmanager/taskmanager.h
    src/libs/relativedates.cpp src/libs/relativedates.h
    # src/svgmanager/svgmanager.cpp src/svgmanager/svgmanager.h
)

qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Add the include directory
add_library(QxOrm STATIC IMPORTED)
set_target_properties(QxOrm PROPERTIES
    IMPORTED_LOCATION ${QXORM_DIR}/lib/libQxOrm.so
)

target_include_directories(${PROJECT_NAME} PRIVATE src ${QXORM_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Svg
    KF6::WidgetsAddons
    QxOrm
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
