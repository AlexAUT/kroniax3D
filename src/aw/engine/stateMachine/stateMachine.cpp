#include <aw/engine/stateMachine/stateMachine.hpp>

#include <cassert>

namespace aw::engine
{
void StateMachine::pushState(std::shared_ptr<State> state)
{
  mPushQueue.push(std::move(state));
}

void StateMachine::popState()
{
  assert(mPushQueue.empty() &&
         "Read in the header file on why pop after push does not what you expect!");
  mPopCount++;
}

void StateMachine::popAllStates()
{
  assert(mPushQueue.empty() &&
         "Read in the header file on why pop after push does not what you expect!");
  mPopCount = mStateStack.size();
}

void StateMachine::update(float dt)
{
  if (!mStateStack.empty())
    mStateStack.top()->update(dt);
}

void StateMachine::render()
{
  if (!mStateStack.empty())
    mStateStack.top()->render();

  while (mPopCount > 0)
  {
    mStateStack.pop();
    mPopCount--;
    if (mStateStack.empty())
      mPopCount = 0;
  }

  auto pushStates = !mPushQueue.empty();
  if (pushStates && !mStateStack.empty())
    mStateStack.top()->onHide();

  while (!mPushQueue.empty())
  {
    mStateStack.push(mPushQueue.front());
    mPushQueue.pop();
  }

  if (pushStates)
    mStateStack.top()->onShow();
}
} // namespace aw::engine
