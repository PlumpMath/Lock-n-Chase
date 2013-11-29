#include "kul_model.h"

NodePath KulModel::getNodePath() {
	return nodePath;
}

std::string KulModel::toStringToSave() {
	std::ostringstream s;
	s << setiosflags (ios::fixed) << setprecision(5) << nodePath.get_x() << "," 
	  << setiosflags (ios::fixed) << setprecision(5) << nodePath.get_y() << ","
	  << setiosflags (ios::fixed) << setprecision(5) << nodePath.get_z() << "\n";

	std::string result = s.str();

	//cout << "KulModel.toStringToSave() = " << result;

	return result;
}

void KulModel::loadSavedFile(std::string str) {
	nodePath.set_x(atoi(str.c_str()));

	str = str.substr(str.find_first_of(',') + 1, str.size());
	nodePath.set_y(atoi(str.c_str()));

	//str = str.substr(str.find_first_of(',') + 1, str.size());
	//nodePath.set_z(atoi(str.c_str()));
}