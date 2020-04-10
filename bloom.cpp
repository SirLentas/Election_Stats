#include<iostream>
#include "bloom.h"
#include "hashFunctions.h"
using namespace std;

#define SetBit(bits,k)     ( bits[(k/32)] |= (1 << (k%32)) )
#define ClearBit(bits,k)   ( bits[(k/32)] &= ~(1 << (k%32)) )
#define TestBit(bits,k)    ( bits[(k/32)] & (1 << (k%32)) )

BloomFilter::BloomFilter(int elements=0){
    length_bit=0;
    mbits=NULL;
    initialize(elements);
}

BloomFilter::~BloomFilter(){
    delete mbits;
    cout<<"BloomFilter deleted!"<<endl;
}

void BloomFilter::initialize(int elements){
    int length_int=3*elements;
    length_int=length_int+1;
    int j=2;
    while(1)
    {
        for(j=2;j<length_int;j++)
        {
        if(length_int %j==0)
        {
            break;
        } 
        } 
        if(length_int==j || length_int==1)
        {
        break;
        } 
        length_int++;
    } 
    cout<<"prime------------"<<length_int<<endl;
    length_int=length_int/32;
    if(length_int%32!=0)   
        length_int++;
    mbits=new int[length_int];
    length_bit=length_int*32;
    for(int i=0;i<length_int;i++){
        mbits[i]=0;
    }
}

void BloomFilter::add(char* id){
    SetBit(mbits,h3(h1(id,length_bit),h2(id,length_bit),1,length_bit));
    SetBit(mbits,h3(h1(id,length_bit),h2(id,length_bit),2,length_bit));
    SetBit(mbits,h3(h1(id,length_bit),h2(id,length_bit),3,length_bit));
}

void BloomFilter::print(){
    int i;
    for ( i = 0; i < length_bit; i++ ){
        cout<<i<<"[";
        if ( TestBit(mbits, i) )
            cout<<"1";
        else
            cout<<"0";
        cout<<"]"<<endl;
    }
}

bool BloomFilter::search(char *id){
  if(!TestBit(mbits,h3(h1(id,length_bit),h2(id,length_bit),1,length_bit)))
    return false;
  if(!TestBit(mbits,h3(h1(id,length_bit),h2(id,length_bit),2,length_bit)))
    return false;
  if(!TestBit(mbits,h3(h1(id,length_bit),h2(id,length_bit),3,length_bit)))
    return false;
  return true;
}