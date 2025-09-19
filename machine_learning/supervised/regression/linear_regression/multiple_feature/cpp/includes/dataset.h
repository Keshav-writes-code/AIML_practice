#pragma once

#include <vector>

class Datapoint {
public:
  std::vector<double> point;
  Datapoint(int attribs);
};

class Dataset {
private:
  std::vector<Datapoint> data;

public:
  Dataset(int samples, double (*targetFunc)(double), double noiselevel = 0.0);
  const std::vector<Datapoint> &get_data() const;
};
