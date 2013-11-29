#ifndef KUL_MODEL_H
#define KUL_MODEL_H

#include <string>
#include <sstream>

#include "nodepath.h"

class KulModel {

protected:
	NodePath nodePath;

public:
	KulModel(){};
	NodePath getNodePath();
	std::string toStringToSave();
	void loadSavedFile(std::string);
};

#endif