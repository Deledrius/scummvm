/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         HYPNO_ARC_STYPE
/* Substitute the variable and function names.  */
#define yyparse         HYPNO_ARC_parse
#define yylex           HYPNO_ARC_lex
#define yyerror         HYPNO_ARC_error
#define yydebug         HYPNO_ARC_debug
#define yynerrs         HYPNO_ARC_nerrs
#define yylval          HYPNO_ARC_lval
#define yychar          HYPNO_ARC_char

/* First part of user prologue.  */
#line 27 "engines/hypno/grammar_arc.y"


#include "common/array.h"
#include "hypno/hypno.h"

#undef yyerror
#define yyerror	 HYPNO_ARC_xerror

Hypno::Shoot *shoot;

extern int HYPNO_ARC_lex();
extern int HYPNO_ARC_lineno;
uint32 HYPNO_ARC_default_sound_rate = 0;

void HYPNO_ARC_xerror(const char *str) {
	error("%s at line %d", str, HYPNO_ARC_lineno);
}

int HYPNO_ARC_wrap() {
	return 1;
}

using namespace Hypno;


#line 105 "engines/hypno/grammar_arc.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "tokens_arc.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NAME = 3,                       /* NAME  */
  YYSYMBOL_FILENAME = 4,                   /* FILENAME  */
  YYSYMBOL_BNTOK = 5,                      /* BNTOK  */
  YYSYMBOL_SNTOK = 6,                      /* SNTOK  */
  YYSYMBOL_KNTOK = 7,                      /* KNTOK  */
  YYSYMBOL_YXTOK = 8,                      /* YXTOK  */
  YYSYMBOL_FNTOK = 9,                      /* FNTOK  */
  YYSYMBOL_ENCTOK = 10,                    /* ENCTOK  */
  YYSYMBOL_ONTOK = 11,                     /* ONTOK  */
  YYSYMBOL_NUM = 12,                       /* NUM  */
  YYSYMBOL_BYTE = 13,                      /* BYTE  */
  YYSYMBOL_COMMENT = 14,                   /* COMMENT  */
  YYSYMBOL_AVTOK = 15,                     /* AVTOK  */
  YYSYMBOL_ABTOK = 16,                     /* ABTOK  */
  YYSYMBOL_CTOK = 17,                      /* CTOK  */
  YYSYMBOL_DTOK = 18,                      /* DTOK  */
  YYSYMBOL_HTOK = 19,                      /* HTOK  */
  YYSYMBOL_HETOK = 20,                     /* HETOK  */
  YYSYMBOL_HLTOK = 21,                     /* HLTOK  */
  YYSYMBOL_H12TOK = 22,                    /* H12TOK  */
  YYSYMBOL_HUTOK = 23,                     /* HUTOK  */
  YYSYMBOL_RETTOK = 24,                    /* RETTOK  */
  YYSYMBOL_QTOK = 25,                      /* QTOK  */
  YYSYMBOL_RESTOK = 26,                    /* RESTOK  */
  YYSYMBOL_PTOK = 27,                      /* PTOK  */
  YYSYMBOL_FTOK = 28,                      /* FTOK  */
  YYSYMBOL_TTOK = 29,                      /* TTOK  */
  YYSYMBOL_TATOK = 30,                     /* TATOK  */
  YYSYMBOL_TPTOK = 31,                     /* TPTOK  */
  YYSYMBOL_ATOK = 32,                      /* ATOK  */
  YYSYMBOL_VTOK = 33,                      /* VTOK  */
  YYSYMBOL_OTOK = 34,                      /* OTOK  */
  YYSYMBOL_LTOK = 35,                      /* LTOK  */
  YYSYMBOL_MTOK = 36,                      /* MTOK  */
  YYSYMBOL_NTOK = 37,                      /* NTOK  */
  YYSYMBOL_NSTOK = 38,                     /* NSTOK  */
  YYSYMBOL_RTOK = 39,                      /* RTOK  */
  YYSYMBOL_R01TOK = 40,                    /* R01TOK  */
  YYSYMBOL_ITOK = 41,                      /* ITOK  */
  YYSYMBOL_I1TOK = 42,                     /* I1TOK  */
  YYSYMBOL_GTOK = 43,                      /* GTOK  */
  YYSYMBOL_JTOK = 44,                      /* JTOK  */
  YYSYMBOL_J0TOK = 45,                     /* J0TOK  */
  YYSYMBOL_KTOK = 46,                      /* KTOK  */
  YYSYMBOL_UTOK = 47,                      /* UTOK  */
  YYSYMBOL_ZTOK = 48,                      /* ZTOK  */
  YYSYMBOL_NONETOK = 49,                   /* NONETOK  */
  YYSYMBOL_A0TOK = 50,                     /* A0TOK  */
  YYSYMBOL_P0TOK = 51,                     /* P0TOK  */
  YYSYMBOL_WTOK = 52,                      /* WTOK  */
  YYSYMBOL_XTOK = 53,                      /* XTOK  */
  YYSYMBOL_CB3TOK = 54,                    /* CB3TOK  */
  YYSYMBOL_C02TOK = 55,                    /* C02TOK  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_start = 57,                     /* start  */
  YYSYMBOL_58_1 = 58,                      /* $@1  */
  YYSYMBOL_header = 59,                    /* header  */
  YYSYMBOL_hline = 60,                     /* hline  */
  YYSYMBOL_enc = 61,                       /* enc  */
  YYSYMBOL_flag = 62,                      /* flag  */
  YYSYMBOL_body = 63,                      /* body  */
  YYSYMBOL_bline = 64                      /* bline  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined HYPNO_ARC_STYPE_IS_TRIVIAL && HYPNO_ARC_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   191

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  200

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if HYPNO_ARC_DEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    78,    79,    82,    83,    84,    87,    91,
      95,    99,   100,   101,   105,   110,   111,   112,   117,   127,
     136,   141,   146,   151,   152,   156,   160,   163,   167,   170,
     171,   197,   219,   225,   230,   235,   241,   246,   251,   256,
     261,   266,   273,   274,   277,   278,   281,   282,   283,   286,
     294,   297,   300,   303,   308,   313,   317,   321,   325,   329,
     333,   337,   341,   345,   349,   353,   357,   361,   365,   369,
     373,   377,   381,   385,   389,   393,   397,   400,   404,   409,
     413,   418,   423,   427,   433,   437,   440,   441,   444,   448,
     451,   456,   459,   463,   467,   476,   477,   480,   483,   486,
     489
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if HYPNO_ARC_DEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NAME", "FILENAME",
  "BNTOK", "SNTOK", "KNTOK", "YXTOK", "FNTOK", "ENCTOK", "ONTOK", "NUM",
  "BYTE", "COMMENT", "AVTOK", "ABTOK", "CTOK", "DTOK", "HTOK", "HETOK",
  "HLTOK", "H12TOK", "HUTOK", "RETTOK", "QTOK", "RESTOK", "PTOK", "FTOK",
  "TTOK", "TATOK", "TPTOK", "ATOK", "VTOK", "OTOK", "LTOK", "MTOK", "NTOK",
  "NSTOK", "RTOK", "R01TOK", "ITOK", "I1TOK", "GTOK", "JTOK", "J0TOK",
  "KTOK", "UTOK", "ZTOK", "NONETOK", "A0TOK", "P0TOK", "WTOK", "XTOK",
  "CB3TOK", "C02TOK", "$accept", "start", "$@1", "header", "hline", "enc",
  "flag", "body", "bline", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-114)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      10,  -114,    10,    16,    90,  -114,  -114,     6,    13,     7,
       9,    26,    65,    15,    30,    32,    42,    90,    44,    45,
      46,     0,    48,    18,    49,    -3,    50,    55,    59,    63,
      66,    67,    69,    57,    29,    90,  -114,    70,    73,  -114,
    -114,    75,    77,    86,    87,    91,    93,    94,   104,   113,
     118,  -114,   121,   122,  -114,   123,   124,    98,   126,   127,
     128,  -114,   129,  -114,  -114,  -114,  -114,  -114,  -114,   130,
     119,  -114,  -114,   141,  -114,   133,   134,   135,   136,   137,
     138,   139,   140,   142,   143,  -114,  -114,  -114,  -114,    70,
     149,  -114,  -114,  -114,   144,    -4,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
     145,   146,   155,   148,     2,   150,   151,   152,   153,   154,
      -4,   157,   156,   158,   159,   160,   161,  -114,   162,   163,
      47,  -114,   164,   165,   166,  -114,   167,   168,   169,   114,
      -4,  -114,   170,    70,   171,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,   172,   173,  -114,   174,
     175,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,   176,   177,   178,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     2,     0,     0,     7,     4,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,    30,    43,    19,     8,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,     9,     0,     0,     0,     0,     0,
       0,    16,     0,    13,    24,    25,    26,    27,    28,     0,
       0,     5,    42,    45,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,    11,    22,    23,    43,
       0,    12,    15,    17,     0,    48,    44,    31,    35,    41,
      38,    37,    39,    36,    32,    33,    40,    34,    21,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,     0,    97,     0,     0,     0,    98,    99,     0,     0,
       0,    95,     0,     0,     0,   100,     0,     0,     0,     0,
      48,    14,     0,    43,     0,    49,    53,    50,    51,    84,
      88,    85,    47,    54,    96,    86,     0,    90,    91,     0,
       0,    55,    56,    71,    58,    59,    62,    69,    68,    60,
      72,    57,    67,    73,    74,    66,    70,    63,    61,    64,
      65,    75,    76,    52,    92,     0,     0,    87,     3,    46,
      80,    94,    81,    83,    89,    78,    79,    93,    77,    82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,   189,  -114,    -9,  -114,   -89,  -114,  -113,  -114
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,    34,    35,    73,    97,   139,   140
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     108,   111,   112,   113,    55,   114,   145,   152,    51,    60,
      36,   115,   116,   117,   118,   119,     6,    37,     1,    38,
     120,    39,    58,    61,   121,   122,    71,   189,    47,   123,
     124,   125,   126,   127,     2,   128,   129,   130,    40,   131,
     132,   133,   134,    48,   135,    49,   136,   137,   138,    56,
     161,   146,   162,   163,   191,    50,    52,    53,    54,    63,
      57,    59,    62,    64,   164,   165,   166,    65,    41,    69,
      66,    67,   167,    68,   168,   169,   170,    70,    42,   171,
      72,   172,   173,   174,   175,    74,   176,    75,   177,    76,
     178,   179,    43,   180,   181,     7,     8,    44,    77,    78,
      45,     9,    89,    79,    46,    80,    81,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    82,    19,    20,    21,
      22,    23,    24,    25,    26,    83,    27,    28,    29,    30,
      84,    31,    32,    85,    86,    87,    88,    33,    90,    91,
      92,    93,    94,    95,    96,    98,    99,   100,   101,   102,
     103,   104,   105,   109,   106,   107,   110,   141,   142,   143,
     144,   153,   147,   148,   149,   150,   151,   188,   154,     0,
     155,   156,   157,   158,   159,   160,   182,   183,   184,   185,
     186,   187,   190,   192,   193,   194,   195,   196,   197,   198,
     199,     5
};

static const yytype_int16 yycheck[] =
{
      89,     5,     6,     7,     4,     9,     4,   120,    17,    12,
       4,    15,    16,    17,    18,    19,     0,     4,     8,    12,
      24,    12,     4,    26,    28,    29,    35,   140,    13,    33,
      34,    35,    36,    37,    24,    39,    40,    41,    12,    43,
      44,    45,    46,    13,    48,    13,    50,    51,    52,    49,
       3,    49,     5,     6,   143,    13,    12,    12,    12,     4,
      12,    12,    12,     4,    17,    18,    19,     4,     3,    12,
       4,     4,    25,     4,    27,    28,    29,    48,    13,    32,
      10,    34,    35,    36,    37,    12,    39,    12,    41,    12,
      43,    44,    27,    46,    47,     5,     6,    32,    12,    12,
      35,    11,     4,    12,    39,    12,    12,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    12,    27,    28,    29,
      30,    31,    32,    33,    34,    12,    36,    37,    38,    39,
      12,    41,    42,    12,    12,    12,    12,    47,    12,    12,
      12,    12,    12,    24,     3,    12,    12,    12,    12,    12,
      12,    12,    12,     4,    12,    12,    12,    12,    12,     4,
      12,     4,    12,    12,    12,    12,    12,    53,    12,    -1,
      12,    12,    12,    12,    12,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    12,    12,
      12,     2
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    24,    57,    58,    57,     0,     5,     6,    11,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    27,
      28,    29,    30,    31,    32,    33,    34,    36,    37,    38,
      39,    41,    42,    47,    59,    60,     4,     4,    12,    12,
      12,     3,    13,    27,    32,    35,    39,    13,    13,    13,
      13,    59,    12,    12,    12,     4,    49,    12,     4,    12,
      12,    26,    12,     4,     4,     4,     4,     4,     4,    12,
      48,    59,    10,    61,    12,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    12,     4,
      12,    12,    12,    12,    12,    24,     3,    62,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    61,     4,
      12,     5,     6,     7,     9,    15,    16,    17,    18,    19,
      24,    28,    29,    33,    34,    35,    36,    37,    39,    40,
      41,    43,    44,    45,    46,    48,    50,    51,    52,    63,
      64,    12,    12,     4,    12,     4,    49,    12,    12,    12,
      12,    12,    63,     4,    12,    12,    12,    12,    12,    12,
      12,     3,     5,     6,    17,    18,    19,    25,    27,    28,
      29,    32,    34,    35,    36,    37,    39,    41,    43,    44,
      46,    47,    12,    12,    12,    12,    12,    12,    53,    63,
      12,    61,    12,    12,    12,    12,    12,    12,    12,    12
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    58,    57,    57,    59,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    61,    61,    62,    62,    63,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     7,     2,     2,     2,     0,     2,     2,
       2,     3,     3,     2,     5,     3,     2,     3,     3,     2,
       4,     4,     3,     3,     2,     2,     2,     2,     2,     3,
       2,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     1,     0,     1,     0,     2,     2,     0,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     2,     3,
       2,     2,     2,     3,     3,     1,     2,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = HYPNO_ARC_EMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == HYPNO_ARC_EMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use HYPNO_ARC_error or HYPNO_ARC_UNDEF. */
