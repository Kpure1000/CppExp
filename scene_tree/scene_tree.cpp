#include "scene_tree.h"

void SceneNode::add_child(GameObject *obj)
{
    _children.emplace_back(obj, this);
}

SceneNode::VisitorType SceneNode::childrenVisitor(std::function<VisitorType(SceneNode*)> const& visitor)
{
    for (auto &&child : this->_children)
    {
        auto visitor_type = visitor(this);
        if (visitor_type == VisitorType::SceneNode_Break)
            break;
        else if (visitor_type == VisitorType::SceneNode_Continue)
            continue;
        child->childrenVisitor(visitor);
    }
    return VisitorType::SceneNode_Break;
}

void SceneNode::parentsVisitor(std::function<VisitorType(SceneNode*)> const& visitor)
{
    SceneNode* parent = this->_parent;
    while (!parent)
    {
        if (visitor(parent) == VisitorType::SceneNode_Break)
            break;
        parent = parent->_parent;
    }
}

SceneNode* SceneTree::find(GameObject* target)
{
    SceneNode* ret = nullptr;
    _root->childrenVisitor([&](SceneNode* node)
    {
        if (node->_obj == target)
        {
            ret = node;
            return SceneNode::VisitorType::SceneNode_Break;
        }
        return SceneNode::VisitorType::SceneNode_Recursive;
    });
    return ret;
}