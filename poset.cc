//
// Created by rhantolq on 26.10.2019.
//

#include "poset.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

namespace {

    using Relations = unordered_set<const string*>;
    // Poset class.
    // Every string in this map represents a Poset element and every element has
    // it's incoming relations stored as first element of the pair and outgoing
    // relations as the second element of the pair.
    using Poset = unordered_map<string, pair<Relations, Relations>>;

    unsigned long id_counter = 0;

    bool cerr_initialized = false;

    void cerr_init() {
        if (!cerr_initialized) {
            ios_base::Init();
            cerr_initialized = true;
        }
    }

    unordered_map<unsigned long, Poset>& posets() {
        static unordered_map<unsigned long, Poset>* ans = new unordered_map<unsigned long, Poset>();
        return *ans;
    }

    void poset_add_out(Relations *additional_out_set, const string *additional_element,
                       const string current_element, Poset *poset) {

        auto *el = &(poset->find(current_element)->second);
        if (el->second.find(additional_element) == el->second.end()) {
            for (auto iterator = additional_out_set->begin(); iterator != additional_out_set->end(); ++iterator) {
                el->second.emplace(*iterator);
            }
            el->second.emplace(additional_element);

            for (auto iterator = el->first.begin(); iterator != el->first.end(); ++iterator) {
                poset_add_out(additional_out_set, additional_element, **iterator, poset);
            }
        }

    }

    void poset_add_in(Relations *additional_in_set, const string *additional_element,
                      const string current_element, Poset *poset) {

        auto *el = &(poset->find(current_element)->second);
        if (el->first.find(additional_element) == el->first.end()) {
            for (auto iterator = additional_in_set->begin(); iterator != additional_in_set->end(); ++iterator) {
                el->first.emplace(*iterator);
            }
            el->first.emplace(additional_element);

            for (auto iterator = el->second.begin(); iterator != el->second.end(); ++iterator) {
                poset_add_in(additional_in_set, additional_element, **iterator, poset);
            }
        }
    }

    /**
     * Log info
     */

    void poset_new_info() {
        cerr_init();
        cerr << "poset_new()" << endl;
    }

    void poset_delete_info(unsigned long id) {
        cerr_init();
        cerr << "poset_delete(" << id << ")" << endl;
    }

    void poset_size_info(unsigned long id) {
        cerr_init();
        cerr << "poset_size(" << id << ")" << endl;
    }

    void poset_insert_info(unsigned long id, char const *value) {
        cerr_init();
        string ret_value;
        if (value == NULL) {
            ret_value = "NULL";
        }
        else {
            ret_value = value;
        }
        cerr << "poset_insert(" << id << ", \"" << ret_value << "\")" << endl;
    }


    void poset_remove_info(unsigned long id, const char *value) {
        cerr_init();
        string ret_value;
        if (value == NULL) {
            ret_value = "NULL";
        }
        else {
            ret_value = value;
        }
        cerr << "poset_remove(" << id << ", \"" << ret_value << "\")" << endl;
    }

    void poset_clear_info(unsigned long id) {
        cerr_init();
        cerr << "poset_clear(" << id << ")" << endl;
    }

    void poset_add_info(unsigned long id, const char *value1, const char *value2) {
        cerr_init();
        string ret_value1, ret_value2;
        if (value1 == NULL) {
            ret_value1 = "NULL";
        }
        else {
            ret_value1 = value1;
        }

        if (value2 == NULL) {
            ret_value2 = "NULL";
        }
        else {
            ret_value2 = value2;
        }

        cerr << "poset_add(" << id << ", \"" << ret_value1 << "\", \"" << ret_value2 << "\")" << endl;
    }

    void poset_del_info(unsigned long id, const char *value1, const char *value2) {
        cerr_init();
        string ret_value1, ret_value2;
        if (value1 == NULL) {
            ret_value1 = "NULL";
        }
        else {
            ret_value1 = value1;
        }

        if (value2 == NULL) {
            ret_value2 = "NULL";
        }
        else {
            ret_value2 = value2;
        }
        cerr << "poset_del(" << id << ", \"" << ret_value1 << "\", \"" << ret_value2 << "\")" << endl;
    }

    void poset_test_info(unsigned long id, const char *value1, const char *value2) {
        cerr_init();
        string ret_value1, ret_value2;
        if (value1 == NULL) {
            ret_value1 = "NULL";
        }
        else {
            ret_value1 = value1;
        }

        if (value2 == NULL) {
            ret_value2 = "NULL";
        }
        else {
            ret_value2 = value2;
        }

        cerr << "poset_test(" << id << ", \"" << ret_value1 << "\", \"" << ret_value2 <<"\")" << endl;
    }

