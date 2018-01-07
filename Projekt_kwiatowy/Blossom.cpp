#include "Blossom.h"
#include "Vertex.h"
#include <algorithm>

Blossom::Blossom(){
	charge = 0;
	tree_type = TreeType::EVEN;
	prent_tree_blossom = NULL;
	tree_parent_edge = NULL;
	outer_children = NULL;
}

void Blossom::add_charge(double val){
	charge += val;
	update_vertex(val);
}

double Blossom::get_min_charge(){
	return get_charge();
}

void Blossom::update_vertex(double val){
	for (auto const& inner : inner_children)
		inner->update_vertex(val);
}

void Blossom::update_charge(double reserve){
	if (get_TreeType() == TreeType::EVEN)
		add_charge(reserve);
	else
		add_charge(-reserve);
	//update
	for (auto const& child : children)
		child->update_charge(reserve);
}

bool Blossom::update_tree()
{
	// Zacząć od dzieci!
	for (auto const &child : children){
		if (child->update_tree())
			return true;
	}

	// Jeżeli kwiat (nie wierzchołek osiągną zero w type "dziwnym" - odłączyć
	if (get_min_charge() == 0 && get_TreeType() == TreeType::ODD){
		recreate_from_blossom();
		return true;
	}

	return false;
}

Blossom* Blossom::get_most_outer_blossom(){
	Blossom* outermost = this;
	while (outermost->outer_children.get() != NULL)
		outermost = outermost->outer_children.get();
	return outermost;
}

Blossom *Blossom::get_inner_blossom_with_vertex(Vertex *v){
	Blossom *inner = v;
	while (inner != NULL && inner->outer_children.get() != this)
		inner = inner->outer_children.get();
	return inner;
}

Blossom* Blossom::get_blossom_root()
{
	Blossom* root = this;
	while (root->prent_tree_blossom != NULL)
		root = root->prent_tree_blossom;
	return root;
}

Vertex* Blossom::get_root_strem(){
	return inner_children[0]->get_root_strem();
}

// 1. Odłącz wszystkie dzieci i demontuj je na pry tylko na poziomie parzystych korzeni.
// 2. Znajdowanie wierzchołka w podłączanym kwiacie.
// 3. Na parzystym dzielimy na poziomie kwiatu, jeśli nieparzysty to bierzemy pod uwage rodzica.


void Blossom::disassemble_and_flip(Vertex *v, Blossom *other, Edge *edge){

	Vertex *v2 = get_root_strem();
	if (get_TreeType() == TreeType::ODD){
		v2 = tree_parent_edge->get_v1();
		if (v2->get_most_outer_blossom() != this)
			v2 = tree_parent_edge->get_v2();
	
	}
	flip_between(v, v2);

	// 1
	if (get_TreeType() == TreeType::EVEN){
		for (auto const &child : children){
			if (child != other)
				child->tree_to_pairs();
		}
	}

	children.clear();

	Blossom *parent = prent_tree_blossom;
    Edge *p_edge = tree_parent_edge;

	prent_tree_blossom = NULL;
	tree_parent_edge = NULL;

	TreeType oldTreeType = get_TreeType();

	if (other != NULL)
		make_pair_with(other, edge);

	if (parent == NULL)
		return;

	// 2
    Vertex *pv = p_edge->get_v1();
	if (pv->get_most_outer_blossom() == this)
        pv = p_edge->get_v2();
	
    p_edge->flip();

	// 3
	if (oldTreeType == TreeType::EVEN)
        parent->disassemble_and_flip(pv,NULL,NULL);
	else
        parent->disassemble_and_flip(pv, this, p_edge);
}

// 1. Dla poziomu równego odłączamy kwiaty poziomu "dziwnego"
// 2. Kwiaty z poziomu "Dziwnego" mają dokładnie jedo dziecko poziomu równego (z pary)
//		- zdemontować pary rekursywnie
//		- wyczyścić listę dzieci i rodziców dla tego kwiatu


void Blossom::tree_to_pairs()
{

	// 1
	if (get_TreeType() == TreeType::EVEN){
		for (auto const& child : children)
			child->tree_to_pairs();

		children.clear();
		prent_tree_blossom = NULL;
		tree_parent_edge = NULL;
	}
	// 2
	else{
		
		Blossom *other = children.front();
		Edge *edge = children.front()->tree_parent_edge;
		other->tree_to_pairs();

		children.clear();
		prent_tree_blossom = NULL;
		tree_parent_edge = NULL;

		make_pair_with(other, edge);
	}
}


