#include "ofApp.h"
#include "../solver.h"

bool pause = true;

const float RADIUS = 6.0f;
const int WIDTH = 800;
const int HEIGHT = 800;


Solver solver(WIDTH, HEIGHT, RADIUS, 16);
//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(FRAMERATE);
}

//--------------------------------------------------------------
void ofApp::update() {
	int fr = (int)ofGetFrameNum();
	if (fr % 1 == 0 && solver.getParticleCount() < 1000 && fr > FRAMERATE * 3) {
		ofColor color;
		color.setHsb(fr / 3 % 255, 150, 255);
		//float radius = abs(ofRandomf()) * 10.0f + 1.0f;
		float radius = RADIUS;
		auto& particle = solver.spawnParticle({ ofGetWidth() / 2.0f, ofGetHeight() / 2.0f }, radius, color);
		float angle = sin(fr / 10.0f) + 3.14159f * 0.5f;
		particle.setVelocity(100.0f * ofVec2f(cos(angle), sin(angle)), 1.0f / FRAMERATE);
	}
	solver.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);

	ofSetColor(255);
	ofNoFill();
	ofSetCircleResolution(100);
	ofDrawCircle(ofGetWidth()/2.0f, ofGetHeight()/2.0f, 300.0f);
	ofFill();

	//ofSetColor(50);
	//ofSetLineWidth(1);
	//for (int i(0); i < solver.grid.width; i++) {
	//	ofDrawLine(i * RADIUS * 2, 0, i * RADIUS * 2, ofGetHeight());
	//}
	//for (int i(0); i < solver.grid.height; i++) {
	//	ofDrawLine(0, i * RADIUS * 2, ofGetWidth(), i * RADIUS * 2);
	//}

	//for (int i(0); i < solver.grid.cells.size(); i++) {
	//	auto c = solver.grid.cells[i];
	//	if (c.particle_count == 0) continue;
	//	ofSetColor(100, 0, 0, 50 * c.particle_count);
	//	int x = i % solver.grid.width;
	//	int y =  floor(i / solver.grid.height);
	//	ofDrawRectangle(x * RADIUS * 2, y * RADIUS * 2, 2 * RADIUS, 2 * RADIUS);
	//}

	int fr = ofGetLastFrameTime();

	stringstream ss;
	ss << "FrameRate: " << fr << endl;
	ofDrawBitmapString(ss.str(), 0, 0);
	ss.clear();
	ss << "Particle count: " << solver.getParticleCount() << endl;
	ofSetColor(255);
	ofDrawBitmapString(ss.str(), 0, 20);
	solver.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
