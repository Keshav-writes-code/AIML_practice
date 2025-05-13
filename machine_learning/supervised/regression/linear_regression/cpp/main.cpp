#include "headers/dataset.h"
#include "headers/lregression.h"
#include <iostream>
#include <vector>

double linearFunc(double x) { return 2.0 * x + 10.0; }

int main() {
  Dataset myData;
  myData.generate(10, linearFunc, 1);
  myData.display();
  std::vector<Datapoint> Dataset = myData.get_data();

  L_Regression my_model;

  double cost;

  cost = my_model.cost(Dataset);
  std::cout << "\n\nCost without Traning : " << cost << "\n\n";

  my_model.fit(Dataset, 10000000);

  cost = my_model.cost(Dataset);
  std::cout << "Cost After Traning : " << cost << "\n\n";
}
