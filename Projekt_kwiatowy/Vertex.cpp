
#include "Vertex.h"
#include <limits>
#include <float.h>
#include "BlossomMatching.h"
#include <algorithm>

double Vertex::get_min_charge(){
	//return DBL_MAX;
	return std::numeric_limits<double>::infinity();
}

void Vertex::update_vertex (double val){
	totalCharge += val;
}


//zrobic liste inicjaizacyjną
Edge::Edge(BlossomMatching *matching, Vertex *v1, Vertex *v2, int weight):
    matching(matching)
    ,v1(v1)
    ,v2(v2)
    ,weight(weight)
    ,matched(0){
}

std::pair<Blossom*,Blossom*> Edge::get_outers(){
    return std::pair<Blossom*,Blossom*> (v1->get_most_outer_blossom(),v2->get_most_outer_blossom());
}

double Edge::get_charge_from_edge(){
   auto outers = get_outers();

    // Krawędzie zawarte wewnątrz tego samego zewnętrznego kwiatu lub pomiedzy parami
    if (outers.first == outers.second || if_beetween_pairs(outers.first, outers.second))
		return std::numeric_limits<double>::infinity();

	// wyliczenie wartości pomocniczej krawedzi łaćzacych kwiaty
    double temp_val = weight - v1->get_total_charge()
        - v2->get_total_charge();
    if (if_beetween_even_and_pair(outers.first, outers.second))
		return temp_val;
	// krawędz miedzy dwoma równymi kwiatami
    if (if_beetween_evens(outers.first, outers.second))
		return temp_val / 2;

    //reszta przypadków
    return get_min_from_outers(outers.first, outers.second);
}

double Edge::get_min_from_outers(Blossom* outer1, Blossom* outer2){
    double temp_val = std::numeric_limits<double>::infinity();
    if (outer1->get_TreeType() == TreeType::ODD)
        temp_val = std::min(temp_val, outer1->get_min_charge());
    if (outer2->get_TreeType() == TreeType::ODD)
        temp_val = std::min(temp_val, outer2->get_min_charge());
    return temp_val;
}

bool Edge::update(){
	if (get_charge_from_edge() > 0)
		return false;
	
    auto outers = get_outers();

	// krawędz między parami a kwiatem
	//przeszukiwanie sąsiadów
    if (if_beetween_even_and_pair(outers.first, outers.second)){
        if (outers.first->get_TreeType() == TreeType::PAIR)
            outers.first->add_to_tree(outers.second, this);
		else
            outers.second->add_to_tree(outers.first, this);
		return true;
	}

	// krawedzie między kwiatami
    if (if_beetween_evens(outers.first, outers.second)){
        Blossom* root1 = outers.first->get_blossom_root();
        Blossom * root2 = outers.second->get_blossom_root();

		if (root1 == root2){
            Blossom *newRoot = outers.first->create_blossom(outers.second, this);
			if (newRoot != NULL){
				matching->rem_root_from_tforest(root1);
				matching->add_root_to_forest(newRoot);
			}
		}
		else{
			//Demontowanie drzewa na pary i kwiaty
            outers.first->disassemble_and_flip(v1,NULL,NULL);
            outers.second->disassemble_and_flip(v2,NULL,NULL);

			// usówanie korzeni z listy korzeni
			matching->rem_root_from_tforest(root1);
			matching->rem_root_from_tforest(root2);

			// złączenie dwóch kwiatów
            outers.first->make_pair_with(outers.second, this);
			this->flip();

			matching->increase_match_size();
		}

		return true;
	}
    return false;
}


bool Edge::if_beetween_pairs(Blossom* outer1, Blossom* outer2){
    bool state1 = outer1->get_TreeType() == TreeType::PAIR;
    bool state2 = outer2->get_TreeType() == TreeType::PAIR;
    return state1 && state2;
}
bool Edge::if_beetween_evens(Blossom* outer1, Blossom* outer2){
    auto type1 = outer1->get_TreeType();
    auto type2 = outer2->get_TreeType();
    if (type1 == TreeType::EVEN && type2 == TreeType::EVEN)
        return true;
    else
        return false;
}
bool Edge::if_beetween_even_and_pair(Blossom* outer1, Blossom* outer2){
    auto type1 = outer1->get_TreeType();
    auto type2 = outer2->get_TreeType();
    if (type1==TreeType::PAIR && type2 == TreeType::EVEN)
        return true;
    else if (type1==TreeType::EVEN && type2 == TreeType::PAIR)
        return true;
    else
        return false;
}

