#pragma once
#include "particle.h"
#include "collisionGrid.h"
#include "thread_pool.h"
using namespace std;

const float GRAVITY_STRENGTH = 200.0f;
const float FRAMERATE = 60.0f;
const int SUB_STEPS = 8;

class Solver
{
	public:
		Solver() = default;
		Solver(int width, int height, float min_radius, int thread_count) : grid(width, height, min_radius), pool(thread_count){};
		void update();
		void draw();
		Particle& spawnParticle(ofVec2f position, float radius, ofColor color);
		void setParticleVelocity(Particle& p, ofVec2f vel, float dt);
		int getParticleCount();
		CollisionGrid grid;
		ThreadPool pool;
		void processCell(int i, int slice_size);

	private:
		vector<Particle> particles;
		float getStepDt();
		void applyGravity();
		void applyContraint();
		void applyCollision();
		void addObjectsToGrid();
		void solveContact(int p_id_1, int p_id_2);
		void checkCellCollision(int p_id, const CollisionCell& c);
		void processCells(const CollisionCell& c_1, const CollisionCell& c_2);
};

