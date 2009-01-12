/*
 * Copyright (C) 2006  Pekka Enberg
 *
 * This file is released under the GPL version 2. Please refer to the file
 * LICENSE for details.
 *
 * The file contains utility functions for parsing a bytecode stream.
 */

#include <vm/vm.h>
#include <vm/bytecode.h>
#include <vm/bytecodes.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum bytecode_type {
	BC_NORMAL = 0x01,
	BC_BRANCH = 0x02,
	BC_WIDE   = 0x04,
};

struct bytecode_info {
	unsigned char size;
	enum bytecode_type type;
};

static struct bytecode_info bytecode_infos[];

unsigned long bc_insn_size(unsigned char *bc_start)
{
	unsigned long size;

	size = bytecode_infos[*bc_start].size;
	if (*bc_start == OPC_WIDE)
		size += bytecode_infos[*++bc_start].size;

	if (size == 0) {
		printf("%s: Unknown bytecode opcode: 0x%x\n", __FUNCTION__, *bc_start);
		abort();
	}
	return size;
}

bool bc_is_branch(unsigned char opc)
{
	return bytecode_infos[opc].type & BC_BRANCH;
}

bool bc_is_wide(unsigned char opc)
{
	return bytecode_infos[opc].type & BC_WIDE;
}

bool bc_is_goto(unsigned char opc)
{
	return opc == OPC_GOTO;
}

/**
 *	bc_target_off - Return branch opcode target offset.
 *	@code: start of branch bytecode.
 */
long bc_target_off(unsigned char *code)
{
	unsigned char opc = *code;

	if (bc_is_wide(opc))
		return read_s32(code + 1);

	return read_s16(code + 1);
}

#define DECLARE_BC(__opc, __size, __type) [__opc] = { .size = __size, .type = __type }

