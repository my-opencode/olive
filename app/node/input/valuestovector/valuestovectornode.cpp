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

#include "valuestovectornode.h"

namespace olive {

const QString ValuesToVectorNode::kParamXIn = QStringLiteral("X");
const QString ValuesToVectorNode::kParamYIn = QStringLiteral("Y");

/**
  Restrict input values to
  NodeValue::kFloat,
  NodeValue::kInt,
  NodeValue::kRational,
  Output is one of
  NodeValue::kVec2,
  NodeValue::kVec3,
  NodeValue::kVec4,
*/

#define super Node

ValuesToVectorNode::ValuesToVectorNode() {
  AddInput(kParamXIn, NodeValue::kFloat, 0.0);
  SetInputProperty(kParamXIn, QStringLiteral("decimalplaces"), 8);
  SetInputProperty(kParamXIn, QStringLiteral("autotrim"), true);

  AddInput(kParamYIn, NodeValue::kFloat, 0.0);
  SetInputProperty(kParamYIn, QStringLiteral("decimalplaces"), 8);
  SetInputProperty(kParamYIn, QStringLiteral("autotrim"), true);
}

void ValuesToVectorNode::Retranslate() {
  super::Retranslate();

  SetInputName(kParamXIn, QStringLiteral("X"));
  SetInputName(kParamYIn, QStringLiteral("Y"));
}

void ValuesToVectorNode::Value(const NodeValueRow &value, const NodeGlobals &globals, NodeValueTable *table) const {
  Q_UNUSED(globals)
  // Push value onto the table
  table->Push(NodeValue::kVec2, 
              QVector2D(value[kParamXIn].toDouble(), value[kParamYIn].toDouble()), 
              this);
}

}  // namespace olive
