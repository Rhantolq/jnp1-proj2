//
// Created by rhantolq on 26.10.2019.
//

#include "poset.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>

namespace jnp1 {

    using namespace std;
    using Relations = unordered_set<const string*>;
    // Poset class.
    // Every string in this map represents a Poset element and every element has
    // it's incoming relations stored as first element of the pair and outgoing
    // relations as the second element of the pair.
    using Poset = unordered_map<string, pair<Relations, Relations>>;

    unsigned long id_counter = 0;

    unordered_map<unsigned long, Poset> posets;
    //           id              l. elementow,    slownik stringow
    //unordered_map<unsigned long, pair<pair<size_t, unordered_map<string, size_t>>, Poset>> posets;


    unsigned long poset_new(void) {
        id_counter++;
        Poset poset;
        posets[id_counter] = poset;
        return id_counter;
    }


    size_t poset_size(unsigned long id) {
        auto found_poset = posets.find(id);
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
        unordered_map<unsigned long, unordered_map<string, pair<unordered_set<string>, unordered_set<string>>>>::iterator found_poset;
        found_poset = posets.find(id);

        if (found_poset == posets.end()) {

            return false;
        }
        else {

            unordered_map<string, pair<unordered_set<string>, unordered_set<string>>> elements;
            elements = found_poset->second;
            string element(value);
            if (elements.find(element) == elements.end()) {
                pair<unordered_set<string>, unordered_set<string>> relations;
                elements.insert(pair<string, pair<unordered_set<string>, unordered_set<string>>>(element, relations));

                return true;
            }
            else {

                return false;
            }
        }

    }

    bool poset_remove(unsigned long id, char const *value) {
        if (posets.find(id) == posets.end()) {
            return false;
        }
        Poset poset = posets[id];
        string name = value;
        if (poset.find(name) == posets[id].end()) {
            return false;
        }
        const string *name_ref = &(poset.find(name)->first);
        auto relations = poset[name];
        auto it = relations.first.begin();
        while (it != relations.first.end()) {
            poset[*(*it)].second.erase(name_ref);
            it++;
        }
        auto it2 = relations.second.begin();
        while (it2 != relations.second.end()) {
            poset[*(*it2)].first.erase(name_ref);
            it2++;
        }
    }
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
