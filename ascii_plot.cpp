#include "ascii_plot.h"

#include <chrono>
#include <iomanip>
#include <thread>
using namespace std;

void simple2DPlot(const Object& obj, const Vector2D& vehiclePos) {
  const int x_min = -10, x_max = 100;
  const int y_min = -10, y_max = 10;
  const int width = (x_max - x_min) / 2 + 1;
  const int height = y_max - y_min + 1;

  char canvas[height][width];
  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j) canvas[i][j] = '.';

  int obj_x = static_cast<int>((obj.position.x - x_min) / 2);
  int obj_y = y_max - static_cast<int>(obj.position.y);
  int veh_x = static_cast<int>((vehiclePos.x - x_min) / 2);
  int veh_y = y_max - static_cast<int>(vehiclePos.y);

  if (obj_y >= 0 && obj_y < height && obj_x >= 0 && obj_x < width)
    canvas[obj_y][obj_x] = 'O';

  if (veh_y >= 0 && veh_y < height && veh_x >= 0 && veh_x < width)
    canvas[veh_y][veh_x] = 'V';

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) cout << canvas[i][j];
    cout << endl;
  }
}

void animateMotionSmoothWithCrash(const Object& objInit,
                                  const Vector2D& vehicleInit,
                                  const Vector2D& vehicleVel, double duration,
                                  double& crashTime, double frameRate) {
  cout << "\033[?25l";  // Hide cursor

  Vector2D objPos = objInit.position;
  Vector2D objVel = objInit.velocity;
  Vector2D vehPos = vehicleInit;
  Vector2D vehVel = vehicleVel;

  int frames = static_cast<int>(duration * frameRate);
  double dt = 1.0 / frameRate;

  for (int i = 0; i <= frames; ++i) {
    cout << "\033[H";
    cout << "Time: " << fixed << setprecision(1) << (i * dt) << " sec\n";

    simple2DPlot(Object(objPos, objVel), vehPos);

    double dist = (objPos - vehPos).magnitude();
    if (dist < 1.0) {
      crashTime = i * dt;
      cout << "\n  CRASH DETECTED! Vehicles collided at time " << fixed
           << setprecision(2) << crashTime << " sec. \n";
      break;
    }

    objPos = objPos + objVel.scalarMultiply(dt);
    vehPos = vehPos + vehVel.scalarMultiply(dt);
    this_thread::sleep_for(chrono::milliseconds(static_cast<int>(1000 * dt)));
  }

  cout << "\033[?25h";
}
