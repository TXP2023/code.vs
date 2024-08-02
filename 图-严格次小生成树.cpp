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
std::vector< std::vector< ll > > father/*父节点*/, maxEdge/*最大边*/, sEdge/*次大边*/;
std::vector< bool > vecb;
std::vector< Edge > v_edge; //Kruskal 边排序
std::vector< ll > depath;
ll n, m, min_length, ans = LLONG_MAX; 

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
 
inline void init(ll u) //预处理 计算father/*父节点*/, maxEdge/*最大边*/, sEdge/*次大边*/
{
    depath[u] = depath[father[u][0]] + 1;
    for (ll i = 1; i <= 18; i++)
    {
        father[u][i] = father[father[u][i - 1]][i - 1];
        if (maxEdge[u][i - 1] == maxEdge[father[u][i - 1]][i - 1])
        {
            maxEdge[u][i] = maxEdge[u][i - 1];
            sEdge[u][i] = std::max(sEdge[father[u][i - 1]][i - 1], sEdge[u][i - 1]);
        }
        if (maxEdge[u][i - 1] > maxEdge[father[u][i - 1]][i - 1])
        {
            maxEdge[u][i] = maxEdge[u][i - 1];
            //sEdge[u][i] = std::max(maxEdge[u][i - 1], sEdge[father[u][i - 1]][i - 1]);
            sEdge[u][i] = std::max(sEdge[u][i - 1], maxEdge[father[u][i - 1]][i - 1]);
        }
        if (maxEdge[father[u][i - 1]][i - 1] > maxEdge[u][i - 1])
        {
            maxEdge[u][i] = maxEdge[father[u][i - 1]][i - 1];
            sEdge[u][i] = std::max(maxEdge[u][i - 1], sEdge[father[u][i - 1]][i - 1]);
        }
    }
    for (size_t i = 0; i < mst[u].size(); i++)
    {
        if (mst[u][i].to == father[u][0])
        {
            continue;
        }
        father[mst[u][i].to][0] = u;
        maxEdge[mst[u][i].to][0] = mst[u][i].val;
        init(mst[u][i].to);
    }
    return;
}

inline ll LCA(ll u, ll v)
{
    if (depath[u] < depath[v])
    {
        std::swap(u, v);
    }
    for (ll i = 18; i >= 0; i--)
    {
        if (depath[u] - depath[v] >= (1 << i))
        {
            u = father[u][i];
        }
    }
    if (u == v)
    {
        return u;
    }
    for (ll i = 18; i >= 0; i--) 
    {
        if (depath[u] != depath[v]) 
        {
            u = father[u][i], v = father[v][i];
        }
    }
    return father[u][0];
} 

inline ll SMST(ll u, ll v, ll w)
{
    ll node = LCA(u, v);
    ll max = 0, smax = 0;
    for (ll i = 18; i >= 0; i--)
    {
        if (depath[father[u][i]] >= depath[node])
        {
            if (max == maxEdge[u][i])
            {
                smax = std::max(sEdge[u][i], smax);
            }
            if (max > maxEdge[u][i])
            {
                smax = std::max(maxEdge[u][i], smax);
            }
            if (max < maxEdge[u][i])
            {
                smax = std::max(sEdge[u][i], max);
                max = maxEdge[u][i];
            }
            u = father[u][i];
        }
        if (depath[father[v][i]] >= depath[node])
        {
            if (max == maxEdge[v][i])
            {
                smax = std::max(smax, sEdge[v][i]);
            }
            if (max > maxEdge[v][i])
            {
                smax = std::max(maxEdge[v][i], smax);
            }
            if (max < maxEdge[v][i])
            {
                smax = std::max(sEdge[v][i], max);
                max = maxEdge[v][i];
            }
            v = father[v][i];
        }
    }
    if (w != max)
    {
        return  min_length - max + w;
    }
    if (smax)
    {
        return min_length - smax + w;
    }
    return LLONG_MAX;
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

    father.resize(n, std::vector< ll >(19, 0));
    maxEdge.resize(n, std::vector< ll >(19, 0));
    sEdge.resize(n, std::vector< ll >(19, 0));
    depath.resize(n, 0);
    init(0);
    for (ll i = 0; i < vecb.size(); i++)
    {
        if (!vecb[i])
        {
            ans = std::min(ans, SMST(v_edge[i].from, v_edge[i].to, v_edge[i].val));
        }
    }

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