#define YYERRCODE HYPNO_ARC_UNDEF


/* Enable debugging if requested.  */
#if HYPNO_ARC_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !HYPNO_ARC_DEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !HYPNO_ARC_DEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = HYPNO_ARC_EMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == HYPNO_ARC_EMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= HYPNO_ARC_EOF)
    {
      yychar = HYPNO_ARC_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == HYPNO_ARC_error)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = HYPNO_ARC_UNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = HYPNO_ARC_EMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 78 "engines/hypno/grammar_arc.y"
             { g_parsedArc->mode = (yyvsp[0].s); }
#line 1280 "engines/hypno/grammar_arc.cpp"
    break;

  case 8: /* hline: CTOK NUM  */
#line 87 "engines/hypno/grammar_arc.y"
                 {
		g_parsedArc->id = (yyvsp[0].i);
		HYPNO_ARC_default_sound_rate = 0;
		debugC(1, kHypnoDebugParser, "C %d", (yyvsp[0].i)); }
#line 1289 "engines/hypno/grammar_arc.cpp"
    break;

  case 9: /* hline: FTOK NUM  */
#line 91 "engines/hypno/grammar_arc.y"
                   {
		HYPNO_ARC_default_sound_rate = (yyvsp[0].i);
		debugC(1, kHypnoDebugParser, "F %d", (yyvsp[0].i));
	}
