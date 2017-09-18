# doublealchemify

An X-PLOR PSF post-processor for alchemical free energy calculations in [NAMD](http://www.ks.uiuc.edu/Research/namd)  

Written by David Huggins

Adapted from alchemify written by Jérôme Hénin  

* * *

## Updates:

Version 1.0 (September 2017) 

* * *

## Motivation

NAMD features an [implementation](http://www.ks.uiuc.edu/Research/namd/2.12/ug/node61.html) of alchemical FEP that uses the dual topology approach. Dual topology requires that the initial and final groups do not interact. To prevent such interactions, the PSF file describing the system should:  

*   contain no bonded parameter coupling the initial and final groups;
*   contain exclusion lists ensuring that no nonbonded interactions between these groups exist.

Psfgen is not designed to handle nonbonded exclusion lists, and it is not straightforward to use it for removing unwanted bonded terms. doublealchemify is a small program that takes care of these two tasks with minimal effort from the user.  
For simulating single amino-acid mutations in proteins, the setup can be handled automatically by the [VMD](http://www.ks.uiuc.edu/Research/vmd) plugin [Mutator](http://www.ks.uiuc.edu/Research/vmd/plugins/mutator).

## Syntax

`doublealchemify <input PSF> <output PSF> <FEPfile> [FEP column]`

## How to use it  

*   Generate an X-PLOR PSF file containing the dual topology, using either psfgen, or CHARMM, or any suitable tool. This PSF may contain auto-generated angles and dihedrals. The unavoidable part of the work is to define the dual topology more or less by hand, unless the alchemical transformation affects only whole molecules and not parts of them.  

*   Create an FEPfile, i.e. a PDB file for your system with a column (usually the B column) containing '1' and '2' flags for atoms that appear and '-1' and '-2' flags for atoms that disappear. The two pairs of molecules 1/-1 and 2/-2 will both be decoupled from one another.

*   Run `doublealchemify in.psf out.psf FEPfile`.

* * *

## License

doublealchemify is Free Software. It is distributed under the [GNU General Public License, version 2](http://www.gnu.org/copyleft/gpl.html).
