/*************************************************************************
    This is the record of an assignment.
    It includes the assignment's name, course, date created and due date
    
    Overloaded comparison operators compare the due dates,
    with less than meaning that the left operand is due before
    the right operand (i.e. the student has less time to complete it).

	Patricia Lindner	February 2022	OU EECS
*************************************************************************/
#include <iostream>
#include <string>
#include "date_time.h"
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
class Assignment{
	public:
		Assignment();

		std::string get_name()const {return name;}
        std::string get_course()const {return course;}
		DateTime get_entered()const {return entered;}
		DateTime get_due()const {return due;}

		bool operator < (const Assignment& ap)const {return due < ap.due;}
		bool operator > (const Assignment& ap)const {return ap.due < due;}
		bool operator <= (const Assignment& ap)const {return !(ap.due < due);}
		bool operator >= (const Assignment& ap)const {return !(due < ap.due);}
		bool operator != (const Assignment& ap)const {return (due < ap.due || ap.due < due);}
		bool operator == (const Assignment& ap)const {return !(due < ap.due || ap.due < due);}
		
		unsigned minutes_til_due()const;
        unsigned minutes_waiting()const;

		void input(std::istream& ins);
		void output(std::ostream& outs)const;

	private:
		std::string name;
        std::string course;
		DateTime entered;
		DateTime due;
};

// A useful non-member function
void convert_minutes(unsigned m);

// Input and Output Operators for those who want to use them.
std::istream& operator >> (std::istream& ins, Assignment & ap);
std::ostream& operator << (std::ostream& outs, const Assignment& ap);

#endif