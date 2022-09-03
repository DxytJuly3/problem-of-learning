/*
给定一个单词列表 words 和一个整数 k ，返回前 k 个出现次数最多的单词。
返回的答案应该按单词出现频率由高到低排序。如果不同的单词有相同出现频率， 按字典顺序 排序。

示例 1：
输入: words = ["i", "love", "leetcode", "i", "love", "coding"], k = 2
输出: ["i", "love"]
解析: "i" 和 "love" 为出现次数最多的两个单词，均为2次。
    注意，按字母顺序 "i" 在 "love" 之前。

示例 2：
输入: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
输出: ["the", "is", "sunny", "day"]
解析: "the", "is", "sunny" 和 "day" 是出现次数最多的四个单词，
    出现次数依次为 4, 3, 2 和 1 次。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/top-k-frequent-words
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
本题是 给定的单词列表，并排出前K个出现次数最多的单词，并且出现相同次数的单词还要按照ascii码排序

解题思路：
    首先使用 map 来对给定的单词列表中的单词进行计数，map 的底层是红黑树，所以去重的同时 也将单词由ascii码排好顺序了
    然后 将 map中各个节点存储到 vector中，并根据节点的单词的出现次数来进行排序
    注意，由于在排除出现次数高低的同时，还需要保证ascii码的顺序，而map已经按照ascii拍好了顺序，所以在根据 出现次数排序时 建议使用稳定的排序算法，稳定的排序算法不会改变相同出现次数的单词的相对顺序
    然后再将 排好顺序的 存放map节点的vector 中前 K个节点的first数据 存放到 需要返回的vector中
*/

class Solution {
public:
    struct mItCompare {
        bool operator()(map<string, int>::iterator it1, map<string, int>::iterator it2) {
            return it1->second > it2->second;
        }
    };
    vector<string> topKFrequent(vector<string>& words, int k) {
        //  统计各个单词的出现次数，并按照ascii码顺序排好
        map<string, int> wordsCount;
        for(auto& word : words) {
            wordsCount[word]++;
        }

        //  将统计单词的map 中的各个节点的迭代器存入 vector中
        vector<map<string, int>::iterator> itV;
        auto mIt = wordsCount.begin();
        while(mIt != wordsCount.end()) {
            itV.push_back(mIt);
            mIt++;
        }

        // 定义一个 比较各个单词出现次数的仿函数，并使用 稳定的排序算法对 存放各个节点迭代器的vector排序
        stable_sort(itV.begin(), itV.end(), mItCompare());

        // 将排好序的存放各个节点的vector的前K个节点的单词存入需要返回的vector中
        vector<string> ret;
        auto vIt = itV.begin();
        while(k--) {
            ret.push_back((*vIt)->first);
            vIt++;
        }

        return ret;
    }
};