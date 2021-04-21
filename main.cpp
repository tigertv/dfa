/*
 * MIT License
 *
 * This file is part of the 'dfa' (https://github.com/tigertv/dfa).
 * Copyright (c) 2021 Max Vetrov(tigertv).
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <string>
#include "Dfa.h"
#include "Transition.h"
#include "State.h"


int main() {
	State initState("S");
	State stateB("B");
	State stateC("C");
	State stateD("D");
	State failState("FAIL_STATE");
	std::set<char> alphabet = {'a', 'b'};

	DFA<State> dfa;

	Transition trans;
	trans.connect(initState, stateB, 'a');
	trans.connect(initState, stateC, 'b');
	trans.connect(stateB, stateD, 'b');
	trans.connect(stateC, stateD, 'b');
	trans.connect(stateD, stateC, 'a');
	dfa.setTransition(trans);

	dfa.setAlphabet(alphabet);
	dfa.setInitial(initState);
	dfa.addFinal(stateD);
	dfa.setFailState(failState);

	std::string s = "ababab";

	std::cout << "input string: " << s << std::endl;
	initState.print();
	std::cout << std::endl;
	for(char c: s) {
		std::cout << "char : " << c << std::endl;
		dfa.step(c);
		State& state = dfa.getCurrentState();
		state.print();
		std::cout << "is_final: " << dfa.isFinal() << std::endl;
		std::cout << "is_failed: " << dfa.isFailed() << std::endl;
		std::cout << std::endl;
	}

}
