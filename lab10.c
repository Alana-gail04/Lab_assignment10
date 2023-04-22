#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26 

struct Trie{
    struct Trie *children[ALPHABET_SIZE];
    int count;
};

void insert(struct Trie **ppTrie, char *word){
    struct Trie *curr = *ppTrie;
    if (curr == NULL){
        curr = (struct Trie *)malloc(sizeof(struct Trie));
        curr->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++){
            curr->children[i] = NULL;
        }
        *ppTrie = curr;
    }
    for (int i = 0; i < strlen(word); i++){
        int index = word[i] - 'a';
        if (curr->children[index] == NULL){
            curr->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            curr->children[index]->count = 0;
            for (int j = 0; j < ALPHABET_SIZE; j++){
                curr->children[index]->children[j] = NULL;
            }
        }
        curr = curr->children[index];
    }
    curr->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word){
    if (pTrie == NULL){
        return 0;
    }
    struct Trie *curr = pTrie;
    for(int i = 0; i < strlen(word); i++){
        int index = word[i] - 'a';
        if(curr->children[index] == NULL){
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie){
    if (pTrie == NULL){
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++){
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void){
    struct Trie *trie = NULL;

    int numWords; 
    scanf("%d", &numWords);

    char word[100];
    for (int i = 0; i < numWords; i++){
        scanf("%s", word);
        insert(&trie, word);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
        for (int i = 0; i < 5; i++){
            printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
        }

    trie = deallocateTrie(trie);
    if (trie != NULL){
        printf("There is an error in this program\n");
    }

    return 0;
}