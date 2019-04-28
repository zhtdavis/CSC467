/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

/***********************************************************************
 *   Interface to the parser module for CSC467 course project.
 * 
 *   Phase 2: Implement context free grammar for source language, and
 *            parse tracing functionality.
 *   Phase 3: Construct the AST for the source language program.
 ***********************************************************************/

/***********************************************************************
 *  C Definitions and external declarations for this module.
 *
 *  Phase 3: Include ast.h if needed, and declarations for other global or
 *           external vars, functions etc. as needed.
 ***********************************************************************/

#include <string.h>
#include "common.h"
#include "ast.h"
#include "symbol.h"
#include "semantic.h"
#define YYERROR_VERBOSE
#define yTRACE(x)    { if (traceParser) fprintf(traceFile, "%s\n", x); }

void yyerror(const char* s);    /* what to do in case of error            */
int yylex();              /* procedure for calling lexical analyzer */
extern int yyline;        /* variable holding current line number   */
extern symbol_table_entry *curr_table_entry;
extern node *ast;

int if_statement_line_num;

#line 51 "parser.y" /* yacc.c:339  */

#define YYDEBUG 1

#line 103 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    myToken1 = 258,
    myToken2 = 259,
    IF = 260,
    ELSE = 261,
    LEFT_CBRACKET = 262,
    RIGHT_CBRACKET = 263,
    LEFT_BRACKET = 264,
    RIGHT_BRACKET = 265,
    LEFT_SBRACKET = 266,
    RIGHT_SBRACKET = 267,
    COMMA = 268,
    SEMI_COLUMN = 269,
    BOOL_TRUE = 270,
    BOOL_FALSE = 271,
    SINGLE_EQUAL = 272,
    BOOL = 273,
    BVEC2 = 274,
    BVEC3 = 275,
    BVEC4 = 276,
    INT = 277,
    IVEC2 = 278,
    IVEC3 = 279,
    IVEC4 = 280,
    FLOAT = 281,
    VEC2 = 282,
    VEC3 = 283,
    VEC4 = 284,
    CONST = 285,
    LIT = 286,
    DP3 = 287,
    RSQ = 288,
    WHILE = 289,
    VOID = 290,
    NOT = 291,
    EXP = 292,
    MULTI = 293,
    DIVIDE = 294,
    PLUS = 295,
    MINUS = 296,
    DOUBLE_EQUAL = 297,
    NOT_EQUAL = 298,
    LESS = 299,
    LESS_EQUAL = 300,
    GREATER = 301,
    GREATER_EQUAL = 302,
    LOGICAL_AND = 303,
    LOGICAL_OR = 304,
    IDENTIFIER = 305,
    INTEGER_LITERAL = 306,
    FLOAT_LITERAL = 307,
    NO_ELSE = 308,
    UNARY_MINUS = 309
  };
#endif
/* Tokens.  */
#define myToken1 258
#define myToken2 259
#define IF 260
#define ELSE 261
#define LEFT_CBRACKET 262
#define RIGHT_CBRACKET 263
#define LEFT_BRACKET 264
#define RIGHT_BRACKET 265
#define LEFT_SBRACKET 266
#define RIGHT_SBRACKET 267
#define COMMA 268
#define SEMI_COLUMN 269
#define BOOL_TRUE 270
#define BOOL_FALSE 271
#define SINGLE_EQUAL 272
#define BOOL 273
#define BVEC2 274
#define BVEC3 275
#define BVEC4 276
#define INT 277
#define IVEC2 278
#define IVEC3 279
#define IVEC4 280
#define FLOAT 281
#define VEC2 282
#define VEC3 283
#define VEC4 284
#define CONST 285
#define LIT 286
#define DP3 287
#define RSQ 288
#define WHILE 289
#define VOID 290
#define NOT 291
#define EXP 292
#define MULTI 293
#define DIVIDE 294
#define PLUS 295
#define MINUS 296
#define DOUBLE_EQUAL 297
#define NOT_EQUAL 298
#define LESS 299
#define LESS_EQUAL 300
#define GREATER 301
#define GREATER_EQUAL 302
#define LOGICAL_AND 303
#define LOGICAL_OR 304
#define IDENTIFIER 305
#define INTEGER_LITERAL 306
#define FLOAT_LITERAL 307
#define NO_ELSE 308
#define UNARY_MINUS 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 59 "parser.y" /* yacc.c:355  */

  int as_int;
  char *as_id;
  float as_float;
  bool as_bool;
  int as_vec;
  struct node_ *as_ast;

