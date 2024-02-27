include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)


if (CODE_COVERAGE)
    evc_include(CodeCoverage)
endif()

set(TEST_TARGET_NAME ${PROJECT_NAME}_tests)
add_executable(${TEST_TARGET_NAME} state_allocator.cpp)
target_link_libraries(${TEST_TARGET_NAME}
    PRIVATE
        fsm::fsm
        Catch2::Catch2WithMain
)

if (CODE_COVERAGE)
    append_coverage_compiler_flags_to_target(${TEST_TARGET_NAME})
    setup_target_for_coverage_gcovr_html(
        NAME coverage
        EXECUTABLE ${TEST_TARGET_NAME}
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
)
endif()

catch_discover_tests(${TEST_TARGET_NAME})
