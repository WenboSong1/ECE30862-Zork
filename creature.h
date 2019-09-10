#ifndef CREATURE_H
#define CREATURE_H
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"


using namespace rapidxml;
using namespace std;

class creature {
public:
	creature();
	virtual ~creature();
    virtual xml_node<>* search(xml_node<>*, string);
	virtual int attack(xml_node<>*, string);
	virtual int add(xml_document<>&, xml_node<>*, string);
    virtual int remove(string, xml_node<>*);
};
#endif /* SUBJECT_H */