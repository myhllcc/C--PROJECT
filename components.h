#ifndef COMPO
#define COMPO
#include<complex>
#include<iostream>
extern class nodes;
const double Pi = 3.14159265358979;
namespace my_compo
{
	class components
	{
	protected: 
		std::complex <double> value;
		components* after_components;
		components* front_components;
		nodes* front_nodes;
		nodes* after_nodes;
		std::string name;
		double frequency;
	public:
		components(std::string my_name, double my_frequency) :
			value{ 0 }, after_components{ nullptr }, front_nodes{ nullptr }, after_nodes{ nullptr }, front_components{ nullptr },
			name{ my_name }, frequency{my_frequency} {}
		virtual ~components() { }
		void set_front_nodes(nodes* my_front_nodes);
		void set_after_nodes(nodes* my_after_nodes);
		void set_after_components(components* my_after_components);
		void set_front_components(components* my_front_components);
		components* get_after_components();
		components* get_front_components();
		nodes* get_after_nodes();
		nodes* get_front_nodes();
		std::complex <double> get_value();
		void set_value(std::complex<double> my_value);
		virtual void print_information() = 0;
		virtual void set_frequency(double my_frequency) = 0;
	};
	class resistor : public components
	{
	private:
		double resistance;
	public:
		resistor(double my_value, double my_frequency) :
			components{ "Resistor", my_frequency}, resistance{my_value} {
			value = std::complex<double>{ my_value,0 };
		}
		~resistor() {}
		void print_phase_shift();
		void print_information();
		void set_frequency(double my_frequency);
	};
	class capacitor : public components
	{
	private:
		double capacitance;
	public:
		capacitor(double my_value, double my_frequency) :
			components{ "Capacitor", my_frequency }, capacitance{ my_value }{
			value = std::complex<double>{ 0, -1 / (2 * Pi * my_frequency * my_value) };
		}
		~capacitor() {}
		void print_phase_shift();
		void print_information();
		void set_frequency(double my_frequency);
	};
	class inductor : public components
	{
	private:
		double inductance;
	public:
		inductor(double my_value, double my_frequency) :
			components{ "Inductor", my_frequency }, inductance{ my_value } {
			value = std::complex<double>{ 0,2 * Pi * my_frequency * my_value };
		}
		~inductor() {}
		void print_phase_shift();
		void print_information();
		void set_frequency(double my_frequency);
	};
}
#endif