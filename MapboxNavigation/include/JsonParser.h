//
// Created by Jingzhe Yu on 4.5.2024.
//

#ifndef MAPBOXTEST_JSONPARSER_H
#define MAPBOXTEST_JSONPARSER_H

#include <cstring>
#include "Model.h"

using namespace std;

class JsonParser {

public:
    static std::shared_ptr<Route> parseDirectionResponse(const string& response);

};


#endif //MAPBOXTEST_JSONPARSER_H
