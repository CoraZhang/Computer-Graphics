#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (auto& object: objects) {
    insert_box_into_box(object->box, this->box);
  }

  if (num_leaves == 0) {
    this->left = nullptr;
    this->right = nullptr;
  } else if (num_leaves == 1) {
    this->left = objects[0];
    this->right = nullptr;
  } else if (num_leaves == 2) {
    this->left = objects[0];
    this->right = objects[1];
  } else {
    int axis;
    (this->box.max_corner - this->box.min_corner).maxCoeff(&axis);
    double mid = this->box.center()(axis);
    std::vector<std::shared_ptr<Object>> lson, rson;

    for (auto& object: objects) {
      if (object->box.center()(axis) < mid) {
        lson.emplace_back(object);
      } else {
        rson.emplace_back(object);
      }
    }

    if (lson.empty()) {
      lson.emplace_back(rson.back());
      rson.pop_back();
    }
    if (rson.empty()) {
      rson.emplace_back(lson.back());
      lson.pop_back();
    }

    this->left = std::make_shared<AABBTree>(lson, a_depth + 1);
    this->right = std::make_shared<AABBTree>(rson, a_depth + 1);
  }
  ////////////////////////////////////////////////////////////////////////////
}
