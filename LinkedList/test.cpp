#include <algorithm>
#include <list>
#include <queue>
#include <functional>
#include <forward_list>
int main()
{
    std::list<int> list;
    std::sort(list.begin(), list.end());
    // list.insert()
    list.remove();
    list.splice();
    list.unique();
    list.emplace();
    std::priority_queue<>;
    std::less<>;
    list.merge();
    auto it = list.begin();
    return 0;
}
