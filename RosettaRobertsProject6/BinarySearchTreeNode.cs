using System;
using System.Collections.Generic;
using System.Linq;

namespace RosettaRobertsProject6
{
    /// <summary>
    ///     Represents a node of a binary tree. null is a valid value and represents and empty tree.
    ///     All instance "methods" are defined as extensions functions
    ///     so they can be called on null.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public sealed class BinarySearchTreeNode<T>
    {
        public BinarySearchTreeNode(T value, BinarySearchTreeNode<T> left, BinarySearchTreeNode<T> right)
        {
            Value = value;
            Left = left;
            Right = right;
        }

        /// <summary>
        ///     The left subtree of this binary search tree.
        /// </summary>
        public BinarySearchTreeNode<T> Left { get; }

        /// <summary>
        ///     The right subtree of this binary search tree
        /// </summary>
        public BinarySearchTreeNode<T> Right { get; }

        /// <summary>
        ///     The value in this node.
        /// </summary>
        public T Value { get; }
    }

    public static class BinarySearchTreeNode
    {
        /// <summary>
        ///     Finds the node of the children of this node with the specified value.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="value">The value to search for</param>
        /// <param name="comparer">The comparator defining the order between elements.</param>
        /// <param name="root">The tree to search through</param>
        /// <returns>The node containing the value or null if no node has the item.</returns>
        public static BinarySearchTreeNode<T> Find<T>(this BinarySearchTreeNode<T> root, T value, IComparer<T> comparer)
        {
            if (root == null) return null;

            int c = comparer.Compare(root.Value, value);

            return c == 0 ? root : (c < 0 ? root.Right : root.Left).Find(value, comparer);
        }

        /// <summary>
        ///     Returns a list of all the items in infix order.
        /// </summary>
        public static string GetStringOfAllValuesInInfixOrder<T>(this BinarySearchTreeNode<T> root) =>
            "[" + string.Join(", ", root.Infix()) + "]";

        /// <summary>
        ///     Alias for <see cref="GetStringOfAllValuesInInfixOrder{T}" />.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <returns></returns>
        public static string ToInfixString<T>(this BinarySearchTreeNode<T> root) =>
            root.GetStringOfAllValuesInInfixOrder();

        /// <summary>
        ///     Returns a display string version of this tree.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <param name="formatter">The function used to format the items in this tree. By default just calls ToString()</param>
        /// <returns></returns>
        public static string ToDisplayString<T>(this BinarySearchTreeNode<T> root,
            Func<BinarySearchTreeNode<T>, string> formatter = null)
        {
            formatter = formatter ?? (item => item.Value?.ToString() ?? "null");

            // Returns the string representation for a row of this tree at a
            // specified depth.
            string Row(BinarySearchTreeNode<T> node, int depth, string accum)
            {
                if (node == null) return accum;

                string value = formatter(node);

                if (depth == 0) return Row(node.Right, depth - 1, Row(node.Left, depth - 1, accum) + value + " ");

                // If the depth doesn't match, we want to put empty spaces in place.
                // This is so nothing is in the same column.
                string spaces = string.Concat(Enumerable.Repeat(" ", value.Length + 1));
                return Row(node.Right, depth - 1, Row(node.Left, depth - 1, accum) + spaces);
            }

            // Join the rows together.
            return string.Join(Environment.NewLine,
                from i in Enumerable.Range(0, root.MaxDepth())
                select Row(root, i, "")
            );
        }

        /// <summary>
        ///     Returns the values in the tree at this node in infix order.
        /// </summary>
        public static IEnumerable<T> Infix<T>(this BinarySearchTreeNode<T> root)
        {
            if (root == null) yield break;

            //Recursive iterative algorithm :P
            foreach (T item in root.Left.Infix()) yield return item;
            yield return root.Value;
            foreach (T item in root.Right.Infix()) yield return item;
        }

        /// <summary>
        ///     Returns the values in this tree in prefix order.
        /// </summary>
        public static IEnumerable<T> Prefix<T>(this BinarySearchTreeNode<T> root)
        {
            if (root == null) yield break;

            yield return root.Value;
            foreach (T item in root.Left.Prefix()) yield return item;
            foreach (T item in root.Right.Prefix()) yield return item;
        }

        /// <summary>
        ///     Returns a new tree equivalent to this except with <paramref name="item" />
        ///     inserted. If this tree already contains <paramref name="item" />,
        ///     then the tree is returned unmodified.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <param name="item"></param>
        /// <param name="comparer"></param>
        /// <returns></returns>
        public static BinarySearchTreeNode<T> Insert<T>(this BinarySearchTreeNode<T> root, T item,
            IComparer<T> comparer)
        {
            if (root == null) return new BinarySearchTreeNode<T>(item, null, null);

            int c = comparer.Compare(root.Value, item);

            // Don't do anything if there's a duplicate.
            if (c == 0) return root;

            // root.Value < item
            if (c < 0)
                return new BinarySearchTreeNode<T>(
                    root.Value,
                    root.Left,
                    root.Right.Insert(item, comparer)
                );

            return new BinarySearchTreeNode<T>(
                root.Value,
                root.Left.Insert(item, comparer),
                root.Right
            );
        }

        /// <summary>
        ///     Returns the minimum node from the given root.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <returns></returns>
        public static T MinValue<T>(this BinarySearchTreeNode<T> root)
        {
            if (root == null) throw new InvalidOperationException("Can't get minimum value of empty tree");

            return root.Left == null ? root.Value : root.Left.MinValue();
        }

