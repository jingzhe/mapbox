//
// Created by Jingzhe Yu on 4.5.2024.
//

#ifndef MAPBOX_NAVIGATION_H
#define MAPBOX_NAVIGATION_H

#include <iostream>
#include <string>
#include <future>
#include "Model.h"

using namespace std;

class Navigation {
public:
    /**
     * Calculates the route object
     *
     * @points the start coordinates, waypoints or destination coordinates
     * @routeHandler callback function, after route is calculated, this callback will be called to inform client application
    */
    virtual void calculateRoute(const std::vector<Point>& points, const function<void (const Route&)>& routeHandler) = 0;

    /**
     * Starts the route simulation
     *
     * @route provided Route object
     * @guidanceHandler callback function, this callback will be called in every seconds to inform client the driving status
    */
    virtual void startSimulation(const Route& route, const function<void (Guidance)>& guidanceHandler) = 0;

    /**
     * Handle simulation command
     *
     * @simulationCommand provided Route object, pause: pause for 10 seconds, stop: stop the simulation
    */
    virtual void updateSimulation(SimulationCommand simulationCommand) = 0;

    /**
     * Return simulation status
     *
     * @return Simulation status: init, on_going or done
    */
    virtual SimulationStatus simulationStatus() = 0;

    virtual ~Navigation() = default;
};

#endif //MAPBOX_NAVIGATION_H
