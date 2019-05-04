#include <aw/config.hpp>

#ifdef AW_OS_ANDROID
#include "consoleSinkAndroidImpl.cpp"
#else
#include "consoleSinkPrintImpl.cpp"
#endif
