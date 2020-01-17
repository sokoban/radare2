/* radare - LGPL - Copyright 2020 - thestr4ng3r */

#include "cbm_basic_dis.h"

#define CBM_BASIC_LINE_MAX 80 // TODO: what is the real val?

static const char *token_str(ut8 b) {
	switch ((RCBMBasicToken)b) {
	case R_CBM_BASIC_TOKEN_CMD_END:        return "END";
	case R_CBM_BASIC_TOKEN_CMD_FOR:        return "FOR";
	case R_CBM_BASIC_TOKEN_CMD_NEXT:       return "NEXT";
	case R_CBM_BASIC_TOKEN_CMD_DATA:       return "DATA";
	case R_CBM_BASIC_TOKEN_CMD_INPUT_HASH: return "INPUT_HASH";
	case R_CBM_BASIC_TOKEN_CMD_INPUT:      return "INPUT";
	case R_CBM_BASIC_TOKEN_CMD_DIM:        return "DIM";
	case R_CBM_BASIC_TOKEN_CMD_READ:       return "READ";
	case R_CBM_BASIC_TOKEN_CMD_LET:        return "LET";
	case R_CBM_BASIC_TOKEN_CMD_GOTO:       return "GOTO";
	case R_CBM_BASIC_TOKEN_CMD_RUN:        return "RUN";
	case R_CBM_BASIC_TOKEN_CMD_IF:         return "IF";
	case R_CBM_BASIC_TOKEN_CMD_RESTORE:    return "RESTORE";
	case R_CBM_BASIC_TOKEN_CMD_GOSUB:      return "GOSUB";
	case R_CBM_BASIC_TOKEN_CMD_RETURN:     return "RETURN";
	case R_CBM_BASIC_TOKEN_CMD_REM:        return "REM";
	case R_CBM_BASIC_TOKEN_CMD_STOP:       return "STOP";
	case R_CBM_BASIC_TOKEN_CMD_ON:         return "ON";
	case R_CBM_BASIC_TOKEN_CMD_WAIT:       return "WAIT";
	case R_CBM_BASIC_TOKEN_CMD_LOAD:       return "LOAD";
	case R_CBM_BASIC_TOKEN_CMD_SAVE:       return "SAVE";
	case R_CBM_BASIC_TOKEN_CMD_VERIFY:     return "VERIFY";
	case R_CBM_BASIC_TOKEN_CMD_DEF:        return "DEF";
	case R_CBM_BASIC_TOKEN_CMD_POKE:       return "POKE";
	case R_CBM_BASIC_TOKEN_CMD_PRINT_HASH: return "PRINT_HASH";
	case R_CBM_BASIC_TOKEN_CMD_PRINT:      return "PRINT";
	case R_CBM_BASIC_TOKEN_CMD_CONT:       return "CONT";
	case R_CBM_BASIC_TOKEN_CMD_LIST:       return "LIST";
	case R_CBM_BASIC_TOKEN_CMD_CLR:        return "CLR";
	case R_CBM_BASIC_TOKEN_CMD_CMD:        return "CMD";
	case R_CBM_BASIC_TOKEN_CMD_SYS:        return "SYS";
	case R_CBM_BASIC_TOKEN_CMD_OPEN:       return "OPEN";
	case R_CBM_BASIC_TOKEN_CMD_CLOSE:      return "CLOSE";
	case R_CBM_BASIC_TOKEN_CMD_GET:        return "GET";
	case R_CBM_BASIC_TOKEN_CMD_NEW:        return "NEW";
	case R_CBM_BASIC_TOKEN_BYWORD_TAB:     return "TAB";
	case R_CBM_BASIC_TOKEN_BYWORD_TO:      return "TO";
	case R_CBM_BASIC_TOKEN_BYWORD_FN:      return "FN";
	case R_CBM_BASIC_TOKEN_BYWORD_SPC:     return "SPC";
	case R_CBM_BASIC_TOKEN_BYWORD_THEN:    return "THEN";
	case R_CBM_BASIC_TOKEN_BYWORD_NOT:     return "NOT";
	case R_CBM_BASIC_TOKEN_BYWORD_STEP:    return "STEP";
	case R_CBM_BASIC_TOKEN_OPERATOR_ADD:   return "+";
	case R_CBM_BASIC_TOKEN_OPERATOR_SUB:   return "-";
	case R_CBM_BASIC_TOKEN_OPERATOR_MUL:   return "*";
	case R_CBM_BASIC_TOKEN_OPERATOR_DIV:   return "/";
	case R_CBM_BASIC_TOKEN_OPERATOR_POW:   return "^";
	case R_CBM_BASIC_TOKEN_OPERATOR_AND:   return "AND";
	case R_CBM_BASIC_TOKEN_OPERATOR_OR:    return "OR";
	case R_CBM_BASIC_TOKEN_OPERATOR_GT:    return ">";
	case R_CBM_BASIC_TOKEN_OPERATOR_EQ:    return "=";
	case R_CBM_BASIC_TOKEN_OPERATOR_LT:    return "<";
	case R_CBM_BASIC_TOKEN_FCN_SGN:        return "SGN";
	case R_CBM_BASIC_TOKEN_FCN_INT:        return "INT";
	case R_CBM_BASIC_TOKEN_FCN_ABS:        return "ABS";
	case R_CBM_BASIC_TOKEN_FCN_USR:        return "USR";
	case R_CBM_BASIC_TOKEN_FCN_FRE:        return "FRE";
	case R_CBM_BASIC_TOKEN_FCN_POS:        return "POS";
	case R_CBM_BASIC_TOKEN_FCN_SQR:        return "SQR";
	case R_CBM_BASIC_TOKEN_FCN_RND:        return "RND";
	case R_CBM_BASIC_TOKEN_FCN_LOG:        return "LOG";
	case R_CBM_BASIC_TOKEN_FCN_EXP:        return "EXP";
	case R_CBM_BASIC_TOKEN_FCN_COS:        return "COS";
	case R_CBM_BASIC_TOKEN_FCN_SIN:        return "SIN";
	case R_CBM_BASIC_TOKEN_FCN_TAN:        return "TAN";
	case R_CBM_BASIC_TOKEN_FCN_ATN:        return "ATN";
	case R_CBM_BASIC_TOKEN_FCN_PEEK:       return "PEEK";
	case R_CBM_BASIC_TOKEN_FCN_LEN:        return "LEN";
	case R_CBM_BASIC_TOKEN_FCN_STR$:       return "STR$";
	case R_CBM_BASIC_TOKEN_FCN_VAL:        return "VAL";
	case R_CBM_BASIC_TOKEN_FCN_ASC:        return "ASC";
	case R_CBM_BASIC_TOKEN_FCN_CHR$:       return "CHR$";
	case R_CBM_BASIC_TOKEN_FCN_LEFT$:      return "LEFT$";
	case R_CBM_BASIC_TOKEN_FCN_RIGHT$:     return "RIGHT$";
	case R_CBM_BASIC_TOKEN_FCN_MID$:       return "MID$";
	case R_CBM_BASIC_TOKEN_CMD_GO:         return "GO";
	default:                               return NULL;
	}
}

