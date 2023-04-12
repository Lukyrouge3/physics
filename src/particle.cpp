#include "particle.h"

Particle::Particle(ofVec2f pos, float r, ofColor col)
{
	position = pos;
	last_position = pos;
	color = col;
	radius = r;
}


void Particle::update(float dt)
{
	const ofVec2f vel = position - last_position;
	last_position = position;
	position = position + vel + acceleration * (dt * dt);

	acceleration = {0, 0};
}

void Particle::draw()
{
	ofSetColor(color);
	ofDrawEllipse(position, radius*2.0f, radius*2.0f);
}

void Particle::accelerate(ofVec2f a)
{
	acceleration += a;
}

void Particle::setVelocity(ofVec2f vel, float dt)
{
	last_position = position;
	last_position -= (vel * dt);
}
