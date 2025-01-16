add_executable(v2_tests)
target_sources(v2_tests
    PRIVATE
        tests.cpp
        s_context.cpp
        s_states.cpp
)

target_link_libraries(v2_tests
    PRIVATE
        fsm::fsm
)