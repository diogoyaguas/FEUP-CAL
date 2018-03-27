/*
 * Line.h
 *
 *  Created on: Mar 26, 2018
 *      Author: ricar
 */

#ifndef SRC_LINE_H_
#define SRC_LINE_H_

#include "Graph.h"
#include "Station.h"
#include <vector>

struct LineID;

class Line {
public:
	Line();
	Line(LineID lineID, vector<int> stopsID);
	virtual ~Line();
private:
	LineID lineID;
	std::vector<int> stopsID;
};

struct LineID
{
	int lineID;
	char type; //0 - On foot (possible future update), 1 - Bus, 2 - Metro, 3 - Train

	bool operator==(const LineID& other) const
	{
		return (lineID == other.lineID && type == other.type);
	}
};

#endif /* SRC_LINE_H_ */
