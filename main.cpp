#include <string.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "room.h"
#include "item.h"
#include "container.h"
#include "creature.h"
#include "trigger.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

int main(void) {

	
	string filename;
	string type;
	room* newroom = new room();
	item* newitem = new item();
	container* newcontainer  = new container();
	creature* newcreature = new creature();
	trigger* newtrigger = new trigger();
	string nextroom;
	string action[7];
	string com[7];
	string container;
	string creature;
	string item;
	string cmd; //the action after turn on
	string command;
	string owner;
	string has;
	string tritem;
	string status;
	int found = 0;
	int over = 0;
	int turn = 0;
	int check = 0;
	int have = 0; // check if the item in the inventory or container
	int attack = 0;
	int number_item = 0;
	int i = 0;
	int y = 0;
	int ctri = 0;
	int rtri = 0;
	int op = 0; //operation of trigger
	int chappened = 0;
	int rhappened = 0;
	int room = 0;
	int cre = 0;
	int co = 0;
	int ro = 0;
	string item_status;

	std::cout << "please type the xmlfile name:" << std::endl;
	cin >> filename;
	//bfilename = "triggersample.xml";
	xml_document<> doc;
	ifstream theFile;
	theFile.open(filename);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	// Find our root node
	xml_node<>* root_node = doc.first_node("map");
	
	xml_node<> * room_node = root_node->first_node("room");
	xml_node<> * item_node;
	xml_node<> * container_node = NULL;
	xml_node<> * creature_node;
	xml_node<> * attack_action;
	xml_node<> * trigger_room;
	xml_node<> * trigger_creature;
	xml_node<> * trigger_action;
	newroom->print(room_node);
	number_item = newitem->cout(root_node);
	string inventory[number_item];
	for(i = 0; i < number_item; i++ ){
		inventory[i] = "empty";
	}
	if(room_node->first_node("trigger")){
		trigger_room = room_node->first_node("trigger");
		rtri = newtrigger->check(room_node);
		rhappened = 0;
		room = 1;
	}
	else 
	{
		room = 0;
	}
	if(room_node->first_node("creature")){
		trigger_creature = newcreature->search(root_node,room_node->first_node("creature")->value());
		if(trigger_creature->first_node("trigger")){
	 		ctri = newtrigger->check(trigger_creature);
			trigger_creature = trigger_creature->first_node("trigger");
			chappened = 0;
			cre = 1;
		}
		else{
			cre = 0;
		}
	}



	
	while(1){

		
		//trigger without command
		if(rtri != 0 && rhappened == 0 && room == 1){
			if(rtri == 3){
				has = trigger_room->first_node("condition")->first_node("has")->value();
				tritem = trigger_room->first_node("condition")->first_node("object")->value();
				owner = trigger_room->first_node("condition")->first_node("owner")->value();
				if(has == "yes"){
					if(owner == "inventory"){
						i = 0; 
						while(inventory[i] != "empty"){
							if(inventory[i] == tritem){
								op = 1;
								ro = 1;
							}
							i++;
						}
					}					
				}
				else if(has == "no"){
					if(owner == "inventory"){
						i = 0; 
						while(inventory[i] != "empty"){
							if(inventory[i] == tritem){
								op = 1;								
							}
							i++;
						}
					}
					if(op == 1){
						op = 0;
					}
					else{
						op = 1;
						ro = 1;
					}
				}
			}
			else if(rtri == 4){
				status = trigger_room->first_node("condition")->first_node("status")->value();
				tritem = trigger_room->first_node("condition")->first_node("object")->value();
				item_node = newitem->search(root_node, tritem);
				if(item_node->first_node("status")){
					item_status = item_node->first_node("status")->value();
				}
				if(item_status == status){
					op = 1;
					ro = 1;
				}
			}
		}

		if(ctri != 0 && chappened == 0 && cre == 1){
			if(ctri == 3){
				has = trigger_creature->first_node("condition")->first_node("has")->value();
				tritem = trigger_creature->first_node("condition")->first_node("object")->value();
				owner = trigger_creature->first_node("condition")->first_node("owner")->value();
				if(has == "yes"){
					if(owner == "inventory"){
						i = 0; 
						while(inventory[i] != "empty"){
							if(inventory[i] == tritem){
								op = 1;
								co = 1;
							}
							i++;
						}
					}					
				}
				else if(has == "no"){
					if(owner == "inventory"){
						i = 0; 
						while(inventory[i] != "empty"){
							if(inventory[i] == tritem){
								op = 1;								
							}
							i++;
						}
					}
					if(op == 1){
						op = 0;
					}
					else{
						op = 1;
						co = 1;
					}
				}
			}
			else if(ctri == 4){
				status = trigger_creature->first_node("condition")->first_node("status")->value();
				tritem = trigger_creature->first_node("condition")->first_node("object")->value();
				item_node = newitem->search(root_node, tritem);
				if(item_node->first_node("status")){
					item_status = item_node->first_node("status")->value();
				}
				if(item_status == status){
					op = 1;
					co = 1;
				}
			}
		}

		if(op == 1 && rhappened == 0 && ro == 1){
			cout << trigger_room->first_node("print")->value() << endl;
			if(trigger_creature->first_node("action")){
			trigger_action = trigger_room->first_node("action");
			rhappened = 1;
			ro = 0;
			}
			else{
				op = 0;
				rhappened = 1;
			}
		}

		if(op == 1 && chappened == 0 && co == 1){
			cout << trigger_creature->first_node("print")->value() << endl;
			if(trigger_creature->first_node("action")){
			trigger_action = trigger_creature->first_node("action");
			chappened = 1;
			co = 0;
			}
			else{
				op = 0;
				chappened = 1;
			}
		}

		//get input
		if(turn == 0 && (attack == 0 || attack == 2) && op == 0){
			cin >> action[0];
			if(action[0] == "open" || action[0] == "turn" || action[0] == "take" || action[0] == "read" || action[0] == "drop" || action[0] == "game" || action[0] == "put" || action[0] == "open" || action[0] == "attack" || action[0] == "add" || action[0] == "delete" || action[0] == "update"){
				cin >> action[1];
				if(action[1] == "on" || action[0] == "put" || action[0] == "attack" || action[0] == "add")
				{
					cin >> action[2];
					if(action[2] == "in" || action[2] == "with" || action[0] == "add"){
						cin >> action[3];
					}
				}
			}
		}
		else{
			i = 0;
			found = 0;

			if(attack == 1){
				cmd = attack_action->value();
				if(attack_action->next_sibling("action")){
					attack_action = attack_action->next_sibling("action");
				}
				else{
					attack = 0;
				}
				
			}

			if(op == 1 || op == 2){
				cmd = trigger_action->value();
				if(trigger_action->next_sibling("action")){
					trigger_action = trigger_action->next_sibling("action");
				}
				else{
					op = 0;
				}
				
			}
			
		
			std::istringstream iss(cmd);
			iss >> action[0] >> action[1] >> action[2] >> action[3];
			
			cmd = action[0];
			if ('A'<=cmd[i] && cmd[i]<='Z'){
		   	 	cmd[i]=char(((int)cmd[i])+32);
			}
			action[0] = cmd;
			cmd = action[1];
			if ('A'<=cmd[i] && cmd[i]<='Z'){
		   	 	cmd[i]=char(((int)cmd[i])+32);
			}
			action[1] = cmd;

			turn = 0;
			i = 0;
			found = 0;
		}

		if((rtri == 1 || rtri == 2) && rhappened == 0 && room == 1){
			command = trigger_room->first_node("command")->value();
			std::istringstream iss(command);
			iss >> com[0] >> com[1] >> com[2] >> com[3];
			
			command = com[0];
			if ('A'<=command[i] && command[i]<='Z'){
		   	 	command[i]=char(((int)command[i])+32);
			}
			com[0] = command;
			//cout << cmd << endl;
			

			if(action[0] == com[0] && action[1] == com[1] && action[2] == com[2] && action[3] == com[3]){
				if(rtri == 1){
					has = trigger_room->first_node("condition")->first_node("has")->value();
					tritem = trigger_room->first_node("condition")->first_node("object")->value();
					owner = trigger_room->first_node("condition")->first_node("owner")->value();
					//cout << has << owner << endl;
					if(has == "yes"){
						if(owner == "inventory"){
							i = 0; 
							while(inventory[i] != "empty"){
								if(inventory[i] == tritem){
									op = 2;
								}
							}
						}					
					}
					else if(has == "no"){
						if(owner == "inventory"){
							i = 0; 
							while(inventory[i] != "empty"){
								if(inventory[i] == tritem){
									//cout << inventory[i] << tritem << endl;
									op = 2;								
								}
								i++;
							}
						}
						if(op == 2){
							op = 0;
						}
						else{
							op = 2;
						}
					}
					//cout << op << endl;	
				}
				else if(rtri == 2){
					status = trigger_room->first_node("condition")->first_node("status")->value();
					tritem = trigger_room->first_node("condition")->first_node("object")->value();
					item_node = newitem->search(root_node, tritem);
					if(item_node->first_node("status")){
						item_status = item_node->first_node("status")->value();
					}
					if(item_status == status){
						op = 2;		
					}
				}
			}
			rtri = 0;
		}


		if((ctri == 1 || ctri == 2) && chappened == 0 && cre == 1){
			command = trigger_creature->first_node("command")->value();
			std::istringstream iss(command);
			iss >> com[0] >> com[1] >> com[2] >> com[3];
			
			command = com[0];
			if ('A'<=command[i] && command[i]<='Z'){
		   	 	command[i]=char(((int)command[i])+32);
			}
			com[0] = command;
			//cout << cmd << endl;
			

			if(action[0] == com[0] && action[1] == com[1] && action[2] == com[2] && action[3] == com[3]){
				if(ctri == 1){
					has = trigger_creature->first_node("condition")->first_node("has")->value();
					tritem = trigger_creature->first_node("condition")->first_node("object")->value();
					owner = trigger_creature->first_node("condition")->first_node("owner")->value();
					cout << has << owner << endl;
					if(has == "yes"){
						if(owner == "inventory"){
							i = 0; 
							while(inventory[i] != "empty"){
								if(inventory[i] == tritem){
									op = 2;
								}
							}
						}					
					}
					else if(has == "no"){
						if(owner == "inventory"){
							i = 0; 
							while(inventory[i] != "empty"){
								if(inventory[i] == tritem){
									cout << inventory[i] << tritem << endl;
									op = 2;								
								}
								i++;
							}
						}
						if(op == 2){
							op = 0;
						}
						else{
							op = 2;
						}
					}
				}
				else if(ctri == 2){
					status = trigger_creature->first_node("condition")->first_node("status")->value();
					tritem = trigger_creature->first_node("condition")->first_node("object")->value();
					item_node = newitem->search(root_node, tritem);
					if(item_node->first_node("status")){
						item_status = item_node->first_node("status")->value();
					}
					if(item_status == status){
						op = 2;		
					}
				}
			}
			ctri = 0;
		}

		//command operation
		if(action[0] == "game" && action[1] == "over")
		{
			std::cout << "Victory!" << std::endl;
			return 0;
		}


		//operate command
		if(op == 2 && rhappened == 0 && chappened == 0 && attack == 0){
			if(room == 1){
			cout << trigger_room->first_node("print")->value() << endl;
			if(trigger_room->first_node("action")){
				trigger_action = trigger_room->first_node("action");
				rhappened = 1;
			}
			else{
				op = 0;
			}
			if(trigger_room->first_node("type")){
				string ta = trigger_room->first_node("type")->value();
				if(ta == "permanent"){
					action[0] = "A";
				}
			}
			}
			if(cre == 1){
			cout << trigger_creature->first_node("print")->value() << endl;
			if(trigger_creature->first_node("action")){
				trigger_action = trigger_creature->first_node("action");
				chappened = 1;
			}
			else{
				op = 0;
			}
			if(trigger_creature->first_node("type")){
				string ta = trigger_creature->first_node("type")->value();
				if(ta == "permanent"){
					action[0] = "A";
				}
			}
			}
		}
		else if(over == 1 && action[0] == "open" && action[1] == "exit"){
			cout << "Game Over" << endl;
			return 0;
		}
		else if(action[0] == "n" || action[0] == "s" || action[0] == "e" || action[0] == "w"){
			nextroom = newroom->move(room_node, action[0]);
			
			if(nextroom != "no"){
				room_node = newroom->search(root_node,nextroom);
				if(room_node->first_node("trigger")){
					trigger_room = room_node->first_node("trigger");
					rtri = newtrigger->check(room_node);
					rhappened = 0;
					room = 1;
				}
				else{
					room = 0;
					rhappened = 0;
				}
				if(room_node->first_node("creature")){
					trigger_creature = newcreature->search(root_node,room_node->first_node("creature")->value());
					if(trigger_creature->first_node("trigger")){
						ctri = newtrigger->check(trigger_creature);
						trigger_creature = trigger_creature->first_node("trigger");
						chappened = 0;
						cre = 1;
					}
				}
				else{
					cre = 0;
					chappened = 0;
				}
				//cout << rtri << ctri << endl;
				newroom->print(room_node);
				have = 0;
				container_node = NULL;
			}
			if(room_node->first_node("type"))
			{
				type = room_node->first_node("type")->value();
				if(type == "exit"){
					over = 1;
				}
			}
		}
		else if(action[0] == "i"){
			newitem->showi(inventory, number_item);
		}
		else if(action[0] == "turn" && action[1] == "on"){
			for(i = 0; i < number_item; i++ )
			{
				if(inventory[i] == action[2])
				{
					have = 1;
				}
			}
			if(have == 1){
				turn = 1;
				item_node = newitem->search(root_node, action[2]);
				std::cout << item_node->first_node("turnon")->first_node("print")->value() << std::endl;
				cmd = item_node->first_node("turnon")->first_node("action")->value();
			}
			else{
				std::cout << "Error!" << std::endl;
			}
		}
		else if(action[0] == "take"){
			check = newitem->take(action[1], room_node, inventory);
			item_node = newitem->search(root_node, action[1]);
			if(check == 0 && container_node != NULL){
				check = newitem->take(action[1], container_node, inventory);
			}
			if(check == 0){
				cout << "Error" << endl;
			}
			else{
				check = 0;
			}
		}
		else if(action[0] == "read"){
			for (i = 0;  i < number_item; i++ ){
				if(inventory[i] == action[1]){
				item_node = newitem->search(root_node, action[1]);
				newitem->read(item_node);
				have = 1;
				}
			}
			if(have == 0)
			{
				cout << "Error" << endl;
			}
			else{
				have = 0;
			}
		}
		else if(action[0] == "drop"){
			newitem->drop(doc, room_node, action[1], inventory);
		}
		else if(action[0] == "open"){
			for (xml_node<>* element_node = room_node->first_node("container"); element_node;element_node = element_node->next_sibling("container")){
				container = element_node->value();
				if(container == action[1])
				{
					container_node = newcontainer->search(root_node, action[1]);
					newcontainer->open(container_node);
					have = 1;
				}
      		}
			if(have == 0)
			{
				cout << "Error" << endl;
			}
			else{
				have = 0;
			}
			
		}
		else if(action[0] == "put"){
			for (xml_node<>* element_node = room_node->first_node("container"); element_node;element_node = element_node->next_sibling("container")){
				container = element_node->value();
				if(container == action[3])
				{
					container_node = newcontainer->search(root_node, action[3]);
					newcontainer->put(doc, container_node, action[1], inventory);
					have = 1;
				}
      		}
			if(have == 0)
			{
				cout << "Error" << endl;
			}
			else{
				have = 0;
			}
		}
		else if(action[0] == "attack"){
			for (xml_node<>* element_node = room_node->first_node("creature"); element_node;element_node = element_node->next_sibling("creature")){
				creature = element_node->value();
				if(creature == action[1]){
					creature_node = newcreature->search(root_node, action[1]);
					for(i = 0; i < number_item; i++){
						if(inventory[i] == action[3]){
							cout << "You assault the " << action[1] << " with " << action[3] << "." <<endl;
							attack = newcreature->attack(creature_node, action[3]);
							if(creature_node->first_node("attack")){
								attack_action = creature_node->first_node("attack")->first_node("action");
							}
							else{
								attack = 2;
							}
						}
					}		
				}
			}
			if(attack == 0){
				cout << "Error" << endl;
			}
		}
		else if(action[0] == "add"){
			newcreature->add(doc, newroom->search(root_node, action[3]), action[1]);
		}
		else if(action[0] == "delete"){
			newcreature->remove(action[1], room_node);
		}
		else if(action[0] == "update"){
			newtrigger->update(doc, newitem->search(root_node, action[1]), action[3]);
		}
		else if(action[0] == "A"){

		}
		else{
			cout << "Error" << endl;
		}

	}



	return 0;
}