    void poset_does_not_exist(unsigned long id, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << " does not exist" << endl;
    }

    void poset_deleted(unsigned long id, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << " deleted" << endl;
    }

    void poset_created(unsigned long id, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << " created" << endl;
    }

    void poset_contains(unsigned long id, size_t number, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << " contains " << number << " element(s)" << endl;
    }

    void poset_invalid_value(int value_no, string function_name) {
        cerr_init();
        cerr << function_name << ": invalid value";
        if (value_no != 0) {
            cerr << value_no;
        }
        cerr << " (NULL)" << endl;
    }

    void element_inserted(unsigned long id, const char *value, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", element \"" << value << "\" inserted" << endl;
    }

    void element_already_exists(unsigned long id, const char *value, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", element \"" << value << "\" already exists" << endl;
    }

    void element_removed(unsigned long id, const char *value, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", element \"" << value << "\" removed" << endl;
    }

    void element_does_not_exist(unsigned long id, const char *value, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", element \"" << value << "\" does not exist" << endl;
    }

    void elements_does_not_exist(unsigned long id, const char *value1, const char *value2, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", element \"" << value1 << "\" or \"" << value2 << "\" does not exist" << endl;
    }

    void relation_exists(unsigned long id, const char *value1, const char *value2, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") exists" << endl;
    }

    void relation_does_not_exists(unsigned long id, const char *value1, const char *value2, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") does not exist" << endl;
    }

    void relation_cannot_be_deleted(unsigned long id, const char *value1, const char *value2, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") cannot be deleted" << endl;
    }
    void relation_deleted(unsigned long id, const char *value1, const char *value2, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") deleted" << endl;
    }

    void relation_added(unsigned long id, const char *value1, const char *value2, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") added" << endl;
    }

    void relation_cannot_be_added(unsigned long id, const char *value1, const char *value2, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") cannot be added" << endl;
    }

    void poset_cleared(unsigned long id, string function_name) {
        cerr_init();
        cerr << function_name << ": poset " << id << " cleared" << endl;
    }
}

namespace jnp1 {

    unsigned long poset_new(void) {
        poset_new_info();
        unsigned long poset_no = id_counter;
        id_counter++;
        Poset poset;
        posets()[poset_no] = poset;
        poset_created(poset_no, __func__);
        return poset_no;
    }


    size_t poset_size(unsigned long id) {
        poset_size_info(id);

        auto found_poset = posets().find(id);
        if (found_poset == posets().end()) {
            poset_does_not_exist(id, __func__);
            return 0;
        }
        else {
            Poset elements = found_poset->second;
            size_t ret = elements.size();
            poset_contains(id, ret, __func__);
            return ret;
        }
    }


    void poset_delete(unsigned long id) {
        poset_delete_info(id);

        auto found = posets().find(id);
        if (found != posets().end()) {
            posets().erase(found);
            poset_deleted(id, __func__);
        }
        else {
            poset_does_not_exist(id, __func__);
        }
    }


    bool poset_insert(unsigned long id, char const *value) {
        poset_insert_info(id, value);

        auto found_poset = posets().find(id);
        if (found_poset == posets().end()) {
            poset_does_not_exist(id, __func__);
            return false;
        }
        else if (value == NULL) {
            poset_invalid_value(0, __func__);
            return false;
        }
        else {
            string element(value);
            pair<Relations, Relations> inout_relations;
            auto result = found_poset->second.emplace(element, inout_relations);
            if (result.second) {
                element_inserted(id, value, __func__);
            }
            else {
                element_already_exists(id, value, __func__);
            }
            return result.second;
        }
    }


    bool poset_remove(unsigned long id, char const *value) {
        poset_remove_info(id, value);

        if (posets().find(id) == posets().end()) {
            poset_does_not_exist(id, __func__);
            return false;
        }
        else if (value == NULL) {
            poset_invalid_value(0, __func__);
            return false;
        }

        Poset& poset = posets()[id];
        string val = value;
        if (poset.find(val) == posets()[id].end()) {
            element_does_not_exist(id, value, __func__);
            return false;
        }
        const string *name_ref = &(poset.find(val)->first);
        auto relations = poset[val];
        auto it = relations.first.begin();
        while (it != relations.first.end()) {
            poset[*(*it)].second.erase(name_ref);
            ++it;
        }
        auto it2 = relations.second.begin();
        while (it2 != relations.second.end()) {
            poset[*(*it2)].first.erase(name_ref);
            ++it2;
        }
        poset.erase(val);

        element_removed(id, value, __func__);
        return true;
    }


