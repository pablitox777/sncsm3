/* main.c
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef ROM_H
#define ROM_H

enum {
	ROM_SIZE = 33554432
};

extern void assign_char_code(int code, unsigned char a, unsigned char b);
extern void patch_char_code_ex(int code, int glyph, unsigned char a, unsigned char b);
extern void patch_char_code(int code, unsigned char a, unsigned char b);

extern void patch_raw(int offset, int code);
extern void patch_2char(int offset, unsigned char a, unsigned char b);
extern void patch_str_ex(unsigned char *buf, int offset, int length, const char *str);
extern void patch_str(int offset, int length, const char *str);
extern void patch_table(int offset, int stride, int num, int length, const char * const * str);
extern void patch_dlg(const char *fn);
extern void patch_dlg_old(int start, int end, void (*patch)(void));

extern void read_rom(const char *fn);
extern void write_rom(const char *fn);

#endif

#ifndef TABLE_EFFECT_H
#define TABLE_EFFECT_H

enum {
	NUM_EFFECTS = 40
};

extern const char * const k_effect_name[NUM_EFFECTS];
extern const char * const k_effect_desc[NUM_EFFECTS];

#endif

#ifndef TABLE_ITEM_H
#define TABLE_ITEM_H

enum {
	NUM_ITEMS = 243
};

extern const char * const k_item_name[NUM_ITEMS];
extern const char * const k_item_desc[NUM_ITEMS];

#endif
#ifndef TABLE_MAGIC_H
#define TABLE_MAGIC_H

enum {
	NUM_MAGICS = 33
};

extern const char * const k_magic_name[NUM_MAGICS];
extern const char * const k_magic_desc[NUM_MAGICS];

#endif
#ifndef TABLE_SPECIAL_H
#define TABLE_SPECIAL_H

enum {
	NUM_SPECIALS = 55
};

extern const char * const k_special_name[NUM_SPECIALS];
extern const char * const k_special_desc[NUM_SPECIALS];

#endif

#ifndef TABLE_WEAPON_H
#define TABLE_WEAPON_H

enum {
	NUM_WEAPONS = 246
};

extern const char * const k_weapon_name[NUM_WEAPONS];
extern const char * const k_weapon_desc[NUM_WEAPONS];

#endif

#ifndef TABLE_BEAST_H
#define TABLE_BEAST_H

enum {
	NUM_BEASTS = 165,
	NUM_BOSSES = 57
};

extern const char * const k_beast_name[NUM_BEASTS];
extern const char * const k_beast_desc[NUM_BEASTS];

extern const char * const k_boss_name[NUM_BOSSES];

#endif


static const char * const k_script[] = {
	"Script/day0_0x017bcb2c_kajishi.txt",
	"Script/day0_0x017bd14c_defeat_ve.txt",
	"Script/day0_0x017be5ec_chiefs_gift.txt",
	"Script/day0_0x017beaac_meet_rival.txt",
	"Script/day0_0x017bf60c_return_home.txt",
	"Script/day0_0x017bfa4c_learn_forge.txt",
	"script/day0_0x017bff6c_craft_weapon.txt",

	"Script/minigame_fishing.txt",
	"Script/teleporter.txt",
	NULL
};
/*--------------------------------------------------------------*/

static bool
should_generate_pair(char a, char b)
{
	assert(('A' <= a && a <= 'Z') || ('a' <= a && a <= 'z'));
	assert('a' <= b && b <= 'z');

	/* Special case for Q and q:
	 * We have already substituted Q -> Qu, q -> qu.
	 */
	if (a == 'Q' || a == 'q')
		return false;

	/* Generate all cases of letter-vowel. */
	if (b == 'a' || b == 'e' || b == 'i' ||
	    b == 'o' || b == 'u' || b == 'y')
		return true;

	/* Blacklist.  A,E,I,O,U,S basically join to everything. */
	if ((a == 'B' && b != 'h' && b != 'l' && b != 'r')
	 || (a == 'C' && b != 'h' && b != 'l' && b != 'r')
	 || (a == 'D' && b != 'r' && b != 'w')
	 || (a == 'F' && b != 'l' && b != 'r')
	 || (a == 'G' && b != 'h' && b != 'l' && b != 'n' && b != 'r')
	 || (a == 'H')
	 || (a == 'J')
	 || (a == 'K' && b != 'h' && b != 'l' && b != 'n' && b != 'r')
	 || (a == 'L' && b != 'l')
	 || (a == 'M' && b != 'n' && b != 'r' && b != 's')
	 || (a == 'N')
	 || (a == 'P' && b != 'h' && b != 'l' && b != 'n' && b != 'r' && b != 's')
	 || (a == 'R' && b != 'h')
	 || (a == 'T' && b != 'h' && b != 'r' && b != 's' && b != 'w')
	 || (a == 'V')
	 || (a == 'W' && b != 'h' && b != 'p' && b != 'r')
	 || (a == 'X')
	 || (a == 'Y')
	 || (a == 'Z'))
		return false;

	return true;
}

static void
create_font_punctuation(int code)
{
	char b;

	for (b = 'A'; b <= 'Z'; b++) {
		patch_char_code(code, ' ', b);
	}

	for (b = 'a'; b <= 'z'; b++) {
		patch_char_code(code, ' ', b);
	}

	for (b = 'a'; b <= 'z'; b++) {
		patch_char_code(code, '-', b);
	}

	/* Apostrophes in contractions. */
	patch_char_code(code, '\'', 'l'); /* I'll */
	patch_char_code(code, '\'', 'r'); /* you're */
	patch_char_code(code, '\'', 's'); /* that's */
	patch_char_code(code, '\'', 't'); /* don't */
	patch_char_code(code, '\'', 'v'); /* you've */

	/* Special: Four-Leaf Twin-Snake fooled; fishermen; */
	patch_char_code(code, '-', 'L');
	patch_char_code(code, '-', 'S');
	patch_char_code(code, 'd', ';');
	patch_char_code(code, 'n', ';');
}

static void
create_font_upper(int code, const char *as)
{
	char b;
	int i;

	for (i = 0; as[i] != '\0'; i++) {
		for (b = 'a'; b <= 'z'; b++) {
			if (should_generate_pair(as[i], b))
				patch_char_code(code, as[i], b);
		}
	}
}

static void
create_font_lower(int code, const char *as)
{
	static const char *bs = " ,.?!\'-abcdefghijklmnopqrstuvwxyz";
	int i, j;

	for (i = 0; as[i] != '\0'; i++) {
		for (j = 0; bs[j] != '\0'; j++) {
			patch_char_code(code, as[i], bs[j]);
		}
	}
}

