#ifndef SIMPLERENDER_VERTEXCONTAINER_INL
#define SIMPLERENDER_VERTEXCONTAINER_INL

template<typename T, typename C>
auto Container<T, C>::begin() {
    return mRoom.begin();
}

template<typename T, typename C>
auto Container<T, C>::end() {
    return mRoom.end();
}

template<typename T, typename C>
const auto Container<T, C>::begin() const {
    return mRoom.begin();
}

template<typename T, typename C>
const auto Container<T, C>::end() const {
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
auto Container<T, C>::erase(It it) {
    return mRoom.erase(it);
}

// return the iterator pointer to last, last won't be erased
template<typename T, typename C>
auto Container<T, C>::erase(It first, int len) {
    return mRoom.erase(first, next(first, len));
}

template<typename T, typename C>
void Container<T, C>::clear() {
    mRoom.clear();
}

// return the iterator pointer the next of item
template<typename T, typename C>
auto Container<T, C>::insert(It it, const T &item) {
    return next(mRoom.insert(it, item));
}

template<typename T, typename C>
int Container<T, C>::size() const noexcept {
    return mRoom.size();
};

template<typename T, typename C>
const T& Container<T, C>::operator[](int n) const {
    return mRoom[n];
}
#endif