#line 1298 "engines/hypno/grammar_arc.cpp"
    break;

  case 10: /* hline: DTOK NUM  */
#line 95 "engines/hypno/grammar_arc.y"
                    {
		g_parsedArc->frameDelay = (yyvsp[0].i);
		debugC(1, kHypnoDebugParser, "D %d", (yyvsp[0].i));
	}
#line 1307 "engines/hypno/grammar_arc.cpp"
    break;

  case 11: /* hline: PTOK NUM NUM  */
#line 99 "engines/hypno/grammar_arc.y"
                       { debugC(1, kHypnoDebugParser, "P %d %d", (yyvsp[-1].i), (yyvsp[0].i)); }
#line 1313 "engines/hypno/grammar_arc.cpp"
    break;

  case 12: /* hline: ATOK NUM NUM  */
#line 100 "engines/hypno/grammar_arc.y"
                       { debugC(1, kHypnoDebugParser, "A %d %d", (yyvsp[-1].i), (yyvsp[0].i)); }
#line 1319 "engines/hypno/grammar_arc.cpp"
    break;

  case 13: /* hline: MTOK FILENAME  */
#line 101 "engines/hypno/grammar_arc.y"
                        {
		debugC(1, kHypnoDebugParser, "M %s", (yyvsp[0].s));
		g_parsedArc->maskVideo = (yyvsp[0].s);
	}
#line 1328 "engines/hypno/grammar_arc.cpp"
    break;

  case 14: /* hline: UTOK NUM NUM NUM NUM  */
#line 105 "engines/hypno/grammar_arc.y"
                               {
		debugC(1, kHypnoDebugParser, "U %d %d %d %d", (yyvsp[-3].i), (yyvsp[-2].i), (yyvsp[-1].i), (yyvsp[0].i));
		ScriptInfo si((yyvsp[-3].i), (yyvsp[-2].i), (yyvsp[-1].i), (yyvsp[0].i));
		g_parsedArc->script.push_back(si);
	}
#line 1338 "engines/hypno/grammar_arc.cpp"
    break;

  case 15: /* hline: VTOK NUM NUM  */
#line 110 "engines/hypno/grammar_arc.y"
                       { debugC(1, kHypnoDebugParser, "V %d %d", (yyvsp[-1].i), (yyvsp[0].i)); }
#line 1344 "engines/hypno/grammar_arc.cpp"
    break;

  case 16: /* hline: VTOK RESTOK  */
#line 111 "engines/hypno/grammar_arc.y"
                      { debugC(1, kHypnoDebugParser, "V 320,200"); }
