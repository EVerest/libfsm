#pragma once

#include <memory>
#include <optional>

#include "c_context.hpp"

namespace compound {

enum class StateID {
    Parent,
    Child,
    Sibling,
};

struct Result {
    Result() = default;
    Result(int result, BasePointerType result_state = nullptr) :
        unhandled(false), output(result), new_state(std::move(result_state)) {
    }

    bool unhandled{true};
    int output;
    BasePointerType new_state{nullptr};
};

struct StateBase {
    using ContainerType = BasePointerType;
    StateBase(StateID id) : m_id(id){};

    virtual ~StateBase() = default;

    StateID get_id() const {
        return m_id;
    }

    virtual ContainerType get_initial() {
        return nullptr;
    }

    virtual void enter(){};

    virtual Result feed(int input) = 0;

    virtual void leave(){};

private:
    StateID m_id;
};

class ParentState : public StateBase {
public:
    ParentState(Context& ctx) : StateBase(StateID::Parent), m_ctx(ctx){};

    ContainerType get_initial() final;

    Result feed(int input) final {
        return {10};
    }

private:
    Context& m_ctx;
};

class ChildState : public StateBase {
public:
    ChildState(Context& ctx) : StateBase(StateID::Child), m_ctx(ctx){};

    Result feed(int input) final;

private:
    Context& m_ctx;
};

class SiblingState : public StateBase {
public:
    SiblingState(Context& ctx) : StateBase(StateID::Sibling), m_ctx(ctx){};

    Result feed(int input) final {
        return {10};
    }

private:
    Context& m_ctx;
};

BasePointerType ParentState::get_initial() {
    return m_ctx.create_state<ChildState>();
}

Result ChildState::feed(int input) {
    return {3, m_ctx.create_state<ParentState>()};
}

} // namespace compound