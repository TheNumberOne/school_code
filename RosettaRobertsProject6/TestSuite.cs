using System;
using System.Collections.Generic;

namespace RosettaRobertsProject6
{
	/// <summary>
	///     A test suite for testing pre sorted and non pre sorted items into a binary tree.
	/// </summary>
	public static class TestSuite
	{
		/// <summary>
		///     Runs the test suite
		/// </summary>
		/// <param name="r">The random number generator to use.</param>
		/// <param name="size">The number of elements to insert into the trees.</param>
		/// <returns></returns>
		public static SuiteRunResult Run(Random r, int size = 10000)
		{
			SuiteRunResult result = new SuiteRunResult();

			// Insert non-presorted items.
			BinarySearchTree<string> nonPreSorted = new BinarySearchTree<string>();

			for (int i = 0; i < size; i++) nonPreSorted.Insert(r.Next(50000).ToString("D5"));

			// Store result
			result.NonPreSorted = nonPreSorted;
			result.NonPreSortedMinDepth = nonPreSorted.MinDepth();
			result.NonPreSortedMaxDepth = nonPreSorted.MaxDepth();

			// Sort some items.
			List<string> items = new List<string>();
			for (int i = 0; i < size; i++) items.Add(r.Next(50000).ToString("D5"));
			items.Sort();

			// Insert presorted items.
			BinarySearchTree<string> preSorted = new BinarySearchTree<string>();

			foreach (string item in items) preSorted.Insert(item);

			// Store result
			result.PreSorted = preSorted;
			result.PreSortedMinDepth = preSorted.MinDepth();
			result.PreSortedMaxDepth = preSorted.MaxDepth();

			return result;
		}

		/// <summary>
		///     The result of running the test suite.
		/// </summary>
		public class SuiteRunResult
		{
			public BinarySearchTree<string> NonPreSorted { get; set; }
			public int NonPreSortedMinDepth { get; set; }
			public int NonPreSortedMaxDepth { get; set; }
			public BinarySearchTree<string> PreSorted { get; set; }
			public int PreSortedMinDepth { get; set; }
			public int PreSortedMaxDepth { get; set; }
		}
	}
}