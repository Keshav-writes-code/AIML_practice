#include "../headers/dataset.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

Datapoint::Datapoint(double xVal, double yVal) {
  this->x = xVal;
  this->y = yVal;
}

void Dataset::generate(int count, double (*func)(double), double noiselevel) {
  std::default_random_engine rng(std::random_device{}());
  std::normal_distribution<double> noise(0.0, noiselevel);

  for (int i = 0; i < count; ++i) {
    double x = static_cast<double>(i);
    double y = func(x) + noise(rng);
    this->data.emplace_back(x, y);
  }
}
void Dataset::display() const {
  if (data.empty()) {
    std::cout << "No data to display." << std::endl;
    return;
  }

  // Get terminal dimensions
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  // Use half of the terminal width and fixed height
  int width = w.ws_col / 2;
  int height = 20; // Fixed height for better visualization

  // Find min and max values for x and y
  double minX = data[0].x;
  double maxX = data[0].x;
  double minY = data[0].y;
  double maxY = data[0].y;

  for (const auto &point : data) {
    minX = std::min(minX, point.x);
    maxX = std::max(maxX, point.x);
    minY = std::min(minY, point.y);
    maxY = std::max(maxY, point.y);
  }

  // Add a small margin to y range for better visualization
  double yMargin = (maxY - minY) * 0.1;
  minY -= yMargin;
  maxY += yMargin;

  // Create a 2D grid for the plot
  std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));

  // Mark axes
  int xAxisPos = height - 1;
  if (minY < 0 && maxY > 0) {
    xAxisPos =
        static_cast<int>(height - 1 - ((-minY) / (maxY - minY) * (height - 1)));
  }

  // Draw x-axis
  for (int j = 0; j < width; ++j) {
    grid[xAxisPos][j] = '-';
  }

  // Draw y-axis
  for (int i = 0; i < height; ++i) {
    grid[i][0] = '|';
  }

  // Place origin marker
  grid[xAxisPos][0] = '+';

  // Plot data points
  for (const auto &point : data) {
    // Convert data coordinates to grid coordinates
    int x =
        static_cast<int>((point.x - minX) / (maxX - minX) * (width - 3)) + 1;
    int y = static_cast<int>(height - 1 -
                             (point.y - minY) / (maxY - minY) * (height - 1));

    // Ensure point is within grid bounds
    if (x >= 0 && x < width && y >= 0 && y < height) {
      grid[y][x] = '*';
    }
  }

  // Display the grid
  std::cout << "\nData Plot (X range: " << minX << " to " << maxX
            << ", Y range: " << minY << " to " << maxY << ")\n\n";

  // Print y-axis labels
  for (int i = 0; i < height; ++i) {
    if (i == 0 || i == height - 1 || i == xAxisPos) {
      double yVal =
          maxY - (static_cast<double>(i) / (height - 1)) * (maxY - minY);
      std::cout << std::setw(8) << std::fixed << std::setprecision(1) << yVal
                << " ";
    } else {
      std::cout << "         ";
    }

    // Print the grid row
    for (int j = 0; j < width; ++j) {
      std::cout << grid[i][j];
    }
    std::cout << std::endl;
  }

  // Print x-axis labels
  std::cout << "         ";
  std::cout << std::fixed << std::setprecision(1) << minX;

  int midPos = width / 2;
  double midX = minX + (maxX - minX) / 2;

  std::cout << std::string(midPos - 8, ' ');
  std::cout << std::fixed << std::setprecision(1) << midX;

  std::cout << std::string(width - midPos - 8, ' ');
  std::cout << std::fixed << std::setprecision(1) << maxX << std::endl;
}

const std::vector<Datapoint> &Dataset::get_data() const { return this->data; }
