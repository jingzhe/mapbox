//
// Created by Jingzhe Yu on 3.5.2024.
//

#include "HttpService.h"
#include <iostream>
#include <cpr/cpr.h>
#include "Model.h"

using namespace std;

const string MAPBOX_URL = "https://api.mapbox.com/directions/v5/mapbox/driving/";

string HttpService::getRoute(const std::vector<Point>& points, const string& token) {
    cpr::Response r = cpr::Get(cpr::Url{MAPBOX_URL + Point::toUrlString(points)},
                               cpr::Parameters{{"alternatives", "true"},
                                               {"geometries", "geojson"},
                                               {"language", "en"},
                                               {"overview", "full"},
                                               {"annotations", "distance,maxspeed"},
                                               {"steps", "true"},
                                               {"access_token", token}});
    //cout << r.text << endl;
    return r.text;
}
