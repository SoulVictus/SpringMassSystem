#pragma once

#include "ofMain.h"
#include "../Spring.h"
#include "../Point.h"
#include <ofVec3f.h>
#include <vector>
#include <memory>
#include <iostream>

class ofApp : public ofBaseApp{

	private:
		ofEasyCam camera;
		std::unique_ptr<Spring> spring;
		std::unique_ptr<Point> point_b;

		float currentDT;
		float prevDT;

		bool isPause = true;

		bool isMovingPoint;
		int movingPointId;
		bool wasFixedBefore;
		
		float addingPointRadius = 60;

		ofVec2f currentMousePos;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void setPause(bool isPause);

		bool checkMouseClickCollidesPoint(Point &point, int x, int y);

		
};
