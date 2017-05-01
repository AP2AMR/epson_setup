#ifndef CONFIGDATA_H
#define CONFIGDATA_H
#include <string>

class ConfigData {
public: 
    ConfigData(const std::string pc, int q, int t, int c);
    ~ConfigData();
    std::string getData();
    const std::string getCommand();

private:
    const std::string printcommand;
    int quality, typeface, cpi;
    std::string sequence;
};

#endif
