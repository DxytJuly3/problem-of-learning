#include <iostream>
#include <vector>

// 直接插入排序
// 走过的地方已经是排好序的: 1 2 3 4 5 7 6 9 11 6 2
// 插入排序, 将当前位置后一位数据 以此与前面已经排好序的数据进行对比, 如果合适则交换位置
// 直到不再合适, 本趟排序完成
// 对于插入排序, 原序列越接近有序, 插入排序的效率越高, 越接近有序, 数据向前比较的次数就越少
// 1 3 5 7 2 9 11 10 15 4 17 18
//
void insertSort(std::vector<int>& v) {
	for (int i = 0; i < v.size() - 1; i++) {
		int cur = i;
		int temp = v[cur + 1]; // 记录已排好序数据之后位置的数据
		while (cur >= 0) {
			// 1 2 3 4 5 7 6 9 11 6 2
			// 1 2 3 4 5 6 7 9 11 6 2
			if (v[cur] > temp) {
				v[cur + 1] = v[cur]; // 将大的数据 放在后面
				cur--;
			}
			else {
				break;
			}

			v[cur + 1] = temp; // 将小的数据放在前面, 此时 cur已经--了
		}
	}
}

// 选择排序
// 在未排序的数据中, 选择最小或最大的 直接放在未排序数据的第一个
// 此时, 前面就变成了已排序数据, 并且 后面的数据不会比前面的数据大或小
void selectSort1(std::vector<int>& v) {
	for (int i = 0; i < v.size() - 1; i++) {
		int minPos = i;
		for (int j = i; j < v.size(); j++) {
			if (v[j] < v[minPos]) {
				minPos = j;
			}
		}
		std::swap(v[i], v[minPos]);
	}
}

// 冒泡排序 以升序解释
// 对比前一个和一个数据的大小, 后一个的大 就用后一个继续向后比较, 前一个大, 就交换位置 继续用大的向后比较
void bubbleSort(std::vector<int>& v) {
	for (int i = 0; i < v.size() - 1; i++) {
		// 需要用flag记录本趟对比 是否发生了数据交换, 如果没有 就说明已经排好序了
		bool flag = false;
		for (int j = 1; j < v.size() - i; j++) { // size-i向后的位置, 已经排好序了, 即 末尾i位已经排好序了
			if (v[j - 1] > v[j]) {
				// 将 大数 v[j-1] 向后移, 下次循环 就还是以 本次的大数v[j-1]向后对比
				std::swap(v[j - 1], v[j]);
				flag = true;
			}
		}
		// flag为false, 说明排序已经完成
		if (!flag)
			break;
	}
}

// 希尔排序
// 希尔排序可以看作是直接插入排序的优化
// 直接插入排序处理的数据越接近有序, 效率就越高
// 所以, 希尔排序就是利用直接插入排序的这个特点, 让数据接近有序, 在正式的使用直接插入排序之前, 需要进行预排序
// 预排序如何操作呢? 将 数据按照一定的间隔分组:
// 3 7 2 9 3 1 6 10 8 27 12, 按照 4分组
// 3       3        8
//   7       1        27
//     2       6         12
//       9       10
// 即分为 3 3 8, 7 1 27, 2 6 12, 9 10. 然后对每组插入排序
// 3       3        8
//   1       7        27
//     2       6         12
//       9       10
// 3 1 2 9 3 7 6 10 8 27 12

// 然后 减小间隔, 再次分组, 按照2分组
// 3 1 2 9 3 7 6 10 8 27 12
// 3   2   3   6    8    12
//   1   9   7   10   27
// 继续对分组进行插入排序
// 2   3   3   6    8    12
//   1   7   9   10   27
// 2 1 3 7 3 9 6 10 8 27 12

// 最后减小间隔到1 直接进行插入排序
// 对 2 1 3 7 3 9 6 10 8 27 12 直接插入排序, 比 3 7 2 9 3 1 6 10 8 27 12 直接插入排序 要快得多

// 分组间隔是如何计算的呢?  大佬计算,(gap先等于size) gap = gap / 3 + 1 最合适
// 知道最后就是1, 1时就是插入排序
void shellSort(std::vector<int>& v) {
	int gap = v.size();
	while (gap > 1) {	   // gap == 1时, 就是最后的插入排序
		gap = gap / 3 + 1; // 每次进入大循环 分组间隔就会减少
						   // 直接按gap大小 跳着进行插入排序, 最终就会以1 进行插入排序
		for (int i = 0; i < v.size() - gap; i++) {
			int cur = i;
			int temp = v[cur + gap];
			while (cur >= 0) {
				if (v[cur] > temp) {
					v[cur + gap] = v[cur];
					cur--;
				}
				else {
					break;
				}

				v[cur] = temp;
			}
		}
	}
}

// 选择排序优化
// 选择排序的思路 是 每次都遍历未排序的数据, 选出最大的或最小的 放在未排序数据的末尾 或 开头
// 但是, 实际上 每次遍历是可以选出未排序数据的 最大值 和最小值的, 不需要二选一
// 所以可以进行优化
// 优化之后, 如果是升序, 每趟遍历选出的 最大值放后面, 最小值放前面.
void selectSort2(std::vector<int>& v) {
	int left = 0;			  // 前面
	int right = v.size() - 1; // 后面
	while (left < right) {	  // 因为 left 和 right 是慢慢接近的
		int minPos = left;
		int maxPos = left;
		for (int i = left + 1; i < right + 1; i++) {
			if (v[i] < v[minPos]) {
				minPos = i;
			}
			if (v[i] > v[maxPos]) {
				maxPos = i;
			}
		}

		// 求出之后, 将 min 和 left 数据交换位置, max 和 right 位置交换数据
		std::swap(v[minPos], v[left]);

		// 两个交换之间 这里有一个问题, 上面 minPos 与 left 位置交换了
		// 就是, 有没有一种可能, left 的位置 实际上是 max 的位置呢?
		// 下面就是使用 maxPos进行交换位置了, 但是 left位置 现在是 min
		// 所以 如果 left == maxPos, 要更新 maxPos
		if (left == maxPos) {
			maxPos = minPos; // 将 maxPos 更新为 minPos
		}
		// 这里建议画图理解

		std::swap(v[maxPos], v[right]);

		left++;
		right--;
	}
}

// 归并排序
// 归并排序 使用 分治 归并的思想
// 对数组进行 2等分, 然后然后对等分出来的数组, 在进行二等分
// 直到 最后每个数组只有一个数据时, 再 反过来 两两合并
//                           3 2 6 7 5 9 8 2 3 0 1 2 8
//             3 2 6 7 5 9 8                          2 3 0 1 2 8
//      3 2 6 7             5 9 8                2 3 0           1 2 8
//   3 2       6 7        5 9     8           2 3     0        1 2    8
//  3   2     6   7      5   9    8          2   3    0       1   2   8

// 归并
// 3   2     6   7      5   9    8          2   3    0       1   2   8
//  2 3       6 7        5 9     8           2 3     0        1 2     8
//     2 3 6 7              5 8 9               0 2 3            1 2 8
//            2 3 5 6 7 8 9                          0 1 2 2 3 8
//                         0 1 2 2 2 3 3 5 6 7 8 8 9
