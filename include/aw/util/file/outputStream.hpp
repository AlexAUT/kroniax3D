#pragma once

#include <aw/config.hpp>

#include <fstream>
#include <string>

namespace aw::file
{
class OutputStream : public std::ostream
{
public:
  OutputStream(std::string_view path);

  bool isOpen() const { return mIsOpen; };

  const std::string_view getPath() const { return mPath; }

private:
  std::string mPath;
  std::ofstream mFileStream;
  bool mIsOpen;

#ifdef AW_OS_ANDROID
  bool mIsAssetFile{false};
#endif
};
} // namespace aw::file
