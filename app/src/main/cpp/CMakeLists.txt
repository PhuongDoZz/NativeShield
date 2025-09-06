cmake_minimum_required(VERSION 3.22.1)

project(NativeShield)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Set visibility to hidden by default
    set(BUILD_CXX_AND_C_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden \
    -fno-rtti -fno-exceptions")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} ${BUILD_CXX_AND_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} ${BUILD_CXX_AND_C_FLAGS}")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections -ffunction-sections")
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -DDEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -DDEBUG")

    add_compile_definitions(DEBUG_BUILD)
endif ()

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -marm")
endif ()

# Add root directory reference for easier header includes,
# It also let you avoid relative path e.g. #include "../include/header.h"
include_directories(./)

add_library(NativeShield SHARED
        main.cpp
        Utils/ElfImg.cpp
        Modules/AntiDebug/AntiDebug.cpp
        Modules/FridaDetect/FridaDetect.cpp
        Modules/RiGisk/RiGisk.cpp
        Modules/RootDetect/RootDetect.cpp
        Modules/AntiDump/AntiDump.cpp
        Modules/AntiLibPatch/AntiLibPatch.cpp)

target_include_directories(NativeShield PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/SecureAPI
        ${CMAKE_CURRENT_SOURCE_DIR}/SecureAPI/syscall/${ANDROID_ABI}
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

target_link_libraries(NativeShield log)