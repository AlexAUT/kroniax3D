#include "basicState.hpp"

#include <aw/engine/engine.hpp>
#include <aw/engine/resources/loaders/ofbxLoader.hpp>
#include <aw/graphics/core/shaderStage.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/util/colors.hpp>

#include <glm/gtx/string_cast.hpp>

#include "logApp.hpp"

BasicState::BasicState(aw::engine::Engine& engine) :
    State(engine.stateMachine()),
    WindowEventSubscriber(engine.messageBus()),
    mEngine(engine),
    mNetworkHandler{*this, "127.0.0.1", 14441}
{
  aw::engine::OFBXLoader loader;
  if (!loader.load(mShipMesh, "assets/meshes/ship.fbx"))
  {
    LOG_APP_E("Could not the ship mesh");
  }

  if (!loader.load(mLevelMesh, "assets/levels/level2.fbx"))
  {
    LOG_APP_E("Could not load the level mesh!");
  }

  if (!loader.load(mMissleMesh, "assets/meshes/missle.fbx"))
  {
    LOG_APP_E("Could not load the missle mesh!");
  }
  mMissleMesh.transform().scale(aw::Vec3{0.05});

  aw::ShaderStage vShader(aw::ShaderStage::Type::Vertex);
  vShader.loadFromPath("assets/shaders/simple_vs.glsl");

  aw::ShaderStage fShader(aw::ShaderStage::Type::Fragment);
  fShader.loadFromPath("assets/shaders/simple_fs.glsl");

  mBasicShader.link(vShader, fShader);

  const auto clearColor = aw::Colors::BEIGE;
  GL_CHECK(glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0));
  GL_CHECK(glEnable(GL_DEPTH_TEST));

  mCamController.distance(4.f);

  mShipMesh.transform().scale(aw::Vec3{0.15});

  mCamController.rotation({aw::pi_2(), 0.f});

  mNetworkHandler.connect();
}

void BasicState::onShow() {}

void BasicState::update(float dt)
{
  mNetworkHandler.update(dt);

  for (auto& player : mPlayers)
    player.ship().update(dt);

  if (!mPause)
  {
    for (auto& missle : mMissles)
    {
      if (missle)
        missle->update(dt);
    }
  }

  // mCamController.lookAt(mShip.transform().position());
  mCamController.apply(mCamera);
}

void BasicState::render()
{
  // LOG_APP(aw::log::Level::Warning, "Render nothing :/ \n");
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  mShipMesh.bind();
  mBasicShader.bind();

  for (auto& player : mPlayers)
  {
    aw::Transform transform;
    mBasicShader.set("mvp", mCamera.viewProjection() * player.ship().transform().toMatrix() *
                                mShipMesh.transform().toMatrix());
    mBasicShader.set("view", mCamera.view());
    mBasicShader.set("color", aw::Colors::SKYBLUE);

    for (auto i = 0U; i < mShipMesh.subMeshes().size(); i++)
    {
      const auto& subMesh = mShipMesh.subMeshes()[i];

      GL_CHECK(glDrawElements(GL_TRIANGLES, subMesh.indicesCount, GL_UNSIGNED_INT,
                              reinterpret_cast<const void*>(subMesh.indicesOffset)));
    }
  }

  mLevelMesh.bind();
  mBasicShader.bind();
  mBasicShader.set("mvp", mCamera.viewProjection() * mLevelMesh.transform().toMatrix());
  mBasicShader.set("view", mCamera.view());
  mBasicShader.set("color", aw::Colors::FORESTGREEN);

  auto q = mShipMesh.transform().rotation();

  for (auto i = 0U; i < mLevelMesh.subMeshes().size(); i++)
  {
    const auto& subMesh = mLevelMesh.subMeshes()[i];
    GL_CHECK(glDrawElements(GL_TRIANGLES, subMesh.indicesCount, GL_UNSIGNED_INT,
                            reinterpret_cast<const void*>(subMesh.indicesOffset)));
  }
  mMissleMesh.bind();
  mBasicShader.bind();
  mBasicShader.set("view", mCamera.view());
  mBasicShader.set("color", aw::Colors::CRIMSON);

  for (auto& missle : mMissles)
  {
    if (!missle || !missle->alive())
      continue;

    mBasicShader.set("mvp", mCamera.viewProjection() * missle->transform().toMatrix() *
                                mMissleMesh.transform().toMatrix());

    for (auto i = 0U; i < mMissleMesh.subMeshes().size(); i++)
    {
      const auto& subMesh = mMissleMesh.subMeshes()[i];

      GL_CHECK(glDrawElements(GL_TRIANGLES, subMesh.indicesCount, GL_UNSIGNED_INT,
                              reinterpret_cast<const void*>(subMesh.indicesOffset)));
    }
  }
}

void BasicState::receive(const aw::windowEvent::Closed& event)
{
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
    auto rot = aw::Vec2(event.delta.y, -event.delta.x) * 0.01f;
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

void BasicState::receive(const aw::windowEvent::MouseWheelScrolled& event)
{
  if (event.wheel == aw::mouse::Wheel::Veritcal)
  {
    mCamController.distance(mCamController.distance() + event.delta);
  }
}

void BasicState::receive(const aw::windowEvent::KeyPressed& event)
{
  if (event.key == aw::keyboard::Key::LAlt)
    mPause = !mPause;
}

void BasicState::receive(const aw::windowEvent::KeyReleased& event) {}
