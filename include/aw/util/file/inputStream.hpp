#pragma once

#include <string>

#include <fstream>

namespace aw::file
{
class InputStream : public std::istream
{
public:
  InputStream(std::string_view path);
  ~InputStream();

  bool isOpen() const { return mIsOpen; }

  const std::string_view getPath() const { return mPath; }

private:
private:
  std::string mPath;
  std::ifstream mFileStream;
  bool mIsOpen;

#ifdef AW_OS_ANDROID
  bool mIsAssetFile{false};
#endif
};
} // namespace aw::file
