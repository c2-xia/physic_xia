#ifndef  COLLIDER_MANAGER
#define  COLLIDER_MANAGER

struct CollierType
{
	enum Enum
	{
		BoxCollider,
	};
};
 
class ColliderManager
{
public:
	ColliderManager() ;
	~ColliderManager() {};

	/*
	1.为了降低代码的复杂度，这里我们约定，
	  Collider的创建和销毁只能通过ColliderManager来完成，不能用指针直接delete
	  因为如果用const之类的代码来控制权限，那管理的代价会非常的大
	  而如果约定俗成，所有的代码遵守这样的规范，那就会让这件事情变简单
	*/
	Collider* Create (CollierType::Enum eType);
	bool	  Destory(Collider* collider);

	std::list<Collider*>& getColliders()
	{
		return _Colliders;
	}
private:
	class BoxCollider* CreateBoxCollider();

private:
	std::list<Collider*> _Colliders;

public:
	static ColliderManager Instance;
};

#endif // ! COLLIDER_MANAGER


