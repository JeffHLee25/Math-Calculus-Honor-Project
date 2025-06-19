// ======================= RadarSimulator.h =======================
#ifndef RADAR_SIMULATOR_H
#define RADAR_SIMULATOR_H

#include <vector>

#include "Object.h"

/**
 * @class RadarSimulator
 * @brief This class manages the core logic of a radar-based simulation.
 *
 * It allows users to:
 * - Input vehicle motion data
 * - Add detected moving objects
 * - Simulate radar detection output
 * - Predict object and vehicle paths
 * - Animate motion and detect collisions
 */
class RadarSimulator {
 private:
  Vector2D vehiclePos;                  // Current position of the vehicle
  Vector2D vehicleVel;                  // Current velocity of the vehicle
  std::vector<Object> detectedObjects;  // List of objects detected by radar
  double crashTime;  // Time of collision, -1.0 if no collision occurred

 public:
  /**
   * @brief Constructor to initialize simulation state.
   * Sets initial position/velocity to (0, 0) and crashTime = -1.0.
   */
  RadarSimulator();

  /**
   * @brief Prompts user to input vehicle's initial position and velocity.
   */
  void inputVehicleData();

  /**
   * @brief Adds a new detected object with user-defined position and velocity.
   */
  void addObject();

  /**
   * @brief Shows current position and relative velocity of detected object.
   * Displays approximate time to impact using vector distance and relative
   * speed.
   */
  void simulateDetection();

  /**
   * @brief Displays all currently detected objects.
   * Shows index, position, and velocity for each.
   */
  void showAllObjects();

  /**
   * @brief Predicts future object and vehicle positions over a given time.
   * Stops and warns if collision is expected within that time frame.
   *
   * @param time How far into the future to simulate, in seconds.
   */
  void predictPath(double time);

  /**
   * @brief Runs the main simulation loop and menu system.
   * Supports all user interaction options.
   */
  void runSimulationLoop();
};

#endif  // RADAR_SIMULATOR_H