#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "container.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

container::container() {}
container::~container() {}

xml_node<>* container::search(xml_node<>* root_node, string itemname) {
	string newitem;
	xml_node<>* target = NULL;
	for (xml_node<>* item_node = root_node->first_node("container"); item_node;item_node = item_node->next_sibling())
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


void container::open(xml_node<>* item) {

    xml_node<>* name = item->first_node("name");
	
	std::cout << name->value() << " contains";


    for (xml_node<>* item_node = item->first_node("item"); item_node;item_node = item_node->next_sibling("item"))
	{
        std::cout << " " << item_node->value();
        if(item_node->next_sibling("item")){
              std::cout << ",";
        }
	}
    
    std::cout << "." << std::endl;
}



void container::put(xml_document<>& doc, xml_node<>* target_container, string item_name, string inventory[]){
    int i = 0;
    while(inventory[i] != item_name){
        if(inventory[i] == "empty"){
            std::cout << "Error!" << std::endl;
             return;
        }
        i++;
    }
    while(inventory[i] != "empty"){
        inventory[i] = inventory[i+1];
        i++;
    }
    
    xml_node<> * new_node = doc.allocate_node(node_element, "item");
    target_container->prepend_node(new_node);  
    const char * text = doc.allocate_string(item_name.c_str(), strlen(item_name.c_str()));
    target_container->first_node("item")->value(text);
    std::cout << "Item " << item_name << " add to " << target_container->first_node("name")->value() << "." << std::endl;
    return;
}