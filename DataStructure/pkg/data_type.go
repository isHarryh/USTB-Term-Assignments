package pkg

// Equalable is an interface for types that can be compared for equality.
type Equalable interface {
	Equals(other any) bool
}

// IntValue is a simple wrapper for int that implements Equalable.
type IntValue int

func (v IntValue) Equals(other any) bool {
	if otherValue, ok := other.(IntValue); ok {
		return v == otherValue
	}
	return false
}
