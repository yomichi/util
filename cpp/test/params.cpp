#include "../include/params.hpp"

int main()
{
  using namespace std;
  using namespace util;
  
  Params params(cin);

  cout << "L " << params.value<int>("L") << endl;
  cout << "T " << params.value<double>("T") << endl;
  cout << "MCS " << params.value_or_default<long>("MCS", 8192) << endl;
  if(params.defined("Flag"))
    cout << "\"Flag\" is defined." << endl;
  
  try{
    params.value<double>("Hoge");
  }catch (out_of_range &e){
    cout << e.what() << endl;
  }

}

