
#include <iostream>

template <typename Hd, typename Tl>
struct Cons {};

struct Nil {};

template <int N>
struct Int {
    const static int value = N;
};

using MyList = Cons <Int<0>, Cons <Int<1>, Cons <Int<2>, Nil>>>;

template <template <typename> class F, typename List>
struct Map {};

template <template <typename> class F, typename Head, typename Tail>
struct Map <F, Cons<Head, Tail>> {
    using type = Cons <typename F<Head>::type, typename Map<F, Tail>::type>;
};

template <template <typename> class F>
struct Map <F, Nil> {
    using type = Nil;
};

template <typename N>
struct S {
    using type = Int<N::value>;
};

template <template <typename...> class F, typename... Args>
struct Curry {
    template <typename... Rest>
    struct Apply : F <Args..., Rest...> {};
};

template <typename N, typename M>
struct Plus {};

template <int N, int M>
struct Plus <Int<N>, Int<M>> {
    using type = Int<N+M>;
};

template <typename T>
struct Var {
    using type = Var<T>;
};

template <typename X, typename T>
struct Abs {
    using type = Abs<X,T>;
};

template <typename T1, typename T2>
struct App {
    using type = App<T1,T2>;
};

template <typename Fst, typename Snd>
struct Pair {
    using First = Fst;
    using Second = Snd;
};

int main()
{
    using AddOne = Curry<Plus, Int<1>>;
    static_assert(AddOne::Apply<Int<1729>>::type::value == 1730, "1 + 1729 = 1730");

    std::cout << "Original value: " << 1729 << '\n';
    std::cout << "Add one: " << AddOne::Apply<Int<1729>>::type::value << '\n';
}