#line 1350 "engines/hypno/grammar_arc.cpp"
    break;

  case 17: /* hline: OTOK NUM NUM  */
#line 112 "engines/hypno/grammar_arc.y"
                       {
		g_parsedArc->objKillsRequired[0] = (yyvsp[-1].i);
		g_parsedArc->objMissesAllowed[0] = (yyvsp[0].i);
		debugC(1, kHypnoDebugParser, "O %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1360 "engines/hypno/grammar_arc.cpp"
    break;

  case 18: /* hline: ONTOK NUM NUM  */
#line 117 "engines/hypno/grammar_arc.y"
                        {
		if (Common::String("O0") == (yyvsp[-2].s)) {
			g_parsedArc->objKillsRequired[0] = (yyvsp[-1].i);
			g_parsedArc->objMissesAllowed[0] = (yyvsp[0].i);
		} else if (Common::String("O1") == (yyvsp[-2].s)) {
			g_parsedArc->objKillsRequired[1] = (yyvsp[-1].i);
			g_parsedArc->objMissesAllowed[1] = (yyvsp[0].i);
		} else
			error("Invalid objective: '%s'", (yyvsp[-2].s));
		debugC(1, kHypnoDebugParser, "ON %d %d", (yyvsp[-1].i), (yyvsp[0].i)); }
#line 1375 "engines/hypno/grammar_arc.cpp"
    break;

  case 19: /* hline: ONTOK NUM  */
#line 127 "engines/hypno/grammar_arc.y"
                    {
		if (Common::String("O0") == (yyvsp[-1].s)) {
			g_parsedArc->objKillsRequired[0] = (yyvsp[0].i);
		} else if (Common::String("O1") == (yyvsp[-1].s)) {
			g_parsedArc->objKillsRequired[1] = (yyvsp[0].i);
		} else
			error("Invalid objective: '%s'", (yyvsp[-1].s));
		debugC(1, kHypnoDebugParser, "ON %d", (yyvsp[0].i));
	}
#line 1389 "engines/hypno/grammar_arc.cpp"
    break;

  case 20: /* hline: TPTOK FILENAME NUM FILENAME  */
#line 136 "engines/hypno/grammar_arc.y"
                                      {
		ArcadeTransition at((yyvsp[-2].s), (yyvsp[0].s), "", (yyvsp[-1].i));
		g_parsedArc->transitions.push_back(at);
		debugC(1, kHypnoDebugParser, "Tp %s %d %s", (yyvsp[-2].s), (yyvsp[-1].i), (yyvsp[0].s));
	}
#line 1399 "engines/hypno/grammar_arc.cpp"
    break;

  case 21: /* hline: TATOK NUM FILENAME enc  */
#line 141 "engines/hypno/grammar_arc.y"
                                 {
		ArcadeTransition at("", "", (yyvsp[-1].s), (yyvsp[-2].i));
		g_parsedArc->transitions.push_back(at);
		debugC(1, kHypnoDebugParser, "Ta %d %s", (yyvsp[-2].i), (yyvsp[-1].s));
	}
#line 1409 "engines/hypno/grammar_arc.cpp"
    break;

  case 22: /* hline: TTOK FILENAME NUM  */
#line 146 "engines/hypno/grammar_arc.y"
                            {
		ArcadeTransition at((yyvsp[-1].s), "", "", (yyvsp[0].i));
		g_parsedArc->transitions.push_back(at);
		debugC(1, kHypnoDebugParser, "T %s %d", (yyvsp[-1].s), (yyvsp[0].i));
	}
#line 1419 "engines/hypno/grammar_arc.cpp"
    break;

  case 23: /* hline: TTOK NONETOK NUM  */
#line 151 "engines/hypno/grammar_arc.y"
                           { debugC(1, kHypnoDebugParser, "T NONE %d", (yyvsp[0].i)); }
#line 1425 "engines/hypno/grammar_arc.cpp"
    break;

  case 24: /* hline: NTOK FILENAME  */
#line 152 "engines/hypno/grammar_arc.y"
                         {
		g_parsedArc->backgroundVideo = (yyvsp[0].s);
		debugC(1, kHypnoDebugParser, "N %s", (yyvsp[0].s));
	}
#line 1434 "engines/hypno/grammar_arc.cpp"
    break;

  case 25: /* hline: NSTOK FILENAME  */
#line 156 "engines/hypno/grammar_arc.y"
                          {
		g_parsedArc->backgroundVideo = (yyvsp[0].s);
		debugC(1, kHypnoDebugParser, "N* %s", (yyvsp[0].s));
	}
#line 1443 "engines/hypno/grammar_arc.cpp"
    break;

  case 26: /* hline: RTOK FILENAME  */
#line 160 "engines/hypno/grammar_arc.y"
                         {
		g_parsedArc->backgroundPalette = (yyvsp[0].s);
		debugC(1, kHypnoDebugParser, "R %s", (yyvsp[0].s)); }
#line 1451 "engines/hypno/grammar_arc.cpp"
    break;

  case 27: /* hline: ITOK FILENAME  */
#line 163 "engines/hypno/grammar_arc.y"
                        {
		g_parsedArc->player = (yyvsp[0].s);
		debugC(1, kHypnoDebugParser, "I %s", (yyvsp[0].s));
	}
#line 1460 "engines/hypno/grammar_arc.cpp"
    break;

  case 28: /* hline: I1TOK FILENAME  */
#line 167 "engines/hypno/grammar_arc.y"
                         {
		debugC(1, kHypnoDebugParser, "I1 %s", (yyvsp[0].s));
	}
#line 1468 "engines/hypno/grammar_arc.cpp"
    break;

  case 29: /* hline: QTOK NUM NUM  */
#line 170 "engines/hypno/grammar_arc.y"
                       { debugC(1, kHypnoDebugParser, "Q %d %d", (yyvsp[-1].i), (yyvsp[0].i)); }
#line 1474 "engines/hypno/grammar_arc.cpp"
    break;

  case 30: /* hline: BNTOK FILENAME  */
#line 171 "engines/hypno/grammar_arc.y"
                         {
		if (Common::String("B0") == (yyvsp[-1].s))
			g_parsedArc->beforeVideo = (yyvsp[0].s);
		else if (Common::String("B1") == (yyvsp[-1].s))
			g_parsedArc->additionalVideo = (yyvsp[0].s);
		else if (Common::String("B2") == (yyvsp[-1].s))
			g_parsedArc->nextLevelVideo = (yyvsp[0].s);
		else if (Common::String("B3") == (yyvsp[-1].s))
			g_parsedArc->defeatNoEnergyFirstVideo = (yyvsp[0].s);
		else if (Common::String("B4") == (yyvsp[-1].s))
			g_parsedArc->defeatMissBossVideo = (yyvsp[0].s);
		else if (Common::String("B5") == (yyvsp[-1].s))
			g_parsedArc->defeatNoEnergySecondVideo = (yyvsp[0].s);
		else if (Common::String("B6") == (yyvsp[-1].s))
			g_parsedArc->hitBoss1Video = (yyvsp[0].s);
		else if (Common::String("B7") == (yyvsp[-1].s))
			g_parsedArc->missBoss1Video = (yyvsp[0].s);
		else if (Common::String("B8") == (yyvsp[-1].s))
			g_parsedArc->hitBoss2Video = (yyvsp[0].s);
		else if (Common::String("B9") == (yyvsp[-1].s))
			g_parsedArc->missBoss2Video = (yyvsp[0].s);
		else if (Common::String("BA") == (yyvsp[-1].s))
			g_parsedArc->briefingVideo = (yyvsp[0].s);

		debugC(1, kHypnoDebugParser, "BN %s", (yyvsp[0].s));
	}
#line 1505 "engines/hypno/grammar_arc.cpp"
    break;

  case 31: /* hline: SNTOK FILENAME enc flag  */
#line 197 "engines/hypno/grammar_arc.y"
                                  {
		uint32 sampleRate = 11025;
		if (Common::String("22K") == (yyvsp[-1].s) || Common::String("22k") == (yyvsp[-1].s))
			sampleRate = 22050;
		else if (HYPNO_ARC_default_sound_rate > 0)
			sampleRate = HYPNO_ARC_default_sound_rate;

		if (Common::String("S0") == (yyvsp[-3].s)) {
			g_parsedArc->music = (yyvsp[-2].s);
			g_parsedArc->musicRate = sampleRate;
		} else if (Common::String("S1") == (yyvsp[-3].s)) {
			g_parsedArc->shootSound = (yyvsp[-2].s);
			g_parsedArc->shootSoundRate = sampleRate;
		} else if (Common::String("S2") == (yyvsp[-3].s)) {
			g_parsedArc->hitSound = (yyvsp[-2].s);
			g_parsedArc->hitSoundRate = sampleRate;
		} else if (Common::String("S4") == (yyvsp[-3].s)) {
			g_parsedArc->enemySound = (yyvsp[-2].s);
			g_parsedArc->enemySoundRate = sampleRate;
		}
		debugC(1, kHypnoDebugParser, "SN %s", (yyvsp[-2].s));
	}
#line 1532 "engines/hypno/grammar_arc.cpp"
    break;

  case 32: /* hline: HETOK BYTE NUM NUM  */
#line 219 "engines/hypno/grammar_arc.y"
                             {
		Segment segment((yyvsp[-2].i), (yyvsp[0].i), (yyvsp[-1].i));
		segment.end = true;
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "HE %x %d %d", (yyvsp[-2].i), (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1543 "engines/hypno/grammar_arc.cpp"
    break;

  case 33: /* hline: HLTOK BYTE NUM NUM  */
#line 225 "engines/hypno/grammar_arc.y"
                             {
		Segment segment((yyvsp[-2].i), (yyvsp[0].i), (yyvsp[-1].i));
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "HL %x %d %d", (yyvsp[-2].i), (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1553 "engines/hypno/grammar_arc.cpp"
    break;

  case 34: /* hline: HUTOK BYTE NUM NUM  */
#line 230 "engines/hypno/grammar_arc.y"
                             {
		Segment segment((yyvsp[-2].i), (yyvsp[0].i), (yyvsp[-1].i));
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "HU %x %d %d", (yyvsp[-2].i), (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1563 "engines/hypno/grammar_arc.cpp"
    break;

  case 35: /* hline: HTOK NAME NUM NUM  */
#line 235 "engines/hypno/grammar_arc.y"
                            {
		assert(Common::String((yyvsp[-2].s)).size() == 1);
		Segment segment((yyvsp[-2].s)[0], (yyvsp[0].i), (yyvsp[-1].i));
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "H %s %d %d", (yyvsp[-2].s), (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1574 "engines/hypno/grammar_arc.cpp"
    break;

  case 36: /* hline: HTOK RTOK NUM NUM  */
#line 241 "engines/hypno/grammar_arc.y"
                            { // Workaround for BYTE == R
		Segment segment('R', (yyvsp[0].i), (yyvsp[-1].i));
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "H R %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1584 "engines/hypno/grammar_arc.cpp"
    break;

  case 37: /* hline: HTOK ATOK NUM NUM  */
#line 246 "engines/hypno/grammar_arc.y"
                            { // Workaround for BYTE == A
		Segment segment('A', (yyvsp[0].i), (yyvsp[-1].i));
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "H A %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1594 "engines/hypno/grammar_arc.cpp"
    break;

  case 38: /* hline: HTOK PTOK NUM NUM  */
#line 251 "engines/hypno/grammar_arc.y"
                            { // Workaround for BYTE == P
		Segment segment('P', (yyvsp[0].i), (yyvsp[-1].i));
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "H P %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1604 "engines/hypno/grammar_arc.cpp"
    break;

  case 39: /* hline: HTOK LTOK NUM NUM  */
#line 256 "engines/hypno/grammar_arc.y"
                            { // Workaround for BYTE == P
		Segment segment('L', (yyvsp[0].i), (yyvsp[-1].i));
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "H P %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1614 "engines/hypno/grammar_arc.cpp"
    break;

  case 40: /* hline: H12TOK BYTE NUM NUM  */
#line 261 "engines/hypno/grammar_arc.y"
                              {
		Segment segment((yyvsp[-2].i), (yyvsp[0].i), (yyvsp[-1].i));
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "HN %x %d %d", (yyvsp[-2].i), (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1624 "engines/hypno/grammar_arc.cpp"
    break;

  case 41: /* hline: HTOK BYTE NUM NUM  */
#line 266 "engines/hypno/grammar_arc.y"
                            {
		Segment segment((yyvsp[-2].i), (yyvsp[0].i), (yyvsp[-1].i));
		g_parsedArc->segments.push_back(segment);
		debugC(1, kHypnoDebugParser, "H %x %d %d", (yyvsp[-2].i), (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1634 "engines/hypno/grammar_arc.cpp"
    break;

  case 42: /* enc: ENCTOK  */
#line 273 "engines/hypno/grammar_arc.y"
                     { (yyval.s) = (yyvsp[0].s); }
#line 1640 "engines/hypno/grammar_arc.cpp"
    break;

  case 43: /* enc: %empty  */
#line 274 "engines/hypno/grammar_arc.y"
                         { (yyval.s) = scumm_strdup(""); }
#line 1646 "engines/hypno/grammar_arc.cpp"
    break;

  case 44: /* flag: NAME  */
#line 277 "engines/hypno/grammar_arc.y"
                     { (yyval.s) = (yyvsp[0].s); }
#line 1652 "engines/hypno/grammar_arc.cpp"
    break;

  case 45: /* flag: %empty  */
#line 278 "engines/hypno/grammar_arc.y"
                         { (yyval.s) = scumm_strdup(""); }
#line 1658 "engines/hypno/grammar_arc.cpp"
    break;

  case 49: /* bline: FNTOK FILENAME  */
#line 286 "engines/hypno/grammar_arc.y"
                      {
		shoot = new Shoot();
		if (Common::String("F0") == (yyvsp[-1].s))
			shoot->animation = (yyvsp[0].s);
		else if (Common::String("F4") == (yyvsp[-1].s))
			shoot->explosionAnimation = (yyvsp[0].s);
		debugC(1, kHypnoDebugParser, "FN %s", (yyvsp[0].s));
	}
#line 1671 "engines/hypno/grammar_arc.cpp"
    break;

  case 50: /* bline: AVTOK NUM  */
#line 294 "engines/hypno/grammar_arc.y"
                    {
		debugC(1, kHypnoDebugParser, "AV %d", (yyvsp[0].i));
	}
#line 1679 "engines/hypno/grammar_arc.cpp"
    break;

  case 51: /* bline: ABTOK NUM  */
#line 297 "engines/hypno/grammar_arc.y"
                    {
		debugC(1, kHypnoDebugParser, "AB %d", (yyvsp[0].i));
	}
#line 1687 "engines/hypno/grammar_arc.cpp"
    break;

  case 52: /* bline: J0TOK NUM  */
#line 300 "engines/hypno/grammar_arc.y"
                    {
		debugC(1, kHypnoDebugParser, "J0 %d", (yyvsp[0].i));
	}
#line 1695 "engines/hypno/grammar_arc.cpp"
    break;

  case 53: /* bline: FNTOK NONETOK  */
#line 303 "engines/hypno/grammar_arc.y"
                        {
		shoot = new Shoot();
		shoot->animation = "NONE";
		debugC(1, kHypnoDebugParser, "FN NONE");
	}
#line 1705 "engines/hypno/grammar_arc.cpp"
    break;

  case 54: /* bline: FTOK FILENAME  */
#line 308 "engines/hypno/grammar_arc.y"
                        {
		shoot = new Shoot();
		shoot->animation = (yyvsp[0].s);
		debugC(1, kHypnoDebugParser, "FN %s", (yyvsp[0].s));
	}
#line 1715 "engines/hypno/grammar_arc.cpp"
    break;

  case 55: /* bline: ITOK NAME  */
#line 313 "engines/hypno/grammar_arc.y"
                     {
		shoot->name = (yyvsp[0].s);
		debugC(1, kHypnoDebugParser, "I %s", (yyvsp[0].s));
	}
#line 1724 "engines/hypno/grammar_arc.cpp"
    break;

  case 56: /* bline: ITOK BNTOK  */
#line 317 "engines/hypno/grammar_arc.y"
                      {  // Workaround for NAME == B1
		shoot->name = (yyvsp[0].s);
		debugC(1, kHypnoDebugParser, "I %s", (yyvsp[0].s));
	}
#line 1733 "engines/hypno/grammar_arc.cpp"
    break;

  case 57: /* bline: ITOK ATOK  */
#line 321 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == A
		shoot->name = "A";
		debugC(1, kHypnoDebugParser, "I A");
	}
#line 1742 "engines/hypno/grammar_arc.cpp"
    break;

  case 58: /* bline: ITOK CTOK  */
#line 325 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == C
		shoot->name = "C";
		debugC(1, kHypnoDebugParser, "I C");
	}
#line 1751 "engines/hypno/grammar_arc.cpp"
    break;

  case 59: /* bline: ITOK DTOK  */
#line 329 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == D
		shoot->name = "D";
		debugC(1, kHypnoDebugParser, "I D");
	}
#line 1760 "engines/hypno/grammar_arc.cpp"
    break;

  case 60: /* bline: ITOK FTOK  */
#line 333 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == F
		shoot->name = "F";
		debugC(1, kHypnoDebugParser, "I F");
	}
#line 1769 "engines/hypno/grammar_arc.cpp"
    break;

  case 61: /* bline: ITOK GTOK  */
#line 337 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == G
		shoot->name = "G";
		debugC(1, kHypnoDebugParser, "I G");
	}
#line 1778 "engines/hypno/grammar_arc.cpp"
    break;

  case 62: /* bline: ITOK HTOK  */
#line 341 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == H
		shoot->name = "H";
		debugC(1, kHypnoDebugParser, "I H");
	}
#line 1787 "engines/hypno/grammar_arc.cpp"
    break;

  case 63: /* bline: ITOK ITOK  */
#line 345 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == I
		shoot->name = "I";
		debugC(1, kHypnoDebugParser, "I I");
	}
#line 1796 "engines/hypno/grammar_arc.cpp"
    break;

  case 64: /* bline: ITOK JTOK  */
#line 349 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == J
		shoot->name = "J";
		debugC(1, kHypnoDebugParser, "I J");
	}
#line 1805 "engines/hypno/grammar_arc.cpp"
    break;

  case 65: /* bline: ITOK KTOK  */
#line 353 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == K
		shoot->name = "K";
		debugC(1, kHypnoDebugParser, "I K");
	}
#line 1814 "engines/hypno/grammar_arc.cpp"
    break;

  case 66: /* bline: ITOK NTOK  */
#line 357 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == N
		shoot->name = "N";
		debugC(1, kHypnoDebugParser, "I N");
	}
#line 1823 "engines/hypno/grammar_arc.cpp"
    break;

  case 67: /* bline: ITOK OTOK  */
#line 361 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == O
		shoot->name = "O";
		debugC(1, kHypnoDebugParser, "I O");
	}
#line 1832 "engines/hypno/grammar_arc.cpp"
    break;

  case 68: /* bline: ITOK PTOK  */
#line 365 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == P
		shoot->name = "P";
		debugC(1, kHypnoDebugParser, "I P");
	}
#line 1841 "engines/hypno/grammar_arc.cpp"
    break;

  case 69: /* bline: ITOK QTOK  */
#line 369 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == Q
		shoot->name = "Q";
		debugC(1, kHypnoDebugParser, "I Q");
	}
#line 1850 "engines/hypno/grammar_arc.cpp"
    break;

  case 70: /* bline: ITOK RTOK  */
#line 373 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == R
		shoot->name = "R";
		debugC(1, kHypnoDebugParser, "I R");
	}
#line 1859 "engines/hypno/grammar_arc.cpp"
    break;

  case 71: /* bline: ITOK SNTOK  */
#line 377 "engines/hypno/grammar_arc.y"
                      {  // Workaround for NAME == S1
		shoot->name = (yyvsp[0].s);
		debugC(1, kHypnoDebugParser, "I %s", (yyvsp[0].s));
	}
#line 1868 "engines/hypno/grammar_arc.cpp"
    break;

  case 72: /* bline: ITOK TTOK  */
#line 381 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == T
		shoot->name = "T";
		debugC(1, kHypnoDebugParser, "I T");
	}
#line 1877 "engines/hypno/grammar_arc.cpp"
    break;

  case 73: /* bline: ITOK LTOK  */
#line 385 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == L
		shoot->name = "L";
		debugC(1, kHypnoDebugParser, "I L");
	}
#line 1886 "engines/hypno/grammar_arc.cpp"
    break;

  case 74: /* bline: ITOK MTOK  */
#line 389 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == M
		shoot->name = "M";
		debugC(1, kHypnoDebugParser, "I M");
	}
#line 1895 "engines/hypno/grammar_arc.cpp"
    break;

  case 75: /* bline: ITOK UTOK  */
#line 393 "engines/hypno/grammar_arc.y"
                     { // Workaround for NAME == U
		shoot->name = "U";
		debugC(1, kHypnoDebugParser, "I U");
	}
#line 1904 "engines/hypno/grammar_arc.cpp"
    break;

  case 76: /* bline: JTOK NUM  */
#line 397 "engines/hypno/grammar_arc.y"
                    {
		debugC(1, kHypnoDebugParser, "J %d", (yyvsp[0].i));
	}
#line 1912 "engines/hypno/grammar_arc.cpp"
    break;

  case 77: /* bline: A0TOK NUM NUM  */
#line 400 "engines/hypno/grammar_arc.y"
                        {
		shoot->position = Common::Point((yyvsp[-1].i), (yyvsp[0].i));
		debugC(1, kHypnoDebugParser, "A0 %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1921 "engines/hypno/grammar_arc.cpp"
    break;

  case 78: /* bline: RTOK NUM NUM  */
#line 404 "engines/hypno/grammar_arc.y"
                        {
		shoot->objKillsCount = (yyvsp[-1].i);
		shoot->objMissesCount = (yyvsp[0].i);
		debugC(1, kHypnoDebugParser, "R %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1931 "engines/hypno/grammar_arc.cpp"
    break;

  case 79: /* bline: R01TOK NUM NUM  */
#line 409 "engines/hypno/grammar_arc.y"
                          {
		shoot->objKillsCount = (yyvsp[-1].i);
		shoot->objMissesCount = (yyvsp[0].i);
		debugC(1, kHypnoDebugParser, "R0/1 %d %d", (yyvsp[-1].i), (yyvsp[0].i)); }
#line 1940 "engines/hypno/grammar_arc.cpp"
    break;

  case 80: /* bline: BNTOK NUM NUM  */
#line 413 "engines/hypno/grammar_arc.y"
                        {
		FrameInfo fi((yyvsp[0].i), (yyvsp[-1].i));
		shoot->bodyFrames.push_back(fi);
		debugC(1, kHypnoDebugParser, "BN %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1950 "engines/hypno/grammar_arc.cpp"
    break;

  case 81: /* bline: KNTOK NUM NUM  */
#line 418 "engines/hypno/grammar_arc.y"
                        {
		FrameInfo fi((yyvsp[0].i), (yyvsp[-1].i));
		shoot->explosionFrames.push_back(fi);
		debugC(1, kHypnoDebugParser, "KN %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1960 "engines/hypno/grammar_arc.cpp"
    break;

  case 82: /* bline: P0TOK NUM NUM  */
#line 423 "engines/hypno/grammar_arc.y"
                        {
		shoot->paletteSize = (yyvsp[-1].i);
		shoot->paletteOffset = (yyvsp[0].i);
		debugC(1, kHypnoDebugParser, "P0 %d %d", (yyvsp[-1].i), (yyvsp[0].i)); }
#line 1969 "engines/hypno/grammar_arc.cpp"
    break;

  case 83: /* bline: OTOK NUM NUM  */
#line 427 "engines/hypno/grammar_arc.y"
                       {
		if ((yyvsp[-1].i) == 0 && (yyvsp[0].i) == 0)
			error("Invalid O command (0, 0)");
		shoot->deathPosition = Common::Point((yyvsp[-1].i), (yyvsp[0].i));
		debugC(1, kHypnoDebugParser, "O %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 1980 "engines/hypno/grammar_arc.cpp"
    break;

  case 84: /* bline: CTOK NUM  */
#line 433 "engines/hypno/grammar_arc.y"
                    {
		shoot->timesToShoot = (yyvsp[0].i);
		debugC(1, kHypnoDebugParser, "C %d", (yyvsp[0].i));
	}
#line 1989 "engines/hypno/grammar_arc.cpp"
    break;

  case 85: /* bline: HTOK NUM  */
#line 437 "engines/hypno/grammar_arc.y"
                    {
		shoot->attackFrames.push_back((yyvsp[0].i));
		debugC(1, kHypnoDebugParser, "H %d", (yyvsp[0].i)); }
#line 1997 "engines/hypno/grammar_arc.cpp"
    break;

  case 86: /* bline: VTOK NUM  */
#line 440 "engines/hypno/grammar_arc.y"
                    { debugC(1, kHypnoDebugParser, "V %d", (yyvsp[0].i)); }
#line 2003 "engines/hypno/grammar_arc.cpp"
    break;

  case 87: /* bline: WTOK NUM  */
#line 441 "engines/hypno/grammar_arc.y"
                    {
		shoot->attackWeight = (yyvsp[0].i);
		debugC(1, kHypnoDebugParser, "W %d", (yyvsp[0].i)); }
#line 2011 "engines/hypno/grammar_arc.cpp"
    break;

  case 88: /* bline: DTOK NUM  */
#line 444 "engines/hypno/grammar_arc.y"
                    {
		shoot->pointsToShoot = (yyvsp[0].i);
		debugC(1, kHypnoDebugParser, "D %d", (yyvsp[0].i));
	}
#line 2020 "engines/hypno/grammar_arc.cpp"
    break;

  case 89: /* bline: LTOK NUM NUM  */
#line 448 "engines/hypno/grammar_arc.y"
                       {
		debugC(1, kHypnoDebugParser, "L %d %d", (yyvsp[-1].i), (yyvsp[0].i));
	}
#line 2028 "engines/hypno/grammar_arc.cpp"
    break;

  case 90: /* bline: LTOK NUM  */
#line 451 "engines/hypno/grammar_arc.y"
                   {
		debugC(1, kHypnoDebugParser, "L %d", (yyvsp[0].i));
		FrameInfo fi((yyvsp[0].i)-1, 0);
		shoot->bodyFrames.push_back(fi);
	}
#line 2038 "engines/hypno/grammar_arc.cpp"
    break;

  case 91: /* bline: MTOK NUM  */
#line 456 "engines/hypno/grammar_arc.y"
                   { debugC(1, kHypnoDebugParser, "M %d", (yyvsp[0].i));
		shoot->missedAnimation = (yyvsp[0].i);
	}
#line 2046 "engines/hypno/grammar_arc.cpp"
    break;

  case 92: /* bline: KTOK NUM  */
#line 459 "engines/hypno/grammar_arc.y"
                   { debugC(1, kHypnoDebugParser, "K %d", (yyvsp[0].i));
		FrameInfo fi((yyvsp[0].i), 1);
		shoot->explosionFrames.push_back(fi);
	}
#line 2055 "engines/hypno/grammar_arc.cpp"
    break;

  case 93: /* bline: KTOK NUM NUM  */
#line 463 "engines/hypno/grammar_arc.y"
                       { debugC(1, kHypnoDebugParser, "K %d %d", (yyvsp[-1].i), (yyvsp[0].i));
		FrameInfo fi((yyvsp[-1].i), 1);
		shoot->explosionFrames.push_back(fi);
	}
#line 2064 "engines/hypno/grammar_arc.cpp"
    break;

  case 94: /* bline: SNTOK FILENAME enc  */
#line 467 "engines/hypno/grammar_arc.y"
                             {
		if (Common::String("S0") == (yyvsp[-2].s))
			shoot->enemySound = (yyvsp[-1].s);
		else if (Common::String("S1") == (yyvsp[-2].s))
			shoot->deathSound = (yyvsp[-1].s);
		else if (Common::String("S2") == (yyvsp[-2].s))
			shoot->hitSound = (yyvsp[-1].s);

		debugC(1, kHypnoDebugParser, "SN %s", (yyvsp[-1].s)); }
#line 2078 "engines/hypno/grammar_arc.cpp"
    break;

  case 95: /* bline: GTOK  */
#line 476 "engines/hypno/grammar_arc.y"
               { debugC(1, kHypnoDebugParser, "G"); }
#line 2084 "engines/hypno/grammar_arc.cpp"
    break;

  case 96: /* bline: TTOK NUM  */
#line 477 "engines/hypno/grammar_arc.y"
                   {
		debugC(1, kHypnoDebugParser, "T %d", (yyvsp[0].i));
	}
#line 2092 "engines/hypno/grammar_arc.cpp"
    break;

  case 97: /* bline: TTOK  */
#line 480 "engines/hypno/grammar_arc.y"
               {
		debugC(1, kHypnoDebugParser, "T");
	}
#line 2100 "engines/hypno/grammar_arc.cpp"
    break;

  case 98: /* bline: MTOK  */
#line 483 "engines/hypno/grammar_arc.y"
               {
		debugC(1, kHypnoDebugParser, "M");
	}
#line 2108 "engines/hypno/grammar_arc.cpp"
    break;

  case 99: /* bline: NTOK  */
#line 486 "engines/hypno/grammar_arc.y"
               {
		shoot->noEnemySound = true;
		debugC(1, kHypnoDebugParser, "N"); }
#line 2116 "engines/hypno/grammar_arc.cpp"
    break;

  case 100: /* bline: ZTOK  */
#line 489 "engines/hypno/grammar_arc.y"
               {
		g_parsedArc->shoots.push_back(*shoot);
		//delete shoot;
		//shoot = nullptr;
		debugC(1, kHypnoDebugParser, "Z");
	}
#line 2127 "engines/hypno/grammar_arc.cpp"
    break;


#line 2131 "engines/hypno/grammar_arc.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == HYPNO_ARC_EMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= HYPNO_ARC_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == HYPNO_ARC_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = HYPNO_ARC_EMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != HYPNO_ARC_EMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

