#pragma once

#include <string>
#include <string_view>

namespace aw::path
{
std::string_view asset();
std::string_view config();
std::string_view internal();

std::string asset(std::string_view fileName);
std::string config(std::string_view fileName);
std::string internal(std::string_view fileName);

bool isAsset(std::string_view path);
bool isConfig(std::string_view path);
bool isInternal(std::string_view path);

} // namespace aw::path
