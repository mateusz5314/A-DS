#ifndef CPP_TREE_HPP_
#define CPP_TREE_HPP_

#include <cassert>
#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>

template<typename T>
class CTree
{
public:

	template<typename TItem>
	class CTreeItem
	{
	public:
		std::shared_ptr<CTreeItem<TItem>> left;
		std::shared_ptr<CTreeItem<TItem>> right;
		TItem value;

		CTreeItem(TItem a):
			left(nullptr),
			right(nullptr),
			value(a)
		{

		}

	};

    CTree()
    :tree_size(0),
	 tree_depth(0),
	 root(nullptr)
    {
    }

    CTree(const CTree& aObj)
    {
    	if(aObj.tree_size>0)
    	{
    		tree_size = aObj.tree_size;
    		tree_depth = aObj.tree_depth;
    		root = nullptr;

    		copy(root, aObj.root);
    	}

    }
    

    CTree& operator=(const CTree& aObj)
    {
    	tree_size = aObj.tree_size;
    	tree_depth = aObj.tree_depth;

    	root = nullptr;

    	copy(root, aObj.root);
    	return *this;
    }

    void copy(std::shared_ptr<CTreeItem<T>> &dest, std::shared_ptr<CTreeItem<T>> src)
    {
		dest = std::make_shared<CTreeItem<T>>(src->value);

    	if (src->left != nullptr)
    	{
    		copy(dest->left, src->left);
    	}
    	else if(src->right != nullptr)
    	{
			copy(dest->right, src->right);
    	}
    }

    void tree_to_tab(std::vector<T*> &dest, std::shared_ptr<CTreeItem<T>> src)
    {
    	dest.push_back( &(src->value) );

    	if (src->left != nullptr)
		{
			tree_to_tab(dest, src->left);
		}

		else if(src->right != nullptr)
		{
			tree_to_tab(dest, src->right);
		}
    }


    bool operator==(const CTree& aObj)
    {
    	bool result = true;

    	if(tree_size == aObj.tree_size)
    	{
    		if(tree_size > 0)
    		{
    			std::vector<T*> my_tree_ele;
    			std::vector<T*> src_tree_ele;

				tree_to_tab(my_tree_ele, root);

				tree_to_tab(src_tree_ele, aObj.root);

				std::sort(my_tree_ele.begin(), my_tree_ele.end(),
						[](T* a, T *b)
						{
							return *a > *b;
						});
				std::sort(src_tree_ele.begin(), src_tree_ele.end(),
						[](T* a, T *b)
						{
							return *a > *b;
						});

				for(int i=0; i<my_tree_ele.size(); i++)
				{
					if ( *(my_tree_ele.at(i)) != *(src_tree_ele.at(i)) )
					{
						result = false;
						break;
					}
				}
    		}
    	}
    	else
    	{
    		result = false;
    	}

    	return result;
    }


    bool operator!=(const CTree& aObj)
    {
    	return !(*this==aObj);
    }



    unsigned int size() const
    {
    	return tree_size;
    }

    unsigned int depth(std::shared_ptr<CTreeItem<T>> aPtr, unsigned int result = 0)
    {
    	if (aPtr!=nullptr)
    	{
			result++;
			if(aPtr->left != nullptr)
			{
				depth(aPtr->left, result);
			}
			else if(aPtr->right != nullptr)
			{
				depth(aPtr->right, result);
			}
			else if(result > tree_depth)
			{
				tree_depth = result;
			}
    	}
    	return tree_depth;
    }

    std::shared_ptr<CTreeItem<T>> search(T aValue)
	{
    	std::shared_ptr<CTreeItem<T>> result = root;

    	while(result!=nullptr)
    	{
    		if(result->value == aValue)
    		{
    			break;
    		}
    		else if(aValue>result->value)
    		{
    			result = result -> right;
    		}
    		else if(aValue < result->value)
    		{
    			result = result -> left;
    		}
    	}

		return result;
	}

    bool contains(const T& aValue)
    {
    	return (search(aValue)!=nullptr);
    }
    

    bool empty() const
    {
    	return (tree_size==0);
    }
    

    bool insert(const T& aValue)
    {
    	bool result = false;

    	if(root == nullptr)
    	{
    		root = std::make_shared<CTreeItem<T>>(aValue);
    		tree_size++;
    		result = true;
    	}

    	else if( !contains(aValue) )
    	{
			std::shared_ptr<CTreeItem<T>> temp = root;

			while(temp!=nullptr)
			{
				if(aValue > temp->value)
				{
					if(temp->right != nullptr)
					{
						temp = temp -> right;
					}
					else
					{
						temp -> right = std::make_shared<CTreeItem<T>>(aValue);
						temp = temp -> right;
						break;
					}
				}

				else if(aValue < temp->value)
				{
					if(temp->left != nullptr)
					{
						temp = temp -> left;
					}
					else
					{
						temp -> left = std::make_shared<CTreeItem<T>>(aValue);
						temp = temp -> left;
						break;
					}
				}

			}
			tree_size++;
    	}

    	return result;
    }

    std::shared_ptr<CTreeItem<T>> consequent(T aValue)
	{
    	std::shared_ptr<CTreeItem<T>> result = search(aValue);
    	if(result -> right != nullptr)
    	{
    		result = result -> right;

    		while(result != nullptr)
    		{
    			if(result->left == nullptr)
    			{
    				break;
    			}
    			else
    			{
    				result = result->left;
    			}
    		}
    	}
    	else if(result -> left != nullptr)
    	{
    		result = result -> left;

			while(result != nullptr)
			{
				if(result->right == nullptr)
				{
					break;
				}
				else
				{
					result = result->right;
				}
			}
    	}
    	else
    	{
    		result = nullptr;
    	}
    	return result;
	}

    void remove_leaf(T aValue)
    {
    	std::shared_ptr<CTreeItem<T>> result = root;

		while(result!=nullptr)
		{
			if(result->value == aValue)
			{
				root = nullptr;
				break;
			}
			else if(result->left != nullptr && result->left->value == aValue)
			{
				result->left = nullptr;
				break;
			}
			else if(result->right != nullptr && result->right->value == aValue)
			{
				result->right = nullptr;
				break;
			}
			else if( aValue > result->value )
			{
				result = result -> right;
			}
			else if( aValue < result->value )
			{
				result = result -> left;
			}
		}

    }

    bool remove(T aValue)
    {
    	bool result = false;

    	if( contains(aValue) )
    	{
    		std::shared_ptr<CTreeItem<T>> to_delete=search(aValue);
    		std::shared_ptr<CTreeItem<T>> next = consequent(aValue);

    		if (next != nullptr)
    		{
    			T temp = to_delete->value;
				to_delete->value = next->value;

				remove_leaf(temp);
    		}
    		else
    		{
				remove_leaf(to_delete->value);
    		}
    		tree_size--;

    	}

    	return result;
    }

    std::shared_ptr<CTreeItem<T>> Begin()
		{
    	return root;
		}


	private:
		unsigned int tree_size = 0;
		unsigned int tree_depth;
		std::shared_ptr<CTreeItem<T>> root;
    
};

#endif // CPP_VECTOR_HPP_
