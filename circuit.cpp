#include "circuit.h"
using namespace my_circuit;
void circuit::add_series(components& A, components& B)
{
	B.set_after_components(A.get_after_components());
	B.set_after_nodes(A.get_after_nodes());
	B.set_front_components(&A);
	A.set_after_components(&B);
	A.set_after_nodes(nullptr);
}
void circuit::add_nodes(nodes& my_nodes)
{
	nodes_vector.push_back(&my_nodes);
}
std::complex <double> circuit::get_impedance()
{
	return circuit_impedance;
}
std::vector<nodes*> circuit::get_nodes_vector()
{
	return nodes_vector;
}
void circuit::add_parallel(components& A, components& B)
{
	this->add_nodes(*new nodes);
	this->add_nodes(*new nodes);
	if (A.get_front_nodes() == nullptr) { //If A do not have front node, we need to add one
		nodes* new_front_nodes = this->nodes_vector[nodes_vector.size() - 2];
		A.get_front_components()->set_after_nodes(new_front_nodes);
		A.get_front_components()->set_after_components(nullptr);
		A.set_front_nodes(new_front_nodes);
		new_front_nodes->add_child(A);
		new_front_nodes->comming_edge_plus();
	}
	else 
	{
		nodes_vector.pop_back();
	}
	if (A.get_after_nodes() == nullptr) {	//If A do not have after node, we need to add one
		nodes* new_after_nodes = this->nodes_vector[nodes_vector.size() - 1];
		A.get_after_components()->set_front_nodes(new_after_nodes); 
		A.get_after_components()->set_front_components(nullptr); 
		new_after_nodes->add_child(*A.get_after_components()); 
		A.set_after_nodes(new_after_nodes);
		A.set_after_components(nullptr);
		new_after_nodes->comming_edge_plus();
	}
	else
	{
		nodes_vector.pop_back();
	}
	//Share nodes with B.
	A.get_front_nodes()->add_child(B);
	B.set_front_nodes(A.get_front_nodes());
	B.set_after_nodes(A.get_after_nodes());
	B.get_after_nodes()->comming_edge_plus();
}
std::complex <double> circuit::calculate_impedance(nodes& start, nodes& end)
{
	std::vector<nodes*> stop_nodes;
	std::complex <double> inverse_nodes_impedance{ 0,0 };
	std::vector<std::complex<double>> nodes_impedance;
	std::complex <double> one{ 1,0 };
	std::complex <double> zero{ 0,0 };
	//First process
	for (int i{}; i < start.child_size(); i++) {
		components* now_child = start.get_child(i);
		std::complex <double> edge_impedance{ now_child->get_value() };
		while (now_child->get_after_nodes() == nullptr) {
			//calculate one edge length
			now_child = now_child->get_after_components();
			edge_impedance += now_child->get_value();
		}
		if (now_child->get_after_nodes()->get_flag()) { 
			//add stop nodes
			stop_nodes.push_back(now_child->get_after_nodes());
			now_child->get_after_nodes()->set_flag(false);
		}
		//comming edge decreased by one
		now_child->get_after_nodes()->add_edge_impedance(edge_impedance);
		now_child->get_after_nodes()->comming_edge_minus();
	}
	//Second process
	for (int i{}; i < stop_nodes.size(); i++) {
		if (stop_nodes[i]->get_front_edge_impedance().size() > 1) {
			//stop_nodes with more than one edge connect to it.
			std::vector<std::complex <double>> nodes_i_edge{ stop_nodes[i]->get_front_edge_impedance() };
			std::complex <double> inverse_edge_impedance{ 0 };
			for (int j{}; j < nodes_i_edge.size(); j++) {
				inverse_edge_impedance = inverse_edge_impedance + one / nodes_i_edge[j];
			}
			nodes_impedance.push_back(one / inverse_edge_impedance);
			stop_nodes[i]->clean_edge_impedance();
		}
		else
		{
			nodes_impedance.push_back(stop_nodes[i]->get_front_edge_impedance()[0]);
			stop_nodes[i]->clean_edge_impedance();
		}
		stop_nodes[i]->set_flag(true);
	}
	//Third process
	while (stop_nodes.size() > 0) {
		for (int i{}; i < stop_nodes.size(); i++) {
			if (stop_nodes[i]->get_comming_edge() == 0) {
				if (stop_nodes[i] == &end && stop_nodes.size() == 1) { //stop at the end node. And all others nodes has been considered.
					inverse_nodes_impedance = { 0,0 };
					for (int i{}; i < nodes_impedance.size(); i++) {
						inverse_nodes_impedance += one / nodes_impedance[i];
					}
					return one / inverse_nodes_impedance;
				}
				else if(stop_nodes[i] != &end && stop_nodes.size() > 1) // find the impedance of the circuit with start node defined as this node.
				{
					nodes& next_start = *stop_nodes[i];
					nodes_impedance[i] += calculate_impedance(next_start, end);
					stop_nodes.erase(stop_nodes.begin() + i); // means this stop node has been considered.
				}
				else if (stop_nodes[i] != &end && stop_nodes.size() == 1) // means only one node left. Because there may some ndoes has been deleted. We need to use parallel law.
				{
					nodes& next_start = *stop_nodes[i];
					inverse_nodes_impedance = { 0,0 };
					for (int i{}; i < nodes_impedance.size(); i++) {
						inverse_nodes_impedance += one / nodes_impedance[i];
					}
					return one / inverse_nodes_impedance + calculate_impedance(next_start, end);
				}

			}
		}
	}
}
void circuit::add_resistor(resistor& my_resistor)
{
	my_components.push_back(std::make_shared<resistor>(my_resistor));
}
void circuit::add_capacitor(capacitor& my_resistor)
{
	my_components.push_back(std::make_shared<capacitor>(my_resistor));
}
void circuit::add_inductor(inductor& my_resistor)
{
	my_components.push_back(std::make_shared<inductor>(my_resistor));
}
double circuit::get_frequency()
{
	return frequency;
}
std::shared_ptr<components> circuit::get_components(int order)
{
	return my_components[order];
}
nodes* circuit::get_start()
{
	return &start;
}
nodes* circuit::get_end()
{
	return &end;
}
size_t circuit::components_size()
{
	return my_components.size();
}
void circuit:: print_components()
{
	if (my_components.size() == 0) {
		std::cout << "No components.";
	}
	else
	{
		for (int i{}; i < my_components.size(); i++) {
			std::cout << i << "---";
			my_components[i]->print_information();
			std::cout << std::endl;
		}
	}
}
void circuit::set_impedance(std::complex<double> my_impedance)
{
	circuit_impedance = my_impedance;
}
void circuit::reset_comming_edge()
{
	start.reset_comming_edge();
	end.reset_comming_edge();
	for (int i{}; i < nodes_vector.size(); i++) {
		nodes_vector[i]->reset_comming_edge();
	}
}
void circuit::print_information()
{
	std::cout << "Voltage = " << voltage <<" V" <<std::endl;
	std::cout << "Frequency = " << frequency << " Hz" <<std::endl;
	std::cout << "Total impedance (real,imag) = " << circuit_impedance << std::endl;
	std::cout << "Impedance magnitude = " << impedance_magnitude << std::endl;
	std::cout << "Phase shift = " << phase_shift << " radian" << std::endl;
}
void circuit::set_impedance_magnitude()
{
	impedance_magnitude = pow(pow(circuit_impedance.real(), 2) + pow(circuit_impedance.imag(), 2), 0.5);
}
void circuit::set_phase_shift()
{
	phase_shift = atan(circuit_impedance.imag()/ circuit_impedance.real());
}
void circuit::set_voltage(double my_voltage)
{
	voltage = my_voltage;
}
void circuit::set_frequency(double my_frequency)
{
	frequency = my_frequency;
	for (int i{}; i < my_components.size(); i++) {
		my_components[i]->set_frequency(my_frequency);
	}
}