#line 260 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 277 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   262

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   191,   191,   197,   201,   203,   207,   209,   211,   215,
     217,   221,   223,   225,   227,   229,   233,   235,   239,   241,
     245,   247,   249,   251,   253,   255,   257,   259,   261,   263,
     265,   267,   269,   271,   273,   275,   277,   279,   281,   283,
     285,   287,   289,   291,   293,   297,   299,   303,   305,   307,
     309,   311,   313,   315,   317,   319,   321,   323,   325
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "myToken1", "myToken2", "IF", "ELSE",
  "LEFT_CBRACKET", "RIGHT_CBRACKET", "LEFT_BRACKET", "RIGHT_BRACKET",
  "LEFT_SBRACKET", "RIGHT_SBRACKET", "COMMA", "SEMI_COLUMN", "BOOL_TRUE",
  "BOOL_FALSE", "SINGLE_EQUAL", "BOOL", "BVEC2", "BVEC3", "BVEC4", "INT",
  "IVEC2", "IVEC3", "IVEC4", "FLOAT", "VEC2", "VEC3", "VEC4", "CONST",
  "LIT", "DP3", "RSQ", "WHILE", "VOID", "NOT", "EXP", "MULTI", "DIVIDE",
  "PLUS", "MINUS", "DOUBLE_EQUAL", "NOT_EQUAL", "LESS", "LESS_EQUAL",
  "GREATER", "GREATER_EQUAL", "LOGICAL_AND", "LOGICAL_OR", "IDENTIFIER",
  "INTEGER_LITERAL", "FLOAT_LITERAL", "NO_ELSE", "UNARY_MINUS", "$accept",
  "program", "scope", "declarations", "declaration", "statements",
  "statement", "arguments_opt", "arguments", "expression", "variable",
  "type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

#define YYPACT_NINF -46

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-46)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,   -46,     9,   -46,   185,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   137,   -46,
      15,   -39,   -18,    21,   -46,   -46,    20,   -46,   -46,    16,
     -13,    17,    71,   -16,    71,   -46,    71,    71,    71,   -46,
     -46,    27,    28,    31,    71,    71,   -46,   -46,    29,   -46,
      33,    26,   104,   140,   153,    91,    71,    71,    71,   -46,
     -46,     7,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,   -46,   -46,   -46,   -46,
     -46,    46,    45,   179,    49,    51,    56,    42,    42,    42,
     -31,   -31,   204,   204,   204,   204,   204,   204,   215,   192,
      -8,   -46,    71,   -46,   -46,     7,   -46,   179,   -46
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     2,    10,     1,    51,    52,    53,    54,
      47,    48,    49,    50,    55,    56,    57,    58,     0,     4,
       0,     0,     0,     0,     3,    15,    45,    14,     9,     0,
       0,     0,     0,     0,     0,     6,     0,     0,     0,    26,
      27,     0,     0,     0,     0,     0,    24,    25,     0,    28,
       0,     0,     0,     0,     0,     0,    17,    17,    17,    29,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,    11,     7,     8,
      44,     0,    16,    19,     0,     0,    12,    43,    41,    42,
      39,    40,    33,    34,    35,    36,    37,    38,    31,    32,
       0,    22,     0,    21,    23,     0,    20,    18,    13
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -46,   -46,    63,   -46,   -46,   -46,   -45,   -30,   -11,   -19,
     -20,     6
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    27,     4,    19,    20,    28,    81,    82,    83,
      49,    50
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      29,    35,   106,     1,    36,   102,    62,    63,    64,     5,
      21,    30,    23,    48,     1,    52,    86,    53,    54,    55,
      23,    25,     1,    24,    22,    59,    60,    84,    85,    25,
      32,    33,    31,    34,    37,    51,    56,    57,    76,    61,
      58,    29,    75,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   101,    26,   102,   103,
     108,   104,   105,     3,   100,    26,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    62,
      38,     0,     0,   107,     0,    29,    39,    40,     0,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    80,    41,    42,    43,     0,     0,    44,     0,     0,
       0,     0,    45,     0,     0,     0,     0,     0,    77,     0,
       0,    26,    46,    47,     0,     0,     0,     0,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    78,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72
};

