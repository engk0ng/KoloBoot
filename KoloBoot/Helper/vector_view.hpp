//
//  vector_view.hpp
//  KoloBoot
//
//  Created by Abu Muhammad on 14/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef vector_view_hpp
#define vector_view_hpp

#include <stdio.h>
#include <iterator>
#include <vector>
#include <iostream>

template <typename T>
class vector_view {
    typedef std::vector<T> vector_type;
    
public:
    using value_type = typename vector_type::value_type;
    using allocator_type = typename vector_type::allocator_typel;
    using size_type = typename vector_type::size_type;
    using difference_type = typename vector_type::difference_type;
    using reference = typename vector_type::reference;
    using const_reference = typename vector_type::const_reference;
    using pointer = typename vector_type::pointer;
    using const_pointer = typename vector_type::const_pointer;
    
    struct iterator
    {
        vector_view& v;
        size_type i;
        iterator& operator++() {++i; return *this;}
        iterator& operator--() {--i; return *this;}
        reference operator*() const { return v[i];}
        bool operator!=(const iterator other) const {
            return &v != &other.v || i != other.i;
        }
    };
    
    struct const_iterator
    {
        const vector_view& v;
        size_type i;
        const_iterator& operator++() {++i; return *this;}
        const_iterator& operator--() {--i; return *this;}
        const_reference operator*() const { return v[i];}
        bool operator!=(const const_iterator other) const {
            return &v != &other.v || i != other.i;
        }
    };
    
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    explicit vector_view(vector_type& vec, int offset = 0):vec{vec}, offset{offset}
    {
        
    }
    
    const reference operator[](size_type index) const {
        return vec[(index + offset) % vec.size()];
    }
    
    reference operator[](size_type index) {
        return vec[(index + offset) % vec.size()];
    }
    
    void rotate(int rotation_length) {
        auto size = vec.size();
        offset = (offset + size - rotation_length) % size;
    }
    
    void set_rotation(int rotation_length) {
        offset = rotation_length % vec.size();
    }
    
    int rotation() const {
        return offset;
    }
    
    iterator begin() {
        return iterator{*this, 0};
    }
    
    const_iterator begin() const {
        return const_iterator{*this, 0};
    }
    
    const_iterator cbegin() const
    {
        return begin();
    }
    
    iterator end()
    {
        return iterator{*this, size()};
    }
    
    const_iterator end() const
    {
        return const_iterator{*this, size()};
    }
    
    const_iterator cend() const
    {
        return end();
    }
    
    bool empty() const
    {
        return vec.empty();
    }
    
    size_type size() const
    {
        return vec.size();
    }
    
private:
    vector_type& vec;
    int offset;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector_view<T>& view) {
    os << "[";
    
    std::string separator = "";
    for (auto element: view) {
        os << separator << element;
        separator = ", ";
    }
    
    return os << "]";
}

#endif /* vector_view_hpp */
