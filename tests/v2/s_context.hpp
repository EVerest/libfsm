#pragma once

#include <memory>

namespace simple {

class StateBase;

using BasePointerType = std::unique_ptr<StateBase>;

struct Context {
public:
    int a;
    int b;
    template <typename StateType, typename... Args> BasePointerType create_state(Args&&... args) {
        return std::make_unique<StateType>(*this, std::forward<Args>(args)...);
    }

private:
    int m_foo = 3;
};

// template <> std::unique_ptr<StateBase> Context::create_state<ResetState>();

} // namespace simple