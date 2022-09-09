/*
句子 是一串由空格分隔的单词。每个 单词 仅由小写字母组成。
如果某个单词在其中一个句子中恰好出现一次，在另一个句子中却 没有出现 ，那么这个单词就是 不常见的 。
给你两个 句子 s1 和 s2 ，返回所有 不常用单词 的列表。返回列表中单词可以按 任意顺序 组织。

示例 1：
输入：s1 = "this apple is sweet", s2 = "this apple is sour"
输出：["sweet","sour"]

示例 2：
输入：s1 = "apple apple", s2 = "banana"
输出：["banana"]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/uncommon-words-from-two-sentences
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
题意分析：
    给定两个字符串 其中是由空格分隔的单词
    找到 两个字符串中的不常用单词 并存储起来返回
    什么是不常用单词？
    即 两个字符串中出现次数只有一次的单词

思路分析：
    思路1：用 哈希map 分别记录 统计s1 s2 中出现的单词
    遍历其中一个map 的单词, 去另一个map中找, 如果没有找到且在此map中只出现了一次 则存储起来, 如果找到了 则将另一个map中此单词的统计++
    遍历完之后, 再遍历另一个map 把只出现过一次的单词 存储起来

    思路2：将 s1 和 s2 链接在一个 string 中, 然后使用 哈希map 统计单词出现的次数
    然后遍历map 找出现次数为1的单词 (这种方法没用到哈希表查找O(1) 的优点)
*/

class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string, int> s1Map;
        unordered_map<string, int> s2Map;
        vector<string> ret;
        auto wordBegin = s1.begin();
        auto wordEnd = s1.begin();
        while(wordEnd != s1.end()) {
            while(wordEnd != s1.end() && *wordEnd != ' ') {
                wordEnd++;
            }
            string word(wordBegin, wordEnd);
            s1Map[word]++;

            if(wordEnd != s1.end())
                wordEnd++;
            wordBegin = wordEnd;
        }

        wordBegin = s2.begin();
        wordEnd = s2.begin();
        while(wordEnd != s2.end()) {
            while(wordEnd != s2.end() && *wordEnd != ' ') {
                wordEnd++;
            }
            string word(wordBegin, wordEnd);
            s2Map[word]++;

            if(wordEnd != s2.end())
                wordEnd++;
            wordBegin = wordEnd;
        }

        for(auto kv : s1Map) {
            auto wordIt = s2Map.find(kv.first);
            if(wordIt != s2Map.end())
                s2Map[kv.first]++;
            else if(kv.second == 1)
                ret.push_back(kv.first);
        }
        for(auto kv : s2Map) {
            if(kv.second == 1)
                ret.push_back(kv.first);
        }

        return ret;
    }
    // 思路2：
    /*vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string, int> sMap;
        string s;
        s += s1;
        s += ' ';
        s += s2;
        vector<string> ret;
        auto wordBegin = s.begin();
        auto wordEnd = s.begin();
        while(wordEnd != s.end()) {
            while(wordEnd != s.end() && *wordEnd != ' ') {
                wordEnd++;
            }
            string word(wordBegin, wordEnd);
            sMap[word]++;

            if(wordEnd != s.end())
                wordEnd++;
            wordBegin = wordEnd;
        }

        for(auto kv : sMap) {
            if(kv.second == 1)
                ret.push_back(kv.first);
        }

        return ret;
    }*/
};