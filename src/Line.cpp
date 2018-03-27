/*
 * Line.cpp
 *
 *  Created on: Mar 26, 2018
 *      Author: ricar
 */

#include "Line.h"

Line::Line() {
	// TODO Auto-generated constructor stub

}

 Line::Line(LineID lineID, vector<int> stopsID)
 {
	 this->lineID = lineID;
	 this->stopsID = stopsID;
 }

Line::~Line() {
	// TODO Auto-generated destructor stub
}

