#include <aw/util/file/inputStream.hpp>

#include <aw/util/file/pathRegistry.hpp>

namespace aw::file
{
InputStream::InputStream(std::string_view path) : std::istream(nullptr), mPath(path)
{
  // Handle android asset file differently because they are zipped inside the apk
#ifdef AW_OS_ANDROID
  if (aw::path::isAsset(mPath))
  {
    auto* buffer = new AndroidAssetBuffer(mPath);
    mIsOpen = buffer->isOpen();
    if (mIsOpen)
      rdbuf(buffer);
    else
      delete buffer;
    return;
  }
#endif
  mFileStream.open(mPath.c_str(), std::ios::binary);
  mIsOpen = mFileStream.is_open();
  rdbuf(mFileStream.rdbuf());
}

InputStream::~InputStream()
{
#ifdef AW_OS_ANDROID
  if (mIsAssetFile)
  {
    delete rdbuf();
    return;
  }
#endif
  rdbuf(nullptr);
  mFileStream.close();
}

} // namespace aw::file
