#include "../IModule.h"
#include "constants.h"

struct ExecutableRegion {
    std::string                 libPath;
    Pointer                     baseAddress;
    std::pair<Pointer, Pointer> chunkData;
    uint32_t                    initialChecksum;

    ExecutableRegion(std::string path,
                     Pointer address,
                     std::pair<Pointer, Pointer> chunk,
                     uint32_t initialChecksum)
            : libPath(std::move(path)),
              baseAddress(address),
              chunkData(std::move(chunk)),
              initialChecksum(initialChecksum) {}
};

class AntiLibPatch : public IModule {
    using onLibTamperedCallbackType = void (*)(const char *libPath,
                                               uint32_t old_checksum,
                                               uint32_t new_checksum);
    onLibTamperedCallbackType onLibTampered;
public:
    explicit AntiLibPatch(onLibTamperedCallbackType = nullptr);
    const char *getName() override;
    eSeverity getSeverity() override;

    bool execute() override;
private:
    std::vector<ExecutableRegion> regions{};
};