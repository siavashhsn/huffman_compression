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
};


void c_gen(vector<pic>& v)
{
    stack<tree*> _stack;
    ll i=v.size()-1, sum=0;
    sort(v.begin(), v.end(), greater<pic>());
    while (i>=0) {
        if(!_stack.empty())
        {
            tree* a = _stack.top();
            if(a->root->sum > v[i].first)
            {
                tree* t = new tree();
                sum+=v[i].first;
                node* p = new node(v[i].second, v[i].first);
                i--;
                sum+=v[i].first;
                node* q = new node(v[i].second, v[i].first);
                i--;
                node* pq = new node(p, q, sum);
                t->root = pq;

                _stack.pop();
                node* head = new node(t->root, a->root, sum);
                t->root=head;
                _stack.push(t);
            }
            else
            {
                _stack.pop();
                sum+=v[i].first;
                node* p = new node(v[i].second, v[i].first);
                i--;
                node* q = new node(p, a->root, sum);
                a->root = q;
                _stack.push(a);
            }
        }
        else
        {
            tree* t = new tree();
            sum+=v[i].first;
            node* p = new node(v[i].second, v[i].first);
            i--;
            sum+=v[i].first;
            node* q = new node(v[i].second, v[i].first);
            i--;
            node* pq = new node(p, q, sum);
            t->root=pq;
            _stack.push(t);
        }
    }
    tree* f = _stack.top();
    f->preorder();
    for(auto i:f->cg)
    {
        cout << i.second << " :: " << i.first << endl;
    }
}


void tree::preorder()
{
    node* p = root;
    vector<int> ans;
    stack<node*> s;
    string code;

    while (true)
    {
        while (p != NULL)
        {
            s.push(p);
            ans.push_back(p->c);
            p = p->lc;
            code.push_back('0');
        }
        cg.push_back(make_pair(code, p->c));
        code.pop_back();
        if (!s.empty())
        {
            p = s.top();
            s.pop();
            p = p->rc;
            code.push_back('1');
        }
        else break;
    }
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

    vector<pic> vfreq;
//    multimap<int, node*> m;

    for(auto& i:freq){
//        node* p = new node(i.first, i.second);
//        m.insert(make_pair(i.first,p));
//    }
        vfreq.push_back(make_pair(i.second, i.first));
    }
    c_gen(vfreq);

    return 0;
}
