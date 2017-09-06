#ifndef SCF_PARSER_HPP
#define SCF_PARSER_HPP

#include "../raster/Frag.hpp"

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <stdio.h>

using std::string;
using std::vector;
using std::map;
using std::getline;
using std::ifstream;
using std::istringstream;
//using std::sscanf_s;

typedef map<string, string> MapType;
void replaceAll(string& subject, const string& search, const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

void substituteConst(const MapType& constMap, string& outString) {
	for (auto iter = constMap.begin(); iter != constMap.end(); iter++) {
		replaceAll(outString, iter->first, iter->second);
	}
}

void scfParse(const string& path, vector<FVertex>& outVertexData) {
	MapType constMap;
	constMap["l"] = "0.2";
	constMap["m"] = "128";
	vector<FVertex> tmpVertexData;
	vector<TexCoord> tmpTexData;

	ifstream infile(path);
	string line;
	while (getline(infile, line)) {
		if(line == "")
			continue;

		char c = line[0];
		switch (c) {
		case '#':
			// just comment
			break;
		case '[': {
			substituteConst(constMap, line);

			char name;
			sscanf_s(line.c_str(), "[%c]", &name);

			if (name == 'v') {
				float x, y, z;
				int b, g, r;
				sscanf_s(line.c_str(), "[v] %f %f %f | %d %d %d", &x, &y, &z, &b, &g, &r);

				BGRA* bgra = new BGRA(b, g, r);
				Info* info = new Info(bgra);
				tmpVertexData.push_back({ info, x, y, z });
			}
			else if (name == 't') {
				float u, v;
				sscanf_s(line.c_str(), "[t] %f %f", &u, &v);
				tmpTexData.push_back(TexCoord(u, v));
			}
			else if (name == 'f') {
				int i1, i2, i3;
				int t1, t2, t3;

				sscanf_s(line.c_str(), "[f] v%d/t%d v%d/t%d v%d/t%d", &i1, &t1, &i2, &t2, &i3, &t3);
				tmpVertexData[i1].tex = tmpTexData[t1];
				tmpVertexData[i2].tex = tmpTexData[t2];
				tmpVertexData[i3].tex = tmpTexData[t3];

				outVertexData.push_back(tmpVertexData[i1]);
				outVertexData.push_back(tmpVertexData[i2]);
				outVertexData.push_back(tmpVertexData[i3]);
			}
			break;
		}
		case ':': {
			// TODO: how to read string as input

			////char cstName[1];
			////char cstVal[3];
			//char* cstName;
			////char* cstVal;
			//float cstVal;
			//cstName = (char*)malloc(10 * sizeof(char));
			////cstVal = (char*)malloc(10 * sizeof(char));
			//sscanf_s(line.c_str(), ": %s = %f", cstName, &cstVal);
			//constMap[cstName] = cstVal;
			break;
		}
		default:
			break;
		}
	}
}
#endif