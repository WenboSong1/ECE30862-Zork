#ifndef ITEM_H
#define ITEM_H
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

class item {
public:
	item();
	virtual ~item();
	virtual xml_node<>* search(xml_node<>*, string);
    virtual int cout(xml_node<>*);
	virtual void read(xml_node<>*);
    virtual void showi(string*, int);
	virtual int take(string, xml_node<>*, string*);
    virtual void drop(xml_document<>&, xml_node<>*, string, string*);
};
#endif /* SUBJECT_H */