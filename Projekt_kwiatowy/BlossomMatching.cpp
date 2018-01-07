#include "BlossomMatching.h"

#include <algorithm>
#include <limits>

BlossomMatching::BlossomMatching(int num):n_vertexes(num),match_size(0){
    vertexes.reserve(n_vertexes);
    for (int i = 0; i < n_vertexes; i++){
		vertexes.push_back(std::unique_ptr<Vertex>(new Vertex(i)));
		free_roots.push_back(vertexes.back().get());
	}
}

bool BlossomMatching::add_edge(int v1, int v2, int weight){
    try{
        edges.push_back(std::unique_ptr<Edge>(new Edge(this, vertexes[v1].get(), vertexes[v2].get(), weight)));
        return true;
    }catch(...){
        return false;
    }

}

bool BlossomMatching::find_min_cost_matching()
{
	while (true)
	{
        // Znajdowanie minimum kosztu krawędzi
		double min_temp_val = std::numeric_limits<double>::infinity();
		for (auto const &edge : edges){
			double edge_temp_val = edge->get_charge_from_edge();
			min_temp_val = std::min(min_temp_val, edge_temp_val);
		}

		for (auto const &root : free_roots)
			root->update_charge(min_temp_val);

		//Zmiany na drzewach
		bool change = false;
		while (true){
			bool round = false;
            for (auto const &root : free_roots)
				if (root->update_tree()){
					round = true;
					change = true;
					break;
				}
			if (round)
				continue;
            for (auto const &edge : edges)
				if (edge->update()){
					round = true;
					change = true;
					break;
				}
			if (round)
				continue;
            else
                break;
		}


		
		// jeśli algorytm utknął
        if (    (!change && min_temp_val == 0)||
                min_temp_val == std::numeric_limits<double>::infinity() ){

            set_matched_edges();
			return false;
        }

		// jeśli idealne zmatchowanie
        if (match_size * 2 == n_vertexes){
            set_matched_edges();
			return true;
        }
	}
}

void BlossomMatching::rem_root_from_tforest(Blossom *root){
	free_roots.remove(root);
}

void BlossomMatching::add_root_to_forest(Blossom *root){
	free_roots.push_back(root);
}

int BlossomMatching::get_cost_from_matching(){
	int weight = 0;
    for (auto& edge : edges){
		if (edge->if_matched())
			weight += edge->get_waight();
	}
	return weight;
}

std::vector<std::pair<int, int>> BlossomMatching::get_matched_edges(){
    return matched_edges;
}

void BlossomMatching::set_matched_edges(){
    matched_edges.reserve(match_size);
    for (auto const& edge : edges){
        if (edge->if_matched()){
            matched_edges.emplace_back(edge->get_v1()->get_id(), edge->get_v2()->get_id());
        }
    }
}
