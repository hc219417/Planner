# Planner

This project is a linked list container that stores information about a student’s pending homework assignments. The list is always kept in order by the date that an assignment is due.

The `Date` class has been altered so that it can now have a date object set to today, using the computer’s internal clock. In the same file there is a new class called `DateTime`, which records the hour and minute when something happened as well as a date.

Using these two, a class called `Assignment` is defined, which records the *name* of an assignment (a string), the *course* the assignment is for (a string), the date/time the assignment was *entered* (a `DateTime`) and the date/time when the assignment is *due* (a `DateTime`). The overloaded comparison operators for the `Assignment` class are based on the date/time an assignment is due, so if assignment1 < assignment2 it means that assignment1 is due before assignment2, disregarding name, course, and time the assignment was entered.

Provided is the header and implementation files for the `Planner` class. This class stores a list of assignments that the student needs to complete. This list is stored in the form of a linked list of nodes. The list is **always** kept in order by the assignment due date, but the people who put the things into the list may not be recording them in that order. This means that when a new assignment is added, a search through the list is done to put it in the right place. *All comparison operators are overloaded for the `Assignment` class*, to facilitate this.

The `Planner` class offers the application programmer the following options:

1. Add a new assignment to the list (it will be inserted in order).
2. View the entire list of assignments, in the order they are stored.
3. Remove an assignment that has been completed. This uses the `find` and `remove` functions, both of which take a string which is the name of the assignment.
4. Learn the number of assignments that are waiting to be completed.
5. See the amount of time you have to complete the assignment that is due soonest.
6. See the average amount of time that assignments have been sitting in the list since they were entered.
7. Identify the assignment that has been in the list the longest.
8. Identify the assignment that was added to the list most recently.
9. See all assignments that must be completed by a date entered by the user.

The main has a menu for all these options.

A `load` and `save` function are provided, the save simply saving the information about the assignments, not the size of the list. The data file is formatted:

**assignment name**

**course**

**date the assignment was entered**

**time the assignment was entered**

**date the assignment is due**

**time the assignment is due**

Since linked lists are built using dynamic memory, the `Planner` class is “holding” dynamic memory and that means implementation of the Big 3 is required.
