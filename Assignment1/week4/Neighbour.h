/*
 * Neighbour.h
 *
 *  Created on: 20 Mar. 2019
 *      Author: dongmo
 */
#include <string>
#ifndef NEIGHBOUR_H_
#define NEIGHBOUR_H_
#include<iostream>
#include<list>

using namespace std;


	struct NeighbourCell {
		string first;
		int pipCount;
	};
	struct Cells {
		int xLoc;
		int yLoc;
		double heuristic;

		bool operator<(const Cells& cell) const {
			return heuristic < cell.heuristic;
		}

	};
	struct Favourable {
		string first;
		int pipCount;
		bool owned;
	};

#endif /* NEIGHBOUR_H_ */