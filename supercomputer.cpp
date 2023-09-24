#include <iostream>

#include <fstream>

#include <vector>

#include <queue>

using namespace std;
int compute(queue < int > q1, queue < int > q2,
 vector < vector < long int >> & graph,
  vector < int > & inDegree, vector < int > & dataSets, int type) {
  queue < int > qaux = q1;
  int rez = 0;
  int ret = 0;
  while (!q1.empty()) {
    int curr = q1.front();

    q1.pop();

    for (int neighbor : graph[curr]) {
      inDegree[neighbor]--;

      if (inDegree[neighbor] == 0) {
        if (dataSets[neighbor] == type) {
          q1.push(neighbor);

        } else {
          q2.push(neighbor);
        }
      }
    }
    if (q1.empty()) {
      if (!q2.empty()) {
        swap(q1, q2);

        if (type == 1)
          type = 2;
        else
          type = 1;
        rez++;
      }
    }
  }

  return rez;
}

int main() {
  ifstream fin("supercomputer.in");

  ofstream fout("supercomputer.out");
  queue < int > q1, q2;
  int N, M;
  int rez = 0;
  int r1 = 0;
  int r2 = 0;
  fin >> N >> M;
  vector < int > dataSets(N + 1, 0);

  for (int i = 1; i <= N; ++i) {
    fin >> dataSets[i];
  }

  vector < vector < long int >> dependencies(N + 1, vector < long int > ());
  vector < int > inDegree(N + 1, 0);
  vector < int > inDegreeaux(N + 1, 0);

  for (int i = 0; i < M; i++) {
    int u, v;
    fin >> u >> v;
    dependencies[u].push_back(v);
    inDegree[v]++;
    inDegreeaux[v]++;
  }
  for (int i = 1; i <= N; i++) {
    if (inDegree[i] == 0) {
      if (dataSets[i] == 1) {
        q1.push(i);
      } else {
        q2.push(i);
      }
    }
  }

  if (!q1.empty() && !q2.empty()) {
    r1 = compute(q1, q2, dependencies, inDegree, dataSets, 1);
    r2 = compute(q2, q1, dependencies, inDegreeaux, dataSets, 2);

    rez = min(r1, r2);
  } else if (q1.empty()) {
    rez = compute(q2, q1, dependencies, inDegree, dataSets, 2);
  } else if (q2.empty()) {
    rez = compute(q1, q2, dependencies, inDegree, dataSets, 1);
  }

  fout << rez << endl;

  return 0;
}
