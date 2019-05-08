#include <aw/util/file/pathRegistry.hpp>

namespace aw::path
{
std::string_view asset()
{
  return "assets";
}
std::string_view config()
{
  return "configs";
}
std::string_view internal()
{
  return "~/.cache/";
}

std::string combineBaseWithFileName(std::string_view base, std::string_view fileName)
{
  std::string string;
  string.reserve(base.size() + fileName.size() + 1);
  string.append(base);
  string.push_back('/');
  string.append(fileName);
  return string;
}

std::string asset(std::string_view fileName)
{
  return combineBaseWithFileName(asset(), fileName);
};

std::string config(std::string_view fileName)
{
  return combineBaseWithFileName(config(), fileName);
};

std::string internal(std::string_view fileName)
{
  return combineBaseWithFileName(internal(), fileName);
}

bool isPrefix(std::string_view path, std::string_view prefix)
{
  return (path.size() >= prefix.size()) && (path.compare(0, prefix.size(), prefix) == 0);
}

bool isAsset(std::string_view path)
{
  return isPrefix(path, asset());
}
bool isConfig(std::string_view path)
{
  return isPrefix(path, config());
}
bool isInternal(std::string_view path)
{
  return isPrefix(path, internal());
}

} // namespace aw::path
