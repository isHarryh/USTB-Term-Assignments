package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"

	"github.com/isHarryh/USTB-Term-Projects/DataStructure/cmd/exp1"
)

func main() {
	if err := runExp1FromIO(os.Stdin, os.Stdout); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}

func runExp1FromIO(reader io.Reader, writer io.Writer) error {
	scanner := bufio.NewScanner(reader)
	scanner.Split(bufio.ScanWords)

	input := make([]int, 0)
	foundEnd := false
	for scanner.Scan() {
		token := scanner.Text()
		value, convErr := strconv.Atoi(token)
		if convErr != nil {
			return fmt.Errorf("invalid integer input %q: %w", token, convErr)
		}
		input = append(input, value)
		if value == 0 {
			foundEnd = true
			break
		}
	}

	if scanErr := scanner.Err(); scanErr != nil {
		return fmt.Errorf("failed to scan input: %w", scanErr)
	}

	if len(input) == 0 {
		return fmt.Errorf("no input read")
	}

	if !foundEnd {
		return fmt.Errorf("input must end with sentinel 0")
	}

	L := exp1.CreateList(input)
	result, ok := exp1.AdjMax(L)
	if !ok {
		return fmt.Errorf("need at least two numbers before 0")
	}

	_, err := fmt.Fprintln(writer, result)
	return err
}
