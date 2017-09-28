#ifndef SIMPLERENDER_VERTEXCONTAINER_INL
#define SIMPLERENDER_VERTEXCONTAINER_INL

template<typename T, typename C>
auto Container<T, C>::begin() {
    return mRoom.begin();
}

template<typename T, typename C>
auto Container<T, C>::end() {https://stackoverflow.com/questions/11275444/c-template-typename-iterator
    return mRoom.end();
}

// push_back
template<typename T, typename C>
int Container<T, C>::push_back(const T& item) {
    mRoom.push_back(item);
    return mRoom.size() - 1;
}

// replace
template<typename T, typename C>
void Container<T, C>::replace(It it, T item) {
    mRoom.insert(mRoom.remove(it), item);
}

// return the iterator pointer to element after it
template<typename T, typename C>
auto Container<T, C>::remove(It it) {
    return mRoom.erase(*it);
}

// return the iterator pointer to item
template<typename T, typename C>
auto Container<T, C>::insert(It it, const T& item) {
    // insert item before it
    mRoom.insert(it, item);
}

template<typename T, typename C>
int Container<T, C>::size() const noexcept {
    return mRoom.size();
};

#endif