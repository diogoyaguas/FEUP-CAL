#ifndef FEUP_CAL_LINE_H_
#define FEUP_CAL_LINE_H_

#include <vector>
#include <string>

using namespace std;

struct LineID {
    int lineID;
    char type; // a - Bus, b - Metro, c - Train

    /**
     * @brief Overload of == operator to class Line
     * @param other - object of class LineID
     * @return bool
     */
    bool operator==(const LineID &other) const {
        return (lineID == other.lineID && type == other.type);
    }
};

class Line {
public:
    /**
     * @brief Default constructor of class Line
     */
    Line();
    /**
     * @brief Constructor of class Line
     * @param lineID
     * @param stopsID
     */
    Line(LineID lineID, std::vector<string> stopsID);
    /**
     * Default destructor of class Line
     */
    virtual ~Line();
    /**
     * @brief Getter of lineID
     * @return object of class LineID
     */
    LineID getLineID() { return lineID; }

private:
    LineID lineID;
    vector<string> stopsID;
};

#endif /* FEUP_CAL_LINE_H_ */
