# 🛡️ NativeShield

**NativeShield** is a comprehensive native **C/C++ Android protection library** that provides advanced **Anti-Debug** and **Anti-Tamper** techniques. It is designed to harden Android applications against reverse engineering, runtime instrumentation, and unauthorized memory access attempts.

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Android-green?logo=android" />
  <img src="https://img.shields.io/badge/Language-C++-blue?logo=c%2B%2B" />
  <img src="https://img.shields.io/badge/Security-AntiDebug%2FAntiTamper-red" />
  <img src="https://img.shields.io/badge/License-MIT-lightgrey" />
  <img src="https://img.shields.io/badge/NDK-Compatible-orange" />
</p>

---

## 📖 Table of Contents

- [Features & Modules](#-features--modules)
- [TODO](#-todo)
- [Important Notes](#-important-notes)
- [Credits](#-credits)
- [License](#-license)

---

## ✨ Features & Modules

NativeShield provides multiple protection layers to secure your Android application:

### 🔍 **Debugger Detection**
- Detects whether a debugger is attached to the app process
- Monitors common debugging techniques and tools
- Real-time detection with configurable response actions

### 🕷️ **Frida Detection**
- Blocks Frida server & gadget attempts at runtime instrumentation
- Detects Frida-related processes and libraries
- Prevents dynamic analysis and code injection

### 🧬 **Riru & Zygisk Detection**
- Identifies hooking frameworks injected into the Android runtime
- Detects Xposed-based modules and LSPosed
- Monitors system-level modifications

### 📱 **Root Detection**
- Finds traces of root binaries, `su`, and common rooting tools
- Checks for SuperSU, Magisk, and other root management apps
- Validates system integrity and permissions

### 🧾 **Memory Access & Dump Detection**
- Prevents `/proc/self/mem` reads and unauthorized memory access
- Blocks ptrace attachments and memory dump tools
- Protects sensitive data in memory

### 🧩 **Library Patch & Hook Detection**
- Detects tampering or hooking attempts on native shared libraries
- Monitors library integrity and modification attempts
- Prevents runtime patching and code injection

---

## 📋 TODO

- [ ] 📖 **Better documentation** (in-code comments & comprehensive README)
- [ ] 🛡️ **App Tamper Detection** (APK signature validation, checksum verification, etc.)
- [ ] 🧩 **Magisk-Hide Detection Module** (e.g. Shamiko detection)
- [ ] 📜 **Blacklist system** for AntiLibPatch module

---

## ⚠️ Important Notes

### AndroidManifest.xml Configuration

**Critical:** Add the following attribute to your `AndroidManifest.xml` for proper functionality:

```xml
<application
    android:name=".MainActivity"
    android:extractNativeLibs="true"
    android:allowBackup="false"
    android:debuggable="false"
    ... >
    
    <!-- Your activities and other components -->
    
</application>
```

This attribute is **required** for the `AntiLibPatch` module to function correctly.

---

## 🙏 Credits

This project builds upon ideas and research from the following excellent projects:

- **[darvincisec/AntiDebugandMemoryDump](https://github.com/darvincisec/AntiDebugandMemoryDump)** - Anti-debugging and memory dump protection techniques
- **[darvincisec/DetectFrida](https://github.com/darvincisec/DetectFrida)** - Frida detection methods and implementations
- **[aimardcr/NativeDetector](https://github.com/aimardcr/NativeDetector)** - Native-level detection mechanisms

Special thanks to the Android security research community for their continuous efforts in improving mobile app security.

---

## 📄 License

```
MIT License

Copyright (c) 2025 PhuongDo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

<p align="center">
  <strong>⭐ If you find NativeShield helpful, please consider giving it a star!</strong>
</p>
