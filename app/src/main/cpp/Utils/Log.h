#include <cstdio>
#include <unistd.h>

#include <android/log.h>
#include <string>

#ifdef DEBUG_BUILD
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "NativeShield", __VA_ARGS__)) // Disable this on production
#else
#define LOGI(...)
#endif
