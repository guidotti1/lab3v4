#include <iostream>
#include <fstream>
#include <string>
#include <map>

// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "artBook.h"
#include "artEntry.h"

#define XML_USE_STL

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

ofstream logfile; 

int main() {
  Cgicc cgi;    // Ajax object
  char *cstr;

  artBook ab; // Phone Book SQL Interface Object
  vector<artEntry> abResults;
  
  // Create AJAX objects to recieve information from web page.
  form_iterator op = cgi.getElement("operation");
  string operation = **op;
  logfile.open("guidottiart.log",ios::out | ios::app);
  logfile << "Op:" << operation << endl;
  logfile.close();
  string output = "Error = "+operation+ " - Operation not support yet!";
  if (operation == "Find Last") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByLast(search);
    if (abResults.size() > 0)
    	{
	      output = "";
	      for (int i = 0; i<abResults.size(); i++) 
	      {
	      	  output += abResults.at(i).last + "^"
		  + abResults.at(i).first + "^"
		  + abResults.at(i).bornDied + "^"
		  + abResults.at(i).title + "^"
		  + abResults.at(i).date + "^"
		  + abResults.at(i).technique + "^"
		  + abResults.at(i).location + "^"
		  + abResults.at(i).url + "^"
		  + abResults.at(i).form + "^"
		  + abResults.at(i).type + "^"
		  + abResults.at(i).school + "^"
		  + abResults.at(i).timeframe + "^";
      	     }
    	}
  else 
    	{
		output = "No Match Found";
    	}
  }

  if (operation == "Find First") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByFirst(search);
    if (abResults.size() > 0)
    	{
	      //output = "success";
	      for (int i = 0; i<abResults.size(); i++) 
	      {
	      	  output +=  abResults.at(i).last + "^"
		  + abResults.at(i).first + "^"
		  + abResults.at(i).bornDied + "^"
		  + abResults.at(i).title + "^"
		  + abResults.at(i).date + "^"
		  + abResults.at(i).technique + "^"
		  + abResults.at(i).location + "^"
		  + abResults.at(i).url + "^"
		  + abResults.at(i).form + "^"
		  + abResults.at(i).type + "^"
		  + abResults.at(i).school + "^"
		  + abResults.at(i).timeframe + "^";
      	     }
    }
  else 
    {
    	output = "No Match Found";
    }
  }
	
  if (operation == "Find Title") 
  {
    form_iterator searchString = cgi.getElement("find");
    string search = **searchString;
    
    abResults = ab.findByTitle(search);
    if (abResults.size() > 0)
    	{
	      //output = "success";
	      for (int i = 0; i<abResults.size(); i++) 
	      {
	      	  output += abResults.at(i).last + "^"
		  + abResults.at(i).first + "^"
		  + abResults.at(i).bornDied + "^"
		  + abResults.at(i).title + "^"
		  + abResults.at(i).date + "^"
		  + abResults.at(i).technique + "^"
		  + abResults.at(i).location + "^"
		  + abResults.at(i).url + "^"
		  + abResults.at(i).form + "^"
		  + abResults.at(i).type + "^"
		  + abResults.at(i).school + "^"
		  + abResults.at(i).timeframe + "^";
      	     }
    }
  else 
    {
      	output = "No Match Found";
    }
  }
	
	/*
  if(operation=="Add Entry"){
    form_iterator afnameString = cgi.getElement("afname");
    form_iterator alnameString = cgi.getElement("alname");
    form_iterator addphoneString = cgi.getElement("aphone");
    form_iterator addtypeString = cgi.getElement("atype");

    string addfname=**afnameString;
    string addlname=**alnameString;
    string addphone=**addphoneString;
    string addtype=**addtypeString;

    pb.addEntry(addfname,addlname,addphone,addtype);
    output="success";
  }
  
  if(operation=="delete"){
    form_iterator idtodeleteString = cgi.getElement("deleteid");
    string iddelete=**idtodeleteString;

    pb.deleteEntry(iddelete);
    output="success";
  }
  if(operation=="edit"){
    form_iterator idtoeditString = cgi.getElement("editid");
    string idedit=**idtoeditString;

    form_iterator editfnameString = cgi.getElement("editfname");
    form_iterator editlnameString = cgi.getElement("editlname");
    form_iterator editphoneString = cgi.getElement("editphone");
    form_iterator edittypeString = cgi.getElement("edittype");

    string editfname=**editfnameString;
    string editlname=**editlnameString;
    string editphone=**editphoneString;
    string edittype=**edittypeString;


    pb.editEntry(idedit,editfname,editlname,editphone,edittype);
    output="success";
  }
  */
  /* send back the results */
  cout << "Content-Type: text/plain\n\n";

  cout << output << endl;
  
  
  return 0;
}