// 1. Jeśli nie ma kwiatów wewnętrznych to to musi być wierzchołek więc koniec
// 2. Znajdź kwiat-dziecko tla wierzchołka
// 3. przejdz po ścierzce odpowiednio zamieniając wierzchołki i odłączając krawędzie
void Blossom::flip_between(Vertex *v1, Vertex *v2){
	if (get_root_strem() != v1)
		std::swap(v1, v2);
	// 1
	if (inner_children.size() == 0)
		return;


	// 2
	Blossom *b2 = get_inner_blossom_with_vertex(v2);
	
	Blossom *first = inner_children[0];
	Blossom *last = b2;
	auto b2_pos = std::find(inner_children.begin(), inner_children.end(), b2);
	long pos = std::distance(inner_children.begin(), b2_pos);
	if (pos % 2 == 1){
		std::swap(v1, v2);
		std::swap(first, last);
	}
	
	Blossom *current = first;
	// 3
	while (current != last){
		Vertex *b_v1 = current->next_blossom_edge->get_v1();
		Vertex *b_v2 = current->next_blossom_edge->get_v2();
		if (get_inner_blossom_with_vertex(b_v1) != current)
			std::swap(b_v1, b_v2);
		current->flip_between(v1, b_v1);
		
		current->next_blossom_edge->flip();
		current = get_inner_blossom_with_vertex(b_v2);
		v1 = b_v2;
	}

	last->flip_between(v1, v2);

	// Rotowanie cykl wewnętrznych kwiatów tak by b2 był teraz łodygą
	std::rotate(inner_children.begin(), b2_pos, inner_children.end());
}


//Dodaje do drzewa za pomocą gałęzi edge
void Blossom::add_to_tree(Blossom *parent, Edge *edge){
	tree_type = TreeType::ODD;
	children.push_back(prent_tree_blossom);
	prent_tree_blossom->tree_type = TreeType::EVEN;
	prent_tree_blossom = parent;
	tree_parent_edge = edge;
	prent_tree_blossom->children.push_back(this);
}
//Łączy pary za pomocą edge
void Blossom::make_pair_with(Blossom *other, Edge *edge){
	this->tree_type = TreeType::PAIR;
	other->tree_type = TreeType::PAIR;
	this->prent_tree_blossom = other;
	other->prent_tree_blossom = this;
	this->tree_parent_edge = edge;
	other->tree_parent_edge = edge;
}
// 1. Znajdowanie najniższego przodka i ścierzki do niego
// 2. LCA jeden przed
// 3. Budowanienie kwiatu od LCA. Stworzenie kwiatu z wartością zero, nadanie parenta LCA jako korzeń.
// 4. Dodawanie kwiatów na ścierzce od LCA, LCA jako rdzeń.
// 5. Zmień wszystkie zewnętrzne krawędzie, aby wskazywały na nowy kwiatek, dodaj wszystkie dzieci
// 6. Jezeli LCA jest korzeniem tego wiatu to trzeba go zmienic


Blossom* Blossom::create_blossom(Blossom * other, Edge *edge){
	// 1
	std::list<Blossom*> path_from_this;
	std::list<Blossom*> path_from_other;
	path_from_this.push_back(this);
	path_from_other.push_back(other);
	
	while (path_from_this.back()->prent_tree_blossom != NULL)
		path_from_this.push_back(path_from_this.back()->prent_tree_blossom);
	
	while (path_from_other.back()->prent_tree_blossom != NULL)
		path_from_other.push_back(path_from_other.back()->prent_tree_blossom);

	// 2
	Blossom* LCA = NULL;
	while (path_from_this.size() > 0 && path_from_other.size() > 0 &&
		path_from_this.back() == path_from_other.back()){
		LCA = path_from_this.back();
		path_from_this.pop_back();
		path_from_other.pop_back();
	}

	// 3
	//Blossom* temp_blossom = new Blossom();
	std::shared_ptr<Blossom> temp_blossom = std::make_shared<Blossom>();
	temp_blossom->prent_tree_blossom = LCA->prent_tree_blossom;
	temp_blossom->tree_parent_edge = LCA->tree_parent_edge;
	
	Blossom* parent = temp_blossom->prent_tree_blossom;
	
	if (parent != NULL){
		parent->children.remove(LCA);
        parent->children.push_back(temp_blossom.get());
	}
	temp_blossom->inner_children.push_back(LCA);
	
	Blossom* that = LCA;
	// 4
    for (auto it = path_from_this.rbegin(); it != path_from_this.rend(); it++){
		temp_blossom->inner_children.push_back(*it);
		that->next_blossom_edge = (*it)->tree_parent_edge;
		that = *it;
	}
	
	that->next_blossom_edge = edge;
	for (auto it = path_from_other.begin(); it != path_from_other.end(); it++){
		temp_blossom->inner_children.push_back(*it);
		(*it)->next_blossom_edge = (*it)->tree_parent_edge;
	}
	
	for (auto const &inner : temp_blossom->inner_children)
        inner->outer_children = std::shared_ptr<Blossom>(temp_blossom);

	// 5
	for (Blossom* inner : temp_blossom->inner_children)
		for (Blossom * child : inner->children)
			if (child->outer_children == NULL){
				temp_blossom->children.push_back(child);
                child->prent_tree_blossom = temp_blossom.get();
			}
			
	temp_blossom->outer_children = NULL;

	// 6
	if (LCA->tree_parent_edge == NULL)
        return temp_blossom.get();
	else
		return NULL;
}

