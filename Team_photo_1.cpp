// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <vector>

using std::vector;

// @include
template <typename HeightType>
struct Player {
  bool operator<(const Player &that) const {
    return height < that.height;
  }

  HeightType height;
};

template <typename HeightType>
class Team {
 public:
  explicit Team(const vector<HeightType>& height) {
    for (const HeightType& h : height) {
      members_.emplace_back(Player<HeightType>{h});
    }
  }

  bool operator<(const Team &that) const {
    vector<Player<HeightType>> this_sorted(SortHeightMembers());
    vector<Player<HeightType>> that_sorted(that.SortHeightMembers());
    for (int i = 0; i < this_sorted.size() && i < that_sorted.size(); ++i) {
      if (!(this_sorted[i] < that_sorted[i])) {
        return false;
      }
    }
    return true;
  }

 private:
  vector<Player<HeightType>> SortHeightMembers() const {
    vector<Player<HeightType>> sorted_members(members_);
    sort(sorted_members.begin(), sorted_members.end());
    return sorted_members;
  }

  vector<Player<HeightType>> members_;
};
// @exclude

int main(int argc, char *argv[]) {
  vector<int> height(3);
  height[0] = 1, height[1] = 5, height[2] = 4;
  Team<int> t1(height);
  height[0] = 2, height[2] = 3, height[3] = 4;
  Team<int> t2(height);
  assert(!(t1 < t2) && !(t2 < t1));
  height[0] = 0, height[1] = 3, height[2] = 2;
  Team<int> t3(height);
  assert(t3 < t1 && !(t1 < t3) && t3 < t2 && !(t1 < t2));
  return 0;
}