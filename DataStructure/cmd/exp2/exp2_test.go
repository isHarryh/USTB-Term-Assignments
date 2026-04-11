package exp2_test

import (
	"testing"

	"github.com/isHarryh/USTB-Term-Projects/DataStructure/cmd/exp2"
)

func TestSolveHanoiN3(t *testing.T) {
	moves, err := exp2.SolveHanoi(3)
	if err != nil {
		t.Fatalf("SolveHanoi failed: %v", err)
	}

	if len(moves) != 7 {
		t.Fatalf("expected 7 moves, got %d", len(moves))
	}

	first := moves[0]
	if first.Disk != 1 || first.From != 'A' || first.To != 'C' {
		t.Fatalf("unexpected first move: %+v", first)
	}

	last := moves[len(moves)-1]
	if last.Disk != 1 || last.From != 'A' || last.To != 'C' {
		t.Fatalf("unexpected last move: %+v", last)
	}
}
