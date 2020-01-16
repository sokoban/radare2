/* radare - LGPL - Copyright 2020 - thestr4ng3r */

#ifndef R2_CBM_DIS_H
#define R2_CBM_DIS_H

// see https://www.c64-wiki.com/wiki/BASIC_token

typedef enum {
	R_CBM_BASIC_TOKEN_CMD_END = 0x80,
	R_CBM_BASIC_TOKEN_CMD_FOR = 0x81,
	R_CBM_BASIC_TOKEN_CMD_NEXT = 0x82,
	R_CBM_BASIC_TOKEN_CMD_DATA = 0x83,
	R_CBM_BASIC_TOKEN_CMD_INPUT_HASH = 0x84,
	R_CBM_BASIC_TOKEN_CMD_INPUT = 0x85,
	R_CBM_BASIC_TOKEN_CMD_DIM = 0x86,
	R_CBM_BASIC_TOKEN_CMD_READ = 0x87,
	R_CBM_BASIC_TOKEN_CMD_LET = 0x88,
	R_CBM_BASIC_TOKEN_CMD_GOTO = 0x89,
	R_CBM_BASIC_TOKEN_CMD_RUN = 0x8A,
	R_CBM_BASIC_TOKEN_CMD_IF = 0x8B,
	R_CBM_BASIC_TOKEN_CMD_RESTORE = 0x8C,
	R_CBM_BASIC_TOKEN_CMD_GOSUB = 0x8D,
	R_CBM_BASIC_TOKEN_CMD_RETURN = 0x8E,
	R_CBM_BASIC_TOKEN_CMD_REM = 0x8F,
	R_CBM_BASIC_TOKEN_CMD_STOP = 0x90,
	R_CBM_BASIC_TOKEN_CMD_ON = 0x91,
	R_CBM_BASIC_TOKEN_CMD_WAIT = 0x92,
	R_CBM_BASIC_TOKEN_CMD_LOAD = 0x93,
	R_CBM_BASIC_TOKEN_CMD_SAVE = 0x94,
	R_CBM_BASIC_TOKEN_CMD_VERIFY = 0x95,
	R_CBM_BASIC_TOKEN_CMD_DEF = 0x96,
	R_CBM_BASIC_TOKEN_CMD_POKE = 0x97,
	R_CBM_BASIC_TOKEN_CMD_PRINT_HASH = 0x98,
	R_CBM_BASIC_TOKEN_CMD_PRINT = 0x99,
	R_CBM_BASIC_TOKEN_CMD_CONT = 0x9A,
	R_CBM_BASIC_TOKEN_CMD_LIST = 0x9B,
	R_CBM_BASIC_TOKEN_CMD_CLR = 0x9C,
	R_CBM_BASIC_TOKEN_CMD_CMD = 0x9D,
	R_CBM_BASIC_TOKEN_CMD_SYS = 0x9E,
	R_CBM_BASIC_TOKEN_CMD_OPEN = 0x9F,
	R_CBM_BASIC_TOKEN_CMD_CLOSE = 0xA0,
	R_CBM_BASIC_TOKEN_CMD_GET = 0xA1,
	R_CBM_BASIC_TOKEN_CMD_NEW = 0xA2,
	R_CBM_BASIC_TOKEN_BYWORD_TAB = 0xA3,
	R_CBM_BASIC_TOKEN_BYWORD_TO = 0xA4,
	R_CBM_BASIC_TOKEN_BYWORD_FN = 0xA5,
	R_CBM_BASIC_TOKEN_BYWORD_SPC = 0xA6,
	R_CBM_BASIC_TOKEN_BYWORD_THEN = 0xA7,
	R_CBM_BASIC_TOKEN_BYWORD_NOT = 0xA8,
	R_CBM_BASIC_TOKEN_BYWORD_STEP = 0xA9,
	R_CBM_BASIC_TOKEN_OPERATOR_ADD = 0xAA,
	R_CBM_BASIC_TOKEN_OPERATOR_SUB = 0xAB,
	R_CBM_BASIC_TOKEN_OPERATOR_MUL = 0xAC,
	R_CBM_BASIC_TOKEN_OPERATOR_DIV = 0xAD,
	R_CBM_BASIC_TOKEN_OPERATOR_POW = 0xAE,
	R_CBM_BASIC_TOKEN_OPERATOR_AND = 0xAF,
	R_CBM_BASIC_TOKEN_OPERATOR_OR = 0xB0,
	R_CBM_BASIC_TOKEN_OPERATOR_GT = 0xB1,
	R_CBM_BASIC_TOKEN_OPERATOR_EQ = 0xB2,
	R_CBM_BASIC_TOKEN_OPERATOR_LT = 0xB3,
	R_CBM_BASIC_TOKEN_FCN_SGN = 0xB4,
	R_CBM_BASIC_TOKEN_FCN_INT = 0xB5,
	R_CBM_BASIC_TOKEN_FCN_ABS = 0xB6,
	R_CBM_BASIC_TOKEN_FCN_USR = 0xB7,
	R_CBM_BASIC_TOKEN_FCN_FRE = 0xB8,
	R_CBM_BASIC_TOKEN_FCN_POS = 0xB9,
	R_CBM_BASIC_TOKEN_FCN_SQR = 0xBA,
	R_CBM_BASIC_TOKEN_FCN_RND = 0xBB,
	R_CBM_BASIC_TOKEN_FCN_LOG = 0xBC,
	R_CBM_BASIC_TOKEN_FCN_EXP = 0xBD,
	R_CBM_BASIC_TOKEN_FCN_COS = 0xBE,
	R_CBM_BASIC_TOKEN_FCN_SIN = 0xBF,
	R_CBM_BASIC_TOKEN_FCN_TAN = 0xC0,
	R_CBM_BASIC_TOKEN_FCN_ATN = 0xC1,
	R_CBM_BASIC_TOKEN_FCN_PEEK = 0xC2,
	R_CBM_BASIC_TOKEN_FCN_LEN = 0xC3,
	R_CBM_BASIC_TOKEN_FCN_STR$ = 0xC4,
	R_CBM_BASIC_TOKEN_FCN_VAL = 0xC5,
	R_CBM_BASIC_TOKEN_FCN_ASC = 0xC6,
	R_CBM_BASIC_TOKEN_FCN_CHR$ = 0xC7,
	R_CBM_BASIC_TOKEN_FCN_LEFT$ = 0xC8,
	R_CBM_BASIC_TOKEN_FCN_RIGHT$ = 0xC9,
	R_CBM_BASIC_TOKEN_FCN_MID$ = 0xCA,
	R_CBM_BASIC_TOKEN_CMD_GO = 0xCB
} RCBMBasicToken;

#endif //R2_CBM_DIS_H
