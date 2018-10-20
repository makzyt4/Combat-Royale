#include "JsonLoader.hpp"

cr::JsonLoader &cr::JsonLoader::getInstance() {
    static cr::JsonLoader instance;

    return instance;
}

picojson::value* cr::JsonLoader::loadFromFile(const std::string& path) {
    std::string fullPath = "../res/json/" + path;

    auto it = this->jsonMap.find(fullPath);

    if (it != this->jsonMap.end()) {
        return it->second;
    }

    std::ifstream t(fullPath);
    std::stringstream buffer;

    if (t) {
        buffer << t.rdbuf();
    } else {
        std::cerr << "Error: Could not open JSON file \"" << fullPath << "\"" << std::endl;
        return nullptr;
    }

    return this->loadFromString(buffer.str());
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
