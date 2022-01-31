#include "Point.h"

Point::Point(ofVec2f position, float mass, bool fixed)
    : position(position),prevPosition(position), isFixed(fixed), mass(mass)
{

}

Point::~Point()
{

}

ofVec2f& Point::getPosition()
{
    return position;
}

void Point::setPosition(ofVec2f position)
{
    this->position = position;
}

ofVec2f& Point::getPrevPosition()
{
    return prevPosition;
}

void Point::setPrevPosition(ofVec2f prevPosition)
{
    this->prevPosition = prevPosition;
}

ofVec2f& Point::getForce()
{
    return force;
}

void Point::updateForce(ofVec2f force)
{
    this->force += force ;
}

void Point::resetForce()
{
    this->force = ofVec2f(0, 0);
}

ofVec2f& Point::getResistanceForce()
{
    return resistanceForce;
}

void Point::updateResistanceForce(ofVec2f force)
{
    this->resistanceForce = force;
}

void Point::resetResistanceForce()
{
    this->resistanceForce = ofVec2f(0, 0);
}

float Point::getMass()
{
    return mass;
}

void Point::setMass(float mass)
{
    this->mass = mass;
}

bool Point::getIsFixed()
{
    return isFixed;
}

void Point::setIsFixed(bool isFixed)
{
    this->isFixed = isFixed;
}
