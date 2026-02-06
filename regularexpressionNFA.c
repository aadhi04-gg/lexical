#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int state = 0;

/* NFA State Structure */
typedef struct nfa {
    int start;
    int end;
} NFA;

/* Stack for NFA */
NFA stack[100];
int top = -1;

/* Push NFA */
void push(NFA n) {
    stack[++top] = n;
}

/* Pop NFA */
NFA pop() {
    return stack[top--];
}

/* Create basic NFA */
NFA create_nfa(char symbol) {
    NFA n;
    n.start = state++;
    n.end = state++;
    printf("%d --%c--> %d\n", n.start, symbol, n.end);
    return n;
}

/* Union */
NFA union_nfa(NFA n1, NFA n2) {
    NFA n;
    n.start = state++;
    n.end = state++;

    printf("%d --ε--> %d\n", n.start, n1.start);
    printf("%d --ε--> %d\n", n.start, n2.start);
    printf("%d --ε--> %d\n", n1.end, n.end);
    printf("%d --ε--> %d\n", n2.end, n.end);

    return n;
}

/* Concatenation */
NFA concat_nfa(NFA n1, NFA n2) {
    printf("%d --ε--> %d\n", n1.end, n2.start);
    NFA n;
    n.start = n1.start;
    n.end = n2.end;
    return n;
}

/* Kleene Star */
NFA star_nfa(NFA n1) {
    NFA n;
    n.start = state++;
    n.end = state++;

    printf("%d --ε--> %d\n", n.start, n1.start);
    printf("%d --ε--> %d\n", n.start, n.end);
    printf("%d --ε--> %d\n", n1.end, n1.start);
    printf("%d --ε--> %d\n", n1.end, n.end);

    return n;
}

int main() {
    char postfix[50];
    printf("Enter postfix regular expression: ");
    scanf("%s", postfix);

    for (int i = 0; i < strlen(postfix); i++) {
        char c = postfix[i];

        if (c >= 'a' && c <= 'z') {
            NFA n = create_nfa(c);
            push(n);
        }
        else if (c == '|') {
            NFA n2 = pop();
            NFA n1 = pop();
            push(union_nfa(n1, n2));
        }
        else if (c == '.') {
            NFA n2 = pop();
            NFA n1 = pop();
            push(concat_nfa(n1, n2));
        }
        else if (c == '*') {
            NFA n1 = pop();
            push(star_nfa(n1));
        }
    }

    NFA result = pop();
    printf("\nStart State: %d\n", result.start);
    printf("End State: %d\n", result.end);

    return 0;
}
