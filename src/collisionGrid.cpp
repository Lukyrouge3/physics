#include "collisionGrid.h"

void CollisionCell::addParticle(int pId)
{
	particles[particle_count] = pId;
	particle_count += particle_count < (CELL_CAPACITY-1);
}

void CollisionCell::removeParticle(int pId)
{
	for (int i(0); i < particle_count; i++) {
		if (particles[i] == pId) {
			particles[i] = particles[particle_count - 1];
			particle_count--;
			return;
		}
	}
}

void CollisionCell::clear()
{
	particle_count = 0;
}

void CollisionGrid::addParticle(int x, int y, int p_id)
{
	auto& cell = get(x / max_diameter, y / max_diameter);
	cell.addParticle(p_id);
}

void CollisionGrid::clear()
{
	for (auto& c : cells) {
		c.clear();
	}
}

CollisionCell& CollisionGrid::get(int x, int y)
{
	return cells[x + y * width];
}