static const yytype_int8 yycheck[] =
{
      20,    14,    10,     7,    17,    13,    37,    38,    39,     0,
       4,    50,     5,    32,     7,    34,    61,    36,    37,    38,
       5,    14,     7,     8,    18,    44,    45,    57,    58,    14,
       9,    11,    50,    17,    17,    51,     9,     9,    12,    10,
       9,    61,     9,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    10,    50,    13,    10,
     105,    10,     6,     0,    75,    50,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    37,
       9,    -1,    -1,   102,    -1,   105,    15,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    10,    31,    32,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    50,    51,    52,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    14,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    56,    57,    58,     0,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    59,
      60,    66,    66,     5,     8,    14,    50,    57,    61,    65,
      50,    50,     9,    11,    17,    14,    17,    17,     9,    15,
      16,    31,    32,    33,    36,    41,    51,    52,    64,    65,
      66,    51,    64,    64,    64,    64,     9,     9,     9,    64,
      64,    10,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,     9,    12,    14,    14,    14,
      10,    62,    63,    64,    62,    62,    61,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      63,    10,    13,    10,    10,     6,    10,    64,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    58,    58,    59,    59,    59,    60,
      60,    61,    61,    61,    61,    61,    62,    62,    63,    63,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    65,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     4,     2,     0,     3,     5,     6,     2,
       0,     4,     5,     7,     1,     1,     1,     0,     3,     1,
       4,     4,     4,     4,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 191 "parser.y" /* yacc.c:1646  */
    { yTRACE("program -> scope") 
			  ast = (yyvsp[0].as_ast); 
			  add_pre_defined_variable_entry();
  			  semantic_check(ast); }
#line 1464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 197 "parser.y" /* yacc.c:1646  */
    { yTRACE("scope -> { declarations statements }") 
															  (yyval.as_ast) = ast_allocate(SCOPE_NODE, (yyvsp[-2].as_ast), (yyvsp[-1].as_ast)); }
#line 1471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 201 "parser.y" /* yacc.c:1646  */
    { yTRACE("declarations -> declarations declaration") 
								  (yyval.as_ast) = ast_allocate(DECLARATIONS_NODE, (yyvsp[-1].as_ast), (yyvsp[0].as_ast)); }
#line 1478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 203 "parser.y" /* yacc.c:1646  */
    { yTRACE("declarations -> NULL") 
								  (yyval.as_ast) = NULL; }
#line 1485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 207 "parser.y" /* yacc.c:1646  */
    { yTRACE("declaration -> type IDENTIFIER ;") 
																  (yyval.as_ast) = ast_allocate(DECLARATION_NODE, 0, (yyvsp[-2].as_ast), (yyvsp[-1].as_id), NULL, yyline); }
#line 1492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 209 "parser.y" /* yacc.c:1646  */
    { yTRACE("declaration -> type IDENTIFIER = expression ;")
																  (yyval.as_ast) = ast_allocate(DECLARATION_NODE, 0, (yyvsp[-4].as_ast), (yyvsp[-3].as_id), (yyvsp[-1].as_ast), yyline); }
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 211 "parser.y" /* yacc.c:1646  */
    { yTRACE("declaration -> CONST type IDENTIFIER = expression ;") 
																  (yyval.as_ast) = ast_allocate(DECLARATION_NODE, 1, (yyvsp[-4].as_ast), (yyvsp[-3].as_id), (yyvsp[-1].as_ast), yyline); }
#line 1506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 215 "parser.y" /* yacc.c:1646  */
    { yTRACE("statements -> statements statement") 
							  (yyval.as_ast) = ast_allocate(STATEMENTS_NODE, (yyvsp[-1].as_ast), (yyvsp[0].as_ast)); }
#line 1513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 217 "parser.y" /* yacc.c:1646  */
    { yTRACE("statements -> NULL") 
							  (yyval.as_ast) = NULL; }
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 221 "parser.y" /* yacc.c:1646  */
    { yTRACE("statement -> variable = expression ;") 
																		  (yyval.as_ast) = ast_allocate(ASSIGNMENT_NODE, (yyvsp[-3].as_ast), (yyvsp[-1].as_ast), yyline); }
#line 1527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 223 "parser.y" /* yacc.c:1646  */
    { yTRACE("statement -> IF ( expression ) statement") 
																		  (yyval.as_ast) = ast_allocate(IF_STATEMENT_NODE, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), NULL); }
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 225 "parser.y" /* yacc.c:1646  */
    { yTRACE("statement -> IF ( expression ) statement ELSE statement") 
																		  (yyval.as_ast) = ast_allocate(IF_STATEMENT_NODE, (yyvsp[-4].as_ast), (yyvsp[-2].as_ast), (yyvsp[0].as_ast)); }
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 227 "parser.y" /* yacc.c:1646  */
    { yTRACE("statement -> scope") 
																		  (yyval.as_ast) = ast_allocate(NESTED_SCOPE_NODE, (yyvsp[0].as_ast)); }
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 229 "parser.y" /* yacc.c:1646  */
    { yTRACE("statement -> ;"); 
																		  (yyval.as_ast) = NULL; }
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 233 "parser.y" /* yacc.c:1646  */
    { yTRACE("arguments_opt -> arguments") 
				  (yyval.as_ast) = ast_allocate(ARGUMENTS_NODE, (yyvsp[0].as_ast), NULL); }
