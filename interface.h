#ifndef INTERFACE
#define INTERFACE
#include <iostream>
#include<vector>
#include<string>
#include "circuit.h"
#include <windows.h>
using namespace my_circuit;
class interface_class
{
public:
	interface_class() {}
	~interface_class() {}
	template <class c_type> void input_positive(c_type& my_input);
	void input_max(int &my_option, int max); //input a number and check if it is smaller than the max.
	void input_p_s(std::string &my_input);
	void main_page(std::vector<circuit> &circuit_sum);
	void page_circuit_information(std::vector<circuit>& circuit_sum, int order_circuit);
	void page_add_component(std::vector<circuit>& circuit_sum, int order);
	void page_add_resistor(std::vector<circuit>& circuit_sum, int order);
	void page_add_inductor(std::vector<circuit>& circuit_sum, int order);
	void page_add_capacitor(std::vector<circuit>& circuit_sum, int order);
	void page_add_circuit(std::vector<circuit> &circuit_sum);
	void main_interface();
	bool check_p_s(std::string my_input); // check if the string input is a correct input. which can only be 'p' or 's'.
	static bool check_positive(double my_input); // check if the double input is a positive number.

};
#endif