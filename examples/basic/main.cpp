#include <iostream>
#include <thread>

#include <cereal/archives/json.hpp>
#define AW_NVP(x) CEREAL_NVP(x)
#define AW_NAME_VALUE(name, value) cereal::make_nvp(name, value)

#include <aw/engine/engine.hpp>
#include <aw/engine/logEngine.hpp>
#include <aw/util/log/consoleSink.hpp>
#include <aw/util/log/log.hpp>
#include <aw/util/log/logger.hpp>

#include <aw/engine/config.hpp>

#include <aw/util/reflection/reflection.hpp>

#include <fstream>

template <typename ClassMember, typename Instance>
void printRecursive(const ClassMember& member, const Instance& instance)
{
  using typeDesc = std::remove_reference_t<decltype(member.underlyingDescriptor())>;

  if constexpr (std::is_base_of_v<aw::reflect::ClassTypeDescriptorBase, typeDesc>)
  {
    member.underlyingDescriptor().forAllMembers(
        [instance = member.value(instance)](const auto& mem) { printRecursive(mem, instance); });
  }
  else
  {
    std::cout << member.name() << "= " << member.value(instance) << std::endl;
  }
}

int main()
{
  auto logger = std::make_shared<aw::log::Logger>();
  logger->addSink(std::make_shared<aw::log::ConsoleSink>());

  aw::log::setDefaultLogger(logger);

  aw::engine::Config config;
  config.test = 42;
  config.application.name = "TestApp";
  config.window.width = 1920;
  config.window.height = 1080;

  {
    std::fstream file("test.json", std::ios::out);
    cereal::JSONOutputArchive outputArchive(file);
  }

  auto reflect = aw::engine::Config::getTypeDescriptor();
  std::cout << reflect.memberCount() << std::endl;
  reflect.forAllMembers([config](const auto& member) { printRecursive(member, config); });

  // aw::Engine engine;
  // engine.run();

  LOG_ENGINE(aw::log::Level::Debug, "Close main!");
}
