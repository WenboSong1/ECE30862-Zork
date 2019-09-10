#ifndef CONTAINER_H
#define CONTAINER_H
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

class container {
public:
	container();
	virtual ~container();
	virtual xml_node<>* search(xml_node<>*, string);
	virtual void open(xml_node<>*);
    virtual void put(xml_document<>&, xml_node<>*, string, string*);
};
#endif /* SUBJECT_H */