    bool poset_del(unsigned long id, char const *value1, char const *value2) {
        poset_del_info(id, value1, value2);

        auto found_poset = posets().find(id);
        bool status = true;
        if (found_poset == posets().end()) {
            poset_does_not_exist(id, __func__);
            status = false;
        }
        if (value1 == NULL)  {
            poset_invalid_value(1, __func__);
            status = false;
        }
        if (value2 == NULL) {
            poset_invalid_value(2, __func__);
            status = false;
        }
        if (!status) {
            return false;
        }

        Poset& poset = found_poset->second;
        string val1 = value1;
        string val2 = value2;
        auto elem1 = poset.find(val1);
        auto elem2 = poset.find(val2);
        if (elem1 == poset.end() || elem2 == poset.end()) {
            elements_does_not_exist(id, value1, value2, __func__);
            return false;
        }

        Relations& elem1out = elem1->second.second;
        Relations& elem2in = elem2->second.first;

        if (elem1out.find(&(elem2->first)) == elem1out.end()) {
            relation_cannot_be_deleted(id, value1, value2, __func__);
            return false;
        }

        auto it = elem1out.begin();
        while (it != elem1out.end()) {
            if (elem2in.find(*it) != elem2in.end()) {
                relation_cannot_be_deleted(id, value1, value2, __func__);
                return false;
            }
            ++it;
        }
        elem1out.erase(&(elem2->first));
        elem2in.erase(&(elem1->first));

        relation_deleted(id, value1, value2, __func__);

        return true;
    }

    bool poset_test(unsigned long id, char const *value1, char const *value2) {
        poset_test_info(id, value1, value2);

        auto found_poset = posets().find(id);
        bool status = true;
        if (found_poset == posets().end()) {
            poset_does_not_exist(id, __func__);
            status = false;
        }
        if (value1 == NULL) {
            poset_invalid_value(1, __func__);
            status = false;
        }
        if (value2 == NULL) {
            poset_invalid_value(2, __func__);
            status = false;
        }
        if (!status) {
            return false;
        }

        Poset& poset = found_poset->second;
        string val1 = value1;
        string val2 = value2;
        auto elem1 = poset.find(val1);
        auto elem2 = poset.find(val2);
        if (elem1 == poset.end() || elem2 == poset.end()) {
            elements_does_not_exist(id, value1, value2, __func__);
            return false;
        }

        bool ret = elem1->second.second.find(&(elem2->first)) != elem1->second.second.end() || elem1 == elem2;

        if (ret) {
            relation_exists(id, value1, value2, __func__);
        }
        else {
            relation_does_not_exists(id, value1, value2, __func__);
        }

        return ret;
    }

    void poset_clear(unsigned long id) {
        poset_clear_info(id);
        auto found = posets().find(id);
        if (found == posets().end()) {
            poset_does_not_exist(id, __func__);
        }
        else {
            posets()[id].clear();
            poset_cleared(id, __func__);
        }
    }


    bool poset_add(unsigned long id, char const *value1, char const *value2) {
        poset_add_info(id, value1, value2);

        unordered_map<unsigned long, Poset>::iterator found_poset;
        found_poset = posets().find(id);
        Poset::iterator found_rel1;
        Poset::iterator found_rel2;

        bool status = true;
        if (found_poset == posets().end()) {
            poset_does_not_exist(id, __func__);
            status = false;
        }
        if (value1 == NULL) {
            poset_invalid_value(1, __func__);
            status = false;
        }
        if (value2 == NULL) {
            poset_invalid_value(2, __func__);
            status = false;
        }

        if (!status) {
            return false;
        }

        found_rel1 = (found_poset->second).find(value1);
        found_rel2 = (found_poset->second).find(value2);
        if (found_rel1 == (found_poset->second).end() || found_rel2 == (found_poset->second).end()) {
            elements_does_not_exist(id, value1, value2, __func__);
            return false;
        }
        else if (found_rel1->second.second.find(&(found_rel2->first)) != found_rel1->second.second.end() ||
                 found_rel2->second.second.find(&(found_rel1->first)) != found_rel2->second.second.end() ||
                 found_rel1 == found_rel2) {

            relation_cannot_be_added(id, value1, value2, __func__);
            return false;
        }
        else {
            poset_add_out(&(found_rel2->second.second), &(found_rel2->first), found_rel1->first, &(found_poset->second));
            poset_add_in(&(found_rel1->second.first), &(found_rel1->first), found_rel2->first, &(found_poset->second));

            relation_added(id, value1, value2, __func__);

            return true;
        }
    }
}

