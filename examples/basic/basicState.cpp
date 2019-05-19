#include "basicState.hpp"

#include <aw/engine/engine.hpp>
#include <aw/engine/resources/loaders/assimpLoader.hpp>

#include "logApp.hpp"

BasicState::BasicState(aw::engine::Engine& engine) :
    State(engine.stateMachine()),
    WindowEventSubscriber(engine.messageBus()),
    mEngine(engine)
{
  aw::engine::AssimpLoader loader;
  if (!loader.load(mLevelMesh, "/home/alex/Documents/git/awEngine/examples/basic/assets/torus.obj"))
    LOG_APP(aw::log::Level::Error, "Could not load level mesh...\n");
}

void BasicState::onShow()
{
  LOG_APP(aw::log::Level::Debug, "SHOW!\n");
}

void BasicState::update(float dt)
{
  // LOG_APP(aw::log::Level::Debug, "Update in basic state! {}\n", dt);
}

void BasicState::render()
{
  // LOG_APP(aw::log::Level::Warning, "Render nothing :/ \n");
}

void BasicState::receive(const aw::windowEvent::Closed& event)
{
  LOG_APP(aw::log::Level::Error, "In event receive?");
  mEngine.terminate();
}

void BasicState::receive(const aw::windowEvent::Resized& event)
{
  LOG_APP(aw::log::Level::Error, "Resize event: {},{}\n", event.width, event.height);
}
