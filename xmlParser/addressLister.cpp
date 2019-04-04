/*
 * addressLister.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: christopherdavis
 */
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Contacts
{

	string name;
	string street;
	string city;
	string state;
	int zipCode;
};

/*
 * Description: opens the xml file to be read
 * Preconditions: a reference to a Contacts structure object
 * Postconditions: a string that is the address of the structure
*/
string getAddress(Contacts &);

/*
 * Description: opens the xml file to be read
 * Preconditions: a string that the user will input, which is the name of the xml file
 * Postconditions: the xml File
*/
void get_xmlFile(ifstream &);

/*
 * Description: associates a given property or tagname with a passed Contacts object
 * Preconditions:
 * 		(o) a string to specify the tag sent
 * 		(o) Contacts structure that associates the following tags with this structure's properties
 * 		(o) the ifstream from which tags will be recognized
 * 		(o) vector<Contacts> a reference to the root container in the event that the tag name sent is a contact tag
 * 		so that the xml_parser substask that creates a new Contacts object can be created
 * Postconditions: n/a
*/
void xml_parserConditions(string currTag, Contacts &ObjAssoc, ifstream &xmlFile, vector<Contacts> &xmlRoot);

/*
 * Description: associates a given property or tagname with the xml root contaier
 * Preconditions:
 * 		(o) a string to specify the tag sent
 * 		(o) vector<Contacts> which associates objects with the xml Root container
 * 		(o) the ifstream from which tags will be recognized
 * Postconditions: n/a
*/
void xml_parserConditions(string currTag, vector<Contacts> &ObjAssoc, ifstream &xmlFile);

/*
 * Description: a loop that associates subsequently recognized tags the xml Root
 * Preconditions:
 * 		(o) vector<Contacts> used to trigger the xml_parser overloaded subtask that links objects with the xml Root
 * 		(o) the ifstream from which tags will be recognized
 * Postconditions: n/a
*/
void fill_structure(vector<Contacts> &ObjAssoc, ifstream &xmlFile);

/*
 * Description: a loop that associates subsequently recognized tags with a given Contacts Object
 * Preconditions:
 * 		(o) Contacts structure object used to trigger the xml_parser overloaded subtask that links objects with Contacts Objects
 * 		(o) the ifstream from which tags will be recognized
 * 		(o) vector <Contacts> which is a reference to the xmlRoot in the event that the tag found is in fact a contacts tag
 * 			--used to ensure that a contact is created
 * Postconditions: n/a
*/
void fill_structure(Contacts &ObjAssoc, ifstream &xmlFile, vector<Contacts> &xmlRootContingent);

/*
 * Description: display all contacts in a given city
 * Preconditions:
 * 		(o) a string to specify which city
 * 		(o) Contacts array to collect data from
 * Postconditions: n/a
*/
void display_city(vector<Contacts> &);

/*
 * Description: display all contacts in a given zip code range
 * Preconditions:
 * 		(o) a string to specify which city
 * 		(o) Contacts array to collect data from
 * Postconditions: n/a
*/
void display_ZipRange(vector<Contacts> &);

int main()
{
	ifstream xmlFile;
	vector<Contacts>  addressBook;

	//open XML file
	get_xmlFile(xmlFile);

	//start off XML file
	fill_structure (addressBook, xmlFile);

	//display people in Palmdale
	display_city(addressBook);

	//display people in ZIP Code range: 90214-90210
	display_ZipRange(addressBook);

	//close XML document
	xmlFile.close ();
	return 0;


}

void get_xmlFile(ifstream &xmlHolder)
{
	string xmlPath;
	do
	{
		cout << "Please enter the name of the XML file containing the addresses \n";
		cin >> xmlPath;
		size_t foundXMLExtension = xmlPath.find (".xml");
		if (foundXMLExtension == string::npos)
		{
			xmlPath += ".xml";
		}
		xmlHolder.open (xmlPath, ios::in);
	}while(xmlHolder.fail());
	cout << "xmlFile Retrieved \n";
	return;
}

