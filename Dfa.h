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

#ifndef DFA_H
#define DFA_H

#include <set>

template<typename T, typename X>
class ITransition {
public:
	virtual T* operator() (T& state, const X& symbol) = 0;
};

template<typename T, typename X = char> // T - state, X - input alphabet
class DFA {
private:
	
	std::set<T*> states; // a finite set of states Q
	std::set<X>* alphabet; // input symbols(alphabet) Σ
	ITransition<T,X>* transition; // δ : Q × Σ → Q
	T* initial; // start state q₀ ∈ Q
	std::set<T*> finals; // a set of accept states F ⊆ Q

	T* failState;
	T* current; // q ∈ Q

public:
	DFA();
	~DFA();

	void setTransition(ITransition<T,X>& transition);
	void setInitial(T& state);
	void addFinal(T& state);
	void setAlphabet(std::set<X>& alphabet);

	void setFailState(T& state);
	void step(const X& symbol);
	bool isFinal(); // check state's finality
	bool isFailed(); // if there is no path to go
	T& getCurrentState();
	void reset();

};

template<typename T, typename X>
DFA<T,X>::DFA() {

}

template<typename T, typename X>
DFA<T,X>::~DFA() {

}

template<typename T, typename X>
void DFA<T,X>::setTransition(ITransition<T,X>& transition) {
	this->transition = &transition;	
}

template<typename T, typename X>
T& DFA<T,X>::getCurrentState() {
	return *current;
}

template<typename T, typename X>
void DFA<T,X>::setInitial(T& state) {
	initial = &state;
	current = initial;
}

template<typename T, typename X>
void DFA<T,X>::step(const X& symbol) {
	if (current == failState) return;

	if (alphabet->find(symbol) == alphabet->end()) {
		current = failState;
		return;
	}

	T* state = (*transition)(*current, symbol);
	if (state) {
		current = state;
	} else {
		current = failState;
	}
}

template<typename T, typename X>
void DFA<T,X>::addFinal(T& state) {
	finals.insert(&state);	
}

template<typename T, typename X>
void DFA<T,X>::reset() {
	current = initial;
}

template<typename T, typename X>
void DFA<T,X>::setAlphabet(std::set<X>& alphabet) {
	this->alphabet = &alphabet;
}

template<typename T, typename X>
bool DFA<T,X>::isFinal() {
	if (current == failState) return false;
	return finals.find(current) != finals.end();
}

template<typename T, typename X>
bool DFA<T,X>::isFailed() {
	return current == failState;
}

template<typename T, typename X>
void DFA<T,X>::setFailState(T& state) {
	failState = &state;
}

#endif
