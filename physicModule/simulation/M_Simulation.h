#ifndef M_SIMULATION
#define M_SIMULATION



class M_Simulation
{
public :
	void process(real rDertaTime);
	void addRigidbody(class Rigidbody*);
	std::list<class Rigidbody*>const & getRigidbodys();
private:

	std::list<class Rigidbody*> _rigidbodys;
};


#endif
