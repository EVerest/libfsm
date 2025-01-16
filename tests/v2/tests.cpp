#include <cstdio>

#include <fsm/v2/fsm.hpp>

// simple states
#include "s_context.hpp"
#include "s_states.hpp"

// compound states
#include "c_context.hpp"
#include "c_states.hpp"

void test_simple() {
    simple::Context ctx;

    fsm::v2::FSM<simple::StateBase> fsm{ctx.create_state<simple::ResetState>()};

    const auto result_0 = fsm.feed(1);
    if (result_0.transitioned()) {
        printf("feed(1) led to a transition\n");
    }
    const auto result_1 = fsm.feed(1.3);
    if (result_1.transitioned()) {
        printf("feed(1.3) led to a transition\n");
    }

    if (fsm.get_current_state_id() == simple::StateID::Reset) {
        printf("state is in reset ...\n");
    }

    printf("result_0: %d, result_1: %f\n", *(result_0.output), *(result_1.output));
}

// ids is not allowed to be empty
template <typename NestedFsmType> void print_state_stack_ids(const NestedFsmType& fsm) {
    const auto ids = fsm.get_current_state_id();
    printf("id chain: ");
    const auto length = ids.size();
    for (int i = 0; i < length - 1; ++i) {
        printf("%d - ", ids[i]);
    }

    printf("%d\n", ids.back());
};

void test_compound() {
    compound::Context ctx;
    fsm::v2::NestedFSM<compound::StateBase> nested_fsm{ctx.create_state<compound::ParentState>()};

    print_state_stack_ids(nested_fsm);
    const auto result = nested_fsm.feed(1);
    printf("Got Result: %d\n", result.output);
    print_state_stack_ids(nested_fsm);
}

int main(int argc, char* argv[]) {
    test_simple();
    test_compound();

    return 0;
}