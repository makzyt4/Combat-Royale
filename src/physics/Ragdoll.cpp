#include "Ragdoll.hpp"

void CR::Ragdoll::addLimbs(b2World* world, const b2Vec2 &position) {
    b2RevoluteJointDef revoluteJointDef;
    revoluteJointDef.collideConnected = false;
    revoluteJointDef.enableLimit = true;

    CR::Box* torso = new Box(world, position + b2Vec2(0, -2), b2Vec2(22, 23), true);
    CR::Box* head = new Box(world, position + b2Vec2(0, -20), b2Vec2(12, 12), true);
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

    CR::Box* leftForearm = new Box(world, position + b2Vec2(-20, -9), b2Vec2(13, 7), true);
    revoluteJointDef.bodyB = leftForearm->getBody();
    revoluteJointDef.localAnchorA.Set(-11, -10);
    revoluteJointDef.localAnchorB.Set(5, 0);
    revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(leftForearm);
    this->addJoint(joint);

    CR::Box* leftUpperLeg = new Box(world, position + b2Vec2(-3, 14), b2Vec2(8, 14), true);
    revoluteJointDef.bodyB = leftUpperLeg->getBody();
    revoluteJointDef.localAnchorA.Set(-3, 9);
    revoluteJointDef.localAnchorB.Set(0, -7);
    revoluteJointDef.lowerAngle = 0 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(leftUpperLeg);
    this->addJoint(joint);

    CR::Box* rightForearm = new Box(world, position + b2Vec2(20, -9), b2Vec2(13, 7), true);
    revoluteJointDef.bodyB = rightForearm->getBody();
    revoluteJointDef.localAnchorA.Set(11, -10);
    revoluteJointDef.localAnchorB.Set(-5, 0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(rightForearm);
    this->addJoint(joint);

    CR::Box* rightUpperLeg = new Box(world, position + b2Vec2(3, 14), b2Vec2(8, 14), true);
    revoluteJointDef.bodyB = rightUpperLeg->getBody();
    revoluteJointDef.localAnchorA.Set(3, 9);
    revoluteJointDef.localAnchorB.Set(0, -7);
    revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 0 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(rightUpperLeg);
    this->addJoint(joint);

    CR::Box* leftLowerLeg = new Box(world, position + b2Vec2(-3, 30), b2Vec2(8, 14), true);
    revoluteJointDef.bodyA = leftUpperLeg->getBody();
    revoluteJointDef.bodyB = leftLowerLeg->getBody();
    revoluteJointDef.localAnchorA.Set(0, 7);
    revoluteJointDef.localAnchorB.Set(0, -7);
    revoluteJointDef.lowerAngle = -90 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 0 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(leftLowerLeg);
    this->addJoint(joint);

    CR::Box* rightLowerLeg = new Box(world, position + b2Vec2(3, 30), b2Vec2(8, 14), true);
    revoluteJointDef.bodyA = rightUpperLeg->getBody();
    revoluteJointDef.bodyB = rightLowerLeg->getBody();
    revoluteJointDef.localAnchorA.Set(0, 7);
    revoluteJointDef.localAnchorB.Set(0, -7);
    revoluteJointDef.lowerAngle = 0 * (M_PI / 180.0);
    revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(rightLowerLeg);
    this->addJoint(joint);

    CR::Box* leftArm = new Box(world, position + b2Vec2(-23, -9), b2Vec2(20, 7), true);
    revoluteJointDef.bodyA = leftForearm->getBody();
    revoluteJointDef.bodyB = leftArm->getBody();
    revoluteJointDef.localAnchorA.Set(-6, 0);
    revoluteJointDef.localAnchorB.Set(5, 0);
    revoluteJointDef.lowerAngle = 0;
    revoluteJointDef.upperAngle = 90 * (M_PI / 180.0);
    joint = (b2RevoluteJoint*) world->CreateJoint(&revoluteJointDef);
    this->addBox(leftArm);
    this->addJoint(joint);

    CR::Box* rightArm = new Box(world, position + b2Vec2(23, -9), b2Vec2(20, 7), true);
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
    this->addLimbs(world, position);
}
