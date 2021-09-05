/*#include <vector>
#include <iostream>
#include <algorithm>

auto print = [](auto const& remark, auto const& v) {
    std::cout << remark;
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';
};

int main()
{
    std::vector<int> v{ 2, 4, 2, 0, 5, 10, 7, 3, 7, 1 };

    print("before sort:\t\t", v);

    // insertion sort
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::rotate(std::upper_bound(v.begin(), i, *i), i, i + 1);
    }

    print("after sort:\t\t", v);

    // simple rotation to the left
    //std::rotate(v.begin(), v.begin() + 1, v.end());

    //print("simple rotate left:\t", v);

    // simple rotation to the right
    std::rotate(v.rbegin(), v.rbegin() + 1, v.rbegin() +9 + 1);

    print("simple rotate right:\t", v);
}*/

#include <vector>
#include <iostream>
#include <algorithm>

template <typename t> void move(std::vector<t>& v, size_t oldIndex, size_t newIndex)
{
    { // debug text
        std::cout << "move " << oldIndex << " to " << newIndex << ":";
        for (size_t i = 0; i < v.size(); ++i)
        {
            int n = v[i];
            if (i == oldIndex)
               std::cout << " [" << n << "] ";   
            else
               std::cout << "  " << n << "  ";   
        }
        std::cout << '\n';
    }
    
	if (oldIndex > newIndex)
		std::rotate(v.rend() - oldIndex -1, v.rend() - oldIndex, v.rend() - newIndex);
	else		
		std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 2, v.begin() + newIndex + 1);
    
    { // debug text
        std::cout << "     result:";
        for (size_t i = 0; i < v.size(); ++i)
        {
            int n = v[i];
            if (i == newIndex)
               std::cout << " [" << n << "] ";   
            else
               std::cout << "  " << n << "  ";   
        }
        std::cout << '\n';
        std::cout << '\n';
    }
}
 
int main()
{
    std::vector<int> v{ 3, 4, 5, 6, 7, 8, 9  };  
 
    move(v, 1, 4);
    move(v, 4, 1);
    //move(v, 3, 3);
}
