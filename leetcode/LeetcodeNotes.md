# Notes

## Problem 1016

> 描述：输入 $01$ 字符串 $S$ ，和一个正整数 $N$ ，如果 $1$ 到 $N$ 之间的所有整数的二进制表示（忽略高位的0）都是 $S$ 的子串，那么返回 `true`，否则返回 `false` . 

0.  思路，避免重复计算，考虑到如果 `1xxx` 部分的整数都是 $S$ 的子串，那么 `1xx` 部分的整数必然是 $S$ 的子串。
1.  题解中最快的解法：从 $1$ 遍历到 $N$ ，但超过 $5005$ 部分的整数全部返回 `false`  ，作弊的做法。

>   定位：不是个有价值的题。

## Problem 0044

>   通配符匹配，输入：字符串；正则表达式，只有 '?', '*' 和所有小写字母。

0.  思路，二维DP，缺点：空间复杂度过高，如果是非常长的字符串，比如文本，这样的做法是不合适的。

1.  最快的解法，代码如下：

    ```c++
    bool isMatch(string s, string p) {
        int is = 0, ip = 0, start = -1, match;
        while (is < s.size()) {
            if (s[is] == p[ip] || p[ip] == '?') {
                is++;
                ip++;
            } else if (p[ip] == '*') {
                start = is;
                match = ++ip;
            } else if (start != -1) {
                is = ++start;
                ip = match;
            } else return false;
        }
        while (ip < p.size() && p[ip] == '*') ip++;
        return (ip == p.size());
    }
    ```

    思路：匹配 `s[si]` 最长的 `p` 的前缀。

