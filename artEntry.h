#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#ifndef ARTENTRY_H
#define ARTENTRY_H

class artEntry {
public:
     artEntry();
     artEntry(string name, string bornDiedInit, string titleInit, string dateInit, string techniqueInit, string locationInit, string urlInit, string formInit, string typeInit, string schoolInit, string timeframeInit, string ARTIDInit);
     string last;
     string first;
     string bornDied;
     string title;
     string date;
     string technique;
     string location;
     string url;
     string form;
     string type;
     string school;
     string timeframe;
     string ARTID;

private:

};

#endif /* ARTENTRY_H */

