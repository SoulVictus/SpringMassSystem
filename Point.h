#pragma once
#include "ofVec2f.h"

class Point
{
private:
	ofVec2f position;
	ofVec2f prevPosition;
	ofVec2f force = ofVec2f(0, 0);
	ofVec2f resistanceForce = ofVec2f(0, 0);
	float mass;
	float radius;
	bool isFixed = false;

public:
	Point(ofVec2f position, float mass, bool isFixed = false);
	~Point();

	ofVec2f& getPosition();
	void setPosition(ofVec2f position);

	ofVec2f& getPrevPosition();
	void setPrevPosition(ofVec2f prevPosition);

	ofVec2f& getForce();
	void updateForce(ofVec2f force);
	void resetForce();

	ofVec2f& getResistanceForce();
	void updateResistanceForce(ofVec2f force);
	void resetResistanceForce();

	float getMass();
	void setMass(float mass);

	bool getIsFixed();
	void setIsFixed(bool isFixed);

};

