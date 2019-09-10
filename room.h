#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class room {
public:
	room();
	virtual ~room();
	virtual xml_node<>* search(xml_node<>*, string);
	virtual void print(xml_node<>*);
	virtual string move(xml_node<>*, string);

};
#endif /* SUBJECT_H */