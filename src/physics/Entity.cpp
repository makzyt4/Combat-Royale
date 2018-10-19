#include "Entity.hpp"

void cr::Entity::addBox(cr::Box* box) {
    this->boxes->push_back(box);
}

void cr::Entity::addJoint(b2RevoluteJoint* joint) {
    this->joints->push_back(joint);
}

void cr::Entity::addSprite(sf::Sprite* sprite) {
    this->sprites->push_back(sprite);
}

std::vector<cr::Box*> *cr::Entity::getBoxes() const {
    return this->boxes;
}

std::vector<b2RevoluteJoint*> *cr::Entity::getJoints() const {
    return this->joints;
}

std::vector<sf::Sprite*> *cr::Entity::getSprites() const {
    return this->sprites;
}

void cr::Entity::setTexture(sf::Texture* texture) {
    this->texture = texture;
}

void cr::Entity::drawWireframe(sf::RenderWindow* window, const sf::Color& color) const {
    for (cr::Box* box : *this->boxes) {
        box->drawWireframe(window, color);
    }
}

void cr::Entity::loadFromJsonFile(const std::string& filename) {
    picojson::value* v = cr::JsonLoader::loadFromFile(filename);

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

    picojson::value sprites = v->get("sprites");

    for (uint8_t i = 0; i < sprites.get<picojson::array>().size(); i++) {
        
    }
}

cr::Entity::Entity(b2World* world, const b2Vec2 &position) {
    this->world = world;
    this->position = position;

    this->boxes = new std::vector<cr::Box*>();
    this->joints = new std::vector<b2RevoluteJoint*>();
    this->sprites= new std::vector<sf::Sprite*>();
}
