#include <fstream>
#include <queue>
#include <vector>

int main(int argc, char** argv)
{
    std::ifstream cin("live.in");
    std::ofstream cout("live.out");

    int p, w;
    cin >> p >> w;
    std::priority_queue<int, std::vector<int>, std::greater<int> > pass;
    std::priority_queue<int, std::vector<int>, std::less<int> > unpass;
    for(int i = 1; i <= p; i++)
    {
        int pass_num = std::max(1, i * w / 100);
        int score;
        cin >> score;
        unpass.push(score);
        if(pass.size() < pass_num)
        {
            int top = unpass.top();
            unpass.pop();
            pass.push(top);
        }
        else
        {
            if(unpass.top() > pass.top())
            {
                int u_top = unpass.top();
                int p_top = pass.top();
                unpass.pop();
                pass.pop();
                unpass.push(p_top);
                pass.push(u_top);
            }
        }
        cout << pass.top() << " ";
    }

    cin.close();
    cout.close();
    return 0;
}