//
// Created by Jingzhe Yu on 4.5.2024.
//

#ifndef MAPBOXTEST_NAVIGATIONIMPL_H
#define MAPBOXTEST_NAVIGATIONIMPL_H

#include <iostream>
#include <string>
#include "Model.h"
#include "RouteCalculator.h"
#include "RouteSimulation.h"
#include "Navigation.h"

using namespace std;

class NavigationImpl: public Navigation{

public:
    NavigationImpl();

    void calculateRoute(const std::vector<Point>& points, const function<void (const Route&)>& routeHandler) override;
    void startSimulation(const Route& route, const function<void (const Guidance)>& guidanceHandler) override;
    bool simulationReady() override;

private:
    std::unique_ptr<RouteCalculator> routeCalculator;
    std::unique_ptr<RouteSimulation> routeSimulation;
};


#endif //MAPBOXTEST_NAVIGATIONIMPL_H
