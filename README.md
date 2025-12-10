[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21756547)
# ELEC2645 Unit 2 Project Template
# Engineering Toolkit (C)

A lightweight, menu-driven engineering assistant for Electrical and Electronic Engineering students.  
Designed to speed up lab work with quick circuit calculations, digital signal generation, waveform analysis,  
and engineering unit conversions — all in a single portable C program.

# Functions
Basic Circuit Analyser      Ohm’s Law, Series/Parallel R, RC/RL time constant, Power	    Quick lab calculations
Signal Generator	        Sine / Square / Triangle / Sawtooth + CSV export	            Create test signals
Frequency Analyser	        RMS / Peak / Mean / Zero-crossing / Simplified DFT          	Validate signal behaviour
Unit Converter	            V, A, Ω, Hz, W, C, L conversions	                            Prevent scaling mistakes

# Test
Circuit Analyser	Correct calculation output based on known EE equations
Signal Generator	Value range, sampling rule (fs ≥ 2×freq), memory safety
Frequency Analysis	Consistent 50 Hz recovery from synthetic CSV file
Unit Converter	    Accurate scaling and numeric stability


# Overall
Electrical engineering labs often require quick calculations, waveform testing, and frequency measurement.
This tool centralises these tasks into a single lightweight program to: Reduce switching between devices, Improve measurement repeatability, Reinforce theoretical learning through interaction, Ensure accuracy in lab documentation

### 1 Run code

You can build the code as we have been using in the labs with 
`gcc main.c funcs.c -o main.out -lm` (the `-lm` is required to link the math library). You can also use `make -B` to force a rebuild using the provided `Makefile`.

Then run the code with `./main.out`


### 2 The assignment

Please read the assignment brief on the Minerva page for details of what you need to implement. 



### 3 Test command

The `test.sh` script is provided to check that your code compiles correctly. This is what the autograder will use to check your submission. You can run it with `bash test.sh` or `./test.sh` or just `make test`. 


You do not need to modify this script, but you can look at it to see what it does.


### 4 Submit Solution

Use the same method as previous labs to commit and push your code to your GitHub repository for the autograder to check. 

In your final journal post, please include a link to your GitHub repository containing your code  *and* a zip file of your code as an attachment.

