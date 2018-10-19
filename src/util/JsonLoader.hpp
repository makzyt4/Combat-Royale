#ifndef CR_JSONLOADER_HPP
#define CR_JSONLOADER_HPP

#include <fstream>
#include <sstream>
#include <string>
#include "../../3rdparty/picojson/picojson.h"

namespace CR {

    class JsonLoader {
    public:
        picojson::value* loadFromFile(const std::string& filename);
        picojson::value* loadFromString(const std::string& text);
    };

}

#endif
