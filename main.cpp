#include "periodProject.hpp"

constexpr int a{1000};
constexpr int b{500000};
constexpr double max_error{0.001};
const auto resolution{getResolution()};
const int t_min{resolution * ((1 / max_error) + 1)};