# Mapbox navigation 

## This project includes 3 sub-projects
C++ 20 is used.

### MapboxNavigation
* This is our core project.
* The library which provides route calculation, route simulation features
* It handles multiple threading inside the library for convenience, the client application doesn't need to create any thread.
* Currently, it only supports driving mode, needs a little bit extra work to support other mode.
* I use Linear interpolation to find accurate position between the coordinates from Mapbox API response for every single second
* I try to make design as clean as possible, there some classes handle its own business: 
  * ```HttpService```: handles http class to Mapbox backend
  * ```JsonParser```: handles http response json parsing to Route object
  * ```GuidanceGenerator```: generate Guidance data from Route object
  * ```RouteSimulation```: handles simulation data
* Interface ```Navigation``` is the only interface which client application needs to use, it has 4 functions
  * ```calculateRoute```: Calculate the route, client application needs implementing a callback handler to handler calculated route.
  * ```startSimulation```: Start simulation, client application needs implementing a callback handler to update simulation status, for example, update car position in map view.
  * ```updateSimulation```: Give command to MapboxNavigation library during simulation, for example, pause for a while or stop the simulation.
  * ```simulationStatus```: Check the simulation status

### Test
* This is a test application for demoing how to use the MapboxNavigation library using console
* Follow the console instructions, it is very easy to use.

### UnitTest
* Implements a couple of unit test cases