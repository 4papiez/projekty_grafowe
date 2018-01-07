#pragma once
#ifndef BlossomMatching_H
#define BlossomMatching_H

#include <vector>
#include <list>
#include <memory>

#include "Blossom.h"
#include "Vertex.h"


class BlossomMatching
{
public:
    BlossomMatching(int num);
    bool add_edge(int v1id, int v2id, int weight);
	bool find_min_cost_matching();
	void increase_match_size() { match_size += 1; }
	void rem_root_from_tforest(Blossom *root);
	void add_root_to_forest(Blossom *root);
	int get_cost_from_matching();
    std::vector<std::pair<int, int>> get_matched_edges();
    void set_matched_edges();

private:
    
    int n_vertexes;
	int match_size;
    std::vector<std::pair<int,int>> matched_edges;
	std::vector<std::unique_ptr<Vertex>> vertexes;
	std::vector<std::unique_ptr<Edge>> edges;
	std::list<Blossom*> free_roots;

};

#endif
