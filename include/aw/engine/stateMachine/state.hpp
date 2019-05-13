#pragma once

namespace aw::engine
{
class StateMachine;

class State
{
public:
  State(StateMachine& stateMachine);
  virtual ~State() = default;

  virtual void update(float dt) = 0;
  virtual void render() = 0;

  virtual void onShow() {}
  virtual void onHide() {}

protected:
  StateMachine& stateMachine();
  const StateMachine& stateMachine() const;

private:
  StateMachine& mStateMachine;
};
} // namespace aw::engine
