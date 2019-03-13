#ifndef EDITOR_BOXCOLLIDER
#define EDITOR_BOXCOLLIDER


class EditorBoxCollider
{
public:
	EditorBoxCollider();
	~EditorBoxCollider();
	
	void process();


	BoxCollider*  _boxCollider;
	BOX_NODE     _boxNodeView;
};

#endif //EDITOR_BOXCOLLIDER