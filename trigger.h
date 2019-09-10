#ifndef TRIGGER_H
#define TRIFFER_H
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

class trigger {
public:
	trigger();
	virtual ~trigger();
    virtual int check(xml_node<>*);
	virtual int update(xml_document<>&, xml_node<>*, string);

};
#endif /* SUBJECT_H */