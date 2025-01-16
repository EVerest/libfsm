add_executable(light_switch_v2)

target_sources(light_switch_v2
    PRIVATE
        light_switch.cpp
        context.cpp
        states.cpp
)

target_link_libraries(light_switch_v2
    PRIVATE
        fsm::fsm
)
