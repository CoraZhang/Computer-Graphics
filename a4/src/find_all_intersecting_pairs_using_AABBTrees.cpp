#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a p_listueue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> p_list;
  if (box_box_intersect(rootA->box, rootB->box)) {
    p_list.emplace_back(rootA, rootB);
  }

  while (!p_list.empty()) {
    std::shared_ptr<Object> node1 = p_list.front().first;
    std::shared_ptr<Object> node2 = p_list.front().second;
    p_list.pop_front();

    auto node1_ptr = std::dynamic_pointer_cast<AABBTree> (node1);
    auto node2_ptr = std::dynamic_pointer_cast<AABBTree> (node2);

    if (!node1_ptr && !node2_ptr) {
      leaf_pairs.emplace_back(std::make_pair(node1, node2));
    } else if (!node1_ptr) {
      if ((node2_ptr->left != nullptr) && (box_box_intersect(node1->box, node2_ptr->left->box))) {
        p_list.emplace_back(node1, node2_ptr->left);
      }
      if ((node2_ptr->right != nullptr) && (box_box_intersect(node1->box, node2_ptr->right->box))) {
        p_list.emplace_back(node1, node2_ptr->right);
      }
    } else if (!node2_ptr) {
      if ((node1_ptr->left != nullptr) && (box_box_intersect(node1_ptr->left->box, node2->box))) {
        p_list.emplace_back(node1_ptr->left, node2);
      }
      if ((node1_ptr->right != nullptr) && (box_box_intersect(node1_ptr->right->box, node2->box))) {
        p_list.emplace_back(node1_ptr->right, node2);
      }
    } else {
      if ((node1_ptr->left != nullptr) && (node2_ptr->left != nullptr) &&
          (box_box_intersect(node1_ptr->left->box, node2_ptr->left->box))) {
        p_list.emplace_back(node1_ptr->left, node2_ptr->left);
      }
      if ((node1_ptr->left != nullptr) && (node2_ptr->right != nullptr) &&
          (box_box_intersect(node1_ptr->left->box, node2_ptr->right->box))) {
        p_list.emplace_back(node1_ptr->left, node2_ptr->right);
      }
      if ((node1_ptr->right != nullptr) && (node2_ptr->right != nullptr) &&
          (box_box_intersect(node1_ptr->right->box, node2_ptr->right->box))) {
        p_list.emplace_back(node1_ptr->right, node2_ptr->right);
      }
      if ((node1_ptr->right != nullptr) && (node2_ptr->left != nullptr) &&
          (box_box_intersect(node1_ptr->right->box, node2_ptr->left->box))) {
        p_list.emplace_back(node1_ptr->right, node2_ptr->left);
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
