#include "components.h"
using namespace my_compo;
void components::set_front_nodes(nodes* my_front_nodes)
{
	front_nodes = my_front_nodes;
}
void components:: set_after_nodes(nodes* my_after_nodes)
{
	after_nodes = my_after_nodes;
}
void components::set_after_components(components* my_after_components)
{
	after_components = my_after_components;
}
void components::set_front_components(components* my_front_components)
{
	front_components = my_front_components;
}
components* components::get_after_components()
{
	return after_components;
}
components* components::get_front_components()
{
	return front_components;
}
nodes* components::get_after_nodes()
{
	return after_nodes;
}
nodes* components::get_front_nodes()
{
	return front_nodes;
}
std::complex <double> components::get_value()
{
	return value;
}
void components::set_value(std::complex<double> my_value)
{
	value = my_value;
}
void resistor::print_phase_shift()
{
	std::cout << "The phase shift is 0" << std::endl;
}
void resistor::print_information()
{
	std::cout << "Resistor: " << resistance<< " (Ohm)";
}
void resistor::set_frequency(double my_frequency)
{
	frequency = my_frequency;
}
void capacitor::print_phase_shift()
{
	std::cout << "The phase shift is +90 degree" << std::endl;
}
void capacitor::print_information()
{
	std::cout << "Capacitor: " << capacitance << " (F)";
}
void capacitor::set_frequency(double my_frequency)
{
	frequency = my_frequency;
	value = std::complex<double>{ 0, -1 / (2 * Pi * my_frequency * capacitance) };
}
void inductor::print_phase_shift()
{
	std::cout << "The phase shift is -90 degree" << std::endl;
}
void inductor::print_information()
{
	std::cout << "Inductor: " << inductance << " (H)";
}
void inductor::set_frequency(double my_frequency)
{
	frequency = my_frequency;
	value = std::complex<double>{ 0,2 * Pi * my_frequency * inductance };
}