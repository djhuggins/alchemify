/******************************************************************************
 *  This program is free software; you can redistribute it and/or modify      *
 *  it under the terms of the GNU General Public License, version 2, as       *
 *  published by the Free Software Foundation.                                *
 *                                                                            *
 *  This program is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with this program; if not, write to the Free Software               *
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA *
 ******************************************************************************/

#include "libdoublealchemify.h"

char    cmd_line(int n, char **arg);
void    usage(void);

/************************************************************************************/
int main(int argc, char **argv) {

    char	col;
    FILE	*in, *out;	
    int	nFinalOne, nInitialOne, nFinalTwo, nInitialTwo, natoms;
    int	finalone[MAX_GROUP_SIZE], initialone[MAX_GROUP_SIZE], finaltwo[MAX_GROUP_SIZE], initialtwo[MAX_GROUP_SIZE];	


    if ((col=cmd_line(argc, argv))=='e') {
        usage();
    }

    natoms = readPDB(argv[3], col, initialone, finalone, initialtwo, finaltwo, &nInitialOne, &nFinalOne, &nInitialTwo, &nFinalTwo);
    if (natoms < 0) DIE("problem reading FEP file")

    printf("\nFEPfile : %i atoms found, %i initial, %i final and %i initial, %i final.\n\n", natoms, nInitialOne, nFinalOne, nInitialTwo, nFinalTwo);



    if (!(nFinalOne || nInitialOne)) DIE("no atoms involved in transformation 1")

    if (!(nFinalTwo || nInitialTwo)) DIE("no atoms involved in transformation 2")

    if (!(nFinalOne && nInitialOne && nFinalTwo &&nInitialTwo)) {
        printf("Either no atoms appearing, or no atoms disappearing.\n"
          "PSF file requires no modification.\n");
        exit(EXIT_SUCCESS);
    }

    in = fopen(argv[1], "r");
    if (!in) DIE("cannot open input file")
    
    out = fopen(argv[2], "w");
    if (!out) DIE("cannot open output file")
    
    if (process(in, out, natoms, initialone, finalone, initialtwo, finaltwo, nInitialOne, nFinalOne, nInitialTwo, nFinalTwo)) {
        fclose(in);
        fclose(out);
        DIE("while processing PSF file")
    }

    fclose(in);
    fclose(out);
    exit(EXIT_SUCCESS);
}


void	usage(void) {
	printf("\ndoublealchemify %u.%u\nhttps://github.com/djhuggins/doublealchemify\n\n",
		MAJOR_VERSION, MINOR_VERSION);
	printf("Usage : doublealchemify input.psf output.psf FEPfile.fep [FEP_column]\n"
		"(default column is B)\n\n");
	printf("Distributed under the terms of the GNU General Public License, version 2\n"
		"(see LICENSE or http:/*www.gnu.org/copyleft/gpl.html)\n\n");
	exit(EXIT_SUCCESS);
}


char	cmd_line(int n, char **arg) {

	if ((n < 4) || (n > 5)) return 'e';	/* error */
	if (n==4) return 'B';	/* default */
	return arg[4][0];	/* first character of fourth parameter */
}

