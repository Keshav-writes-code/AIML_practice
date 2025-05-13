#ifndef DATASET_H
#define DATASET_H

#include <vector>

class Datapoint {
public:
  double x;
  double y;
  Datapoint(double xVal, double yVal);

private:
};

class Dataset {
private:
  std::vector<Datapoint> data;

public:
  void generate(int count, double (*func)(double), double noiselevel = 0.0);
  void display() const;
  const std::vector<Datapoint> &get_data() const;
};

#endif
