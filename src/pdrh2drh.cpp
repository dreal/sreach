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




//read in a pdrh file
//output a txt file containing all random variables and their corresponding
//distributions, and a drh file
#include <iostream>
#include <fstream>
#include <string>
#include "pdrh2drh.hpp"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

void pdrh2drh (string const & modelfile) {
  string line;
  ifstream myfile1 (modelfile);
  ofstream myfile2 ("rv.txt");
  ofstream myfile3 ("model_w_define.drh");
  if (myfile1.is_open())
  {
    while (getline (myfile1, line))
    {

      string str = line.substr(0, 2);
      if (str == "B(" || str =="N(" || str =="U(" || str =="E(")
      {
        myfile2 << line << '\n';
      }
      else{
        myfile3 << line << '\n';
      }
    }
    myfile1.close();
    myfile2.close();
    myfile3.close();
  }
  else {
      cout << "Unable to open the given pdrh model file";
      exit (EXIT_FAILURE);
  }
}
