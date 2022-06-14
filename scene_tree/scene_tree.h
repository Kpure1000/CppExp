#ifndef SCENE_TREE_H
#define SCENE_TREE_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

struct GameObject
{
    GameObject(const std::string &name)
        : name(name)
    {
    }
    std::string name;
};

std::ostream& operator<<(std::ostream& os, const GameObject& obj);

std::ostream& operator<<(std::ostream& os, GameObject&& obj);

struct SceneNode
{

    SceneNode(GameObject *obj, SceneNode *parent) : _obj(obj), _parent(parent) {}

    SceneNode *_parent;
    GameObject *_obj;
    std::vector<std::shared_ptr<SceneNode>> _children;

    SceneNode* child(int index)
    {
        return _children[index].get();
    }

    const SceneNode* child(int index)const
    {
        return _children[index].get();
    }

    SceneNode* operator[](int index);
    const SceneNode* operator[](int index) const;

    inline bool has_child() const 
    {
        return !_children.empty();
    }

    inline int children_size() const 
    {
        return _children.size();
    }

    

    void add_child(GameObject *obj);

    void removeChildren();

    using VisitorFn = std::function<bool(SceneNode *)>;
    /**
     * recursive visitor
     */
    bool childrenVisitor(VisitorFn const &visitor) const;
    /**
     * iterative visitor
     */
    void childrenVisitor_it(VisitorFn const &visitor) const;
    void parentsVisitor(VisitorFn const &visitor);

};

struct SceneTree
{
    SceneTree() : _root(std::make_shared<SceneNode>(new GameObject("R"), nullptr)) {}

    using FoundFn = std::function<bool(SceneNode *target)>;
    SceneNode *find(FoundFn const& foundFn);
    SceneNode *find(GameObject *target);
    void remove(SceneNode* node);

    std::shared_ptr<SceneNode> _root;
};

#endif