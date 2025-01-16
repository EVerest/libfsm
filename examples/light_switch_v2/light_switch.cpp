// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 - 2023 Pionix GmbH and Contributors to EVerest
#include <cstddef>
#include <cstdio>

#include <chrono>
#include <thread>
#include <vector>

#include <fsm/v2/fsm.hpp>

#include "states.hpp"

int main(int argc, char* argv[]) {

    Context ctx;

    fsm::v2::NestedFSM<StateBase> fsm(ctx.create_state<LightOff>());

    auto state = ctx.create_state<ManualMode>();

    fsm.feed(Event::PressedOff);
    fsm.feed(Event::PressedOn);
    fsm.feed(Event::PressedOn);
    fsm.feed(Event::PressedOn);
    fsm.feed(Event::PressedOff);
    fsm.feed(Event::EnterMotionMode);
    fsm.feed(Event::MotionDetect);
    fsm.feed(Event::Timeout);
    fsm.feed(Event::PressedOn);
    fsm.feed(Event::PressedOn);

    return 0;
}
