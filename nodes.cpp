#include "nodes.h"
void nodes::add_child(components &my_child)
{
	child.push_back(&my_child);
}
components* nodes::get_child(int order)
{
	return child[order];
}
void nodes::set_flag(bool my_flag)
{
	flag = my_flag;
}
bool nodes::get_flag()
{
	return flag;
}
int nodes::get_comming_edge()
{
	return comming_edge;
}
void nodes::comming_edge_plus()
{
	comming_edge += 1;
	stored_comming_edge += 1;
}
void nodes::comming_edge_minus()
{
	comming_edge -= 1;
}
void nodes::add_edge_impedance(std::complex <double> my_impedance)
{
	front_edge_impedance.push_back(my_impedance);
}
std::vector<std::complex <double>> nodes::get_front_edge_impedance()
{
	return front_edge_impedance;
}
void nodes::clean_edge_impedance()
{
	front_edge_impedance.clear();
	std::vector<std::complex <double>>().swap(front_edge_impedance);
}
size_t nodes::child_size()
{
	return child.size();
}
void nodes::reset_comming_edge()
{
	comming_edge = stored_comming_edge;
}