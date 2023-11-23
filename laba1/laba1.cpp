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
		std::cout << "Pipe: " << name << ", Length: " << length << " km, Diameter: " << diameter << " mm, ";
		if (under_repair) {
			std::cout << "under repair";
		}
		else {
			std::cout << "not under repair";
		}
		std::cout << std::endl;
	}

};