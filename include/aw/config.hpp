#pragma once

#ifdef __EMSCRIPTEN__

#define AW_OS_EMSCRIPTEN

#elif __ANDROID__

#define AW_OS_ANDROID

#elif _WIN32

#define AW_OS_WINDOWS

#ifdef _WIN64

#define AW_OS_WINDOWS_64

#else

#define AW_OS_WINDOWS_32

#endif
#elif __APPLE__

#define AW_OS_MAC

#if TARGET_IPHONE_SIMULATOR

#define AW_OS_IOS

#elif TARGET_OS_IPHONE

#define AW_OS_IOS

#elif TARGET_OS_MAC

#define AW_OS_IOS

#else

#error "Unknown Apple platform"

#endif
#elif __linux__

#define AW_OS_LINUX

#else

#error "Unknown compiler"

#endif
