#include "include/NmeaParser.h"

NmeaParser::NmeaParser() : listener(make_unique<GnssListener>("/dev/ttyAMA0", []())) {
    listener = make_unique<GnssListener>();
}
