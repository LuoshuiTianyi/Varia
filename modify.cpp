#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
struct word {
  string zh, ma, lev;
};
word a[200001];
int cnt, ch[26 * 26 * 26 * 26][26];
int bel[26 * 26 * 26 * 26];
bool vis[200001];
string st;
void dfs(int x) {
  int now = bel[x];
  //if (st.size() == 3 && st[0] == 'v' && st[1] == 'r' && st[2] == '')
  if (now) cout << a[now].zh << "\t" << st << "\t" << a[now].lev << endl;
  for (int j = 0; j < 26; j++)
    if (ch[x][j]) {
      st.push_back((char)j + 'a');
      dfs(ch[x][j]);
      st.pop_back();
    }
}
int main() {
  freopen("tmp.txt", "r", stdin);
  freopen("tmp.out", "w", stdout);
  for (int t = 1; t <= 60630; t++) {
    string s;
    getline(cin, s);
    int pos = 0;
    while (s[pos] != '\t') pos++;
    a[t].zh = s.substr(0, pos++);
    int tp = pos;
    while (s[pos] != '\t') pos++;
    a[t].ma = s.substr(tp, pos - tp);
    a[t].lev = s.substr(++pos, 1);
    int now = 0;
    for (int i = 0; i < a[t].ma.size(); i++) {
      int to = a[t].ma[i] - 'a';
      if (!ch[now][to]) ch[now][to] = ++cnt;
      now = ch[now][to];
    }
    if (!bel[now] || a[t].ma) bel[now] = t;
  }
  for (int i = 1; i <= cnt; i++)
    if (!bel[i]) {
      int Min = 1e9;
      for (int j = 0; j < 26; j++) Min = min(Min, ch[i][j]);
      bel[i] = Min;
    }
  for (int i = 1; i <= cnt; i++) vis[bel[i]] = 1;
  for (int i = 1; i <= 60630; i++)
    if (!vis[i]) 
      cout << a[i].zh << "\t" << a[i].ma << "\t1" << endl;
  dfs(0);
}
