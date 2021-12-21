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
#ifndef FSM_UTILS_IDENTIFIABLE_HPP
#define FSM_UTILS_IDENTIFIABLE_HPP

#include <utility>

namespace fsm {
namespace utils {

template <typename IDType> struct IdentifiableBase {
    IdentifiableBase(IDType id) : id(id) {
    }
    const IDType id;
};

template <typename IDType, IDType ID, typename T = void> struct Identifiable : IdentifiableBase<IDType> {
    Identifiable(T&& data) : IdentifiableBase<IDType>(ID), data(std::forward<T>(data)) {
    }

    Identifiable(const IdentifiableBase<IDType>& ev) :
        IdentifiableBase<IDType>(ID), data(static_cast<const Identifiable<IDType, ID, T>&>(ev).data) {
    }

    T data;
};

template <typename IDType, IDType ID> struct Identifiable<IDType, ID, void> : IdentifiableBase<IDType> {
    Identifiable() : IdentifiableBase<IDType>(ID) {
    }

    Identifiable(const IdentifiableBase<IDType>& ev) : IdentifiableBase<IDType>(ID) {
    }
};

template <typename IDType> struct IdentifiableTypeFactory {
    using Base = IdentifiableBase<IDType>;
    template <IDType ID, typename T = void> using Derived = Identifiable<IDType, ID, T>;
};

} // namespace utils
} // namespace fsm

#endif // FSM_UTILS_IDENTIFIABLE_HPP
