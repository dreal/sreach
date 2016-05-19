``SReach`` is a Bounded Model Checker for hybrid systems with parametric uncertainty, and probabilistic hybrid automata with addtional randomness. It combines dreal/dreach and statistical analyzing methods.

Installation
============

Required Packages
-----------------

 - Clang-omp
 - [GSL](GNU Scientific Library)
 - [Boost] (Link with libc++)
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
    cmake -DCMAKE_CXX_COMPILER=clang-omp++ ../src
    make

We have tested them under Ubuntu 12.04, and Mac OSX EI Capitan v10.11.5.

Usage
=====

The command line is as follows:

     <testfile> <prob_drh-modelfile> <dreach> <k-unfolding_steps_for_dreach_model> <precision>

where:

 - ``<testfile>`` is a text file containing a sequence of test specifications, give the path to it
 - ``<prob_drh-modelfile>`` is the file name and path of the probabilistic extension model of the dreach model
 - ``<dreach>`` is the exectuable dreach
 - ``<k-unfolding_steps_for_dreach_model>`` is the given steps to unfold the probabilistic hybrid system
 - ``<precision>`` is the given \delta for the \delta-decision procedure dReal/dReach

For example, try the following command (the path for dReach needs to be changed):

    ./sreach_sq(or sreach_para) ../statistical_test/test01 \\
                 ../models/bouncing_ball_with_drag.pdrh \\
                 dreach \\
                 8 \\
                 0.001

The final output should be the dReach output followed by something like:

    BFTI 0.9 1000 1 1 0.01: Reject Null Hypothesis, successes = ??, samples = ??


To time the total CPU time, use command "time" before the command line of SReach.

For more details, the user can go to the [Statistical_testing.pdf][testing], and [Usage.pdf][usage] in the [documents][doc] folder.

[testing]: https://github.com/dreal/SReach/raw/master/documents/Statistical_testing.pdf
[usage]: https://github.com/dreal/SReach/raw/master/documents/Usage.pdf
[doc]: https://github.com/dreal/SReach/tree/master/documents
