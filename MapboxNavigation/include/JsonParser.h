//
// Created by Jingzhe Yu on 4.5.2024.
//

#ifndef MAPBOX_JSONPARSER_H
#define MAPBOX_JSONPARSER_H

#include <cstring>
#include "Model.h"

using namespace std;

class JsonParser {

public:
    static std::shared_ptr<Route> parseDirectionResponse(const string& response);

};


#endif //MAPBOX_JSONPARSER_H
