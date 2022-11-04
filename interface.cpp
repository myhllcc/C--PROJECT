#include "interface.h"
bool interface_class::check_p_s(std::string my_input)
{
	return (my_input == "p" || my_input == "s");
}
bool interface_class::check_positive(double my_input)
{
	return my_input > 0;
}
template<class c_type> void interface_class::input_positive(c_type& my_input)
{
	std::cin >> my_input;
	while (std::cin.fail() || my_input <= 0) {
		std::cout << "The input is incorrect. " << std::endl << "Please enter again: ";
		std::cin.clear();
		std::cin.sync();
		std::cin.ignore(100, '\n');
		std::cin >> my_input;
	}
}
void interface_class::input_max(int &my_input, int max)
{
	std::cin >> my_input;
	while (std::cin.fail() || my_input < 0 || my_input > max) {
		std::cout << "The input is incorrect. " << std::endl << "Please enter again: ";
		std::cin.clear();
		std::cin.sync();
		std::cin.ignore(100, '\n');
		std::cin >> my_input;
	}
}
void interface_class::input_p_s(std::string &my_input)
{
	std::cin >> my_input;
	while (std::cin.fail() || (my_input != "p" && my_input != "s")) {
		std::cout << "The input is incorrect. " << std::endl << "Please enter again: ";
		std::cin.clear();
		std::cin.sync();
		std::cin.ignore(100, '\n');
		std::cin >> my_input;
	}
}
void interface_class::main_page(std::vector<circuit>& circuit_sum)
{
	system("CLS");
	std::cout << "Main Menu" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "0: Add a new circuit" << std::endl;
	std::cout << "1: Circuit Manipulate" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	int option{};
	input_max(option, 1);
	switch (option) {
	case 0: {
		page_add_circuit(circuit_sum);
	}
	case 1: {
		size_t number_circuit{ };
		number_circuit = circuit_sum.size();
		if (number_circuit == 0)
		{
			std::cout << "The number of circuit you have created is zero. So we will create a new circuit.";
			Sleep(2000);
			page_add_circuit(circuit_sum);
		}
		else
		{
			std::cout << "Which circuit do you want to manipulate?";
			int order{};
			input_max(order, number_circuit - 1);
			page_circuit_information(circuit_sum, order);
		}
	}

	}
}
void interface_class::page_circuit_information(std::vector<circuit>& circuit_sum, int order)
{
	circuit& my_circuit = circuit_sum[order];
	system("CLS");
	std::cout << "Menu Circuit" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "0: Go Back to the main page " << std::endl;
	std::cout << "1: Print components" << std::endl;
	std::cout << "2: Add componnets" << std::endl;
	std::cout << "3: Print information" << std::endl;
	std::cout << "4: Change voltage" << std::endl;
	std::cout << "5: Change frequency" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	int option{};
	input_max(option, 5);
	while (option >= 0  && option <= 5) {
		switch (option) {
		case 0: {
			main_page(circuit_sum);
		}
		case 1: {
			my_circuit.print_components();
			std::cout << "Please enter the option you want: ";
			input_max(option, 5);
			break;
		}
		case 2: {
			page_add_component(circuit_sum, order);
		}
		case 3: {
			std::complex<double> total_impedance{ (0,0) };
			if (my_circuit.components_size() == 0) {
				std::cout << "Can not calculate its impedance as there is no components." << std::endl;
				std::cout << "Please enter the option you want: ";
				input_max(option, 5);
				break;
			}
			else
			{
				total_impedance = my_circuit.calculate_impedance(*my_circuit.get_start(), *my_circuit.get_end());
				my_circuit.reset_comming_edge();
				my_circuit.set_impedance(total_impedance);
				my_circuit.set_impedance_magnitude();
				my_circuit.set_phase_shift();
				my_circuit.print_information();
				std::cout << "Please enter the option you want: ";
				input_max(option, 5);
				break;
			}
		}
		case 4:{
			double voltage{};

			std::cout << "Voltage(V) = ";
			input_positive(voltage);
			my_circuit.set_voltage(voltage);
			std::cout << "Please enter the option you want: ";
			input_max(option, 5);
			break;
		}
		case 5: {
			double frequency{};
			std::cout << "Frequency(Hz) = ";
			input_positive(frequency);
			my_circuit.set_frequency(frequency);
			std::cout << "Please enter the option you want: ";
			input_max(option, 5);
			break;
		}
		}

	}


}
void interface_class::page_add_circuit(std::vector<circuit>& circuit_sum)
{
	system("CLS");
	std::cout << "Menu Circuit" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "0: Go back to the main page." << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Creat circuit " << circuit_sum.size() << std::endl;
	double voltage{};
	double frequency{};
	std::cout << "Voltage(V) =  ";
	input_positive(voltage);
	std::cout << "Frequency(Hz) =  ";
	input_positive(frequency);
	circuit_sum.push_back(circuit(voltage, frequency));
	std::cout << "The circuit" << circuit_sum.size() - 1 << "has been created";
	main_page(circuit_sum);
	system("CLS");
}
void interface_class::page_add_component(std::vector<circuit>& circuit_sum, int order)
{
	system("CLS");
	std::cout << "Menu 2" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "0: Go Back to the main page. " << std::endl;
	std::cout << "1: Add a new resistor." << std::endl;
	std::cout << "2: Add a new capacitor." << std::endl;
	std::cout << "3: Add a new inductor." << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	int menu_number{};
	std::cin >> menu_number;
	switch (menu_number) {
	case 0:
		main_page(circuit_sum);
	case 1:
		page_add_resistor(circuit_sum, order);
		break;
	case 2:
		page_add_capacitor(circuit_sum, order);
		break;
	case 3:
		page_add_inductor(circuit_sum, order);
		break;
	}

}
void interface_class::page_add_resistor(std::vector<circuit>& circuit_sum, int order)
{
	system("CLS");
	circuit& my_circuit = circuit_sum[order];
	std::cout << "Menu Resistor" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Option list" << std::endl;
	std::cout << "0: Go back to the circuit menu." << std::endl;
	std::cout << "1: Creat a new resistor." << std::endl;
	std::cout << "2: Print all components information" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	int option;
	std::cout << "Please enter the option you want: ";
	input_max(option, 2);
	while (option == 0 || option == 1 || option == 2) {
		switch (option) {
		case 0: {
			page_circuit_information(circuit_sum, order);
			break;
		}

		case 1: {
			double resistance{ 0 };
			std::cout << std::endl << "Resistance(Ohm) = ";
			input_positive(resistance);
			my_circuit.add_resistor(*new resistor(resistance, my_circuit.get_frequency()));
			if (my_circuit.components_size() == 1) {
				my_circuit.get_components(0)->set_front_nodes(my_circuit.get_start()); //Set the front nodes of the first components is the start node
				my_circuit.get_components(0)->set_after_nodes(my_circuit.get_end()); // Set the after nodes of the first components is the end node
				my_circuit.get_end()->comming_edge_plus(); // The edgee entering the end node plus one.
				my_circuit.get_start()->add_child(*my_circuit.get_components(0));
				std::cout << "The first component has been added." << std::endl;
			}
			else
			{
				int order{};
				std::cout << "Which componnet do you want to connect to ? The order of components starts from zero: ";
				input_max(order, my_circuit.components_size()-2);
				std::cout << "Do you want connect in parallel or in series? Please enter p for parallel and s for series: ";
				std::string answer;
				input_p_s(answer);
				if (answer == "p") {
					my_circuit.add_parallel(*my_circuit.get_components(order), *my_circuit.get_components(my_circuit.components_size() - 1));
				}
				else if (answer == "s") {
					my_circuit.add_series(*my_circuit.get_components(order), *my_circuit.get_components(my_circuit.components_size() - 1));
				}
			}
			std::cout << "resistor added successfully. Please enter the option you want";
			input_max(option, 2);
			break;
		}
		case 2: {
			my_circuit.print_components();
			std::cout << "Please enter the option you want: ";
			input_max(option, 2);
			break;
		}
		}
	}
}
void interface_class::page_add_capacitor(std::vector<circuit>& circuit_sum, int order)
{
	system("CLS");
	circuit& my_circuit = circuit_sum[order];
	std::cout << "Menu Capacitor" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Option list" << std::endl;
	std::cout << "0: Go back to the circuit menu." << std::endl;
	std::cout << "1: Creat a new capacitor." << std::endl;
	std::cout << "2: Print all components information" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	int option;
	std::cout << "Please enter the option you want: ";
	input_max(option, 2);
	while (option == 0 || option == 1 || option == 2) {
		switch (option) {
		case 0: {
			page_circuit_information(circuit_sum, order);
			break;
		}

		case 1: {
			double capacitance{ 0 };
			std::cout << std::endl << "Capacitance(F) = ";
			input_positive(capacitance);
			my_circuit.add_capacitor(*new capacitor(capacitance, my_circuit.get_frequency()));
			if (my_circuit.components_size() == 1) {
				my_circuit.get_components(0)->set_front_nodes(my_circuit.get_start()); 
				my_circuit.get_components(0)->set_after_nodes(my_circuit.get_end()); 
				my_circuit.get_end()->comming_edge_plus();
				my_circuit.get_start()->add_child(*my_circuit.get_components(0));
				std::cout << "The first component has been added." << std::endl;
			}
			else
			{
				int order{};
				std::cout << "Which componnet do you want to connect to ? The order of components starts from zero: ";
				input_max(order, my_circuit.components_size() - 2);
				std::cout << "Do you want connect in parallel or in series? Please enter p for parallel and s for series: ";
				std::string answer;
				input_p_s(answer);
				if (answer == "p") {
					my_circuit.add_parallel(*my_circuit.get_components(order), *my_circuit.get_components(my_circuit.components_size() - 1));
				}
				else if (answer == "s") {
					my_circuit.add_series(*my_circuit.get_components(order), *my_circuit.get_components(my_circuit.components_size() - 1));
				}
			}
			std::cout << "capacitor added successfully. Please enter the option you want";
			input_max(option, 2);
			break;
		}
		case 2: {
			my_circuit.print_components();
			std::cout << "Please enter the option you want: ";
			input_max(option, 2);
			break;
		}
		}
	}
}
void interface_class::page_add_inductor(std::vector<circuit>& circuit_sum, int order)
{
	system("CLS");
	circuit& my_circuit = circuit_sum[order];
	std::cout << "Menu Inductor" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Option list" << std::endl;
	std::cout << "0: Go back to the circuit  menu." << std::endl;
	std::cout << "1: Creat a new inductor." << std::endl;
	std::cout << "2: Print all components information" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	int option;
	std::cout << "Please enter the option you want: ";
	input_max(option, 2);
	while (option == 0 || option == 1 || option == 2) {
		switch (option) {
		case 0: {
			page_circuit_information(circuit_sum, order);
			break;
		}

		case 1: {
			double inductance{ 0 };
			std::cout << std::endl << "Inductance(H) = ";
			input_positive(inductance);
			my_circuit.add_inductor(*new inductor(inductance, my_circuit.get_frequency()));
			if (my_circuit.components_size() == 1) {
				my_circuit.get_components(0)->set_front_nodes(my_circuit.get_start());
				my_circuit.get_components(0)->set_after_nodes(my_circuit.get_end());
				my_circuit.get_end()->comming_edge_plus(); 
				my_circuit.get_start()->add_child(*my_circuit.get_components(0));
				std::cout << "The first component has been added." << std::endl;
			}
			else
			{
				int order{};
				std::cout << "Which componnet do you want to connect to ? The order of components starts from zero: ";
				input_max(order, my_circuit.components_size() - 2);
				std::cout << "Do you want connect in parallel or in series? Please enter p for parallel and s for series: ";
				std::string answer;
				input_p_s(answer);
				if (answer == "p") {
					my_circuit.add_parallel(*my_circuit.get_components(order), *my_circuit.get_components(my_circuit.components_size() - 1));
				}
				else if (answer == "s") {
					my_circuit.add_series(*my_circuit.get_components(order), *my_circuit.get_components(my_circuit.components_size() - 1));
				}
			}
			std::cout << "inductor added successfully. Please enter the option you want";
			input_max(option, 2);
			break;
		}
		case 2: {
			my_circuit.print_components();
			std::cout << "Please enter the option you want: ";
			input_max(option, 2);
			break;
		}
		}
	}
}
void interface_class::main_interface()
{
	std::vector<circuit> circuit_sum;
	main_page(circuit_sum);
}