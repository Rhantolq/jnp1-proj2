	//
	// Created by rhantolq on 26.10.2019.
	//

#include "poset.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>

namespace jnp1 {

    using namespace std;
    using Relations = unordered_set<string*>;
    using Poset = unordered_map<string, pair<Relations, Relations>>;
    unsigned long id_counter = 0;
    unordered_map<unsigned long, Poset> posets;
    
	unsigned long poset_new(void) {
        id_counter++;
        Poset poset;
        posets[id_counter] = poset;
        return id_counter;
    }
    
	size_t poset_size(unsigned long id) {
        unordered_map<unsigned long, Poset>::iterator found_poset = posets.find(id);

        if (found_poset == posets.end()) {
            return 0;
        }
        else {
            Poset elements = found_poset->second;
            return elements.size();
	        }
	}


	void poset_delete(unsigned long id) {
	    if (posets.find(id) != posets.end()) {
	        posets.erase(id);
	    }
	}

	bool poset_insert(unsigned long id, char const *value) {
		unordered_map<unsigned long, Poset>::iterator found_poset;
		found_poset = posets.find(id);

		if (found_poset == posets.end()) {

			return false;
		}
		else {

			unordered_map<string, pair<unordered_set<string*>, unordered_set<string*>>> *elements;
			elements = &(found_poset->second);
			string element(value);

			if ((*elements).find(element) == (*elements).end()) {
				pair<unordered_set<string*>, unordered_set<string*>> relations;
				(*elements).insert(pair<string, pair<Relations, Relations>>(element, relations));
				
				return true;
			}
			else {
			
				return false;
			}
		}

	}


/*
    bool poset_remove(unsigned long id, char const *value) {
        if (posets.find(id) == posets.end()) {
            return false;
        }
        Poset poset = posets[id];
        
    }*/
}

using namespace std;

int main() {

	unordered_set<string> relations;
	unordered_map<string, unordered_set<string>> elements;
	unordered_map<string, int> mapa;
//	mapa["asd"]= 1;
//	string str2 = &(mapa.find("asd")->first);
//	cout<<str2<<endl;


	unsigned long id =  jnp1::poset_new();
	cout << (jnp1::poset_size(id))<<endl;
	cout << jnp1::poset_insert(id, "abc") << endl;
	cout<<jnp1::poset_insert(0, "aabc") << endl;
	cout << (jnp1::poset_size(id)) << endl;
	jnp1::poset_delete(id);
	return 0;
}
