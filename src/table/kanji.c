/* kanji.c
 *
 * The kanji begin at 0x889f.  However, they are not contiguous.
 * This table marks which characters are actually usable.
 *
 * +n means n contiguous usable characters.
 * -n means n contiguous unusable nothings.
 */

#include "table/kanji.h"

const int k_contiguous_kanji[] = {
	/* 889f */  1,
	/* 88a0 */ -3,  3, -5,  2, -3,
	/* 88b0 */ -3,  3,-10,
	/* 88c0 */  1, -2,  3, -2,  6, -1, 1,
	/* 88d0 */  1, -2,  5, -1,  4, -2, 1,
	/* 88e0 */  5, -1,  2, -2,  3, -3,
	/* 88f0 */  1, -2,  1, -1,  2, -1, 2, -6,

	/* 89__ */-16,-16,-16,-16,
	/* 8940 */  3, -2,  2, -1,  3, -5,
	/* 8950 */ -1,  3, -8,  4,
	/* 8960 */ -3,  1, -1,  2, -1,  3, -5,
	/* 8970 */  5, -2,  1, -2,  1, -3,  1, -1,
	/* 8980 */  1, -2,  3, -1,  4, -1,  1, -1,  2,
	/* 8990 */ -3,  1, -2,  1, -1,  1, -1,  6,
	/* 89a0 */ -1,  1, -1,  2, -4,  1, -4,  2,
	/* 89b0 */  1, -2, 11, -1,  1,
	/* 89c0 */ -1,  2, -1,  4, -1,  2, -1,  3, -1,
	/* 89d0 */  1, -1,  4, -1,  3, -1,  2, -2,  1,
	/* 89e0 */ -4,  3, -4,  1, -2,  2,
	/* 89f0 */  4, -1,  3, -1,  2, -1,  1, -3,

	/* 8a__ */-16,-16,-16,-16,
	/* 8a40 */ -2,  6, -2,  3, -2,  1,
	/* 8a50 */  3, -1,  1, -3,  4, -4,
	/* 8a60 */ -5,  1, -1,  1, -1,  1, -1,  5,
	/* 8a70 */  1, -1,  2, -1,  3, -1,  2, -1,  1, -3,
	/* 8a80 */ -4,  2, -1,  2, -1,  2, -2,  1, -1,
	/* 8a90 */  1, -3,  2, -2,  1, -1,  1, -5,
	/* 8aa0 */  1, -2,  1, -2,  1, -1,  4, -2,  2,
	/* 8ab0 */ -1,  1, -2,  2, -1,  1, -5,  3,
	/* 8ac0 */ -2,  2, -1,  5, -2,  2, -1,  1,
	/* 8ad0 */ -1,  4, -1,  2, -1,  1, -1,  3, -2,
	/* 8ae0 */ -1,  2, -3,  4, -1,  5,
	/* 8af0 */  5, -1,  5, -1,  1, -3,

	/* 8b__ */-16,-16,-16,-16,
	/* 8b40 */  2, -1,  1, -2,  2, -3,  4, -1,
	/* 8b50 */  1, -1,  5, -1,  3, -1,  3, -1,
	/* 8b60 */  1, -2,  1, -3,  1, -4,  1, -3,
	/* 8b70 */  2, -1, 12, -1,
	/* 8b80 */  2, -1,  1, -1,  2, -2,  1, -1,  2, -1,  2,
	/* 8b90 */  4, -1,  3, -1,  1, -1,  1, -3,  1,
	/* 8ba0 */ -3,  4, -2,  1, -1,  1, -1,  1, -1,  1,
	/* 8bb0 */  1, -1,  6, -1,  3, -1,  3,
	/* 8bc0 */ -1,  3, -2,  5, -3,  2,
	/* 8bd0 */ -6,  1, -1,  2, -3,  1, -1,  1,
	/* 8be0 */  1, -1,  1, -2,  2, -2,  2, -1,  1, -1,  2,
	/* 8bf0 */  1, -1,  3, -1,  3, -3,  1, -3,
	
	/* 8c__ */-16,-16,-16,-16,
	/* 8c40 */  2, -1,  1, -6,  1, -2,  2, -1,
	/* 8c50 */  3, -4,  5, -2,  2,
	/* 8c60 */  3, -2,  5, -1,  1, -1,  3,
	/* 8c70 */  3, -3,  1, -1,  2, -2,  2, -2,
	/* 8c80 */  1, -1, 11, -1,  2,
	/* 8c90 */  1, -1,  5, -1,  3, -1,  2, -1,  1,
	/* 8ca0 */  1, -1,  3, -3,  2, -1,  1, -1,  3,
	/* 8cb0 */ -1,  1, -1,  9, -2,  1, -1,
	/* 8cc0 */  1, -1,  4, -1,  3, -2,  4,
	/* 8cd0 */ -2,  1, -2,  3, -1,  5, -1,  1,
	/* 8ce0 */ -3,  3, -4,  3, -3,
	/* 8cf0 */  1, -2,  1, -1,  8, -3,
	
	/* 8d__ */-16,-16,-16,-16,
	/* 8d40 */ -2,  1, -1,  2, -2,  2, -1,  2, -1,  1, -1,
	/* 8d50 */ -1,  6, -1,  1, -1,  1, -1,  1, -3,
	/* 8d60 */  1, -1,  4, -1,  1, -4,  1, -3,
	/* 8d70 */ -1,  3, -3,  1, -2,  1, -1,  1, -1,  1, -1,
	/* 8d80 */  3, -1,  4, -3,  2, -2,  1,
	/* 8d90 */  4, -1,  2, -1,  1, -2,  2, -1,  1, -1,
	/* 8da0 */  3, -2,  2, -3,  1, -1,  1, -3,
	/* 8db0 */  1, -2,  2, -1,  3, -2,  1, -1,  1, -2,
	/* 8dc0 */  1, -2,  3, -1,  2, -1,  3, -1,  2,
	/* 8dd0 */  1, -2,  3, -1,  9,
	/* 8de0 */ -1,  2, -4,  1, -4,  2, -2,
	/* 8df0 */  1, -3,  3, -9,
	
	/* 8e__ */-16,-16,-16,-16,
	/* 8e40 */  2, -1,  3, -1,  1, -3,  1, -3,  1,
	/* 8e50 */ -1,  2, -2,  1, -3,  2, -2,  3,
	/* 8e60 */ -1,  4, -1,  5, -1,  4,
	/* 8e70 */  9, -2,  4, -1,
	/* 8e80 */  3, -1,  5, -1,  5, -1,
	/* 8e90 */ -1,  1, -1,  5, -1,  3, -1,  3,
	/* 8ea0 */ -1,  1, -3,  2, -1,  2, -1,  1, -1,  3,
	/* 8eb0 */ -2,  1, -2,  6, -1,  4,
	/* 8ec0 */  1, -9,  6,
	/* 8ed0 */  1, -1,  3, -1,  3, -1,  1, -1,  1, -2,  1,
	/* 8ee0 */ -1, 13, -1,  1,
	/* 8ef0 */  2, -1,  2, -1,  2, -1,  1, -1,  2, -3,

	/* 8f__ */-16,-16,-16,-16,
	/* 8f40 */  2, -1,  1, -1,  1, -3,  1, -1,  2, -3,
	/* 8f50 */  3, -1,  1, -1,  2, -2,  4, -1,  1,
	/* 8f60 */  1, -1,  4, -2,  1, -1,  2, -2,  2,
	/* 8f70 */  2, -2,  2,-10,
	/* 8f80 */  1, -1,  3, -2,  5, -2,  2,
	/* 8f90 */ -1,  1, -3,  1, -1,  3, -2,  2, -1,  1,
	/* 8fa0 */  1, -1,  1, -1,  2, -5,  4, -1,
	/* 8fb0 */  1, -2,  1, -1,  2, -1,  1, -2,  1, -4,
	/* 8fc0 */ -1,  2, -1,  5, -3,  3, -1,
	/* 8fd0 */  1, -4,  1, -2,  1, -1,  3, -3,
	/* 8fe0 */  5, -1,  5, -1,  3, -1,
	/* 8ff0 */  1, -1,  2, -1,  3, -1,  1, -2,  1, -3,

	/* 90__ */-16,-16,-16,-16,
	/* 9040 */ -1,  1, -2,  5, -2,  4, -1,
	/* 9050 */ -1,  6, -1,  1, -1,  3, -1,  2,
	/* 9060 */ -1,  1, -2,  2, -1,  6, -1,  1, -1,
	/* 9070 */ -1,  1, -1,  1, -2,  2, -1,  1, -1,  1, -1,  1, -2,
	/* 9080 */ -1,  2, -1,  6, -1,  1, -3,  1,
	/* 9090 */ -4,  1, -2,  1, -8,
	/* 90a0 */ -1,  2, -3,  3, -2,  5,
	/* 90b0 */  2, -1, 13,
	/* 90c0 */ -2,  2, -1,  1, -1,  3, -2,  4,
	/* 90d0 */ -1,  1, -1,  3, -2,  1, -1,  1, -1,  2, -1,  1,
	/* 90e0 */  4, -2,  9, -1,
	/* 90f0 */ -2,  6, -1,  1, -2,  1, -3,

	/* 91__ */-16,-16,-16,-16,
	/* 9140 */  1, -3,  1, -1,  1, -1,  2, -1,  1, -1,  3,
	/* 9150 */  1, -1,  2, -4,  1, -5,  2,
	/* 9160 */ -1,  3, -1,  6, -2,  3,
	/* 9170 */ -1,  4, -2,  1, -2,  4, -2,
	/* 9180 */  5, -2,  2, -1,  2, -1,  1, -1,  1,
	/* 9190 */  1, -1,  7, -2,  5,
	/* 91a0 */ 16,
	/* 91b0 */  2, -2,  7, -1,  3, -1,
	/* 91c0 */ -3,  1, -1,  1, -1,  2, -1,  1, -1,  1, -1,  2,
	/* 91d0 */ -1,  4, -1,  1, -5,  3, -1,
	/* 91e0 */  1, -2,  4, -1,  1, -1,  1, -3,  1, -1,
	/* 91f0 */  1, -1,  2, -1,  1,-10,

	/* 92__ */-16,-16,-16,-16,
	/* 9240 */  3, -1,  2, -4,  1, -2,  2, -1,
	/* 9250 */  2, -1,  3, -1,  1, -1,  4, -2,  1,
	/* 9260 */ -1,  7, -1,  6, -1,
	/* 9270 */  1, -1,  2, -1,  4, -1,  1, -1,  1, -1,  1, -1,
	/* 9280 */ -3,  1, -1, 10, -1,
	/* 9290 */ -3,  1, -5,  3, -1,  1, -2,
	/* 92a0 */  1, -2,  5, -1,  2, -1,  1, -1,  1, -1,
	/* 92b0 */ -1,  2, -1,  2, -1,  3, -2,  1, -1,  2,
	/* 92c0 */  1, -2,  2, -1,  2, -1,  2, -2,  1, -2,
	/* 92d0 */ -2,  1, -4,  1, -4,  1, -1,  1, -1,
	/* 92e0 */  4, -4,  4, -1,  1, -1,  1,
	/* 92f0 */ -1,  2, -1,  1, -1,  2, -1,  2, -5,

	/* 93__ */-16,-16,-16,-16,
	/* 9340 */  1, -1,  1, -1,  2, -1,  1, -1,  3, -3,  1,
	/* 9350 */  1, -2,  7, -2,  2, -1,  1,
	/* 9360 */  2, -2,  3, -1,  2, -4,  2,
	/* 9370 */ -1,  3, -1,  1, -1,  8, -1,
	/* 9380 */  4, -3,  1, -2,  3, -3,
	/* 9390 */  1, -1,  3, -1,  1, -2,  6, -1,
	/* 93a0 */ -1,  2, -1,  4, -1,  2, -1,  4,
	/* 93b0 */  3, -1,  4, -1,  2, -3,  2,
	/* 93c0 */ -1,  1, -3,  3, -3,  1, -1,  1, -2,
	/* 93d0 */ -7,  1, -4,  2, -1,  1,
	/* 93e0 */  1, -1,  3, -2,  1, -1,  2, -1,  1, -1,  2,
	/* 93f0 */  2, -1,  1, -1,  4, -1,  1, -1,  1, -3,

	/* 94__ */-16,-16,-16,-16,
	/* 9440 */ -3,  1, -1,  2, -3,  1, -1,  4,
	/* 9450 */ -2,  2, -5,  5, -2,
	/* 9460 */  1, -2,  1, -3,  2, -1,  2, -2,  1, -1,
	/* 9470 */  5, -2,  1, -1,  3, -4,
	/* 9480 */ -3,  2,-10,  1,
	/* 9490 */ -1,  2, -3,  2, -2,  2, -4,
	/* 94a0 */  1, -6,  2, -1,  2, -1,  1, -1,  1,
	/* 94b0 */  3, -1,  1, -5,  4, -2,
	/* 94c0 */  1, -1,  1, -1,  3, -3,  1, -1,  2, -2,
	/* 94d0 */ -1,  1, -1,  3, -4,  6,
	/* 94e0 */  1, -1,  1, -1,  1, -1,  4, -3,  1, -1,  1,
	/* 94f0 */  3, -2,  3, -4,  1, -3,

	/* 95__ */-16,-16,-16,-16,
	/* 9540 */  1, -2,  1, -3,  1, -3,  1, -4,
	/* 9550 */  1, -2,  1, -1,  1, -1,  3, -1,  3, -2,
	/* 9560 */  3, -6,  1, -2,  3, -1,
	/* 9570 */  2, -1,  2, -1,  2, -2,  1, -1,  1, -1,  1, -1,
	/* 9580 */  7, -2,  3, -4,
	/* 9590 */  2, -2,  2, -1,  1, -2,  1, -1,  4,
	/* 95a0 */  2, -3,  4, -1,  1, -1,  1, -3,
	/* 95b0 */ -1,  2, -2,  6, -2,  1, -1,  1,
	/* 95c0 */  1, -1,  1, -1,  1, -1,  5, -3,  2,
	/* 95d0 */  5, -1,  2, -2,  2, -3,  1,
	/* 95e0 */  1, -1,  1, -2,  3, -1,  2, -4,  1,
	/* 95f0 */  4, -2,  1, -1,  1, -1,  2, -4,

	/* 96__ */-16,-16,-16,-16,
	/* 9640 */  2, -1,  1, -3,  1, -2,  3, -1,  2,
	/* 9650 */ -2,  3, -1, 10,
	/* 9660 */  1, -2,  2, -3,  5, -3,
	/* 9670 */  1, -5,  1, -4,  4, -1,
	/* 9680 */  9, -7,
	/* 9690 */ -4,  1, -1,  1, -1,  1, -3,  4,
	/* 96a0 */ -1,  3, -2,  3, -3,  2, -1,  1,
	/* 96b0 */  4, -1,  1, -3,  7,
	/* 96c0 */  1, -1,  1, -2,  2, -1,  1, -1,  1, -2,  1, -1,  1,
	/* 96d0 */ -1,  2, -1,  2, -1,  4, -2,  1, -1,  1,
	/* 96e0 */ -1,  5, -2,  3, -1,  1, -1,  2,
	/* 96f0 */  5, -6,  2, -3,

	/* 97__ */-16,-16,-16,-16,
	/* 9740 */ -1,  2, -1,  3, -1,  3, -1,  1, -1,  1, -1,
	/* 9750 */ -2,  1, -1,  3, -2,  7,
	/* 9760 */ -1,  1, -1,  3, -1,  3, -2,  3, -1,
	/* 9770 */  1, -3,  1, -1,  1, -1,  1, -1,  2, -1,  2, -1,
	/* 9780 */ -1,  1, -1,  1, -1,  1, -2,  1, -1,  2, -1,  2, -1,
	/* 9790 */  4, -3,  2, -1,  1, -2,  1, -2,
	/* 97a0 */  1, -1,  6, -2,  1, -1,  2, -1,  1,
	/* 97b0 */ -1,  1, -1,  2, -1,  2, -1,  1, -1,  2, -2,  1,
	/* 97c0 */ -1,  4, -2,  1, -2,  1, -1,  4,
	/* 97d0 */ -1,  1, -3,  3, -4,  4,
	/* 97e0 */ -1,  3, -3,  1, -1,  1, -2,  3, -1,
	/* 97f0 */  5, -1,  1, -2,  1, -1,  1, -4,

	/* 98__ */-16,-16,-16,-16,
	/* 9840 */  4, -2,  1, -1,  3, -3,  1, -1,
	/* 9850 */ -1,  6, -2,  3, -2,  2,
	/* 9860 */ -1,  2, -3,  2, -4,  1, -3,
	/* 9870 */ -2,  1,-13,

	0
};