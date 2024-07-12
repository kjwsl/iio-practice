# NMEA Parser


```plantuml
class NmeaParser {

}

struct NmeaData {
    MessageType message_type
    TalkerId talker_id
    int checksum

    virtual NmeaData* parse(const string msg)
    virtual NmeaData* parse_msg(NmeaData*) = 0


}

struct GgaData extends NmeaData {

}


```
