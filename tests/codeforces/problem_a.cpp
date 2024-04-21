#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>


void dfs(int i, int &c, std::vector<std::vector<int>> &nodes, std::vector<bool> &used, std::vector<std::vector<int>> & ret)
{
    if (used[i]){
        return;
    }
    used[i] = 1;
    ret[i][0] = c;
    int n=nodes[i].size();
    for (int j=0;j<n;j++){
        if (used[nodes[i][j]])
            { continue;}
        dfs(nodes[i][j],c,nodes,used,ret);
        c++;
    }
    if (n>1 ||i==0){
        c --;
        ret[i][1]=c;
    }

}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> nodes(n, std::vector<int>(0));
    for (int i=0;i<n-1;i++){
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        nodes[u].push_back(v);
        nodes[v].push_back(u);
    };
    int cur=1;
    std::vector<bool> used(n, 0);
    std::vector<std::vector<int>> ret(n, std::vector<int>(2));
    dfs(0,cur,nodes,used,ret);
    for (int i=0;i<n;i++){
        std::cout << ret[i][0] << " " << ret[i][1] << std::endl;
    }
    return 0;
}