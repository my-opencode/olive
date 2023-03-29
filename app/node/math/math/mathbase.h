/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2022 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef MATHNODEBASE_H
#define MATHNODEBASE_H

#include "node/node.h"

namespace olive {

class MathNodeBase : public Node
{
public:
  MathNodeBase() = default;

  enum Operation {
    kOpAdd,
    kOpSubtract,
    kOpMultiply,
    kOpDivide,
    kOpPower
  };

  static QString GetOperationName(Operation o);

  static ShaderCode GetShaderCode(const QString &shader_id);
  static void ProcessSamplesNumber(const void *context, const SampleJob &job, SampleBuffer &mixed_samples);
  static void ProcessSamplesSamples(const void *context, const SampleJob &job, SampleBuffer &mixed_samples);

protected:
  enum Pairing {
    kPairNone = -1,

    kPairNumberNumber,
    kPairVecVec,
    kPairMatrixMatrix,
    kPairColorColor,
    kPairTextureTexture,

    kPairVecNumber,
    kPairMatrixVec,
    kPairNumberColor,
    kPairTextureNumber,
    kPairTextureColor,
    kPairTextureMatrix,
    kPairSampleSample,
    kPairSampleNumber,

    kPairCount
  };

  class PairingCalculator
  {
  public:
    PairingCalculator(const NodeValue &table_a, const NodeValue &table_b);

    bool FoundMostLikelyPairing() const;
    Pairing GetMostLikelyPairing() const;

    const NodeValue& GetMostLikelyValueA() const;
    const NodeValue& GetMostLikelyValueB() const;

  private:
    static QVector<int> GetPairLikelihood(const NodeValue &table);

    Pairing most_likely_pairing_;

    NodeValue most_likely_value_a_;

    NodeValue most_likely_value_b_;

  };

  template<typename T, typename U>
  static T PerformAll(Operation operation, T a, U b);

  template<typename T, typename U>
  static T PerformMultDiv(Operation operation, T a, U b);

  template<typename T, typename U>
  static T PerformAddSub(Operation operation, T a, U b);

  template<typename T, typename U>
  static T PerformMult(Operation operation, T a, U b);

  template<typename T, typename U>
  static T PerformAddSubMult(Operation operation, T a, U b);

  template<typename T, typename U>
  static T PerformAddSubMultDiv(Operation operation, T a, U b);

  static void PerformAllOnFloatBuffer(Operation operation, const float *input, float *output, float b, size_t start, size_t end);

#if defined(Q_PROCESSOR_X86) || defined(Q_PROCESSOR_ARM)
  static void PerformAllOnFloatBufferSSE(Operation operation, const float *input, float *output, float b, size_t start, size_t end);
#endif

  static QString GetShaderUniformType(const NodeValue::Type& type);

  static QString GetShaderVariableCall(const QString& input_id, const NodeValue::Type& type, const QString &coord_op = QString());

  static QVector4D RetrieveVector(const NodeValue& val);

  static float RetrieveNumber(const NodeValue& val);

  static bool NumberIsNoOp(const Operation& op, const float& number);

  NodeValue PushVector(NodeValue::Type type, const QVector4D& vec) const;

  NodeValue ValueInternal(Operation operation, Pairing pairing, const QString& param_a_in, const NodeValue &val_a, const QString& param_b_in, const NodeValue& val_b, const ValueParams &p) const;

};

}

#endif // MATHNODEBASE_H
