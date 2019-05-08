#pragma once

#include <string_view>

namespace aw::filePath
{
std::string_view fileName(std::string_view path);
std::string_view stem(std::string_view path);
std::string_view extension(std::string_view path);

bool hasFileName(std::string_view path);
bool hasStem(std::string_view path);
bool hasExtension(std::string_view path);

std::string_view parentPath(std::string_view path);

bool hasParentPath(std::string_view path);

bool isAbsolute(std::string_view path);
bool isRelative(std::string_view path);
} // namespace aw::filePath
