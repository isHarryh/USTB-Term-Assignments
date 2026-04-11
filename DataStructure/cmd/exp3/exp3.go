package exp3

import (
	"fmt"
	"slices"
	"strings"

	"github.com/isHarryh/USTB-Term-Projects/DataStructure/pkg/tree"
)

type HuffmanValue struct {
	Symbol    rune
	Weight    int
	minSymbol rune
}

type HuffmanNode = tree.BinaryNode[HuffmanValue]

func hasHigherPriority(a, b *HuffmanNode) bool {
	if a.Value.Weight != b.Value.Weight {
		return a.Value.Weight < b.Value.Weight
	}
	return a.Value.minSymbol < b.Value.minSymbol
}

func pickTwoMinimumNodes(nodes []*HuffmanNode) (int, int) {
	min1, min2 := -1, -1

	for i := range nodes {
		if min1 == -1 || hasHigherPriority(nodes[i], nodes[min1]) {
			min2 = min1
			min1 = i
			continue
		}

		if min2 == -1 || hasHigherPriority(nodes[i], nodes[min2]) {
			min2 = i
		}
	}

	if min1 > min2 {
		min1, min2 = min2, min1
	}

	return min1, min2
}

func removeTwoAndAppend(nodes []*HuffmanNode, idx1, idx2 int, node *HuffmanNode) []*HuffmanNode {
	result := make([]*HuffmanNode, 0, len(nodes)-1)
	for i := range nodes {
		if i == idx1 || i == idx2 {
			continue
		}
		result = append(result, nodes[i])
	}
	result = append(result, node)
	return result
}

// BuildHuffmanTree builds a Huffman tree from symbols and weights.
func BuildHuffmanTree(symbols []rune, weights []int) (*HuffmanNode, error) {
	if len(symbols) == 0 || len(weights) == 0 {
		return nil, fmt.Errorf("symbols and weights must not be empty")
	}
	if len(symbols) != len(weights) {
		return nil, fmt.Errorf("symbols and weights length mismatch")
	}

	seen := make(map[rune]bool)
	forest := make([]*HuffmanNode, 0, len(symbols))

	for i, s := range symbols {
		if seen[s] {
			return nil, fmt.Errorf("duplicate symbol %q", s)
		}
		seen[s] = true

		if weights[i] <= 0 {
			return nil, fmt.Errorf("weight must be positive for symbol %q", s)
		}

		forest = append(forest, tree.NewBinaryNode(HuffmanValue{
			Symbol:    s,
			Weight:    weights[i],
			minSymbol: s,
		}))
	}

	for len(forest) > 1 {
		idx1, idx2 := pickTwoMinimumNodes(forest)
		left := forest[idx1]
		right := forest[idx2]

		if hasHigherPriority(right, left) {
			left, right = right, left
		}

		parentMin := left.Value.minSymbol
		if right.Value.minSymbol < parentMin {
			parentMin = right.Value.minSymbol
		}

		parent := tree.NewBinaryNode(HuffmanValue{
			Weight:    left.Value.Weight + right.Value.Weight,
			minSymbol: parentMin,
		})
		parent.Left = left
		parent.Right = right

		forest = removeTwoAndAppend(forest, idx1, idx2, parent)
	}

	return forest[0], nil
}

// GenerateHuffmanCodes returns Huffman codes for all leaf symbols.
func GenerateHuffmanCodes(root *HuffmanNode) (map[rune]string, error) {
	if root == nil {
		return nil, fmt.Errorf("root must not be nil")
	}

	codes := make(map[rune]string)
	var walk func(node *HuffmanNode, prefix string)
	walk = func(node *HuffmanNode, prefix string) {
		if node == nil {
			return
		}
		if node.IsLeaf() {
			if prefix == "" {
				codes[node.Value.Symbol] = "0"
				return
			}
			codes[node.Value.Symbol] = prefix
			return
		}

		walk(node.Left, prefix+"0")
		walk(node.Right, prefix+"1")
	}

	walk(root, "")
	return codes, nil
}

// FormatTree returns an indented pre-order string representation of the tree.
func FormatTree(root *HuffmanNode) (string, error) {
	if root == nil {
		return "", fmt.Errorf("root must not be nil")
	}

	lines := make([]string, 0)
	var walk func(node *HuffmanNode, depth int)
	walk = func(node *HuffmanNode, depth int) {
		if node == nil {
			return
		}

		indent := strings.Repeat("  ", depth)
		if node.IsLeaf() {
			lines = append(lines, fmt.Sprintf("%s%c:%d", indent, node.Value.Symbol, node.Value.Weight))
		} else {
			lines = append(lines, fmt.Sprintf("%s*:%d", indent, node.Value.Weight))
		}

		walk(node.Left, depth+1)
		walk(node.Right, depth+1)
	}

	walk(root, 0)
	return strings.Join(lines, "\n"), nil
}

// SortedSymbols returns symbols in ascending order.
func SortedSymbols(codes map[rune]string) []rune {
	keys := make([]rune, 0, len(codes))
	for k := range codes {
		keys = append(keys, k)
	}
	slices.Sort(keys)
	return keys
}
