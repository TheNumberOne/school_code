﻿using System;
using System.Drawing;
using System.Windows.Forms;

namespace RosettaRobertsProject6
{
    /// <summary>
    ///     Author: Rosetta Roberts
    ///     <para />
    ///     The form used for testing of the binary search tree class.
    /// </summary>
    public partial class BinarySearchTreeSuite : Form
    {
        private BinarySearchTreeNode<string> _lastFound;

        /// <summary>
        ///     The first tree
        /// </summary>
        private BinarySearchTree<string> _tree1;

        /// <summary>
        ///     Not the first tree.
        /// </summary>
        private BinarySearchTree<string> _tree2;


        public BinarySearchTreeSuite()
        {
            InitializeComponent();
            Tree1 = new BinarySearchTree<string>();
            Tree2 = new BinarySearchTree<string>();
        }

        /// <summary>
        ///     A property for the first tree that updates the Form's display
        ///     when set.
        /// </summary>
        private BinarySearchTree<string> Tree1
        {
            get => _tree1;
            set
            {
                _tree1 = value;
                DisplayTree(TxtTree1, value);
                TxtTree1Minimum.Text = value.Empty() ? "" : value.MinValue();
                TxtTree1Maximum.Text = value.Empty() ? "" : value.MaxValue();
                TxtTree1MinDepth.Text = value.MinDepth().ToString();
                TxtTree1MaxDepth.Text = value.MaxDepth().ToString();
            }
        }

        /// <summary>
        ///     A property for the second tree that updates the Form's display
        ///     when set.
        /// </summary>
        private BinarySearchTree<string> Tree2
        {
            get => _tree2;
            set
            {
                _tree2 = value;
                DisplayTree(TxtTree2, value);
                TxtTree2Minimum.Text = value.Empty() ? "" : value.MinValue();
                TxtTree2Maximum.Text = value.Empty() ? "" : value.MaxValue();
                TxtTree2MinDepth.Text = value.MinDepth().ToString();
                TxtTree2MaxDepth.Text = value.MaxDepth().ToString();
            }
        }

        /// <summary>
        ///     A property for the active tree that switches between
        ///     tree1 and tree2.
        /// </summary>
        private BinarySearchTree<string> ActiveTree
        {
            get
            {
                switch (WhichActive)
                {
                    case Active.Tree1: return Tree1;
                    case Active.Tree2: return Tree2;
                    default:
                        throw new ArgumentOutOfRangeException();
                }
            }
            set
            {
                switch (WhichActive)
                {
                    case Active.Tree1:
                        Tree1 = value;
                        break;
                    case Active.Tree2:
                        Tree2 = value;
                        break;
                }
            }
        }

        /// <summary>
        ///     Used to store the last node found.
        /// </summary>
        private BinarySearchTreeNode<string> LastFound
        {
            get => _lastFound;
            set
            {
                _lastFound = value;
                // Update tree's display.
                Tree1 = Tree1;
                Tree2 = Tree2;
            }
        }

        /// <summary>
        ///     Which tree is active?
        /// </summary>
        private Active WhichActive { get; set; } = Active.Tree1;

        /// <summary>
        ///     A property that allows setting the result box.
        /// </summary>
        private string Result
        {
            set => TxtResult.Text = value;
        }

        /// <summary>
        ///     Displays the binary search tree in the given textbox. Bolds the last node
        ///     found.
        /// </summary>
        private void DisplayTree(RichTextBox textBox, BinarySearchTree<string> tree)
        {
            textBox.Clear();
            int maxDepth = tree.MaxDepth();

            for (int i = 0; i < maxDepth; i++)
            {
                if (i != 0) textBox.AppendText("\n");
                AppendLevel(textBox, tree.Root, i);
            }
        }

