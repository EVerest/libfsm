cmake_minimum_required(VERSION 3.11)

project(fsm
    VERSION 0.2.0
    DESCRIPTION "Finite State Machine library"
    HOMEPAGE_URL "https://github.com/EVerest/libfsm"
	LANGUAGES CXX
)

find_package(everest-cmake 0.1 REQUIRED
    PATHS ../everest-cmake
)

#
# options
#
option(BUILD_EXAMPLES "enable building of examples" OFF)
option(FSM_INSTALL "Install the library (shared data might be installed anyway)" ${EVC_MAIN_PROJECT})
option(${PROJECT_NAME}_BUILD_TESTING "Build unit tests, used if included as dependency" ON)
option(BUILD_TESTING "Build unit tests, used if standalone project" ON)

#
# library declaration
#
add_library(fsm INTERFACE)
add_library(fsm::fsm ALIAS fsm)

target_include_directories(fsm INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

#
# examples
#
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

#
# tests
#
if((${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME} OR ${PROJECT_NAME}_BUILD_TESTING) AND BUILD_TESTING)
    include(CTest)
    add_subdirectory(tests)
endif()


#
# installation definition
#
if (FSM_INSTALL)
    install(
        TARGETS fsm
        EXPORT fsm-targets
    )

    install(
        DIRECTORY include/
        TYPE INCLUDE
    )

    evc_setup_package(
        NAME fsm
        EXPORT fsm-targets
        NAMESPACE fsm
    )
endif()
