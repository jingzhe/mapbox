//
// Created by Jingzhe Yu on 3.5.2024.
//

#ifndef MAPBOXTEST_HTTPSERVICE_H
#define MAPBOXTEST_HTTPSERVICE_H

#include <string>
#include "Model.h"

class HttpService {

public:
    static std::string getRoute(const std::vector<Point>& points);

};

#endif //MAPBOXTEST_HTTPSERVICE_H
