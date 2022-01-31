#pragma once
#include "Point.h"
#include "ofVec2f.h"
#include <vector>
#include <utility>
#include "ofGraphics.h"
class Spring
{
private:

	ofVec2f position;
	std::vector<Point*> pointsVector;
	std::vector<std::pair<Point&, Point&>> connectionsVector;
	std::vector<float> lengthsVector;

	float mass;
	float k;

public:
	Spring(ofVec2f startPosition, float mass, float lineLength, float k, int amount);
	~Spring();

	void draw();
	void update(float deltatime);
	void updateSpringForce();
	void updateGravity();
	void addPoint(ofVec2f pos, float addingPointRadius);

	void clearSpring();
	
	Point& getPoint(int index);
	std::vector<Point*>& getPointsVector();
};

