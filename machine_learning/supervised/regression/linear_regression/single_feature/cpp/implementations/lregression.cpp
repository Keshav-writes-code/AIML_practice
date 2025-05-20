#include "../headers/lregression.h"
#include <cmath>
#include <iostream>
#include <vector>

L_Regression::L_Regression() {
  this->w = 0;
  this->b = 0;
  this->alpha = 0.01;
}
double L_Regression::y_predict(double x) const {
  return (x * this->w) + this->b;
}

double L_Regression::cost(const std::vector<Datapoint> &dataset) {
  // Mean Squared Error

  double summed_squared_error = 0.0;

  for (const Datapoint &data : dataset) {
    const double y_predicted = this->y_predict(data.x);
    const double error = y_predicted - data.y;
    summed_squared_error += std::pow(error, 2.0);
  }

  double mean =
      summed_squared_error / (2.0 * static_cast<double>(dataset.size()));
  return mean;
}

void L_Regression::fit(const std::vector<Datapoint> &dataset,
                       const int epochs) {

  const double threshold = 0.001;
  double prev_cost = 0.0;

  for (int i = 0; i < epochs; i++) {
    double dw = 0, db = 0;
    for (auto &data : dataset) {
      double y_pred = this->y_predict(data.x);
      double error = y_pred - data.y;
      dw += error * data.x;
      db += error;
    }
    dw /= dataset.size();
    db /= dataset.size();

    const double dynamic_alpha =
        this->alpha * (((static_cast<double>(epochs - i) / epochs) * 13) + 1);
    const double w_new = this->w - (dynamic_alpha * dw);
    const double b_new = this->b - (dynamic_alpha * db);

    this->w = w_new;
    this->b = b_new;

    if ((i + 2) % 100 == 0) {
      prev_cost = this->cost(dataset);
    } else if ((i + 1) % 100 == 0) {
      const double next_cost = this->cost(dataset);
      if (prev_cost - next_cost <= threshold) {
        std::cout << "\nBreak at " << i << "th Iterations\n";
        break;
      }
    }
  }
}
