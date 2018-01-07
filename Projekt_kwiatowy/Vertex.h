#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include "Blossom.h"

class BlossomMatching;


//-------------------------------------------------------------
class Edge
{
public:
	Edge(BlossomMatching* matching, Vertex* v1, Vertex* v2, int weight);
	Vertex* get_v1() { return v1; }
	Vertex* get_v2() { return v2; }
	int get_waight() { return weight; }
    void set_waight(int value){weight = value;}
	double get_charge_from_edge();
    std::pair<Blossom*,Blossom*> get_outers();
    double get_min_from_outers(Blossom* outer1, Blossom* outer2);
	bool update();
	bool if_matched() { return matched; }
    bool if_beetween_pairs(Blossom* outer1, Blossom* outer2);
    bool if_beetween_evens(Blossom* outer1, Blossom* outer2);
    bool if_beetween_even_and_pair(Blossom* outer1, Blossom* outer2);
    void flip(){matched = !matched;}
private:
	BlossomMatching* matching;
	//zamienic na podkresl.
	Vertex* v1;
	Vertex* v2;
	int weight;
	bool matched;
	
};


//-----------------------------------------------------------------------

class Vertex : public Blossom{
public:
    Vertex(int _id) : Blossom(), id(_id), totalCharge(0) {}
    double get_total_charge() { return totalCharge; }
    void set_total_charge(double value){totalCharge = value;}
	virtual double get_min_charge();
    double get_min_from_outers(Blossom* outer1, Blossom* outer2);
	virtual void update_vertex(double val);
    virtual Vertex *get_root_strem(){return this;}
    int get_id(){return id;}

private:
    const int id;
    //zamienic na cos innego
	double totalCharge;

};

#endif
