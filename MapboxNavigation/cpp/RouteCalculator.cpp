//
// Created by Jingzhe Yu on 5.5.2024.
//

#include "HttpService.h"
#include "JsonParser.h"
#include "RouteCalculator.h"

void RouteCalculator::calculateRoute(const std::vector<Point>& points, const string& token, const function<void (const Route& route)>& routeHandler) {
    thread = std::make_unique<std::thread>(doCalculateRoute, std::ref(points), std::ref(token), std::ref(routeHandler));
}

void RouteCalculator::doCalculateRoute(const std::vector<Point>& points, const string& token, const function<void (const Route& route)>& routeHandler) {
    if (points.size() < 2) {
        auto route = std::make_shared<Route>(Route {});
        route->status = "Bad_Input";
        routeHandler(*route);
        return;
    }
    auto res = HttpService::getRoute(points, token);
    auto route = JsonParser::parseDirectionResponse(res);

    routeHandler(*route);
}

RouteCalculator::~RouteCalculator() {
    if (thread->joinable()) {
        thread->join();
    }
}
