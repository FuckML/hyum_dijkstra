#include <iostream>
#include<stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <functional>
using namespace std;
const int inf = 98765432;
#define max(a,b) (a>b ? a:b)
#define min(a,b) (a<b ? a:b)

int d_x[4] = { 0, 0, 1, -1 };
int d_y[4] = { 1, -1, 0, 0 };


double D[40001];
bool C[40001];
int R[40001];
int N;
int M;


struct Edge {
  int end;
  double cost;
  Edge(int end, double cost) :end(end), cost(cost) {}
};
struct Check {
  int v;
  int Dist;
  Check(int v, int Dist) : v(v), Dist(Dist) {

  }
  bool operator > (const Check &ch) const {
    return Dist > ch.Dist;
  }
};
vector<Edge> v[40001];
string v_name[40001];
stack<string> st;
void find(int x) {
  if (x == 0) {
    return;
  }
  st.push(v_name[x]);
  find(R[x]);

}
void dijkstra(int s) {
  //memset(D, 0, sizeof(D));
  //memset(C, 0, sizeof(C));
  for (int i = 1; i <= N; i++) {
    D[i] = inf;
  }
  D[s] = 0;
  priority_queue<Check, vector<Check>, greater<Check>> q; // min-heap 구현
  q.push(Check(s, 0));

  for (int i = 1; i <= N; i++) {
    int min_node = -1;
    while (!q.empty()) {
      auto p = q.top();
      int vertex = p.v;
      q.pop();
      if (C[vertex] == false) {
        min_node = vertex;
        break;
      }
    }
    if (min_node == -1) {
      break;
    }
    C[min_node] = true;
    for (int j = 0; j < v[min_node].size(); j++) {
      int next_node = v[min_node][j].end;
      int next_cost = v[min_node][j].cost;
      if (D[next_node] > D[min_node] + next_cost) {
        D[next_node] = D[min_node] + next_cost;
        q.push(Check(next_node, D[next_node]));
        R[next_node] = min_node;
      }
    }
  }
}
#define BUF_SIZE 250
int main() {
  FILE *fp;
  char buf[250];
  fp = fopen("case.txt", "r");
  fgets(buf, BUF_SIZE, fp);
  N = atoi(buf);
  for (int i = 0; i < N; i++) {
    fgets(buf, BUF_SIZE, fp);
    v_name[i] = buf;
  }
  int s, e;
  double weight;
  int start_index = 0;
  int end_index = 0;
  int max_weight = 0;
  while (fscanf(fp,"%d %d %lf",&s, &e, &weight) != EOF) {
    v[s].push_back(Edge(e, weight));
    if (max_weight < weight) {
      max_weight = weight;
      start_index = s;
      end_index = e;
    }
    
  }
  char s_start[250], s_end[250];
  int i_start, i_end;
  //fgets(s_start, BUF_SIZE, stdin);
  //fgets(s_end, BUF_SIZE, stdin);

/*
  for (int i = 0; i < N; i++) {
    if (strcmp(s_start,v_name[i].c_str()) == 0) {
      cout << i << endl;
      i_start = i;
    }
    if (strcmp(s_end, v_name[i].c_str()) == 0) {
      cout << i << endl;
      i_end = i;
    }
  }*/
  cout << start_index << " " << end_index << " " << max_weight << endl;

  cin >> i_start >> i_end;

  dijkstra(i_start);
  find(i_end);

  string path_name;
  printf("최단 경로의 길이 : %lf\n", D[i_end]);
  while (!st.empty()) {
    path_name = st.top();
    st.pop();
    if (st.empty()) {
      cout << path_name;
    } else {
      cout << path_name << "- >";
    }
  }

}