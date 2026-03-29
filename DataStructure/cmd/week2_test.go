package cmd

import (
	"fmt"
	"testing"

	. "github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg"
	. "github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg/list"
)

func TestWeek2Question1(t *testing.T) {
	// Init La = {1, 2, 3, 4}
	la := NewSequentialList[IntValue]()
	la.Insert(1, 0)
	la.Insert(2, 1)
	la.Insert(3, 2)
	la.Insert(4, 3)

	// Init Lb = {3, 4, 5, 6}
	lb := NewSequentialList[IntValue]()
	lb.Insert(3, 0)
	lb.Insert(4, 1)
	lb.Insert(5, 2)
	lb.Insert(6, 3)

	println("Week 2 Question 1: Diff Lists and Intersect Lists")
	println(fmt.Sprintf("Original La = %s", la.String()))
	println(fmt.Sprintf("Original Lb = %s", lb.String()))

	// Do list intersection operation
	if lc, ok := intersectLists(la, lb); ok {
		println(fmt.Sprintf("La ^ LB = %s", lc.String()))
	} else {
		println("IntersectLists operation failed")
	}

	// Do list difference operation
	if diffLists(la, lb) {
		println(fmt.Sprintf("La - Lb = %s", la.String()))
	} else {
		println("DiffLists operation failed")
	}
}

func intersectLists(la, lb *SequentialList[IntValue]) (*SequentialList[IntValue], bool) {
	result := NewSequentialList[IntValue]()
	for i := 0; i < lb.Length(); i++ {
		value, _ := lb.Get(i)
		index := la.Search(value)
		if index != -1 {
			result.Insert(value, result.Length())
		}
	}
	return result, true
}

func diffLists(la, lb *SequentialList[IntValue]) bool {
	for i := 0; i < lb.Length(); i++ {
		value, _ := lb.Get(i)
		index := la.Search(value)
		if index != -1 {
			la.Remove(index)
		}
	}
	return true
}

func TestWeek2Question2(t *testing.T) {
	// Init students list
	students := NewSequentialList[StudentInfo]()
	students.Insert(StudentInfo{"0001", "丁一", "男", "计02"}, 0)
	students.Insert(StudentInfo{"0002", "王二", "女", "计02"}, 1)
	students.Insert(StudentInfo{"0003", "张三", "男", "计02"}, 2)
	students.Insert(StudentInfo{"0032", "李四", "男", "计02"}, 3)

	println("Week 2 Question 2: Implement Students Table")
	println(fmt.Sprintf("Original students list: %s", students.String()))

	// Insert a new student
	x := StudentInfo{"0031", "新生", "女", "计02"}
	students.Insert(x, 3)
	println(fmt.Sprintf("After inserting new student: %s", students.String()))

	// Remove a student
	y := StudentInfo{"0002", "王二", "女", "计02"}
	index := students.Search(y)
	if index != -1 {
		students.Remove(index)
	}
	println(fmt.Sprintf("After removing student: %s", students.String()))
}

type StudentInfo struct {
	Sno   string
	Name  string
	Sex   string
	Class string
}

func (s StudentInfo) Equals(other any) bool {
	if otherInfo, ok := other.(StudentInfo); ok {
		return s.Sno == otherInfo.Sno
	}
	return false
}
