/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2020 - 2021 Pionix GmbH and Contributors to EVerest
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FSM_HPP
#define FSM_HPP

#include <fsm/async.hpp>

#include "fsm_defs.hpp"

struct FSM {
    using EventInfoType = fsm::EventInfo<EventBaseType, EventBufferType>;
    using StateHandleType = fsm::async::StateHandle<EventInfoType, StateIDType>;
    using TransitionType = StateHandleType::TransitionWrapperType;
    using FSMContextType = StateHandleType::FSMContextType;

    // define state descriptors
    StateHandleType sd_light_off{{State::LightOff, "LightOff"}};

    struct ManualModeStateType : public StateHandleType {
        using StateHandleType::StateHandleType;
        int cur_brightness{0};
    } sd_manual_mode{{State::ManualMode, "ManualMode"}};

    struct MotionModeHierarchy {
        StateHandleType sd_mm_init{{State::MotionModeInit, "MotionModeInit"}};
        StateHandleType sd_mm_detect{{State::MotionModeDetect, "MotionModeDetect"}};
        MotionModeHierarchy();
        StateHandleType::TransitionTableType super;
    } sdh_motion_mode;

    // define transitions
    StateHandleType& t_manual_mode_init();
    StateHandleType& t_manual_mode_on_press();

    FSM();
};

#endif // FSM_HPP
