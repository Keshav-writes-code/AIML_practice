#include "../headers/lregression.h"
#include <cmath>
#include <iostream>
#include <vector>

L_Regression::L_Regression() {
  this->w = 0;
  this->b = 0;
  this->alpha = 0.001;
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

    const double w_new = this->w - (this->alpha * dw);
    const double b_new = this->b - (this->alpha * db);

    this->w = w_new;
    this->b = b_new;
  }
}
