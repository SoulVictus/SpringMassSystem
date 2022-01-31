#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	prevDT = 0.f;
	spring = std::make_unique<Spring>(ofVec2f(250, 250), 50, 25, 20000, 10);

	spring->getPoint(0).setIsFixed(true);
	spring->getPoint(9).setIsFixed(true);

}

//--------------------------------------------------------------
void ofApp::update(){
	if (!isPause)
	{
		spring->update(0.01);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	spring->draw();
	
	ofSetColor(ofColor::blue, 20);
	ofDrawCircle(currentMousePos, addingPointRadius);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case 'p':
			setPause(!isPause);
			break;
		case 'r':
			spring->clearSpring();
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	currentMousePos = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (isMovingPoint) {
		spring->getPoint(movingPointId).setPosition(ofVec2f(x, y));
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if (button == 1)
	{
		ofVec2f pointPos = ofVec2f(x, y);
		spring->addPoint(pointPos, addingPointRadius);
		return;
	}


	for (size_t i = 0; i < spring->getPointsVector().size(); i++)
	{
		Point &point = *spring->getPointsVector().at(i);
		if (checkMouseClickCollidesPoint(point, x, y))
		{
			switch (button) {
				case 0:
					point.setIsFixed(!point.getIsFixed());
					break;
				case 2:
					wasFixedBefore = point.getIsFixed();
					point.setIsFixed(true);
					isMovingPoint = true;
					movingPointId = i;
					break;
			}		
		}
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (isMovingPoint) {
		spring->getPoint(movingPointId).resetForce();
		isMovingPoint = false;
		if (!wasFixedBefore)
			spring->getPoint(movingPointId).setIsFixed(false);
	}

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	if (scrollY > 0)
		addingPointRadius += 5;
	if (scrollY < 0)
		addingPointRadius -= 5;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

bool ofApp::checkMouseClickCollidesPoint(Point& point, int x, int y)
{
	ofVec2f pos = point.getPosition();
	ofVec2f mousePos = ofVec2f(x, y);
	if (pos.distance(mousePos) < 10)
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::setPause(bool isPause)
{
	this->isPause = isPause;
}
