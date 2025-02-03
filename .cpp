//@Author - Sarafat

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

// Knapsack-like function to check character variety
int checkVariety(const string &password) {
    int upper = 0, lower = 0, digit = 0, special = 0;
    for (char ch : password) {
        if (isupper(ch)) upper = 1;
        else if (islower(ch)) lower = 1;
        else if (isdigit(ch)) digit = 1;
        else special = 1;
    }
    return upper + lower + digit + special; // Score out of 4
}

// Huffman-like encoding to check entropy
int checkEntropy(const string &password) {
    map<char, int> freq;
    for (char ch : password) freq[ch]++;

    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto &p : freq) pq.push(p.second);

    int entropy = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        entropy += a + b;
        pq.push(a + b);
    }
    return entropy;
}

// DFS-based approach to check character graph connectivity
void dfs(char node, map<char, vector<char>> &graph, set<char> &visited) {
    visited.insert(node);
    for (char neighbor : graph[node]) {
        if (!visited.count(neighbor)) dfs(neighbor, graph, visited);
    }
}

int checkGraphStrength(const string &password) {
    map<char, vector<char>> graph;
    for (int i = 0; i < password.size() - 1; i++) {
        graph[password[i]].push_back(password[i + 1]);
        graph[password[i + 1]].push_back(password[i]);
    }

    set<char> visited;
    dfs(password[0], graph, visited);
    return visited.size(); // More connectivity = stronger password
}

// Main function
int main() {
    string password;

    while (true) {
        cout << "\nEnter password (or type 'exit' to quit): ";
        cin >> password;

        if (password == "exit") {
            cout << "Exiting program.\n";
            break;
        }

    int varietyScore = checkVariety(password);
    int entropyScore = checkEntropy(password);
    int graphScore = checkGraphStrength(password);

    int totalScore = varietyScore + (entropyScore / 5) + (graphScore / 2);

    //To ensure the max score is 20
    if (totalScore > 20) totalScore = 20;

    cout << "\nPassword Strength Score: " << totalScore << "/20\n";
    if (totalScore > 15) cout << "Strength: Strong\n";
    else if (totalScore > 10) cout << "Strength: Medium\n";
    else cout << "Strength: Weak\n";

    }

    return 0;
}
