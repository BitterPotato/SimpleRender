//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_PARSER_HPP
#define SIMPLERENDER_PARSER_HPP

#include "common/FVertex.hpp"

#include <map>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <stdio.h>

using std::map;
using std::getline;
using std::ifstream;
using std::istringstream;
//using std::sscanf;

typedef map<string, string> MapType;

class Parser {
public:
    MY_UTIL_DECL void scfParse(const string& path, vector<FVertex>& outVertexData);
private:
    MY_UTIL_DECL void replaceAll(string& subject, const string& search, const string& replace);
    MY_UTIL_DECL void substituteConst(const MapType& constMap, string& outString);
};



#endif //SIMPLERENDER_PARSER_HPP
