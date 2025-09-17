#include <bits/stdc++.h>
using namespace std;


// T1: return 1 when x contains an even number of 1; 0 otherwise
// assumption: width = 32
// 基本思路：将所有的1都异或到第0位，最后返回最低位的取反
// 充分利用位运算的并行性，可以同时累计多位上的1

int even_ones(unsigned x) {
    x ^= (x >> 16); // 16 bits as a part, accumulate the 1 simultaneously
    x ^= (x >> 8); // 8 ....
    x ^= (x >> 4); // 4 ....
    x ^= (x >> 2); // 2 ....
    x ^= (x >> 1);
    return !(x & 1);
}

// T2: return number of 1
int bitCount(int x) { // 11010001 10010011 01001111 00000100
    int m1 = 0x11 | (0x11 << 8); // 00000000 00000000 00010001 00010001
    int mask = m1 | (m1 << 16); // 00010001 00010001 00010001 00010001
    // 每4bits为1个单位
    int s = mask & x; // 00010001 00010001 00000001 00000000 抓取mask对应位置的1
    s += mask & (x >> 1); // 00010001 00010010 00000010 00000000
    s += mask & (x >> 2); // 00100001 00010010 00010011 00000001
    s += mask & (x >> 3); // 00110001 00100010 00010100 00000001
    // 此时s每4bit的值分别对应x中每4bit中1的个数
    //                                         00110001 00100010
    // combine high and low order sums
    s = s + (s >> 16); // 00110001 00010010 01000101 00100011 
    // low order 16 bits now consists of 4 sums (答案全部汇总到最低的两单元)
    mask = 0xF | (0xF<<8); // 00000000 00000000 00001111 00001111
    s = (s & mask) + ((s >> 4) & mask); // 答案汇总到每个单元中的最低4位
    return (s + (s >> 8)) & 0x3f; // 00111111 最多可能有32个1，即只需要取出后面6位上的1
}

int main() {
    int x;
    cin >> x;
    cout << even_ones(x) << endl << bitCount(x) << endl;
    return 0; 
}