#include "Line.h"

using namespace std;

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

