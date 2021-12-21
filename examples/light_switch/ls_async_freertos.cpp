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
#include <stdlib.h>

extern "C" {
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
}

#include <fsm/specialization/async/freertos.hpp>

#include "async_fsm.hpp"

constexpr int STACK_SIZE = 400;

void log(const std::string& msg) {
    vLoggingPrintf("fsm log: %s\n", msg.c_str());
}

void delay(int ms) {
    constexpr TickType_t delay = 1000 / portTICK_PERIOD_MS;
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void set_brightness(int value) {
    vLoggingPrintf("Set brightness to value: %d\n", value);
}

void main_task(void* pvParameters) {
    FSM fsm_desc;
    fsm::async::FreeRTOSController<FSM::StateHandleType> fsm_ctrl;
    fsm_ctrl.run(fsm_desc.sd_light_off);

    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOn(), true);
    fsm_ctrl.submit_event(EventPressedOff(), true);
    fsm_ctrl.submit_event(EventPressedMot(), true);
    fsm_ctrl.submit_event(EventMotionDetect(), true);
    delay(5000);

    fsm_ctrl.stop();

    exit(0);

    // vTaskDelete(nullptr);
}

int main(int argc, char* argv[]) {
    xTaskCreate(main_task, "main_task", STACK_SIZE, nullptr, tskIDLE_PRIORITY, nullptr);

    vTaskStartScheduler();

    return 0;
}
