#include <core/generators/normal.h>

namespace dnn_opt
{
namespace core
{
namespace generators
{

normal* normal::make(float mean, float dev)
{
  return new normal(mean, dev);
}

void normal::generate(int count, float* params)
{
  float ext = _max - _min;

  for(int i = 0; i < count; i++)
  {
    params[i] = (* _distribution)(*_generator) * ext + _min;
  }
}

float normal::generate()
{
  return (*_distribution)(*_generator);
}

void normal::set_constraints(int count, float* params)
{
  float min = get_min();
  float max = get_max();

  for(int i = 0; i < count; i++)
  {
    params[i] = std::max(min, std::min(max, params[i]));
  }
}

normal::normal(float mean, float dev)
: generator(mean - dev, mean + dev)
{
  std::random_device device;

  _generator = new std::mt19937(device());
  _distribution = new std::normal_distribution<float>(mean, dev);
  _mean = mean;
  _dev = dev;
}

normal::~normal()
{
  delete _generator;
  delete _distribution;
}

} // namespace generators
} // namespace core
} // namespace dnn_opt
