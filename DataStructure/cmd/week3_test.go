package cmd

import (
	"fmt"
	"testing"

	. "github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg"
	. "github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg/list"
)

func TestWeek3Question1(t *testing.T) {
	// Init La = {x, y, z, y, x}
	la := NewLinkedList[StringValue]()
	la.Insert("x", 0)
	la.Insert("y", 1)
	la.Insert("z", 2)
	la.Insert("y", 3)
	la.Insert("x", 4)

	// Init Lb = {x, y, y, x}
	lb := NewLinkedList[StringValue]()
	lb.Insert("x", 0)
	lb.Insert("y", 1)
	lb.Insert("y", 2)
	lb.Insert("x", 3)

	println("Week 3 Question 1: Check if a list is symmetric")

	println(fmt.Sprintf("La = %s", la.String()))
	if isSymmetric(la) {
		println("La is symmetric")
	} else {
		println("La is not symmetric")
	}

	println(fmt.Sprintf("Lb = %s", lb.String()))
	if isSymmetric(lb) {
		println("Lb is symmetric")
	} else {
		println("Lb is not symmetric")
	}
}

func isSymmetric(list *LinkedList[StringValue]) bool {
	length := list.Length()
	if length <= 1 {
		return true
	}

	stack := NewLinkedList[StringValue]()

	for i := 0; i < length/2; i++ {
		value, _ := list.Get(i)
		stack.Insert(value, 0)
	}

	halfIndex := (length + 1) / 2

	for i := 0; i < length/2; i++ {
		stackValue, _ := stack.Get(0)
		listValue, _ := list.Get(halfIndex + i)
		if !listValue.Equals(stackValue) {
			return false
		}
		stack.Remove(0)
	}

	return true
}
