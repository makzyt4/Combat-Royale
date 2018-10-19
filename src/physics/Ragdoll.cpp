#include "Ragdoll.hpp"

void CR::Ragdoll::loadFromFile(const std::string& filename) {
    CR::JsonLoader* loader = new CR::JsonLoader();
    picojson::value* v = loader->loadFromFile(filename);

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

        CR::Box* box = new Box(this->world, this->position + localPosition, size, dynamic);
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

        revoluteJointDef.bodyA = this->boxes[bodyAIndex.get<double>()]->getBody();
        revoluteJointDef.bodyB = this->boxes[bodyBIndex.get<double>()]->getBody();
        revoluteJointDef.localAnchorA.Set(laAX.get<double>(), laAY.get<double>());
        revoluteJointDef.localAnchorB.Set(laBX.get<double>(), laBY.get<double>());
        revoluteJointDef.lowerAngle = lowerAngle.get<double>() * (M_PI / 180.0);
        revoluteJointDef.upperAngle = upperAngle.get<double>() * (M_PI / 180.0);

        b2RevoluteJoint* joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
        this->addJoint(joint);
    }
}


CR::Ragdoll::Ragdoll(b2World* world, const b2Vec2 &position) {
    this->world = world;
    this->position = position;
}
