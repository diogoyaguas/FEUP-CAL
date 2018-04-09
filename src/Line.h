#ifndef FEUP_CAL_LINE_H_
#define FEUP_CAL_LINE_H_

#include <vector>
#include <string>

using namespace std;

struct LineID {
    int lineID;
    char type; // a - Bus, b - Metro, c - Train

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

private:
    LineID lineID;
    vector<string> stopsID;
};

#endif /* FEUP_CAL_LINE_H_ */
