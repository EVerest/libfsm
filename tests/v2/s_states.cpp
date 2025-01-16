#include "s_states.hpp"

#include <cstdio>

namespace simple {

void ResetState::enter() {
    printf("Entered ResetState!\n");
}

void ResetState::leave() {
    printf("Left ResetState!\n");
}

Result<double> ResetState::feed(double input) {
    return {3.140, m_ctx.create_state<ResetState>()};
}

} // namespace simple