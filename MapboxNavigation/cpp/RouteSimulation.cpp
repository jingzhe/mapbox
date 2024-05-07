//
// Created by Jingzhe Yu on 5.5.2024.
//
#include <iostream>
#include "RouteSimulation.h"
#include "GuidanceGenerator.h"

void RouteSimulation::startSimulation(const Route& route, const function<void (const Guidance)>& guidanceHandler) {
    producerThread = std::make_unique<std::thread>(&RouteSimulation::doStartSimulation, this, std::ref(route));
    consumerThread = std::make_unique<std::thread>(&RouteSimulation::consumer, this, std::ref(guidanceHandler));
}

void RouteSimulation::doStartSimulation(const Route& route) {
    auto guidanceVector = GuidanceGenerator::generateGuidance(route);
    for (const auto& guidance : guidanceVector) {
        std::this_thread::sleep_for(1s);
        {
            std::unique_lock<std::mutex> locker(lockQueue);
            guidanceBuffer.push(guidance);
        }

        // notify consumer
        queueCheck.notify_one();
    }
    reachDestination = true;
}

void RouteSimulation::consumer(const function<void (const Guidance)>& guidanceHandler) {
    while (!reachDestination) {
        std::unique_lock<std::mutex> locker(lockQueue);
        queueCheck.wait_for(locker, 10ms, [&]() {return guidanceBuffer.empty();});
        while (!guidanceBuffer.empty()) {
            auto guidance = guidanceBuffer.front();
            guidanceHandler(guidance);
            guidanceBuffer.pop();
        }
    }
}

bool RouteSimulation::ready() const {
    return reachDestination;
}

RouteSimulation::~RouteSimulation() {
    if (producerThread->joinable()) {
        producerThread->join();
    }
    if (consumerThread->joinable()) {
        consumerThread->join();
    }
}