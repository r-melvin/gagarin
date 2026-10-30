/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Provenance: reconstruction-from-LZO-1.00-src/lzo1x_d.ch (GPL-2.0-or-later) + own-binary-via-Ghidra */
/*
 * gagarin reconstruction of the LZO1X decoder at 0x55C0E0.
 *
 * The decoder version shipped in the retail binary is not available, so this
 * is rewritten from LZO 1.00's lzo1x_d.ch (macros and structure) to reproduce
 * the retail code: no overrun checks, byte-wise copies, two-way return value.
 * Included into the same translation unit as lzo1x_1.c (see lzo1x.c).
 */

LZO_PUBLIC(int)
lzo1x_decompress ( const lzo_byte *in , lzo_uint  in_len,
                         lzo_byte *out, lzo_uint *out_len,
                         lzo_voidp wrkmem )
{
	register lzo_byte *op;
	register const lzo_byte *ip;
	register lzo_uint t;
	register const lzo_byte *m_pos;

	const lzo_byte * const ip_end = in + in_len;

	LZO_UNUSED(wrkmem);

	*out_len = 0;

	op = out;
	ip = in;

	if (*ip > 17)
	{
		t = *ip++ - 17;
		goto copy_run;
	}

	for (;;)
	{
		t = *ip++;
		if (t >= 16)
			goto match;
		/* a literal run */
		if (t == 0)
		{
			t = 15;
			while (*ip == 0)
			{
				t += 255;
				ip++;
			}
			t += *ip++;
		}
		/* copy literals */
		*op++ = *ip++; *op++ = *ip++; *op++ = *ip++;
copy_run:
		do *op++ = *ip++; while (--t > 0);

first_literal_run:

		t = *ip++;
		if (t >= 16)
			goto match;
		m_pos = op - 1 - M2_MAX_OFFSET;
		m_pos -= t >> 2;
		m_pos -= *ip++ << 2;
		*op++ = *m_pos++; *op++ = *m_pos++; *op++ = *m_pos;
		goto match_done;

		for (;;)
		{
match:
			if (t >= 64)				/* a M2 match */
			{
				m_pos = op - 1;
				m_pos -= (t >> 2) & 7;
				m_pos -= *ip++ << 3;
				t = (t >> 5) - 1;
				goto copy_match;
			}
			else if (t >= 32)			/* a M3 match */
			{
				t &= 31;
				if (t == 0)
				{
					t = 31;
					while (*ip == 0)
					{
						t += 255;
						ip++;
					}
					t += *ip++;
				}
				m_pos = op - 1;
				m_pos -= *ip++ >> 2;
				m_pos -= *ip++ << 6;
			}
			else						/* a M4 match */
			{
				m_pos = op;
				m_pos -= (t & 8) << 11;
				t &= 7;
				if (t == 0)
				{
					t = 7;
					while (*ip == 0)
					{
						t += 255;
						ip++;
					}
					t += *ip++;
				}
				m_pos -= *ip++ >> 2;
				m_pos -= *ip++ << 6;
				if (m_pos == op)
					goto eof_found;
				m_pos -= 0x4000;
			}

			/* copy match */
copy_match:
			*op++ = *m_pos++; *op++ = *m_pos++;
			do *op++ = *m_pos++; while (--t > 0);

match_done:
			t = ip[-2] & 3;
			if (t == 0)
				break;

			/* copy literals */
			do *op++ = *ip++; while (--t > 0);
			t = *ip++;
			if (t < 16)
			{
				m_pos = op - 1;
				m_pos -= t >> 2;
				m_pos -= *ip++ << 2;
				*op++ = *m_pos++; *op++ = *m_pos;
				goto match_done;
			}
		}
	}

eof_found:
	*out_len = op - out;
	return (ip == ip_end ? 0 : -1);
}
