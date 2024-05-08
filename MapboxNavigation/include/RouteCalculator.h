//
// Created by Jingzhe Yu on 5.5.2024.
//

#ifndef MAPBOXTEST_ROUTECALCULATOR_H
#define MAPBOXTEST_ROUTECALCULATOR_H

#include <iostream>
#include <string>
#include <thread>
#include "Model.h"

using namespace std;

class RouteCalculator {
public:
    RouteCalculator() = default;
    ~RouteCalculator();
    void calculateRoute(const std::vector<Point>& points, const function<void (const Route&)>& routeHandler);

private:
    static void doCalculateRoute(const std::vector<Point>& points, const function<void (const Route&)>& routeHandler);

    std::unique_ptr<std::thread> thread;
};


#endif //MAPBOXTEST_ROUTECALCULATOR_H
