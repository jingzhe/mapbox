//
// Created by Jingzhe Yu on 4.5.2024.
//

#include "NavigationImpl.h"
#include <thread>

using namespace std::chrono_literals;

NavigationImpl::NavigationImpl() {
    routeCalculator = std::make_unique<RouteCalculator>();
    routeSimulation = std::make_unique<RouteSimulation>();
}

void NavigationImpl::calculateRoute(const std::vector<Point>& points, const function<void (const Route&)>& routeHandler) {
    routeCalculator->calculateRoute(points, routeHandler);
}

void NavigationImpl::startSimulation(const Route& route, const function<void (const Guidance)>& guidanceHandler) {
    routeSimulation->startSimulation(route, guidanceHandler);
}

void NavigationImpl::updateSimulation(SimulationCommand simulationCommand) {
    routeSimulation->updateSimulation(simulationCommand);
}

SimulationStatus NavigationImpl::simulationStatus() {
    return routeSimulation->simulationStatus();
}

