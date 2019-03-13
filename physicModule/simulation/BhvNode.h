



struct BHV_Node
{
	BHV_Node(Collider*);

	void cal_BHV();

	class Collider* _collider;
	Vector3R center;
	float    radius;
	
	BHV_Node* left,* right;

};


struct BhvTree
{
	BhvTree(struct BhvList& list);
	BHV_Node* pRoot; 
};
struct BhvList
{
	~BhvList();
	std::list<BHV_Node*> _list;
	void Push(BHV_Node* pNode);
};