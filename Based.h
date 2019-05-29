#pragma once


#include <iostream>

class Printable {
public: 
	virtual std::string getInformation() = 0;
};

class Named : public Printable {
private : 
	std::string name;
public: 
	Named(std::string pam) {
		name = pam;
	}
	std::string getInformation() override {
		return name;
	}
};