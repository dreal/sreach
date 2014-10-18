/***********************************************************************************************
 * Copyright (C) 2014 Qinsi Wang and Edmund M. Clarke.  All rights reserved.
 * By using this software the USER indicates that he or she has read, understood and will comply
 * with the following:
 *
 * 1. The USER is hereby granted non-exclusive permission to use, copy and/or
 * modify this software for internal, non-commercial, research purposes only. Any
 * distribution, including commercial sale or license, of this software, copies of
 * the software, its associated documentation and/or modifications of either is
 * strictly prohibited without the prior consent of the authors. Title to copyright
 * to this software and its associated documentation shall at all times remain with
 * the authors. Appropriated copyright notice shall be placed on all software
 * copies, and a complete copy of this notice shall be included in all copies of
 * the associated documentation. No right is granted to use in advertising,
 * publicity or otherwise any trademark, service mark, or the name of the authors.
 *
 * 2. This software and any associated documentation is provided "as is".
 *
 * THE AUTHORS MAKE NO REPRESENTATIONS OR WARRANTIES, EXPRESSED OR IMPLIED,
 * INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR THAT
 * USE OF THE SOFTWARE, MODIFICATIONS, OR ASSOCIATED DOCUMENTATION WILL NOT
 * INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS OR OTHER INTELLECTUAL PROPERTY
 * RIGHTS OF A THIRD PARTY.
 *
 * The authors shall not be liable under any circumstances for any direct,
 * indirect, special, incidental, or consequential damages with respect to any
 * claim by USER or any third party on account of or arising from the use, or
 * inability to use, this software or its associated documentation, even if the
 * authors have been advised of the possibility of those damages.
 * ***********************************************************************************************/


//assign values to random variables according to the distributions
//Bernoulli, Uniform, Normal, and Exponential distributions right now

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <boost/regex.hpp>
#include "simulation.hpp"
#include <cstdlib>
#include <vector>
#include <sstream>
#include "evalrv.hpp"

using std::bernoulli_distribution;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::exponential_distribution;
using std::ifstream;
using std::normal_distribution;
using std::ofstream;
using std::string;
using std::uniform_real_distribution;
using std::vector;
using std::ostringstream;

