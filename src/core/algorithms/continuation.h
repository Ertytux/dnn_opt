/*
Copyright (c) 2018, Jairo Rojas-Delgado <jrdelgado@uci.cu>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
* Neither the name of the <organization> nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef DNN_OPT_CORE_ALGORITHMS_CONTINUATION
#define DNN_OPT_CORE_ALGORITHMS_CONTINUATION

#include <vector>
#include <functional>
#include <core/base/algorithm.h>
#include <core/base/proxy_sampler.h>
#include <core/base/reader.h>
#include <core/base/set.h>
#include <core/solutions/network.h>
#include <core/generators/uniform.h>

namespace dnn_opt
{
namespace core
{
namespace algorithms
{

class continuation : public virtual algorithm
{
public:

  /** Forward declaration of the builder seq of subsets of training patterns */
  class seq;

  /** Forward declaration of a descent builder */
  class descent;

  class fixed;

  static continuation* make(algorithm* base, seq* builder);

  virtual void reset() override;

  virtual void optimize() override;

  virtual void optimize(int eta, std::function<bool()> on) override;

  virtual void optimize_idev(int count, float dev, std::function<bool()> on) override;

  virtual void optimize_dev(float dev, std::function<bool()> on) override;

  virtual void optimize_eval(int count, std::function<bool()> on) override;

  virtual solution* get_best() override;

  virtual void init() override;

  virtual void set_params(std::vector<float> &params) override;

  using algorithm::set_params;

  virtual ~continuation() override;

protected:

  continuation(algorithm* base, seq* builder);

  /** The base algorithm that performs optimization */
  algorithm* _base;

  /** A pointer of @ref get_solutions() that do not degrade to core::solution */
  set<solutions::network>* _network_solutions;

  /** The dataset reader extracted from the first network solution */
  reader* _reader;

  /** The builder of the sequence of subsets of training patterns */
  seq* _builder;

private:

  void set_reader(int index);

};

/**
 * @brief The continuation::builder class is an abstract class to implement
 * custom ways of selecting the representative subset of training patterns.
 *
 * @author Jairo Rojas-Delgado<jrdelgado@uci.cu>
 * @date january, 2018
 * @version 1.0
 */
class continuation::seq
{
public:

  virtual void build() = 0;

  virtual reader* get(int idx) = 0;

  virtual int size() = 0;

};

class continuation::descent : public virtual continuation::seq
{
public :

  static descent* make(reader* dataset, int k, float beta);

  virtual void build() override;

  virtual reader* get(int idx) override;

  virtual float get_beta();

  virtual int size() override;

  virtual ~descent();

protected:

  descent(reader* dataset, int k, float beta);

private:

  /** Amount of subsets of training patterns */
  int _k;

  /** Proportion of the i-th subset respect to the (i+1)-th subset*/
  float _beta;

  reader* _dataset;

  std::vector<reader*> _sequence;

};


class continuation::fixed : public virtual continuation::seq
{
public :

  static fixed* make(reader* dataset, int k, float beta);

  virtual void build() override;

  virtual reader* get(int idx) override;

  virtual float get_beta();

  virtual int size() override;

  virtual ~fixed();

protected:

  fixed(reader* dataset, int k, float beta);

private:

  /** Amount of subsets of training patterns */
  int _k;

  /** Proportion of the i-th subset respect to the (i+1)-th subset*/
  float _beta;

  reader* _dataset;

  std::vector<reader*> _sequence;

};

} // namespace algorithms
} // namespace core
} // namespace dnn_opt

#endif