#line 1562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 235 "parser.y" /* yacc.c:1646  */
    { yTRACE("arguments_opt -> NULL") 
				  (yyval.as_ast) = NULL; }
#line 1569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 239 "parser.y" /* yacc.c:1646  */
    { yTRACE("arguments -> arguments , expression") 
								  (yyval.as_ast) = ast_allocate(ARGUMENTS_NODE, (yyvsp[-2].as_ast), (yyvsp[0].as_ast)); }
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 241 "parser.y" /* yacc.c:1646  */
    { yTRACE("arguments -> expression") 
								  (yyval.as_ast) = ast_allocate(ARGUMENTS_NODE, NULL, (yyvsp[0].as_ast)); }
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 245 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> type ( arguments )") 
												  	  	  (yyval.as_ast) = ast_allocate(CONSTRUCTOR_NODE, (yyvsp[-3].as_ast), (yyvsp[-1].as_ast), yyline); }
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 247 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> DP3 ( arguments_opt )") 
													  	  (yyval.as_ast) = ast_allocate(FUNCTION_NODE, 0, (yyvsp[-1].as_ast), yyline); }
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 249 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> LIT ( arguments_opt )") 
													  	  (yyval.as_ast) = ast_allocate(FUNCTION_NODE, 1, (yyvsp[-1].as_ast), yyline); }
#line 1604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 251 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> RSQ ( arguments_opt )") 
													  	  (yyval.as_ast) = ast_allocate(FUNCTION_NODE, 2, (yyvsp[-1].as_ast), yyline); }
