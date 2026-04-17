#include <queue>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct compare {
  bool operator()(ListNode *a, ListNode *b) { return a->val > b->val; }
};

class Solution {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    priority_queue<ListNode *, vector<ListNode *>, compare> pq;

    for (auto l : lists) {
      if (l)
        pq.push(l);
    }

    ListNode *head = new ListNode(0);
    ListNode *tail = head;

    while (!pq.empty()) {
      ListNode *s = pq.top();
      pq.pop();

      tail->next = s;
      tail = tail->next;

      if (s->next) {
        pq.push(s->next);
      }
    }

    return head->next;
  }
};
