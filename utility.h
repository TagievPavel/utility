#ifndef UTILITY_H
#define UTILITY_H

#include<cstddef>
#include<type_traits>
#include<limits>
#include<cmath>
#include<tuple>

struct tuple_for_each
{
public:
	template <typename Tuple, typename CallBack>
	tuple_for_each(Tuple&& tup, CallBack&& fn)
	{
		loop<0>(std::forward<Tuple>(tup), std::forward<CallBack>(fn));
	}

private:
	template <std::size_t Idx, typename Tuple, typename CallBack>
	void loop(Tuple&& tup, CallBack&& fn) const
	{
		if constexpr (Idx < std::tuple_size_v<std::remove_reference_t<Tuple>>)
		{
			fn(std::get<Idx>(tup));
			loop<Idx + 1>(std::forward<Tuple>(tup), std::forward<CallBack>(fn));
		}
	}
	/*
	* Example:
	* auto tup = std::make_tuple("Hello", 10, 3.14);
	* tuple_for_each(tup, [](const auto& el) { std::cout << el << std::endl; });
	*/

};

constexpr auto range(const std::size_t param)
{
	//https://habr.com/ru/post/516630/
	struct iterator
	{
	public:
		void operator ++ () { ++i; }
		bool operator != (iterator other) { return i != other.i; }
		std::size_t operator * () { return i; }

	public:
		std::size_t i;

	};

	struct wrapper
	{
	public:
		iterator begin() { return iterator{ 0 }; }
		iterator end()   { return iterator{ e }; }

	public:
		std::size_t e;

	};
	/*
	*Example:
	*for (auto i : range(10))
	*	std::cout << i << std::endl;
	*/
	return wrapper{ param };
}

template <typename Type>
bool is_equal(const Type& lhv, const Type& rhv)
{
	if constexpr (std::is_floating_point_v<Type>)
		return std::abs(lhv - rhv) < std::numeric_limits<Type>::epsilon();

	return lhv == rhv;
}

#endif//UTILITY_H