using System.Collections;
using System.Collections.Generic;

namespace RosettaRobertsProject6
{
	/// <summary>
	///     Represents a binary search tree. Using this in a for loop
	///     will iterate over the elements in sorted order.
	/// </summary>
	/// <typeparam name="T">The type of element held by this tree.</typeparam>
	public class BinarySearchTree<T> : IEnumerable<T>
	{
		/// <summary>
		///     Creates a binary search tree with the given comparator.
		///     If null or absent, uses the default comparator for that type.
		/// </summary>
		/// <param name="comparer"></param>
		public BinarySearchTree(IComparer<T> comparer = null)
		{
			Comparer = comparer ?? Comparer<T>.Default;
		}

		/// <summary>
		///     The comparator of this tree.
		/// </summary>
		public IComparer<T> Comparer { get; }

		/// <summary>
		///     The root node of this tree.
		/// </summary>
		private BinarySearchTreeNode<T> Root { get; set; }

		/// <inheritdoc />
		/// <summary>
		///     Allows an in-order traversal of the items.
		/// </summary>
		/// <returns></returns>
		public IEnumerator<T> GetEnumerator()
		{
			return Root.Infix().GetEnumerator();
		}

		IEnumerator IEnumerable.GetEnumerator()
		{
			return GetEnumerator();
		}

		/// <summary>
		///     Returns the node that contains the specified value or
		///     null if the <paramref name="value" /> is not in this tree.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		public BinarySearchTreeNode<T> Find(T value)
		{
			return Root.Find(value, Comparer);
		}

		/// <summary>
		///     Returns a string representation of this tree.
		/// </summary>
		/// <returns></returns>
		public override string ToString()
		{
			return Root.ToDisplayString();
		}

		/// <summary>
		///     Returns a string representation sh
		/// </summary>
		/// <returns></returns>
		public string ToInfixString()
		{
			return Root.ToInfixString();
		}

		/// <summary>
		///     Inserts the specified value into this tree.
		///     Duplicates are not reinserted.
		/// </summary>
		/// <param name="value"></param>
		public void Insert(T value)
		{
			Root = Root.Insert(value, Comparer);
		}

		/// <summary>
		///     Returns the minimum value in this tree.
		/// </summary>
		/// <returns></returns>
		public T MinValue()
		{
			return Root.MinValue();
		}

		/// <summary>
		///     Returns the maximum value in this tree.
		/// </summary>
		/// <returns></returns>
		public T MaxValue()
		{
			return Root.MaxValue();
		}

		/// <summary>
		///     Deletes <paramref name="value" /> from this tree. Doesn't modify
		///     anything if <paramref name="value" /> is not in this tree.
		/// </summary>
		/// <param name="value"></param>
		public void Delete(T value)
		{
			Root = Root.Delete(value, Comparer);
		}

		/// <summary>
		///     Returns the node containing the greatest item less than
		///     <paramref name="value" />. If there is no such item,
		///     returns null.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		public BinarySearchTreeNode<T> Predecessor(T value)
		{
			return Root.Predecessor(value, Comparer);
		}

		/// <summary>
		///     Returns a new binary search tree containing all the elements
		///     in both this and <paramref name="other" />. Uses the comparator
		///     of this tree.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		public BinarySearchTree<T> Intersect(BinarySearchTree<T> other)
		{
			return new BinarySearchTree<T>(Comparer)
			{
				Root = Root.Intersect(other.Root, Comparer)
			};
		}

		/// <summary>
		///     Returns the minimum depth of this binary search tree
		/// </summary>
		/// <returns></returns>
		public int MinDepth()
		{
			return Root.MinDepth();
		}

		/// <summary>
		///     Returns the maximum depth of this binary search tree
		/// </summary>
		/// <returns></returns>
		public int MaxDepth()
		{
			return Root.MaxDepth();
		}

		/// <summary>
		///     Returns whether this tree is empty or not.
		/// </summary>
		/// <returns></returns>
		public bool Empty()
		{
			return Root == null;
		}
	}
}