void fill_structure(vector<Contacts> &ObjAssoc, ifstream &xmlFile)
{
	cout << "Filling root \n";
	string tagName;
	char data;
	while (xmlFile >> data)
	{
		if (data == '<')
		{
			xmlFile.get(data);
			//make sure that this isn't an end tag
			if (data != '/')
			{
				xmlFile.putback(data);
					//getline until ">"
				getline(xmlFile, tagName, '>');
				xml_parserConditions(tagName, ObjAssoc, xmlFile);
			}
		}

	}
	return;

}

void fill_structure(Contacts &ObjAssoc, ifstream &xmlFile, vector<Contacts> &xmlRootContingent)
{
	cout << "Filling a Contact \n";
	string tagName;
	char data;
	while (xmlFile >> data)
	{
		if (data == '<')
		{
			xmlFile.get(data);
			//make sure that this isn't an end tag
			if (data != '/')
			{
				xmlFile.putback(data);
					//getline until ">"
				getline(xmlFile, tagName, '>');
				xml_parserConditions(tagName, ObjAssoc, xmlFile, xmlRootContingent);
			}
		}

	}
	return;
}

void xml_parserConditions(string currTag, vector<Contacts> &ObjAssoc, ifstream &xmlFile)
{
	if ("contact" == currTag)
	{
		Contacts c;
		ObjAssoc.push_back(c);
		cout << "contact Added \n";
		fill_structure(ObjAssoc.back(), xmlFile, ObjAssoc);
	}
	return;
}

void xml_parserConditions(string currTag, Contacts &ObjAssoc, ifstream &xmlFile, vector<Contacts> &xmlRoot)
{
	if ("contact" == currTag)
	{
		xml_parserConditions (currTag, xmlRoot, xmlFile);
		return;
	}
	else
	{
		string value;
		getline(xmlFile, value, '<');

		if ("name" == currTag)
		{
			//cout << "put in " << value << "\n";
			ObjAssoc.name = value;
			return;
		}
		else if ("street" == currTag)
		{
			//cout << "put in " << value << " for " << ObjAssoc.name << "\n";
			ObjAssoc.street = value;
			return;
		}
		else if ("city" == currTag)
		{
			//cout << "put in " << value << " for " << ObjAssoc.name << "\n";
			ObjAssoc.city = value;
			return;
		}
		else if ("state" == currTag)
		{
			ObjAssoc.state = value;
			return;
		}
		else if ("zip" == currTag)
		{
			//cout << "put in " << value << " for " << ObjAssoc.name << "\n";
			ObjAssoc.zipCode = stoi(value);
			return;
		}
	}

	return;
}

void display_city(vector<Contacts> & addressBook)
{
	string cityName;
	cout << endl;
	cout << endl;
	cout << "please enter the name of the city which you would like to \n"
			"display the names of the inhabitants off \n";
	cin >> cityName;
	cout << endl;
	cout << endl;
	int size (0);
	size = addressBook.size();
	int counter(1);

	for (int i = 0; i < size; i ++)
	{
		if (cityName == addressBook[i].city)
		{
			cout << "Name " << (counter) << ": ";
			cout << addressBook[i].name << "\n";
			cout << "Address " << (counter) << ": ";
			cout << getAddress(addressBook[i]) <<"\n";
			if (i < (size-1))
			{
				cout << "=======================================";
				cout << "\n";
			}
			counter ++;
		}
	}
	cout << "\n";

	return;
}

void display_ZipRange(vector<Contacts> &addressBook)
{
	int upper, lower;
	cout << endl;
	cout << endl;
	cout << "specify upper boundary for ZIP code \n";
	cin >> upper;
	cout << "specify lower boundary for ZIP code \n";
	cin >> lower;
	cout << endl;
	cout << endl;

	int size (0);
	size = addressBook.size();
	int counter(1);

	for (int i = 0; i < size; i ++)
	{
		if (upper > addressBook[i].zipCode && lower < addressBook[i].zipCode)
		{
			cout << "Name " << (counter) << ": ";
			cout << addressBook[i].name << "\n";
			cout << "Address " << (counter) << ": ";
			cout << getAddress(addressBook[i]) << "\n";
			if (i < (size-1))
			{
				cout << "=======================================";
				cout << "\n";
			}
			counter ++;
		}
	}
	return;
}
string getAddress(Contacts &person)
{
	string address;
	address += person.street;
	address += ", ";
	address += person.city;
	address += ", ";
	address += person.state;
	return address;

}
