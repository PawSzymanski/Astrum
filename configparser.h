/*
 *  configparser.h
 *
 *  Created: 2017-07-08
 *   Author: Patryk Wojtanowski
 */

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class ConfigParser
{
	bool eol, eos;
	unsigned int line, word;
	std::string section;
	std::string file_dir;
    std::map<std::string, std::vector<std::vector<std::string> > > dane;




public:
    ConfigParser();

    bool load(std::string dir);
    bool setSection(std::string s);
	bool EndOfLine();
	bool EndOfSection();

    float getFloat();

    std::string getString();

    std::vector< std::vector <std::string> > & getData();
    std::vector< std::string > getSections();

private:
    void next();
};

#endif // CONFIGPARSER_H
