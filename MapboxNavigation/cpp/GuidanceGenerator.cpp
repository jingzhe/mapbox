//
// Created by Jingzhe Yu on 6.5.2024.
//
#include <cmath>
#include "GuidanceGenerator.h"


double calculateInterpolationLat(const Point& p1, const Point& p2, double lon) {
    auto lat = (p1.lat * (p2.lon - lon) + p2.lat * (lon - p1.lon)) / (p2.lon - p1.lon);
    return lat;
}

std::vector<Guidance> GuidanceGenerator::generateGuidance(const Route& route) {
    std::vector<Guidance> vec;

    for (const auto& leg : route.legs) {
        int maxSpeedIndex = 0;
        for (const auto &edge: leg.edges) {
            for (int i = 0; i < edge.coordinates.size() - 1; i++) {
                const auto &point1 = edge.coordinates[i];
                const auto &point2 = edge.coordinates[i + 1];
                auto distance = leg.distances[maxSpeedIndex];
                auto maxSpeed = leg.maxSpeeds[maxSpeedIndex];
                auto speedKph = maxSpeed == 0 ? 40 : maxSpeed;
                auto speed = speedKph / 3.6;
                auto interpolation = floor(distance / speed) - 1; // interpolation point number
                auto lonStep = (point2.lon - point1.lon) / (interpolation + 1);
                auto maneuver = edge.coordinates.size() - i <= 4 ? edge.maneuver : Maneuver("", "Follow the route");
                auto speedLimit = maxSpeed == 0 ? "unknown" : std::to_string(maxSpeed);
                auto guidance1 = Guidance(point1, speedKph, speedLimit, maneuver, edge.street);
                vec.push_back(guidance1);
                for (int k = 1; k <= interpolation; k++) {
                    double lon = point1.lon + k * lonStep;
                    double lat = calculateInterpolationLat(point1, point2, lon);
                    auto guidance = Guidance(Point(lon, lat), speedKph, speedLimit, maneuver, edge.street);
                    vec.push_back(guidance);
                }
                maxSpeedIndex++;
            }
        }
    }
    return vec;
}