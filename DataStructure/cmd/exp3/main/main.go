package main

import (
	"fmt"
	"os"

	"github.com/isHarryh/USTB-Term-Projects/DataStructure/cmd/exp3"
)

func main() {
	if err := runExp3(); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}

func runExp3() error {
	symbols := []rune{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}
	weights := []int{5, 9, 7, 8, 14, 6, 3, 11}

	root, err := exp3.BuildHuffmanTree(symbols, weights)
	if err != nil {
		return err
	}

	codes, err := exp3.GenerateHuffmanCodes(root)
	if err != nil {
		return err
	}

	fmt.Println("Huffman Tree:")
	treeText, err := exp3.FormatTree(root)
	if err != nil {
		return err
	}
	fmt.Println(treeText)

	fmt.Println("Huffman Codes:")
	for _, s := range exp3.SortedSymbols(codes) {
		fmt.Printf("%c: %s\n", s, codes[s])
	}

	return nil
}
