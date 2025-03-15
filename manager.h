#ifndef MANAGER_H
#define MANAGER_H
#include<windows.h>
//#include "person.h"
#include <iostream>
using namespace std;
#include <string>

class persons{
    protected:
    string name;
    string password;
    string goal;
    int height;
    int weight;
    int age;
    int insuline_dosage;
    int sugar;
    int bp;
    public:
    persons(){                                                        //defalut constructor
        name = "unknown";
        password = "unknown";
        goal = "unknown";
        height = 0;
        weight = 0;
        age = 0;
        insuline_dosage= 0;
        sugar = 0;
        bp = 0;
    }
    persons(string n, string p, string g){                           //parameterized constructor
        name = n;
        password = p;
        goal = g;
    }
    void setName(string n){
        name = n;
    }
    string getName(){
        return name;
    }
    void setPassword(string p){
        password = p;
    }
    string getPassword(){
        return password;
    }
    /*void setGoal(string g){
        goal = g;
    }
    string getGoal(){
        return goal;*/
    void setinsuline_dosage(int s){
        insuline_dosage = s;
    }
    int getinsuline_dosage(){
        return insuline_dosage;
    }
    void setsugar(int b){
        sugar = b;
    }
    int getsugar(){
        return sugar;
    }
    void setbp(int d){
        bp = d;
    }
    int getbp(){
        return bp;
    }
    void setHeight(int h){
        height = h;
    }
    int getHeight(){
        return height;
    }
    void setWeight(int w){
        weight = w;
    }
    int getWeight(){
        return weight;
    }
    void setAge(int a){
      age = a;
    }
    int getAge(){
      return age;
    }

};
class manager{
public:
persons* person;
bool one(persons* person);
void save(persons* person);
persons* storage(string name, string password);
bool play(persons* person);
bool create();
bool login();
bool menu();
bool checkname(persons* person);
bool checkpassword(persons* person);
void add(persons* person);
};
#endif
