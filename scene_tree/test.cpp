#include "scene_tree.h"
#include <iostream>
#include <iomanip>

int main(int argc, char const *argv[])
{
    // add
    SceneTree tree;
    tree._root = new SceneNode(new GameObject("R"), nullptr);
    auto root = tree._root;
    
    root->add_child(new GameObject("R.A"));
    (*root)[0]->add_child(new GameObject("R.A.A"));
    (*(*root)[0])[0]->add_child(new GameObject("R.A.A.A"));
    (*root)[0]->add_child(new GameObject("R.A.B"));
    (*root)[0]->add_child(new GameObject("R.A.C"));

    root->add_child(new GameObject("R.B"));
    (*root)[1]->add_child(new GameObject("R.B.A"));
    (*root)[1]->add_child(new GameObject("R.B.B"));
    (*root)[1]->add_child(new GameObject("R.B.C"));
    (*(*root)[1])[2]->add_child(new GameObject("R.B.C.A"));
    (*root)[1]->add_child(new GameObject("R.B.D"));
    
    root->add_child(new GameObject("R.C"));
    (*root)[2]->add_child(new GameObject("R.C.A"));
    (*root)[2]->add_child(new GameObject("R.C.B"));
    (*root)[2]->add_child(new GameObject("R.C.C"));

    SceneNode* cur;

    int count = 0;
    root->childrenVisitor([&](SceneNode *node)
    {
        std::cout << *(node->_obj) << std::endl;
        count++;
        if (node->_obj->name == "R.B")
        {
            cur = node;
        }
        return true;
    });

    std::cout << "nodes count: " << count <<std::endl;

    tree.remove(cur);

    root->childrenVisitor_it([&](SceneNode *node)
    {
        std::cout << *(node->_obj) << std::endl;
        return true;
    });


    return 0;
}
