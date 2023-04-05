#include "ofApp.h"
#include "../solver.h"

bool pause = true;

Solver solver;
//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(FRAMERATE);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (ofGetFrameNum() / FRAMERATE >= 5) {
		int fr = (int)ofGetFrameNum();
		if (fr % 4 == 0 && solver.getParticleCount() < 500) {
			ofColor color;
			color.setHsb(fr / 3 % 255, 150, 255);
			float radius = abs(ofRandomf()) * 10.0f + 5.0f;
			auto& particle = solver.spawnParticle({ ofGetWidth() / 2.0f, ofGetHeight() / 2.0f }, radius, color);
			float angle = sin(fr / 10.0f) + 3.14159f * 0.5f;
			particle.setVelocity(100.0f * ofVec2f(cos(angle), sin(angle)), 1.0f / FRAMERATE);
		}
		solver.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);

	ofSetColor(255);
	ofNoFill();
	ofSetCircleResolution(100);
	ofDrawCircle(ofGetWidth()/2.0f, ofGetHeight()/2.0f, 300.0f);

	int fr = ofGetLastFrameTime();

	stringstream ss;
	//ss << "FrameRate: " << fr << endl;
	//ofDrawBitmapString(ss.str(), 0, 0);
	//ss.clear();
	ss << "Particle count: " << solver.getParticleCount() << endl;
	ofSetColor(255);
	ofDrawBitmapString(ss.str(), 0, 20);
	ofFill();
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
