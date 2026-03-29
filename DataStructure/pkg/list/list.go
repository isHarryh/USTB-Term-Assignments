package list

import (
	. "github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg"
)

// List is an interface for linear lists.
type List[T Equalable] interface {
	// Clear removes all elements from the list.
	Clear()

	// IsEmpty returns whether the list contains no elements.
	IsEmpty() bool

	// Length returns the number of elements in the list.
	Length() int

	// Get returns the element at index and whether the index is valid.
	Get(index int) (T, bool)

	// Search returns the index of value, or -1 if not found.
	Search(value T) int

	// Insert inserts value at index and returns whether it succeeds.
	Insert(value T, index int) bool

	// Remove deletes the element at index and returns whether it succeeds.
	Remove(index int) bool

	// String returns a human-readable representation of the list.
	String() string
}
