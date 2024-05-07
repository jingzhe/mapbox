//
// Created by Jingzhe Yu on 6.5.2024.
//

#ifndef MAPBOXTEST_GUIDANCEGENERATOR_H
#define MAPBOXTEST_GUIDANCEGENERATOR_H

#include <vector>
#include "Model.h"

using namespace std;

class GuidanceGenerator {
public:
    static std::vector<Guidance> generateGuidance(const Route& route);
};


#endif //MAPBOXTEST_GUIDANCEGENERATOR_H
