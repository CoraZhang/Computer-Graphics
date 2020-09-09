#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
typedef std::pair<double, std::shared_ptr<Object>> pi;

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  sqrd = std::numeric_limits<double>::infinity();

  std::priority_queue<pi, std::vector<pi>, std::greater<>> pq;
  double dist = point_box_squared_distance(query, root->box);
  pq.push(std::make_pair(dist, root));

  while (!pq.empty()) {
    pi cur_node = pq.top();
    pq.pop();
    dist = cur_node.first;
    std::shared_ptr<Object> cur_tree = cur_node.second;

    if (dist < sqrd) {
      std::shared_ptr<Object> type_filter = std::dynamic_pointer_cast<AABBTree>(cur_tree);
      if (type_filter == nullptr) {
        double t_sqrd;
        std::shared_ptr<Object> t_desc;
        if (cur_tree->point_squared_distance(query, min_sqrd, max_sqrd, t_sqrd, t_desc)) {
          if (t_sqrd < sqrd) {
            sqrd = t_sqrd;
            descendant = cur_tree;
          }
        }
      } else {
        if (std::static_pointer_cast<AABBTree>(cur_tree)->left != nullptr) {
          pq.push(std::make_pair(point_box_squared_distance(query, std::static_pointer_cast<AABBTree>(cur_tree)->left->box), std::static_pointer_cast<AABBTree>(cur_tree)->left));
        }
        if (std::static_pointer_cast<AABBTree>(cur_tree)->right != nullptr) {
          pq.push(std::make_pair(point_box_squared_distance(query, std::static_pointer_cast<AABBTree>(cur_tree)->right->box), std::static_pointer_cast<AABBTree>(cur_tree)->right));
        }
      }
    }
  }
  
  return sqrd != std::numeric_limits<double>::infinity();
  ////////////////////////////////////////////////////////////////////////////
}