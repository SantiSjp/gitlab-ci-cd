cmake_minimum_required(VERSION 3.8)
project(gitlabci VERSION 0.0.1 LANGUAGES CXX)

set(PROJECT_NAME gitlabci)
set(VERSION 0.0.1)

option(BUILD_TESTS "Build unit tests" ON)
option(GEN_PACKAGE "Generate Package" OFF)

set(SOURCE_FILES
    src/calc.cpp
)

set(HEADER_FILES
    include/calc/calc.h
)

add_library(cicd_demo_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_compile_features(cicd_demo_lib PUBLIC cxx_std_17)
target_include_directories(cicd_demo_lib
    PUBLIC
           $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(programa)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

if(GEN_PACKAGE)
    install(TARGETS example_program
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)

    set(CPACK_PACKAGE_NAME "gitlabci")
    set(CPACK_PACKAGE_VENDOR "santi")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple CI/CD example project.")
    set(CPACK_PACKAGE_VERSION ${VERSION})
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_PROCESSOR}")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

    set(CPACK_GENERATOR "RPM")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Santi")
    set(CPACK_SOURCE_IGNORE_FILES
        .git*
    )
    include(CPack)
endif()
