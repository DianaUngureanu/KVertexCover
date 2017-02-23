#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *input, *output;

    int edges[200][200];
    int nv, ne, k, i, j, l;

    input = fopen( "test.in", "r");
    output = fopen("test.out", "w");

    /* Citesc numarul de varfuri din graf, numarul de laturi
    si numarul k pentru acoperire */
    fscanf(input, "%d %d %d", &nv, &ne, &k);

    /* Citesc toate muchiile din graf */
    for(i = 1; i <= ne; i++)
        fscanf(input, "%d %d", &edges[i][0], &edges[i][1]);

    /* Codific urmatoarele lucruri: fiecare nod i, cu i de la
    1 la k sa apara cel putin o data si sa fie unic */
    for(i = 1; i <= k; i++) {

        fprintf(output, "(");

        for(j = 1; j <= nv; j++) {
            if(j == nv)
                fprintf(output, "x%d)", (j-1) * 3 + i);
            else
                fprintf(output, "x%dV", (j-1) * 3 + i);
        }

        fprintf(output, "^");

        for(j = 1; j <= nv; j++) {
            for(l = 1; l <= nv; l++) {
                if(j != l) {
                    fprintf(output, "(~x%dV", (j-1) * 3 + i);
                    fprintf(output, "~x%d)^", (l-1) * 3 + i);
                }
            }
        }
    }

    /* verific pentru fiecare muchie ca macar unul din cele doua
    noduri sa faca parte din acoperire */
    for(i = 1; i <= nv; i++) {
        for(j = 1; j <= k; j++) {
            for(l = 1; l <= k; l++) {
                if(j != l) {

                    fprintf(output, "(~x%dV", (i-1) * 3 + j);
                    fprintf(output, "~x%d)^", (i-1) * 3 + l);
                }
            }
        }
    }



    for(i = 1; i <= ne; i++) {

        fprintf(output,"(");

        for(j = 1; j <= k; j++) {

            fprintf(output, "x%dV", (edges[i][0]-1) * 3 + j);

            if(j == k)
                fprintf(output, "x%d", (edges[i][1]-1) * 3 + j);
            else
                fprintf(output, "x%dV", (edges[i][1]-1) * 3 + j);
        }

        if(i == ne)
            fprintf(output, ")");
        else
            fprintf(output, ")^");
    }

    return 0;
}
