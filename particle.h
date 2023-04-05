#pragma once
#include <ofMain.h>

struct Particle {
	ofVec2f position;
	ofVec2f last_position;
	ofVec2f acceleration;
	ofColor color;
	float radius;
	Particle(ofVec2f pos, float radius, ofColor color);
	Particle() = default;
	void update(float dt);
	void draw();
	void accelerate(ofVec2f a);
	void setVelocity(ofVec2f vel, float dt);
};

