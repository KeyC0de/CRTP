#include <iostream>
#if defined _DEBUG && !defined NDEBUG
#	include <vld.h>
#endif


class TreeNode
{
	static inline int m_nodes = 0;
	int m_id;
	TreeNode* m_pLeft;
	TreeNode* m_pRight;
public:
	TreeNode()
		:
		m_id(++m_nodes),
		m_pLeft{nullptr},
		m_pRight{nullptr}
	{

	}

	TreeNode( int id )
		:
		m_id(id),
		m_pLeft{nullptr},
		m_pRight{nullptr}
	{
		++m_nodes;
	}

	void setLeft( TreeNode* left )
	{
		m_pLeft = left;
	}

	void setRight( TreeNode* right )
	{
		m_pRight = right;
	}

	TreeNode* getLeft()
	{
		return m_pLeft;
	}

	TreeNode* getRight()
	{
		return m_pRight;
	}

	int getId() const
	{
		return m_id;
	}
};


template<typename T>
class TreeParser
{
	static inline uint32_t parsers = 0;
protected:
	//template<typename T, typename = std::enable_if_t<std::is_base_of_v<TreeParser, T>>>
	TreeParser()
	{
		++parsers;
	}
public:
	void preorderTraversal( TreeNode* node )
	{
		if ( node != nullptr )
		{
			processNode( node );
			preorderTraversal( node->getLeft() );
			preorderTraversal( node->getRight() );
		}
	}

	~TreeParser() = default;

	/// \brief the 'interface' method
	void processNode( TreeNode* node )	// 2, 3. the generic algorithm is customized by derived classes
	{
		static_cast<T*>( this )->processNode( node );	// depending on the client's demand - the m_pRight function will be called
	}
};

class SpecializedTreeParser1
	: public TreeParser<SpecializedTreeParser1> // 1. is-a relationship
{
public:
	explicit SpecializedTreeParser1()
		:
		TreeParser()
	{

	}

	void processNode( TreeNode* node )
	{
		std::cout << "Customized (derived - SpecializedTreeParser1) preorderTraversal() - "
			"id="
			<< node->getId()
			<< '\n';
	}
};

class SpecializedTreeParser2
	: public TreeParser<SpecializedTreeParser2> // 1. is-a relationship
{
public:
	explicit SpecializedTreeParser2()
		:
		TreeParser()
	{

	}

	void processNode( TreeNode* node )
	{
		std::cout << "Customized (derived - SpecializedTreeParser2) preorderTraversal() - "
			"id="
			<< node->getId()
			<< '\n';
	}
};


int main()
{
	TreeNode root;
	TreeNode leftChild;
	TreeNode rightChild;

	root.setLeft( &leftChild );
	root.setRight( &rightChild );

	std::cout << "Root id: "
		<< root.getId()
		<< '\n';
	std::cout << "Left child id: "
		<< leftChild.getId()
		<< '\n';
	std::cout << "Right child id: "
		<< rightChild.getId()
		<< '\n';

	SpecializedTreeParser1 tp1;
	tp1.preorderTraversal( &root );

	SpecializedTreeParser2 tp2;
	tp2.preorderTraversal( &root );
	// only 1 of 2 types of parsing may happen at a program's build though
	//std::cout << "#parsers="
	//	<< tp2.parsers
	//	<< '\n';

	std::system( "pause" );
	return EXIT_SUCCESS;
}
