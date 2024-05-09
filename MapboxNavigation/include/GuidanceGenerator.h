//
// Created by Jingzhe Yu on 6.5.2024.
//

#ifndef MAPBOX_GUIDANCEGENERATOR_H
#define MAPBOX_GUIDANCEGENERATOR_H

#include <vector>
#include "Model.h"

using namespace std;

class GuidanceGenerator {
public:
    static std::vector<Guidance> generateGuidance(const Route& route);
};


#endif //MAPBOX_GUIDANCEGENERATOR_H
