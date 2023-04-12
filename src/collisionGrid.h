#pragma once
#include "particle.h"
#include "grid.h"

struct CollisionCell {
	static const int CELL_CAPACITY = 10;

	int particles[CELL_CAPACITY] = {};
	int particle_count = 0;

	CollisionCell() = default;

	void addParticle(int pId);
	void removeParticle(int pId);
	void clear();
};

struct CollisionGrid
{
	float max_radius;
	float max_diameter;
	int height;
	int width;
	vector<CollisionCell> cells;

	CollisionGrid() = default;
	CollisionGrid(int w, int h, float mr) : max_radius(mr), width(w / (2 * mr)), height(w / (2 * mr)), max_diameter(2 * mr)
		{ cells.resize(ceil((float)(width * height))); };

	void addParticle(int x, int y, int pId);
	void clear();
	CollisionCell& get(int x, int y);
};