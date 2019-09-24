#include "Point.h"
#include "Configuration.h"

struct CalibrationData {
    bool calibrationExists;
    Point data[CALIBRATION_POINTS];
};