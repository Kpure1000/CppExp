#include "scene_tree.h"
#include <iostream>
#include <iomanip>

int main(int argc, char const *argv[])
{
    // add
    SceneTree tree;
    auto root = tree._root;
    
    root->add_child(new GameObject("A"));
    (*root)[0]->add_child(new GameObject("A"));
    (*(*root)[0])[0]->add_child(new GameObject("A"));
    (*root)[0]->add_child(new GameObject("B"));
    (*root)[0]->add_child(new GameObject("C"));

    root->add_child(new GameObject("B"));
    (*root)[1]->add_child(new GameObject("A"));
    (*root)[1]->add_child(new GameObject("B"));
    (*root)[1]->add_child(new GameObject("C"));
    (*(*root)[1])[2]->add_child(new GameObject("A"));
    (*(*root)[1])[2]->add_child(new GameObject("B"));
    (*root)[1]->add_child(new GameObject("D"));
    
    root->add_child(new GameObject("C"));
    (*root)[2]->add_child(new GameObject("A"));
    (*root)[2]->add_child(new GameObject("B"));
    (*root)[2]->add_child(new GameObject("C"));

    SceneNode* cur;
    SceneNode* tar;

    // std::cout << "test: visitor\n";

    // root->childrenVisitor_it([&](SceneNode *node)
    // {
    //     std::cout << *(node->_obj) << std::endl;

    //     if (node->_obj->name == "R.B")
    //     {
    //         cur = node;
    //     }
    //     if (node->_obj->name == "R.A.B")
    //     {
    //         tar = node;
    //     }
    //     return true;
    // });

    std::cout << "test: visitorEx\n";

    int degree = 0;

    root->childrenVisitorEx(
        [&](SceneNode *node)
        {
            std::cout << std::setw(degree + 1) << std::setfill(' ') << '-' << *(node->_obj) << ", degree: " << degree << std::endl;
            if(node->has_child())
                degree++;
            return true;
        },
        [&](SceneNode *node)
        {
            if(node->has_child())
                degree--;
            return true;
        }
    );

    // std::cout << "test: move\n";
    // tree.move(cur, tar);
    // root->childrenVisitor_it([&](SceneNode *node)
    // {
    //     std::cout << *(node->_obj) << std::endl;
    //     return true;
    // });

    // std::cout << "\ntest: remove\n";
    // tree.remove(tar);
    // root->childrenVisitor_it([&](SceneNode *node)
    // {
    //     std::cout << *(node->_obj) << std::endl;
    //     return true;
    // });


    return 0;
}
