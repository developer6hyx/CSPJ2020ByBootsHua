#include <iostream>

int pass[1000001] = {};
int unpass[1000001] = {};

void sift_down_large(int i, int heap_size)
{
    while(true)
    {
        int left = i << 1;
        int right = (i << 1) + 1;
        int largest = i;
        if(left <= heap_size && unpass[left] > unpass[i])
        {
            largest = left;
        }
        if(right <= heap_size && unpass[right] > unpass[largest])
        {
            largest = right;
        }
        if(largest == i)
        {
            return ;
        }
        else
        {
            std::swap(unpass[i], unpass[largest]);
            i = largest;
        }
    }
}

void sift_down_small(int i, int heap_size)
{
    while(true)
    {
        int left = i << 1;
        int right = (i << 1) + 1;
        int smallest = i;
        if(left <= heap_size && pass[left] < pass[i])
        {
            smallest = left;
        }
        if(right <= heap_size && pass[right] < pass[smallest])
        {
            smallest = right;
        }
        if(smallest == i)
        {
            return ;
        }
        else
        {
            std::swap(pass[smallest], pass[i]);
            i = smallest;
        }
    }
}

void sift_up_large(int i)
{
    while(true)
    {
        if(i == 1)
        {
            return ;
        }
        if(unpass[i] > unpass[(i >> 1)])
        {
            std::swap(unpass[i], unpass[(i >> 1)]);
            i >>= 1;
        }
        else
        {
            return ;
        }
    }
}

void sift_up_small(int i)
{
    while(true)
    {
        if(i == 1)
        {
            return ;
        }
        if(pass[i] < pass[(i >> 1)])
        {
            std::swap(pass[i], pass[(i >> 1)]);
            i >>= 1;
        }
        else
        {
            return ;
        }
    }
}

int main(int argc, char** argv)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m;
    int pass_size = 0, unpass_size = 0;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        int num = std::max(i * m / 100, 1);
        int score;
        std::cin >> score;
        unpass[++unpass_size] = score;
        sift_up_large(unpass_size);
        if(pass_size < num)
        {
            int unpass_top = unpass[1];
            std::swap(unpass[1], unpass[unpass_size]);
            unpass[unpass_size--] = 0;
            sift_down_large(1, unpass_size);
            pass[++pass_size] = unpass_top;
            sift_up_small(pass_size);
        }   
        else
        {
            if(pass[1] < unpass[1])
            {
                std::swap(pass[1], unpass[1]);
                sift_down_small(1, pass_size);
                sift_down_large(1, unpass_size);
            }
        }
        std::cout << pass[1] << " ";
    }
    return 0;
}