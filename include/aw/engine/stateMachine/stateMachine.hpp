#pragma once

#include <aw/engine/stateMachine/state.hpp>

#include <memory>
#include <queue>
#include <stack>

namespace aw::engine
{
// push/pop will always take place after the next render call, so each state has a update() before
// render()
// you can call push after pop but be aware that you cannot call pop() push() pop() push() the
// second pop will then be discareded
class StateMachine
{
public:
  void pushState(std::shared_ptr<State> state);

  void popState();
  void popAllStates();

  void update(float dt);
  void render();

private:
private:
  std::stack<std::shared_ptr<State>> mStateStack;
  int mPopCount{0};
  std::queue<std::shared_ptr<State>> mPushQueue;
};
} // namespace aw::engine
