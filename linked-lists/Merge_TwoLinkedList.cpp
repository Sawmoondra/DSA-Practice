#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // dummy node simplifies edge cases (avoids special-casing the head)
        ListNode dummy(0);
        ListNode* tail = &dummy;

        // walk both lists, always attaching the smaller current node
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        // attach whichever list still has leftover nodes
        tail->next = (l1 != nullptr) ? l1 : l2;
        return dummy.next;
    }
};

ListNode* buildList(initializer_list<int> vals) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int v : vals) {
        ListNode* node = new ListNode(v);
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
    }
    return head;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Solution sol;

    // both lists non-empty
    ListNode* a1 = buildList({1, 2, 4});
    ListNode* b1 = buildList({1, 3, 4});
    ListNode* r1 = sol.mergeTwoLists(a1, b1);
    cout << "Merged: ";
    printList(r1); // 1 1 2 3 4 4

    // both empty
    ListNode* a2 = buildList({});
    ListNode* b2 = buildList({});
    ListNode* r2 = sol.mergeTwoLists(a2, b2);
    cout << "Both empty: ";
    printList(r2); // (nothing)

    // one empty
    ListNode* a3 = buildList({});
    ListNode* b3 = buildList({0});
    ListNode* r3 = sol.mergeTwoLists(a3, b3);
    cout << "One empty: ";
    printList(r3); // 0

    return 0;
}
