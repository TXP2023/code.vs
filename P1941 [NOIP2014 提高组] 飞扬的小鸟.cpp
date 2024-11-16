//P1941 [NOIP2014 提高组] 飞扬的小鸟
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>

typedef long long ll;
typedef unsigned long long unill;

struct operate {
    unill up; //点击一下上升的高度
    unill down; //不点击下降的高度
};

struct _data //管道数据
{
    unill x; //横坐标
    unill up; //管道上限
    unill down; //管道下限

    //运算符重载控制sort函数
    bool operator <(const _data& other)const {
        return x < other.x;
    }
};


std::vector< std::vector< unill > > dp(2); //动态规划数组
std::vector< operate > opers; //储存操作数据
std::vector< _data > datas; //储存障碍数据
std::vector< bool > out; //储存小年可以通过几个障碍
unill n, m, k, maxout = 0; //界面的长度，高度和水管的数量
unill ans = LLONG_MAX;

int main() {
    // freopen("D:\\code\\SHU_RU.in", "r", stdin);

    scanf("%lld%lld%lld", &n, &m, &k);

    //输入操作数据
    opers.resize(n);
    for (unill i = 0; i < n; i++) {
        scanf("%lld%lld", &opers[i].up, &opers[i].down);
    }

    //输入管道数据
    datas.resize(k);
    for (unill i = 0; i < k; i++) {
        scanf("%lld%lld%lld", &datas[i].x, &datas[i].down, &datas[i].up);
    }
    std::sort(datas.begin(), datas.end());

    //动态规划

    dp[0].resize(m, 0);
    dp[1].resize(m, LLONG_MAX);
    for (unill i = 1; i <= n; i++) {
        //上升
        for (unill j = opers[i - 1].up; j < m; j++) {
            dp[i % 2][j] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1, dp[i % 2][j - opers[i - 1].up] + 1);
        }

        //碰到天花板的特殊情况
        for (unill j = m - 1; j < m + opers[i - 1].up; j++) {
            dp[i % 2][m - 1] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1, dp[i % 2][m - 1]);
        }

        //往下掉
        for (unill j = 0; j <= m - opers[i - 1].down - 1; j++) {
            dp[i % 2][j] = std::min(dp[i % 2][j], dp[i % 2 ^ 1][j + opers[i - 1].down]);
        }

        //处理因为管道而无法到达的地方
        if (!datas.empty() && datas.front().x == i) {
            //下限处理
            for (unill j = 0; j < datas.front().down; j++) {
                dp[i % 2][j] =  LLONG_MAX;
            }

            //上线处理
            for (unill j = datas.front().up - 1; j <= m - 1; j++) {
                dp[i % 2][j] = LLONG_MAX;
            }

            //弹出
            datas.erase(datas.begin());
            for (unill j = 0; j < m; j++) {
                if (dp[i % 2][j] < LLONG_MAX) {
                    maxout++;
                    break;
                }
            }
        }

        //预处理
        dp[i % 2 ^ 1].clear();
        dp[i % 2 ^ 1].resize(m, LLONG_MAX);
    }

    //寻找结果
    for (unill i = 0; i < m; i++) {
        if (dp[n % 2][i] < ans) {
            ans = dp[n % 2][i];
        }
    }

    //输出结果
    switch (ans) {
    case LLONG_MAX:
        printf("0\n%llu\n", maxout);
        break;

    default:
        printf("1\n%llu\n", ans);
        break;
    }
    return 0;
}