#include <vector>
#include <stdio.h>

typedef long long ll;
typedef size_t unill;

template< typename T, int size >
class biTree
{
public:
	inline void build(int _size, T inti)
	{
		_v.resize(_size, inti);
	}

	template< typename T2>
	inline void TreeAdd(T change/*更改*/, T2 x/*下标*/)
	{
		for (size_t i = x; i <= _tree.size() - 1; i += lowbit(x))
		{
			_v[i] += change;
		}
		return;
	}

	template< typename T2 >
	inline T TreeSum(T2 x)
	{
		T sum = 0;
		for (T2 i = x; i >= 1; i -= lowbit(i))
		{
			sum += _v[i];
		}
		return sum;
	}

private:
	template< typename T >
	inline T lowbit(T x)
	{
		return ((x) & -(x));
	}

	std::vector< T > _v;
};

//函数前向声明
//快读函数
template< typename T >
inline T readf();

biTree< ll, 0 > tree;
ll n;

int main()
{
	n = readf< ll >();
}

template< typename T >
inline T readf()
{
#if false
	T sum = 0;
	char ch = getchar();
	while (ch > '9' || ch < '0') ch = getchar();
	while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = getchar();
	return sum;
#else
	T ret = 0, sgn = 0, ch = getchar();
	while (!isdigit(ch))
	{
		sgn |= ch == '-', ch = getchar();
	}
	while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
	return sgn ? -ret : ret;
#endif
}