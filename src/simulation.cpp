/***********************************************************************************************
 * Copyright (C) 2014 Qinsi Wang and Edmund M. Clarke.  All rights reserved.
 * Note: the implementation of different statistical testing classes are from the statistical model checker developed by Paolo Zuliani.
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

void simulation (string const & distrfile){

  ifstream rvfile (distrfile); // the random variables file

  ofstream assignfile ("simres.txt"); // output the simulation results for rvs


  if (rvfile.is_open())
  {
    string s, sre, line2;
    boost::regex re;
    boost::cmatch matches;

    while (getline (rvfile, line2))
    {
      string distr = line2.substr(0,1);

      if (distr == "B")
      {

          sre = "(B)(\\s)*(\\()([-+]?[0-9]*.?[0-9]+)(\\s)*(\\))(\\s)*([a-zA-Z][a-zA-Z0-9_]*)(;)(\\s)*";
          try
          {
              // Assignment and construction initialize the FSM used
              // for regexp parsing
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
                  double para = atof(paraStr.c_str());//parameter for the bernoulli distribution

                  default_random_engine generator(time(0));
                  bernoulli_distribution distribution(para);
                  double x = double(distribution(generator));
                  assignfile << matches[8] << " " << x << endl;
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
                  default_random_engine generator(time(0));
                  exponential_distribution<double> distribution(para);
                  double x = distribution(generator);
                  assignfile << matches[8] << " " << x << endl;
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
                  default_random_engine generator(time(0));
                  uniform_real_distribution<double> distribution(para1, para2);
                  double x = distribution(generator);
                  assignfile << matches[12] << " " << x << endl;
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
                  default_random_engine generator(time(0));
                  normal_distribution<double> distribution(para1, para2);
                  double x = distribution(generator);
                  assignfile << matches[12] << " " << x << endl;
              } else {cout << "Does not match!" << endl; }
          } catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<std::logic_error> > &) {
              cout << "regex_match failed!" << endl;
          }
      }
    }
    rvfile.close();
  }
  else
  cout << "Unable to open the distribution file. " << endl;



    assignfile.close();

}
