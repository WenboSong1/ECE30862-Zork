#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "trigger.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

trigger::trigger() {}
trigger::~trigger() {}

int trigger::check(xml_node<>* target_node){
    xml_node<>* trigger;
    xml_node<>* condition;
    if(target_node->first_node("trigger")){
        trigger = target_node->first_node("trigger");
        if(trigger->first_node("command")){
            condition = trigger->first_node("condition");
            if(condition->first_node("has")){
                return 1; //need command and has condition
            }
            else if(condition->first_node("status")){
                return 2; //need command and status condition
            }
        }
        else{
            condition = trigger->first_node("condition");
            if(condition->first_node("has")){
                return 3; //no command and has condition
            }
            else if(condition->first_node("status")){
                return 4; //no command and status condition
            }
        }

    }
    else{
        return 0; // no trigger
    }  
}

int trigger::update(xml_document<>& doc, xml_node<>* target_item, string status){

    if(target_item->first_node("status")){
        const char * text = doc.allocate_string(status.c_str(), strlen(status.c_str()));
        target_item->first_node("status")->value(text);
    }
    else{
        xml_node<> * new_node = doc.allocate_node(node_element, "status");
        target_item->append_node(new_node);  
        const char * text = doc.allocate_string(status.c_str(), strlen(status.c_str()));
        target_item->first_node("status")->value(text);
    }
    return 1;
}