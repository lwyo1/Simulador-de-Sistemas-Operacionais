cmake_minimum_required(VERSION 3.16)

project(Projeto_SO VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appProjeto_SO
    main.cpp
)

qt_add_qml_module(appProjeto_SO
    URI Projeto_SO
    QML_FILES
        Main.qml
        SOURCES
SOURCES mainwindow.h mainwindow.cpp
RESOURCES mainwindow.ui
SOURCES csvreader.cpp
SOURCES csvreader.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appProjeto_SO PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appProjeto_SO
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appProjeto_SO
    PRIVATE Qt6::Quick
)
target_link_libraries(appProjeto_SO PRIVATE Qt6::Widgets)

install(TARGETS appProjeto_SO
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