        /// <summary>
        ///     Returns the maximum value under this root.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <returns></returns>
        public static T MaxValue<T>(this BinarySearchTreeNode<T> root)
        {
            if (root == null) throw new InvalidOperationException("Can't get maximum value of empty tree");

            return root.Right == null ? root.Value : root.Right.MaxValue();
        }

        /// <summary>
        ///     Returns a new binary search tree with all the same elements as
        ///     this one except with item removed.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <param name="item">The item to delete</param>
        /// <param name="comparer"></param>
        /// <returns>A binary tree with the specified item removed.</returns>
        public static BinarySearchTreeNode<T> Delete<T>(this BinarySearchTreeNode<T> root, T item,
            IComparer<T> comparer)
        {
            if (root == null) return null;

            int c = comparer.Compare(root.Value, item);

            // root.Value < item
            if (c < 0) return new BinarySearchTreeNode<T>(root.Value, root.Left, root.Right.Delete(item, comparer));

            // root.Value > item
            if (c > 0) return new BinarySearchTreeNode<T>(root.Value, root.Left.Delete(item, comparer), root.Right);

            // c == 0
            if (root.Left == null) return root.Right;
            if (root.Right == null) return root.Left;

            (T center, BinarySearchTreeNode<T> newLeft) = root.Left.DeleteMax();
            return new BinarySearchTreeNode<T>(center, newLeft, root.Right);
        }

        /// <summary>
        ///     Returns the maximum value of this tree and a new tree
        ///     with the maximum value removed.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <returns></returns>
        private static (T max, BinarySearchTreeNode<T> newRoot) DeleteMax<T>(this BinarySearchTreeNode<T> root)
        {
            if (root == null) throw new InvalidOperationException("Can't delete max of empty tree.");
            if (root.Right == null) return (root.Value, root.Left);

            (T max, BinarySearchTreeNode<T> newRight) = DeleteMax(root.Right);
            return (max, new BinarySearchTreeNode<T>(root.Value, root.Left, newRight));
        }

        /// <summary>
        ///     Returns the node containing the greatest value less than <paramref name="item" />.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <param name="item"></param>
        /// <param name="comparer"></param>
        /// <returns>Null if the item has no predecessor in this tree.</returns>
        public static BinarySearchTreeNode<T> Predecessor<T>(this BinarySearchTreeNode<T> root, T item,
            IComparer<T> comparer)
        {
            BinarySearchTreeNode<T> parentPredecessor = null;

            // We don't need recursion!!
            while (root != null)
            {
                if (comparer.Compare(root.Value, item) < 0)
                {
                    //The root node might be the predecessor in limited cases.
                    parentPredecessor = root;
                    root = root.Right;
                }
                else
                {
                    root = root.Left;
                }
            }

            return parentPredecessor;
        }

        /// <summary>
        ///     Returns a new tree that contains
        ///     all the values in both other trees. Doesn't modify passed in trees
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="left"></param>
        /// <param name="right"></param>
        /// <param name="comparer"></param>
        /// <returns></returns>
        public static BinarySearchTreeNode<T> Intersect<T>(this BinarySearchTreeNode<T> left,
            BinarySearchTreeNode<T> right, IComparer<T> comparer)
        {
            if (left == null) return right;
            if (right == null) return left;

            foreach (T item in right.Prefix()) left = left.Insert(item, comparer);

            return left;
        }

        /// <summary>
        ///     Returns the maximum depth of the binary search tree.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <returns></returns>
        public static int MaxDepth<T>(this BinarySearchTreeNode<T> root) => MaxDepth(root, 0, 0);

        /// <summary>
        ///     Returns the maximum depth of the binary search tree
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <param name="currentDepth">The current depth of <paramref name="root" /></param>
        /// <param name="bestDepth">The current best depth found. Passing this allows us to partially optimize tai recursion.</param>
        /// <returns></returns>
        private static int MaxDepth<T>(this BinarySearchTreeNode<T> root, int currentDepth, int bestDepth)
        {
            //Optimized tail recursion into while loop
            while (root != null)
            {
                currentDepth++;
                bestDepth = MaxDepth(root.Left, currentDepth, bestDepth);
                root = root.Right;
            }

            return Math.Max(currentDepth, bestDepth);
        }

        /// <summary>
        ///     Returns the minimum depth of this tree.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="root"></param>
        /// <returns></returns>
        public static int MinDepth<T>(this BinarySearchTreeNode<T> root) => MinDepth(root, 0, int.MaxValue);

        /// <summary>
        ///     Returns the minimum depth of this tree.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="node"></param>
        /// <param name="currentDepth">The current depth of <paramref name="node" /></param>
        /// <param name="bestDepth">The best depth currently found. Doesn't search below this depth.</param>
        /// <returns></returns>
        private static int MinDepth<T>(this BinarySearchTreeNode<T> node, int currentDepth, int bestDepth)
        {
            //Optimized tail recursion into loop.
            while (node != null)
            {
                currentDepth++;
                //Don't search deeper than the shallowest depth already found.
                if (currentDepth >= bestDepth) return bestDepth;

                bestDepth = MinDepth(node.Left, currentDepth, bestDepth);
                node = node.Right;
            }

            return currentDepth;
        }
    }
}