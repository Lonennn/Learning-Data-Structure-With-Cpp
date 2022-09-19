#include <algorithm>
#include <list>
#include <queue>
#include <functional>
#include <forward_list>
int main()
{
    std::list<int> list;
    std::sort(list.begin(), list.end());
    auto it = list.begin();
    return 0;
}
