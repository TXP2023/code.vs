#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

typedef long long ll;

std::vector<ll> v, head, c;
std::vector<ll> dp;
std::string str;
ll n;

int main() {
    freopen(".in", "r", stdin);
    std::cin >> n;      // 读取字符串长度
    std::cin >> str;    // 读取括号字符串

    v.resize(n + 1);
    head.resize(n + 1, 0);

    // 读取每个数字
    for (ll i = 1; i <= n; i++) {
        std::cin >> v[i];  // 使用 cin 读取每个数字
    }

    // 处理配对括号
    for (ll i = 1; i <= n; i++) {
        if (i > 1 && str[i - 1] == ')' && str[i - 2] == '(') {
            head[i - 1] = i - 2;  // 更新配对的括号位置
        }
    }

    // 建立 head 数组
    for (ll i = 1; i < n; i++) {
        if (str[i - 1] == '(' || head[i - 1]) {
            continue;
        }
        ll j = i - 2;
        while (j >= 0 && head[j] != 0) {
            j = head[j] - 1;
            if (j >= 0 && str[j] == '(') {
                head[i - 1] = j;  // 更新 head 数组
                break;
            }
        }
    }

    ll _max = 0;
    dp.resize(n + 1, 0);
    c.resize(n + 1, -0x3f3f3f3f);  // 使用负无穷大初始化

    // 动态规划计算
    for (ll i = 1; i <= n; i++) {
        dp[i] = _max;  // 初始化 dp[i]
        if (head[i - 1] != 0) // 如果当前括号有配对
        {  
            c[i] = std::max(dp[head[i - 1]] - v[head[i - 1] + 1], c[head[i - 1]]);  // 更新 c
            dp[i] = std::max(_max, c[i] + v[i]);  // 更新 dp[i]
            _max = std::max(_max, dp[i]);  // 更新最大值
        }
    }

    std::cout << dp[n] << std::endl;  // 输出最终结果
    return 0;
}
