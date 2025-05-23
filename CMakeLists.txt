cmake_minimum_required(VERSION 3.10)
project(RafLaz VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

add_library(RafLazLib SHARED
        src/RafLaz.cpp
)
target_include_directories(RafLazLib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_compile_definitions(RafLazLib PRIVATE LIBRARY_EXPORTS)
# Set properties for Windows DLL
set_target_properties(RafLazLib PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        PUBLIC_HEADER include/RafLaz.h
)

Python3_add_library(pyRafLaz MODULE
        src/python_wrapper.cpp
)
target_link_libraries(pyRafLaz PRIVATE RafLazLib)
target_include_directories(pyRafLaz PRIVATE
        ${Python3_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_target_properties(pyRafLaz PROPERTIES
        PREFIX ""
        OUTPUT_NAME "raflaz"
)

include(GNUInstallDirs)
install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/RafLaz.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS RafLazLib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  # For Windows DLL
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(DEFINED ENV{CONDA_BUILD})
    # Install the Python module to the correct location for Conda
    install(TARGETS pyRafLaz
            LIBRARY DESTINATION ${Python3_SITEARCH}
    )
else()
    # Normal installation
    install(TARGETS pyRafLaz
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()
