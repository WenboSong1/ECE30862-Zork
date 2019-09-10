#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "room.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

room::room() {}
room::~room() {}

xml_node<>* room::search(xml_node<>* root_node, string roomname) {
	string newroom;
	xml_node<>* target = NULL;
	for (xml_node<>* room_node = root_node->first_node("room"); room_node; room_node = room_node->next_sibling())
	{
		newroom = room_node->first_node("name")->value();
		if (newroom == roomname)
		{
			target = room_node;
		}
	}

	return target;
}

void room::print(xml_node<>* room) {
	xml_node<>* description = room->first_node("description");
	
	std::cout << description->value() << std::endl;
}

string room::move(xml_node<>* room, string deriction) {
	string newd;
	string border;
	string newroom = "no";
	if (deriction == "n")
	{
		newd = "north";
	}
	else if (deriction == "s")
	{
		newd = "south";
	}
	else if (deriction == "e")
	{
		newd = "east";
	}
	else if (deriction == "w")
	{
		newd = "west";
	}

	for (xml_node<>* borderl = room->first_node("border"); borderl; borderl = borderl->next_sibling("border"))
	{
		border = borderl->first_node("direction")->value();
		if (border == newd)
		{
		
			newroom = borderl->first_node("name")->value();
		
			return newroom;
		}
	}
	if (newroom == "no")
	{
		std::cout << "Can't go that way!" << std::endl;
		return newroom;
	}

	return newroom;
}