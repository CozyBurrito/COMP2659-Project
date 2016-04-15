# 1 "klingon.c" 1
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 7 "klingon.c" 2
# 1 "C:/c68/include/stdlib.h" 1
# 18 "C:/c68/include/stdlib.h"
typedef unsigned long  size_t;




typedef char  wchar_t;
# 44 "C:/c68/include/stdlib.h"
typedef struct {
    int		quot;
    int		rem;
} div_t;

typedef struct {
    long	quot;
    long	rem;
} ldiv_t;

 double atof (const char *s) ;
 int atoi (const char *str) ;
 long atol (const char *str) ;
 long int strtol (const char *nptr, char **endptr, int base) ;
 unsigned long int strtoul (const char *nptr, char **endptr, int base) ;
 double strtod (const char *s, char **endptr) ;

 void srand (unsigned int seed) ;
 int rand (void) ;

 void *malloc (size_t n) ;
 void free (void *param) ;
 void *realloc (void *_r, size_t n) ;
 void *calloc (size_t n, size_t sz) ;





 void *alloca (size_t) ;
# 89 "C:/c68/include/stdlib.h"
 void  abort (void) ;


 int atexit (void (*)(void)) ;

 void  exit (int) ;

 char *getenv (const char *tag) ;
 int system (const char *s) ;

 void *bsearch (const void *key, const void *base, size_t num, size_t size, int (*cmp )(const void *, const void *)) ;
 void qsort (void *base, size_t total_elems, size_t size, int (*cmp )(const void *, const void *)) ;

 int abs (int x) ;
 long labs (long x) ;

 div_t div (int num, int denom) ;
 ldiv_t ldiv (long num, long denom) ;

 int mblen (const char *, size_t) ;
 size_t mbstowcs (wchar_t *, const char *, size_t) ;
 int mbtowc (wchar_t *, const char *, size_t) ;
 size_t wcstombs (char *, const wchar_t *, size_t) ;
 int wctomb (char *, wchar_t) ;

 wchar_t *wcscat (wchar_t *, const wchar_t *) ;
 int wcscmp (const wchar_t *, const wchar_t *) ;
 wchar_t *wcscpy (wchar_t *, const wchar_t *) ;
 size_t wcslen (const wchar_t *) ;
 wchar_t *wcsncat (wchar_t *, const wchar_t *, size_t) ;
 int wcsncmp (const wchar_t *, const wchar_t *, size_t) ;
 wchar_t *wcsncpy (wchar_t *, const wchar_t *, size_t) ;
# 8 "klingon.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 9 "klingon.c" 2
# 1 "C:/c68/include/time.h" 1
# 26 "C:/c68/include/time.h"
typedef long 		time_t;
# 34 "C:/c68/include/time.h"
typedef unsigned long	clock_t;

struct tm
{
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
};



struct timeval {
	long	tv_sec;
	long	tv_usec;
};

struct timezone {
	int	tz_minuteswest;
	int	tz_dsttime;
};


 clock_t	clock	 (void) ;
 double		difftime (time_t, time_t) ;
 time_t		mktime	 (const struct tm *) ;
 time_t		time	 (time_t *) ;
 char * 	asctime	 (const struct tm *) ;
 char *		ctime	 (const time_t *) ;
 struct tm *	gmtime   (const time_t *) ;
 struct tm *	localtime (const time_t *) ;
 unsigned long  strftime (	char *s, size_t maxsize, const char *format, const struct tm *timeptr) ;



 void		tzset	(void) ;


 clock_t	_clock	 (void) ;
 int	gettimeofday (struct timeval *, struct timezone *) ;
 int	settimeofday (struct timeval *, struct timezone *) ;



typedef unsigned long  fd_set;


 int	select	(int, fd_set *, fd_set *, fd_set *,					struct timeval *) ;
