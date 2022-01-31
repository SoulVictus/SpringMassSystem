#include "Spring.h"


Spring::Spring(ofVec2f startPosition, float mass, float lineLength, float k, int amount)
	: position(startPosition), mass(mass), k(k)
{
	for (size_t i = 0; i < amount; i++)
	{
		pointsVector.push_back(new Point(ofVec2f(lineLength * i + startPosition.x, startPosition.y) + position, mass));
	}

	for (size_t i = 1; i < amount; i++)
	{
		connectionsVector.emplace_back(*pointsVector.at(i - 1), *pointsVector.at(i));
		lengthsVector.push_back((connectionsVector.back().first.getPosition() - connectionsVector.back().second.getPosition()).length());
	}

}

Spring::~Spring()
{

}

void Spring::draw()
{
	ofSetColor(0, 255, 255);
	for (int i = 0; i < connectionsVector.size(); i++)
	{
		ofDrawLine(connectionsVector.at(i).first.getPosition(), connectionsVector.at(i).second.getPosition());
	}

	ofSetColor(0, 255, 0);
	for (int i = 0; i < pointsVector.size(); i++)
	{
		if (pointsVector.at(i)->getIsFixed())
			ofSetColor(255, 0, 0);
		else
			ofSetColor(0, 255, 0);

		ofDrawCircle(pointsVector.at(i)->getPosition(), 10);
	}
}

void Spring::update(float deltatime)
{
	updateGravity();
	updateSpringForce();
	for (size_t i = 0; i < pointsVector.size(); i++)
	{
		if (!pointsVector.at(i)->getIsFixed())
		{
			ofVec2f newPosition = pointsVector.at(i)->getPosition() + (pointsVector.at(i)->getPosition() - pointsVector.at(i)->getPrevPosition()) + ((deltatime * deltatime) * 0.5) * pointsVector.at(i)->getForce() / pointsVector.at(i)->getMass();
			pointsVector.at(i)->setPrevPosition(pointsVector.at(i)->getPosition());
			pointsVector.at(i)->setPosition(newPosition);
			pointsVector.at(i)->resetForce();
		}
		else {
			pointsVector.at(i)->setPrevPosition(pointsVector.at(i)->getPosition());
		}
	}
}

Point& Spring::getPoint(int index)
{
	return *pointsVector.at(index);
}

void Spring::addPoint(ofVec2f pos, float addingPointRadius)
{
	if (pointsVector.empty()) {
		pointsVector.push_back(new Point(pos, 50, true));
		return;
	}


	std::vector<int> pointsIdVector;
	for (size_t i = 0; i < pointsVector.size(); i++)
	{
		if (pointsVector.at(i)->getPosition().distance(pos) < addingPointRadius)
		{
			pointsIdVector.push_back(i);
		}
	}
	//std::cout << connectionsVector.size() << "\n";
	
	if (!pointsIdVector.empty())
	{
		pointsVector.push_back(new Point(pos, 50));
		for (int id : pointsIdVector)
		{
			connectionsVector.emplace_back(*pointsVector.at(id), *pointsVector.back());
			lengthsVector.push_back((pointsVector.back()->getPosition() - pointsVector.at(id)->getPosition()).length());
		}
	}
}

std::vector<Point*>& Spring::getPointsVector()
{
	return pointsVector;
}

void Spring::updateSpringForce()
{
	for (size_t i = 0; i < connectionsVector.size(); i++)
	{
		std::pair<Point&, Point&> connection = connectionsVector.at(i);

		ofVec2f shift = connection.second.getPosition() - connection.first.getPosition();				
		ofVec2f force = -this->k * (lengthsVector.at(i) * (shift / shift.length()) - shift);

		if (!connection.first.getIsFixed())
			connectionsVector.at(i).first.updateForce(force);
		if (!connection.second.getIsFixed())
			connectionsVector.at(i).second.updateForce(-force);
	}
}

void Spring::updateGravity()
{
	for (size_t i = 0; i < pointsVector.size(); i++)
	{
		if (!pointsVector.at(i)->getIsFixed())
			pointsVector.at(i)->updateForce(ofVec2f(0, 600 * pointsVector.at(i)->getMass()));
	}
}

void Spring::clearSpring()
{
	pointsVector.clear();
	connectionsVector.clear();
	lengthsVector.clear();
}

