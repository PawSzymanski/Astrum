#include "dirreader.h"

DirReader::DirReader()
{

}

std::vector<std::__cxx11::string> DirReader::operator()(std::__cxx11::string dir)
{
    std::vector<std::string> content;
    DIR * d;
    dirent * ent;

    d = opendir(dir.c_str());
    if(d != NULL)
    {
        while(true)
        {
            ent = readdir(d);
            if(ent == NULL) break;
            if(ent->d_name[0] == '.') continue;
            content.push_back(std::string(ent->d_name));
        }
        closedir(d);
    }
    else
        std::cout<<"nie mozna otworzyc dira"<<std::endl;

    return content;
}
