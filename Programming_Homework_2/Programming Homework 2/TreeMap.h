#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "BinarySearchTree.h"

template<class K, class V>
class TreeMap {
public:
    TreeMap();

    void clear();
    const V &get(const K &key) const;
    const V &operator[](const K &key) const;

    void put(const K &key, const V &value);

    bool containsKey(const K &key);
    bool deletekey(const K &key);
    bool pop(const K &key);
    bool update(const K &key, const V &value);

    const KeyValuePair<K, V> &ceilingEntry(const K &key);
    const KeyValuePair<K, V> &floorEntry(const K &key);
    const KeyValuePair<K, V> &firstEntry();
    const KeyValuePair<K, V> &lastEntry();

    void pollFirstEntry();
    void pollLastEntry();
    
    void print() const;
    int size();

private:
    BinarySearchTree<KeyValuePair<K, V> > stree;
};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    stree.removeAllNodes();
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    KeyValuePair<K,V> searchedPair(key);
    
    return stree.get(searchedPair).getValue();
}

template<class K, class V>
bool TreeMap<K, V>::pop(const K &key) {
    
}

template<class K, class V>
bool TreeMap<K, V>::update(const K &key, const V &value) {
    KeyValuePair<K,V> newPair(key,value);
    stree.insert(newPair);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    KeyValuePair<K,V> removeItem(key);
    return stree.getCeiling(removeItem);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::floorEntry(const K &key) {
    //TODO
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {
    return stree.getMin();
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {
    return stree.getMax();
}

template<class K, class V>
void TreeMap<K, V>::pollFirstEntry() {
    //TODO
}

template<class K, class V>
void TreeMap<K, V>::pollLastEntry() {
    //TODO

}

template<class K, class V>
void TreeMap<K, V>::print() const {
    std::cout << "# TreeMap (BinarySearchTree):" << std::endl;
    stree.printPretty();
    std::cout << "# End TreeMap" << std::endl;
}

template<class K, class V>
int TreeMap<K, V>::size() {
    //TODO
}

template<class K, class V>
void TreeMap<K, V>::put(const K &key, const V &value) {
    KeyValuePair<K,V> newPair(key,value);
    stree.insert(newPair);
}

template<class K, class V>
const V &TreeMap<K, V>::operator[](const K &key) const {
    return get(key);
}

template<class K, class V>
bool TreeMap<K, V>::deletekey(const K &key) {
    KeyValuePair<K,V> deleteItem(key);
    return stree.remove(deleteItem);
}

template<class K, class V>
bool TreeMap<K, V>::containsKey(const K &key) {
    KeyValuePair<K,V> searchedItem(key);
    try{
        stree.get(searchedItem);
        return true;
    }
    catch(NoSuchItemException &){
        return false;
    }
}






#endif
