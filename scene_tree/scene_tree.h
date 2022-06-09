#include <iostream>
#include <vector>
#include <unordered_map>

struct GameObject
{
    GameObject(const std::string &name)
        : name(name)
    {
    }
    std::string name;
};

std::ostream& operator<<(std::ostream& os, const GameObject& obj)
{
    return os << obj.name;
}

std::ostream& operator<<(std::ostream& os, GameObject&& obj)
{
    return os << obj.name;
}

struct SceneNode
{

    SceneNode(GameObject *obj, SceneNode *root) : _obj(obj), _parent(root) {}

    enum class VisitorType
    {
        SceneNode_Break,
        SceneNode_Continue,
        SceneNode_Recursive
    };

    SceneNode *_parent;
    GameObject *_obj;
    std::vector<SceneNode *> _children;

    void add_child(GameObject *obj);

    VisitorType childrenVisitor(std::function<VisitorType(SceneNode *)> const &visitor);
    void parentsVisitor(std::function<VisitorType(SceneNode *)> const &visitor);
};

struct SceneTree
{
    SceneTree() {}

    SceneNode *find(GameObject *target);

    SceneNode *_root;
};