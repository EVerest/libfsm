#include "states.hpp"

#include <cstdio>

Result ManualMode::feed(Event ev) {
    if (ev == Event::PressedOn) {
        current_brightness = (current_brightness % 3) + 1;
        m_ctx.set_brightness(current_brightness);
        return {nullptr};
    } else if (ev == Event::PressedOff) {
        return {m_ctx.create_state<LightOff>()};
    }

    return {};
}

void ManualMode::leave() {
    printf("Left the manual mode\n");
}

MotionMode::ContainerType MotionMode::get_initial() {
    return m_ctx.create_state<MotionIdle>();
}

Result MotionMode::feed(Event ev) {
    if (ev == Event::PressedOff) {
        return {m_ctx.create_state<LightOff>()};
    } else if (ev == Event::PressedOn) {
        return {m_ctx.create_state<ManualMode>()};
    }

    return {};
}

Result MotionDetected::feed(Event ev) {
    if (ev == Event::Timeout) {
        return {m_ctx.create_state<MotionIdle>()};
    } else if (ev == Event::MotionDetect) {
        // rearm timer
    }

    return {};
}

Result LightOff::feed(Event ev) {
    if (ev == Event::PressedOn) {
        return {m_ctx.create_state<ManualMode>()};
    } else if (ev == Event::EnterMotionMode) {
        return {m_ctx.create_state<MotionMode>()};
    }

    return {};
}

Result MotionIdle::feed(Event ev) {
    if (ev == Event::MotionDetect) {
        return {m_ctx.create_state<MotionDetected>()};
    }

    return {};
}
