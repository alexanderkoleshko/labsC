#include <stdio.h>
 
int main ()
{
    printf("Input example of your word:\n");
    char pattern[10];
    scanf("%s", pattern);
    char words[10][10] = {
        "house",
        "car",
        "cat",
        "rat",
        "rabbit",
        "cucamber",
        "object",
        "polygon",
        "fine"};
    printf("Similar:\n");
    int i, k;
    int equal;
    for (i = 0; i < 10; i++)
    {
        equal = 1;
        for (k = 0; pattern[k] && words[i][k] && equal; k++)
        {
            if (pattern[k] == '_')
            {
                continue;
            }
            if (pattern[k] != words[i][k])
            {
                equal = 0;
            }
        }
        if (pattern[k] || words[i][k])
        {
            equal = 0;
        }
        if (equal > 0)
        {
            printf("%s\n", words[i]);
        }
    }
 
    return 0;
}
