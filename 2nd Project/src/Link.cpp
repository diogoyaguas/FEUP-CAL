#include "Station.h"

Link::Link() = default;

Link::~Link() = default;

Link::Link(LineID lineID, Station *dest) : dest(dest) {
    this->lineID = lineID;
    this->travelSpeed = 0;
    //TODO: calculate travelTime;
}

Link::Link(LineID lineID, Station *dest, double travelSpeed) : dest(dest), travelSpeed(travelSpeed) {
    this->lineID = lineID;
}

Link::Link(LineID lineID, int idSource, int idDest) {
	this->lineID = lineID;
	this->idSource = idSource;
	this->idDest = idDest;

}

Station *Link::getDest() {
    return dest;
}

double Link::getTravelSpeed() {
    return travelSpeed;
}

double Link::getWeight() {
    return weight;
}

LineID Link::getLineID() {
    return lineID;
}

int Link::getIdSource()
{
	return idSource;
}

int Link::getIdDest()
{
	return idDest;
}
