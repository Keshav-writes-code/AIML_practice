#ifndef LR_H
#define LR_H

#include "dataset.h"
#include <vector>

class L_Regression {
private:
  double w;
  double b;
  double alpha;

public:
  L_Regression();
  double y_predict(double x) const;
  double cost(const std::vector<Datapoint> &dataset);
  void fit(const std::vector<Datapoint> &dataset, const int epochs);
};

#endif
