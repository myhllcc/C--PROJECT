#ifndef CIRCUIT
#define CIRCUIT
#include<iostream>
#include "components.h"
#include "nodes.h"
#include "circuit.h"
#include<vector>
#include<math.h>
using namespace my_compo;
namespace my_circuit
{
	class circuit
	{
	private:
		std::vector<nodes*> nodes_vector; //store all of nodes
		std::complex <double> circuit_impedance{};
		std::vector<std::shared_ptr<components>> my_components; //store all of components
		double voltage{};
		double frequency{};
		nodes start;
		nodes end;
		double impedance_magnitude{};
		double phase_shift{};
	public:
		circuit() :
			circuit_impedance{ (0,0)} { }
		circuit(double my_voltage, double my_frequency):
			circuit_impedance{ (0,0) }, voltage{ my_voltage }, frequency{ my_frequency }, impedance_magnitude{0},
			phase_shift{ 0 } {
			nodes_vector.push_back(&start);
			nodes_vector.push_back(&end);
		}
		~circuit() { }
		void add_series(components& A, components& B);
		void add_nodes(nodes& my_nodes);
		void add_parallel(components& A, components& B);
		std::complex <double> calculate_impedance(nodes& start, nodes& end );
		std::complex <double> get_impedance();
		std::vector<nodes*> get_nodes_vector();
		void add_resistor(resistor& my_resistor);
		void add_capacitor(capacitor& my_resistor);
		void add_inductor(inductor& my_resistor);
		double get_frequency();
		std::shared_ptr<components> get_components(int order);
		nodes* get_start();
		nodes* get_end();
		size_t components_size();
		void print_components(); //print all of components in the circuit
		void set_impedance(std::complex<double> my_impedance);
		void reset_comming_edge(); //initialise the number of entering edge of all nodes.
		void print_information();
		void set_impedance_magnitude();
		void set_phase_shift();
		void set_voltage(double my_voltage);
		void set_frequency(double my_frequency);
	};
}

#endif CIRCUIT