#include "STL-myList.h"
using std::cout;
using std::endl;

int main()
{
    July::list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);
    lt1.push_back(3);
    lt1.push_back(4);
    lt1.push_back(5);
    lt1.insert(lt1.begin(), 1);
    lt1.insert(lt1.begin(), 2);
    lt1.insert(lt1.begin(), 3);
    lt1.insert(lt1.begin(), 4);
    lt1.insert(lt1.begin(), 5);
    July::list<int>::iterator it1 = lt1.begin();
    while (it1 != lt1.end())
    {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;

    lt1.erase((lt1.end())._node->_prev);
    lt1.erase((lt1.end())._node->_prev);
    lt1.erase((lt1.end())._node->_prev);
    lt1.erase(lt1.begin());
    lt1.erase(lt1.begin());
    lt1.erase(lt1.begin());

    July::list<int>::iterator it2 = lt1.begin();
    while (it2 != lt1.end())
    {
        cout << *it2 << " ";
        ++it2;
    }
    cout << endl;


    return 0;
}
