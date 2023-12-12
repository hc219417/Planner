/**
 *   @file: planner.h
 * @author: Hannah Culver
 *   @date: February 24, 2022
 *  @brief: header file for the planner class
 */

#include <iostream>
#include <string>
#include "node.h"
#include "date_time.h"
#include "assignment.h"
#ifndef PLANNER_H
#define PLANNER_H

class Planner{
    public:
        Planner();

        ~Planner();
        Planner(const Planner& other);
        Planner& operator = (const Planner& other);

        void add(Assignment a);
        void display(std::ostream& outs)const;

        Assignment find(std::string assignmentname);
        
        void remove(std::string assignmentname);
        
        int waiting();

        unsigned due_next();
        unsigned average_wait();
        unsigned oldest();
        unsigned newest();

        void find_all(DateTime due_by);

        void load(std::istream& ins);
        void save(std::ostream& outs)const;

    private:
        node* head;
        Assignment assignment;
};

#endif