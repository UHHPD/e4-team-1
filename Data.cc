#include "Data.hh"
#include<cmath>
#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

using namespace std;

Data::Data(const std::string& filename) {
  ifstream file(filename);

  // check if file opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Error could not open file with name: " +
                             filename);
  }

  int size = -1;
  file >> size;

  // read in data from file: m_siz+1 bin edges
  for (int i = 0; i < size + 1; ++i) {
    double edge;
    file >> edge;
    m_bins.push_back(edge);
  }
  // read in data from file: m_siz bin contents
  for (int i = 0; i < size; ++i) {
    double entries;
    file >> entries;
    m_data.push_back(entries);
  }
  for (int i = 0; i < size; ++i) {
    double uncertainties;
    file >> uncertainties;
    m_uncertainty.push_back(uncertainties);
  }
  
  // done! close the file
  file.close();

  assertSizes();
};
int Data::checkCompatibility(const Data& in, int n){
  int k=0;
    for(int l=0;l<=56;l++){
    double deltay=abs(in.measurement(l)-measurement(l));
    //std::cout<<deltay<<endl;
    double sigmay=sqrt(pow(in.error(l),2)-pow(error(l),2));
  if (deltay>n*sigmay){k++;}
  }
return k;
}
void Data::assertSizes() { assert(m_data.size() + 1 == m_bins.size()); }

