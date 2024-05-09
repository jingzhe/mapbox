//
// Created by Jingzhe Yu on 4.5.2024.
//

#include "JsonParser.h"
#include <memory>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;


std::shared_ptr<Route> JsonParser::parseDirectionResponse(const string& response) {

    auto route = std::make_shared<Route>(Route {});
    try {
        json data = json::parse(response);
        route->status = data.at("code");
        if (route->status != "Ok") {
            throw std::invalid_argument("Wrong response from Mapbox direction API");
        }
        auto routeJson = data.at("routes").front();

        route->distance = routeJson.at("distance");
        route->duration = routeJson.at("duration");

        auto legsJson = routeJson.at("legs");

        for (const auto &legJson: legsJson) {
            auto leg = Leg();
            auto annotationJson = legJson.at("annotation");
            auto maxspeedsJson = annotationJson.at("maxspeed");
            for (const auto &maxspeedJson: maxspeedsJson) {
                int speed = 0;
                try {
                    speed = maxspeedJson.at("speed");
                } catch (const json::exception &e) {
                }
                leg.maxSpeeds.push_back(speed);
            }
            auto distancesJson = annotationJson.at("distance");
            for (const auto &distance: distancesJson) {
                leg.distances.push_back(distance);
            }

            auto stepsJson = legJson.at("steps");
            for (const auto &stepJson: stepsJson) {
                auto edge = Edge();
                edge.duration = stepJson.at("duration");
                edge.distance = stepJson.at("distance");
                edge.street = stepJson.at("name");
                auto maneuverJson = stepJson.at("maneuver");
                edge.maneuver.type = maneuverJson.at("type");
                edge.maneuver.instruction = maneuverJson.at("instruction");
                auto coordinates = stepJson.at("geometry").at("coordinates");
                for (const auto &point: coordinates) {
                    edge.coordinates.emplace_back(point.front(), point.back());
                }
                leg.edges.emplace_back(edge);
            }
            // Mapbox return maneuver for previous edge, which is not helpful. It should be for the next edge
            // So I adjust maneuver for convenience
            for (int i = 0; i < leg.edges.size() - 1; i++) {
                leg.edges[i].maneuver = leg.edges[i + 1].maneuver;
            }
            route->legs.emplace_back(leg);
        }
    } catch (const std::exception& ex) {
        cout << "Parsing Mapbox response failed:" << ex.what() << endl;
        route->status = "Bad_Http_Response";
    }

    return route;
}
