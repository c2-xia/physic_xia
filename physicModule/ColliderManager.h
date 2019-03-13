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
	1.Ϊ�˽��ʹ���ĸ��Ӷȣ���������Լ����
	  Collider�Ĵ���������ֻ��ͨ��ColliderManager����ɣ�������ָ��ֱ��delete
	  ��Ϊ�����const֮��Ĵ���������Ȩ�ޣ��ǹ���Ĵ��ۻ�ǳ��Ĵ�
	  �����Լ���׳ɣ����еĴ������������Ĺ淶���Ǿͻ������������
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


