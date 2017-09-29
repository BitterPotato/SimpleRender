//
// Created by WJ Yang on 2017/9/23.
//

#ifndef SIMPLERENDER_PARSER_HPP
#define SIMPLERENDER_PARSER_HPP

#include "common/setup.hpp"
#include "mesh/Container.hpp"

class FVertex;

#include <map>

using std::map;

typedef map<string, string> MapType;

class Parser {
public:
    MY_UTIL_DECL void scfParse(const string& path, FVertexContainer& outVertexData);
private:
    MY_UTIL_DECL void replaceAll(string& subject, const string& search, const string& replace);
    MY_UTIL_DECL void substituteConst(const MapType& constMap, string& outString);
};



#endif //SIMPLERENDER_PARSER_HPP
