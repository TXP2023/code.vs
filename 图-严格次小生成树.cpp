#include <vector>
#include <stdio.h>
#include <climits>
#include <algorithm>
#include <ctype.h>
#include <numeric>
#include <queue>

typedef long long ll;
typedef size_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

//存边
class Edge
{
public:
    ll from;//两端节点
    ll to;
    ll val;//权值

//private:
    bool operator <(const Edge& other)const {
        return val < other.val;
    }
};

struct data
{
    ll to;//节点
    ll val;//权值
};

std::vector< std::vector< data > > mst; //最小生成树
std::vector< bool > vecb;
std::vector< Edge > v_edge; //Kruskal 边排序
std::vector< ll > depath;
ll n, m, min_length, ans; 

//并查集函数
template< typename T, typename T2 > 
inline T findSet(T x, std::vector< T2 >& _set)
{
    if (_set[x] == x)
    {
        return x;
    }
    else
    {
        return _set[x] = findSet(_set[x], _set);
    }
}

//克鲁斯卡尔最小生成树函数
inline ll Kruskal(ll _n/*节点数*/, std::vector< Edge > _e/*边集*/)
{
    mst.resize(_n);

    //排序边权
    //std::sort(_e.begin(), _e.end()); 
    
    //构造 初始化并查集
    std::vector< ll > set(_e.size());
    std::iota(set.begin(), set.end(), 0);

    ll cnt = 0, lenght = 0;
    for (size_t i = 0; i < _n-1;)
    {
        if (findSet(_e.front().from, set) != findSet(_e.front().to, set))
        {
            i++;
            lenght += _e.front().val;
            set[findSet(_e.front().from, set)] = findSet(_e.front().to, set);
            mst[_e.front().from].push_back({ _e.front().to, _e.front().val });
            mst[_e.front().to].push_back({ _e.front().from, _e.front().val });
            _e.erase(_e.begin());
            vecb[cnt] = true;
        }
        else
        {
            _e.erase(_e.begin());
        }
        cnt++;
    }
    return lenght;
}

inline void init()
{
    std::queue< ll > que;
    
}

int main(void)
{
    freopen(".in", "r", stdin);
    n = readf< ll >(), m = readf< ll >();
    
    for (size_t i = 0; i < m; i++)
    {
        ll from = readf< ll >() - 1, to = readf< ll >() - 1, val = readf< ll >();
        v_edge.push_back({ from,to,val });
    }

    bool f = false;
    vecb.resize(m, false);
    std::sort(v_edge.begin(), v_edge.end());
    min_length = Kruskal(n, v_edge); //正确

    printf("%lld\n", ans);
    return 0;
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
        sgn |= ch == '-', ch = getchar();
    while (isdigit(ch)) 
        ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}