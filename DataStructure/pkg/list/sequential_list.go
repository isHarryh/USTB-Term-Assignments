package list

import (
	"fmt"
	"strings"

	. "github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg"
)

// SequentialList is a linear list implementation using sequential storage structure.
type SequentialList[T Equalable] struct {
	data []T
	last int
}

func NewSequentialList[T Equalable]() *SequentialList[T] {
	return &SequentialList[T]{
		data: make([]T, 0),
		last: -1,
	}
}

func (l *SequentialList[T]) Clear() {
	l.data = make([]T, 0)
	l.last = -1
}

func (l *SequentialList[T]) IsEmpty() bool {
	return l.last == -1
}

func (l *SequentialList[T]) Length() int {
	return l.last + 1
}

func (l *SequentialList[T]) Get(index int) (T, bool) {
	if index < 0 || index >= l.Length() {
		var zero T
		return zero, false
	}
	return l.data[index], true
}

func (l *SequentialList[T]) Search(value T) int {
	for i := 0; i <= l.last; i++ {
		if l.data[i].Equals(value) {
			return i
		}
	}
	return -1
}

func (l *SequentialList[T]) Insert(value T, index int) bool {
	if index < 0 || index > l.Length() {
		return false
	}
	var zero T
	l.data = append(l.data, zero)
	for i := l.last; i >= index; i-- {
		l.data[i+1] = l.data[i]
	}
	l.data[index] = value
	l.last++
	return true
}

func (l *SequentialList[T]) Remove(index int) bool {
	if index < 0 || index >= l.Length() {
		return false
	}
	for i := index; i < l.last; i++ {
		l.data[i] = l.data[i+1]
	}
	l.last--
	return true
}

func (l *SequentialList[T]) String() string {
	var result strings.Builder
	result.WriteString("[")
	for i := 0; i <= l.last; i++ {
		fmt.Fprintf(&result, "%v", l.data[i])
		if i < l.last {
			result.WriteString(", ")
		}
	}
	result.WriteString("]")
	fmt.Fprintf(&result, " (length: %d)", l.Length())
	return result.String()
}
