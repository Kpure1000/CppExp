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
    root->_children[0]->add_child(new GameObject("R.A.A"));
    root->_children[0]->_children[0]->add_child(new GameObject("R.A.A.A"));
    root->_children[0]->add_child(new GameObject("R.A.B"));
    root->_children[0]->add_child(new GameObject("R.A.C"));

    root->add_child(new GameObject("R.B"));
    root->_children[1]->add_child(new GameObject("R.B.A"));
    root->_children[1]->add_child(new GameObject("R.B.B"));
    root->_children[1]->add_child(new GameObject("R.B.C"));
    root->_children[1]->_children[2]->add_child(new GameObject("R.B.C.A"));
    root->_children[1]->add_child(new GameObject("R.B.D"));
    
    root->add_child(new GameObject("R.C"));
    root->_children[2]->add_child(new GameObject("R.C.A"));
    root->_children[2]->add_child(new GameObject("R.C.B"));
    root->_children[2]->add_child(new GameObject("R.C.C"));

    SceneNode* cur;

    int count = 0;
    root->childrenVisitor_it([&](SceneNode *node)
    {
        std::cout << *(node->_obj) << std::endl;
        count++;
        if (node->_obj->name == "R.B.B")
        {
            cur = node;
        }
        return true;
    });

    std::cout << "nodes count: " << count <<std::endl;

    cur->_parent->childrenVisitor_it([&](SceneNode *node)
    {
        std::cout << *(node->_obj) << std::endl;
        return true;
    });


    return 0;
}
