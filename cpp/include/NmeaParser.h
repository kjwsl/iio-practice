#ifndef __NMEA_PARSER_H__
#define __NMEA_PARSER_H__

#include <memory>
#include <string>
#include "GnssListener.h"

using namespace std;
using namespace gnss::impl;

class NmeaParser {
    public:
        NmeaParser();
    
    private:
        unique_ptr<gnss::impl::GnssListener> mListener;
        string mBuffer;
        const GnssListener::GnssCallback mCallback {

        };

};

#endif // __NMEA_PARSER_H__
