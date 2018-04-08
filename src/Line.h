#ifndef FEUP_CAL_LINE_H_
#define FEUP_CAL_LINE_H_

#include <vector>
#include <string>

using namespace std;

struct LineID {
    int lineID;
    char type; //0 - On foot (possible future update), 1 - Bus, 2 - Metro, 3 - Train

    bool operator==(const LineID &other) const {
        return (lineID == other.lineID && type == other.type);
    }
};

class Line {
public:
    Line();

    Line(LineID lineID, std::vector<string> stopsID);

    virtual ~Line();

    LineID getLineID() { return lineID; }
    vector<string> getStopsID() {return stopsID;}
private:
    LineID lineID;
    vector<string> stopsID;
};

#endif /* FEUP_CAL_LINE_H_ */