static void
create_font(void)
{
	int i;

	/* Full-width characters. */
	assign_char_code(0x8140, ' ', ' ');
	assign_char_code(0x8143, ',', ' ');
	assign_char_code(0x8144, '.', ' ');
	assign_char_code(0x8146, ':', ' ');
	assign_char_code(0x8147, ';', ' ');
	assign_char_code(0x8148, '?', ' ');
	assign_char_code(0x8149, '!', ' ');
	assign_char_code(0x815e, '/', ' ');
	assign_char_code(0x8163, '.', '.');
	assign_char_code(0x8166,'\'', ' ');
	assign_char_code(0x8169, '(', ' ');
	assign_char_code(0x816a, ')', ' ');
	assign_char_code(0x817b, '+', ' ');
	assign_char_code(0x817c, '-', ' ');
	assign_char_code(0x8193, '%', '%');
	assign_char_code(0x83c0, '@', 'R'); /* Ritchburn/Rifmonica. */
	assign_char_code(0x83c2, '@', 'r'); /* Ritchie/Rif. */

	for (i = 0; i <= 9; i++) {
		assign_char_code(0x824f + i, '~', '0' + i);
	}

	for (i = 0; i < 26; i++) {
		assign_char_code(0x8260 + i, '~', 'A' + i);
		assign_char_code(0x8281 + i, 'a' + i, '~');
	}

	/* Q is inevitably followed by u. */
	patch_char_code_ex(0x8270, 0x0060, 'Q', 'u');
	patch_char_code_ex(0x8291, 0x007a, 'q', 'u');

	/* "Case-sensitive letter and bigram frequency counts
	 *  from large-scale English corpora"
	 *
	 * Lower case frequency: etaon isrhl dcumf pgywb vkxzj q
	 * Upper case frequency: TSAMC INBRP EDHWL OFYGJ UKVQX Z
	 */

	create_font_punctuation(0x8e00);

	/* Attempt to share second letters:
	 * [Th][th] (e ) -- the , then, etc.
	 * [Wh][wh] (en) -- who , when, etc.
	 */
	patch_char_code(0x8cfc, 'T','h');
	patch_char_code(0x89fc, 't','h');
	patch_char_code(0x90fc, 'W','h');
	patch_char_code(0x93fc, 'w','h');

	/* Attempt to group capitals into the same few slots. */
	create_font_upper(0x8c00, "TSAMCIN");
	create_font_upper(0x9000, "BRPEDHWL");
	create_font_upper(0x9100, "OFYGJUKVXZ");

	create_font_lower(0x8900, "eta");
	create_font_lower(0x8a00, "oni");
	create_font_lower(0x8b00, "srh");
	create_font_lower(0x8d00, "ldc");
	create_font_lower(0x8f00, "umf");
	create_font_lower(0x9200, "pgy");
	create_font_lower(0x9300, "wbv");
	create_font_lower(0x9500, "kxz");
	create_font_lower(0x889f, "j");

	{
		/* A-space, I-space. */
		patch_char_code(0x8c00, 'A', ' ');
		patch_char_code(0x8c00, 'I', ' ');
		patch_char_code(0x8c00, 'I','\'');
		patch_char_code(0x9100, 'O', 'K');

		/* AGL, ATK, DEF, DUR, TEC, HP. */
		patch_char_code(0x8c00, 'A', 'G');
		patch_char_code(0x9100, 'G', 'L');
		patch_char_code(0x9000, 'L', ' ');

		patch_char_code(0x8c00, 'A', 'T');
		patch_char_code(0x8c00, 'T', 'K');
		patch_char_code(0x9100, 'K', ' ');

		patch_char_code(0x9000, 'D', 'E');
		patch_char_code(0x9000, 'E', 'F');
		patch_char_code(0x9100, 'F', ' ');

		patch_char_code(0x9000, 'D', 'U');
		patch_char_code(0x9100, 'U', 'R');
		patch_char_code(0x9000, 'R', ' ');

		patch_char_code(0x8c00, 'T', 'E');
		patch_char_code(0x9000, 'E', 'C');
		patch_char_code(0x8c00, 'C', ' ');

		patch_char_code(0x9000, 'H', 'P');
		patch_char_code(0x9000, 'P', ' ');

		/* n-M, m-M (ItmMat, WpnMat). */
		patch_char_code(0x8a00, 'n', 'M');
		patch_char_code(0x8f00, 'm', 'M');

		/* V.E. */
		patch_char_code(0x9100, 'V', '.');
		patch_char_code(0x9000, 'E', ' ');
		patch_char_code(0x9000, 'E', ',');
		patch_char_code(0x9000, 'E', '!');

		/* Hm.. */
		patch_char_code(0x9000, 'H', 'm');
	}
}

/*--------------------------------------------------------------*/

static void
translate_name_entry_menu(void)
{
    
	// GANA TABLE
    patch_str(0x00bd5324, 10, "AaAeAiAoAu");      	patch_str(0x00bd5324+0xc, 10, "HaHeHiHoHu");   patch_str(0x00bd5324+0x18, 10, "NaNeNiNoNu"); 
	patch_str(0x00bd5324+0x24, 10, "BaBeBiBoBu");   patch_str(0x00bd5324+0x30, 10, "IaIeIiIoIu");  patch_str(0x00bd5324+0x3c, 10, "OaOeOiOoOu"); 
	patch_str(0x00bd5324+0x48, 10, "CaCeCiCoCu");   patch_str(0x00bd5324+0x54, 10, "JaJeJiJoJu");  patch_str(0x00bd5324+0x60, 10, "PaPePiPoPu");
	patch_str(0x00bd5324+0x6c, 10, "DaDeDiDoDu");   patch_str(0x00bd5324+0x78, 10, "KaKeKiKoKu");  patch_str(0x00bd5324+0x84, 10, "RaReRiRoRu"); 
	patch_str(0x00bd5324+0x90, 10, "EaEeEiEoEu");   patch_str(0x00bd5324+0x9c, 10, "LaLeLiLoLu");  patch_str(0x00bd5324+0xa8, 10, "SaSeTiToTu"); 
	patch_str(0x00bd5324+0xb4, 10, "FaFeFiFoFu");   patch_str(0x00bd5324+0xc0, 10, "MaMeMiMoMu");  patch_str(0x00bd5324+0xcc, 10, "YaYeZiZoUu");
	patch_str(0x00bd5324+0xd8, 10, "GaGeGiGoGu"); 

	// KaNa TabLE
    patch_str(0x00bd5420, 10, "aaaeaiaoau");     	patch_str(0x00bd5420+0xc, 10, "hahehihohu");   patch_str(0x00bd5420+0x18, 10, "naneninonu"); 
	patch_str(0x00bd5420+0x24, 10, "babebibobu");   patch_str(0x00bd5420+0x30, 10, "iaieiiioiu");  patch_str(0x00bd5420+0x3c, 10, "oaoeoiooou"); 
	patch_str(0x00bd5420+0x48, 10, "cacecicocu");   patch_str(0x00bd5420+0x54, 10, "jajejijoju");  patch_str(0x00bd5420+0x60, 10, "papepipopu");
	patch_str(0x00bd5420+0x6c, 10, "dadedidodu");   patch_str(0x00bd5420+0x78, 10, "kakekikoku");  patch_str(0x00bd5420+0x84, 10, "rareriroru"); 
	patch_str(0x00bd5420+0x90, 10, "eaeeeieoeu");   patch_str(0x00bd5420+0x9c, 10, "lalelilolu");  patch_str(0x00bd5420+0xa8, 10, "sasetitotu"); 
	patch_str(0x00bd5420+0xb4, 10, "fafefifofu");   patch_str(0x00bd5420+0xc0, 10, "mamemimomu");  patch_str(0x00bd5420+0xcc, 10, "yayezizouu");
	patch_str(0x00bd5420+0xd8, 10, "gagegigogu"); 	 
	 
	//EN Table 551c 
/*	patch_str(0x00bd5420, 10, "aaaeaiaoau");     	patch_str(0x00bd5420+0xc, 10, "hahehihohu");   patch_str(0x00bd5420+0x18, 10, "naneninonu"); 
	patch_str(0x00bd5420+0x24, 10, "babebibobu");   patch_str(0x00bd5420+0x30, 10, "iaieiiioiu");  patch_str(0x00bd5420+0x3c, 10, "oaoeoiooou"); 
	patch_str(0x00bd5420+0x48, 10, "cacecicocu");   patch_str(0x00bd5420+0x54, 10, "jajejijoju");  patch_str(0x00bd5420+0x60, 10, "papepipopu");
	patch_str(0x00bd5420+0x6c, 10, "dadedidodu");   patch_str(0x00bd5420+0x78, 10, "kakekikoku");  patch_str(0x00bd5420+0x84, 10, "rareriroru"); 
	patch_str(0x00bd5420+0x90, 10, "eaeeeieoeu");   patch_str(0x00bd5420+0x9c, 10, "lalelilolu");  patch_str(0x00bd5420+0xa8, 10, "sasetitotu"); 
	patch_str(0x00bd5420+0xb4, 10, "fafefifofu");   patch_str(0x00bd5420+0xc0, 10, "mamemimomu");  patch_str(0x00bd5420+0xcc, 10, "yayezizouu");
	patch_str(0x00bd5420+0xd8, 10, "gagegigogu"); */

	
    /* Default Names. */
	patch_str(0x00bd5680, 22, "Is it correct?");
	patch_str(0x00bd5696, 8, " Yes");
	patch_str(0x00bd569e, 4, "No");
	patch_str(0x00bd56c0, 32, "Enter the hero's nickname");
	patch_str(0x00bd56e4, 24, "Enter the hero's name");
    patch_str(0x00bd5708, 22, "Enter partner's name"); 
    patch_str(0x00bd5730, 6, "Name");
    patch_str(0x00bd5736, 6, "Nick");
	patch_str(0x00bd5744, 12, "~Ritchburn");
	patch_str(0x00bd5752, 12, "~Rifmonica");
	patch_str(0x00bd575e, 10, "Run~-dor");
	patch_str(0x00bd5768,  8, "Enzi");
	patch_str(0x00bd5770, 12, "Killfith");
	patch_str(0x00bd577c, 12, "Rufeel");
	patch_str(0x00bd57a0, 10, "~Ritchie");
	patch_str(0x00bd57aa,  6, "~Rif");

	/* Hiragana table. */
	patch_2char(0x00bd5408, 'K', 'a'); patch_2char(0x00bd540a, 'n', 'a');
	patch_2char(0x00bd540e, '~', 'E'); patch_2char(0x00bd5410, '~', 'N');
	patch_2char(0x00bd5414, '~', 'D'); patch_2char(0x00bd5416, 'e', 'l');
	patch_2char(0x00bd541a, '~', 'O'); patch_2char(0x00bd541c, '~', 'K');

	/* Katakana table. */
	patch_2char(0x00bd5504, 'G', 'a'); patch_2char(0x00bd5506, 'n', 'a');
	patch_2char(0x00bd550a, '~', 'E'); patch_2char(0x00bd550c, '~', 'N');
	patch_2char(0x00bd5510, '~', 'D'); patch_2char(0x00bd5512, 'e', 'l');
	patch_2char(0x00bd5516, '~', 'O'); patch_2char(0x00bd5518, '~', 'K');

	/* English table. */
	patch_2char(0x00bd5600, 'G', 'a'); patch_2char(0x00bd5602, 'n', 'a');
	patch_2char(0x00bd5606, 'K', 'a'); patch_2char(0x00bd5608, 'n', 'a');
	patch_2char(0x00bd560c, '~', 'D'); patch_2char(0x00bd560e, 'e', 'l');
	patch_2char(0x00bd5612, '~', 'O'); patch_2char(0x00bd5614, '~', 'K');
}

