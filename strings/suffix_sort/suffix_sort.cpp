#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)

using namespace std;

void coloring(const string& s, int* const color) 
{  
  int n = s.length();
  int col[256];
  memset(col, 0, 4 * 256);  
  FOR(i, 0, n)    col[s.at(i)] = 1;
  FOR(i, 1, 256)  col[i] += col[i - 1];
  FOR(i, 0, n)    color[i] = col[s.at(i)] - 1;    
}

int* sort(string& arg)
{
  arg += "$";
  int n = arg.length();
  int* color = new int[n];
  int* fwd = new int[n];
  int* cmp = new int[n];
  int* pos = new int[n];

  FOR(i, 0, n) fwd[i] = i;
  memset(pos, 0, 4 * n);
  memset(cmp, 0, 4 * n);
  memset(color, 0, 4 * n);

  coloring(arg, color);

  for (int step = 1; step < n; step <<= 1) 
  {
    int fstep = step / 2;
    int bstep = n - fstep;

    // sort step
    memset(pos, 0, 4 * n);

    FOR(i, 0, n)  pos[color[i]]++;
    FOR(i, 1, n)  pos[i] += pos[i - 1];
    memcpy(pos + 1, pos, 4 * (n - 1));
    pos[0] = 0;

    memset(cmp, 0, 4 * n);
    FOR(i, 0, n) {
      int fw = (fwd[i] + bstep) % n;
      cmp[pos[color[fw]]++] = fw;
    }
    memcpy(fwd, cmp, 4 * n);
  
    // color step
    int clr = 1;
    memset(cmp, 0, 4 * n);
    for (int i = 1; i != n; ++i) {

      int f = fwd[i];
      int fp = fwd[i - 1];
      int sh = (f + fstep) % n;
      int shp = (fp + fstep) % n;

      if (color[f] == color[fp] && color[sh] == color[shp]) {
        cmp[f] = cmp[fp];
      } else {
        cmp[f] = clr++;
      }
    }
    memcpy(color, cmp, 4 * n);
  }

  delete[] cmp;
  delete[] color;
  return fwd;
}

string suffix(const string& arg, int pos) {
  return arg.substr(pos, arg.length()  - pos);
}

void print(string& s, int* suff) {
  
  FOR(i,1,s.length() + 1)
  {
    cout << suffix(s, suff[i]) << "\n";
  }
  
}

int main() 
{
  int* sf = sort(string("abcdefabcdef"));
  print(string("abcdefabcdef"), sf);
  delete[] sf;
  cout << "Time = ";


  int size = 50000;
  int step = 5;
  char* x = new char[size + 2];
  memset(x, 0, size + 5);
  for (int i = 0; i < size; i++) {
    x[i] = 'a' + (i % 26);
  }
  string s(x);
  //cin >> s;
  int sum = 0;
  for (int i = 0; i < step; i++) {
    int time = clock();
    int* suff = sort(s);
    int res = clock() - time;
    sum += res;
    delete[] suff;
  }
  cout << sum / step << "\n";  
  
  /*cout << "***\n";
  for (int i = 0; i < s.length();  ++i) 
  {
    cout << suffix(s, suff[i]) << "\n";
  }/**/
  
  return 0;
}