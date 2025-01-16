#pragma once

#include <memory>

class StateBase;
using BasePointerType = std::unique_ptr<StateBase>;

struct Context {
public:
    template <typename StateType, typename... Args> BasePointerType create_state(Args&&... args) {
        return std::make_unique<StateType>(*this, std::forward<Args>(args)...);
    }

    void set_brightness(int value);
};
