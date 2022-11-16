//@author Paul Miller-Schmidt
#include <vector>
#include <math.h> 


/*Sum vector
@brief - sum two vectors of any type.
@param - two vectors of the same type T. 
@return - summed vector of the given type T.
*/
template <class T>
T sum_v(T a, T b) {
    assert(a.size() == b.size());
    T result;
    result.reserve(a.size());
    for(int i=0;i<a.size();i++){
        result.push_back(a[i]+b[i]);
    }
    return result;
};

/* Add constanct vector
@brief - add a constant type T to every element of vector type T.
@param - vector to be added to and constant to add. 
@return - void.
*/
template <class T>
void add_constant_v(std::vector<T> *a, T b) {
    for (int i=0;i<a->size();i++) {a->at(i) += b;};
};  
