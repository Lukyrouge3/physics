#include "solver.h"

void Solver::applyGravity()
{
	ofVec2f acc(0, GRAVITY_STRENGTH);
	for (auto& particle : particles) {
		particle.accelerate(acc);
	}
}

void Solver::applyContraint()
{
	float radius = 300.0f;
	ofVec2f position(ofGetWidth()/2, ofGetHeight()/2);

	for (auto& particle : particles) {
		ofVec2f toParticle = position - particle.position;
		float dist = toParticle.length();
		if (dist > (radius - particle.radius)) {
			ofVec2f n = toParticle / dist;
			particle.position = position - n * (radius - particle.radius);
		}
	}
}

void Solver::applyCollision()
{
	auto size = particles.size();
	for (int i(0); i < size; i++) {
		auto& object1 = particles[i];
		for (int j(i + 1); j < size; j++) {
			auto& object2 = particles[j];
			ofVec2f v = object1.position - object2.position;
			float min_dist = object1.radius + object2.radius;
			float dist2 = v.x * v.x + v.y * v.y;
			if (dist2 < min_dist*min_dist) {
				float dist = sqrt(dist2);
				ofVec2f n = v / dist;
				float delta = 0.75f * 0.5f * (dist - min_dist);
				const float mass_ratio_1 = object1.radius / (object1.radius + object2.radius);
				const float mass_ratio_2 = object2.radius / (object1.radius + object2.radius);	
				object1.position -= n * (mass_ratio_2 * delta);
				object2.position += n * (mass_ratio_1 * delta);
			}
		}
	}
}

void Solver::update()
{	
	const float step_dt = getStepDt();
	for (uint32_t i{ SUB_STEPS }; i--;) {
		applyGravity();
		applyContraint();
		applyCollision();

		for (auto& particle : particles) {
			particle.update(step_dt);
		}
	}
}

void Solver::draw()
{
	ofSetCircleResolution(22);
	for (auto& particle : particles) {
		particle.draw();
	}
}

Particle& Solver::spawnParticle(ofVec2f position, float radius, ofColor color)
{
	Particle p(position, radius, color);
	particles.push_back(p);
	return particles.back();
}

void Solver::setParticleVelocity(Particle& p, ofVec2f vel, float dt)
{
	p.setVelocity(vel, dt);
}

int Solver::getParticleCount()
{
	return particles.size();
}

float Solver::getStepDt()
{
	return (1.0 / FRAMERATE) / (float) SUB_STEPS;
}
