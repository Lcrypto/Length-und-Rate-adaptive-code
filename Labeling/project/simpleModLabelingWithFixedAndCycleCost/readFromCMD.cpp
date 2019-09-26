#include<string>
#include<iostream>
#include"typeCasting.h"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>


bool readFromCmd(int argc, char* argv[], bool& fullSearch, bool& givenFirstMatrix,
    int& SEED, int& START, int& END, int& MAX_CIRC, int& NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, int& NUMBER_OF_ATTEMPTS_FOR_ONE_STEP,
    int& VARIABLE_NODES, int& CHECK_NODES, std::string& INPUT_FILENAME, bool& FIXED_VALUES, int& UP_GIRTH, bool& DISCRETE_LIFTING, double& LIFT_PEN) {
    bool validInput = 1;
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("file", boost::program_options::value<std::string>(), "file with lifted matrix, optional parameter")
        ("regular", boost::program_options::value<std::string>(), "if protograph is regular with all entries equal to 1, then it is possible to set it with command --regular CHECK_VAR,")
        ("startCirc", boost::program_options::value<int>(), "minimum circ size, mandatory parameter")
        ("endCirc", boost::program_options::value<int>(), "maximum circ size, end = start * 2^k, mandatory parameter")
        ("maxCirc", boost::program_options::value<int>(), "max circ size to consider, it equal endCirc by default")
        ("seed", boost::program_options::value<int>(), "seed for our randomized algo, mandatory parameter")
        ("numberOfAttemptsForFirstMatrix", boost::program_options::value<int>(), "number of attempts for matrix with circ = start")
        ("numberOfAttemptsForOneStep", boost::program_options::value<int>(), "number of attempts to go from circ to 2 * circ, mandatory parameter")
        ("fullSearch", boost::program_options::value<int>(), "0/1 parameter, equals 1 iff we want to check all liftings for start circulant")
        ("givenFirstMatrix", boost::program_options::value<int>(), "0/1 parameter, equals 1 iff matrix in input file is lifted and we want to use it as a start matrix")
        ("fixedValues", boost::program_options::value<int>(), "0/1 parameter,  1 if we want too fix some values from the given matrix, 0/1 matrix must be placed after start matrix in the same file ")
        ("upGirth", boost::program_options::value<int>(), "cycles up to which girth should be considered, 8 by default")
        ("DISCRETE_LIFTING", boost::program_options::value<int>(), "0/1 parameter, equals 1 iff we use only small set of circulant from MSU team's presentation, 0 by default")
        ("LIFT_PEN", boost::program_options::value<double>(), "penalty for lifting is proportional to the (emd + 1)^LIFT_PEN, -1 by default");


        
    
        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);


        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        if ((!vm.count("file")) && (!vm.count("regular"))) {
            std::cout << "file has not been set\n";
            return 0;
        }

        if (vm.count("file"))
            INPUT_FILENAME = vm["file"].as<std::string>();

       


        if (!vm.count("startCirc")) {
            std::cout << "start circ has not been set\n";
            return 0;
        }
        else
            START = vm["startCirc"].as < int >();

        if (!vm.count("endCirc")) {
            std::cout << "end circ has not been set\n";
            return 0;
        }
        else
            END = vm["endCirc"].as < int >();

        if (!vm.count("maxCirc")) {
            MAX_CIRC = END;
        }
        else
            MAX_CIRC = vm["maxCirc"].as<int>();

        if (!vm.count("seed")) {
            std::cout << "seed has not been set\n";
            return 0;
        }
        else
            SEED = vm["seed"].as < int >();

        if (!vm.count("numberOfAttemptsForOneStep")) {
            std::cout << "numberOfAttemptsForOneStep has not been set\n";
            return 0;
        }
        else
            NUMBER_OF_ATTEMPTS_FOR_ONE_STEP = vm["numberOfAttemptsForOneStep"].as < int >();

        if (vm.count("numberOfAttemptsForFirstMatrix"))
            NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX = vm["numberOfAttemptsForFirstMatrix"].as<int>();

        if (vm.count("fullSearch"))
            fullSearch = vm["fullSearch"].as<int>();

        if (vm.count("givenFirstMatrix"))
            givenFirstMatrix = vm["givenFirstMatrix"].as<int>();

        if (vm.count("fixedValues"))
            FIXED_VALUES = vm["fixedValues"].as<int>();

        if (vm.count("upGirth"))
            UP_GIRTH = vm["upGirth"].as<int>();

        if (vm.count("DISCRETE_LIFTING"))
            DISCRETE_LIFTING = vm["DISCRETE_LIFTING"].as<int>();
        
        if (vm.count("LIFT_PEN"))
            LIFT_PEN = vm["LIFT_PEN"].as<double>();

        
        



    if ((NUMBER_OF_ATTEMPTS_FOR_ONE_STEP < 0) || (SEED < 0) || (START < 0) || (END < 0) || 
        (INPUT_FILENAME == "") || ((NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX < 0) && (!fullSearch) && (!givenFirstMatrix)))
        return 0;
    bool goodLimits = 1;
    if (END % START != 0) {
        goodLimits = 0;
    }
    else {
        long long ratio = END / START;
        while (ratio % 2 == 0)
            ratio /= 2;
        if (ratio != 1)
            goodLimits = 0;
    }

    if (!goodLimits) {
        std::cerr << "wrong limits\n";
        return 0;
    }
    return validInput;
}
