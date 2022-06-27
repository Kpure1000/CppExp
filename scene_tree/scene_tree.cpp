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

SceneNode* SceneNode::operator[](int index)
{
    return _children[index].get();
}

const SceneNode* SceneNode::operator[](int index) const
{
    return _children[index].get();
}

int SceneNode::get_child_index(SceneNode* node) const
{
    auto cur_it = std::find_if(_children.begin(), _children.end(),
                               [&](std::shared_ptr<SceneNode> node_s)
                               {
                                   return node_s.get() == node;
                               });
    return cur_it != _children.end() ? cur_it - _children.begin() : -1;
}

void SceneNode::add_child(GameObject *obj)
{
    _children.emplace_back(new SceneNode{obj, this});
}

void SceneNode::add_child(GameObject *obj, int index)
{
    _children.insert(_children.begin() + index, std::make_shared<SceneNode>(obj, this));
}

void SceneNode::removeChildren()
{
    for (int i = 0; i < _children.size(); i++)
    {
        _children[i]->removeChildren();
        _children[i]->_children.clear();
    }
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

bool SceneNode::childrenVisitorEx(VisitorFn const& preVisitor, VisitorFn const& sufVisitor) const
{
    if (!preVisitor(const_cast<SceneNode*>(this)))
    {
        return false;
    }

    for (int i = 0; i < _children.size(); i++)
    {
        if (!_children[i]->childrenVisitorEx(preVisitor, sufVisitor))
        {
            return false;
        }
    }

    if (!sufVisitor(const_cast<SceneNode*>(this)))
    {
        return false;
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
        for (int i = top_node->children_size() - 1; i >= 0; i--)
        {
            tree_stack.push(top_node->_children[i].get());
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
    return find([&target](SceneNode* node)    {
        return node->_obj == target;
    });
}

void SceneTree::remove(SceneNode* node)
{
    node->removeChildren();
    node->_children.clear();
    if (node == _root.get())
        return;
    auto parent = node->_parent;
    parent->_children.erase(std::find_if(parent->_children.begin(), parent->_children.end(),
        [&](std::shared_ptr<SceneNode> node_s)
        {
            return node_s.get() == node;
        }));

}

void SceneTree::move(SceneNode* source, SceneNode* target, int child_index)
{
    target->add_child(source->_obj, child_index);

    auto cur_parent = source->_parent;

    int source_index = cur_parent->get_child_index(source);

    std::swap(target->_children[child_index], cur_parent->_children[source_index]);
    
    target->_children[child_index]->_parent = target;

    cur_parent->_children.erase(cur_parent->_children.begin() + source_index);
}
