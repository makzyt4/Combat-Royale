#include "Entity.hpp"

cr::Entity::Entity(b2World* world, const b2Vec2 &position) {
    this->world = world;
    this->position = position;

    this->boxes = new std::vector<cr::Box*>();
    this->joints = new std::vector<b2RevoluteJoint*>();
    this->spriteInfos = new std::vector<cr::SpriteInfo*>();
}

void cr::Entity::addBox(cr::Box* box) {
    this->boxes->push_back(box);
}

void cr::Entity::addJoint(b2RevoluteJoint* joint) {
    this->joints->push_back(joint);
}

void cr::Entity::addSpriteInfo(cr::SpriteInfo* spriteInfo) {
    this->spriteInfos->push_back(spriteInfo);
}

std::vector<cr::Box*> *cr::Entity::getBoxes() const {
    return this->boxes;
}

std::vector<b2RevoluteJoint*> *cr::Entity::getJoints() const {
    return this->joints;
}

std::vector<cr::SpriteInfo*> *cr::Entity::getSpriteInfos() const {
    return this->spriteInfos;
}

void cr::Entity::setTexture(sf::Texture* texture) {
    this->texture = texture;
}

void cr::Entity::loadFromJsonFile(const std::string& filename) {
    picojson::value* v = cr::JsonLoader::getInstance().loadFromFile(filename);

    b2RevoluteJointDef revoluteJointDef;
    revoluteJointDef.collideConnected = false;
    revoluteJointDef.enableLimit = true;

    picojson::value boxes = v->get("boxes");

    for (uint8_t i = 0; i < boxes.get<picojson::array>().size(); i++) {
        picojson::value boxJson = boxes.get(i);
        picojson::value localPositionJson = boxJson.get("local_position");
        picojson::value lpX = localPositionJson.get(0);
        picojson::value lpY = localPositionJson.get(1);

        picojson::value sizeJson = boxJson.get("size");
        picojson::value szX = sizeJson.get(0);
        picojson::value szY = sizeJson.get(1);

        bool dynamic = boxJson.get("dynamic").get<bool>();

        b2Vec2 localPosition = b2Vec2(lpX.get<double>(), lpY.get<double>());
        b2Vec2 size = b2Vec2(szX.get<double>(), szY.get<double>());

        cr::Box* box = new Box(this->world, this->position + localPosition, size, dynamic);
        this->addBox(box);
    }

    picojson::value joints = v->get("joints");

    for (uint8_t i = 0; i < joints.get<picojson::array>().size(); i++) {
        picojson::value jointJson = joints.get(i);
        
        picojson::value bodyAIndex = jointJson.get("body_a_index");
        picojson::value bodyBIndex = jointJson.get("body_b_index");

        picojson::value localAnchorA = jointJson.get("local_anchor_a");
        picojson::value laAX = localAnchorA.get(0);
        picojson::value laAY = localAnchorA.get(1);

        picojson::value localAnchorB = jointJson.get("local_anchor_b");
        picojson::value laBX = localAnchorB.get(0);
        picojson::value laBY = localAnchorB.get(1);

        picojson::value lowerAngle = jointJson.get("lower_angle");
        picojson::value upperAngle = jointJson.get("upper_angle");

        revoluteJointDef.bodyA = this->boxes->at(bodyAIndex.get<double>())->getBody();
        revoluteJointDef.bodyB = this->boxes->at(bodyBIndex.get<double>())->getBody();
        revoluteJointDef.localAnchorA.Set(laAX.get<double>(), laAY.get<double>());
        revoluteJointDef.localAnchorB.Set(laBX.get<double>(), laBY.get<double>());
        revoluteJointDef.lowerAngle = lowerAngle.get<double>() * (M_PI / 180.0);
        revoluteJointDef.upperAngle = upperAngle.get<double>() * (M_PI / 180.0);

        b2RevoluteJoint* joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addJoint(joint);
    }

    picojson::value texturePaths = v->get("texture_paths");

    std::vector<sf::Texture*> textures;

    for (uint8_t i = 0; i < texturePaths.get<picojson::array>().size(); i++) {
        textures.push_back(TextureLoader::getInstance().loadFromFile(texturePaths.get(i).get<std::string>()));
    }

    picojson::value sprites = v->get("sprites");

    for (uint8_t i = 0; i < sprites.get<picojson::array>().size(); i++) {
        picojson::value rectJson = sprites.get(i).get("rect");
        picojson::value offsetJson = sprites.get(i).get("offset");
        picojson::value layersJson = sprites.get(i).get("layers");

        uint8_t textureIndex = sprites.get(i).get("texture_index").get<double>();
        uint8_t bodyIndex = sprites.get(i).get("body_index").get<double>();
        std::string colorType = sprites.get(i).get("color_type").get<std::string>();
        sf::Vector2i offset = sf::Vector2i(offsetJson.get(0).get<double>(),
                                           offsetJson.get(1).get<double>());
        std::vector<std::string> layers;

        for (uint8_t i = 0; i < layersJson.get<picojson::array>().size(); i++) {
            layers.push_back(layersJson.get(i).get<std::string>());
        }

        sf::Sprite* sprite = new sf::Sprite();
        sprite->setTexture(*textures.at(textureIndex));

        sf::IntRect* rect = new sf::IntRect(rectJson.get(0).get<double>(), 
                                            rectJson.get(1).get<double>(), 
                                            rectJson.get(2).get<double>(), 
                                            rectJson.get(3).get<double>());

        sprite->setTextureRect(*rect);

        cr::SpriteInfo* spriteInfo = new SpriteInfo(bodyIndex, colorType, offset, layers, sprite);

        this->spriteInfos->push_back(spriteInfo);
    }
}

void cr::Entity::drawWireframe(sf::RenderWindow* window, const sf::Color& color) const {
    for (cr::Box* box : *this->boxes) {
        box->drawWireframe(window, color);
    }
}

void cr::Entity::draw(sf::RenderWindow* window) const {
    this->draw(window, new PlayerAppearance());
}

void cr::Entity::draw(sf::RenderWindow* window, cr::PlayerAppearance* appearance) const {
    for (int i = 0; i < this->spriteInfos->size(); i++) {
        cr::SpriteInfo* si = this->spriteInfos->at(i);

        uint8_t bodyIndex = si->getBodyIndex();
        std::string colorType = si->getColorType(); 
        sf::Vector2i offset = si->getOffset();
        std::vector<std::string> layers = si->getLayers();
        sf::Sprite* sprite = si->getSprite();

        b2Body *body = this->boxes->at(bodyIndex)->getBody();

        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle() * 180.0 / M_PI;

        sf::FloatRect rect = sprite->getGlobalBounds();

        sprite->setOrigin(rect.width / 2, rect.height / 2);
        sprite->setPosition(position.x + offset.x, position.y + offset.y);

        sf::Transform t;
        t.rotate(angle, position.x, position.y);

        window->draw(*sprite, t);
    }
}