vector<string> simulation (vector<string> & distrfile){

    vector<string> assignfile;

    string s, sre, sre2, sre3;
    boost::regex re, re2, re3;
    boost::cmatch matches, matches2, matches3;
    
   

    for (unsigned i = 0; i < distrfile.size(); i++){
      
      string line2 = distrfile[i];
      string distr = line2.substr(0,1);

      if (distr == "B")
      {

          sre = "(B)(\\s)*(\\()([-+]?[0-9]*.?[0-9]+)(\\s)*(\\))(\\s)*([a-zA-Z][a-zA-Z0-9_]*)(;)(\\s)*";
          try
          {
              re = sre;
          }
          catch (boost::regex_error& e)
          {
              cout << sre << " is not a valid regular expression: \""
              << e.what() << "\"" << endl;
          }
          try {
              if (boost::regex_match(line2.c_str(), matches, re)) {

                  string paraStr = string() + matches[4];
                  double para = atof(paraStr.c_str());

                  std::random_device rd;
                  default_random_engine generator(rd());
                  bernoulli_distribution distribution(para);
                  double x = double(distribution(generator));
                  std::ostringstream strs;
                  strs << x;
                  std::string x_str = strs.str();
                  string Bsample = matches[8] + " " + x_str;
                  assignfile.push_back(Bsample);
              }else {cout << "Does not match!" << endl;}
          } catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<std::logic_error> > &) {
              cout << "regex_match failed!" << endl;
          }
      }
      else if (distr == "E")
      {
          sre = "(E)(\\s)*(\\()([-+]?[0-9]*.?[0-9]+)(\\s)*(\\))(\\s)*([a-zA-Z][a-zA-Z0-9_]*)(;)(\\s)*";
          try
          {
              re = sre;
          }
          catch (boost::regex_error& e)
          {
              cout << sre << " is not a valid regular expression: \""
              << e.what() << "\"" << endl;
          }
          try {
              if (boost::regex_match(line2.c_str(), matches, re)) {
                  string paraStr = string() + matches[4];
                  double para = atof(paraStr.c_str());
                  std::random_device rd;
                  default_random_engine generator(rd());
                  exponential_distribution<double> distribution(para);
                  double x = distribution(generator);
                  std::ostringstream strs;
                  strs << x;
                  std::string x_str = strs.str();
                  string Esample = matches[8] + " " + x_str;
                  assignfile.push_back(Esample);
              } else {cout << "Does not match!" << endl;}
          } catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<std::logic_error> > &) {
              cout << "regex_match failed!" << endl;
          }

      }
      else if (distr == "U")
      {
          sre = "(U)(\\s)*(\\()([-+]?[0-9]*.?[0-9]+)(\\s)*(,)(\\s)*([-+]?[0-9]*.?[0-9]+)(\\s)*(\\))(\\s)*([a-zA-Z][a-zA-Z0-9_]*)(;)(\\s)*";
          try
          {
              re = sre;
          }
          catch (boost::regex_error& e)
          {
              cout << sre << " is not a valid regular expression: \""
              << e.what() << "\"" << endl;
          }
          try {
              if (boost::regex_match(line2.c_str(), matches, re)) {
                  string paraStr1 = string() + matches[4];
                  double para1 = atof(paraStr1.c_str());
                  string paraStr2 = string() + matches[8];
                  double para2 =atof(paraStr2.c_str());
                  std::random_device rd;
                  default_random_engine generator(rd());
                  uniform_real_distribution<double> distribution(para1, para2);
                  double x = distribution(generator);
                  std::ostringstream strs;
                  strs << x;
                  std::string x_str = strs.str();
                  string Usample = matches[12] + " " + x_str;
                  assignfile.push_back(Usample);
              } else {cout << "Does not match!" << endl; }
          } catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<std::logic_error> > &) {
              cout << "regex_match failed!" << endl;
          }
      }
      else if (distr == "N")
      {
          sre = "(N)(\\s)*(\\()([-+]?[0-9]*.?[0-9]+)(\\s)*(,)(\\s)*([-+]?[0-9]*.?[0-9]+)(\\s)*(\\))(\\s)*([a-zA-Z][a-zA-Z0-9_]*)(;)(\\s)*";
          try
          {
              re = sre;
          }
          catch (boost::regex_error& e)
          {
              cout << sre << " is not a valid regular expression: \""
              << e.what() << "\"" << endl;
          }
          try {
              if (boost::regex_match(line2.c_str(), matches, re)) {
                  string paraStr1 = string() + matches[4];
                  double para1 = atof(paraStr1.c_str());
                  string paraStr2 = string() + matches[8];
                  double para2 =atof(paraStr2.c_str());
                  std::random_device rd;
                  default_random_engine generator(rd());
                  normal_distribution<double> distribution(para1, para2);
                  double x = distribution(generator);
                  std::ostringstream strs;
                  strs << x;
                  std::string x_str = strs.str();
                  string Nsample = matches[12] + " " + x_str;
                  assignfile.push_back(Nsample);
              } else {cout << "Does not match!" << endl; }
          } catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<std::logic_error> > &) {
              cout << "regex_match failed!" << endl;
          }
      }
      else if (distr == "D")
      {
          sre = "(DD)(\\s)*(\\()(([-+]?[0-9]*.?[0-9]+)(\\s)*(:)(\\s)*(1|(0.[0-9]+))(\\s)*(,)(\\s)*)*([-+]?[0-9]*.?[0-9]+)(\\s)*(:)(\\s)*(1|(0.[0-9]+)|([-+]?[0-9]*.?[0-9]+)(\\s)*(([-+*/])(\\s)*(0|[-+]?[0-9]*.?[0-9]+))+(\\)))(\\s)*(\\))(\\s)*([a-zA-Z][a-zA-Z0-9_]*)(;)(\\s)*";
          sre2 = "([-+]?[0-9]*.?[0-9]+)(\\s)*(:)(\\s)*(1|(0.[0-9]+)|([-+]?[0-9]*.?[0-9]+)(\\s)*([-+*/])(\\s)*([-+]?[0-9]*.?[0-9]+))";
          sre3 = "([a-zA-Z][a-zA-Z0-9_]*)(;)";
          try
          {
              re = sre;
              re2 = sre2;
              re3 = sre3;
          }
          catch (boost::regex_error& e)
          {
              cout << sre << " is not a valid regular expression: \""
              << e.what() << "\"" << endl;
          }
          try {
              if (boost::regex_match(line2.c_str(), matches, re)) {
                  
                  // get the var name first
                  boost::sregex_iterator rit2 (line2.begin(), line2.end(), re3);
                  boost::sregex_iterator rend2;
                  std::string ddvarname0 = rit2->str();
                  std::string ddvarname = ddvarname0.substr(0, ddvarname0.length()-1);
                  
                  boost::sregex_iterator rit (line2.begin(), line2.end(), re2);
                  boost::sregex_iterator rend;
                  std::vector<double> ddpara1;
                  std::vector<double> ddpara2;
                  std::string ddvalstr, ddprobstr;
                  char delimeter(':');
                  
                  while (rit!=rend) {
                      std::string ddres = rit->str();
                      std::string ddres2 = ddres.substr(1, (ddres.length() - 1));
                      std::istringstream iss(ddres2);
                      std::getline(iss, ddvalstr, delimeter);
                      double ddval = std::strtod(ddvalstr.c_str(), nullptr);
                      ddpara1.push_back(ddval);
                      std::getline(iss, ddprobstr);
                      //cout << ddprobstr << endl;
                      // call eval.cpp now
                      double ddprob;
                      if (ddprobstr.find('+')!=std::string::npos || ddprobstr.find('-')!=std::string::npos || ddprobstr.find('x')!=std::string::npos || ddprobstr.find('/')!=std::string::npos) {
                          ddprobstr = ddprobstr.substr(1);
                          ddprob = eval(ddprobstr);
                          cout << ddprob << endl;
                      }else{
                          ddprob = std::strtod(ddprobstr.c_str(), nullptr);
                          cout << ddprob << endl;
                      }
                      ddpara2.push_back(ddprob);
                      ++rit;
                      iss.clear();
                  }
                  
                  std::random_device rd;
                  std::default_random_engine generator(rd());
                  std::size_t j(0);
                  // call to ddpara2.front() / back() would fail otherwise!
                  assert(!ddpara2.empty());
                  
                  std::discrete_distribution<> distribution(ddpara2.size(),
                                                            ddpara2.front(),
                                                            ddpara2.back(),
                                                            [&ddpara2,&j](double)
                                                            {
                                                                auto w = ddpara2[j];
                                                                ++j;
                                                                return w;
                                                            });
                  float x = distribution(generator) + 1;
                  std::ostringstream strs;
                  strs << x;
                  std::string x_str = strs.str();
                  string Dsample = ddvarname + " " + x_str;
                  assignfile.push_back(Dsample);
                  
              } else {cout << "Does not match! DD" << endl; }
          } catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<std::logic_error> > &) {
              cout << "regex_match failed!" << endl;
          }
      }
    }
    
return assignfile;
}
