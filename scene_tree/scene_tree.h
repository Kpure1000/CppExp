#ifndef SCENE_TREE_H
#define SCENE_TREE_H

#include <vector>
#include <unordered_map>
#include <functional>

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
    std::vector<SceneNode *> _children;

    SceneNode* child(int index)
    {
        return _children[index];
    }

    const SceneNode* child(int index)const
    {
        return _children[index];
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
    SceneTree() {}

    using FoundFn = std::function<bool(SceneNode *target)>;
    SceneNode *find(FoundFn const& foundFn);
    SceneNode *find(GameObject *target);
    void remove(SceneNode* node);

    SceneNode *_root;
};

#endif