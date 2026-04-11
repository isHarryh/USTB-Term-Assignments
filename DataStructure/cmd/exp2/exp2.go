package exp2

import (
	"fmt"
)

// Move represents one legal move in Hanoi solution.
type Move struct {
	Disk int
	From rune
	To   rune
}

// SolveHanoi returns the move sequence from tower A to C using B as auxiliary.
func SolveHanoi(n int) ([]Move, error) {
	if n < 1 {
		return nil, fmt.Errorf("n must be >= 1")
	}

	moves := make([]Move, 0)

	var solve func(disk int, from, aux, to rune)
	solve = func(disk int, from, aux, to rune) {
		if disk == 1 {
			moves = append(moves, Move{Disk: 1, From: from, To: to})
			return
		}

		solve(disk-1, from, to, aux)
		moves = append(moves, Move{Disk: disk, From: from, To: to})
		solve(disk-1, aux, from, to)
	}

	solve(n, 'A', 'B', 'C')
	return moves, nil
}
