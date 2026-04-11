package exp3_test

import (
	"testing"

	"github.com/isHarryh/USTB-Term-Projects/DataStructure/cmd/exp3"
)

func TestBuildHuffmanTreeAndCodes(t *testing.T) {
	symbols := []rune{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}
	weights := []int{5, 9, 7, 8, 14, 6, 3, 11}

	root, err := exp3.BuildHuffmanTree(symbols, weights)
	if err != nil {
		t.Fatalf("BuildHuffmanTree failed: %v", err)
	}

	if root.Value.Weight != 63 {
		t.Fatalf("expected root weight 63, got %d", root.Value.Weight)
	}

	codes, err := exp3.GenerateHuffmanCodes(root)
	if err != nil {
		t.Fatalf("GenerateHuffmanCodes failed: %v", err)
	}

	if len(codes) != len(symbols) {
		t.Fatalf("expected %d codes, got %d", len(symbols), len(codes))
	}

	expected := map[rune]string{
		'a': "1001",
		'b': "110",
		'c': "001",
		'd': "101",
		'e': "01",
		'f': "000",
		'g': "1000",
		'h': "111",
	}

	for s, code := range expected {
		if codes[s] != code {
			t.Fatalf("symbol %c expected code %s, got %s", s, code, codes[s])
		}
	}
}
