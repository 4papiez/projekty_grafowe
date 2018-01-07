#pragma once

#ifndef BLOSSOM_H
#define BLOSSOM_H

#include <vector>
#include <list>
#include <memory>

// poziomy kwiatów w drzewie
enum class TreeType{
	EVEN,//element parzysty
	ODD,//element nieparzysty
	PAIR//para nie bedąca czescią lasu
};
class Edge;
class Vertex;

class Blossom
{
public:
	Blossom();

	double get_charge() { return charge; }
	TreeType get_TreeType() { return tree_type; }
	void add_charge(double value); 
	void update_charge(double value);
	
    void disassemble_and_flip(Vertex* v, Blossom* other, Edge* edge);
	void tree_to_pairs();
	void flip_between(Vertex *v1, Vertex *v2);
	void make_pair_with(Blossom* pair, Edge *edge);
	void add_to_tree(Blossom *parent, Edge *parentEdge);
	
	virtual Vertex* get_root_strem();
	//zapewnia >=0
	virtual double get_min_charge();
	bool update_tree();
	virtual void update_vertex(double value);

	Blossom* get_most_outer_blossom();
	Blossom* get_inner_blossom_with_vertex(Vertex *v);
	Blossom* get_blossom_root();
	Blossom* create_blossom(Blossom* blos, Edge *edge);
	void recreate_from_blossom();
private:
	double charge;
	TreeType tree_type;
	Blossom* prent_tree_blossom;
	Blossom* next_blossom;
	Edge* tree_parent_edge;
	Edge* next_blossom_edge;
	std::list<Blossom*> children;
	std::vector<Blossom*> inner_children;
	std::shared_ptr<Blossom> outer_children;
};

#endif
