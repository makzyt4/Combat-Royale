#ifndef CR_JSONLOADER_HPP
#define CR_JSONLOADER_HPP

#include <fstream>
#include <sstream>
#include <string>
#include "../../3rdparty/picojson/picojson.h"

namespace cr {

    class JsonLoader {
    public:
        static picojson::value* loadFromFile(const std::string& filename);
        static picojson::value* loadFromString(const std::string& text);
    };

}

#endif
