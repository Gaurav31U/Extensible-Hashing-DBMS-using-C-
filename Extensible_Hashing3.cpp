// Arthor - Name - Gaurav Kumar
//        - Roll No. - 20074013
//        - Program - IDD 5th semester
// -Implementation of extensible Hashing using c++ stl

#include <bits/stdc++.h>
using namespace std;
#define all(a) a.begin(), a.end()

unordered_map<string,string> dir;
unordered_map<string, vector<int>> bucket;
int Global;
string hashfun(int n, int len = Global)
{
    string ans = "";
    for (int i = 0; i < len; i++)
    {
        if (n & 1)
            ans += "1";
        else
            ans += "0";
        n >>= 1;
    }
    reverse(all(ans));
    return ans;
}
void intialize(int N, unordered_map<string,string> &temp)
{
    Global = N;
    for (int i = 0; i < (1 << N); i++)
    {
        string s = hashfun(i);
        temp[s] = s;
    }
}
void splitbucket(string s, string h)
{
    vector<int> res;
    // res.push_back(val);
    for (auto it : bucket[h])
        res.push_back(it);
    // cout<<"Bucket splitting\n";
    bucket.erase(h);
    string s1 = "0" + h;
    string s2 = "1" + h;
    int n = h.size() + 1;
    for (auto it : res)
        bucket[hashfun(it, n)].push_back(it);
    for (auto it = dir.begin(); it != dir.end(); it++)
    { ////
        if ((it->first).substr(Global - n, n) == s1)
            it->second = s1;
        if ((it->first).substr(Global - n, n) == s2)
            it->second = s2;
    }
}
void expansion(string s)
{
    Global++;
    int n = s.size();
    vector<int> res;
    // res.push_back(val);
    for (auto it : bucket[s])
        res.push_back(it);
    bucket.erase(s);
    unordered_map<string,string> temp;
    intialize(Global, temp);
    for (auto it : res)
        bucket[hashfun(it)].push_back(it);
    for (auto it = temp.begin(); it != temp.end(); it++)
    { ////
        if ((it->first).substr(Global - n, n) == s)
            continue;
        it->second = dir[(it->first).substr(Global - n, n)];
    }
    dir = temp;
}
void shrink()
{
    Global--;
    unordered_map<string,string> temp;
    // intialize(Global,temp);
    for (auto it : dir)
        temp[it.first.substr(1, Global)] = it.second;
    dir = temp;
    if(bucket.size()< (1<<(Global-1)))
        shrink();
}
bool search(int val)
{
    string s = dir[hashfun(val)];
    auto v = bucket[s];
    for (auto it : v)
        if (it == val)
            return true;
    return false;
}
void drop(string s, string h)
{
    string s1 = "0" + h.substr(1, h.size() - 1);
    string s2 = "1" + h.substr(1, h.size() - 1);
    string temp=h.substr(1, h.size() - 2);
    string res = h.substr(1, h.size() - 1);
    vector<int> ans;
    for (auto it : bucket[s1])
        ans.push_back(it);
    for (auto it : bucket[s2])
        ans.push_back(it);
    bucket.erase(s1);
    bucket.erase(s2);
    for (auto it : ans)
        bucket[res].push_back(it);
    for (auto it = dir.begin(); it != dir.end(); it++)
        if (it->second == s1 || it->second == s2)
            it->second = res;

    int maxlocal = 0;
    for (auto it : dir)
        if (it.second.size() > maxlocal)
            maxlocal = it.second.size();
    unordered_map<string, int> mp;
    for (auto it : dir)
        if (it.second.size() == maxlocal)
            mp[it.second]++;
    if (mp.size() == 2 && mp[s1] && mp[s2])
        shrink();
    if (maxlocal == (Global - 1))
        shrink();
    if(bucket.find(temp)==bucket.end() && temp.size()>=1)
        drop(s,res);
    
}
void insert(int val)
{
    if(search(val)){
        cout<<"Element already exists..\n";
    }
    string s = hashfun(val);
    string h = dir[s];
    if (bucket[h].size() == 2)
    {
        if (h.size() == s.size()) // comparing local depth and global depth
            expansion(h);
        else
            splitbucket(s, h);
        insert(val);
    }
    else
    {
        bucket[h].push_back(val);
        // values.push_back(val);
    }
}

void remove(int val)
{
    if (search(val) == 0)
    {
        cout << "Element Doesn't Exists...\n";
        return;
    }
    string s = hashfun(val);
    string h = dir[s];

    if (bucket[h].back() == val)
        bucket[h].pop_back();
    else
    {
        int temp = bucket[h].back();
        bucket[h].clear();
        bucket[h].push_back(temp);
    }
    if (bucket[h].empty())
    {
        drop(s, h);
    }
}
void showall()
{
    cout << "Global Depth = " << Global << "\n";
    cout << "Number of Buckets = " << bucket.size() << "\n";
    for (auto it : dir)
    {
        if (bucket.find(it.second) != bucket.end())
        {
            cout << it.first << " " << it.second << " -> ";
            for (auto i : bucket[it.second])
                cout << i << " ";
            cout << "\n";
        }
    }
}
signed main()
{
    intialize(1, dir);
    cout << "Command Line:\n";
    cout << "1.Insert Data\n2.Delete Data\n3.Show Data\n0.Exit\n";
    int p;
    cin >> p;
    while (p)
    {
        if (p == 1)
        {
            int val;
            cin >> val;
            insert(val);
        }
        else if (p == 2)
        {
            int val;
            cin >> val;
            remove(val);
        }
        else if (p == 3)
        {
            showall();
        }
        cout << "Next Command:....\n";
        cin >> p;
    }
    return 0;
}