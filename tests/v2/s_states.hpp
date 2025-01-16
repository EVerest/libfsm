#pragma once

#include <memory>
#include <optional>

#include "s_context.hpp"

namespace simple {

enum class StateID {
    Reset,
    PowerOn
};

struct StateBase;

template <typename OutputType> struct Result {
    Result() = default;
    Result(OutputType result_output, BasePointerType result_state = nullptr) :
        unhandled(false), output(std::move(result_output)), new_state(std::move(result_state)) {
    }

    bool unhandled{true};
    std::optional<OutputType> output;
    BasePointerType new_state{nullptr};
};

struct StateBase {
    using ContainerType = BasePointerType;
    StateBase(StateID id) : m_id(id){};

    virtual ~StateBase() = default;

    StateID get_id() const {
        return m_id;
    }

    virtual void enter(){};

    virtual Result<int> feed(int input) = 0;
    virtual Result<double> feed(double input) = 0;

    virtual void leave(){};

private:
    StateID m_id;
};

class ResetState : public StateBase {
public:
    ResetState(Context& ctx) : StateBase(StateID::Reset), m_ctx(ctx){};

    void enter() final;
    void leave() final;

    Result<double> feed(double input) final;

    Result<int> feed(int input) final {
        return {10};
    }

private:
    Context& m_ctx;
};

} // namespace simple