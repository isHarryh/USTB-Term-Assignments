package exp1

import (
	"testing"
)

func TestExp1Adjmax(t *testing.T) {
	input := []int{2, 6, 4, 7, 3, 0}
	L := CreateList(input)

	result, ok := AdjMax(L)
	if !ok {
		t.Fatalf("AdjMax returned invalid result")
	}

	if result != 4 {
		t.Fatalf("expected 4, got %d", result)
	}
}
