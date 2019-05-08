#include <aw/util/file/outputStream.hpp>

#include <aw/util/file/pathRegistry.hpp>

#include <cassert>

namespace aw::file
{
OutputStream::OutputStream(std::string_view path) : mPath(path)
{
  assert(!aw::path::isAsset(path) && "Never write to asset directory");

  mFileStream.open(mPath.c_str());
  mIsOpen = mFileStream.is_open();

  rdbuf(mFileStream.rdbuf());
}
} // namespace aw::file
