/**
 * mkplt.cpp
 *
 * make plot XML file for ALPS application (http://alps.comp-phys.org/)
 *
 * Copyright (c) 2013 by Yuichi Motoyama <yomichi@tsg.jp>
 *
 * Distributed under the Boost Software License version 1.0.
 * (See acompanied file License.txt or http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


struct axis{
  std::string name;
  std::string t;
  axis(std::string const &name_, std::string const &t_):name(name_), t(t_){}
};

struct feach{
  std::string name;
  feach(std::string const &n):name(n){}
};

struct constraint{
  std::string name;
  std::string val;
  std::string t;
  std::string ct;
  constraint(std::string const &name_, std::string const &val_, std::string const &t_, std::string const &ct_):name(name_),val(val_),t(t_),ct(ct_){}
};

void help()
{
  std::clog << "required fields : \n"
            << "-x  name :  alias of '-xp name'. \n"
            << "-xp name :  set <xaxis name=\"name\" type=\"parameter\" />  \n"
            << "-xm name :  set <xaxis name=\"name\" type=\"mean\" error=\"true\" />  \n"
            << "-xi name :  set <xaxis name=\"name\" type=\"index\" />  \n"
            << "you should choose one of them.\n\n"
            << "-y  name :  alias of '-ym name'.  \n"
            << "-yp name :  set <yaxis name=\"name\" type=\"parameter\" />  \n"
            << "-ym name :  set <yaxis name=\"name\" type=\"mean\" error=\"true\" />  \n"
            << "-yt name :  set <yaxis name=\"name\" type=\"autocorr\"/>  \n"
            << "you should choose one of them.\n\n"
            << "\n"
            << "option fields : \n"
            << "-f  name :  set <foreach name=\"<name>\" >.  \n"
            << "-e  name val : alias of '-ep name val'. \n"
            << "-ep name val :  set <constraint name=\"name\" type=\"parameter\" operator=\"equal\" value=\"val\" />. \n"
            << "-em name val :  set <constraint name=\"name\" type=\"mean\" operator=\"equal\" value=\"val\" />. \n"
            << "-g  name val : alias of '-gp name val'. \n"
            << "-gp name val :  set <constraint name=\"name\" type=\"parameter\" operator=\"greater\" value=\"val\" />. \n"
            << "-gm name val :  set <constraint name=\"name\" type=\"mean\" operator=\"greater\" value=\"val\" />. \n"
            << "-l  name val : alias of '-lp name val'. \n"
            << "-lp name val :  set <constraint name=\"name\" type=\"parameter\" operator=\"less\" value=\"val\" />. \n"
            << "-lm name val :  set <constraint name=\"name\" type=\"mean\" operator=\"less\" value=\"val\" />. \n"
            << "-o name : output file \n"
            << "-h      : show this message. \n"
            << std::endl;
}

int main(int argc, char** argv)
{
  using namespace std;
  if(argc == 1){
    help();
    return 0;
  }

  vector<axis> xa,ya;
  vector<feach> feachs;
  vector<constraint> constraints;
  vector<string> filename;

  int argi=1;
  while(argi<argc){
    string arg(argv[argi]);

    if(arg == "-x" || arg == "-xp"){
      ++argi;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      xa.push_back(axis(argv[argi], "parameter"));
      ++argi;
      continue;
    }
    if(arg == "-xm"){
      ++argi;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      xa.push_back(axis(argv[argi], "mean"));
      ++argi;
      continue;
    }
    if(arg == "-xi"){
      ++argi;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      xa.push_back(axis(argv[argi], "index"));
      ++argi;
      continue;
    }
    if(arg == "-y" || arg == "-ym"){
      ++argi;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      ya.push_back(axis(argv[argi], "mean"));
      ++argi;
      continue;
    }
    if(arg == "-yp"){
      ++argi;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      ya.push_back(axis(argv[argi], "parameter"));
      ++argi;
      continue;
    }
    if(arg == "-yt"){
      ++argi;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      ya.push_back(axis(argv[argi], "autocorr"));
      ++argi;
      continue;
    }
    if(arg == "-f"){
      ++argi;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      feachs.push_back(feach(argv[argi]));
      ++argi;
      continue;
    }
    if(arg == "-e" || arg == "-ep"){
      argi+=2;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      constraints.push_back(constraint(argv[argi-1], argv[argi], "parameter", "equal" ));
      ++argi;
      continue;
    }
    if(arg == "-em"){
      argi+=2;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      constraints.push_back(constraint(argv[argi-1], argv[argi], "mean", "equal" ));
      ++argi;
      continue;
    }
    if(arg == "-g" || arg == "-gp"){
      argi+=2;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      constraints.push_back(constraint(argv[argi-1], argv[argi], "parameter", "greater" ));
      ++argi;
      continue;
    }
    if(arg == "-gm"){
      argi+=2;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      constraints.push_back(constraint(argv[argi-1], argv[argi], "parameter", "greater" ));
      ++argi;
      continue;
    }
    if(arg == "-l" || arg == "-lp"){
      argi+=2;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      constraints.push_back(constraint(argv[argi-1], argv[argi], "parameter", "less" ));
      ++argi;
      continue;
    }
    if(arg == "-lm"){
      argi+=2;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      constraints.push_back(constraint(argv[argi-1], argv[argi], "mean", "less" ));
      ++argi;
      continue;
    }
    if(arg == "-o"){
      ++argi;
      if(argi >=argc){
        cerr << "params error\n";
        return 0;
      }
      filename.push_back(argv[argi]);
      ++argi;
      continue;
    }
    if(arg == "-h"){
      help();
      return 0;
    }
  }
  if(xa.size()!=1 || ya.size()!=1){
    cerr << "params erro\n";
    help();
    return 0;
  }

  ofstream output;
  if(filename.size()>0){
    output.open(filename[0].c_str());
    cout.rdbuf(output.rdbuf());
  }

  cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
       << "<!DOCTYPE plot SYSTEM \"conf/plot.dtd\">\n"
       << "<plot name=\"" << xa[0].name << " vs " << ya[0].name << "\" output=\"text\">\n";
  for(int i = 0; i < feachs.size(); ++i){
    cout << "<for-each name=\"" << feachs[i].name << "\">\n";
  }
  for(int i = 0; i < constraints.size(); ++i){
    cout << "<constraint name=\"" << constraints[i].name
         << "\" type=\"" << constraints[i].t
         << "\" operator=\"" << constraints[i].ct
         << "\" value=\"" << constraints[i].val
         << "\" />\n";
  }
  if(xa[0].t == "parameter")
    cout << "<xaxis name=\"" << xa[0].name << "\" type=\"parameter\"/>\n";
  else  if(xa[0].t == "mean")
    cout << "<xaxis name=\"" << xa[0].name << "\" type=\"mean\" />\n";
  else
    cout << "<xaxis name=\"" << xa[0].name << "\" type=\"index\" />\n";
  if(ya[0].t == "parameter")
    cout << "<yaxis name=\"" << ya[0].name << "\" type=\"parameter\"/>\n";
  else if(ya[0].t == "autocorr")
    cout << "<yaxis name=\"" << ya[0].name << "\" type=\"autocorr\"/>\n";
  else
    cout << "<yaxis name=\"" << ya[0].name << "\" type=\"mean\" error=\"true\"/>\n";
  
  for(int i=0; i<feachs.size(); ++i){
    cout << "</for-each>\n";
  }
  cout << "</plot>\n";

  return 0;
}