static struct bytecode_info bytecode_infos[] = {
	DECLARE_BC(OPC_NOP, 1, BC_NORMAL),
	DECLARE_BC(OPC_ACONST_NULL, 1, BC_NORMAL),
	DECLARE_BC(OPC_ICONST_M1, 1, BC_NORMAL),
	DECLARE_BC(OPC_ICONST_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_ICONST_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_ICONST_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_ICONST_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_ICONST_4, 1, BC_NORMAL),
	DECLARE_BC(OPC_ICONST_5, 1, BC_NORMAL),
	DECLARE_BC(OPC_LCONST_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_LCONST_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_FCONST_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_FCONST_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_FCONST_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_DCONST_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_DCONST_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_BIPUSH, 2, BC_NORMAL),
	DECLARE_BC(OPC_SIPUSH, 3, BC_NORMAL),
	DECLARE_BC(OPC_LDC, 2, BC_NORMAL),
	DECLARE_BC(OPC_LDC_W, 3, BC_NORMAL | BC_WIDE),
	DECLARE_BC(OPC_LDC2_W, 3, BC_NORMAL | BC_WIDE),
	DECLARE_BC(OPC_ILOAD, 2, BC_NORMAL),
	DECLARE_BC(OPC_LLOAD, 2, BC_NORMAL),
	DECLARE_BC(OPC_FLOAD, 2, BC_NORMAL),
	DECLARE_BC(OPC_DLOAD, 2, BC_NORMAL),
	DECLARE_BC(OPC_ALOAD, 2, BC_NORMAL),
	DECLARE_BC(OPC_ILOAD_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_ILOAD_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_ILOAD_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_ILOAD_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_LLOAD_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_LLOAD_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_LLOAD_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_LLOAD_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_FLOAD_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_FLOAD_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_FLOAD_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_FLOAD_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_DLOAD_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_DLOAD_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_DLOAD_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_DLOAD_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_ALOAD_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_ALOAD_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_ALOAD_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_ALOAD_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_IALOAD, 1, BC_NORMAL),
	DECLARE_BC(OPC_LALOAD, 1, BC_NORMAL),
	DECLARE_BC(OPC_FALOAD, 1, BC_NORMAL),
	DECLARE_BC(OPC_DALOAD, 1, BC_NORMAL),
	DECLARE_BC(OPC_AALOAD, 1, BC_NORMAL),
	DECLARE_BC(OPC_BALOAD, 1, BC_NORMAL),
	DECLARE_BC(OPC_CALOAD, 1, BC_NORMAL),
	DECLARE_BC(OPC_SALOAD, 1, BC_NORMAL),
	DECLARE_BC(OPC_ISTORE, 2, BC_NORMAL),
	DECLARE_BC(OPC_LSTORE, 2, BC_NORMAL),
	DECLARE_BC(OPC_FSTORE, 2, BC_NORMAL),
	DECLARE_BC(OPC_DSTORE, 2, BC_NORMAL),
	DECLARE_BC(OPC_ASTORE, 2, BC_NORMAL),
	DECLARE_BC(OPC_ISTORE_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_ISTORE_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_ISTORE_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_ISTORE_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_LSTORE_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_LSTORE_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_LSTORE_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_LSTORE_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_FSTORE_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_FSTORE_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_FSTORE_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_FSTORE_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_DSTORE_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_DSTORE_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_DSTORE_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_DSTORE_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_ASTORE_0, 1, BC_NORMAL),
	DECLARE_BC(OPC_ASTORE_1, 1, BC_NORMAL),
	DECLARE_BC(OPC_ASTORE_2, 1, BC_NORMAL),
	DECLARE_BC(OPC_ASTORE_3, 1, BC_NORMAL),
	DECLARE_BC(OPC_IASTORE, 1, BC_NORMAL),
	DECLARE_BC(OPC_LASTORE, 1, BC_NORMAL),
	DECLARE_BC(OPC_FASTORE, 1, BC_NORMAL),
	DECLARE_BC(OPC_DASTORE, 1, BC_NORMAL),
	DECLARE_BC(OPC_AASTORE, 1, BC_NORMAL),
	DECLARE_BC(OPC_BASTORE, 1, BC_NORMAL),
	DECLARE_BC(OPC_CASTORE, 1, BC_NORMAL),
	DECLARE_BC(OPC_SASTORE, 1, BC_NORMAL),
	DECLARE_BC(OPC_POP, 1, BC_NORMAL),
	DECLARE_BC(OPC_POP2, 1, BC_NORMAL),
	DECLARE_BC(OPC_DUP, 1, BC_NORMAL),
	DECLARE_BC(OPC_DUP_X1, 1, BC_NORMAL),
	DECLARE_BC(OPC_DUP_X2, 1, BC_NORMAL),
	DECLARE_BC(OPC_DUP2, 1, BC_NORMAL),
	DECLARE_BC(OPC_DUP2_X1, 1, BC_NORMAL),
	DECLARE_BC(OPC_DUP2_X2, 1, BC_NORMAL),
	DECLARE_BC(OPC_SWAP, 1, BC_NORMAL),
	DECLARE_BC(OPC_IADD, 1, BC_NORMAL),
	DECLARE_BC(OPC_LADD, 1, BC_NORMAL),
	DECLARE_BC(OPC_FADD, 1, BC_NORMAL),
	DECLARE_BC(OPC_DADD, 1, BC_NORMAL),
	DECLARE_BC(OPC_ISUB, 1, BC_NORMAL),
	DECLARE_BC(OPC_LSUB, 1, BC_NORMAL),
	DECLARE_BC(OPC_FSUB, 1, BC_NORMAL),
	DECLARE_BC(OPC_DSUB, 1, BC_NORMAL),
	DECLARE_BC(OPC_IMUL, 1, BC_NORMAL),
	DECLARE_BC(OPC_LMUL, 1, BC_NORMAL),
	DECLARE_BC(OPC_FMUL, 1, BC_NORMAL),
	DECLARE_BC(OPC_DMUL, 1, BC_NORMAL),
	DECLARE_BC(OPC_IDIV, 1, BC_NORMAL),
	DECLARE_BC(OPC_LDIV, 1, BC_NORMAL),
	DECLARE_BC(OPC_FDIV, 1, BC_NORMAL),
	DECLARE_BC(OPC_DDIV, 1, BC_NORMAL),
	DECLARE_BC(OPC_IREM, 1, BC_NORMAL),
	DECLARE_BC(OPC_LREM, 1, BC_NORMAL),
	DECLARE_BC(OPC_FREM, 1, BC_NORMAL),
	DECLARE_BC(OPC_DREM, 1, BC_NORMAL),
	DECLARE_BC(OPC_INEG, 1, BC_NORMAL),
	DECLARE_BC(OPC_LNEG, 1, BC_NORMAL),
	DECLARE_BC(OPC_FNEG, 1, BC_NORMAL),
	DECLARE_BC(OPC_DNEG, 1, BC_NORMAL),
	DECLARE_BC(OPC_ISHL, 1, BC_NORMAL),
	DECLARE_BC(OPC_LSHL, 1, BC_NORMAL),
	DECLARE_BC(OPC_ISHR, 1, BC_NORMAL),
	DECLARE_BC(OPC_LSHR, 1, BC_NORMAL),
	DECLARE_BC(OPC_IUSHR, 1, BC_NORMAL),
	DECLARE_BC(OPC_LUSHR, 1, BC_NORMAL),
	DECLARE_BC(OPC_IAND, 1, BC_NORMAL),
	DECLARE_BC(OPC_LAND, 1, BC_NORMAL),
	DECLARE_BC(OPC_IOR, 1, BC_NORMAL),
	DECLARE_BC(OPC_LOR, 1, BC_NORMAL),
	DECLARE_BC(OPC_IXOR, 1, BC_NORMAL),
	DECLARE_BC(OPC_LXOR, 1, BC_NORMAL),
	DECLARE_BC(OPC_IINC, 3, BC_NORMAL),
	DECLARE_BC(OPC_I2L, 1, BC_NORMAL),
	DECLARE_BC(OPC_I2F, 1, BC_NORMAL),
	DECLARE_BC(OPC_I2D, 1, BC_NORMAL),
	DECLARE_BC(OPC_L2I, 1, BC_NORMAL),
	DECLARE_BC(OPC_L2F, 1, BC_NORMAL),
	DECLARE_BC(OPC_L2D, 1, BC_NORMAL),
	DECLARE_BC(OPC_F2I, 1, BC_NORMAL),
	DECLARE_BC(OPC_F2L, 1, BC_NORMAL),
	DECLARE_BC(OPC_F2D, 1, BC_NORMAL),
	DECLARE_BC(OPC_D2I, 1, BC_NORMAL),
	DECLARE_BC(OPC_D2L, 1, BC_NORMAL),
	DECLARE_BC(OPC_D2F, 1, BC_NORMAL),
	DECLARE_BC(OPC_I2B, 1, BC_NORMAL),
	DECLARE_BC(OPC_I2C, 1, BC_NORMAL),
	DECLARE_BC(OPC_I2S, 1, BC_NORMAL),
	DECLARE_BC(OPC_LCMP, 1, BC_NORMAL),
	DECLARE_BC(OPC_FCMPL, 1, BC_NORMAL),
	DECLARE_BC(OPC_FCMPG, 1, BC_NORMAL),
	DECLARE_BC(OPC_DCMPL, 1, BC_NORMAL),
	DECLARE_BC(OPC_DCMPG, 1, BC_NORMAL),
	DECLARE_BC(OPC_IFEQ, 3, BC_BRANCH),
	DECLARE_BC(OPC_IFNE, 3, BC_BRANCH),
	DECLARE_BC(OPC_IFLT, 3, BC_BRANCH),
	DECLARE_BC(OPC_IFGE, 3, BC_BRANCH),
	DECLARE_BC(OPC_IFGT, 3, BC_BRANCH),
	DECLARE_BC(OPC_IFLE, 3, BC_BRANCH),
	DECLARE_BC(OPC_IF_ICMPEQ, 3, BC_BRANCH),
	DECLARE_BC(OPC_IF_ICMPNE, 3, BC_BRANCH),
	DECLARE_BC(OPC_IF_ICMPLT, 3, BC_BRANCH),
	DECLARE_BC(OPC_IF_ICMPGE, 3, BC_BRANCH),
	DECLARE_BC(OPC_IF_ICMPGT, 3, BC_BRANCH),
	DECLARE_BC(OPC_IF_ICMPLE, 3, BC_BRANCH),
	DECLARE_BC(OPC_IF_ACMPEQ, 3, BC_BRANCH),
	DECLARE_BC(OPC_IF_ACMPNE, 3, BC_BRANCH),
	DECLARE_BC(OPC_GOTO, 3, BC_BRANCH),
	DECLARE_BC(OPC_JSR, 3, BC_BRANCH),
	DECLARE_BC(OPC_ATHROW, 1, BC_NORMAL),
	DECLARE_BC(OPC_RET, 2, BC_NORMAL),
	/* OPC_TABLESWITCH and OPC_LOOKUPSWITCH are variable-length.  */
	DECLARE_BC(OPC_TABLESWITCH, 0, BC_BRANCH),
	DECLARE_BC(OPC_LOOKUPSWITCH, 0, BC_BRANCH),
	DECLARE_BC(OPC_IRETURN, 1, BC_NORMAL),
	DECLARE_BC(OPC_LRETURN, 1, BC_NORMAL),
	DECLARE_BC(OPC_FRETURN, 1, BC_NORMAL),
	DECLARE_BC(OPC_DRETURN, 1, BC_NORMAL),
	DECLARE_BC(OPC_ARETURN, 1, BC_NORMAL),
	DECLARE_BC(OPC_RETURN, 1, BC_NORMAL),
	DECLARE_BC(OPC_GETSTATIC, 3, BC_NORMAL),
	DECLARE_BC(OPC_PUTSTATIC, 3, BC_NORMAL),
	DECLARE_BC(OPC_GETFIELD, 3, BC_NORMAL),
	DECLARE_BC(OPC_PUTFIELD, 3, BC_NORMAL),
	DECLARE_BC(OPC_INVOKEVIRTUAL, 3, BC_NORMAL),
	DECLARE_BC(OPC_INVOKESPECIAL, 3, BC_NORMAL),
	DECLARE_BC(OPC_INVOKESTATIC, 3, BC_NORMAL),
	DECLARE_BC(OPC_NEW, 3, BC_NORMAL),
	DECLARE_BC(OPC_NEWARRAY, 2, BC_NORMAL),
	DECLARE_BC(OPC_CHECKCAST, 3, BC_NORMAL),
	DECLARE_BC(OPC_WIDE, 3, BC_NORMAL),
	DECLARE_BC(OPC_IFNULL, 3, BC_BRANCH),
	DECLARE_BC(OPC_IFNONNULL, 3, BC_BRANCH),
	DECLARE_BC(OPC_GOTO_W, 5, BC_BRANCH | BC_WIDE),
	DECLARE_BC(OPC_JSR_W, 5, BC_BRANCH | BC_WIDE),
	DECLARE_BC(OPC_ANEWARRAY, 3, BC_NORMAL),
	DECLARE_BC(OPC_MULTIANEWARRAY, 4, BC_NORMAL),
	DECLARE_BC(OPC_ARRAYLENGTH, 1, BC_NORMAL),
	DECLARE_BC(OPC_INSTANCEOF, 3, BC_NORMAL),
	DECLARE_BC(OPC_MONITORENTER, 1, BC_NORMAL),
	DECLARE_BC(OPC_MONITOREXIT, 1, BC_NORMAL),
};
