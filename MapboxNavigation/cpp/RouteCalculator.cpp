//
// Created by Jingzhe Yu on 5.5.2024.
//

#include "HttpService.h"
#include "JsonParser.h"
#include "RouteCalculator.h"

void RouteCalculator::calculateRoute(const std::vector<Point>& points, const function<void (const Route& route)>& routeHandler) {
    thread = std::make_unique<std::thread>(doCalculateRoute, std::ref(points), std::ref(routeHandler));
}

void RouteCalculator::doCalculateRoute(const std::vector<Point>& points, const function<void (const Route& route)>& routeHandler) {
    auto res = HttpService::getRoute(points);
    auto route = JsonParser::parseDirectionResponse(res);

    routeHandler(*route);
}

RouteCalculator::~RouteCalculator() {
    if (thread->joinable()) {
        thread->join();
    }
}
