/* (C) Programmed by:Demiurgos  */
//Version:2.x //adapted version for decksim
//Binary read and write overloaded templates for STL Containers

#ifndef _RWBIN_H
#define _RWBIN_H
#endif

//max size of containers (this size is the biggest size that could be written, increasing this value (i.e unsigned int) will increase
//the maximun size and the actual size of the binary file
//This value will always be positive, always write an unsigned value to economise size of written file
//WARNING:max_size value should be the same when reading and writting
typedef unsigned short max_size;

//Writes an element in a binary file
//TEMPLATES R/W
template <typename T>
void binary_write(const T &element,ofstream &out);
template <typename T>
void binary_read(T &element,ifstream &input);

//PAIR R/W
//ifdef  _STL_PAIR_H
template <typename T,typename P>
void binary_write(const pair<T,P> &element,ofstream &out);
template <typename T,typename P>
void binary_read(pair<T,P> &element,ifstream &input);
//endif

//VECTOR R/W
//ifdef _STL_VECTOR_H
template <typename T>
void binary_write(const vector<T> &v,ofstream &out);
template <typename T>
void binary_read(vector<T> &v,ifstream &input);
//endif

//STRING R/W
//ifdef _STL_STRING_H
void binary_write(const string &element,ofstream &out);
void binary_read(string &element,ifstream &input);
//endif
//SET R/W
//ifdef _STL_SET_H
template <typename T>
void binary_write(const set<T> &v,ofstream &out);
template <typename T>
void binary_read(set<T> &v,ifstream &input);
//endif
//DEQUE R/W
//ifdef _STL_DEQUE_H
template <typename T>
void binary_write(const deque<T> &v,ofstream &out);
template <typename T>
void binary_read(deque<T> &v,ifstream &input);
//endif

//MAP R/W
//ifdef _STL_MAP_H
template <typename T,typename K>
void binary_write(const map<K,T> &m,ofstream &out);
template <typename T,typename K>
void binary_read(map<K,T> &m,ifstream &input);
//endif

/******************************************************/

//TEMPLATES R/W
template <typename T>
void binary_write(const T &element,ofstream &out) {
    out.write((char *)&element,sizeof(T));
}
//Reads an element from a binary file
template <typename T>
void binary_read(T &element,ifstream &input) {
    input.read((char *) &element,sizeof(T));
}

//PAIR R/W
//ifdef _STL_PAIR_H
//Writes a pair in a binary file
template <typename T,typename P>
void binary_write(const pair<T,P> &element,ofstream &out) {
    binary_write(element.first,out);
    binary_write(element.second,out);
}
//Reads a pair from a binary file
template <typename T,typename P>
void binary_read(pair<T,P> &element,ifstream &input) {
    binary_read(element.first,input);
    binary_read(element.second,input);
}
//endif
//VECTOR R/W
//ifdef _STL_VECTOR_H
//Writes a vector in a binary file, it writes the size of the vector first (unsigned)
template <typename T>
void binary_write(const vector<T> &v,ofstream &out) {
    max_size siz=v.size();
    T elem;
    binary_write(siz,out); //writes vector size
    for(max_size i=0; i<siz; i++) {
        elem=v[i];
        binary_write(elem,out); //writes each element
    }
}
//Reads a vector from a binary file
template <typename T>
void binary_read(vector<T> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read vector size
    T elem;
    v.clear();
    v.reserve(siz); //so its not necessary to change vector capacity later
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        v.push_back(elem);
    }
}
//endif
//STRING R/W
//ifdef _STL_STRING_H
//Read/Write string cases (usign a write as a vector)
void binary_write(const string &element,ofstream &out) {
    max_size siz=element.size();
    char c;
    binary_write(siz,out); //writes vector size
    for(max_size i=0; i<siz; i++) {
        c=element[i];
        binary_write(c,out);
    }
}

void binary_read(string &element,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read size
    char c;
    element.clear();
    element.reserve(siz); //so its not necessary to change capacity later
    for(max_size i=0; i<siz; i++) {
        binary_read(c,input);
        element.push_back(c);
    }
}
//endif
//SET R/W
//ifdef _STL_SET_H
template <typename T>
void binary_write(const set<T> &v,ofstream &out) {
    max_size siz=v.size();
    typename set<T>::const_iterator it;
    T elem;
    binary_write(siz,out); //writes set size
    for(it=v.begin(); it!=v.end(); it++) {
        elem=*it;
        binary_write(elem,out); //writes each element
    }
}

template <typename T>
void binary_read(set<T> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read set size
    T elem;
    v.clear();
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        v.insert(elem);
    }
}
//endif
//DEQUE R/W
//ifdef _STL_DEQUE_H
template <typename T>
void binary_write(const deque<T> &v,ofstream &out) {
    max_size siz=v.size();
    typename deque<T>::const_iterator it;
    T elem;
    binary_write(siz,out); //writes set size
    for(it=v.begin(); it!=v.end(); it++) {
        elem=*it;
        binary_write(elem,out); //writes each element
    }
}

template <typename T>
void binary_read(deque<T> &v,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read set size
    T elem;
    v.clear();
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        v.push_back(elem);
    }
}
//endif
//MAP R/W
//ifdef _STL_MAP_H
template <typename T,typename K>
void binary_write(const map<K,T> &m,ofstream &out) {
    max_size siz=m.size();
    binary_write(siz,out); //writes map size
    typename map<K,T>::const_iterator it;
    pair<K,T> elem;
    for(it=m.begin(); it!=m.end(); it++) {
        elem=*it;
        binary_write(elem,out); //writes each pair of elements
    }
}

template <typename T,typename K>
void binary_read(map<K,T> &m,ifstream &input) {
    max_size siz;
    binary_read(siz,input);//read map size
    pair<K,T> elem;
    m.clear();
    for(max_size i=0; i<siz; i++) {
        binary_read(elem,input);
        m.insert(elem);
    }
}
//endif

