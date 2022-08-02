#include <bits/stdc++.h>
using namespace std;


class Solution {
    private:
        int time = 1;                  // discovery time variable, it starts with 1 as discussed above 
        vector<bool> vis;              // visited array
        vector<int> par, disc, low;   // arrays to keep track for parent, discovery time, low values
        map<char,int> id;             //string to int for nodes 
        map<int, char> di;              // int to string 
        int edges = 0;
        int vertices = 0;
        vector<vector<int>> graph;

        
        void printStackTill_UV(stack<pair<int, int>>& , pair<int, int>& ,vector<vector<char>>& , int); //helper function for epmtying the stach which has been by DFS algorithm 

    public:
        Solution(string );  //Constructor 
        void print_maps();  //helper function used for debuging
        pair<string,int> print_biconnected_component(); //the main function to find biconnected components. it uses DFS to do that.
        void DFS(int , stack<pair<int, int>>& , vector<vector<char>>& , int& );  //recursive DFS 


        


};

pair<string, int> find_components(string );


Solution::Solution(string input){  //takes input string that conatains edges and maps them into numbers and build the graph inorder to run the algorithm on it 
            int c = 0;
            for(int i=0; i<=(int)input.size(); i++){
                char j = input[i];
                if (j == '-'){
                    edges++;
                    if (id.find(char(input[i-1])) == id.end()){
                        id.insert(pair<char, int>(input[i-1], c));
                        di.insert(pair<int, char>(c, input[i-1]));
                        c++;
                    }
                    if (id.find(char(input[i+1])) == id.end()){
                        id.insert(pair<char, int>(input[i+1], c));
                        di.insert(pair<int, char>(c, input[i+1]));
                        c++;
                    }
                }
            }   
            vertices = (int)di.size();
            graph.resize(vertices+1, vector<int>{});
            
            for(int i=0; i<=(int)input.size(); i++){  //Creating the adjacancy list
                char j = input[i];
                if (j == '-'){
                    auto it1= id.find(input[i-1]);
                    auto it2= id.find(input[i+1]);
                    int u = it1->second;
                    int v = it2->second;
                    graph[u].push_back(v);
                    graph[v].push_back(u);
                }  
            }

}

void Solution::printStackTill_UV(stack<pair<int, int>>& st, pair<int, int>& p ,vector<vector<char>>& table, int row){  //emptyes the stack when needed and fills the output vector with the needed biconneceted componenets
                    while(!st.empty()) {
                    auto it1 = di.find(st.top().first);
                    auto it2 = di.find(st.top().second);
                    //check if the node has been added to this row before
                    int flag1 = 0;
                    int flag2 = 0;
                    for(int i =0; i<table[row].size(); i++){
                        if (table[row][i] == it1->second){flag1++;}
                        if (table[row][i] == it2->second){flag2++;}
                    }
                    if (flag1 == 0){table[row].push_back(it1->second);} //if it has not been added before then add it
                    if (flag2 == 0){table[row].push_back(it2->second);} //if it has not been added before then add it

                    flag1 =0;
                    flag2 = 0;
                    if(st.top() == p) {
                        st.pop(); //pop the stack 
                        break;
                    }
                    st.pop();
                    }
                    cout << endl;

}

void Solution::print_maps(){ //helper function used only in the development stage and debugging stage to insure the correct mapping between node names and numbers
            map<char, int>::iterator itr;
            for (itr = id.begin(); itr != id.end(); ++itr) {
                cout << '\t' << itr->first << '\t' << itr->second<< '\n';  
            }
            cout<<"-----------"<<endl;
            map<int, char>::iterator itra;
            for (itra = di.begin(); itra != di.end(); ++itra) {
                cout << '\t' << itra->first << '\t' << itra->second<< '\n';  
            }

}

pair<string, int> Solution:: print_biconnected_component(){  //the main functions which implements the algorithm using DFS and other helper functions
                                low.resize(vertices+1, 0);       // mark the low value of each node is 0
                                vis.resize(vertices+1, false);   // mark the visited array as false
                                par.resize(vertices+1, -1);      // mark the parent of each node as -1
                                disc.resize(vertices+1, 0);      // mark the discovery time of each node
                                string cycles;              // string to be returned 
                                int componenets;                 // number of biconnected components to be returned
                                // graph can have multiple components, so we need to go to each node and apply DFS

                                vector<vector<char>> table(vertices+1, vector<char>{});
                                int row = 0;
                                for(int i=1; i<=vertices; i++)
                                {
                                    // if the current is not previously visited
                                    if(vis[i] == false)
                                    {
                                        stack<pair<int, int>> st;    // stack of edges
                                        DFS(i, st, table, row);           // call DFS

                                        // add the final component to the table
                                        
                                        while(!st.empty()) {
                                            auto it1 = di.find(st.top().first);
                                            auto it2 = di.find(st.top().second);
                                            int flag1 = 0;
                                            int flag2 = 0;
                                            for(int i =0; i<table[row].size(); i++){
                                                if (table[row][i] == it1->second){flag1++;}
                                                if (table[row][i] == it2->second){flag2++;}
                                            }
                                            if (flag1 == 0){table[row].push_back(it1->second);}
                                            if (flag2 == 0){table[row].push_back(it2->second);}
                                            
                                            flag1 =0;
                                            flag2 = 0;
                                            st.pop();
                                        }
                                    }
                                }
                                for(int r = table.size()-1; r>row; r--){table.erase(table.begin() + r);} //deleting unused rows
                                componenets = table.size(); // value to returned 

                                for(int r = 0; r <table.size(); r++){ //going through the 2D vector and constructing the strign to be returned
                                    for(int i = 0; i<table[r].size(); i++){cycles.push_back( table[r][i]); cycles.push_back('-');}
                                    cycles.pop_back();
                                    cycles.push_back(' ');
                                }
                                cycles.pop_back();
                                return make_pair(cycles, componenets);


}


void Solution::DFS(int src, stack<pair<int, int>>& st, vector<vector<char>>& table, int& row){
                disc[src] = low[src] = time;     // mark the low time and discovery time
                time++;                          // increment the time
                vis[src] = true;                 // mark visited as true
                int child = 0;                   // varible to keep count of DFS call made from source

                vector<int> nbrs = graph[src];   // iterate over all neighbours
                for(auto& nbr: nbrs)
                {
                    pair<int, int> edge = {src, nbr};   // current edge
                    if(vis[nbr] == false) {             // if the neighbour is not previously visited
                        child += 1;
                        par[nbr] = src;                 // mark the parent
                        st.push(edge);                  // push edge to stack
                        DFS(nbr, st, table, row);            // make DFS call
                        low[src] = min(low[src], low[nbr]);     // update the low time

                        if(par[src] == -1 and child > 1) {      // check for Articulation point, if it's true then add all nodes to the table
                            printStackTill_UV(st, edge, table, row);
                            row++;

                        }

                        if(par[src] != -1 and low[nbr] >= disc[src]) {   // check for Articulation point, if it's true then add all nodes to the table
                            printStackTill_UV(st, edge, table, row);
                            row++;
                        }
                    }
                    else if(par[src] != nbr and disc[nbr] < low[src]) {  // if the neighbour is previously visited
                        low[src] = disc[nbr];       // update the low value
                        st.push(edge);              // push edge to stack
                    }
                }
}


pair<string, int> find_components(string s){ //driver function only
    Solution sol(s);
    pair<string , int> x = sol.print_biconnected_component();
    return x;
}