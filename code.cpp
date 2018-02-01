#include <iostream>
#include <vector>
#include <functional>

template <typename Collection, typename callable>
Collection map(Collection collection, callable f)
{
	std::transform(collection.begin(), collection.end(), collection.begin(), f);
	return collection;
}

template <typename Collection, typename Predicate>
Collection filter_not(Collection collection, Predicate p)
{
	auto it = std::remove_if(collection.begin(), collection.end(), p);
	collection.erase(it, std::end(collection));
	return collection;
}

template <typename Collection, typename Predicate>
Collection filter(Collection collection, Predicate p)
{
	Collection r (collection.size());
	auto it = std::copy_if(collection.begin(), collection.end(), r.begin(), p);
	r.resize(std::distance(r.begin(), it));
	return r;
}

template <typename Collection, typename Element>
Element head(Collection c)
{
	return c[0];
}

template <typename Collection>
Collection tail(Collection c)
{
	Collection r;
	std::copy(c.begin() + 1, c.end(), std::back_inserter(r));
	return r;
}
int main() {
	std::vector<int> vi = {1,2,3,4,5};
	std::function<int(int)> plus1 = [] (int a) { return a + 1;};
	auto mapped = map(vi, plus1);
	for (auto i : mapped)
	std::cout << i << std::endl;
	

	std::function<int(int)> greaterThan3 = [] (int a) { return a > 3; };
	auto filtered = filter(vi, greaterThan3);
	for (auto i : filtered)
		std::cout << i << std::endl;
	std::cout << std:: endl;
	auto tailed = tail(vi);
	for (auto i : tailed)
		std::cout << i << std::endl;

	return 0;
}
