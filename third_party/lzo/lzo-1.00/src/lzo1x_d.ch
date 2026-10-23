/* lzo1x_d.ch -- implementation of the LZO1X decompression algorithm

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1997 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 1996 Markus Franz Xaver Johannes Oberhumer

   The LZO library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   The LZO library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the LZO library; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Markus F.X.J. Oberhumer
   markus.oberhumer@jk.uni-linz.ac.at
 */


#include "lzo1_d.ch"


#if defined(HAVE_ANY_IP) && defined(HAVE_ANY_OP)
   /* too many local variables, cannot allocate registers */
#  undef LZO_OPTIMIZE_GNUC_i386
#endif


/***********************************************************************
// decompress a block of data.
************************************************************************/

LZO_PUBLIC(int)
DO_DECOMPRESS  ( const lzo_byte *in , lzo_uint  in_len,
                       lzo_byte *out, lzo_uint *out_len,
                       lzo_voidp wrkmem )
{
#if 0 && defined(__GNUC__) && defined(__i386__)
	register lzo_byte *op __asm__("%edi");
	register const lzo_byte *ip __asm__("%esi");
	register lzo_uint t __asm__("%ecx");
	register const lzo_byte *m_pos __asm__("%ebx");
#else
	register lzo_byte *op;
	register const lzo_byte *ip;
	register lzo_uint t;
	register const lzo_byte *m_pos;
#endif

	const lzo_byte * const ip_end = in + in_len;
#if defined(HAVE_ANY_OP)
	lzo_byte * const op_end = out + *out_len;
#endif

	LZO_UNUSED(wrkmem);

	*out_len = 0;

	op = out;
	ip = in;

	if (*ip > 17)
	{
		t = *ip++ - 17;
		assert(t > 0); NEED_OP(t); NEED_IP(t+1);
		do *op++ = *ip++; while (--t > 0);
		goto first_literal_run;
	}

	while (TEST_IP && TEST_OP)
	{
		t = *ip++;
		if (t >= 16)
			goto match;
		/* a literal run */
		if (t == 0)
		{
			NEED_IP(1);
			while (*ip == 0)
			{
				t += 255;
				ip++;
				NEED_IP(1);
			}
			t += 15 + *ip++;
		}
		/* copy literals */
		assert(t > 0); NEED_OP(t+3); NEED_IP(t+4);
#if defined(LZO_UNALIGNED_OK_4) || defined(LZO_ALIGNED_OK_4)
#if !defined(LZO_UNALIGNED_OK_4)
		if (PTR_ALIGNED2_4(op,ip))
		{
#endif
		* (lzo_uint32p) op = * (const lzo_uint32p) ip;
		op += 4; ip += 4;
		if (--t > 0)
		{
			if (t >= 4)
			{
				do {
					* (lzo_uint32p) op = * (const lzo_uint32p) ip;
					op += 4; ip += 4; t -= 4;
				} while (t >= 4);
				if (t > 0) do *op++ = *ip++; while (--t > 0);
			}
			else
				do *op++ = *ip++; while (--t > 0);
		}
#if !defined(LZO_UNALIGNED_OK_4)
		}
		else
#endif
#endif
#if !defined(LZO_UNALIGNED_OK_4)
		{
			*op++ = *ip++; *op++ = *ip++; *op++ = *ip++;
			do *op++ = *ip++; while (--t > 0);
		}
#endif


first_literal_run:


		t = *ip++;

#if defined(LZO1X_0) || defined(LZO1Y_0)
		assert(t >= 16);
		goto match;
#else
		if (t >= 16)
			goto match;
		m_pos = op - 1 - M2_MAX_OFFSET;
		m_pos -= t >> 2;
		m_pos -= *ip++ << 2;
		TEST_LOOKBEHIND(m_pos,out); NEED_OP(3);
		*op++ = *m_pos++; *op++ = *m_pos++; *op++ = *m_pos;
		goto match_done;
#endif


		/* handle matches */
		while (TEST_IP && TEST_OP)
		{
match:
			if (t >= 64)				/* a M2 match */
			{
				m_pos = op - 1;
#if defined(LZO1X)
				m_pos -= (t >> 2) & 7;
				m_pos -= *ip++ << 3;
				t = (t >> 5) - 1;
#elif defined(LZO1Y)
				m_pos -= (t >> 2) & 3;
				m_pos -= *ip++ << 2;
				t = (t >> 4) - 3;
#endif
				TEST_LOOKBEHIND(m_pos,out); assert(t > 0); NEED_OP(t+3-1);
				goto copy_match;
			}
			else if (t >= 32)			/* a M3 match */
			{
				t &= 31;
				if (t == 0)
				{
					NEED_IP(1);
					while (*ip == 0)
					{
						t += 255;
						ip++;
						NEED_IP(1);
					}
					t += 31 + *ip++;
				}
				m_pos = op - 1;
#if defined(LZO_UNALIGNED_OK_2) && (LZO_BYTE_ORDER == LZO_LITTLE_ENDIAN)
				m_pos -= (* (const lzo_ushortp) ip) >> 2;
				ip += 2;
#else
				m_pos -= *ip++ >> 2;
				m_pos -= *ip++ << 6;
#endif
			}
#if defined(LZO1X_0) || defined(LZO1Y_0)
			else						/* a M4 match */
			{
				assert(t >= 16);
#else
			else if (t >= 16)			/* a M4 match */
			{
#endif
				m_pos = op;
				m_pos -= (t & 8) << 11;
				t &= 7;
				if (t == 0)
				{
					NEED_IP(1);
					while (*ip == 0)
					{
						t += 255;
						ip++;
						NEED_IP(1);
					}
					t += 7 + *ip++;
				}
#if defined(LZO_UNALIGNED_OK_2) && (LZO_BYTE_ORDER == LZO_LITTLE_ENDIAN)
				m_pos -= (* (const lzo_ushortp) ip) >> 2;
				ip += 2;
#else
				m_pos -= *ip++ >> 2;
				m_pos -= *ip++ << 6;
#endif
				if (m_pos == op)
					goto eof_found;
				m_pos -= 0x4000;
			}
#if !defined(LZO1X_0) && !defined(LZO1Y_0)
			else							/* a M1 match */
			{
				m_pos = op - 1;
				m_pos -= t >> 2;
				m_pos -= *ip++ << 2;
				TEST_LOOKBEHIND(m_pos,out); NEED_OP(2);
				*op++ = *m_pos++; *op++ = *m_pos;
				goto match_done;
			}
#endif

			/* copy match */
			TEST_LOOKBEHIND(m_pos,out); assert(t > 0); NEED_OP(t+3-1);
#if defined(LZO_UNALIGNED_OK_4) || defined(LZO_ALIGNED_OK_4)
#if !defined(LZO_UNALIGNED_OK_4)
			if (t >= 2 * 4 - (3 - 1) && PTR_ALIGNED2_4(op,m_pos))
			{
				assert((op - m_pos) >= 4);	/* bec. both pointers are aligned */
#else
			if (t >= 2 * 4 - (3 - 1) && (op - m_pos) >= 4)
			{
#endif
				* (lzo_uint32p) op = * (const lzo_uint32p) m_pos;
				op += 4; m_pos += 4; t -= 4 - (3 - 1);
				do {
					* (lzo_uint32p) op = * (const lzo_uint32p) m_pos;
					op += 4; m_pos += 4; t -= 4;
				} while (t >= 4);
				if (t > 0) do *op++ = *m_pos++; while (--t > 0);
			}
			else
#endif
			{
copy_match:
				*op++ = *m_pos++; *op++ = *m_pos++;
				do *op++ = *m_pos++; while (--t > 0);
			}

match_done:
			t = ip[-2] & 3;
			if (t == 0)
				break;

			/* copy literals */
			assert(t > 0); NEED_OP(t); NEED_IP(t+1);
			do *op++ = *ip++; while (--t > 0);
			t = *ip++;
		}
	}

#if defined(HAVE_TEST_IP) || defined(HAVE_TEST_OP)
	/* no EOF code was found */
	*out_len = op - out;
	return LZO_E_EOF_NOT_FOUND;
#endif

eof_found:
	assert(t == 1);
	*out_len = op - out;
	return (ip == ip_end ? LZO_E_OK :
	       (ip < ip_end  ? LZO_E_INPUT_NOT_CONSUMED : LZO_E_INPUT_OVERRUN));


#if defined(HAVE_NEED_IP)
input_overrun:
	*out_len = op - out;
	return LZO_E_INPUT_OVERRUN;
#endif

#if defined(HAVE_NEED_OP)
output_overrun:
	*out_len = op - out;
	return LZO_E_OUTPUT_OVERRUN;
#endif

#if defined(LZO_TEST_DECOMPRESS_OVERRUN_LOOKBEHIND)
lookbehind_overrun:
	*out_len = op - out;
	return LZO_E_LOOKBEHIND_OVERRUN;
#endif
}


/*
vi:ts=4
*/

