#include "../array.h"
#include "../ATree.h"
#include "../BTree.h"
#include "../find.h"
#include "../list.h"
#include "../queue.h"
#include "../sort.h"
#include "../stack.h"
#include "../tree.h"

#include <iostream>
#include <queue>

void print(CS::BTree::Node* node) {

    std::queue<CS::BTree::Node*> que;

    while (node != nullptr) {

        int size = node->data.size();

        CS::BTree::Node** tmp = makeLinks(node);

        for (int index = 0; index <= size; ++index)
            que.push(tmp[index]);

        std::cout << "{ ";

        for (int index = 0; index < size; ++index) {

            std::cout << node->data[index] << ' ';

        }

        std::cout << "}" << std::endl;

        node = que.front();
        que.pop();
    }
}

void print(CS::Tree::Node* tmp) {

    if (tmp == nullptr)
        return;

    if (tmp->left != nullptr) print(tmp->left);

    std::cout << tmp->data << ' ';

    if (tmp->right != nullptr) print(tmp->right);
}

void runTest() {

    std::cout << "\n\nBTree\n\n";

    {    
        CS::BTree tree;
        CS::BTree tmp(2);

        tmp.push(50);
        //
        //   50
        //
        print(tmp.data());
        std::cout << "\n============\n" << std::endl;

        tmp.push(60);
        tmp.push(70);
        tmp.push(80);
        tmp.push(90);
        //
        //            70
        //  50 60    |    80 90
        //
        print(tmp.data());
        std::cout << "\n============\n" << std::endl;

        tmp.push(100);
        tmp.push(110);
        tmp.push(120);
        //
        //                70 100
        //  50 60  |  80 90  |  110 120
        //
        print(tmp.data());
        std::cout << "\n============\n" << std::endl;

        tmp.push(81);
        tmp.push(82);
        tmp.push(83);
        //
        //                70 82 100
        //  50 60  |  80 81 | 83 90  |  110 120
        //
        print(tmp.data());
        std::cout << "\n============\n" << std::endl;

        tmp.push(130);
        tmp.push(140);
        tmp.push(150);
        tmp.push(160);
        tmp.push(170);
        tmp.push(180);
        //
        //                      100
        //          70 82         |            130 160
        //  50 60 | 80 81 | 83 90 || 110 120 | 140 150 | 170 180
        //
        print(tmp.data());
        std::cout << "\n============\n" << std::endl;
        std::cout << "\n============\n" << std::endl;

        tmp.erase(110);
        //                      
        //        70      82      100                160
        //  50 60 | 80 81 | 83 90 |  120 130 140 150 | 170 180
        //
        print(tmp.data());
        std::cout << "\n============\n" << std::endl;

        tmp.erase(100);
        //                      
        //        70      82      120           160
        //  50 60 | 80 81 | 83 90 | 130 140 150 | 170 180
        //
        print(tmp.data());
        std::cout << "\n============\n" << std::endl;

        tmp.erase(50);
        //                      
        //               82      120           160
        //   60 70 80 81 | 83 90 | 130 140 150 | 170 180
        //
        print(tmp.data());
        std::cout << "\n============\n" << std::endl;

        tmp.erase(180);
        //                      
        //               82      120         150  
        //   60 70 80 81 | 83 90 | 130 140  | 160 170 
        //
        print(tmp.data());
        std::cout << "\n============\n" << std::endl;            
    }

    std::cout << "\n\narray\n\n";

    {    
        CS::Array arr;
        arr.push_back(1);
        arr.push_back(2);
        arr.push_back(3);
        arr.push_back(4);

        for (int index = 0; index < array_size; ++index) {

            std::cout << arr[index] << ' ';

        }

        std::cout << std::endl;
        std::cout << "push 6,7,8" << std::endl;
        arr.push_back(6);
        arr.push_back(7);
        arr.push_back(8);

        for (int index = 0; index < array_size; ++index) {

            std::cout << arr[index] << ' ';

        }

        std::cout << std::endl;
        std::cout << "erase 4 index 3" << std::endl;
        arr.erase(3);

        for (int index = 0; index < array_size; ++index) {

            std::cout << arr[index] << ' ';

        }

        std::cout << std::endl;
        std::cout << "insert(3,4)" << std::endl;
        arr.insert(3, 4);

        for (int index = 0; index < array_size; ++index) {

            std::cout << arr[index] << ' ';

        }

        std::cout << std::endl;
        std::cout << "push 9.10,11,12" << std::endl;
        arr.push_back(9);
        arr.push_back(10);
        arr.push_back(11);
        arr.push_back(12);

        for (int index = 0; index < array_size; ++index) {

            std::cout << arr[index] << ' ';

        }

        std::cout << std::endl;
        std::cout << "min = " << arr.min() << std::endl;
        std::cout << "max = " << arr.max() << std::endl;

        std::cout << std::endl;
        std::cout << "find 7 " << arr.find(7) << std::endl;
        std::cout << "arr[find 7] " << arr[arr.find(7)] << std::endl;
        std::cout << "find 22 " << arr.find(22) << std::endl;    
    }

    std::cout << "\n\narray + buff\n\n";

    {    
        CS::Array arr(25);

        for (int index = 0; index < 25; ++index) {

            arr.push_back(index + 1);

        }

        for (int index = 0; index < 25; ++index) {

            std::cout << arr[index] << ' ';

        }    
    }

    std::cout << "\n\nforward_list\n\n";

    {
        CS::forward_list list;

        std::cout << "push 3,5,6,7,8" << std::endl;

        list.push_back(3);
        list.push_back(5);
        list.push_back(6);
        list.push_back(7);
        list.push_back(8);

        for (CS::forward_list::Node* node = list.find(3); node != nullptr; node = node->next)
            std::cout << node->data << ' ';

        std::cout << std::endl;

        std::cout << "insert(5,4)(5,9)(6,12)" << std::endl;

        list.insert(list.find(5), 4);
        list.insert(list.find(5), 9);
        list.insert(list.find(6), 12);

        for (CS::forward_list::Node* node = list.find(3); node != nullptr; node = node->next)
            std::cout << node->data << ' ';

        std::cout << std::endl;

        std::cout << "erase 9,12" << std::endl;

        list.erase(list.find(9));
        list.erase(list.find(12));

        for (CS::forward_list::Node* node = list.find(3); node != nullptr; node = node->next)
            std::cout << node->data << ' ';

        std::cout << std::endl;

        std::cout << "addfront 2,1" << std::endl;

        list.addFront(2);
        list.addFront(1);

        for (CS::forward_list::Node* node = list.find(1); node != nullptr; node = node->next)
            std::cout << node->data << ' ';

        std::cout << std::endl;
    }

    std::cout << "\n\nList\n\n";

    {
        CS::List list;

        std::cout << "push 3,5,6,7,8" << std::endl;

        list.push_back(3);
        list.push_back(5);
        list.push_back(6);
        list.push_back(7);
        list.push_back(8);

        for (CS::List::Node* node = list.find(3); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';

        std::cout << std::endl;

        std::cout << "insert(5,4)(5,9)(6,12)" << std::endl;

        list.insert(list.find(5), 4);
        list.insert(list.find(5), 9);
        list.insert(list.find(6), 12);

        for (CS::List::Node* node = list.find(3); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';

        std::cout << std::endl;

        std::cout << "erase 9,12" << std::endl;

        list.erase(list.find(9));
        list.erase(list.find(12));

        for (CS::List::Node* node = list.find(3); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';

        std::cout << std::endl;

        std::cout << "addfront 2,1" << std::endl;

        list.addFront(2);
        list.addFront(1);

        for (CS::List::Node* node = list.find(1); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';

        std::cout << std::endl;

        std::cout << "addend 9 10 11" << std::endl;

        list.addEnd(9);
        list.addEnd(10);
        list.addEnd(11);

        for (CS::List::Node* node = list.find(1); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';

        std::cout << std::endl;
    }

    std::cout << "\n\ncoppy forward list\n\n";

    {
        CS::forward_list FBasa;
        for (int index = 1; index < 10; ++index) FBasa.push_back(index);

        for (CS::forward_list::Node* node = FBasa.find(1); node != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        std::cout << "coppy in empty" << std::endl;
        CS::forward_list FEmpty;

        FBasa.coppy(FBasa.front(), FEmpty.front());

        for (CS::forward_list::Node* node = FBasa.find(1); node != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        for (CS::forward_list::Node* node = FEmpty.find(1); node != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        std::cout << "coppy in not empty" << std::endl;
        CS::forward_list FNEmpty;

        for (int index = 22; index < 44; ++index) FNEmpty.push_back(index);

        for (CS::forward_list::Node* node = FNEmpty.find(22); node != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        ////remark
        //std::cout << "remark " << FNEmpty.find(43)->data << std::endl;

        FBasa.coppy(FBasa.front(), FNEmpty.front());

        ////remark wait wrong acces
        //std::cout << "remark " << FNEmpty.find(43)->data << std::endl;

        for (CS::forward_list::Node* node = FBasa.find(1); node != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        for (CS::forward_list::Node* node = FNEmpty.find(1); node != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;
    }

    std::cout << "\n\ncoppy List\n\n";

    {
        CS::List FBasa;
        for (int index = 1; index < 10; ++index) FBasa.push_back(index);

        for (CS::List::Node* node = FBasa.find(1); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        std::cout << "coppy in empty" << std::endl;
        CS::List FEmpty;

        FBasa.coppy(FBasa.front(), FEmpty.front());

        for (CS::List::Node* node = FBasa.find(1); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        for (CS::List::Node* node = FEmpty.find(1); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        std::cout << "coppy in not empty" << std::endl;
        CS::List FNEmpty;

        for (int index = 22; index < 44; ++index) FNEmpty.push_back(index);

        for (CS::List::Node* node = FNEmpty.find(22); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        ////remark
        //std::cout << "remark " << FNEmpty.find(43)->data << std::endl;

        FBasa.coppy(FBasa.front(), FNEmpty.front());

        ////remark wait wrong acces
        //std::cout << "remark " << FNEmpty.find(43)->data << std::endl;

        for (CS::List::Node* node = FBasa.find(1); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;

        for (CS::List::Node* node = FNEmpty.find(1); node->next != nullptr; node = node->next)
            std::cout << node->data << ' ';
        std::cout << std::endl;
    }

    std::cout << "\n\nstack\n\n";

    {
        CS::Stack tmp;

        std::cout << "push 1 2 3 4 5 6 7 8 9" << std::endl;

        for (int index = 1; index < 10; ++index)
            tmp.push(index);

        std::cout << "top() " << tmp.top() << std::endl;
        std::cout << "size  " << tmp.size() << std::endl;

        for (int index = 1; index < 10; ++index)
            std::cout << tmp.pop() << ' ';

        std::cout << std::endl;

        std::cout << "top() " << tmp.top() << std::endl;
        std::cout << "size  " << tmp.size() << std::endl;
    }

    std::cout << "\n\nqueue\n\n";

    {
        CS::Queue tmp;

        std::cout << "push 1 2 3 4 5 6 7 8 9" << std::endl;

        for (int index = 1; index < 10; ++index)
            tmp.push(index);

        std::cout << "top() " << tmp.front() << std::endl;
        std::cout << "size  " << tmp.size() << std::endl;

        for (int index = 1; index < 10; ++index)
            std::cout << tmp.pop() << ' ';

        std::cout << std::endl;

        std::cout << "top() " << tmp.front() << std::endl;
        std::cout << "size  " << tmp.size() << std::endl;
    }

    std::cout << "\n\nsort\n\n";

    {
        CS::Array tmp(10);

        tmp.push_back(2);
        tmp.push_back(1);

        for (int index = 0; index < 10; ++index) {

            std::cout << tmp[index] << ' ';

        }

        std::cout << std::endl;

        CS::Array scratch(10);

        CS::mergeSort(tmp.front(), tmp.back(), scratch.front());

        for (int index = 0; index < 10; ++index) {

            std::cout << tmp[index] << ' ';

        }

        std::cout << std::endl;
    }

    std::cout << "\n\nfind\n\n";

    {
        int tmp[10] = { 1,2,3,4,5,6,7,8,9,10 };

        for (int index = 0; index < 10; ++index) std::cout << tmp[index] << ' ';
        std::cout << std::endl;

        int* val = CS::bSearch(tmp, tmp + 9, 10);
        *val = 111;

        for (int index = 0; index < 10; ++index) std::cout << tmp[index] << ' ';
        std::cout << std::endl;
    }

    std::cout << "\n\nATree\n\n";

    {
        CS::ATree tmp;

        //push

        tmp.push(10);
        tmp.push(20);
        tmp.push(30); //RR

        tmp.push(29);
        tmp.push(31);
        tmp.push(28); //RL

        tmp.push(9);
        tmp.push(0); //LL

        tmp.push(21);
        tmp.push(22);
        tmp.push(23); //LR

        tmp.erase(23);
        tmp.erase(32);
        tmp.erase(30);
        tmp.erase(22);
    }

    std::cout << "\n\ntree transfer\n\n";

    {
        CS::Tree tree;
        tree.push(1);
        tree.push(20);
        tree.push(2);
        tree.push(19);
        tree.push(3);
        tree.push(18);
        tree.push(4);
        tree.push(17);
        tree.push(5);
        tree.push(16);
        tree.push(6);
        tree.push(15);
        tree.push(7);
        tree.push(14);
        tree.push(8);
        tree.push(13);
        tree.push(9);
        tree.push(12);
        tree.push(10);
        tree.push(11);

        CS::traversePreOrder(tree.data(), [](CS::Tree::Node* node) -> bool {std::cout << node->data << ' '; return true; });

        std::cout << std::endl;

        CS::traverseInOrder(tree.data(), [](CS::Tree::Node* node) -> bool {std::cout << node->data << ' '; return true; });

        std::cout << std::endl;

        CS::traversePostOrder(tree.data(), [](CS::Tree::Node* node) -> bool {std::cout << node->data << ' '; return true; });

        std::cout << std::endl;
    }

}