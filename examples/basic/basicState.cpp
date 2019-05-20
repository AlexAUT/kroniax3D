#include "basicState.hpp"

#include <aw/engine/engine.hpp>
#include <aw/engine/resources/loaders/assimpLoader.hpp>
#include <aw/graphics/core/shaderStage.hpp>
#include <aw/opengl/opengl.hpp>

#include "logApp.hpp"

BasicState::BasicState(aw::engine::Engine& engine) :
    State(engine.stateMachine()),
    WindowEventSubscriber(engine.messageBus()),
    mEngine(engine)
{
  aw::engine::AssimpLoader loader;
  if (!loader.load(mLevelMesh, "/home/alex/Documents/git/awEngine/examples/basic/assets/torus.obj"))
    LOG_APP_E("Could not load level mesh...\n");

  aw::gpu::ShaderStage vShader(aw::gpu::ShaderStage::Type::Vertex);
  vShader.loadFromPath(
      "/home/alex/Documents/git/awEngine/examples/basic/assets/shaders/simple_vs.glsl");

  aw::gpu::ShaderStage fShader(aw::gpu::ShaderStage::Type::Fragment);
  fShader.loadFromPath(
      "/home/alex/Documents/git/awEngine/examples/basic/assets/shaders/simple_fs.glsl");

  mBasicShader.link(vShader, fShader);

  glClearColor(0.75, 0.75, 0.75, 1.0);
}

void BasicState::onShow()
{
  LOG_APP_D("SHOW!\n");
}

void BasicState::update(float dt)
{
  // LOG_APP(aw::log::Level::Debug, "Update in basic state! {}\n", dt);
}

void BasicState::render()
{
  // LOG_APP(aw::log::Level::Warning, "Render nothing :/ \n");
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  mLevelMesh.bind();
  mBasicShader.bind();
  GL_CHECK(glDrawElements(GL_TRIANGLES, mLevelMesh.indices().size(), GL_UNSIGNED_INT, nullptr));
}

void BasicState::receive(const aw::windowEvent::Closed& event)
{
  LOG_APP_E("In event receive?");
  mEngine.terminate();
}

void BasicState::receive(const aw::windowEvent::Resized& event)
{
  LOG_APP_E("Resize event: {},{}\n", event.width, event.height);
  GL_CHECK(glViewport(0, 0, event.width, event.height));
}
