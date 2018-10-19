#include "Box.hpp"


cr::Box::Box(b2World *world, const b2Vec2 &position, const b2Vec2 &size, const bool &is_dynamic) { 
    b2BodyDef *boxDef = new b2BodyDef();
    boxDef->position.Set(position.x, position.y);
    boxDef->type = (is_dynamic) ? b2_dynamicBody : b2_staticBody;

    this->body = world->CreateBody(boxDef);

    this->shape = new b2PolygonShape();
    this->shape->SetAsBox(size.x / 2.0f, size.y / 2.0f);

    b2FixtureDef *boxFixDef = new b2FixtureDef();
    boxFixDef->shape = this->shape;
    boxFixDef->density = 1.0f;
    boxFixDef->friction = 0.3f;

    this->body->CreateFixture(boxFixDef);
}

b2Body* cr::Box::getBody() const {
    return this->body;
}

b2PolygonShape* cr::Box::getShape() const {
    return this->shape;
}

std::vector<b2Vec2> cr::Box::getVertices() const {
    const int8_t count = this->shape->GetVertexCount();
    std::vector<b2Vec2> verts;

    for (int8_t i = 0; i < count; i++) {
        b2Vec2 vert = this->shape->GetVertex(i);
        verts.push_back(this->body->GetWorldPoint(vert));
    }

    return verts;
}

b2Vec2 cr::Box::getPosition() const {
    return this->body->GetPosition();
}

float cr::Box::getAngle() const {
    return this->body->GetAngle();
}

void cr::Box::drawWireframe(sf::RenderWindow* window, const sf::Color& color) const {
    std::vector<b2Vec2> verts = this->getVertices();

    sf::VertexArray lines(sf::LinesStrip, 5);

    for (int8_t i = 0; i < verts.size() + 1; i++) {
        lines[i].position = sf::Vector2f(verts[i % verts.size()].x, verts[i % verts.size()].y);
        lines[i].color = color;
    }

    window->draw(lines);
}
