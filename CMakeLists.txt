cmake_minimum_required(VERSION 3.10)
project(RafLaz VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set position independent code
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Create shared library
add_library(RafLazLib SHARED
        src/RafLaz.cpp
)

# Add include directories for mylibrary
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

# Install rules
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
