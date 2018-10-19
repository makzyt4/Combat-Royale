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

void CR::Ragdoll::addLimbs(b2World* world, const b2Vec2 &position) {
    b2RevoluteJointDef revoluteJointDef;
    revoluteJointDef.collideConnected = false;
    revoluteJointDef.enableLimit = true;

    CR::Box* torso = new Box(world, position + b2Vec2(0, -2), b2Vec2(22, 23), true); // 0
    CR::Box* head = new Box(world, position + b2Vec2(0, -20), b2Vec2(12, 12), true); // 1
    revoluteJointDef.bodyA = torso->getBody();
    revoluteJointDef.bodyB = head->getBody();
    revoluteJointDef.localAnchorA.Set(0, -12);
    revoluteJointDef.localAnchorB.Set(0, 6);
    revoluteJointDef.lowerAngle = -15 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 15 * (M_PI / 180.0);
    b2RevoluteJoint* joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(torso);
    this->addBox(head);
    this->addJoint(joint);

    CR::Box* leftForearm = new Box(world, position + b2Vec2(-20, -9), b2Vec2(13, 7), true); // 2
    revoluteJointDef.bodyB = leftForearm->getBody();
    revoluteJointDef.localAnchorA.Set(-11, -10);
    revoluteJointDef.localAnchorB.Set(5, 0);
    revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(leftForearm);
    this->addJoint(joint);

    CR::Box* leftUpperLeg = new Box(world, position + b2Vec2(-3, 14), b2Vec2(8, 14), true); // 3
    revoluteJointDef.bodyB = leftUpperLeg->getBody();
    revoluteJointDef.localAnchorA.Set(-3, 9);
    revoluteJointDef.localAnchorB.Set(0, -7);
    revoluteJointDef.lowerAngle = 0 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(leftUpperLeg);
    this->addJoint(joint);

    CR::Box* rightForearm = new Box(world, position + b2Vec2(20, -9), b2Vec2(13, 7), true); // 4
    revoluteJointDef.bodyB = rightForearm->getBody();
    revoluteJointDef.localAnchorA.Set(11, -10);
    revoluteJointDef.localAnchorB.Set(-5, 0);
    revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(rightForearm);
    this->addJoint(joint);

    CR::Box* rightUpperLeg = new Box(world, position + b2Vec2(3, 14), b2Vec2(8, 14), true); // 5
    revoluteJointDef.bodyB = rightUpperLeg->getBody();
    revoluteJointDef.localAnchorA.Set(3, 9);
    revoluteJointDef.localAnchorB.Set(0, -7);
    revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 0 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(rightUpperLeg);
    this->addJoint(joint);

    CR::Box* leftLowerLeg = new Box(world, position + b2Vec2(-3, 30), b2Vec2(8, 14), true); // 6
    revoluteJointDef.bodyA = leftUpperLeg->getBody();
    revoluteJointDef.bodyB = leftLowerLeg->getBody();
    revoluteJointDef.localAnchorA.Set(0, 7);
    revoluteJointDef.localAnchorB.Set(0, -7);
    revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 0 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(leftLowerLeg);
    this->addJoint(joint);

    CR::Box* rightLowerLeg = new Box(world, position + b2Vec2(3, 30), b2Vec2(8, 14), true); // 7
    revoluteJointDef.bodyA = rightUpperLeg->getBody();
    revoluteJointDef.bodyB = rightLowerLeg->getBody();
    revoluteJointDef.localAnchorA.Set(0, 7);
    revoluteJointDef.localAnchorB.Set(0, -7);
    revoluteJointDef.lowerAngle = 0 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(rightLowerLeg);
    this->addJoint(joint);

    CR::Box* leftArm = new Box(world, position + b2Vec2(-26, -9), b2Vec2(20, 7), true); // 8
    revoluteJointDef.bodyA = leftForearm->getBody();
    revoluteJointDef.bodyB = leftArm->getBody();
    revoluteJointDef.localAnchorA.Set(-6, 0);
    revoluteJointDef.localAnchorB.Set(5, 0);
    revoluteJointDef.lowerAngle = 0;
    revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(leftArm);
    this->addJoint(joint);

    CR::Box* rightArm = new Box(world, position + b2Vec2(26, -9), b2Vec2(20, 7), true); // 9
    revoluteJointDef.bodyA = rightForearm->getBody();
    revoluteJointDef.bodyB = rightArm->getBody();
    revoluteJointDef.localAnchorA.Set(6, 0);
    revoluteJointDef.localAnchorB.Set(-5, 0);
    revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 0;
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(rightArm);
    this->addJoint(joint);
}

CR::Ragdoll::Ragdoll(b2World* world, const b2Vec2 &position) {
    this->world = world;
    this->position = position;
    // this->addLimbs(world, position);
}
