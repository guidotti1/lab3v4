
#include "artEntry.h"

artEntry::artEntry() {
    //empty constructor to avoid initialization errors
	last="";
	first="";
	bornDied="";
	title="";
	date="";
	technique="";
	location="";
	url="";
	form="";
	type="";
	school="";
	timeframe="";
	ARTID="";
}

artEntry::artEntry(string name, string bornDiedInit, string titleInit, string dateInit, string techniqueInit, string locationInit, string urlInit, string formInit, string typeInit, string schoolInit, string timeframeInit, string ARTIDInit) 
{
    stringstream nameStream(name);
    getline(nameStream, last, ',');
    getline(nameStream, first);
    bornDied = bornDiedInit;
    title = titleInit;
    date = dateInit;
    technique = techniqueInit;
    location = locationInit;
    url = urlInit;
    form = formInit;
    type = typeInit;
    school = schoolInit;
    timeframe = timeframeInit;
    ARTID = ARTIDInit;
}


