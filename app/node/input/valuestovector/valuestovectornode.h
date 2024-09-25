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

#ifndef VALUESTOVECTORNODE_H
#define VALUESTOVECTORNODE_H

#include "node/node.h"

namespace olive {

class ValuesToVectorNode : public Node
{
  Q_OBJECT
public:
  ValuesToVectorNode();

  NODE_DEFAULT_FUNCTIONS(ValuesToVectorNode)

  virtual QString Name() const override
  {
    return tr("Values to Vector2");
  }

  virtual QString id() const override
  {
    return QStringLiteral("org.olivevideoeditor.Olive.valuestovector");
  }

  virtual QVector<CategoryID> Category() const override
  {
    return {kCategoryGenerator};
  }

  virtual QString Description() const override
  {
    return tr("Create a vector, from discrete values, that can be connected to various other inputs.");
  }

  static const QString kParamXIn;
  static const QString kParamYIn;

  virtual void Retranslate() override;

  virtual void Value(const NodeValueRow& value, const NodeGlobals &globals, NodeValueTable *table) const override;

protected:
  virtual void InputValueChangedEvent(const QString &input, int element) override;
};

}

#endif // VALUESTOVECTORNODE_H
