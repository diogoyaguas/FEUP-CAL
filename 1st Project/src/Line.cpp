#include "Line.h"

#include <utility>

using namespace std;

Line::Line() = default;

Line::Line(LineID lineID, vector<string> stopsID)
 {
	 this->lineID = lineID;
	 this->stopsID = std::move(stopsID);
 }

Line::~Line() = default;



