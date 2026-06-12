#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};

ListNode* buildList(vector<int> vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* curr = head;
    for (int i = 1; i < vals.size(); i++) {
        curr->next = new ListNode(vals[i]);
        curr = curr->next;
    }
    return head;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Solution sol;

    // 1 -> 2 -> 3 -> 4 -> 5
    ListNode* l1 = buildList({1, 2, 3, 4, 5});
    printList(sol.reverseList(l1)); // expected: 5 -> 4 -> 3 -> 2 -> 1

    // 1 -> 2
    ListNode* l2 = buildList({1, 2});
    printList(sol.reverseList(l2)); // expected: 2 -> 1

    // empty
    printList(sol.reverseList(nullptr)); // expected: (blank)

    return 0;
}