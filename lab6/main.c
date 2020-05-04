#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAXWORD 100

struct tnode { // узел
    char *word;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *p, char *w) { // добавление поддеревьев
    if(p == NULL) { // если дерево пусто, то инициализируем его
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->left = p->right = NULL; // выделяем память для поддеревьев
    }
    else if(strcmp(w, p->word) < 0) // если строка меньше родителя, то мы добавляем в левое поддерево
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w); // // если строка больше родителя, то мы добавляем в правое поддерево
    return p;
}

void freemem(struct tnode *tree) { // функция удаления поддерева
    if(tree!=NULL) {
        freemem(tree->left);
        freemem(tree->right);
        free(tree->word);
        free(tree);
    }
}

bool checkPal(char *word){ // проверка, является ли строка палиндромом
    int len = strlen(word);
    for(int i = 0; i < len/2; ++i)
    {
        if(word[i] != word[len-i-1])
        {
            return false;
        }
    }
    return true;
}

void treeprint(struct tnode* root){ // inorder обход дерева, другими словами центрированный
    if(root == NULL) return;
    treeprint(root->left);
    if (checkPal(root->word)){
        printf("%s", root->word);
        printf("\n");
    }
    treeprint(root->right);
}

int main(int argc, const char * argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;
    printf("Inpur your words:\n");
    do {
        scanf("%s",word);
        root = addtree(root, word);
    } while(strcmp(word, "end")); // условие выхода – ввод 'end'
    treeprint(root);
    freemem(root);
    getchar();
    return 0;
}