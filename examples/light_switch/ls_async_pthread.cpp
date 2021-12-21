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
#include <iostream>

#include <fsm/specialization/async/pthread.hpp>

#include "async_fsm.hpp"

void set_brightness(int value) {
    std::cout << "Set brightness to value: " << value << "\n";
}

int main(int argc, char* argv[]) {
    FSM fsm_desc;
    fsm::async::PThreadController<FSM::StateHandleType> fsm_ctrl;
    fsm_ctrl.run(fsm_desc.sd_light_off);

    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOff(), true);
    fsm_ctrl.submit_event(EventPressedMot(), true);
    fsm_ctrl.submit_event(EventMotionDetect(), true);
    std::this_thread::sleep_for(std::chrono::seconds(5));

    fsm_ctrl.stop();
    return 0;
}
