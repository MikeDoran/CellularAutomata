#include "CellGrid.h"
#include <vector>

//instantiates a new cell grid
bool CellGrid::load(int width, int height, int n) {
	std::vector<int> temp(width * height, 0);
	cells = temp;

	W = width;
	H = height;
	N = n;

	return true;
}

//fills the grid with flat noise between 0 and n-1
void CellGrid::makeNoise() {
	for (std::vector<int>::iterator it = cells.begin(); it != cells.end(); ++it) {
		*it = rand() % N;
	}
}

//steps all the cells in the grid based on rules specified in hood
//0 - moore neighborhood (all 8 neighbors)
//1 - Von Neumann neighborhood (top bottom left right)
//2 - Doran (couldn't find a name for this one) neighborhood (corners)
void CellGrid::step(int hood) {
	std::vector<int> newGrid;

	int x = 0;
	int y = 0;
	int neighbors[8] = { 0 };
	for (std::vector<int>::iterator it = cells.begin(); it != cells.end(); ++it) {
		int succ = (*it + 1) % N;

		//Get the neighbors (Assuming moore neighborhood)
		//TODO: make a switch for von neumann?
		neighbors[0] = ((x - 1) + ((y - 1) * W));//md
		neighbors[1] = ((x)+((y - 1) * W));//mv
		neighbors[2] = ((x + 1) + ((y - 1) * W));//md
		neighbors[3] = ((x + 1) + ((y)* W));//mv
		neighbors[4] = ((x + 1) + ((y + 1) * W));//md
		neighbors[5] = ((x)+((y + 1) * W));//mv
		neighbors[6] = ((x - 1) + ((y + 1) * W));//md
		neighbors[7] = ((x - 1) + ((y)* W));//mv

		switch (hood) {
		case 0: //Moore neighborhood
			for (int i = 0; i < 8; i++) {
				if ((neighbors[i] >= 0) && cells[neighbors[i]] == succ) {
					newGrid.push_back(succ);
					break;
				}
				else if (i == 7) {
					newGrid.push_back(*it);
				}
			}
			break;
		case 1://Von-neumann neighborhood
			for (int i = 1; i < 8; i += 2) {
				if ((neighbors[i] >= 0) && cells[neighbors[i]] == succ) {
					newGrid.push_back(succ);
					break;
				}
				else if (i == 7) {
					newGrid.push_back(*it);
				}
			}
			break;
		case 2://Doran neighborhood
			for (int i = 0; i < 8; i += 2) {
				if ((neighbors[i] >= 0) && cells[neighbors[i]] == succ) {
					newGrid.push_back(succ);
					break;
				}
				else if (i == 6) {
					newGrid.push_back(*it);
				}
			}
			break;
		}

		//update coords
		x++;
		x %= W;
		if (x == 0) y++;
	}

	cells.swap(newGrid);
}