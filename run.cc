#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <cmath>

#include "Data.hh"

// generic function comparing two values of some type T used later for int and
// double
template <class T>
bool testEqual(const std::string& name, T expected, T real) {
  if (expected != real) {
    std::cout << "(" << name << ": <" << expected << ">"
              << ", " << real << ") ";
    return false;
  }
  return true;
}

bool testReadingSize() {
  std::cout << "testReadingSize...";
  Data datA("testA");
  return testEqual<int>("size", 1, datA.size());
}

bool testReadingMeasurement() {
  std::cout << "testReadingMeasurement...";
  Data datA("testA");
  return testEqual("measurement", 10., datA.measurement(0));
}

bool testReadingBinEdges() {
  std::cout << "testReadingBinEdges...";
  Data datA("testA");
  return testEqual("bin low", 0., datA.binLow(0)) &&
         testEqual("bin high", 1., datA.binHigh(0));
}

bool testReadingErrors() {
  std::cout << "testReadingErrors...";
  Data datA("testA");
  return testEqual("error", 2., datA.error(0));
}

bool testCopyConstructor() {
  std::cout << "testCopyConstructor...";
  Data a("testA");
  Data b(a);
  Data c = a;  // equivalent to Data c(a)
  return testEqual("measurement", 10., b.measurement(0)) &&
         testEqual("measurement", 10., c.measurement(0));
}

void runTests() {
  std::cout << "running tests...\n";
  std::vector<std::function<bool()> > tests(
      {testReadingSize, testReadingMeasurement, testReadingBinEdges,
       testReadingErrors, testCopyConstructor});
  for (auto test : tests)
    std::cout << (test() ? " ok" : " FAILED!") << std::endl;
}
 int checkCompatibility(std::vector<Data> in, int n){
    int k=0;
    for(int l=0;l<=56;l++){
    double meany=0;
    for(int i=0; i<=3;i++){
    for(int j=i+1;j<=3;j++){
    double deltay=abs(in.at(i).measurement(l)-in.at(j).measurement(l));
    meany+=deltay;
    //std::cout<<deltay<<std::endl;} 
    }
    meany=meany/6;
    double varianzy=0;
    double sigmay=0;
    for(int i=0; i<=3;i++){
    for(int j=i+1;j<=3;j++){
    double deltay=abs(in.at(i).measurement(l)-in.at(j).measurement(l));
    varianzy+=pow(meany-deltay,2);
    }
  }
  sigmay=pow(varianzy,0.5);
  //std::cout<<sigmay<<std::endl;
  for(int i=0; i<=3;i++){
    for(int j=i+1;j<=3;j++){
    double deltay=abs(in.at(i).measurement(l)-in.at(j).measurement(l));  

  if (n*sigmay<deltay){k++;}
  }
  }
  }
  }
  return k;
  }



int main() {
  using namespace std;
  
  cout << "******************************************************" << endl;
  runTests();
  cout << "******************************************************" << endl;
  // create an object which holds data of experiment A
  Data datA("exp_A");
  Data datB("exp_B");
  Data datC("exp_C");
  Data datD("exp_D");
  vector<Data> Experimente;
  Experimente.push_back(datA);Experimente.push_back(datB);Experimente.push_back(datC);Experimente.push_back(datD);

  //cout<< Experimente.at(0).measurement(27)<<endl;
  //cout<< Experimente.at(1).measurement(27)<<endl;
  //cout<< Experimente.at(2).measurement(27)<<endl;
  //cout<< Experimente.at(3).measurement(27)<<endl;
  double meany=0;
  for(int i=0; i<=3;i++){
    for(int j=i+1;j<=3;j++){
    double deltay=abs(Experimente.at(i).measurement(27)-Experimente.at(j).measurement(27));
    meany+=deltay;
    cout<<deltay<<endl;}
  } 
  meany=meany/6;
  cout<<meany<<endl;
  double varianzy=0;
  double sigmay=0;
  for(int i=0; i<=3;i++){
    for(int j=i+1;j<=3;j++){
    double deltay=abs(Experimente.at(i).measurement(27)-Experimente.at(j).measurement(27));
    varianzy+=pow(meany-deltay,2);
    }
  }
  sigmay=pow(varianzy,0.5);
  cout<<varianzy<<endl;
  cout<<sigmay<<endl;

 
  //datA.checkCompatibility(datB,1);
  cout<<datA.checkCompatibility(datB,2)<<endl;
  // here is the data from experiment A
  cout << "bin 27: from " << datA.binLow(27) << " to " << datA.binHigh(27)
       << endl;
  cout << "measurement of experiment A in bin 27: " << datA.measurement(27)
       << endl;
  
  cout << "******************************************************" << endl;
  
  return 0;
}
