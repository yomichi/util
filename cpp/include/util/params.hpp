/**
 * params.hpp
 *
 * Minimal parameter file reader.
 * 
 * Copyright (c) 2013 by Yuichi Motoyama <yomichi@tsg.jp>
 *
 * Distributed under the Boost Software License version 1.0.
 * (See acompanied file License.txt or http://www.boost.org/LICENSE_1_0.txt)
 *
 */


#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

namespace util{

class Params{
  typedef std::map<std::string, std::string> map_type;
public:
  typedef typename map_type::iterator iterator;
  typedef typename map_type::const_iterator const_iterator;

  Params(){}
  Params(std::istream &is){ load(is);}
  Params(const char * filename)
  {
    std::ifstream ifs(filename);
    load(ifs);
  }
  Params(std::string const &filename)
  {
    std::ifstream ifs(filename.c_str());
    load(ifs);
  }

  void load(std::istream &is);
  void load(const char* filename)
  {
    std::ifstream ifs(filename);
    load(ifs);
  }
  void load(std::string const& filename)
  {
    std::ifstream ifs(filename.c_str());
    load(ifs);
  }

  template<class T>
  T value(const char* name) const {
    const_iterator it = dict_.find(name);
    if(it!=dict_.end())
      return boost::lexical_cast<T>(it->second);
    else{
      throw std::out_of_range("Parameter "+std::string(name)+" is not defined.");
    }
  }

  template<class T>
  T value(std::string const &name) const { return value<T>(name.c_str());}

  template<class T>
  T value_or_default(const char *name, T val) const
  {
    const_iterator it = dict_.find(name);
    return it!=dict_.end() ? boost::lexical_cast<T>(it->second) : val;
  }

  template<class T>
  T value_or_default(std::string const &name, T val) const { return value_or_default<T>(name.c_str(), val);}

  bool defined(std::string const &name) const
  {
    const_iterator it = dict_.find(name);
    return it!=dict_.end();
  }

  iterator begin(){ return dict_.begin();}
  const_iterator begin()const { return dict_.begin();}
  iterator end(){ return dict_.end();}

private:
  map_type dict_;
};

void Params::load(std::istream &is)
{
  std::string buf;
  while(!is.eof()){
    getline(is, buf);
    std::stringstream ss(buf, std::stringstream::in | std::stringstream::out);
    std::string name, val;
    ss >> name >> val;
    dict_[name] = val;
  }
}

} // end of namespace util

#endif
