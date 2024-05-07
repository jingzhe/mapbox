//
// Created by Jingzhe Yu on 3.5.2024.
//

#ifndef MAPBOXTEST_MODEL_H
#define MAPBOXTEST_MODEL_H

#include <format>
#include <utility>

struct Point {
    double lon;
    double lat;

    Point(double x, double y): lon(x), lat(y) {
    }

    [[nodiscard]] std::string urlStr() const {
        return std::format("{},{}", lon, lat);
    }

    static std::string toUrlString(const std::vector<Point>& points) {
        auto str = std::reduce(points.begin() + 1, points.end(), points[0].urlStr(),
                               [] (const std::string& acc, Point point) {
            return acc + ';' + point.urlStr();
        });
        return str;
    }
};

struct Maneuver {
    std::string type;
    std::string instruction;

    Maneuver() = default;
    Maneuver(std::string  type, std::string  instruction): type(std::move(type)), instruction(std::move(instruction)) {

    };
};

struct Edge {
    double distance;
    double duration;
    std::string street;
    std::vector<Point> coordinates;
    Maneuver maneuver;
};

struct Leg {
    std::vector<Edge> edges;
    double distance;
    double duration;
    std::vector<int> maxSpeeds;
    std::vector<float> distances;
};

struct Route {
    std::vector<Leg> legs;
    double distance;
    double duration;
    std::string status;
};

struct Guidance {
    Point point;
    double speed;
    double speedLimit;
    Maneuver maneuver;
    std::string status;

    Guidance(const Point& point, double speed, double speedLimit, Maneuver maneuver, std::string status)
        : point(point), speed(speed), speedLimit(speedLimit), maneuver(std::move(maneuver)), status(std::move(status)) {
    }
};

#endif //MAPBOXTEST_MODEL_H
