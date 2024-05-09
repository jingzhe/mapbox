#include <iostream>
#include <Model.h>
#include <NavigationImpl.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

const string MAPBOX_TOKEN = "pk.eyJ1IjoiamluZ3poZXl1IiwiYSI6ImNsdnFmNWc5bjBlam4ybG1oYXplOTl3bHgifQ.s5Y8Q8mqLKAamzTxp1LA8w";
Route gRoute;

void calculateRoute(const std::unique_ptr<Navigation>& navigation) {
    auto startPoint = Point(25.467067, 65.08034);
    //auto destPoint = Point(25.4935245, 65.0084495); // 10 mins drive
    auto destPoint = Point(25.466874228304153, 65.08162289725789); // 2 mins drive

    auto points = std::vector { startPoint, destPoint };
    auto routeHandler = [](const Route& route) {
        gRoute = route;
        if (route.status == "Ok") {
            cout << "Your route is calculated, duration:" << route.duration / 60 << " minutes, distance:"
                 << route.distance / 1000 << " km" << endl;
        } else {
            cout << "Failed to calculate the route, status:" << route.status << endl;
        }
    };

    navigation->calculateRoute(points, MAPBOX_TOKEN, routeHandler);
    while (gRoute.status != "Ok") {
        cout << "waiting for route calculation..." << endl;
        std::this_thread::sleep_for(200ms);
        if (gRoute.status.find("Bad") != string::npos) {
            break;
        }
    }
}

int main() {
    std::cout << "Start route calculation..." << std::endl;
    std::unique_ptr<Navigation> navigation = std::make_unique<NavigationImpl>();

    calculateRoute(navigation);
    if (gRoute.status != "Ok") {
        return 0;
    }
    cout << "Do you want to start simulation? Type y and Enter to continue, type n and Enter to exit" << endl;

    string input;
    cin >> input;
    if (input == "y") {
        cout << "Simulation start..." << endl;
        cout << "Enter p to pause for 10 seconds" << endl;
        cout << "Enter s to stop the simulation" << endl;

        auto guidanceHandler = [](const Guidance& guidance) {
            auto now = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(now);
            string timeStr = std::ctime(&time);
            timeStr.erase(timeStr.find_last_not_of("\t\n\v\f\r ") + 1);
            cout << "[" << timeStr << "] | Street:" << guidance.status << " | speed:" << guidance.speed << " | speed limit:" << guidance.speedLimit << " | " << guidance.point.lon << ", " << guidance.point.lat << " | Maneuver:" << guidance.maneuver.type << " " << guidance.maneuver.instruction<< endl;
        };
        navigation->startSimulation(gRoute, guidanceHandler);
        char buf[20];
        fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
        while (navigation->simulationStatus() != SimulationStatus::done) {
            long numRead = read(0, buf, 4);
            if (numRead > 0) {
                string command {buf};
                command.erase(command.find_last_not_of("\t\n\v\f\r ") + 1);
                if (command == "p") {
                    cout << "Pause 10 seconds" << endl;
                    navigation->updateSimulation(SimulationCommand::pause);
                } else if (command == "s") {
                    cout << "Simulation will be stopped" << endl;
                    navigation->updateSimulation(SimulationCommand::stop);
                }
            }

            std::this_thread::sleep_for(1s);
        }
        cout << "Simulation is done!" << endl;
    } else {
        cout << "Exit simulator" << endl;
    }

    return 0;
}

