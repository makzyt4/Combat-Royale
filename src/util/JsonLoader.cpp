#include "JsonLoader.hpp"


picojson::value* cr::JsonLoader::loadFromFile(const std::string& filename) {
    std::ifstream t(filename);
    std::stringstream buffer;

    if (t) {
        buffer << t.rdbuf();
    } else {
        std::cerr << "Error: Could not open JSON file \"" 
                  << filename.c_str() << "\"" << std::endl;
    }

    return cr::JsonLoader::loadFromString(buffer.str());
}

picojson::value* cr::JsonLoader::loadFromString(const std::string& text) {
    auto v = new picojson::value();

    std::string err = picojson::parse(*v, text);

    if (!err.empty()) {
        std::cerr << err << std::endl;
        return nullptr;
    }

    return v;
}
