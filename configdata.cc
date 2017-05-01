#include "configdata.h"

ConfigData::ConfigData(const std::string pc, int q, int t, int c) :
    printcommand(pc), 
    quality(q), 
    typeface(t), 
    cpi(c),
    sequence("")
{

}

ConfigData::~ConfigData(){

}

std::string ConfigData::getData() {
    const char escapeChar = 27;
    sequence += escapeChar;
    sequence += 'x';  
    sequence += '0' + quality;

    sequence += escapeChar;
    sequence += 'k';
    sequence += '0' + typeface;

    sequence += escapeChar;
    sequence += cpi ? 'M' : 'P';

    return sequence;
}

const std::string ConfigData::getCommand() {
    return printcommand;
}
