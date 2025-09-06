#include "AntiLibPatch.h"
#include "SecureAPI.h"
#include "Log.h"
#include "obfuscate.h"
#include "constants.h"
#include "ElfImg.h"

#include <vector>
#include <map>

#include <elf.h>
#include <fcntl.h>
#include <dirent.h>
#include <link.h>
#include <dlfcn.h>

static std::vector<std::string> blacklists{
        // Add your library here incase you don't want a certain library to be detected when it's tampered
        AY_OBFUSCATE("libclang_rt.ubsan_standalone-aarch64-android.so"),
        AY_OBFUSCATE("libart.so")
};

_forceinline static uint32_t crc32(const uint8_t *data, size_t size) {
    uint32_t    crc = 0xFFFFFFFF;
    for (size_t i   = 0; i < size; i++) {
        crc ^= data[i];
        for (size_t j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (0xEDB88320 & (-(crc & 1)));
        }
    }
    return ~crc;
}

AntiLibPatch::AntiLibPatch(
        void (*callback)(const char *libPath,
                         uint32_t old_checksum,
                         uint32_t new_checksum)) : onLibTampered(callback) {
    LOGI("AntiLibPatch::AntiLibPatch");
    SandHook::ElfImg linker(AY_OBFUSCATE("/linker"));
    ElfW(Addr) soListAddress = linker.getSymbAddress(
            AY_OBFUSCATE("__dl__ZL6solist"));

    if (soListAddress == null) {
        return;
    }

    ElfW(Addr) soInfo = *(ElfW(Addr) *) (soListAddress);
    while (soInfo != null) {
        ElfW(Addr) next           = *(ElfW(Addr) *) (soInfo + x32_64(0xA4, 0x28));
        ElfW(Addr) baseAddress    = *(ElfW(Addr) *) (soInfo + x32_64(0x104, 0xD0));
        const char *soNameAddress = *(const char **) (soInfo + x32_64(0x108, 0xD8));
        if (soNameAddress != nullptr) {
            struct dl_phdr_info info{};
            info.dlpi_addr  = baseAddress;
            info.dlpi_name  = soNameAddress;
            info.dlpi_phdr  = *(const ElfW(Phdr) **) (soInfo + x32_64(0x80, 0x0));
            info.dlpi_phnum = *(ElfW(Half) *) (soInfo + x32_64(0x84, 0x8));
            if (info.dlpi_phdr != nullptr) {
                LOGI("base %zx, libName %s\n", baseAddress, info.dlpi_name);

                bool      blacklistedLibrary = false;
                for (auto &blacklistedName: blacklists) {
                    if (SecureAPI::strstr(info.dlpi_name, blacklistedName.c_str())) {
                        blacklistedLibrary = true;
                        break;
                    }
                }

                if (!blacklistedLibrary) {
                    for (int i = 0; i < info.dlpi_phnum; ++i) {
                        const ElfW(Phdr) *phdr = &info.dlpi_phdr[i];
                        if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X) &&
                            (phdr->p_flags & PF_R)) {
                            ElfW(Addr) start = phdr->p_vaddr;
                            ElfW(Addr) end   = start + phdr->p_memsz;

                            auto     regionAddress = reinterpret_cast<const uint8_t *>(baseAddress +
                                                                                       start);
                            auto     regionSize    = end - start;
                            uint32_t checksum      = crc32(regionAddress, regionSize);

                            if (checksum != 0) {
                                regions.emplace_back(info.dlpi_name,
                                                     info.dlpi_addr,
                                                     std::pair(start, end),
                                                     checksum);
                            }
                        }
                    }
                }
            }
        }

        soInfo = next;
    }
}

const char *AntiLibPatch::getName() {
    return AY_OBFUSCATE("Lib. Patch & Hook Detection");
}

eSeverity AntiLibPatch::getSeverity() {
    return HIGH;
}

bool AntiLibPatch::execute() {
    LOGI("AntiLibPatch::execute");

    for (const auto &region: regions) {
        auto     regionSize      = region.chunkData.second - region.chunkData.first;
        auto     *regionAddress  = reinterpret_cast<uint8_t *>(region.baseAddress +
                                                               region.chunkData.first);
        uint32_t currentChecksum = crc32(regionAddress, regionSize);
        if (currentChecksum != region.initialChecksum) {
            if (this->onLibTampered) {
                this->onLibTampered(region.libPath.c_str(),
                                    region.initialChecksum,
                                    currentChecksum);
            }

            return true;
        }
    }

    return false;
}