        /// <summary>
        ///     Appends the level of <paramref name="node" /> at the specified <paramref name="depth" />.
        ///     Bolds the last node found.
        /// </summary>
        private void AppendLevel(RichTextBox textBox, BinarySearchTreeNode<string> node, int depth)
        {
            // Tail call optimized.
            while (true)
            {
                if (node == null) return;

                // First we've gotta add the nodes on the left.
                AppendLevel(textBox, node.Left, depth - 1);

                // Added space for padding.
                string s = node.Value + " ";

                int previousLength = textBox.TextLength;
                textBox.AppendText(depth == 0 ? s : " ".Repeat(s.Length));

                // Select text. Subtracted one to not include trailing space.
                textBox.Select(previousLength, s.Length - 1);

                // Set font style.
                textBox.SelectionFont = NodeFont(node, textBox.Font);

                // Add the nodes on the right now.
                node = node.Right;
                depth--;
            }
        }

        /// <summary>
        ///     Calculates the font for the given node.
        ///     Basically bold if last found and normal otherwise.
        /// </summary>
        private Font NodeFont(BinarySearchTreeNode<string> node, Font defaultFont)
        {
            if (node != LastFound) return defaultFont;

            //return new Font(defaultFont, node == LastFound ? FontStyle.Bold : FontStyle.Regular);
            return new Font(defaultFont.FontFamily, defaultFont.Size * 1.3f, FontStyle.Bold);
        }

        /// <summary>
        ///     Updates how the active tree is displayed.
        /// </summary>
        private void UpdateActive()
        {
            //The property setter handles this for us.
            ActiveTree = ActiveTree;
        }

        /// <summary>
        ///     Event handler for active radio buttons to
        ///     select which tree is active.
        /// </summary>
        private void ActiveTreeChanged(object sender, EventArgs e)
        {
            if (BtnTree1Active.Checked)
                WhichActive = Active.Tree1;
            else if (BtnTree2Active.Checked) WhichActive = Active.Tree2;
        }

        /// <summary>
        ///     Finds the binary tree with both tree1 and tree2
        ///     and outputs it to the result text box.
        /// </summary>
        private void Intersect(object sender, EventArgs e)
        {
            Result = Tree1.Intersect(Tree2).ToString();
        }

        /// <summary>
        ///     Inserts the input into the active tree.
        /// </summary>
        private void Insert(object sender, EventArgs e)
        {
            ActiveTree.Insert(TxtInput.Text);
            UpdateActive();
        }

        /// <summary>
        ///     Deletes the input from the active tree.
        /// </summary>
        private void Delete(object sender, EventArgs e)
        {
            ActiveTree.Delete(TxtInput.Text);
            UpdateActive();
        }

        /// <summary>
        ///     Finds the predecessor of the input from the active tree.
        /// </summary>
        private void Predecessor(object sender, EventArgs e)
        {
            LastFound = ActiveTree.Predecessor(TxtInput.Text);
            Result = LastFound.ToDisplayString();
        }

        /// <summary>
        ///     Finds the input in the tree.
        /// </summary>
        private void Find(object sender, EventArgs e)
        {
            LastFound = ActiveTree.Find(TxtInput.Text);
            Result = LastFound.ToDisplayString();
        }

        /// <summary>
        ///     Runs a test suite for inserting non-presorted and presorted items
        ///     into an empty tree.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RunTestSuite(object sender, EventArgs e)
        {
            int size = (int) NumTestSuiteSize.Value;
            TestSuite.SuiteRunResult result = TestSuite.Run(new Random(), size);
            Result = $@"Not pre-sorted {size} elements:
	Min depth: {result.NonPreSortedMinDepth}
	Max depth: {result.NonPreSortedMaxDepth}
Pre-sorted {size} elements:
	Min depth: {result.PreSortedMinDepth}
	Max depth: {result.PreSortedMaxDepth} (difference due to removal of duplicates)";
        }

        /// <summary>
        ///     An enum for which tree is active.
        /// </summary>
        private enum Active
        {
            Tree1,
            Tree2
        }
    }
}