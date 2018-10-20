#ifndef CR_JSONLOADER_HPP
#define CR_JSONLOADER_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "../../3rdparty/picojson/picojson.h"

namespace cr {

    class JsonLoader {
    private:
        JsonLoader() = default;

        std::map<std::string, picojson::value*> jsonMap;

    public:
        static JsonLoader &getInstance();

        picojson::value* loadFromFile(const std::string& filename);
        picojson::value* loadFromString(const std::string& text);
    };

}

#endif