/*
#include <cassert>
using namespace std;
using namespace jnp1;
int main() {

    unordered_set<string> relations;
    unordered_map<string, unordered_set<string>> elements;
    unordered_map<string, int> mapa;
    // mapa["asd"]= 1;
    // string str2 = &(mapa.find("asd")->first);
    // cout<<str2<<endl;
*/
/*
    unsigned long id =  jnp1::poset_new();
    cout << "id = " << id << endl;
    cout << (jnp1::poset_size(id))<<endl;
    cout << jnp1::poset_insert(id, "abc") << endl;
    cout<<jnp1::poset_insert(0, "aabc") << endl;
    cout << "Size of poset id1 = " << (jnp1::poset_size(id)) << endl;
    unsigned long id_test = jnp1::poset_new();
    cout << jnp1::poset_insert(id_test, "siema") << endl;
    cout << jnp1::poset_insert(id_test, "siema") << endl;
    cout << jnp1::poset_insert(id_test, "siema2") << endl;
    auto it1 = jnp1::posets[id_test].find("siema");
    auto it2 = jnp1::posets[id_test].find("siema2");
    it1->second.second.insert(&(it2->first));
    it2->second.first.insert(&(it1->first));
    cout<< "Assert siema r siema2 = " <<jnp1::poset_test(id_test, "siema", "siema2") << endl;
    cout << "Assert del siema r siema2 = " << jnp1::poset_del(id_test, "siema", "siema2") << endl;
    cout << "Assert ! siema r siema2 = " << jnp1::poset_test(id_test, "siema", "siema2") << endl;
    cout<< "Size id_test = " << jnp1::poset_size(id_test) << endl;
    cout<< "Assert !in id1 siema r siema2 " <<jnp1::poset_test(id, "siema", "siema2") << endl;
    jnp1::poset_delete(id);
    jnp1::poset_delete(id_test);*/ /*
    unsigned long p1;

    p1 = poset_new();
    assert(poset_size(p1) == 0);
    assert(poset_size(p1 + 1) == 0);
    assert(!poset_insert(p1, NULL));
    assert(poset_insert(p1, "A"));
    assert(poset_test(p1, "A", "A"));
    assert(!poset_insert(p1, "A"));
    assert(!poset_insert(p1 + 1, "B"));
    assert(poset_size(p1) == 1);
    assert(!poset_remove(p1 + 1, "A"));
    assert(poset_remove(p1, "A"));
    assert(!poset_remove(p1, "A"));
    assert(poset_insert(p1, "B"));
    assert(poset_insert(p1, "C"));
    assert(poset_add(p1, "B", "C"));
    assert(!poset_remove(p1, "A"));
    assert(!poset_add(p1, NULL, "X"));
    assert(!poset_del(p1, NULL, "X"));
    assert(!poset_test(p1, NULL, "X"));
    assert(!poset_add(p1, "X", NULL));
    assert(!poset_del(p1, "X", NULL));
    assert(!poset_test(p1, "X", NULL));
    assert(!poset_add(p1, NULL, NULL));
    assert(!poset_del(p1, NULL, NULL));
    assert(!poset_test(p1, NULL, NULL));
    assert(!poset_add(p1, "C", "D"));
    assert(!poset_add(p1, "D", "C"));
    assert(!poset_del(p1, "C", "D"));
    assert(!poset_del(p1, "D", "C"));
    assert(!poset_test(p1, "C", "D"));
    assert(!poset_test(p1, "D", "C"));
    assert(!poset_add(p1 + 1, "C", "D"));
    assert(!poset_del(p1 + 1, "C", "D"));
    assert(!poset_test(p1 + 1, "C", "D"));
    poset_clear(p1);
    poset_clear(p1 + 1);
    assert(poset_insert(p1, "E"));
    assert(poset_insert(p1, "F"));
    assert(poset_insert(p1, "G"));
    assert(poset_add(p1, "E", "F"));
    assert(!poset_add(p1, "E", "F"));
    assert(!poset_add(p1, "F", "E"));
    assert(poset_test(p1, "E", "F"));
    assert(!poset_test(p1, "F", "E"));
    assert(poset_add(p1, "F", "G"));
    assert(poset_test(p1, "E", "G"));
    assert(!poset_del(p1, "E", "G"));
    assert(poset_del(p1, "E", "F"));
    assert(!poset_del(p1, "E", "F"));
    assert(!poset_del(p1, "G", "F"));
    assert(!poset_del(p1, "G", "G"));
    assert(poset_size(p1) == 3);
    poset_delete(p1);
    poset_delete(p1);
    poset_delete(p1 + 1);

    return 0;
}
*/