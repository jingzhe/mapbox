//
// Created by Jingzhe Yu on 3.5.2024.
//

#ifndef MAPBOX_HTTPSERVICE_H
#define MAPBOX_HTTPSERVICE_H

#include <string>
#include "Model.h"

class HttpService {

public:
    static std::string getRoute(const std::vector<Point>& points, const std::string& token);

};

#endif //MAPBOX_HTTPSERVICE_H