# 10 "klingon.c" 2
# 1 "C:/c68/include/linea.h" 1
# 325 "C:/c68/include/linea.h"
typedef struct {



   short  _VPLANES;
   short  _VWRAP;




   short  *_CONTRL;
   short  *_INTIN;
   short  *_PTSIN;
   short  *_INTOUT;
   short  *_PTSOUT;
# 349 "C:/c68/include/linea.h"
   short  _COLBIT0;
   short  _COLBIT1;
   short  _COLBIT2;
   short  _COLBIT3;




   short  _LSTLIN;



   short  _LNMASK;



   short  _WMODE;
# 372 "C:/c68/include/linea.h"
   short  _X1;

   short  _Y1;

   short  _X2;

   short  _Y2;


   short  *_PATPTR;

   short  _PATMSK;

   short  _MFILL;



   short  _CLIP;
   short  _XMINCL;
   short  _YMINCL;
   short  _XMAXCL;
   short  _YMAXCL;


   short  _XDDA;


   short  _DDAINC;



   short  _SCALDIR;
   short  _MONO;





   short  _SOURCEX;
# 417 "C:/c68/include/linea.h"
   short  _SOURCEY;

   short  _DESTX;
   short  _DESTY;
   short  _DELX;

   short  _DELY;

   short  *_FBASE;
   short  _FWIDTH;

   short  _STYLE;
# 435 "C:/c68/include/linea.h"
   short  _LITEMASK;

   short  _SKEWMASK;

   short  _WEIGHT;

   short  _ROFF;


   short  _LOFF;


   short  _SCALE;

   short  _CHUP;




   short  _TEXTFG;

   char  *_SCRTCHP;




   short  _SCRPT2;



   short  _TEXTBG;


   short  _COPYTRAN;
# 476 "C:/c68/include/linea.h"
 short(*_SEEDABORT) (void) ;
# 484 "C:/c68/include/linea.h"
} __LINEA;
# 546 "C:/c68/include/linea.h"
typedef struct _font {



   short  font_id;

   short  size;

   char   name[32];

   short  first_ade;


   short  last_ade;


   short  top;

   short  ascent;

   short  half;

   short  descent;

   short  bottom;



short max_char_width;

short max_cell_width;

  short left_offset;

  short right_offset;

   short  thicken;

   short  ul_size;

   short  lighten;

   short  skew;



   short  flags;





   char   *h_table;

   short  *off_table;

   char   *dat_table;

   short  form_width;

   short  form_height;

 struct _font *next_font;


} __FONT;
# 620 "C:/c68/include/linea.h"
typedef short(*FPTR) (void) ;
typedef FPTR *FUNCPTR;
# 628 "C:/c68/include/linea.h"
typedef struct {



   char   fg0bg0;
   char   fg0bg1;
   char   fg1bg0;
   char   fg1bg1;

} OP_TAB;





typedef struct  {
	short	bl_xmin;
	short	bl_ymin;
	char	*bl_form;
	short	bl_nxwd;
	short 	bl_nxln;
	short 	bl_nxpl;
}SDDB;
# 673 "C:/c68/include/linea.h"
typedef struct {



   short   bb_b_wd;
   short   bb_b_ht;
   short   bb_plane_ct;
   short   bb_fg_col;
   short   bb_bg_col;
   OP_TAB  bb_op_tab;
   SDDB	   bb_s;
   SDDB	   bb_d;
   short   *bb_p_addr;
   short   bb_p_nxln;
   short   bb_p_nxpl;
   short   bb_p_mask;
   char	   bb_fill[24];

} BBPB;
# 700 "C:/c68/include/linea.h"
typedef struct
{
	char		*fd_addr;


	short		fd_w;
	short		fd_h;
	short		fd_wdwidth;
	short		fd_stand;
	short		fd_nplanes;
	short		fd_r1;
	short		fd_r2;
	short		fd_r3;
} MFDB;
# 720 "C:/c68/include/linea.h"
typedef struct
{
	short	sp_xhot;
	short	sp_yhot;
	short	sp_format;
	short	sp_bg;
	short	sp_fg;
	short	sp_data[32];





} SFORM;
# 750 "C:/c68/include/linea.h"
extern __LINEA *__aline;



extern __FONT  **__fonts;



extern short  (**__funcs) (void) ;
# 1013 "C:/c68/include/linea.h"
 void linea0 (void) ;
 void linea1 (void) ;
 int linea2 (void) ;
 void linea3 (void) ;
 void linea4 (void) ;
 void linea5 (void) ;
 void linea6 (void) ;
 void linea7 (BBPB *P) ;
 void linea8 (void) ;
 void linea9 (void) ;
 void lineaa (void) ;
 void lineab (void) ;
 void lineac (void *P) ;
 void linead (int x, int y, SFORM *sd, void *ss) ;
 void lineae (void) ;
 void lineaf (void) ;
