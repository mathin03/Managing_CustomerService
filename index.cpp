#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <array>
#include <utility>
#include <algorithm>

using namespace std;

// Queue for Handling Incoming Requests
queue<string> incoming_requests;

void add_request(const string& request) {
    incoming_requests.push(request);
}

string get_next_request() {
    if (incoming_requests.empty()) return "No requests.";
    string next_request = incoming_requests.front();
    incoming_requests.pop();
    return next_request;
}

// Priority Queue (Heap) for High-Priority Requests
priority_queue<pair<int, string>> priority_requests;

void add_priority_request(int priority, const string& request) {
    priority_requests.push({priority, request});
}

string get_next_priority_request() {
    if (priority_requests.empty()) return "No high-priority requests.";
    string next_request = priority_requests.top().second;
    priority_requests.pop();
    return next_request;
}

// Stack for Revisiting Recently Resolved Requests
stack<string> resolved_requests_stack;

void add_resolved_request(const string& request) {
    resolved_requests_stack.push(request);
}

string revisit_last_resolved_request() {
    if (resolved_requests_stack.empty()) return "No resolved requests to revisit.";
    string last_resolved_request = resolved_requests_stack.top();
    resolved_requests_stack.pop();
    return last_resolved_request;
}

// Linked List for Maintaining a History of All Requests
struct Node {
    string data;
    Node* next;
    Node(const string& request) : data(request), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList() : head(nullptr) {}
    void append(const string& request) {
        Node* new_node = new Node(request);
        if (!head) head = new_node;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = new_node;
        }
    }
    void display() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
private:
    Node* head;
};

LinkedList request_history;

void add_to_history(const string& request) {
    request_history.append(request);
}

// Array for Storing Predefined Common Responses
array<string, 4> common_responses = {
    "Please restart your device.",
    "Ensure your software is up to date.",
    "Check your internet connection.",
    "Try clearing your browser cache."
};

string get_common_response(int index) {
    if (index >= 0 && index < common_responses.size()) return common_responses[index];
    return "No common response found.";
}

// Tree for Categorizing Requests
class TreeNode {
public:
    string category;
    vector<TreeNode*> subcategories;
    vector<string> requests;
    TreeNode(const string& category) : category(category) {}
    void add_subcategory(TreeNode* subcategory) {
        subcategories.push_back(subcategory);
    }
    void add_request(const string& request) {
        requests.push_back(request);
    }
    void display(int level = 0) const {
        string indent(level * 4, ' ');
        cout << indent << category << endl;
        for (const auto& request : requests) {
            cout << indent << "  - " << request << endl;
        }
        for (const auto& subcategory : subcategories) {
            subcategory->display(level + 1);
        }
    }
};

TreeNode root_category("Root");

void add_category(TreeNode* parent_category, TreeNode* subcategory) {
    parent_category->add_subcategory(subcategory);
}

void add_request_to_category(TreeNode* category, const string& request) {
    category->add_request(request);
}

// Example Usage
int main() {
    
    // Adding requests
    add_request("Request 1");
    add_request("Request 2");
    add_priority_request(1, "Urgent Request 1");
    add_resolved_request("Resolved Request 1");
    add_to_history("Request 1");
    add_to_history("Request 2");

    // Categorizing requests
    TreeNode* tech_support = new TreeNode("Tech Support");
    TreeNode* billing = new TreeNode("Billing");
    add_category(&root_category, tech_support);
    add_category(&root_category, billing);
    add_request_to_category(tech_support, "Tech Issue 1");
    add_request_to_category(billing, "Billing Issue 1");

    // Displaying categorized requests
    root_category.display();

    // Getting next request and common response
    string next_request = get_next_request();
    string common_response = get_common_response(0);

    cout << "Next request: " << next_request << endl;
    cout << "Common response: " << common_response << endl;

    return 0;
}