static int
insert_chain(char cadena[],int start,int stride,int max,int next){
	
	int end,i;	
	//printf("address:%x\n",start);
	//getchar();
	for(i=max;i>=1;i--){	
		patch_str(start,stride,cadena);   /* equipment */	
		start+=next;
		//printf("address:%x\n",start);
		//getchar();
   }	
   
   end=start;			
   return end;	
}

static void
translate_main_menu(void)
{   
	/* First menu. */
	patch_str(0x000bacf0,  8, "Equip"  );   /* equipment */
	patch_str(0x000bace4, 12, "Support");
	patch_str(0x000bacd8, 12, "Item  " );
	patch_str(0x000bacd0,  8, "Magic"  );
	patch_str(0x000bacc8,  8, "Weapon" );
	patch_str(0x000bacbc, 12, "Status" );

	/* Second menu. */
	patch_str(0x000bad38,  8, "Quest"  );   /* quest items */
	patch_str(0x000bad2c, 12, "Rank"   );   /* craft rank */
	patch_str(0x000bad24,  8, "Tech"   );   /* techniques */
	patch_str(0x000bad1c,  8, "Spec"   );   /* special attack */
	patch_str(0x000bad10, 12, "Effect" );
	patch_str(0x000bad04, 12, "Beastiary" );   /* bestiary */
	patch_str(0x000bacf8, 12, "Options" );   /* options */

	/* Rank/Techniques submenu. */
	patch_str(0x000bad78,  8, "Sword"  );
	patch_str(0x000bad70,  8, "Axe"    );
	patch_str(0x000bad68,  8, "Spear"  );
	patch_str(0x000bad5c,  6, "Fist"   );
	patch_str(0x000bad54,  8, "Drill"  );
	patch_str(0x000bad4c,  8, "Bow"    );


	/* Item types. */
	patch_str(0x000baeb4,  8, "Recovr"                    );    /* recover */
	patch_str(0x000baeac,  8, "ItmMat"					  );    /* item material */
	patch_str(0x000baea4,  8, "Spec"					  );      /* special */
	patch_str(0x000bae9c,  8, "WpnMat"					  );    /* weapon material */
	
	/* messages */
	patch_str(0x000badcc,  22, "You have no weapons"	  );
	patch_str(0x000bade4,  18, "Can't use magic"	      );
	patch_str(0x000badfc,  26, "You don't have any items" );
	patch_str(0x000bae30,  20, "No weapon effects");
    patch_str(0x000bae4c,  24, "No special moves");
	patch_str(0x000bae64,  18, "No quest items");
	patch_str(0x000bae7d,  24, "No techniques learned");     
	patch_str(0x000bae94,  10, "Upgrade");     /* imbue material */
	/* Note: 'equipment' comes from the string at 0x000bacf0. */

	/* Forge. */
	patch_str(0x000baf1c,  8, "Create");
	patch_str(0x000baf00,  8, "Strgth");    /* strengthen */

	patch_str(0x000baef8,  8, "Disass");    /* disassemble */
	patch_str(0x000baeec,  8, "Disass+");/* disassemble plus */
    patch_str(0x000baee4,  8, "Repair");
    
   	patch_str(0x000baf14,  8, "Remove");/* remove */
   	//patch_str(0x000baf08,  8, "Remove+");/* remove PLUS*/
    patch_str(0x000baee4,  8, "Repair");
   
	/* Spell types. */
	patch_str(0x000baf34,  8, "Any");       /* any recover */
	patch_str(0x000baf24,  8, "Field");     /* field support */
	patch_str(0x000baf44,  8, "Aux");       /* battle/field support */
	patch_str(0x000baf2c,  8, "Battle");    /* battle attack/support */
	patch_str(0x000baf3c,  8, "Attack");    /* battle attack */
	patch_str(0x000baf4c,  8, "Attack");    /* battle attack */

	/* Equip self/guardian beast. */
	patch_str(0x000baf5c,  8, "Equip");     /* equipment */
	patch_str(0x000baf64,  8, "Magic");
	/* Note: 'item' comes from the string at 0x000bacd8. */
	patch_str(0x000baf54,  8, "Remove");    /* unequip/remove */
   
    patch_str(0x00b89fe8, 8, "Guard");
    
	/* Shop menu. */
	patch_str(0x000baf7c,  8, "Buy");
	patch_str(0x000baf74,  8, "Sell");
	patch_str(0x000baf6c,  8, "Create");
	patch_str(0x000baf84,  16, "Buy how many?");
	patch_str(0x000baf98,  16, "Sell how many?");
    patch_str(0x000bafac,  18, "Create how many?");
    patch_str(0x000bafbe,  16, "Use how many?");
    patch_str(0x000bafce,  20, "Discard how many?");
    patch_str(0x000bafd4,  22, "Is it okay to sell?");
	patch_str(0x000bafec,  22, "Equip it right away?");
    patch_str(0x000bb004,  20, "Not enough money.");
    patch_str(0x000bb018,  20, "Out of materials.");
    patch_str(0x000bb02c,  22, "Can't carry anymore.");
     patch_str(0x000bb05c,  24, "Item does not exist.");
     patch_str(0x000bb074,  22, "Not enough points.");
    patch_str(0x000bb08d,  24, "Item has disappeared.");

    patch_str(0x000bb0a8,  30, "Can't recover. Needs repair.");
    patch_str(0x000bb0c8,  30, "Can't equip. Needs repair.");
    patch_str(0x000bb0e9,  30, "Returning to item list.");
    patch_str(0x000bb100,  20, "Use this item?");
   
    //SAVE MENU
    patch_str(0x000bb13C,  18, "Overwrite data?");
    patch_str(0x000bb150,  16, "Load data? ");
    patch_str(0x000bb164,  16, "Save data? ");
    patch_str(0x000bb178,  14, "Delete data?");
    patch_str(0x000bb188,  10, "Reset it?");
    patch_str(0x000bb19c,  14, "Are you sure?");
    patch_str(0x000bb1b4,  18, "Reset system data?");
    patch_str(0x000bb1d8,  18, "New data.");
    patch_str(0x000bb1e4,  24, "The Data is corrupted.");
    patch_str(0x000bb1fc,  18, "Different Version.");
    patch_str(0x000bb214,  16, "Reading failure.");//change
    patch_str(0x000bb22c,  16, "Writing failure.");
    patch_str(0x000bb244,  26, "Saving...");
    patch_str(0x000bb260,  18, "   Initializing...");
    patch_str(0x000bb274,  18, "   Loading...");
    patch_str(0x000bb288,  18, "Save Complete.");
    patch_str(0x000bb29c,  18, "Load Complete.");
    patch_str(0x000bb2b0,  18, "Init. Complete");
    
    
    
    //Confirmation menu
    patch_str(0x000bb2e4,  6, "Yes");
    patch_str(0x000bb2dc,  6, "No");
    patch_str(0x000bb2ec,  8, "Cancel");
    
    //forge menu
    patch_str(0x000bb308,  18, "No materials");
    patch_str(0x000bb31c,  30, "No weapons to upgrade.");
    patch_str(0x000bb33c,  30, "No weapons to strenghten.");
    patch_str(0x000bb35c,  14, "Disassemble?");
    patch_str(0x000bb36c,  22, "Select ability");
    patch_str(0x000bb37c,  16, "Select effect");
    patch_str(0x000bb38c,  26, "Craftknight rank too low");
    patch_str(0x000bb3a8,  18, "Already enhanced");
    patch_str(0x000bb3bc,  22, "No items to upgrade.");
    patch_str(0x000bb3d4,  30, "No item has been set.");
    patch_str(0x000bb3f4,  22, "There are points left.");
    patch_str(0x000bb40c,  18, "Proceed anyway?");
    patch_str(0x000bb420,  22, "~2~5~5 TEC required");
   
   
    patch_str(0x000bb67c,  30, "Learned new skill~: Upgrade");
    patch_str(0x000bb658,  34, "You can now enhance weapons once");
  
	patch_str(0x000bb558,  18, "when TEC is full");         
	patch_str(0x000bb56c,  30, "Keep a shapestone's effects");      
	patch_str(0x000bb58c,  34, "Disassembling skill has improved!");   
	   
	patch_str(0x000bb49c,  22, "~4 weapon parameters.");
	patch_str(0x000bb4b4,  22, "~3 weapon parameters.");
	patch_str(0x000bb4cc,  22, "~2 weapon parameters.");
	patch_str(0x000bb4e4,  34, "Strengthen skill up. Improve up to");
	
	patch_str(0x000bb5c4, 26 , "single weapon parameter.");
	patch_str(0x000bb5e0,  34, "Spend TEC points to improve a");
	patch_str(0x000bb604,  30, "Learned~: Strengthen.");
	
	patch_str(0x000bb5b0,  18, "three times.");
	patch_str(0x000bb624,  18, "twice.");
	patch_str(0x000bb638,  30, "Weapons can now be upgraded");
	
	patch_str(0x000bb508,  14, "materials.");
	patch_str(0x000bb518,  26, "effects and recover used");
	patch_str(0x000bb534,  34, "Learned~: Remove upgrades. Remove");
	
	//misc
	patch_str(0x000bb6a0,  10, "Comment");//should be <Comment> any workaround?
    patch_str(0x000bb6e4,  12, " obtained!");
    patch_str(0x000bb6f0,  14, " handed over.");
    patch_str(0x000bb700,  14, " was paid for.");
    
    patch_str(0x000bb778,  14, "Storage");//should be <Storage> any workaround?
    patch_str(0x000bb788,  18, "- Empty -");//should be --Empty-- any workaround?
    patch_str(0x000bb79c,  18, "End");
    patch_str(0x000bb7b2,  16, "Received.");
    patch_str(0x000bb7c4,  22, "Choose your weapon.");   
	
	//omake
	patch_str(0x000bb95c, 22, "~Vs Gunvald ~E~X"); 
	patch_str(0x000bb974, 14 , "~Vs Borgrim"); 
	patch_str(0x000bb984, 18 , "~Vs Gunvald"); 
	patch_str(0x000bb998, 18 , "~Vs Magdrad"); 
	patch_str(0x000bb9ac, 14 , "~Vs Phantom"); 
	patch_str(0x000bb9bc, 6 , "Save"); 
	patch_str(0x000bb9c4, 18 , "Big Summons"); 
	patch_str(0x000bb9d8, 10 , "Ultbst"); 
	patch_str(0x000bb9e4, 10 , "Voice");
	patch_str(0x000bb9f0, 6 , "~S~E"); 
	patch_str(0x000bba18, 10 , "Firewood"); 
	patch_str(0x000bba24, 6 , "Fish"); 
	patch_str(0x000bba2c, 14 , "Gunvald ~E~X"); 
	patch_str(0x000bba3c, 10 , "Borgrim"); 
	patch_str(0x000bba48, 14 , "Gunvald"); 
	patch_str(0x000bba58, 10 , "Magdrad"); 
	patch_str(0x000bba64,  6, "Dragon"); 
	patch_str(0x000bba6c,  10, "Cancel"); 
	patch_str(0x000bba78,  10, "Support"); 
	patch_str(0x000bba84, 6 , "Equip"); 
	patch_str(0x000bba8c, 6 , "Start"); 
	patch_str(0x000bba94, 6 , "Serge"); 
	patch_str(0x000bba9c, 6 , "Soldr"); 
	patch_str(0x000bbaa4, 10 , "Bostaph"); 
	patch_str(0x000bbab0, 6 , "Tram"); 
	patch_str(0x000bbab8, 6 , "Pike"); 
	patch_str(0x000bbac0, 6 , "Gillan"); 
	patch_str(0x000bbac8, 10 , "Murno"); 
	patch_str(0x000bbad4, 6 , "Rob"); 
	patch_str(0x000bbadc, 6 , "Anise"); 
	patch_str(0x000bbae4, 6 , "Tier"); 
	patch_str(0x000bbaec, 6 , "Lemmy"); 
	patch_str(0x000bbaf4, 10 , "Jade"); 
	patch_str(0x000bbb00, 6 , "V.E"); 
	patch_str(0x000bbb0c, 18 , "Ult Battle Rush"); 
	patch_str(0x000bbb20, 14 , "~E~X~2  Rush"); 
	patch_str(0x000bbb30, 14 , "~E~X~1  Rush"); 
	patch_str(0x000bbb40, 18 , "Rival Rush"); 
	patch_str(0x000bbb54, 14 , "Boss Rush");  
	patch_str(0x000bbb64, 6 , "End"); 
	patch_str(0x000bbb6c, 10 , "Conditions"); 
	patch_str(0x000bbb78, 14 , "Mini Games"); 
	patch_str(0x000bbb88, 14 , "Sound Mode"); 
	patch_str(0x000bbb98, 14 , "Bonus Battle");  
	patch_str(0x000bbba8, 26 , "Fight against Gunvald ~E~X"); 
	patch_str(0x000bbbc4, 22 , "Fight against Borgrim"); 
	patch_str(0x000bbbdc, 26 , "Fight against Gunvald"); 
	patch_str(0x000bbbf8, 22 , "Fight against Magdrad"); 
	patch_str(0x000bbc10, 18 , "Fight with Phantom");  
	patch_str(0x000bbc24, 22 , "Save data"); 
	patch_str(0x000bbc3c, 30 , "Play the Firewood mini game"); 
	patch_str(0x000bbc5c, 26 , "Play the Fishing mini game"); 
	patch_str(0x000bbc78, 26 , "Listen Character's Voices"); 
	patch_str(0x000bbc94, 22 , "Listen available B~G~M");  
	patch_str(0x000bbcac, 30 , "Defeat giant Summon Creatures"); 
	patch_str(0x000bbccc, 26 , "~Vs Giant Summon Creature"); 
	patch_str(0x000bbce8, 34 , "Play Ultimate battle attack"); 
	patch_str(0x000bbd0c, 34 , "Start Rival Rush"); 
	patch_str(0x000bbd30, 30 , "Start Boss Rush");  
	patch_str(0x000bbd50, 30 , "~E~X~2 attack"); 
	patch_str(0x000bbd70, 30 , "~E~X~1 attack"); 
	patch_str(0x000bbd90, 22 , "Defeat Serge"); 
	patch_str(0x000bf928, 22 , "Defeat Serge"); 
	patch_str(0x000bbda8, 22 , "Defeat Soldier"); 
	patch_str(0x000bf940, 22 , "Defeat Soldier"); 
	patch_str(0x000bf958, 26 , "Defeat Bostaph"); 
	patch_str(0x000bbdc0, 26 , "Defeat Bostaph"); 
	patch_str(0x000bbddc, 22 , "Defeat Tram"); 
	patch_str(0x000bf974, 22 , "Defeat Tram"); 
	patch_str(0x000bbdf4, 22 , "Defeat Pike"); 
	patch_str(0x000bf98c, 22 , "Defeat Pike"); 
	patch_str(0x000bf9a4, 22 , "Defeat Gillan"); 
		patch_str(0x000bbe0c, 22 , "Defeat Gillan"); 
	patch_str(0x000bbe24, 26 , "Defeat Murno"); 
		patch_str(0x000bf9bc, 26 , "Defeat Murno"); 
	patch_str(0x000bf9d8, 22 , "Defeat Rob"); 
		patch_str(0x000bbe40, 22 , "Defeat Rob"); 
	patch_str(0x000bbe58, 22 , "Defeat Anise"); 
	patch_str(0x000bf9f0, 22 , "Defeat Anise"); 
	patch_str(0x000bfa08, 22  , "Defeat Tier"); 
	patch_str(0x000bbe70, 22  , "Defeat Tier"); 
	patch_str(0x000bbe88, 22 , "Defeat Lemmy"); 
		patch_str(0x000bfa20, 22 , "Defeat Lemmy"); 
	patch_str(0x000bfa38, 26 , "Defeat Jade"); 
	patch_str(0x000bbea0, 26 , "Defeat Jade"); 
	patch_str(0x000bbebc, 26 , "DefeatV.E"); 
	patch_str(0x000bfa54, 26 , "DefeatV.E"); 
	patch_str(0x000bbed4, 14 , "Game voices"); 
	//patch_str(0x000bbb0c, 10 , "SE dummy"); 
	patch_str(0x000bbef0, 18 , "Game B~G~M"); 
	patch_str(0x000bbf04, 34 , "Summon Night Swordcraft Story ~2"); 
	patch_str(0x000bbf28, 30 , "Summon Night Swordcraft Story"); 
	patch_str(0x000bbf48, 30 , "Practice Firewood Mini game"); 
	patch_str(0x000bbf68, 26 , "Practice fishing mini game"); 
	patch_str(0x000bbf84, 26 , "Choose Gunvald E~X"); 
	patch_str(0x000bbfa0, 22 , "Choose Borgrim"); 
	patch_str(0x000bbfb8, 26 , "Choose Gunvald"); 
	patch_str(0x000bbfd4, 22 , "Choose Magdrad"); 
	patch_str(0x000bbfec, 18 , "Choose Ult Beast"); 
	patch_str(0x000bf7d0, 26 , "Choose Gunvald E~X"); 
	patch_str(0x000bfc30, 22 , "Borgrim chosen"); 
	patch_str(0x000bfc50, 26 , "Gunvald chosen"); 
	patch_str(0x000bfc0c, 22 , "Magdrad chosen"); 
	patch_str(0x000bfc24, 18 , "Ult Beast chosen"); 
	patch_str(0x000bc000, 18 , "Go back"); 
	patch_str(0x000bfb90, 18 , "Go back"); 
	patch_str(0x000bfbb0, 22 , "Change Support");  
	patch_str(0x000bc014, 22 , "Change Support");  
	patch_str(0x000bfbb0, 18 , "Modify Equipment"); 
	patch_str(0x000bc014, 18 , "Modify Equipment");
	patch_str(0x000bc040, 10 , "Begin"); 
	patch_str(0x000bfba4, 10 , "Begin"); 
	patch_str(0x000bc04c, 18 , "chosen Serge"); 
	patch_str(0x000bfa80, 18 , "chosen Soldier"); 
	patch_str(0x000bc074, 22 , "chosen Bostaph"); 
	patch_str(0x000bfaac, 18 , "chosen Tram"); 
	patch_str(0x000bc0a0, 18 , "chosen Pike"); 
	patch_str(0x000bfad4, 18 , "chosen Gillan"); 
	patch_str(0x000bc0c8, 22 , "chosen Murno"); 
	patch_str(0x000bfb00, 18 , "chosen Rob"); 
	patch_str(0x000bc0f4, 18 , "chosen Anise"); 
	patch_str(0x000bfb28,  18, "chosen Tier"); 
	patch_str(0x000bc11c, 18 , "chosen Lemmy"); 
	patch_str(0x000bfb50, 22 , "chosen Jade");  
	patch_str(0x000bfb68, 18 , "chosenV.E"); 
	patch_str(0x000bc15e,  12, " chosen"); //careful!
	patch_str(0x000bfa6c, 18 , "Serge chosen"); 
	patch_str(0x000bc060, 18 , "chosen Soldier"); 
	patch_str(0x000bfa94, 22 , "chosen Bostaph"); 
	patch_str(0x000bc08c, 18 , "chosen Tram"); 
	patch_str(0x000bfac0, 18 , "chosen Pike"); 
	patch_str(0x000bc0b4, 18 , "chosen Gillan"); 
	patch_str(0x000bfae8, 22 , "chosen Murno"); 
	patch_str(0x000bc0e0, 18 , "chosen Rob"); 
	patch_str(0x000bfb14, 18 , "chosen Anise"); 
	patch_str(0x000bc108,  18, "chosen Tier"); 
	patch_str(0x000bfb3c, 18 , "chosen Lemmy"); 
	patch_str(0x000bc130, 22 , "chosen Jade");  
	patch_str(0x000bc148, 18 , "chosenV.E"); 
	patch_str(0x000bfca2,  12, " chosen"); //careful!
	patch_str(0x000bc16c,  26, "Play Big battle attack"); 
	patch_str(0x000bc188, 30 , "Play E~X~2 battle attack"); 
	patch_str(0x000bc1a8, 30 , "Play E~X~1 battle attack"); 
	patch_str(0x000bc1c8, 34 , "Play Rival battle attack"); 
	patch_str(0x000bc1ec, 30 , "Play Boss battle attack"); 
	patch_str(0x000bc20c, 18 , "Exit extras menu"); 
	patch_str(0x000bc220, 34 , "Conditions to get more extras"); 
	patch_str(0x000bc244, 22 , "Play mini games"); 
	patch_str(0x000bc25c, 30 , "Listen to game B~G~M"); 
	patch_str(0x000bc27c, 22 , "Play bonus battle"); 
    patch_str(0x000bc294, 6 , "Voice"); 
	patch_str(0x000bc29c,  10, "Ending");  
	patch_str(0x000bc2a8,  10, "Fun Story"); 
	patch_str(0x000bc2b4, 10 , "Tommorow!"); 
	patch_str(0x000bc2c0,  14, "Invisible sign"); 
	patch_str(0x000bc2d0, 10 , "Assemble"); 
	patch_str(0x000bc2dc, 10 , "Nasty Flam"); 
	patch_str(0x000bc2e8, 10  , "Love Story"); 
	patch_str(0x000bc2f4,  22, "Hurry up!"); 
	patch_str(0x000bc30c,  18, "Bursting Anger"); 
	patch_str(0x000bc320, 14 , "End of Sorrow"); 
	patch_str(0x000bc330, 10 , "Smile"); 
	patch_str(0x000bc33c,  14, "Fleeting Peace"); 
	patch_str(0x000bc34c, 14 , "Be rich fast"); 
	patch_str(0x000bc35c, 14 , "Watching Stars"); 
	patch_str(0x000bc36c, 14 , "Anything else?");  
	patch_str(0x000bc37c, 22 , "Let's try!"); 
	patch_str(0x000bc394,  18, "Start from the end"); 
	patch_str(0x000bc3a8, 10 , "Final Boss"); 
	patch_str(0x000bc3b4, 14 , "Lurker of Ruin"); 
	patch_str(0x000bc3c4,  10, "Wind Guide"); 
	patch_str(0x000bc3d0, 10 , "~Zhu Ruins"); 
	patch_str(0x000bc3dc, 10 , "Ao Temple"); 
    patch_str(0x000bc3e8, 14 , "Mine Moist"); 
	patch_str(0x000bc3f8, 10 , "Woe Forest"); 
	patch_str(0x000bc404, 14 , "Pass Rock road"); 
	patch_str(0x000bc414, 10 , "Home Song"); 
	patch_str(0x000bc420, 14 , "Louise Ruins"); 
	patch_str(0x000bc430, 22 , "Bustle of Prosban");
	patch_str(0x000bc448, 22 , "Moments in Manig");  
	patch_str(0x000bc460, 10 , "Mine Day"); 
	patch_str(0x000bc46c, 18 , "Requiem Loser"); 
	patch_str(0x000bc480, 22 , "Which one will win?"); 
	patch_str(0x000bc498,  14, "Ao Zhu battle"); 
	patch_str(0x000bc4a8, 22 , "Final Battle Ride"); 
	patch_str(0x000bc4c0, 10 , "Huge Rival"); 
	patch_str(0x000bc4cc, 10 , "LastResort");  
	patch_str(0x000bc4d8, 10 , "FriendCard"); 
	patch_str(0x000bc4e4, 14 , "Go get them!"); 
	patch_str(0x000bc4f4, 26 , "Epilogue Two Miracles"); 
	patch_str(0x000bc510, 26 , "Opening Theme : Encounter"); 
	patch_str(0x000bc52c, 26 , "Precede Rock Beginning"); 
	patch_str(0x000bc548, 34 , "Start! Gunvald combat version"); 
	patch_str(0x000bc56c, 18 , "Requiem Loser");  
	patch_str(0x000bc580, 10 , "Win Proof"); 
	patch_str(0x000bc58c, 14 , "Curry Palace"); 
	patch_str(0x000bc59c,  22, "Start! Gunvald"); 
	patch_str(0x000bc5b4,  14, "Feel not lost"); 
	patch_str(0x000bc5c4, 6 , "Enigma"); 
	patch_str(0x000bc5cc, 10 , "Warcouncil"); 
	patch_str(0x000bc5d8, 10 , "Sly Vortex");  
	patch_str(0x000bc5e4, 10 , "The Oath"); 
	patch_str(0x000bc5f0, 14 , "Emergency!"); 
	patch_str(0x000bc600, 14 , "Infuriated!"); 
	patch_str(0x000bc610, 14 , "Sorrow Examine"); 
	patch_str(0x000bc620, 18 , "Blue Sky"); 
	patch_str(0x000bc634, 14 , "Peaceful Day"); 
	patch_str(0x000bc644, 34 , "Add two to get Newbie Craftknights");  
	patch_str(0x000bc668, 16 , "Trading now"); 
	patch_str(0x000bc67c, 14 , "To new venture"); 
	patch_str(0x000bc68c, 18 , "Goura's Labyrinth"); 
	patch_str(0x000bc6a0, 22 , "Oni Hot Springs"); 
	patch_str(0x000bc6b8, 18 , "Glacier Gorge"); 
	patch_str(0x000bc6cc, 10 , "Sun Beach");//subterranean bay 
	patch_str(0x000bc6d8, 14 , "Ruined Factory");  
	patch_str(0x000bc6e8, 14 , "Hidden Cave"); 
	patch_str(0x000bc6f8, 14 , "Savage Forest"); 
	patch_str(0x000bc708,  10, "Cliff town"); //waterfall
	patch_str(0x000bc714, 18 , "What can you do?"); 
	patch_str(0x000bc728, 10 , "GoraAdvent"); 
	patch_str(0x000bc734, 18 , "Envoy blocked path"); 
	patch_str(0x000bc748, 18 , "Monoshift Activate");  
	patch_str(0x000bc75c, 14 , "To Battle"); 
	patch_str(0x000bc76c,  14, "End Title"); 
	patch_str(0x000bc77c,  18, "Opening Theme"); 
	patch_str(0x000bc790,  14, "Title Theme"); 
	patch_str(0x000bc7a0, 10 , "Win Proof"); 
	patch_str(0x000bc7ac, 26 , "Real Game! Battle version"); 
	patch_str(0x000bc7c8, 18 , "Impossible Fight");  
	patch_str(0x000bc7dc,  14, "Stalking Fear"); 
	patch_str(0x000bc7ec,  14, "Too late!"); 
	patch_str(0x000bc7fc, 10 , "Enraged!"); 
	patch_str(0x000bc808,  14, "In loneliness"); 
	patch_str(0x000bc818,  18, "Happy! Fun!"); 
	patch_str(0x000bc82c, 14 , "Warm Gaze"); 
	patch_str(0x000bc83c, 34 , "You and I a craftknight story");  
	patch_str(0x000bc860,  16, "Trading now");  
	patch_str(0x000bc874,  10, "Cent. City"); 
	patch_str(0x000bc880,  14, "Curry Palace"); 
	patch_str(0x000bc890,  10, "Next"); 
	patch_str(0x000bc89c,  10, "Outskirt"); 
	patch_str(0x000bc8a8,  10, "Ice Cage"); 
	patch_str(0x000bc8b4,  14, "Snow Port"); 
	patch_str(0x000bc8c4,  10, "Flame Jail");  
	patch_str(0x000bc8d0,  14, "Volcanic Islet"); 
	patch_str(0x000bc8e0,  10, "Sea Cave"); 
	patch_str(0x000bc8ec,  10, "Blessing"); 
	patch_str(0x000bc8f8,  10, "Sneak Plan"); 
	patch_str(0x000bc904,  26, "Seal of Labyrinth vision~2"); 
	patch_str(0x000bc920,  10, "Maze Seal"); 
	patch_str(0x000bc92c,  10, "Wystern");  
	patch_str(0x000bc938,  14, "Let's Create"); 
	patch_str(0x000bc948,  14, "Parista Paris"); 
	patch_str(0x000bc958,  10, "Foeappear!"); 
	patch_str(0x000bc964, 10 , "Real Game!"); 
	patch_str(0x000bc970,  18, "Ending Theme"); 
	patch_str(0x000bc984,  14, "Opening Theme"); 
	
	
	//Game Voices
	//int stride,int max,int next
	char cadena[30]="Sword Bolt ";
	int next=0;
	next=insert_chain(cadena,0x000bc994,12,20,20);
	//printf("Salida: %x\n",next);
	strcpy(cadena,"Velworen   ");
    next=insert_chain(cadena,next,12,19,20);
    //printf("Salida: %x\n",next);
	strcpy(cadena,"Sldr");
	next=insert_chain(cadena,next,4,13,12);
	//printf("Salida: %x\n",next);
	strcpy(cadena,"Serge ");
	next=insert_chain(cadena,next,6,18,12);
	//printf("Salida: %x\n",next);
	strcpy(cadena,"Bostaph ");
	next=insert_chain(cadena,next,8,16,16);
	//printf("Salida: %x\n",next);
	strcpy(cadena,"Tram  ");
	next=insert_chain(cadena,next,6,18,12);
	//printf("Salida: %x\n",next);
	strcpy(cadena,"Pike  ");
	next=insert_chain(cadena,next,6,26,12);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Gillan");
	next=insert_chain(cadena,next,4,20,12);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Murno   ");
	next=insert_chain(cadena,next,8,22,16);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Rob ");
	next=insert_chain(cadena,next,4,22,12);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Anise ");
	next=insert_chain(cadena,next,6,26,12);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Tier  ");
	next=insert_chain(cadena,next,6,25,12);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Lemmy ");
	next=insert_chain(cadena,next,6,29,12);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Jade    ");
	next=insert_chain(cadena,next,8,24,16);
	printf("Salida: %x\n",next);
	strcpy(cadena,"V.E   ");
	next=insert_chain(cadena,next,6,25,12);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Rufeel    ");
	next=insert_chain(cadena,next,10,26,20);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Rufeel    ");
	next=insert_chain(cadena,next,10,29,20);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Killfith  ");
	next=insert_chain(cadena,next,10,24,20);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Killfith  ");
	next=insert_chain(cadena,next,10,31,20);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Enzi  ");
	next=insert_chain(cadena,next,6,28,16);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Enzi  ");
	next=insert_chain(cadena,next,6,31,16);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Run-dor ");
	next=insert_chain(cadena,next,8,24,20);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Run-dor ");
	next=insert_chain(cadena,next,8,29,20);
	printf("Salida: %x\n",next);
    strcpy(cadena,"Rifmonica ");
	next=insert_chain(cadena,next,10,70,16);
	printf("Salida: %x\n",next);
	strcpy(cadena,"Ritchburn   ");
	next=insert_chain(cadena,next,12,70,20);
	printf("Salida: %x\n",next);
    
    patch_str(0x000bf52c, 26 , "You need a fishing rod."); 
    patch_str(0x000bf548, 22 , "You need bait."); 
    patch_str(0x000bf560, 30 , "Murno is now available."); 
    patch_str(0x000bf580, 34 , "Gunvald is now available."); 
    patch_str(0x000bf5a4, 30 , "Borgrim is now available."); 
    patch_str(0x000bf5d8, 14 , "Alert message!"); 
    patch_str(0x000bf5e8, 18 , "Messaging failed!"); 
    patch_str(0x000bf5fc, 14 , "Gunvald  E~X"); 
    patch_str(0x000bf610, 10 , "Firewood"); 
    patch_str(0x000bf61c, 6 , "Fish"); 
    patch_str(0x000bf638, 18 , "~2 Big Summons"); 
    patch_str(0x000bf64c, 18 , "Ult Battle Rush"); 
	patch_str(0x000bf684, 14 , "~E~X~2  Rush"); 
	patch_str(0x000bf694, 14 , "~E~X~1  Rush"); 
	patch_str(0x000bf660, 18 , "Rival Rush"); 
	patch_str(0x000bf674, 14 , "Boss Rush");  
   	patch_str(0x000bf6a4, 6 , "Serge"); 
	patch_str(0x000bf6ac, 6 , "Soldr"); 
	patch_str(0x000bf6b4, 10 , "Bostaph"); 
	patch_str(0x000bf6c0, 6 , "Tram"); 
	patch_str(0x000bf6c8, 6 , "Pike"); 
	patch_str(0x000bf6d0, 6 , "Gillan"); 
	patch_str(0x000bf6d8, 10 , "Murno"); 
	patch_str(0x000bf6e4, 6 , "Rob"); 
	patch_str(0x000bf6ec, 6 , "Anise"); 
	patch_str(0x000bf6f4, 6 , "Tier"); 
	patch_str(0x000bf6fc, 6 , "Lemmy"); 
	patch_str(0x000bf704, 10 , "Jade"); 
	patch_str(0x000bf710, 6 , "V.E"); 
	patch_str(0x000bf71c, 10 , "Cancel"); 
	patch_str(0x000bf728, 6 , "Ok"); 
	patch_str(0x000bf730, 10 , "Support"); 
	patch_str(0x000bf73c, 6 , "Equip"); 
	patch_str(0x000bf744, 14 , "Used Items"); 
		patch_str(0x000bf754, 6 , "Weapon"); 
	patch_str(0x000bf75c, 10 , "Magdrad"); 
	patch_str(0x000bf768,  6, "Dragon"); 
    patch_str(0x000bf770, 10 , "Borgrim"); 
	patch_str(0x000bf77c, 14 , "Gunvald"); 
	patch_str(0x000bf78c,  6, "Beast"); 
	patch_str(0x000bf794,  10, "Rival"); 
	patch_str(0x000bf7a0,  6, "Hero"); 
	patch_str(0x000bf7a8,  6, "Cancel"); 
	patch_str(0x000bf7b0,  6, "Gift"); 
	patch_str(0x000bf7b8,  6, "Trade"); 
	patch_str(0x000bf7c0,  6, "Fight"); 
	patch_str(0x000bf7c8,  6, "Comp."); 
	
	patch_str(0x000bf7d0,  26, "Gunvald Ex in use"); 
	patch_str(0x000bf7f0,  30, "Firewood Minigame unlocked"); 
	patch_str(0x000bf810, 26 , "Fishing Minigame unlocked"); 
	patch_str(0x000bf82c, 26 , "Voice Test unlocked"); 
	patch_str(0x000bf848,  22, "~B~G~M Test unlocked"); 
	patch_str(0x000bf860,  30, "~2 Big Summons unlocked"); 
	patch_str(0x000bf880, 34 , "Ultra battle attack unlocked"); 
	patch_str(0x000bf8a4, 34 , "Rival Attack unlocked"); 
	patch_str(0x000bf8c8, 30 , "Boss Attack unlocked"); 
	patch_str(0x000bf8e8, 30 , "~E~X~2 Attack unlocked"); 
	patch_str(0x000bf908, 30 , "~E~X~1 Attack unlocked"); 
 
	patch_str(0x000bf928, 22 , "Serge unlocked"); 
	patch_str(0x000bf940, 22 , "Soldier unlocked"); 
	patch_str(0x000bf958, 26 , "Bostaph unlocked"); 
	patch_str(0x000bf974, 22 , "Tram unlocked"); 
	patch_str(0x000bf98c, 22 , "Pike unlocked"); 
	patch_str(0x000bf9a4, 22 , "Gillan unlocked"); 
	patch_str(0x000bf9bc, 26 , "Murno unlocked"); 
	patch_str(0x000bf9d8, 22 , "Rob unlocked"); 
	patch_str(0x000bf9f0, 22 , "Anise unlocked"); 
	patch_str(0x000bfa08, 22 , "Tier unlocked"); 
	patch_str(0x000bfa20, 22 , "Lemmy unlocked"); 
	patch_str(0x000bfa38, 26 , "Jade unlocked"); 
	patch_str(0x000bfa54, 22 , "V.E unlocked"); 
	patch_str(0x000bfbf8, 18 , "Weapon Replaced"); 
	patch_str(0x000bfce4, 30 , "Weapons and Items exchanged"); 
	patch_str(0x000bfd28, 14 , "Make a match"); 
	patch_str(0x000bfd38, 22 , "You don't have weapons"); 
	patch_str(0x000bfd50, 26 , "You don't have items"); 
	patch_str(0x000bfcb0, 18 , "Communication end"); 
	patch_str(0x000bfd6c, 18 , "Sent Complete"); 
	patch_str(0x000bfd80, 18 , "Receive complete"); 
	patch_str(0x000bfda2, 20 , " Activated!"); //carefull!!!
	patch_str(0x000bfdb8, 10 , "Obtained!"); 
	patch_str(0x000bfd94, 10 , "Saving..."); 
	patch_str(0x000bfa54, 34 , "Match with Huge Stray Summon"); 
	patch_str(0x000bfdc4, 34 , "Confirm trade?"); 
	patch_str(0x000bfdd4, 6 , "Yes"); 
	patch_str(0x000bfddc, 6 , "No"); 
	patch_str(0x000c732c, 16 , "Hammer"); 
	patch_str(0x000c7384, 16 , "Govan's Sword"); 
	patch_str(0x000bfe3c, 18 , "Reverse upgrade?"); 
    patch_str(0x000bfea8, 22 , "You don't have weapons"); 
    patch_str(0x000bfec0, 26 , "All weapons repaired!"); 
    patch_str(0x000bfedc, 10 , "Obtained!"); 
    patch_str(0x000c0040, 30 , "   Load clear data?       "); 
   patch_str(0x000c0060, 18 , " Will be inherited"); 
    
      patch_str(0x000c0074, 14 , " Equipment"); //there's a middle dot used, lol
       patch_str(0x000c0084,  34, " Fishing points Minigame records"); 
         patch_str(0x000c00a8, 30 , " Skills list    Effects list"); 
          patch_str(0x000c00c8, 30 , " Forge rank     Beastiary"); 
           patch_str(0x000c00e8,  22, " Secrets        Money"); 
            patch_str(0x000c0100, 26 , "from the clear save data"); 
            patch_str(0x000c0210, 22 , "Choose your bait"); 
              patch_str(0x000c0228, 26 , "Choose your fishing rod"); 
     patch_str(0x000c0244, 30 , "A btn Start   ~B btn End"); 
     //patch_str(0x000d5678, 2 , "~\"");ADD \" 
     //patch_str(0x000d567b, 2 , "~\""); 

     patch_str(0x000c0264, 30 , "Business is over for today."); 
        patch_str(0x000d585a, 8 , "Retry"); 
        patch_str(0x000d5864, 14 , "Back to title"); 
        patch_str(0x000d5874, 8 , "~0 retry"); 
        patch_str(0x000d587e, 8 , "~1 retry"); 
        patch_str(0x000d5888, 10 , "~2 retries"); 
        patch_str(0x00bd9fc0, 8 , "Let's go"); 
        patch_str(0x00bd9fca, 22 , "OK, Pace Up!"); 
        patch_str(0x00bd9fe2, 22 , "Don't be hit by hammer"); 
        patch_str(0x00bd9ffa, 16 , "Let's go fast"); 
        patch_str(0x00bda00c, 14 , "Looks good!"); 
        patch_str(0x00bda01c, 14 , "How's this?"); 
        patch_str(0x00bda02c, 14 , "Feels good!"); 
        patch_str(0x00bda03c, 8 , "Great!"); 
        patch_str(0x00bda046, 14 , "Feels good!"); 
        patch_str(0x00bda056,  12, "Good!"); 
        patch_str(0x00bda064, 14 , "Amazing!"); 
        patch_str(0x00bda074,  6, "Close."); 
        patch_str(0x00bda07c, 24 , "Guard prevented hammer."); 
        patch_str(0x00bda096, 12 , "Don't push"); 
        patch_str(0x00bda0a4, 26 , "Break with axe or drill."); 
      patch_str(0x00bc8fac, 16 , "Blade Rush"); 
        patch_str(0x00bc8fc8, 38 , "Sword Bolt's Secret Technique"); 
    	patch_str(0x00bc8ff0, 16 , "Splash"); 
        patch_str(0x00bc900c, 38 , "Phantom Dragon's Special Technique"); 
        patch_str(0x00bc9034, 16 , "Last Boss Attack"); 
        patch_str(0x00bc9050, 38 , "Velworen's exclusive Special move"); 
        patch_str(0x00bc7c1c, 16 , "Aqua Wave"); 
        patch_str(0x00bc7c5c, 16 , "Flame Breath"); 
        patch_str(0x00bc7c9c, 16 , "Flame Breath"); 
    	patch_str(0x00bc7cdc,  16, "Spark Saber"); 
        patch_str(0x00bc7d1c,  16, "Swordbolt"); 
    	patch_str(0x00bc7d5c,  16, "Water Dragon Hit"); 
        patch_str(0x00bc7d9c,  16, "Flame Dragon Hit"); 
        patch_str(0x00bc7ddc,  16, "Gunvald Laser"); 
        patch_str(0x00bc7e1c,  16, "Borgrim Combo"); 
        patch_str(0x00bc7e5c,  16, "Medium Bell"); 
        patch_str(0x00bc7e9c,  16, "Big Bell"); 
        patch_str(0x00bc7edc,  16, "Pre-Last Boss"); 
        patch_str(0x00bc7f1c,  16, "Pre-Last Boss"); 
      patch_str(0x00b79d04,  16, "Revolver"); 
        patch_str(0x00b79df4,  16, "Phantom Dragon"); 
        patch_str(0x00b79d7c, 16 , "Magdrad"); 
        patch_str(0x00b79f5c, 16 , "Golden Golem"); 
        patch_str(0x00b79fd4,16  , "Demon Ape"); 
        patch_str(0x00b7a04c, 16 , "Blade Wing"); 
        patch_str(0x00b7a0c4, 16 , "Skull Fighter"); 
        patch_str(0x00b7a13c, 16 , "Skull Leader"); 
        patch_str(0x00b7a6dc,  16, "Exploder"); 
        patch_str(0x00b7c554,  16, "Sword Bolt"); 
        
        
       patch_str(0x00bbc8f8,  16, "Level Up!"); 
       patch_str(0x00bbc90e,  16, "Level Up!"); 
       patch_str(0x00bbc920,  16, "Allocate points"); 
       patch_str(0x00bbc944,  14, "unused points?"); 
       patch_str(0x00bbc932, 16 , "Exit and keep"); 
       patch_str(0x00bbc954, 6 , "Yes"); 
       patch_str(0x00bbc95c, 6 , "No"); 
       patch_str(0x00bbc964, 12 , "Items Gained"); 
       patch_str(0x00bbc976, 10 , "learned!"); 
       patch_str(0x00bbc986, 10 , "castable!"); 
       patch_str(0x00bbc992, 28 , "More new magic learned!"); 
       patch_str(0x00bbc9b0,22  , "Learned new magic!"); 
       
       
       
       
       
       
       
       /*patch_str(0x0,  , "");*/
}