# 11 "klingon.c" 2
# 1 "./klingon.h" 1
# 1 "./model.h" 1
# 1 "./globals.h" 1
# 10 "./globals.h"
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
typedef unsigned char SCANCODE;
typedef unsigned char UBYTE;
typedef enum { false, true } bool;
# 10 "./model.h" 2
# 30 "./model.h"
typedef struct {
	UINT16 posX;
	UINT16 posY;

	UINT16 deltaX;
	UINT16 deltaY;

	UINT8 alive;

	UINT8 move_requested;
	UINT8 move_requested_direction;

} playerShip;
# 57 "./model.h"
typedef struct {
	UINT16 posX;
	UINT16 posY;

	UINT16 deltaX;

	UINT16 active;

} enemyShip;
# 82 "./model.h"
struct Model {
	UINT16 score;

	playerShip players[1 ];

	enemyShip enemies[6 ];

};

void randomize_enemy_cor(struct Model *modelPtr, UINT16 enemy);

void init_model(struct Model *modelPtr);

void set_active(struct Model *modelPtr, UINT16 enemy, UINT16 active);
UINT16 get_active(struct Model *modelPtr, UINT16 enemy);
void update_score(struct Model *modelPtr, UINT16 value);

void set_score(struct Model *modelPtr, UINT16 value);
UINT16 get_score(struct Model *modelPtr);

void set_player_move_requested(struct Model *modelPtr, UINT16 player, UINT8 request);
UINT8 get_player_move_requested(struct Model *modelPtr, UINT16 player);

void set_player_move_requested_direction(struct Model *modelPtr, UINT16 player, UINT8 direction);
UINT8 get_player_move_requested_direction(struct Model *modelPtr, UINT16 player);

void set_player_cor(struct Model *modelPtr, UINT16 player, UINT16 x, UINT16 y);
UINT16 get_player_posX(struct Model *modelPtr, UINT16 player);
UINT16 get_player_posY(struct Model *modelPtr, UINT16 player);

void set_player_deltaX(struct Model *modelPtr, UINT16 player, UINT16 deltaX);
UINT16 get_player_deltaX(struct Model *modelPtr, UINT16 player);
void set_player_deltaY(struct Model *modelPtr, UINT16 player, UINT16 deltaY);
UINT16 get_player_deltaY(struct Model *modelPtr, UINT16 player);

void set_player_alive(struct Model *modelPtr, UINT16 player, UINT8 alive);
UINT8 get_player_alive(struct Model *modelPtr, UINT16 player);

void set_enemy_cor(struct Model *modelPtr, UINT16 enemy, UINT16 x, UINT16 y);
UINT16 get_enemy_posX(struct Model *modelPtr, UINT16 enemy);
UINT16 get_enemy_posY(struct Model *modelPtr, UINT16 enemy);

void generate_enemy(struct Model *modelPtr, UINT16 enemy);

void set_enemy_deltaX(struct Model *modelPtr, UINT16 enemy, UINT16 deltaX);
UINT16 get_enemy_deltaX(struct Model *modelPtr, UINT16 enemy);

void printModel(struct Model *modelPtr);
# 10 "./klingon.h" 2
# 1 "./events.h" 1
# 1 "./model.h" 1
# 10 "./events.h" 2



UINT8 move_player_ship(struct Model *modelPtr, UINT16 player);

void move_enemy_ship(struct Model *modelPtr, UINT16 enemy);

void request_player_move(struct Model *modelPtr, UINT16 player, UINT8 direction);

void collision(struct Model *modelPtr, UINT16 enemy, UINT16 player);

UINT8 game_over(struct Model *modelPtr);

int enemy_collision(struct Model *modelPtr, int enemyY, UINT16 enemy);
# 11 "./klingon.h" 2
# 1 "./renderer.h" 1
# 1 "./raster.h" 1
# 1 "./bitmaps.h" 1
# 1 "./globals.h" 1
# 10 "./bitmaps.h" 2


extern const UINT8 empty[];
extern const UINT8 en_ship[];
extern const UINT8 p1_ship[];
extern const UINT8 fat[];
extern const UINT8 splash[];
extern const UINT8 rocket_left[];
extern const UINT8 rocket_right[];
extern const UINT8 rocket_empty[];
# 10 "./raster.h" 2
# 1 "./clr_qk.h" 1
# 10 "./clr_qk.h"
void clr_scrn(long *base);
# 11 "./raster.h" 2
# 1 "./globals.h" 1
# 12 "./raster.h" 2


