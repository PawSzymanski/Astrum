/*
 *  configcreator.h
 *
 *  Created: 2017-07-08
 *   Author: Patryk Wojtanowski
 */

#ifndef CONFIGCREATOR_H
#define CONFIGCREATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class ConfigCreator
{
	std::string dir;
    std::map<std::string, std::vector<std::vector<std::string> > > dane;



public:
    ConfigCreator();
    void setDir(std::string dir);
    void addSection(std::string section, std::vector<std::vector<std::string> > &data);
    void create();
};

#endif // CONFIGCREATOR_H
