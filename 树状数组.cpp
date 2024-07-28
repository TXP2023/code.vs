#include <vector>

template< typename T >
inline T lowbit(T x)
{
	return ((x) & -(x));
}

template< typename T1, typename T2, typename T3 >
inline void TreeAdd(T1 change/*更改*/, T2 x/*下标*/, std::vector< T3 >& _tree/*数组*/)
{
	for (size_t i = x; i <= _tree.size() - 1; i += lowbit(x))
	{
		_tree[i] += change;
	}
	return;
}
 