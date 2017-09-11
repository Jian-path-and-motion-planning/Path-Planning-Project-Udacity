#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

#include "../Eigen-3.3/Eigen/Core"
#include "../Eigen-3.3/Eigen/QR"
#include "../json.hpp"

#include "../logger.h"
#include "../map.h"
#include "../path_planner.h"
#include "../trajectory.h"
#include "../utils.h"

#include "stub.h"

// for convenience
using namespace std;
using json = nlohmann::json;

int main()
{
  SET_LOG_LEVEL(logDEBUG3);
  LOG(logINFO) << "----- Test Path Planner -----";
  
  Map::GetInstance();
  
  PathPlanner path_planner;
  
  LOG(logINFO) << "Get ego vehicle sensor data";
  EgoSensorData ego_data;
  ego_data.x = stub_ego_data["x"];
  ego_data.y = stub_ego_data["y"];
  ego_data.s = stub_ego_data["s"];
  ego_data.d = stub_ego_data["d"];
  ego_data.speed = stub_ego_data["speed"];
  ego_data.yaw = stub_ego_data["yaw"];
  
  path_planner.SetEgoData(ego_data);
  
    // Convert Sensor fusion data from json to SensorData class:
  LOG(logINFO) << "Get environment sensor data";
  for (const auto& sensed_vehicle : stub_environment_data)
  {
    EnvironmentSensorData::SensedVehicleData data;
    data.id = sensed_vehicle[0];
    data.x = sensed_vehicle[1];
    data.y= sensed_vehicle[2];
    data.vx = sensed_vehicle[3];
    data.vy = sensed_vehicle[4];
    data.s = sensed_vehicle[5];
    data.d = sensed_vehicle[6];
    path_planner.environment_data.sensed_vehicle_list.push_back(data);
  }

  LOG(logINFO) << "Generate next path";
  Trajectory next_path = path_planner.Generate();

  vector<double> next_x_values;
  vector<double> next_y_values;

  LOG(logINFO) << "Setting next_values ";
  next_x_values = next_path.GetXvalues();
  next_y_values = next_path.GetYvalues();
  
  LOG(logDEBUG3) << "next_path: " << endl << next_path << endl;

  return 0;
}