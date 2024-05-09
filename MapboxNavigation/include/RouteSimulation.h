//
// Created by Jingzhe Yu on 5.5.2024.
//

#ifndef MAPBOX_ROUTESIMULATION_H
#define MAPBOX_ROUTESIMULATION_H

#include <mutex>
#include <queue>
#include <future>
#include "Model.h"

using namespace std;

class RouteSimulation {

public:
    void startSimulation(const Route& route, const function<void (const Guidance)>& guidanceHandler);
    SimulationStatus simulationStatus() const;
    void updateSimulation(SimulationCommand simulationCommand);
    ~RouteSimulation();

private:
    void doStartSimulation(const Route& route);
    void consumer(const function<void (const Guidance)>& guidanceHandler);

    std::unique_ptr<std::thread> producerThread;
    std::unique_ptr<std::thread> consumerThread;
    std::mutex lockQueue;
    std::condition_variable queueCheck;
    std::queue<Guidance> guidanceBuffer;
    std::atomic<SimulationStatus> status = { SimulationStatus::init };
    std::atomic<SimulationCommand> command = { SimulationCommand::none };

};


#endif //MAPBOX_ROUTESIMULATION_H
