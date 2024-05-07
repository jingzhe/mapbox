//
// Created by Jingzhe Yu on 4.5.2024.
//

#ifndef MAPBOXTEST_NAVIGATION_H
#define MAPBOXTEST_NAVIGATION_H

#include <iostream>
#include <string>
#include <future>
#include "Model.h"

using namespace std;

class Navigation {
public:
    virtual void calculateRoute(const std::vector<Point>& points, const function<void (const Route&)>& routeHandler) = 0;
    virtual void startSimulation(const Route& route, const function<void (Guidance)>& guidanceHandler) = 0;
    virtual bool simulationReady() = 0;

    virtual ~Navigation() = default;
};

#endif //MAPBOXTEST_NAVIGATION_H
