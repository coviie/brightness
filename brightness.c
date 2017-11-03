/*
 *     brightness.c
 *     by Jia Wen Goh (jgoh01) and Rifat Ralfi Salhon (rsalho01), 09/06/2017
 *
 *     Prints the average brightness of a given .pgm image.
 */ 


#include <stdio.h>
#include <pnmrdr.h>
#include <stdlib.h>
typedef Pnmrdr_T T;

void processFile        (FILE* input);
void invalidFileMsg     ();

/*
 * [Name]:              main
 * [Purpose]:           main call, check arguments and set filename accordingly
 * [Parameters]:        1 int (argc), 1 char* (argv[])
 * [Returns]:           0 for success
 */
int main(int argc, char *argv[])
{
        FILE *fp;

        if (argc == 2) {
                fp = fopen(argv[1], "r");
        } else if (argc == 1) {
                fp = stdin;
        } else {
                fprintf(stderr, "Wrong format. Use: ./brightness <filename>\n");
                exit(EXIT_FAILURE);
        }

        processFile(fp);
        return 0;
}

/*
 * [Name]:              processFile
 * [Purpose]:           Determines brightness from given pgm image.
 * [Parameters]:        1 FILE* (examined pgm image)
 * [Returns]:           void
 */
void processFile(FILE *input) 
{
        if (input == NULL)
                invalidFileMsg();

        T pixelData = Pnmrdr_new(input);
        T *datap = &pixelData;

        Pnmrdr_mapdata image = Pnmrdr_data(pixelData);

        if ((image.width == 0) || (image.height == 0))
                invalidFileMsg();

        double totalBrightness = 0.0;
        for (unsigned i = 0; i < image.width * image.height ; i++)
                totalBrightness += Pnmrdr_get(pixelData);

        totalBrightness /= image.denominator * (image.width * image.height);

        printf("%0.3f\n", totalBrightness);

        Pnmrdr_free(datap);
        fclose(input);
        exit(EXIT_SUCCESS);
}

/*
 * [Name]:              invalidFileMsg
 * [Purpose]:           Prints the error message if there's any file errors
 * [Parameters]:        -
 * [Returns]:           -
 */
void invalidFileMsg()
{
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);     
}