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


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "replace.hpp"
#include <cstdlib>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::endl;

vector<string> split(string const & s)
{
    vector<string> rvandval;
    typedef boost::tokenizer<boost::char_separator<char> > tok_t;

    boost::char_separator<char> sep(" ", "", boost::keep_empty_tokens);
    tok_t tok(s, sep);
    for(tok_t::iterator i = tok.begin(); i!=tok.end(); ++i)
        rvandval.push_back(*i);
    return rvandval;
}

void replace (string const & olddrhfile, vector<string> & simresf){

    ifstream drhfile (olddrhfile); // the .drh file
    ofstream nudrhfile ("numodel.drh");
    
    
    if (drhfile.is_open())
    {
        string line2;

        while (getline (drhfile, line2))
        {
        
            for (unsigned i = 0; i < simresf.size(); i++) {
         
                string line1 = simresf[i];
                vector<string> rvandval = split(line1);
                string target1 = "(" + rvandval[0] + " ";
                string target2 = " " + rvandval[0] + " ";
                string target3 = rvandval[0] + " ";
                string target4 = " " + rvandval[0];
                string replace1 = "(" + rvandval[1] + " ";
                string replace2 = " " + rvandval[1] + " ";
                string replace3 = rvandval[1] + " ";
                string replace4 = " " + rvandval[1];

                boost::replace_all(line2, target1, replace1);
                boost::replace_all(line2, target2, replace2);
                boost::replace_all(line2, target3, replace3);
                boost::replace_all(line2, target4, replace4);
            
            }
            nudrhfile << line2 << endl;
        
        }
        drhfile.close();
    }else{
      cout << "Unable to open the drh model file. " << endl;
      exit (EXIT_FAILURE);
  }

  nudrhfile.close();

}