R_API size_t r_cbm_basic_disassemble(R_OUT RStrBuf *out, RBuffer *buf) {
	ut64 pos = 0;
	ut16 next_op_addr = r_buf_read_le16_at (buf, pos);
	pos += 2;
	if (next_op_addr == UT16_MAX) {
		return pos;
	}
	r_strbuf_appendf (out, "(->0x%04x)", (unsigned int)next_op_addr);
	if (!next_op_addr) {
		// zero addr means end of program
		return pos;
	}

	ut64 line_num = r_buf_read_le16_at (buf, pos);
	pos += 2;
	if (line_num == UT16_MAX) {
		return pos;
	}
	r_strbuf_appendf (out, " %2d ", (unsigned int)line_num);

	ut8 b;
	while (pos < CBM_BASIC_LINE_MAX) {
		b = r_buf_read8_at (buf, pos++);
		if (b == 0 || b == UT8_MAX) {
			// 0 => end of line
			// 0xff => fail
			break;
		}
		const char *token = token_str (b);
		if (token) {
			r_strbuf_append (out, token);
		} else if (IS_PRINTABLE (b) && b != '\n') {
			r_strbuf_appendf (out, "%c", (char)b);
		} else {
			r_strbuf_appendf (out, " 0x%02x ", (unsigned int)b);
		}
	}

	return pos;
}