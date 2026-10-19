#include <iostream>
#include <array>
#include <vector>
using namespace std;
namespace {
int N;
struct Node{
    char left, right;
};
array<Node, 26> nodes;
string preorder,inorder,postorder;

void Traversal(const int node) {
    Node& cur = nodes[node];
    preorder += char(node + 'A');
    if(cur.left != '.') Traversal(nodes[node].left - 'A');
    inorder += char(node + 'A');
    if(cur.right != '.') Traversal(nodes[node].right - 'A');
    postorder += char(node + 'A');
}
} // namespace

int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=0;i<N;++i) {
        char node, left, right;
        cin >> node >> left >> right;
        nodes[node - 'A'] = {left, right};
    }
    Traversal(0);
    cout << preorder << '\n';
    cout << inorder << '\n';
    cout << postorder << '\n';
    return 0;
}