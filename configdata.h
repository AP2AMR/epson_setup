#ifndef CONFIGDATA_H
#define CONFIGDATA_H

class ConfigData {
public: 
  ConfigData(const char *c, int q, int t, int ci);
  ~ConfigData();
  char *getData();
  const char *getCommand();
private:
  const char *printcommand;
  int quality, typeface, cpi;
  char sequence[8];
};

#endif
