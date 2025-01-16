#include "s_context.hpp"

#include "s_states.hpp"

namespace simple {

template <> BasePointerType Context::create_state<ResetState>() {
    return std::make_unique<ResetState>(*this);
}

} // namespace simple