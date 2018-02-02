#include <iostream>
#include <functional>

template <typename F>
struct c;

template <typename Return, typename Arg>
struct c<std::function<Return(Arg)>> {
	using type = std::function<Return(Arg)>;
	const type result;
	c(type fun) : result(fun) {}
};


// recursive specialization for functions with more arguments
template <typename Return, typename Arg, typename...Args>
struct c<std::function<Return(Arg, Args...)>> {
	using remaining_type = typename c<std::function<Return(Args...)>>::type;
	using type = std::function<remaining_type(Arg)>;
	const type result;

	c(std::function<Return(Arg, Args...)> fun): result (
		[=](const Arg& a) {
			return c<std::function<Return(Args...)>>(
				[=](const Args&...args){ 
					return fun(a, args...); 
				}
			).result;
		}
	) {}
};


template <typename Return, typename...Args>
auto curry(const std::function<Return(Args...)> fun) -> typename c<std::function<Return(Args...)>>::type
{
    return c<std::function<Return(Args...)>>(fun).result;
}

template <typename Return, typename...Args>
auto curry(Return(* const fun)(Args...)) -> typename c<std::function<Return(Args...)>>::type
{
    return c<std::function<Return(Args...)>>(fun).result;
}

int f(int a, int b, int c) {
	return a + b + c;
}

int main() {
	std::cout << curry(f)(1)(2)(3) << std::endl;
	return 0;
}
