#pragma once

#include "context.hpp"

class Context;

enum class Event {
    PressedOn,
    PressedOff,
    EnterMotionMode,
    MotionDetect,
    Timeout,
};

enum class StateID {
    LightOff,
    ManualMode,
    MotionMode,
    MotionIdle,
    MotionDetected,
};

struct Result {
    constexpr Result() = default;
    Result(BasePointerType result_state) : unhandled(false), new_state(std::move(result_state)) {
    }

    bool unhandled{true};
    BasePointerType new_state{nullptr};
};

struct PollResult {
    bool unhandled{false};
    BasePointerType new_state{nullptr};
};

struct StateBase {
    using ContainerType = BasePointerType;
    StateBase(StateID id, Context& ctx) : m_id(id), m_ctx(ctx){};

    virtual ~StateBase() = default;

    StateID get_id() const {
        return m_id;
    }

    virtual ContainerType get_initial() {
        return nullptr;
    };

    virtual void enter(){};
    virtual Result feed(Event) = 0;
    virtual void leave(){};

private:
    StateID m_id;

protected:
    Context& m_ctx;
};

struct LightOff : public StateBase {
    LightOff(Context& ctx) : StateBase(StateID::LightOff, ctx){};

    void enter() final {
        m_ctx.set_brightness(0);
    }

    Result feed(Event) final;
};

struct ManualMode : public StateBase {
    ManualMode(Context& ctx) : StateBase(StateID::ManualMode, ctx){};

    void enter() final {
        m_ctx.set_brightness(current_brightness);
    }

    void leave() final;

    Result feed(Event) final;

private:
    int current_brightness{1};
};

struct MotionMode : public StateBase {
    MotionMode(Context& ctx) : StateBase(StateID::MotionMode, ctx){};

    ContainerType get_initial() final;

    Result feed(Event) final;
};

struct MotionIdle : public StateBase {
    MotionIdle(Context& ctx) : StateBase(StateID::MotionIdle, ctx){};

    void enter() final {
        m_ctx.set_brightness(0);
    }

    Result feed(Event) final;
};

struct MotionDetected : public StateBase {
    MotionDetected(Context& ctx) : StateBase(StateID::MotionDetected, ctx){};

    void enter() final {
        m_ctx.set_brightness(3);
    }

    Result feed(Event) final;

private:
    static const int TIMEOUT_MS = 3000;
    bool timeout_started{false};
};
