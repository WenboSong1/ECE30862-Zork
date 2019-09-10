#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "item.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

item::item() {}
item::~item() {}

xml_node<>* item::search(xml_node<>* root_node, string itemname) {
	string newitem;
	xml_node<>* target = NULL;
	for (xml_node<>* item_node = root_node->first_node("item"); item_node;item_node = item_node->next_sibling())
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

int item::cout(xml_node<>* root_node){
    int i = 0;
    for (xml_node<>* item_node = root_node->first_node("item"); item_node;item_node = item_node->next_sibling())
	{
		i++;
	}
    i++;
    return i;
}

void item::read(xml_node<>* item) {
	xml_node<>* description = item->first_node("writing");
	if(description){
	    std::cout << description->value() << std::endl;
    }
    else{
        std::cout << "Nothing written." << std::endl;
    }
}

void item::showi(string inventory[],int i){
    int x = 0;
    std::cout << "Inventory: ";
    while(x <= i){
 
       std:: cout << inventory[x] << " ";
        if(inventory[x+1] == "empty")
        {
            std:: cout << std::endl;
            return;
        }

        x++;
    }
    return;
}

int item::take(string item, xml_node<>* target_room, string inventory[]){
    int i = 0;

    while( inventory[i] != "empty"){
        i++;
    }

    for (xml_node<>* element_node = target_room->first_node("item"); element_node;element_node = element_node->next_sibling("item"))
	{
		if(element_node->value() == item){
            target_room->remove_node(element_node); 
            std::cout << "Item " << item << " added to inventory" << std::endl;
            inventory[i] = item;
            return 1;
        }
	}
    return 0;
}

void item::drop(xml_document<>& doc, xml_node<>* target_room, string item_name, string inventory[]){
    int i = 0;
    while(inventory[i] != item_name){
        if(inventory[i] == "empty"){
            std::cout << "Error!" << std::endl;
            return;
        }
        i++;
    }
    if(inventory[i] != item_name){
        std::cout << "Error!" << std::endl;
        return;
    }
    while(inventory[i] != "empty"){
        inventory[i] = inventory[i+1];
        i++;
    }
    
    xml_node<> * new_node = doc.allocate_node(node_element, "item");
    target_room->append_node(new_node);  
    const char * text = doc.allocate_string(item_name.c_str(), strlen(item_name.c_str()));
    target_room->first_node("item")->value(text);
    std::cout << item_name << " dropped." << std::endl;
    return;
}
