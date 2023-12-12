/**
 *   @file: planner.cc
 * @author: Hannah Culver
 *   @date: February 24, 2022
 *  @brief: implementation file for the planner class
 */

#include <iostream>
#include <string>
#include "planner.h"
using namespace std;

Planner::Planner(){
    head = NULL;
}

Planner::~Planner(){
    node* rmptr;
    while(head != NULL){
        rmptr = head;
        head = head -> link();
        delete rmptr;
    }
}

Planner::Planner(const Planner& other){
    if(other.head == NULL){
        head = NULL;
        return;
    }
    else{
        node* src, *dest;
        head = new node(other.head -> data());
        src = other.head -> link();
        dest = head;
        while(src != NULL){
            dest -> set_link(new node(src -> data()));
            src = src -> link();
            dest = dest -> link();
        }
    }
}
 
Planner& Planner::operator = (const Planner& other){
    if(this == &other){
        return *this;
    }
    node* rmptr;
    while(head != NULL){
        rmptr = head;
        head = head -> link();
        delete rmptr;
    }
    if(other.head == NULL){
        head = NULL;
        exit(0);    // tried putting 'return' here but kept getting an error message
    }               // (not sure if that'll mess anything up when you go to test it)
    else{
        node* src, *dest;
        head = new node(other.head -> data());
        src = other.head -> link();
        dest = head;
        while(src != NULL){
            dest -> set_link(new node(src -> data()));
            src = src -> link();
            dest = dest -> link();
        }
    }
    return *this;
}

void Planner::add(Assignment a){
    node* cursor, *previous;
    cursor = head;
    if(head == NULL){ //special case #1 (empty list)
        head = new node(a);
        return;
    }
    if(a.get_due() < head -> data().get_due()){ // special case #2 (assignment
        head = new node(a,cursor);              // needs to be put before head)
        return;
    }
    if(cursor -> link() == NULL){ //special case #3 (only one item in the list)
        cursor -> set_link(new node(a));
        return;
    }
    else{ //add assignment elsewhere
        while(cursor != NULL){
            previous = cursor;
            cursor = cursor -> link();
            if(a.get_due() < cursor -> data().get_due()){ //add assignment to middle of list
                node* tmp = new node(a,cursor);
                previous -> set_link(tmp);
                return;
            }
            else if(cursor -> link() == NULL){ //add assignment to end of list
                cursor -> set_link(new node(a));
                return;
            }
        }
    }
}

void Planner::display(std::ostream& outs)const{
    if(head == NULL){
        cout << "Error: empty list";
        return;
    }
    node* cursor = head;
    while(cursor != NULL){
        cout << cursor -> data();
        cursor = cursor -> link();
    }
}

Assignment Planner::find(std::string assignmentname){
    if(head == NULL){
        cout << "Error: empty list" << endl;
        return Assignment();
    }
    node* cursor = head;
    while(cursor != NULL){
        if(cursor -> data().get_name() == assignmentname){
            return cursor -> data();
        }
        cursor = cursor -> link();
    }
    return Assignment(); //default constructor
}

void Planner::remove(std::string assignmentname){
    node* cursor, *previous;
    cursor = head;
    if(head == NULL){ //special case #1 (empty list)
        cout << "Error: empty list" << endl;
        return;
    }
    if(head -> data().get_name() == assignmentname){    // special case #2 (head is already
        head = head -> link();                          // pointing to item that needs removed)
        delete cursor; 
    }
    else{
        while(cursor != NULL && cursor -> data().get_name() != assignmentname){
            previous = cursor;
            cursor = cursor -> link();
        }
        if(cursor != NULL){
            previous -> set_link(cursor -> link());
            delete cursor;
        }
    }
}

int Planner::waiting(){
    Assignment a;
    int count = 0;
    if(head == NULL){
        cout << "Error: empty list" << endl;
        return 0;
    }
    node* cursor = head;
    while(cursor != NULL){
        if(a.get_due() < cursor -> data().get_due()){ //a.get_due() is the same as saying 'now'
            count++;
        }
        cursor = cursor -> link();
    }
    return count;
}
        
unsigned Planner::due_next(){
    if(head == NULL){
        cout << "Error: empty list" << endl;
        return -1; //return -1 instead of 0 to avoid getting past due message in main
    }
    unsigned tmp = head -> data().minutes_til_due();
    return tmp;
}

unsigned Planner::average_wait(){
    int count = 0;
    unsigned sum = 0;
    if(head == NULL){
        cout << "Error: empty list" << endl;
        return 0;
    }
    node* cursor = head;
    while(cursor != NULL){
        sum += cursor -> data().minutes_waiting();
        cursor = cursor -> link();
        count++;
    }
    unsigned tmp = sum / count;
    return tmp;
}

unsigned Planner::oldest(){
    if(head == NULL){
        cout << "Error: empty list" << endl;
        return 0;
    }
    node* cursor = head;
    unsigned tmp = cursor -> data().minutes_waiting();
    if(cursor -> link() == NULL){
        return tmp;
    }
    else{
        cursor = cursor -> link();
        while(cursor != NULL){
            if(cursor -> data().minutes_waiting() > tmp){
                tmp = cursor -> data().minutes_waiting();
            }
            cursor = cursor -> link();
        }
        return tmp;
    }
    return tmp;
}

unsigned Planner::newest(){ //same as oldest() function...
    if(head == NULL){
        cout << "Error: empty list" << endl;
        return 0;
    }
    node* cursor = head;
    unsigned tmp = cursor -> data().minutes_waiting();
    if(cursor -> link() == NULL){
        return tmp;
    }
    else{
        cursor = cursor -> link();
        while(cursor != NULL){
            if(cursor -> data().minutes_waiting() < tmp){ //...except for this less than symbol
                tmp = cursor -> data().minutes_waiting();
            }
            cursor = cursor -> link();
        }
        return tmp;
    }
    return tmp;
}

void Planner::find_all(DateTime due_by){
    int count = 0;
    if(head == NULL){
        cout << "Error: empty list" << endl;
        return;
    }
    node* cursor = head;
    while(cursor != NULL){
        if(cursor -> data().get_due() < due_by){
            cout << cursor -> data();
            count++;
        }
        cursor = cursor -> link();
    }
    if(count == 0){
        cout << "None" << endl;
    }
}

void Planner::load(std::istream& ins){
    Assignment a;
    while(!ins.eof()){
        ins >> a;
        if(head == NULL){
            head = new node(a);
        }
        else{
            node* cursor = head;
            while(cursor -> link() != NULL){
                cursor = cursor -> link();
            }
            cursor -> set_link(new node(a));
        }
        while(ins.peek() == '\n' || ins.peek() == '\r'){
            ins.ignore(); //clear out last leftover newline
        }
    }
}

void Planner::save(std::ostream& outs)const{
    if(head == NULL){
        cout << "Error: empty list" << endl;
        return;
    }
    node* cursor = head;
    while(cursor != NULL){
        outs << cursor -> data();
        cursor = cursor -> link();
    }
}