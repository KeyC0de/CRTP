#include <iostream>


static int nodes = 0;

class TreeNode
{
private:
	int m_id;
public:
	TreeNode* left;
	TreeNode* right;

	TreeNode()
		: m_id(++nodes),
		left(nullptr),
		right(nullptr)
	{}
	TreeNode( int id )
		: m_id(id),
		left(nullptr),
		right(nullptr)
	{
		++nodes;
	}

	int getId() const
	{
		return m_id;
	}
};


template<typename T>
class TreeParser
{
protected:
	//template<typename T, typename = std::enable_if_t<std::is_base_of_v<TreeParser, T>>>
	TreeParser()
	{
		++parsers;
	}
public:
	static uint32_t parsers;
	void preorderTraversal( TreeNode* node )
	{
		if ( node != nullptr )
		{
			processNode( node );
			preorderTraversal( node->left );
			preorderTraversal( node->right );
		}
	}

	~TreeParser() = default;

	/// \brief the 'interface' method
	void processNode( TreeNode* node )	// 2, 3. the generic algorithm is customized by derived classes
	{
		static_cast<T*>( this )->processNode( node );	// depending on the client's demand - the right function will be called
	}
};

template<class T>
uint32_t TreeParser<T>::parsers = 0;

class SpecializedTreeParser1
	: public TreeParser<SpecializedTreeParser1> // 1. is-a relationship
{
public:
	explicit SpecializedTreeParser1()
		: TreeParser()
	{}

	void processNode( TreeNode* node )
	{
		std::cout << "Customized (derived - SpecializedTreeParser1) preorderTraversal() - "
			"id=" << node->getId() << '\n';
	}
};

class SpecializedTreeParser2
	: public TreeParser<SpecializedTreeParser2> // 1. is-a relationship
{
public:
	explicit SpecializedTreeParser2()
		: TreeParser()
	{}

	void processNode( TreeNode* node )
	{
		std::cout << "Customized (derived - SpecializedTreeParser2) preorderTraversal() - "
			"id=" << node->getId() << '\n';
	}
};


int main() 
{
	TreeNode root;
	TreeNode leftChild;
	TreeNode rightChild;

	root.left = &leftChild;
	root.right = &rightChild;

	std::cout << "Root id: " << root.getId() << '\n';
	std::cout << "Left child id: " << leftChild.getId() << '\n';
	std::cout << "Right child id: " << rightChild.getId() << '\n';

	SpecializedTreeParser1 _1;
	_1.preorderTraversal( &root );

	SpecializedTreeParser2 _2;
	_2.preorderTraversal( &root );
	// only 1 of 2 types of parsing may happen at a program's build though
	//std::cout << "#parsers=" << _2.parsers << '\n';

	std::system( "pause" );
	return EXIT_SUCCESS;
}