#pragma once
#include "particle.h"
using namespace std;

const float GRAVITY_STRENGTH = 100.0f;
const float FRAMERATE = 60.0f;
const int SUB_STEPS = 8;

class Solver
{
	public:
		Solver() = default;
		void applyGravity();
		void applyContraint();
		void applyCollision();
		void update();
		void draw();
		Particle& spawnParticle(ofVec2f position, float radius, ofColor color);
		void setParticleVelocity(Particle& p, ofVec2f vel, float dt);
		int getParticleCount();

	private:
		vector<Particle> particles;
		float getStepDt();
};

