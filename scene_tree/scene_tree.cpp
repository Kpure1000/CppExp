#include "scene_tree.h"
#include <iostream>
#include <stack>

std::ostream& operator<<(std::ostream& os, const GameObject& obj)
{
    return os << obj.name;
}


std::ostream& operator<<(std::ostream& os, GameObject&& obj)
{
    return os << obj.name;
}

//////////////////
/// SceneNode
//////////////////

void SceneNode::add_child(GameObject *obj)
{
    _children.emplace_back(new SceneNode{obj, this});
}

bool SceneNode::childrenVisitor(VisitorFn const& visitor) const 
{
    if (!visitor(const_cast<SceneNode*>(this)))
    {
        return false;
    }

    for (int i = 0; i < _children.size(); i++)
    {
        if (!_children[i]->childrenVisitor(visitor))
        {
            return false;
        }
    }
    return true;
}

void SceneNode::childrenVisitor_it(VisitorFn const& visitor) const 
{
    std::stack<const SceneNode*> tree_stack;
    tree_stack.push(this);
    while (!tree_stack.empty())
    {
        auto top_node = tree_stack.top();
        tree_stack.pop();
        if (!visitor(const_cast<SceneNode *>(top_node)))
        {
            return;
        }
        for (int i = top_node->_children.size() - 1; i >= 0; i--)
        {
            tree_stack.push(top_node->_children[i]);
        }
    }
}

void SceneNode::parentsVisitor(VisitorFn const& visitor)
{
    SceneNode* parent = this->_parent;
    while (!parent)
    {
        if (!visitor(parent))
            break;
        parent = parent->_parent;
    }
}

//////////////////
/// SceneTree
//////////////////

SceneNode* SceneTree::find(FoundFn const& foundFn)
{
    SceneNode* ret = nullptr;
    _root->childrenVisitor([&](SceneNode* node)
    {
        if (foundFn(node))
        {
            ret = node;
            return false;
        }
        return true;
    });
    return ret;
}

SceneNode* SceneTree::find(GameObject* target)
{
    return find([&target](SceneNode* node)
    {
        return node->_obj == target;
    });
}
