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
	const int slice_count = pool._thread_count * 2;
	const int slice_size = (grid.width / slice_count) * grid.height;
	for (int i(0); i < pool._thread_count; i++) {
		pool.addTask([this, i, slice_size] {
			this->processCell(2 * i, slice_size);
		});
	}
	pool.waitForCompletion();
	for (int i(0); i < pool._thread_count; i++) {
		pool.addTask([this, i, slice_size] {
			this->processCell(2 * i + 1, slice_size);
		});
	}
	pool.waitForCompletion();
}

void Solver::addObjectsToGrid()
{
	grid.clear();

	ofVec2f worldSize(ofGetWidth(), ofGetHeight());

	int i(0);
	for (const auto& p : particles) {
		if (p.position.x > 1.0f && p.position.x < worldSize.x - 1.0f
			&& p.position.y > 1.0f && p.position.y < worldSize.y - 1.0f) {
			grid.addParticle((int)p.position.x, (int)p.position.y, i);
		}
		i++;
	}
}

void Solver::solveContact(int p_id_1, int p_id_2)
{
	auto& object1 = particles[p_id_1];
	auto& object2 = particles[p_id_2];
	ofVec2f v = object1.position - object2.position;
	float min_dist = object1.radius + object2.radius;
	const float dist = sqrt(v.x * v.x + v.y * v.y);
	if (dist < min_dist && dist > 0.01f) {
		ofVec2f n = v / dist;
		float delta = 0.5f * (dist - min_dist) * 0.75f;
		//const float mass_ratio_1 = object1.radius / (object1.radius + object2.radius);
		//const float mass_ratio_2 = object2.radius / (object1.radius + object2.radius);
		/*object1.position -= n * (mass_ratio_2 * delta);
		object2.position += n * (mass_ratio_1 * delta);*/
		object1.position -= (n * delta);
		object2.position += (n * delta);
	}
}

void Solver::checkCellCollision(int p_id, const CollisionCell& c)
{
	for (int i(0); i < c.particle_count; i++) {
		solveContact(p_id, c.particles[i]);
	}
}

void Solver::processCells(const CollisionCell& c_1, const CollisionCell& c_2)
{
	for (auto& p_1 : c_1.particles) {
		for (auto& p_2 : c_2.particles) {
			if (p_1 == p_2) continue;
			solveContact(p_1, p_2);
		}
	}
}

void Solver::processCell(int i, int slice_size)
{
	const int start = i * slice_size;
	const int end = start + slice_size;
	for (int i(start); i < end; i++) {
		const int x = i % grid.width;
		const int y = floor(i / grid.width);
		if (x == 0 || x == grid.width - 1 || y == 0 || y == grid.height - 1) continue;

		const auto& current_cell = grid.get(x, y);
		for (int dx(-1); dx <= 1; dx++) {
			for (int dy(-1); dy <= 1; dy++) {
				const auto& other_cell = grid.get(x + dx, y + dy);
				processCells(current_cell, other_cell);
			}
		}
	}
}

void Solver::update()
{	
	const float step_dt = getStepDt();
	for (uint32_t i{ SUB_STEPS }; i--;) {
		addObjectsToGrid();
		applyCollision();
		applyGravity();
		applyContraint();

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
