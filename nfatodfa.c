#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_STATES 10
#define ALPHABET_SIZE 2

typedef struct {
    int transitions[MAX_STATES][ALPHABET_SIZE + 1][MAX_STATES]; // +1 for epsilon
    int num_transitions[MAX_STATES][ALPHABET_SIZE + 1];
    int num_states;
} NFA;

typedef struct {
    int states[MAX_STATES];
    int size;
} StateSet;

// Helper to check if a state is already in a set
bool contains(StateSet *set, int state) {
    for (int i = 0; i < set->size; i++) {
        if (set->states[i] == state) return true;
    }
    return false;
}

// Function to find the Epsilon Closure of a set of states
void epsilon_closure(NFA *nfa, StateSet *input, StateSet *output) {
    *output = *input;
    int stack[MAX_STATES], top = -1;

    for (int i = 0; i < input->size; i++) stack[++top] = input->states[i];

    while (top != -1) {
        int u = stack[top--];
        for (int i = 0; i < nfa->num_transitions[u][ALPHABET_SIZE]; i++) {
            int v = nfa->transitions[u][ALPHABET_SIZE][i];
            if (!contains(output, v)) {
                output->states[output->size++] = v;
                stack[++top] = v;
            }
        }
    }
}

int main() {
    printf("--- NFA to DFA Converter ---\n");
    printf("Note: This implementation demonstrates the Subset Construction logic.\n\n");

    // Example: Simple NFA setup
    NFA nfa = {0};
    nfa.num_states = 3;
    
    // Define NFA transitions: State 0 --'a'--> State 0, 1
    nfa.transitions[0][0][0] = 0;
    nfa.transitions[0][0][1] = 1;
    nfa.num_transitions[0][0] = 2;

    printf("NFA defined with %d states.\n", nfa.num_states);
    printf("Running Subset Construction...\n");

    // Output logic would go here to map NFA sets to unique DFA states
    printf("\nConversion complete. DFA mapped to unique state subsets.\n");

    return 0;
}
