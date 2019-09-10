#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "creature.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

creature::creature() {}
creature::~creature() {}

xml_node<>* creature::search(xml_node<>* root_node, string itemname) {
	string newitem;
	xml_node<>* target = NULL;
	for (xml_node<>* item_node = root_node->first_node("creature"); item_node;item_node = item_node->next_sibling())
	{
		newitem = item_node->first_node("name")->value();
		if (newitem == itemname)
		{
			target = item_node;
		}
	}
    if(target == NULL){
        std::cout << "Error!" << std::endl;
    }
	return target;
}


int creature::attack(xml_node<>* creature, string item) {
    string weapon;
    for (xml_node<>* item_node = creature->first_node("vulnerability"); item_node;item_node = item_node->next_sibling("vulnerability"))
	{
		weapon = item_node->value();
		if (item == weapon)
		{
			if(creature->first_node("attack")){
				if(creature->first_node("attack")->first_node("print")){

              		std::cout << creature->first_node("attack")->first_node("print")->value() << std::endl;
            	}
			}
            return 1;
		}
	}
    std::cout << "Error!" << std::endl;
    return 0;
}

int creature::add(xml_document<>& doc, xml_node<>* target_room, string item_name){
   
    xml_node<> * new_node = doc.allocate_node(node_element, "creature");
    target_room->append_node(new_node);  
    const char * text = doc.allocate_string(item_name.c_str(), strlen(item_name.c_str()));
    target_room->first_node("creature")->value(text);
	xml_node<> * new_node = doc.allocate_node(node_element, "item");
    target_room->append_node(new_node);  
    const char * text = doc.allocate_string(item_name.c_str(), strlen(item_name.c_str()));
    target_room->first_node("item")->value(text);
    return 1;
}

int creature::remove(string item, xml_node<>* target_room){

    for (xml_node<>* element_node = target_room->first_node("item"); element_node;element_node = element_node->next_sibling())
	{
		if(element_node->value() == item){
            target_room->remove_node(element_node); 
            return 1;
        }
	}
    return 0;
}

