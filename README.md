<a href="https://scan.coverity.com/projects/1715">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/1715/badge.svg"/>
</a>

``SReach`` is a Bounded Model Checker for hybrid systems with parametric uncertainty, and probabilistic hybrid automata with addtional randomness. It combines dreal/dreach and statistical analyzing methods.

Installation
============

Required Packages
-----------------

 - [GSL](GNU Scientific Library)
 - [Boost]
 - [CMake]
 - [dReal] and [dReach]

[GSL]: http://www.gnu.org/software/gsl/
[Boost]: http://www.boost.org/
[CMake]: http://www.cmake.org/
[dReal]: http://dreal.cs.cmu.edu
[dReach]: http://dreal.cs.cmu.edu

Compile
-------

    mkdir build
    cd build
    cmake -DCMAKE_CXX_COMPILER=g++-4.9 -DCMAKE_C_COMPILER=gcc-4.9 ../src
    make

We have tested them under Ubuntu 12.04, and Mac OSX v10.9.2.
``SReach`` uses the GNU Scientific Library (GSL), so you need that
to be installed.

Usage
=====

The command line is as follows:

     <testfile> <prob_drh-modelfile> <dReach> <k-unfolding_steps_for_dreach_model> <precision>

where:

 - ``<testfile>`` is a text file containing a sequence of test specifications, give the path to it
 - ``<prob_drh-modelfile>`` is the file name and path of the probabilistic extension model of the dreach model
 - ``<dReach>`` is the dReach executable, give the path to it
 - ``<k-unfolding_steps_for_dreach_model>`` is the given steps to unfold the probabilistic hybrid system
 - ``<precision>`` is the given \delta for the \delta-decision procedure dReal/dReach

For example, try the following command (the path for dReach needs to be changed):

    ./sreach_sq(or sreach_para) ../statistical_test/test01 \\
                 ../models/bouncing_ball_with_drag.pdrh \\
                 ~/Desktop/qinsiw/sreach/dreal/bin/dReach \\
                 8 \\
                 0.001

The final output should be the dReach output followed by something like:

    BFTI 0.9 1000 1 1 0.01: Reject Null Hypothesis, successes = ??, samples = ??


To time the total CPU time, use command "time" before the command line of SReach.

For more details, the user can go to the [Statistical_testing.pdf][testing], and [Usage.pdf][usage] in the [documents][doc] folder.

[testing]: https://github.com/dreal/SReach/raw/master/documents/Statistical_testing.pdf
[usage]: https://github.com/dreal/SReach/raw/master/documents/Usage.pdf
[doc]: https://github.com/dreal/SReach/tree/master/documents
