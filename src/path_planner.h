#ifndef PATH_PLANNER_H
#define PATH_PLANNER_H

#include <iostream>
#include <vector>
#include "json.hpp"

#include "kinematic_state.h"
#include "point.h"
#include "sensor_data.h"
#include "trajectory.h"
#include "trajectory_strategy.h"

using namespace std;

// for convenience
using json = nlohmann::json;

class PathPlanner {
public:

  // Program Parameters
  static constexpr double LANE_WIDTH = 4;
  static constexpr int NUM_LANES = 3;
  static constexpr int SPEED_LIMITS[] = {10, 20, 30};

  // Inputs of the Path Planner
  KinematicState ego_data;

  // The sensor_fusion variable contains all the information about the cars on the right-hand side of the road.
  // The data format for each car is: [ id, x, y, vx, vy, s, d]. The id is a unique identifier for that car. The x, y values are in global map coordinates, and the vx, vy values are the velocity components, also in reference to the global map. Finally s and d are the Frenet coordinates for that car.
  SensorData environment_data;

  // Output of the Path Planner
  // Trajectory next_path;
  
  TrajectoryStrategy* strategy;

  // Constructor and destructor
  PathPlanner();
  virtual ~PathPlanner();

  // Methods
  //! Process the inputs and generate the output trajectory
  Trajectory Generate();

  // // Test methods
  // //! Generates a Straight Line
  // void GenerateStraightLine();
  
  // //! Generates a Circle path
  // void GenerateCircle();
  
  void SetPreviousPath(json previous_path_x, json previous_path_y);
  
  void SetPreviousEndPoint(double end_path_s, double end_path_d);
};

#endif