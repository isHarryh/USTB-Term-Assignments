package list

import (
	"fmt"
	"strings"

	. "github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg"
)

// LinkedList is a linear list implementation using linked storage structure with one-way links.
type LinkedList[T Equalable] struct {
	head *node[T]
	size int
}

type node[T Equalable] struct {
	value T
	next  *node[T]
}

func NewLinkedList[T Equalable]() *LinkedList[T] {
	return &LinkedList[T]{
		head: nil,
		size: 0,
	}
}

func (l *LinkedList[T]) Clear() {
	l.head = nil
	l.size = 0
}

func (l *LinkedList[T]) IsEmpty() bool {
	return l.size == 0
}

func (l *LinkedList[T]) Length() int {
	return l.size
}

func (l *LinkedList[T]) Get(index int) (T, bool) {
	if index < 0 || index >= l.size {
		var zero T
		return zero, false
	}
	current := l.head
	for i := 0; i < index; i++ {
		current = current.next
	}
	return current.value, true
}

func (l *LinkedList[T]) Search(value T) int {
	current := l.head
	for i := 0; i < l.size; i++ {
		if current.value.Equals(value) {
			return i
		}
		current = current.next
	}
	return -1
}

func (l *LinkedList[T]) Insert(value T, index int) bool {
	if index < 0 || index > l.size {
		return false
	}
	newNode := &node[T]{value: value}
	if index == 0 || l.head == nil {
		newNode.next = l.head
		l.head = newNode
	} else {
		prev := l.head
		for i := 0; i < index-1; i++ {
			prev = prev.next
		}
		newNode.next = prev.next
		prev.next = newNode
	}
	l.size++
	return true
}

func (l *LinkedList[T]) Remove(index int) bool {
	if index < 0 || index >= l.size {
		return false
	}
	if index == 0 {
		l.head = l.head.next
		l.size--
		return true
	} else {
		prev := l.head
		for i := 0; i < index-1; i++ {
			prev = prev.next
		}
		if prev != nil && prev.next != nil {
			prev.next = prev.next.next
			l.size--
			return true
		}
	}
	return false
}

func (l *LinkedList[T]) String() string {
	var result strings.Builder
	result.WriteString("[")
	current := l.head
	for current != nil {
		fmt.Fprintf(&result, "%v", current.value)
		if current.next != nil {
			result.WriteString(", ")
		}
		current = current.next
	}
	result.WriteString("]")
	fmt.Fprintf(&result, " (length: %d)", l.Length())
	return result.String()
}
