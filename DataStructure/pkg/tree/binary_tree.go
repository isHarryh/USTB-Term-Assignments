package tree

// BinaryNode is a generic node of a binary tree.
type BinaryNode[T any] struct {
	Value T
	Left  *BinaryNode[T]
	Right *BinaryNode[T]
}

// BinaryTree is a generic binary tree with a root pointer.
type BinaryTree[T any] struct {
	Root *BinaryNode[T]
}

func NewBinaryNode[T any](value T) *BinaryNode[T] {
	return &BinaryNode[T]{
		Value: value,
	}
}

func NewBinaryTree[T any](root *BinaryNode[T]) *BinaryTree[T] {
	return &BinaryTree[T]{
		Root: root,
	}
}

func (n *BinaryNode[T]) IsLeaf() bool {
	return n != nil && n.Left == nil && n.Right == nil
}

func (t *BinaryTree[T]) IsEmpty() bool {
	return t == nil || t.Root == nil
}

func (t *BinaryTree[T]) PreOrder(visit func(node *BinaryNode[T])) {
	if t == nil || visit == nil {
		return
	}

	var walk func(node *BinaryNode[T])
	walk = func(node *BinaryNode[T]) {
		if node == nil {
			return
		}
		visit(node)
		walk(node.Left)
		walk(node.Right)
	}

	walk(t.Root)
}
