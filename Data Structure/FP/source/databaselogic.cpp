// #include "bplustree.hpp"

// void test()
// {
//     BPlusTree<int> tree(3);

//     tree.insert(10);
//     tree.insert(20);
//     tree.insert(5);
//     tree.insert(15);
//     tree.insert(25);
//     tree.insert(30);

//     std::cout << "B+ Tree after insertions:" << std::endl;
//     tree.printTree();

//     int searchKey = 15;
//     std::cout << "\nSearching for key " << searchKey << ": " << (tree.search(searchKey) ? "Found" : "Not Found") << std::endl;

//     int lower = 10, upper = 25;
//     std::vector<int> rangeResult = tree.rangeQuery(lower, upper);
//     std::cout << "\nRange query [" << lower << ", " << upper << "]: ";
//     for (int key : rangeResult) {
//         std::cout << key << " ";
//     }
//     std::cout << std::endl;

//     int removeKey = 20;
//     tree.remove(removeKey);
//     std::cout << "\nB+ Tree after removing " << removeKey << ":" << std::endl;
//     tree.printTree();

// }