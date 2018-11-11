#include <cmath>
#include <copt/solutions/griewangk.h>

namespace dnn_opt
{
namespace copt
{
namespace solutions
{

griewangk* griewangk::make(generator* generator, unsigned int size)
{
  auto* result = new griewangk(generator, size);

  result->init();

  return result;
}

float griewangk::calculate_fitness()
{
  double summatory = 0;
  double multiplier = 1;
  float result = 0;

  solution::calculate_fitness();

  for(int i = 0; i < size(); i++)
  {
    summatory  += get(i) * get(i) / 4000;
    multiplier *= cos(get(i) / sqrt(i));
  }

  result = summatory - multiplier + 1;

  return result;
}

griewangk::griewangk(generator* generator, unsigned int size)
: solution(generator, size),
  core::solution(generator, size),
  core::solutions::griewangk(generator, size)
{

}

griewangk::~griewangk()
{

}

} // namespace solutions
} // namespace copt
} // namespace dnn_opt