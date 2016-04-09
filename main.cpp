#include <map>
#include <stack>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, char> pic;
typedef pair<char, int> pci;

class node
{
public:
    ll f;
    char c;
    ll sum;
    node* lc;
    node* rc;
    node(node* lc, node* rc, ll sum) {
        this->sum=sum;
        this->lc=lc;
        this->rc=rc;
        this->c=c;
        this->f=f;
    }
    node(char c, ll f){
        this->c=c;
        this->f=f;
        this->lc = NULL;
        this->rc = NULL;
        this->sum = 0;
    }
};

class tree
{
public:
    node* root;
    void preorder();
    vector<pair<string, char>> cg;
    tree(){ this->root=NULL; }
    tree(node* root){ this->root=root; }
};


void build_t(multimap<ll, tree*>& m, vector<ll>& v)
{
    ll sum=0;
    while(m.size()>1)
    {
        sort(v.begin(), v.end(), greater<ll>());
        ll f = v[v.size()-1];
        auto i = m.find(f)->second;
        sum += f;
        v.pop_back();
        m.erase(m.find(f), m.end());

        f = v[v.size()-1];
        auto j=m.find(f)->second;
        sum += f;
        v.pop_back();
        m.erase(m.find(f), m.end());

        node* p= new node(i->root, j->root, sum);
        tree* ttt = new tree(p);
        m.insert(make_pair(sum, ttt));
        v.push_back(sum);
        sum = 0;
    }
    tree* i = m.begin()->second;
    i->preorder();
}


void tree::preorder()
{
    node* p = root;
    stack<node*> s;
    string code="";

    while (true)
    {
        while (p != NULL)
        {
            s.push(p);
            p = p->lc;
            code.push_back('0');
        }
        cg.push_back(make_pair(code, s.top()->c));
        code.pop_back();
        if (!s.empty())
        {
            p = s.top();
            s.pop();
            p = p->rc;
            if(p!=NULL)
                code.push_back('1');
        }
        else break;
    }
    for(auto& i:cg)
        cout << bitset<4>(i.second) << "--" << i.first << endl;
    delete p;
}



int main()
{
    string fname = "/home/siavash/Desktop/1.txt";
    cout << "File Location: ";
    //cin >> fname;
    ifstream input(fname, ios::binary );
    vector<char> buffer((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));

    map<char, ll> freq;
    for(size_t i=0; i < buffer.size(); i++) {
        char c = buffer[i] & 0b00001111;
        freq[c]++;
        c = buffer[i] >> 4;
        freq[c]++;
    }

    vector<ll> v;
    multimap<ll, tree*> m;
    for(auto& i:freq){
        v.push_back(i.second);
        node* p = new node(i.first, i.second);
        tree* t = new tree(p);
        m.insert(make_pair(i.second,t));
    }

    for(auto& i:m){
        tree* t = i.second;
        cout << i.first << "---" << bitset<4>(t->root->c) << endl;
    }
    build_t(m, v);

    return 0;
}
