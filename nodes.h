#ifndef NODES
#define NODES
#include<vector>
#include "components.h"
using namespace my_compo;
class nodes
{
private:
	bool flag{}; //check if the program has processed this node
	int stored_comming_edge{}; //number of edges connecting to this node. Stored the initial value of comming_edge
	int comming_edge{}; //nnumber of edges connecting to this node. 
	std::vector<components*> child; //components connect directly to the node
	std::vector<std::complex <double>> front_edge_impedance; //impedance of edges that connecting to the node
public:
	nodes() :
		flag{ true }, comming_edge{ 0 }, stored_comming_edge{ 0 }{}
	~nodes() {}
	void add_child(components &my_child);
	components* get_child(int order);
	void set_flag(bool my_flag);
	bool get_flag();
	int get_comming_edge();
	void comming_edge_plus();
	void comming_edge_minus();
	void add_edge_impedance(std::complex <double> my_impedance);
	std::vector<std::complex <double>> get_front_edge_impedance();
	void clean_edge_impedance();
	size_t child_size();
	void reset_comming_edge();
};
#endif 