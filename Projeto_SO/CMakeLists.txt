cmake_minimum_required(VERSION 3.16)
project(Projeto_SO VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appProjeto_SO
    main.cpp
    mainwindow.h mainwindow.cpp mainwindow.ui

    csvreader.h csvreader.cpp
    process.h
    memory.h memory.cpp
    scheduler.h scheduler.cpp
    report.h report.cpp
    ganttwidget.h ganttwidget.cpp
)

set_target_properties(appProjeto_SO PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appProjeto_SO PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(appProjeto_SO PRIVATE Qt6::Widgets)

install(TARGETS appProjeto_SO
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)