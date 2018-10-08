#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

IntSet::IntSet(){ used = 0; }

int IntSet::size() const { return used; }


bool IntSet::isEmpty() const{
    if(!size()) return true;
    return false;
}

bool IntSet::contains(int anInt) const{
    for(int i = 0; i < size(); ++i){
        if (anInt == data[i]) return true;
    }
    return false;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const{
    //is "this" a subset of otherIntSet?
    for(int i=0;i < size();++i){
        if (!otherIntSet.contains(data[i])) return false;
    }
    return true;
}

void IntSet::DumpData(ostream& out) const{
    // already implemented ... DON'T change anything
    if (size() > 0){
      out << data[0];
       for (int i = 1; i < size(); ++i)
           out << "  " << data[i];
    }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const{
    //"this" intset is returned as the union of itself with otherIntSet
    IntSet dummy = *this;
    for(int i=0;i<otherIntSet.size();++i){
        if(!contains(otherIntSet.data[i])) dummy.add(otherIntSet.data[i]);
    }
    return dummy; // dummy IntSet object returned
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const{

    IntSet dummy;
    dummy.reset();
    
    for(int i=0; i<size(); ++i){
        if(otherIntSet.contains(data[i])){
            dummy.add(data[i]);
        }
    }

   return dummy; // dummy IntSet object returned
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const{
    //IntSet(ret)=Int(orig)-otherIntSet
    IntSet dummy = *this;
    for(int i=0;i<otherIntSet.size();++i){
        dummy.remove(otherIntSet.data[i]);
        }
   return dummy; // dummy IntSet object returned
}

void IntSet::reset(){ for(int i=0;i<MAX_SIZE;++i) data[i]=0; }

bool IntSet::add(int anInt){
    if (!contains(anInt)) {
        data[size()] = anInt;
        ++used;
        return true;
    }
   return false; // dummy value returned
}

bool IntSet::remove(int anInt){
//assuming that ALL elems matching anInt should be removed

    if(contains(anInt)){
        int tArr[MAX_SIZE];
        for(int j=0,i=0;i < size();++i){    //copy over non-matching elems to temp
            if(data[i]!=anInt){
                tArr[j++]=data[i]; //tempArr now has elems != anInt
            }
            //reduce size of tArray by one every time a match is found
        }
        reset();
        used--;
        for(int i=0;i < size();++i){
            data[i]=tArr[i]; //read array(sans anInt) back into data[]
        }
        return true;
    }
   return false; // dummy value returned
}

bool equal(const IntSet& is1, const IntSet& is2){
    
    if (is1.size()!=is2.size()) return false;
    
    IntSet dummy;
    dummy.reset();  //set all elements to zero
    dummy = is1.intersect(is2);
    if (dummy.size() == is1.size()) return true;
    return false; // dummy value returned
    
}

