#include <aw/engine/config.hpp>

#include <aw/engine/logEngine.hpp>
#include <aw/util/file/inputStream.hpp>
#include <aw/util/file/outputStream.hpp>
#include <aw/util/file/pathRegistry.hpp>

namespace aw::engine
{
void Config::save() {}

Config Config::load()
{
  Config config;

  auto path = aw::path::config("engine.json");
  aw::file::InputStream file(path);
  if (!file.isOpen())
  {
    LOG_ENGINE(aw::log::Level::Warning,
               "Could not find engine config at {}, using default config\n", path);
    return config;
  }

  return config;
}
} // namespace aw::engine
