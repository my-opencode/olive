# Code documentation

## Create a custom node

*Placeholder conventions:*

a. Format conventions:

- \<smallcase> all smallcase.
- \<UPPERCASE> all uppercase.
- \<CamelCase> camelcase.
- \<anything_human> human readable string such as a GUI label.

b. Values conventions:

- \<category> The category of the node.
- \<nodename> Then name of the node.
- \<InputName> The name of a node input. E.G.: "ParamAIn" = parameter A input.
- \<type_of_the_input> A type. Can be native C++ like double. Usually a property of NodeValue. E.G.: NodeValue::kInt.

### Files to update (u) or add (a):

- [u] app/node/factory.cpp
- [u] app/node/factory.h
- [u] app/node/\<category>/CMakeLists.txt
- [a] app/node/\<category>/\<nodename>/CMakeLists.txt
- [a] app/node/\<category>/\<nodename>/\<nodename>node.cpp
- [a] app/node/\<category>/\<nodename>/\<nodename>node.h

### Update app/node/factory.cpp

> Import the new node node to the factory.

```diff
+ #include "<category>/<nodename>/<nodename>node.h"
```

```diff
Node *NodeFactory::CreateFromFactoryIndex(const NodeFactory::InternalID &id)
{
  switch (id) {
...
+  case k<NodeName>Node:
+    return new <NodeName>Node();
```

### Update app/node/factory.h

> Add its id.

```diff
class NodeFactory
{
public:
  enum InternalID {
...
+    k<NodeName>Node,
```

### Update app/node/\<category>/CMakeLists.txt

> Add the node.

```diff
+ add_subdirectory(<nodename>)
```

### Create a node directory: app/node/\<category>/\<nodename>

### Add file app/node/\<category>/\<nodename>/CMakeLists.txt

```c#
# Olive - Non-Linear Video Editor
# Copyright (C) 2022 Olive Team
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

set(OLIVE_SOURCES
  ${OLIVE_SOURCES}
  node/<category>/<nodename>/<nodename>node.h
  node/<category>/<nodename>/<nodename>node.cpp
  PARENT_SCOPE
)
```

### Add file app/node/\<category>/\<nodename>/\<nodename>node.cpp

```c#
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

#include "<nodename>node.h"

namespace olive {

/* Define your node's inputs. */
const QString <NodeName>Node::k<InputName> = QStringLiteral("<inputname_human>");

#define super Node

<NodeName>Node::<NodeName>Node()
{
  /* Define your node's input fields. */
  AddInput(k<InputName>, /* e.g.: kAudioVolumeIn */
           <type_of_the_input>, /* e.g.: NodeValue::kFloat */
           <defaultvalue>, /* e.g.: 0.0 */
           <optional_input_flags> /* e.g.: InputFlags(kInputFlagNotConnectable) */
           );
  /** Inputs can be extended with SetInputProperty() */
}

void <NodeName>Node::Retranslate()
{
  super::Retranslate();

  /** Set the GUI names of your inputs. */
  SetInputName(k<InputName>, QStringLiteral("<inputname_human>"));

  /** 
   * For combo boxes, use:
   * QStringList
   * and
   * SetComboBoxStrings
   */
}

void <NodeName>Node::Value(const NodeValueRow &value, const NodeGlobals &globals, NodeValueTable *table) const
{
  /** Flag unused arguments */
  // Q_UNUSED(value)
  Q_UNUSED(globals)
  // Q_UNUSED(table)

  /**
   * Compute logic goes here.
   */

  /** 
   * Nodes return a table.
   * Push the node output to the table.
   * When using an input value directly, do not forget to cast it if needed.
   */
  table->Push(value[k<InputName>].toDouble()); /** Example with a cast to double/float */
}
}
```

### Add file app/node/\<category>/\<nodename>/\<nodename>node.h

```c#
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

#ifndef <NODENAME>NODE_H
#define <NODENAME>NODE_H

#include "node/node.h"

namespace olive {

class <NodeName>Node : public Node
{
  Q_OBJECT
public:
  <NodeName>Node();

  NODE_DEFAULT_FUNCTIONS(<NodeName>Node)

  virtual QString Name() const override
  {
    return tr("<nodename_human>");
  }

  virtual QString id() const override
  {
    return QStringLiteral("org.olivevideoeditor.Olive.<nodename>");
  }

  virtual QVector<CategoryID> Category() const override
  {
    return {kCategoryGenerator};
  }

  virtual QString Description() const override
  {
    return tr("Description of the new node.");
  }

  /** Declare inputs */
  static const QString k<InputName>;

  virtual void Retranslate() override;

  virtual void Value(const NodeValueRow& value, const NodeGlobals &globals, NodeValueTable *table) const override;

/** 
 * Declare methods that you need to override 
 * E.G.:
protected:
  virtual void InputValueChangedEvent(const QString &input, int element) override;
};
 */

}

#endif // <NODENAME>NODE_H
```
