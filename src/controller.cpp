#include "controller.h"

Controller::Controller()
    : engine(configs),
      position_logger("../data/position_data.csv", static_cast<size_t>(configs["count"])),
      velocity_logger("../data/velocity_data.csv", static_cast<size_t>(configs["count"])),
      energy_logger("../data/energy_data.csv", std::vector<std::string>{"Kinetic Energy", "Potential Energy"}) {};

void Controller::log() {
  std::vector<double> row_pos{engine.getTime()};
  std::vector<double> row_vel{engine.getTime()};

  for (auto &particle : engine.particles) {
    for (int i = 0; i != 3; ++i) { row_pos.push_back(particle.position[i]); }
    for (int i = 0; i != 3; ++i) { row_vel.push_back(particle.velocity[i]); }
  }
  position_logger.log(row_pos);
  velocity_logger.log(row_vel);
}

void Controller::update() {
  engine.update();
}

void Controller::run() {
  for (size_t i = 0; i < (size_t)configs["steps"]; i++) {
    update();
    if (i % (size_t)configs["log_step"] == 0) {
      std::system("clear");
      printf("%s%.2f%s\n", "completed: ", ((float) i / (float) configs["steps"] * 100 + 1.f), "%");
      log();
    }
  }
}
