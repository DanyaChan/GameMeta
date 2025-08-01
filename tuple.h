//
// Created by Danila Salnikov on 01.08.25.
//
#pragma once

#include <iostream>

struct True {
    constexpr static bool value = true;
    constexpr static int sum = 1;
    static void print() {
        std::cout << "1";
    };
};

struct False {
    constexpr static bool value = false;
    constexpr static int sum = 0;
    static void print() {
        std::cout << "0";
    };
};

template <int n>
struct Int {
    constexpr static int value = n;
    constexpr static int sum = n;
    static void print() {
        std::cout << n;
    };
};

template <bool cond, typename TrueT, typename FalseT>
struct If {
    using type = TrueT;
};

template <typename TrueT, typename FalseT>
struct If<false, TrueT, FalseT> {
    using type = FalseT;
};

template <typename Head, typename ...Args>
struct Tuple {
    template <typename T>
    using push = Tuple<T, Head, Args...>;

    template <typename T>
    using pushBack = Tuple<Head, Args..., T>;

    using head = Head;

    using pop = Tuple<Args...>;

    using reverse = typename Tuple<Args...>::reverse::template pushBack<Head>;

private:
    template <typename ...Other>
    static auto concatenate_helper(Tuple<Other...>) {
        return Tuple<Head, Args..., Other...>();
    }
public:

    template <typename Other>
    using concatenate = decltype(concatenate_helper(Other()));

    static void print() {
        Head::print();
        pop::print();
    }

    constexpr static int size = 1 + pop::size;

    template <int n>
    struct Get {
        using type = typename pop::template get<n - 1>;
    };
    template <int n, typename SetTo>
    struct Set {
        using type = typename Tuple<Head>::
            template concatenate<typename pop::template set<n - 1, SetTo>>;
    };

    template<>
    struct Get<0> {
        using type = Head;
    };
    template<int n>
    using get = typename Get<n>::type;

    template <typename SetTo>
    struct Set<0, SetTo> {
        using type = Tuple<SetTo, Args...>;
    };
    template<int n, typename SetTo>
    using set = typename Set<n, SetTo>::type;

    constexpr static int sum = Head::sum + pop::sum;
};


template <typename Head>
struct Tuple<Head> {
    template <typename T>
    using push = Tuple<T, Head>;
    template <typename T>
    using pushBack = Tuple<Head, T>;

    using reverse = Tuple;

    static void print() {
        Head::print();
        std::cout << std::endl;
    }

private:
    template <typename ...Other>
    static auto concatenate_helper(Tuple<Other...>) {
        return Tuple<Head, Other...>();
    }
public:

    template <typename Other>
    using concatenate = decltype(concatenate_helper(Other()));

    template <int n>
    struct Get {
        using type = void;
    };
    template <int n, typename SetTo>
    struct Set {
        using type = void;
    };

    template<>
    struct Get<0> {
        using type = Head;
    };
    template<int n>
    using get = typename Get<n>::type;

    template <typename SetTo>
    struct Set<0, SetTo> {
        using type = Tuple<SetTo>;
    };
    template<int n, typename SetTo>
    using set = typename Set<n, SetTo>::type;

    constexpr static int sum = Head::sum;

    constexpr static int size = 1;
};

template <int n, typename T>
struct GetRow {
    using type = typename GetRow<n - 1, T>::type::template push<T>;
    using Ty = T;
};

template <typename T>
struct GetRow<1, T> {
    using type = Tuple<T>;
};

template <int n, int m, typename T>
struct GetField {
    using type = typename GetRow<n, typename GetRow<m, T>::type>::type;
};

// Neighbours num
// 123
// 4*5
// 678

template <typename F, int X, int Y>
struct N1_S {
    constexpr static int w = F::head::size;
    constexpr static int h = F::size;
    using type = typename F::template get<(Y + h - 1) % h>::template get<(X + w - 1) % w>;
};

template <typename F, int X, int Y>
struct N2_S {
    constexpr static int w = F::head::size;
    constexpr static int h = F::size;
    using type = typename F::template get<(Y + h - 1) % h>::template get<X>;
};

template <typename F, int X, int Y>
struct N3_S {
    constexpr static int w = F::head::size;
    constexpr static int h = F::size;
    using type = typename F::template get<(Y + h - 1) % h>::template get<(X + 1) % w>;
};