#line 1611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 253 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> INTEGER_LITERAL") 
													  	  (yyval.as_ast) = ast_allocate(INT_NODE, (yyvsp[0].as_int), yyline); }
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 255 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> FLOAT_LITERAL"); 
													  	  (yyval.as_ast) = ast_allocate(FLOAT_NODE, (yyvsp[0].as_float), yyline); }
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 257 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> BOOL_TRUE")
													  	  (yyval.as_ast) = ast_allocate(BOOL_NODE, 1, yyline); }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 259 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> BOOL_FALSE")
													  	  (yyval.as_ast) = ast_allocate(BOOL_NODE, 0, yyline); }
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 261 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> variable")
														  (yyval.as_ast) = ast_allocate(EXPR_VAR_NODE, (yyvsp[0].as_ast), yyline); }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 263 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> ! expression")
														  (yyval.as_ast) = ast_allocate(UNARY_EXPRESSION_NODE, '!', (yyvsp[0].as_ast), yyline); }
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 265 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> unary - expresion")
														  (yyval.as_ast) = ast_allocate(UNARY_EXPRESSION_NODE, '-', (yyvsp[0].as_ast), yyline); }
#line 1660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 267 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression && expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 0, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 269 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression || expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 1, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 271 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression == expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 2, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 273 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression != expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 3, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 275 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression < expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 4, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 277 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression <= expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 5, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 279 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression > expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 6, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 281 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression >= expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 7, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 283 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression + expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 8, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 285 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression - expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 9, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 287 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression * expression")
													  	  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 10, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 289 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression / expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 11, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 291 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> expression ^ expression")
														  (yyval.as_ast) = ast_allocate(BINARY_EXPRESSION_NODE, 12, (yyvsp[-2].as_ast), (yyvsp[0].as_ast), yyline); }
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 293 "parser.y" /* yacc.c:1646  */
    { yTRACE("expression -> ( expression )")
														  (yyval.as_ast) = ast_allocate(NESTED_EXPRESSION_NODE, (yyvsp[-1].as_ast)); }
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 297 "parser.y" /* yacc.c:1646  */
    { yTRACE("variable -> IDENTIFIER")
															   (yyval.as_ast) = ast_allocate(VAR_NODE, (yyvsp[0].as_id), -1, yyline); }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 299 "parser.y" /* yacc.c:1646  */
    { yTRACE("variable -> IDENTIFIER [ INTEGER_LITERAL ]")
															   (yyval.as_ast) = ast_allocate(VAR_NODE, (yyvsp[-3].as_id), (yyvsp[-1].as_int), yyline); }
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 303 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> INT")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 0); }
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 305 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> IVEC2")
	          (yyval.as_ast) = ast_allocate(TYPE_NODE, 1); }
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 307 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> IVEC3")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 2); }
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 309 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> IVEC4")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 3); }
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 311 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> BOOL")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 4); }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 313 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> BVEC2")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 5); }
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 315 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> BVEC3")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 6); }
#line 1821 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 317 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> BVEC4")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 7); }
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 319 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> FLOAT") 
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 8); }
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 321 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> VEC2")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 9); }
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 323 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> VEC3")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 10); }
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 325 "parser.y" /* yacc.c:1646  */
    { yTRACE("type -> VEC4")
			  (yyval.as_ast) = ast_allocate(TYPE_NODE, 11); }
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1860 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 328 "parser.y" /* yacc.c:1906  */


/***********************************************************************ol
 * Extra C code.
 *
 * The given yyerror function should not be touched. You may add helper
 * functions as necessary in subsequent phases.
 ***********************************************************************/
void yyerror(const char* s) {
  if (errorOccurred)
    return;    /* Error has already been reported by scanner */
  else
    errorOccurred = 1;
        
  fprintf(errorFile, "\nPARSER ERROR, LINE %d",yyline);
  if (strcmp(s, "parse error")) {
    if (strncmp(s, "parse error, ", 13))
      fprintf(errorFile, ": %s\n", s);
    else
      fprintf(errorFile, ": %s\n", s+13);
  } else
    fprintf(errorFile, ": Reading token %s\n", yytname[YYTRANSLATE(yychar)]);
}

