#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstdlib>

typedef long long ll;

ll operators[1000001] = {};
ll result[1000001] = {};
ll left[1000001] = {};
ll right[1000001] = {};
ll will_change[1000001] = {};
ll number[1000001] = {};

void update(ll node)
{
    if(operators[node] == -1)
    {
        return ;
    }
    if(operators[node] == 0)
    {
        result[node] = !result[left[node]];
    }
    if(operators[node] == 1)
    {
        result[node] = result[left[node]] & result[right[node]];
    }
    if(operators[node] == 2)
    {
        result[node] = result[left[node]] | result[right[node]];
    }
    return ;
}

void dfs(ll node)
{
    if(left[node])
    {
        dfs(left[node]);
    }
    if(right[node])
    {
        dfs(right[node]);
    }
    update(node);
}

void check_change(ll node)
{
    if(operators[node] == -1)
    {
        will_change[node] = true;
        return ;
    }
    if(operators[node] == 0)
    {
        check_change(left[node]);
    }
    if(operators[node] == 1)
    {
        if(result[left[node]] == 1 && result[right[node]] == 1)
        {
            check_change(left[node]);
            check_change(right[node]);
        }
        if(result[left[node]] == 0 && result[right[node]] == 1)
        {
            check_change(left[node]);
        }
        if(result[left[node]] == 1 && result[right[node]] == 0)
        {
            check_change(right[node]);
        }
    }
    if(operators[node] == 2)
    {
        if(result[left[node]] == 0 && result[right[node]] == 0)
        {
            check_change(left[node]);
            check_change(right[node]);
        }
        if(result[left[node]] == 1 && result[right[node]] == 0)
        {
            check_change(left[node]);
        }
        if(result[left[node]] == 0 && result[right[node]] == 1)
        {
            check_change(right[node]);
        }
    }
}

int main(int argc, char** argv)
{
    std::ifstream cin("expr.in");
    std::ofstream cout("expr.out");

    std::string expression, str;
    std::getline(cin, expression);
    std::istringstream iss(expression);
    std::stack<ll> stack;
    ll root = 0;
    while(iss >> str)
    {
        if(str[0] == 'x')
        {
            root++;
            number[atoi(str.c_str() + 1)] = root;
            operators[root] = -1;
            stack.push(root);
        }
        if(str[0] == '!')
        {
            root++;
            operators[root] = 0;
            left[root] = stack.top();
            stack.pop();
            stack.push(root);
        }
        if(str[0] == '&')
        {
            root++;
            operators[root] = 1;
            right[root] = stack.top();
            stack.pop();
            left[root] = stack.top();
            stack.pop();
            stack.push(root);
        }
        if(str[0] == '|')
        {
            root++;
            operators[root] = 2;
            right[root] = stack.top();
            stack.pop();
            left[root] = stack.top();
            stack.pop();
            stack.push(root);
        }
    }
    ll n;
    cin >> n;
    for(ll i = 1; i <= n; i++)
    {
        cin >> result[number[i]];
    }
    dfs(root);
    check_change(root);
    ll answer = result[root];
    ll questions;
    cin >> questions;
    for(ll i = 1; i <= questions; i++)
    {
        ll change_node;
        cin >> change_node;
        if(will_change[number[change_node]])
        {
            cout << (1 ^ answer) << "\n";
        }
        else
        {
            cout << answer << "\n";
        }
        
    }

    cin.close();
    cout.close();
    return 0;
}
