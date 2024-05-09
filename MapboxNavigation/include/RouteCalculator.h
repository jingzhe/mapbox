//
// Created by Jingzhe Yu on 5.5.2024.
//

#ifndef MAPBOX_ROUTECALCULATOR_H
#define MAPBOX_ROUTECALCULATOR_H

#include <iostream>
#include <string>
#include <thread>
#include "Model.h"

using namespace std;

class RouteCalculator {
public:
    RouteCalculator() = default;
    ~RouteCalculator();
    void calculateRoute(const std::vector<Point>& points, const string& token, const function<void (const Route&)>& routeHandler);

private:
    static void doCalculateRoute(const std::vector<Point>& points, const string& token, const function<void (const Route&)>& routeHandler);

    std::unique_ptr<std::thread> thread;
};


#endif //MAPBOX_ROUTECALCULATOR_H
