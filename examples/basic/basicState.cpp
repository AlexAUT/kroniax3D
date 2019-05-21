#include "basicState.hpp"

#include <aw/engine/engine.hpp>
#include <aw/engine/resources/loaders/assimpLoader.hpp>
#include <aw/graphics/core/shaderStage.hpp>
#include <aw/opengl/opengl.hpp>

#include <glm/gtx/string_cast.hpp>

#include "logApp.hpp"

BasicState::BasicState(aw::engine::Engine& engine) :
    State(engine.stateMachine()),
    WindowEventSubscriber(engine.messageBus()),
    mEngine(engine)
{
  aw::engine::AssimpLoader loader;
  if (!loader.load(mLevelMesh, "/home/alex/Documents/git/awEngine/examples/basic/assets/ship.obj"))
    LOG_APP_E("Could not load level mesh...\n");

  aw::graphics::ShaderStage vShader(aw::graphics::ShaderStage::Type::Vertex);
  vShader.loadFromPath(
      "/home/alex/Documents/git/awEngine/examples/basic/assets/shaders/simple_vs.glsl");

  aw::graphics::ShaderStage fShader(aw::graphics::ShaderStage::Type::Fragment);
  fShader.loadFromPath(
      "/home/alex/Documents/git/awEngine/examples/basic/assets/shaders/simple_fs.glsl");

  mBasicShader.link(vShader, fShader);

  GL_CHECK(glClearColor(0.75, 0.75, 0.75, 1.0));
  GL_CHECK(glEnable(GL_DEPTH_TEST));

  mCamController.distance(4.f);
}

void BasicState::onShow() {}

void BasicState::update(float dt)
{
  using namespace aw::math;
  mCamController.apply(mCamera);
}

void BasicState::render()
{
  // LOG_APP(aw::log::Level::Warning, "Render nothing :/ \n");
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  mLevelMesh.bind();
  mBasicShader.bind();
  mBasicShader.set("mvp", mCamera.viewProjection());
  GL_CHECK(glDrawElements(GL_TRIANGLES, mLevelMesh.indices().size(), GL_UNSIGNED_INT, nullptr));
}

void BasicState::receive(const aw::windowEvent::Closed& event)
{
  LOG_APP_E("In event receive?");
  mEngine.terminate();
}

void BasicState::receive(const aw::windowEvent::Resized& event)
{
  GL_CHECK(glViewport(0, 0, event.size.x, event.size.y));
  mCamera.aspectRatio(static_cast<float>(event.size.x) / static_cast<float>(event.size.y));
}

void BasicState::receive(const aw::windowEvent::MouseMoved& event)
{
  if (mRightPressed)
  {
    auto rot = aw::math::Vec2(event.delta.y, -event.delta.x) * 0.01f;
    mCamController.rotation(mCamController.rotation() + rot);
  }
}

void BasicState::receive(const aw::windowEvent::MouseButtonPressed& event)
{
  if (event.button == aw::mouse::Button::Right)
    mRightPressed = true;
}

void BasicState::receive(const aw::windowEvent::MouseButtonReleased& event)
{
  if (event.button == aw::mouse::Button::Right)
    mRightPressed = false;
}
