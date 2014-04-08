<a href="https://scan.coverity.com/projects/1715">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/1715/badge.svg"/>
</a>

``statsmt_sq`` is a combination of dreal/dreach and statistical analyzing methods (sequential version).

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

    make build
    cd build
    cmake ../src
    make

We have tested them under Mac OSX v10.9.2, and Ubuntu 12.04.
``statsmt_sq`` uses the GNU Scientific Library (GSL), so you need that
to be installed.

Usage
=====

The command line is as follows:

    statsmt <testfile> <prob_drh-modelfile> <dReach> <k-unfolding_steps_for_dreach_model>

where:

 - ``<testfile>`` is a text file containing a sequence of test specifications, give the path to it
 - ``<prob_drh-modelfile>`` is the file name and path of the probabilistic extension model of the dreach model
 - ``<dReach>`` is the dReach executable, give the path to it
 - ``<k-unfolding_steps_for_dreach_model>`` is the given steps to unfold the probabilistic hybrid system

For example, try the following command (the path for dReach needs to be changed):

    ./statsmt_sq ../statistical_test/test01 \\
                 ../models/bouncing_ball_with_drag.pdrh \\
                 ~/Desktop/qinsiw/misc/dreal/bin/dReach \\
                 8

The final output should be the dReach output followed by something like:

    BFTI 0.9 1000 1 1 0.01: Reject Null Hypothesis, successes = ??, samples = ??
    Elapsed time: ?? seconds

where the question mark figures vary from run to run, of course.

Since dReach will be called for each simulation/sampling, it may take
some time to return the final result if the pdrh model is large.


Specification of the model file
===================================
the ``.pdrh`` model file has the similar format of dReach's ``drh``
file, except the following differences:

 - In the declaration section of variables, the user can add
   declarations for the system parameters which are random variables.
   E.g:

   ````
   N(1, 1) rv1;
   B(1) rv2;
   U(9.8, 9.8) g;
   ````
   Currently, it can handle Bernoulli, Uniform, Normal, and
   Exponential distributions, which are widely used. (It is not hard
   to add any other distributions upon the demands.)


 - In the pre-process section (#define), the user can also use the declared random variables.

For more details, the user can go to the given sample models.