static void
translate_items(void)
{
	patch_table(0x00bbca9c +  0, 84, NUM_ITEMS, 18, k_item_name);
	patch_table(0x00bbca9c + 44, 84, NUM_ITEMS, 38, k_item_desc);
}

static void
translate_magics(void)
{
	patch_table(0x00bc73dc +  0, 64, NUM_MAGICS, 18, k_magic_name);
	patch_table(0x00bc73dc + 24, 64, NUM_MAGICS, 38, k_magic_desc);
}

static void
translate_weapons(void)
{
	patch_table(0x00bc1e9c +  0, 88, NUM_WEAPONS, 18, k_weapon_name);
	patch_table(0x00bc1e9c + 50, 88, NUM_WEAPONS, 38, k_weapon_desc);
}

static void
translate_specials(void)
{
	patch_table(0x00bc81dc +  0, 68, NUM_SPECIALS, 18, k_special_name);
	patch_table(0x00bc81dc + 28, 68, NUM_SPECIALS, 38, k_special_desc);
}

static void
translate_effects(void)
{
	patch_table(0x00bc9100 +  0, 68, NUM_EFFECTS, 18, k_effect_name);
	patch_table(0x00bc9100 + 28, 68, NUM_EFFECTS, 38, k_effect_desc);
}

static void
translate_bestiary(void)
{
	patch_table(0x00b75114 +  0, 120, NUM_BEASTS, 18, k_beast_name);
	patch_table(0x00b75114 + 64, 120, NUM_BEASTS, 56, k_beast_desc);

	patch_table(0x00b75114 - 120 * 99, 120, NUM_BOSSES, 18, k_boss_name);
}

static void
translate_dialogue(void)
{
	int i;

	for (i = 0; k_script[i] != NULL; i++) {
		patch_dlg(k_script[i]);
	}
}

/*--------------------------------------------------------------*/

int
main(int argc, char *argv[])
{
	(void)argc, (void)argv;

	read_rom("sncsm3.gba");

	create_font();
	translate_name_entry_menu();
	translate_main_menu();
	translate_items();
	translate_magics();
	translate_weapons();
	translate_specials();
	translate_effects();
	translate_bestiary();
	//translate_dialogue();

	write_rom("out.gba");

	return 0;
}
