#pragma once
#include<iostream>


class RegExpr {
public:
	virtual void print() = 0;
	virtual std::string toString() = 0;
	virtual ~RegExpr();
	size_t getType();
protected:
	size_t type;
};

