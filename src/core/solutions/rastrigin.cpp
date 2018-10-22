#include <math.h>
#include <core/solutions/rastrigin.h>

namespace dnn_opt
{
namespace core
{
namespace solutions
{

rastrigin* rastrigin::make(generator* generator, unsigned int size)
{
  auto* result = new rastrigin(generator, size);

  result->init();

  return result;
}

float rastrigin::calculate_fitness()
{
  float result = 10 * size();

  solution::calculate_fitness();
  for(int i = 0; i < size(); i++)
  {
    result += pow(get(i), 2) - 10 * cos(2 * 3.141592653f * get(i));
  }

  return result;
}

rastrigin::rastrigin(generator* generator, unsigned int size )
: solution(generator, size)
{

}

rastrigin::~rastrigin()
{

}

} // namespace solutions
} // namespace core
} // namespace dnn_opt