void plot_pixel(UINT8 *base, int x, int y);
void print_line(UINT8 *base, int x0, int y0, int x1, int y1);
void print_char(UINT8 *base, int x, int y, char ch);
void print_string(UINT8 *base, int x, int y, char *str);
void print_num(UINT8 *base, int x, int y, UINT16 num);
void print_clr_num(UINT8 *base, int x, int y);
void clear_screen(long *base);
void plot_bitmap_64_byte(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
# 10 "./renderer.h" 2
# 1 "./model.h" 1
# 11 "./renderer.h" 2
# 1 "./bitmaps.h" 1
# 12 "./renderer.h" 2
# 1 "./globals.h" 1
# 13 "./renderer.h" 2



void init_render(UINT8 *base);
void render_model(struct Model *modelPtr, UINT8 *base, UINT8 has_moved);
void render_ship(struct Model *modelPtr, UINT8 *base, UINT8 ship, UINT16 ship_num);
void render_score(struct Model *modelPtr, UINT8 *base);
void render_line(UINT8 *base);
# 12 "./klingon.h" 2
# 1 "./globals.h" 1
# 13 "./klingon.h" 2
# 1 "./music.h" 1
# 1 "./PSG.h" 1
# 1 "./globals.h" 1
# 9 "./PSG.h" 2
# 119 "./PSG.h"
void write_psg(int reg, UINT8 val);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
# 10 "./music.h" 2
# 1 "./globals.h" 1
# 11 "./music.h" 2


void start_sound();
UINT8 update_music(UINT32 time_elapsed);
# 14 "./klingon.h" 2
# 1 "./effects.h" 1
# 10 "./effects.h"
void thruster();
void stop_thruster();
void explosion();
# 15 "./klingon.h" 2
# 1 "./sys.h" 1
# 1 "./globals.h" 1
# 10 "./sys.h" 2


void kbd_isr();
UINT16* get_video_base();
void set_video_base(UINT16 *base);

void vbl_isr();
# 16 "./klingon.h" 2




void play_klingon();
typedef void (*Vector)();
Vector install_vector(int num, Vector vector);
# 13 "klingon.c" 2


Vector install_vector(int num, Vector vector);

UINT8 buffer[35256];

struct Model game;
struct Model *gamePtr = &game;

int music_ticks = 0;
int score_ticks = 0;
int enemy_ticks = 0;
int render_request = 1;
UINT8 has_moved = 1;

void play_klingon() {
	long old_ssp;
	Vector orig_vector;
	Vector main_vector;
	UINT8 ch;
	UINT8 switchBase = 0;

    UINT8 *base = (UINT8 *)get_video_base();
	UINT8 *base2 = buffer;

	base2 = (UINT8*)((UINT32)base2 + (256 - ((UINT32)base2) & 255));

	init_model(gamePtr);

	srand(time(0));

	orig_vector = install_vector(28 , vbl_isr);

	old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
	start_sound();
	_trap_1_wl((short)0x20,(long)(old_ssp)) ;

	while(!game_over(gamePtr)) {


	if(buffer_full()){
		ch = get_input();
		request_player_move(gamePtr, 0, ch);
	}
		if(render_request == 1) {
			if(switchBase) {
				render_model(gamePtr, base, has_moved);
				set_video_base((UINT16*)base);
			}
			else {
				render_model(gamePtr, base2, has_moved);
				set_video_base((UINT16*)base2);
			}

			switchBase = !switchBase;
			render_request = 0;
		}

		old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;


		stop_thruster();
		_trap_1_wl((short)0x20,(long)(old_ssp)) ;
	}

	old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
	stop_sound();
	explosion();
	_trap_1_wl((short)0x20,(long)(old_ssp)) ;


	install_vector(28 , orig_vector);

	render_model(gamePtr, base, has_moved);
	set_video_base((UINT16*)base);

}

Vector install_vector(int num, Vector vector) {
	Vector orig;
	Vector *vectp = (Vector *)((long)num << 2);
	long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;

	orig = *vectp;
	*vectp = vector;

	_trap_1_wl((short)0x20,(long)(old_ssp)) ;
	return orig;
}




void do_VBL_ISR() {
	int i = 0;

	music_ticks++;
	if (update_music(music_ticks)){
		music_ticks = 0;
	}

	score_ticks++;
	if(score_ticks >= 70){
		update_score(gamePtr, 1);
		score_ticks = 0;
	}

	has_moved = move_player_ship(gamePtr, 0);
	if(has_moved){
		thruster();
	}

	enemy_ticks++;
	for(i = 0; i < 6  && enemy_ticks >= 10; i++) {
		move_enemy_ship(gamePtr, i);
		collision(gamePtr,i,0);
	}
	if(enemy_ticks >= 10) {
		enemy_ticks = 0;
	}

	render_request = 1;
}
