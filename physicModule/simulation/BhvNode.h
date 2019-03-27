


struct InsertTestState
{
	enum Enum
	{
		eCross,
		eContain,
		eOut,
		eInContain,//·´°üº¬
		eInvalide
	};	
};


struct BHV_Node
{
	BHV_Node(Collider*);

	void cal_BHV();

	class Collider* _collider;
	Vector3R center;
	real    radius;
	
	InsertTestState::Enum getState(BHV_Node* other);
	static BHV_Node* CalNewNode(BHV_Node* a, BHV_Node* b);
	
	BHV_Node* left,* right;

};


struct BhvTree
{
	BhvTree(struct BhvList& list);
	~BhvTree();
	void push(BHV_Node*);
	BHV_Node* pRoot; 
};
struct BhvList
{
	~BhvList();
	std::list<BHV_Node*> _list;
	void Push(BHV_Node* pNode);
};