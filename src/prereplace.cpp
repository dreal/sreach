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

// for those rvs representing continuous probabilistic jumps, replace them with the sampled values
// return a vector containing the remaining rvs and their distributions
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "prereplace.hpp"
#include "replace.hpp"
#include <cstdlib>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::endl;


vector<string> prereplace (vector<string> & oldrvfile, vector<string> & presimresf){
   
  
    vector<string> nurvfile;

    for (unsigned i = 0; i < oldrvfile.size(); i++){
        
        string line2 = oldrvfile[i];
        string str = line2.substr(0, 1);
        
        for ( unsigned j = 0; j < presimresf.size(); j++) {
            
            string line1 = presimresf[j];
            vector<string> rvandval = split(line1);
            
            string target1 = "(" + rvandval[0] + " ";
            string target2 = " " + rvandval[0] + " ";
            string target3 = rvandval[0] + " ";
            string target4 = " " + rvandval[0];
            string target5 = rvandval[0] + ")";
            string target6 = " " + rvandval[0] + ",";
            string target7 = ":" + rvandval[0] + " ";
            string target8 = ":" + rvandval[0] + ",";
            
            string replace1 = "(" + rvandval[1] + " ";
            string replace2 = " " + rvandval[1] + " ";
            string replace3 = rvandval[1] + " ";
            string replace4 = " " + rvandval[1];
            string replace5 = rvandval[1] + ")";
            string replace6 = " " + rvandval[1] + ",";
            string replace7 = ":" + rvandval[1] + " ";
            string replace8 = ":" + rvandval[1] + ",";
            
            
            boost::replace_all(line2, target1, replace1);
            boost::replace_all(line2, target2, replace2);
            boost::replace_all(line2, target3, replace3);
            boost::replace_all(line2, target4, replace4);
            boost::replace_all(line2, target5, replace5);
            boost::replace_all(line2, target6, replace6);
            boost::replace_all(line2, target7, replace7);
            boost::replace_all(line2, target8, replace8);
        }
        if (str != "j"){
            nurvfile.push_back(line2);
        }
        
    }
    
    return nurvfile;
}
