#include "configdata.h"

ConfigData::ConfigData(const char *pc, int q, int t, int c){
  printcommand = pc;
  quality = q;
  typeface = t;
  cpi = c;
}
ConfigData::~ConfigData(){

}
char *ConfigData::getData() {
  sequence[0] = sequence[3] = sequence[6] = 27;
  sequence[1] = 'x'; sequence[4] = 'k'; sequence[8] = 0;
  sequence[2] = '0' + quality;
  sequence[5] = '0' + typeface;
  switch (cpi) {
  case 0:
    sequence[7] = 'P';
    break;
  case 1:
    sequence[7] = 'M';
    break;
  }
  return sequence;
}
const char *ConfigData::getCommand() {
  return printcommand;
}
