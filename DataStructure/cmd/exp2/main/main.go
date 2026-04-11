package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"

	"github.com/isHarryh/USTB-Term-Projects/DataStructure/cmd/exp2"
)

func main() {
	if err := runExp2FromIO(os.Stdin, os.Stdout); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}

// RunExp2FromIO reads n, prints move sequence, and prints total move count.
func runExp2FromIO(reader io.Reader, writer io.Writer) error {
	scanner := bufio.NewScanner(reader)
	scanner.Split(bufio.ScanWords)

	if !scanner.Scan() {
		if err := scanner.Err(); err != nil {
			return fmt.Errorf("failed to read input: %w", err)
		}
		return fmt.Errorf("no input read")
	}

	token := scanner.Text()
	n, convErr := strconv.Atoi(token)
	if convErr != nil {
		return fmt.Errorf("invalid integer input %q: %w", token, convErr)
	}

	moves, err := exp2.SolveHanoi(n)
	if err != nil {
		return err
	}

	for i, mv := range moves {
		if _, err = fmt.Fprintf(writer, "Step %d: Move disk %d from %c to %c\n", i+1, mv.Disk, mv.From, mv.To); err != nil {
			return err
		}
	}

	_, err = fmt.Fprintf(writer, "Total moves: %d\n", len(moves))
	return err
}
