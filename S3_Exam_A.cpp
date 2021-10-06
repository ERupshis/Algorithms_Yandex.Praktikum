#include "solution.h"
#include <vector>
#include <cassert>

int BinarySearch(const std::vector<int>& arr, int l, int r, int k) { // O(log n) due to we decrease search range in 2 times every recursion call	
	if (l > r) { // base case - value is not found
		return -1;
	}

	int mid = (l + r) / 2;
	if (arr[mid] == k) { // base case - value is found
		return mid;
	}

	if (arr[l] <= arr[mid]) { // left part of arr is sorted.
		if (arr[l] <= k && k <= arr[mid]) {
			return BinarySearch(arr, l, mid - 1, k); // value is in left part
		}
		else {
			return BinarySearch(arr, mid + 1, r, k); // value in right part of array
		}
	}
	if (arr[mid] <= k && k <= arr[r]) { // right part of arr is sorted
		return BinarySearch(arr, mid + 1, r, k); // value is in right part
	}
	return BinarySearch(arr, l, mid - 1, k); // next recursion call to find sorted part of array		
}

int broken_search(const std::vector<int>& vec, int k) {
	return BinarySearch(vec, 0, vec.size() - 1, k);
}

void test() {
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}
