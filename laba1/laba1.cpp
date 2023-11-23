#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class Pipe {
public:
	std::string name;
	double length;
	double diameter;
	bool under_repair;

	Pipe(const std::string& n, double len, double dia, bool repair = false) :
		name(n), length(len), diameter(dia), under_repair(repair) {}

	void toggleRepairStatus() {
		under_repair = !under_repair;
	}

	void display() const {
		std::cout << "Pipe: " << name << ", Length: " << length << "км, Диаметр " << diameter << " mm, ";
		if (under_repair) {
			std::cout << "under repair";
		}
		else {
			std::cout << "not under repair";
		}
		std::cout << std::endl;
	}

};

class CompressorStation {
public:
	std::string name;
	int num_workshops;
	int num_workshops_in_operation;
	double efficiency;
	CompressorStation(const std::string& n, int workshops, int workshops_in_operation, double eff) :
		name(n), num_workshops(workshops), num_workshops_in_operation(workshops_in_operation), efficiency(eff) {}

	void startWorkshop() {
		if (num_workshops_in_operation < num_workshops) {
			num_workshops_in_operation++;
		}
	}

	void stopWorkshop() {
		if (num_workshops_in_operation > 0) {
			num_workshops_in_operation--;
		}
	}

	void display() const {
		std::cout << "Compressor Station: " << name << ", Total Workshops: " << num_workshops << ", Workshops in Operation: " << num_workshops_in_operation
			<< ", Efficiency: " << efficiency << std::endl;
	}
};

void saveData(const std::vector<Pipe>& pipes, const std::vector<CompressorStation>& stations) {
	std::ofstream outFile("data.txt", std::ios::out);
	if (!outFile.is_open()) {
		std::cerr << "Error opening the file to save data." << std::endl;
		return;
	}

	for (const auto& pipe : pipes) {
		outFile << "Pipe" << std::endl;
		outFile << pipe.name << std::endl;
		outFile << pipe.length << std::endl;
		outFile << pipe.diameter << std::endl;
		outFile << pipe.under_repair << std::endl;
	}

	for (const auto& station : stations) {
		outFile << "Station" << std::endl;
		outFile << station.name << std::endl;
		outFile << station.num_workshops << std::endl;
		outFile << station.num_workshops_in_operation << std::endl;
		outFile << station.efficiency << std::endl;
	}

	outFile.close();
}

void loadData(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations) {
	std::ifstream inFile("data.txt", std::ios::in);
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file to load data." << std::endl;
		return;
	}

	pipes.clear();
	stations.clear();

	std::string line;
	while (std::getline(inFile, line)) {
		std::istringstream iss(line);
		std::string type;
		iss >> type;
		if (type == "Pipe") {
			std::string name;
			double length, diameter;
			bool under_repair;
			getline(inFile, name);
			inFile >> length >> diameter >> std::boolalpha >> under_repair;
			pipes.emplace_back(name, length, diameter, under_repair);
		}
		if (type == "Station") {
			std::string name;
			int num_workshops, num_workshops_in_operation;
			double efficiency;
			getline(inFile, name);
			inFile >> num_workshops >> num_workshops_in_operation >> efficiency;
			stations.emplace_back(name, num_workshops, num_workshops_in_operation, efficiency);
		}
	}
}
int main() {
	std::vector<Pipe> pipes;
	std::vector<CompressorStation> stations;


	int choice;
	do {
		std::cout << "1. Add Pipe" << std::endl;
		std::cout << "2. Add Compressor Station" << std::endl;
		std::cout << "3. View All Objects" << std::endl;
		std::cout << "4. Edit Pipe" << std::endl;
		std::cout << "5. Edit Compressor Station" << std::endl;
		std::cout << "6. Save" << std::endl;
		std::cout << "7. Load" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "Select an action: ";
		std::cin >> choice;

		switch (choice) {
		case 1: {
			std::string name;
			double length, diameter;
			std::cin.ignore(); // Игнорируем символ новой строки после ввода предыдущего значения
			std::cout << "Enter the pipe name (Warning: allowed symbols are 1-9, a-z and '_'): ";
			std::getline(std::cin, name);
			std::cout << "Enter the pipe length (in km): ";
			std::cin >> length;
			std::cout << "Enter the pipe diameter (in mm): ";
			std::cin >> diameter;
			pipes.emplace_back(name, length, diameter, false);
			break;
		}
		case 2: {
			std::string name;
			int num_workshops, num_workshops_in_operation;
			double efficiency;
			std::cin.ignore(); // Игнорируем символ новой строки после ввода предыдущего значения
			std::cout << "Enter the Compressor Station name (Warning: allowed symbols are 1-9, a-z and '_'): ";
			std::getline(std::cin, name);
			std::cout << "Enter the total number of workshops: ";
			std::cin >> num_workshops;
			std::cout << "Enter the number of workshops in operation: ";
			std::cin >> num_workshops_in_operation;
			std::cout << "Enter the efficiency of the Compressor Station: ";
			std::cin >> efficiency;
			stations.emplace_back(name, num_workshops, num_workshops_in_operation, efficiency);
			break;
		}
		case 3: {
			std::cout << "All objects:" << std::endl;
			for (const auto& pipe : pipes) {
				pipe.display();
			}
			for (const auto& station : stations) {
				station.display();
			}
			break;
		}
		case 4: {
			std::cin.ignore(); // Игнорируем символ новой строки после ввода предыдущего значения
			std::cout << "Enter the name of the pipe to edit: ";
			std::string name;
			std::getline(std::cin, name);
			bool found = false;
			for (auto& pipe : pipes) {
				if (pipe.name == name) {
					pipe.toggleRepairStatus();
					std::cout << "Repair status of pipe '" << name << "' changed." << std::endl;
					found = true;
					break;
				}
			}
			if (!found) {
				std::cout << "Pipe with name '" << name << "' not found." << std::endl;
			}
			break;
		}
		case 5: {
			std::cin.ignore(); // Игнорируем символ новой строки после ввода предыдущего значения
			std::cout << "Enter the name of the Compressor Station to edit: ";
			std::string name;
			std::getline(std::cin, name);
			bool found = false;
			for (auto& station : stations) {
				if (station.name == name) {
					int choice;
					std::cout << "Select action: 1. Start Workshop 2. Stop Workshop: ";
					std::cin >> choice;
					if (choice == 1) {
						station.startWorkshop();
						std::cout << "Workshop at Compressor Station '" << name << "' started." << std::endl;
					}
					else if (choice == 2) {
						station.stopWorkshop();
						std::cout << "Workshop at Compressor Station '" << name << "' stopped." << std::endl;
					}
					else {
						std::cout << "Invalid choice." << std::endl;
					}
					found = true;
					break;
				}
			}
			if (!found) {
				std::cout << "Compressor Station with name '" << name << "' not found." << std::endl;
			}
			break;
		}
		case 6: {
			saveData(pipes, stations);
			std::cout << "Data saved to 'data.txt'." << std::endl;
			break;
		}
		case 7: {
			loadData(pipes, stations);
			std::cout << "Data loaded from 'data.txt'." << std::endl;
			break;
		}
		case 0:
			std::cout << "Exiting the program." << std::endl;
			break;
		default:
			std::cout << "Invalid choice." << std::endl;
			break;
		}
	} while (choice != 0);
	return 0;
}
