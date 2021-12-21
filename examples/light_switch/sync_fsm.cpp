// SPDX-License-Identifier: Apache-2.0
// Copyright 2020 - 2021 Pionix GmbH and Contributors to EVerest
#include "sync_fsm.hpp"

extern void set_brightness(int value);

FSM::FSM() {
    // define transitions
    sd_light_off.transitions = [this](const EventBaseType& ev, TransitionType& trans) {
        switch (ev.id) {
        case EventID::PressedMot:
            return trans.set(sdh_motion_mode.sd_mm_init);
        case EventID::PressedOn:
            return trans.set<FSM, &FSM::t_manual_mode_init>(this);
        default:
            return;
        }
    };

    sd_manual_mode.transitions = [this](const EventBaseType& ev, TransitionType& trans) {
        switch (ev.id) {
        case EventID::PressedOff:
            return trans.set(sd_light_off);
        case EventID::PressedMot:
            return trans.set(sdh_motion_mode.sd_mm_init);
        case EventID::PressedOn:
            return trans.set<FSM, &FSM::t_manual_mode_on_press>(this);
        default:
            return;
        }
    };

    sdh_motion_mode.super = [this](const EventBaseType& ev, TransitionType& trans) {
        switch (ev.id) {
        case EventID::PressedOff:
            return trans.set(sd_light_off);
        case EventID::PressedOn:
            return trans.set<FSM, &FSM::t_manual_mode_on_press>(this);
        default:
            return;
        }
    };

    // define entry functions
    sd_light_off.entry = [this](FSMInitContextType& ctx) { set_brightness(0); };

    sd_manual_mode.entry = [this](FSMInitContextType& ctx) { set_brightness(sd_manual_mode.cur_brightness); };
}

FSM::StateHandleType& FSM::t_manual_mode_init() {
    sd_manual_mode.cur_brightness = 1;
    return sd_manual_mode;
}

FSM::StateHandleType& FSM::t_manual_mode_on_press() {
    sd_manual_mode.cur_brightness = (sd_manual_mode.cur_brightness % 3) + 1;
    return sd_manual_mode;
}

FSM::MotionModeHierarchy::MotionModeHierarchy() {
    sd_mm_init.transitions = [this](const EventBaseType& ev, TransitionType& trans) {
        switch (ev.id) {
        case EventID::MotionDetect:
            return trans.set(sd_mm_detect);
        default:
            return super(ev, trans);
        }
    };

    sd_mm_detect.transitions = [this](const EventBaseType& ev, TransitionType& trans) {
        switch (ev.id) {
        case EventID::MotionDetect:
            return trans.set(sd_mm_detect);
        case EventID::MotionDetectTimeout:
            return trans.set(sd_mm_init);
        default:
            return super(ev, trans);
        }
    };

    sd_mm_init.entry = [this](FSMInitContextType& ctx) { set_brightness(0); };

    sd_mm_detect.entry = [this](FSMInitContextType& ctx) {
        set_brightness(3);
        ctx.set_callback([this](FSMContextType& ctx) { ctx.submit_event(EventMotionDetectTimeout()); }, true, 3000);
    };
}
