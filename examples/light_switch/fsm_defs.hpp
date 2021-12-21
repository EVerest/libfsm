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
#ifndef FSM_DEFS_HPP
#define FSM_DEFS_HPP

#include <string>

#include <fsm/utils/Identifiable.hpp>

enum class EventID
{
    PressedOn,
    PressedMot,
    PressedOff,
    MotionDetect,
    MotionDetectTimeout
};

using EventTypeFactory = fsm::utils::IdentifiableTypeFactory<EventID>;

using EventPressedOn = EventTypeFactory::Derived<EventID::PressedOn>;
using EventPressedMot = EventTypeFactory::Derived<EventID::PressedMot>;
using EventPressedOff = EventTypeFactory::Derived<EventID::PressedOff>;
using EventMotionDetect = EventTypeFactory::Derived<EventID::MotionDetect>;
using EventMotionDetectTimeout = EventTypeFactory::Derived<EventID::MotionDetectTimeout>;

enum class State
{
    LightOff,
    ManualMode,
    MotionModeInit,
    MotionModeDetect
};

struct StateIDType {
    const State id;
    const std::string name;
};

using EventBufferType = std::aligned_union_t<0, EventPressedOn>;
using EventBaseType = EventTypeFactory::Base;

#endif // FSM_DEFS_HPP
