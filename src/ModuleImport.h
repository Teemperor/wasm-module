#ifndef WASMINT_MODULEIMPORT_H
#define WASMINT_MODULEIMPORT_H

#include <string>

class ModuleImport {

    std::string importName_;

    std::string module_;
    std::string function_;


public:
    ModuleImport() {
    }

    ModuleImport(std::string importName, std::string module, std::string function);

    const std::string importName() const {
        return importName_;
    }

    const std::string module() const {
        return module_;
    }

    const std::string function() const {
        return function_;
    }
};


#endif //WASMINT_MODULEIMPORT_H
