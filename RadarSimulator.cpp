#include "RadarSimulator.h"

#include <iomanip>
#include <iostream>

#include "ascii_plot.h"
using namespace std;

RadarSimulator::RadarSimulator() : crashTime(-1.0) {
  vehiclePos = Vector2D(0, 0);
  vehicleVel = Vector2D(0, 0);
}

void RadarSimulator::inputVehicleData() {
  cout << "Enter vehicle position (x y): ";
  cin >> vehiclePos.x >> vehiclePos.y;
  cout << "Enter vehicle velocity (x y): ";
  cin >> vehicleVel.x >> vehicleVel.y;
  crashTime = -1.0;
}

void RadarSimulator::addObject() {
  Vector2D pos, vel;
  cout << "Enter object position (x y): ";
  cin >> pos.x >> pos.y;
  cout << "Enter object velocity (x y): ";
  cin >> vel.x >> vel.y;
  detectedObjects.emplace_back(pos, vel);
  crashTime = -1.0;
}

void RadarSimulator::showAllObjects() {
  if (detectedObjects.empty()) {
    cout << "No objects detected.\n";
    return;
  }
  for (size_t i = 0; i < detectedObjects.size(); ++i) {
    cout << "Object " << i + 1 << ":\n";
    cout << "  Position: ";
    detectedObjects[i].position.print();
    cout << endl;
    cout << "  Velocity: ";
    detectedObjects[i].velocity.print();
    cout << endl;
  }
}


void RadarSimulator::predictPath(double time) {
  if (detectedObjects.empty()) {
    cout << "No objects to predict.\n";
    return;
  }

  Object& obj = detectedObjects[0];
  double dt = 0.1, t = 0.0;
  Vector2D objPos = obj.position;
  Vector2D vehPos = vehiclePos;

  while (t <= time) {
    if ((objPos - vehPos).magnitude() < 1.0) {
      cout << "Collision predicted at time " << fixed << setprecision(2) << t
           << " sec.\n";
      return;
    }
    objPos = objPos + obj.velocity.scalarMultiply(dt);
    vehPos = vehPos + vehicleVel.scalarMultiply(dt);
    t += dt;
  }

  cout << "No collision predicted within " << fixed << setprecision(2) << time
       << " sec.\n";
  cout << "Predicted object position: ";
  objPos.print();
  cout << "\nPredicted vehicle position: ";
  vehPos.print();
  cout << endl;
}
void RadarSimulator::simulateDetection() {
  if (detectedObjects.empty()) {
    std::cout << "No objects detected.\n";
    return;
  }

  for (size_t i = 0; i < detectedObjects.size(); ++i) {
    const Object& obj = detectedObjects[i];
    Vector2D relPos = obj.position - vehiclePos;
    Vector2D relVel = obj.velocity - vehicleVel;

    double dist = relPos.magnitude();
    double speed = relVel.magnitude();
    double dot = relPos.dot(relVel);

    std::cout << "Object #" << i << ":\n";
    std::cout << "  Position: (" << obj.position.x << ", " << obj.position.y
              << ")\n";
    std::cout << "  Velocity: (" << obj.velocity.x << ", " << obj.velocity.y
              << ")\n";
    std::cout << "  Relative Distance: " << dist << "\n";
    std::cout << "  Relative Speed: " << speed << "\n";
    std::cout << "  Dot Product (relPos ¡P relVel): " << dot << "\n";

    if (speed > 0.01) {
      double timeToImpact = dist / speed;
      std::cout << "  Estimated Time to Impact: " << timeToImpact
                << " seconds\n";
    }

    if (dot < 0) {
      std::cout << "  Interpretation: Object is approaching the vehicle.\n";
    } else {
      std::cout << "  Interpretation: Object is moving away or not on a "
                   "collision course.\n";
    }
    std::cout << "----------------------------------------\n";
  }
}





void RadarSimulator::runSimulationLoop() {
  int choice;
  do {
    cout << "\n==== Radar Path Prediction Simulator ====\n";
    cout << "1. Input Vehicle Data\n";
    cout << "2. Add Detected Object\n";
    cout << "3. Show All Objects\n";
    cout << "4. Simulate Detection\n";
    cout << "5. Predict Path (Specify Time)\n";
    cout << "6. Animate With CRASH Detection\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
      case 1:
        inputVehicleData();
        break;
      case 2:
        addObject();
        break;
      case 3:
        showAllObjects();
        break;
      case 4:
        simulateDetection();
        break;
      case 5: {
        double t;
        cout << "Enter time in seconds: ";
        cin >> t;
        predictPath(t);
        break;
      }
      case 6: {
        if (detectedObjects.empty()) {
          cout << "No objects to animate.\n";
          break;
        }
        double seconds;
        cout << "Enter duration in seconds: ";
        cin >> seconds;
        crashTime = -1.0;
        animateMotionSmoothWithCrash(detectedObjects[0], vehiclePos, vehicleVel,
                                     seconds, crashTime, 10.0);
        break;
      }
      case 0:
        cout << "Exiting...\n";
        break;
      default:
        cout << "Invalid choice.\n";
        break;
    }
  } while (choice != 0);
}
