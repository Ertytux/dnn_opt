#include <core/activations/hard_limit.h>

namespace dnn_opt
{
namespace core
{
namespace activations
{

hard_limit* hard_limit::make()
{
  return new hard_limit();
}

void hard_limit::f(int size, const float* sum, float* out)
{
  for(int i = 0; i < size; i++)
  {
    out[i] = sum[i] > 0 ? 1 : 0;
  }
}

} // namespace activations
} // namespace core
} // namespace dnn_opt
