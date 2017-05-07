// C++ program to find minimum and second minimum
// using minimum number of comparisons
#include <iostream>
#include <list>
#include <memory>
using namespace std;

// Tournament Tree node
struct Node
{
	int idx;
	shared_ptr<Node> left, right;
};

shared_ptr<Node> createNode(int idx)
{
	shared_ptr<Node> t(new Node{ idx });
	return t;
}

// This function traverses tree across height to
// find second smallest element in tournament tree.
// Note that root is smallest element of tournament
// tree.
void traverseHeight(shared_ptr<Node> const& root, int arr[], int &res)
{
	// Base case
	if (root == nullptr || (root->left == nullptr &&
		root->right == nullptr))
		return;

	// If left child is smaller than current result,
	// update result and recur for left subarray.
	if (res > arr[root->left->idx] &&
		root->left->idx != root->idx)
	{
		res = arr[root->left->idx];
		traverseHeight(root->right, arr, res);
	}

	// If right child is smaller than current result,
	// update result and recur for left subarray.
	else if (res > arr[root->right->idx] &&
		root->right->idx != root->idx)
	{
		res = arr[root->right->idx];
		traverseHeight(root->left, arr, res);
	}
}

// Prints minimum and second minimum in arr[0..n-1]
void findSecondMin(int arr[], int n)
{
	// Create a list to store nodes of current
	// level
	list<shared_ptr<Node>> li;

	shared_ptr<Node> root;
	for (int i = 0; i < n; i += 2)
	{
		shared_ptr<Node> t1(new Node{ i });
		shared_ptr<Node> t2;
		if (i + 1 < n)
		{
			// Make a node for next element
			t2 = createNode(i + 1);

			// Make smaller of two as root
			root = (arr[i] < arr[i + 1]) ? createNode(i) :
				createNode(i + 1);

			// Make two nodes as children of smaller
			root->left = t1;
			root->right = t2;

			// Add root
			li.push_back(root);
		}
		else
			li.push_back(t1);
	}

	int lsize = li.size();

	// Construct the complete tournament tree from above
	// prepared list of winners in first round.
	while (lsize != 1)
	{
		// Find index of last pair
		int last = (lsize & 1) ? (lsize - 2) : (lsize - 1);

		// Process current list items in pair
		for (int i = 0; i < last; i += 2)
		{
			// Extract two nodes from list, make a new
			// node for winner of two
			shared_ptr<Node> f1 = li.front();
			li.pop_front();

			shared_ptr<Node> f2 = li.front();
			li.pop_front();
			root = (arr[f1->idx] < arr[f2->idx]) ?
				createNode(f1->idx) : createNode(f2->idx);

			// Make winner as parent of two
			root->left = f1;
			root->right = f2;

			// Add winner to list of next level
			li.push_back(root);
		}
		if (lsize & 1)
		{
			li.push_back(li.front());
			li.pop_front();
		}
		lsize = li.size();
	}

	// Traverse tree from root to find second minimum
	// Note that minimum is already known and root of
	// tournament tree.
	int res = INT_MAX;
	traverseHeight(root, arr, res);
	cout << "Minimum: " << arr[root->idx]
		<< ", Second minimum: " << res << endl;
}

// Driver code
int main()
{
	int arr[] = { 61, 6, 100, 9, 10, 12, 17 };
	int n = sizeof(arr) / sizeof(arr[0]);
	findSecondMin(arr, n);
	return 0;
}