template <typename F, int X, int Y>
struct N4_S {
    constexpr static int w = F::head::size;
    constexpr static int h = F::size;
    using type = typename F::template get<Y>::template get<(X + w - 1) % w>;
};

template <typename F, int X, int Y>
struct N5_S {
    constexpr static int w = F::head::size;
    constexpr static int h = F::size;
    using type = typename F::template get<Y>::template get<(X + 1) % w>;
};

template <typename F, int X, int Y>
struct N6_S {
    constexpr static int w = F::head::size;
    constexpr static int h = F::size;
    using type = typename F::template get<(Y + 1) % h>::template get<(X + w - 1) % w>;
};

template <typename F, int X, int Y>
struct N7_S {
    constexpr static int w = F::head::size;
    constexpr static int h = F::size;
    using type = typename F::template get<(Y + 1) % h>::template get<X>;
};

template <typename F, int X, int Y>
struct N8_S {
    constexpr static int w = F::head::size;
    constexpr static int h = F::size;
    using type = typename F::template get<(Y + 1) % h>::template get<(X + 1) % w>;
};

template <typename F, int X, int Y>
using n1 = typename N1_S<F, X, Y>::type;
template <typename F, int X, int Y>
using n2 = typename N2_S<F, X, Y>::type;
template <typename F, int X, int Y>
using n3 = typename N3_S<F, X, Y>::type;
template <typename F, int X, int Y>
using n4 = typename N4_S<F, X, Y>::type;
template <typename F, int X, int Y>
using n5 = typename N5_S<F, X, Y>::type;
template <typename F, int X, int Y>
using n6 = typename N6_S<F, X, Y>::type;
template <typename F, int X, int Y>
using n7 = typename N7_S<F, X, Y>::type;
template <typename F, int X, int Y>
using n8 = typename N8_S<F, X, Y>::type;

template <typename F, int X, int Y>
struct GetValue {
    using Neighbours = Tuple<
            n1<F, X, Y>,
            n2<F, X, Y>,
            n3<F, X, Y>,
            n4<F, X, Y>,
            n5<F, X, Y>,
            n6<F, X, Y>,
            n7<F, X, Y>,
            n8<F, X, Y>
        >;

    constexpr static int sum = Neighbours::sum;

    using curRow = typename F::template get<Y>;
    using curVal = typename curRow::template get<X>;

    template <typename Cur, int nbrs>
    struct Value {
    };

    template <int nbrs>
    struct Value<Int<1>, nbrs> {
        using type = typename If<(nbrs == 2 || nbrs == 3), Int<1>, Int<0>>::type;
    };
    template <int nbrs>
    struct Value<Int<0>, nbrs> {
        using type = typename If<(nbrs == 3), Int<1>, Int<0>>::type;
    };

    using value = typename Value<curVal, sum>::type;
};

template <typename F, int X, int Y>
using getValue = typename GetValue<F, X, Y>::value;

template <typename Field>
struct NextIter {
    constexpr static int w = Field::head::size;
    constexpr static int h = Field::size;

    template <int x, int y, typename WalkField>
    struct Walk {
        using curRow = typename WalkField::template get<y>;
        using curVal = typename curRow::template get<x>;
        using assignRow = typename curRow::template set<x,
            getValue<Field, x, y>
        >;
        using assignField = typename WalkField::template set<y, assignRow>;

        using result = typename Walk<x - 1, y, assignField>::result;
    };

    template <int y, typename WalkField>
    struct Walk<0, y, WalkField> {
        using curRow = typename WalkField::template get<y>;
        using curVal = typename curRow::template get<0>;
        using assignRow = typename curRow::template set<0,
        getValue<Field, 0, y>
        >;
        using assignField = typename WalkField::template set<y, assignRow>;

        using result = typename Walk<w - 1, y - 1, assignField>::result;
    };

    template <typename WalkField>
    struct Walk<0, 0, WalkField> {
        using curRow = typename WalkField::template get<0>;
        using curVal = typename curRow::template get<0>;
        using assignRow = typename curRow::template set<0,
            getValue<Field, 0, 0>
        >;
        using assignField = typename WalkField::template set<0, assignRow>;

        using result = assignField;
    };

    using type = typename Walk<w - 1, h - 1, Field>::result;

    static void debug_print() {
        std::cout << w << h << std::endl;
    }
};

template <typename F>
using nextIter = typename NextIter<F>::type;