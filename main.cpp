#include <iostream>
#include "tuple.h"

int main() {

    using f0 = Tuple<
        Tuple<Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>,
        Tuple<Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>,
        Tuple<Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>,
        Tuple<Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>,
        Tuple<Int<0>, Int<0>, Int<0>, Int<0>, Int<1>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>,
        Tuple<Int<0>, Int<0>, Int<1>, Int<0>, Int<1>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>,
        Tuple<Int<0>, Int<0>, Int<0>, Int<1>, Int<1>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>,
        Tuple<Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>,
        Tuple<Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>,
        Tuple<Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>, Int<0>>
        >;
    using f1 = nextIter<f0>;
    using f2 = nextIter<f1>;
    using f3 = nextIter<f2>;
    using f4 = nextIter<f3>;
    f0::print();
    f1::print();
    f2::print();
    f3::print();
    f4::print();
    return 0;
}