#pragma once

#include <vector>

class CellGrid {
public:
	bool load(int width, int height, int n);
	void makeNoise();
	void step(int hood);

	std::vector<int> cells;

private:
	int W, H, N;
};