// 1. Rozmontuj obecny kwiat na drzewo i pary, kwiat dziecka jest podłączony do wewnętrznego kwiatu łodygi.
// 2. Formowanie par i a drzewa z reszy(równych ścierzek).
// 3. Ustaw rodzica na następny kwiat wewnętrzny, z wyjątkiem ostatniego, który będzie dzieckiem bieżącego rodzica.
// 4. Dodaj wcześniejszy wewnętrzny kwiat do dzieci, z wyjątkiem łodygi, która będzie rodzicem bieżącego dziecka.
// 5. Zamień wskaźnik na potomka dla rodzica z tego kwiatka na wewnętrzny.
// 6. Ustaw nadrzędny kwiatek dla dziecka, którego brzeg jest już ustawiony i usóń kwiat (Aby usunąć ten kwiat, resetujemy do niego wszystkie zewnętrzne wskaźniki)
// 7. Weź pozostały cykl długości nieparzystej i zdemontuj go do par. Idź w kierunku następnych wskaźników

void Blossom::recreate_from_blossom(){
		// 1
	Blossom *inner_end;
	if (tree_parent_edge->get_v1()->get_most_outer_blossom() == this)
		inner_end = get_inner_blossom_with_vertex(tree_parent_edge->get_v1());
	else
		inner_end = get_inner_blossom_with_vertex(tree_parent_edge->get_v2());
	auto inner_end_pos = std::find(inner_children.begin(), inner_children.end(), inner_end);
	int pos = std::distance(inner_children.begin(), inner_end_pos);

	// 2
	int chil_size = inner_children.size();
	int start = (pos % 2) ? pos : 0;
	int end = (pos % 2) ? chil_size : pos;
	int b_pos = (pos % 2) ? -1 : 1;
	int e_pos = (pos % 2) ? -1 : 0;
	int stem = (pos % 2) ? chil_size : 0;
	int i =0,y=0;
	
	for (i = start; i < end+1; i++){
		if (i % 2 == stem % 2)
			inner_children[i%chil_size]->tree_type = TreeType::ODD; 
		else
			inner_children[i%chil_size]->tree_type = TreeType::EVEN;
		
		// 3
		if(i == pos){
			inner_children[i%chil_size]->prent_tree_blossom = prent_tree_blossom;
			inner_children[i%chil_size]->tree_parent_edge = tree_parent_edge;
		}
		else{
			inner_children[i%chil_size]->prent_tree_blossom = inner_children[i + b_pos];
			inner_children[i%chil_size]->tree_parent_edge = inner_children[i + e_pos]->next_blossom_edge;
		}
		
		// 4
		inner_children[i%chil_size]->children.clear();
		if(i==stem)
			inner_children[i%chil_size]->children.push_back(children.front());
		else 
			inner_children[i%chil_size]->children.push_back(inner_children[(i - b_pos) % chil_size]);
	}

	// 5
	prent_tree_blossom->children.remove(this);
	prent_tree_blossom->children.push_back(inner_children[pos]);
	// 6
	children.front()->prent_tree_blossom = inner_children[0];
	
	for (auto const& inner : inner_children)
		inner->outer_children.reset();

	// 7
	i = (pos % 2) ? 1: pos + 1;
	y = (pos % 2) ? pos : chil_size;
	for (i; i<y;i += 2){
		inner_children[i]->children.clear();
		inner_children[i + 1]->children.clear();
		inner_children[i]->prent_tree_blossom = NULL;
		inner_children[i + 1]->prent_tree_blossom = NULL;

		inner_children[i]->make_pair_with(inner_children[i + 1],
			inner_children[i]->next_blossom_edge);
	}
}
