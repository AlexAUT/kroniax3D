#include <aw/util/file/path.hpp>

namespace aw::filePath
{
std::string_view fileName(std::string_view path)
{
  auto lastSlash = path.find_last_of('/');

  // There is not slash so it is a file directly
  if (lastSlash == std::string_view::npos)
    return path;

  // It ends with a slash
  if (lastSlash == path.size() - 1)
    return "";

  return path.substr(lastSlash + 1);
}

std::string_view stem(std::string_view path)
{
  std::string_view name = fileName(path);
  auto ext = extension(name);
  return name.substr(0, name.size() - ext.size());
}

std::string_view extension(std::string_view path)
{
  auto lastDot = path.find_last_of('.');
  if (lastDot == std::string_view::npos)
    return "";

  // If the path ends with a dot it has no extension
  if (lastDot == path.size() - 1)
    return "";

  // Look if there is not a slash right behind the dot
  if (lastDot > 0 && path[lastDot - 1] != '/')
    return path.substr(lastDot);

  return "";
}

bool hasFileName(std::string_view path)
{
  return fileName(path) != "";
}

bool hasStem(std::string_view path)
{
  return stem(path) != "";
}

bool hasExtension(std::string_view path)
{
  return extension(path) != "";
}

std::string_view parentPath(std::string_view path)
{
  auto lastSlash = path.find_last_of('/');
  if (lastSlash != 0 && lastSlash == std::string_view::npos)
    return "";
  // Handle case pos == 0 to return the slash
  if (lastSlash == 0)
    return path.substr(0, 1);

  // Otherwise return everything before the slash
  return path.substr(0, lastSlash);
}

bool hasParentPath(std::string_view path)
{
  return parentPath(path) != "";
}

bool isAbsolute(std::string_view path)
{
  return !path.empty() && path.front() == '/';
}

bool isRelative(std::string_view path)
{
  return !isAbsolute(path);
}

} // namespace aw::filePath
