package exp1

import (
	. "github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg"
	. "github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg/list"
)

// CreateList creates a linked list from integers and stops at sentinel 0.
func CreateList(input []int) *LinkedList[IntValue] {
	l := NewLinkedList[IntValue]()
	for _, v := range input {
		if v == 0 {
			break
		}
		l.Insert(IntValue(v), l.Length())
	}
	return l
}

// AdjMax returns the first node value of the adjacent pair with maximum sum.
func AdjMax(L *LinkedList[IntValue]) (int, bool) {
	if L == nil || L.Length() < 3 {
		return 0, false
	}

	first, _ := L.Get(0)
	second, _ := L.Get(1)
	maxSum := int(first + second)
	maxFirst := int(first)

	for i := 1; i < L.Length()-1; i++ {
		left, _ := L.Get(i)
		right, _ := L.Get(i + 1)
		sum := int(left + right)
		if sum > maxSum {
			maxSum = sum
			maxFirst = int(left)
		}
	}

	return maxFirst, true
}
