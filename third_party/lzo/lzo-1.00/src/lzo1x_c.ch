/* lzo1x_1.c -- implementation of the LZO1X-1 compression algorithm

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



/***********************************************************************
// compress a block of data.
************************************************************************/

static
int do_compress          ( const lzo_byte *in , lzo_uint  in_len,
                                 lzo_byte *out, lzo_uint *out_len,
                                 lzo_voidp wrkmem )
{
#if 1 && defined(__GNUC__) && defined(__i386__)
	register const lzo_byte *ip __asm__("%esi");
#else
	register const lzo_byte *ip;
#endif
	lzo_uint32 dv;
	lzo_byte *op;
	const lzo_byte * const in_end = in + in_len;
	const lzo_byte * const ip_end = in + in_len - M2_MAX_LEN - 5;
	const lzo_byte *ii;
	lzo_dict_p const dict = (lzo_dict_p) wrkmem;

	op = out;
	ip = in;
	ii = ip;

	DVAL_FIRST(dv,ip); UPDATE_D(dict,cycle,dv,ip,in); ip++;
	DVAL_NEXT(dv,ip);  UPDATE_D(dict,cycle,dv,ip,in); ip++;
	DVAL_NEXT(dv,ip);  UPDATE_D(dict,cycle,dv,ip,in); ip++;
	DVAL_NEXT(dv,ip);  UPDATE_D(dict,cycle,dv,ip,in); ip++;

	while (1)
	{
#if 1 && defined(__GNUC__) && defined(__i386__)
		register const lzo_byte *m_pos __asm__("%edi");
#else
		register const lzo_byte *m_pos;
#endif
		lzo_uint m_len;
		lzo_moff_t m_off;
		lzo_uint lit;

		{
			lzo_uint dindex = DINDEX(dv,ip);
			GINDEX(m_pos,m_off,dict,dindex,in);
			UPDATE_I(dict,cycle,dindex,ip,in);
		}


		if (LZO_CHECK_MPOS_NON_DET(m_pos,m_off,in,ip,M4_MAX_OFFSET))
		{
		}
#if defined(LZO_UNALIGNED_OK_2)
		else if (* (const lzo_ushortp) m_pos != * (const lzo_ushortp) ip)
#else
		else if (m_pos[0] != ip[0] || m_pos[1] != ip[1])
#endif
		{
		}
		else
		{
			if (m_pos[2] == ip[2])
			{
				lit = ip - ii;
				m_pos += 3;
				if (m_off <= M2_MAX_OFFSET)
					goto match;
#if 0
				if (lit <= 3)
					goto match;
#else
				if (lit == 3)			/* better compression, but slower */
				{
					assert(op - 2 > out); op[-2] |= LZO_BYTE(3);
					*op++ = *ii++; *op++ = *ii++; *op++ = *ii++;
					goto code_match;
				}
#endif
				if (*m_pos == ip[3])
					goto match;
			}
			else
			{
				/* still need a better way for finding M1 matches */
#if 0
				/* a M1 match */
#if 0
				if (m_off <= M1_MAX_OFFSET && lit > 0 && lit <= 3)
#else
				if (m_off <= M1_MAX_OFFSET && lit == 3)
#endif
				{
					register lzo_uint t;

					t = lit;
					assert(op - 2 > out); op[-2] |= LZO_BYTE(t);
					do *op++ = *ii++; while (--t > 0);
					assert(ii == ip);
					m_off -= 1;
					*op++ = LZO_BYTE(M1_MARKER | ((m_off & 3) << 2));
					*op++ = LZO_BYTE(m_off >> 2);
					ip += 2;
					goto match_done;
				}
#endif
			}
		}


	/* a literal */
		++ip;
		if (ip >= ip_end)
			break;
		DVAL_NEXT(dv,ip);
		continue;


	/* a match */
match:

		/* store current literal run */
		if (lit > 0)
		{
			register lzo_uint t = lit;

			if (t <= 3)
			{
				assert(op - 2 > out);
				op[-2] |= LZO_BYTE(t);
			}
			else if (t <= 18)
				*op++ = LZO_BYTE(t - 3);
			else
			{
				register lzo_uint tt = t - 18;

				*op++ = 0;
				while (tt > 255)
				{
					tt -= 255;
					*op++ = 0;
				}
				assert(tt > 0);
				*op++ = LZO_BYTE(tt);
			}
			do *op++ = *ii++; while (--t > 0);
		}


		/* code the match */
code_match:
		assert(ii == ip);
		ip += 3;
		if (*m_pos++ != *ip++ || *m_pos++ != *ip++ || *m_pos++ != *ip++ ||
		    *m_pos++ != *ip++ || *m_pos++ != *ip++ || *m_pos++ != *ip++
#ifdef LZO1Y
		    || *m_pos++ != *ip++ || *m_pos++ != *ip++ || *m_pos++ != *ip++
		    || *m_pos++ != *ip++ || *m_pos++ != *ip++ || *m_pos++ != *ip++
#endif
           )
		{
			--ip;
			m_len = ip - ii;
			assert(m_len >= 3); assert(m_len <= M2_MAX_LEN);

			if (m_off <= M2_MAX_OFFSET)
			{
				m_off -= 1;
#if defined(LZO1X)
				*op++ = LZO_BYTE(((m_len - 1) << 5) | ((m_off & 7) << 2));
				*op++ = LZO_BYTE(m_off >> 3);
#elif defined(LZO1Y)
				*op++ = LZO_BYTE(((m_len + 1) << 4) | ((m_off & 3) << 2));
				*op++ = LZO_BYTE(m_off >> 2);
#endif
			}
			else if (m_off <= M3_MAX_OFFSET)
			{
				m_off -= 1;
				*op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
				goto m3_m4_offset;
			}
			else
#if defined(LZO1X)
			{
				m_off -= 0x4000;
				assert(m_off > 0); assert(m_off <= 0x7fff);
				*op++ = LZO_BYTE(M4_MARKER |
				                 ((m_off & 0x4000) >> 11) | (m_len - 2));
				goto m3_m4_offset;
			}
#elif defined(LZO1Y)
				goto m4_match;
#endif
		}
		else
		{
			{
				const lzo_byte *end;
				end = in_end;
				while (ip < end && *m_pos == *ip)
					m_pos++, ip++;
				m_len = (ip - ii);
			}
			assert(m_len > M2_MAX_LEN);

			if (m_off <= M3_MAX_OFFSET)
			{
				m_off -= 1;
				if (m_len <= 33)
					*op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
				else
				{
					m_len -= 33;
					*op++ = M3_MARKER | 0;
					goto m3_m4_len;
				}
			}
			else
			{
#if defined(LZO1Y)
m4_match:
#endif
				m_off -= 0x4000;
				assert(m_off > 0); assert(m_off <= 0x7fff);
				if (m_len <= M4_MAX_LEN)
					*op++ = LZO_BYTE(M4_MARKER |
					                 ((m_off & 0x4000) >> 11) | (m_len - 2));
				else
				{
					m_len -= M4_MAX_LEN;
					*op++ = LZO_BYTE(M4_MARKER | ((m_off & 0x4000) >> 11));
m3_m4_len:
					while (m_len > 255)
					{
						m_len -= 255;
						*op++ = 0;
					}
					assert(m_len > 0);
					*op++ = LZO_BYTE(m_len);
				}
			}

m3_m4_offset:
			*op++ = LZO_BYTE((m_off & 63) << 2);
			*op++ = LZO_BYTE(m_off >> 6);
		}

#if 0
match_done:
#endif
		ii = ip;
		if (ip >= ip_end)
			break;
		DVAL_FIRST(dv,ip);
	}


	/* store final literal run */
	if (in_end - ii > 0)
	{
		register lzo_uint t = in_end - ii;

		if (op == out && t <= 238)
			*op++ = LZO_BYTE(17 + t);
		else if (t <= 3)
			op[-2] |= LZO_BYTE(t);
		else if (t <= 18)
			*op++ = LZO_BYTE(t - 3);
		else
		{
			register lzo_uint tt = t - 18;

			*op++ = 0;
			while (tt > 255)
			{
				tt -= 255;
				*op++ = 0;
			}
			assert(tt > 0);
			*op++ = LZO_BYTE(tt);
		}
		do *op++ = *ii++; while (--t > 0);
	}

	*out_len = op - out;
	return LZO_E_OK;
}


/***********************************************************************
// public entry point
************************************************************************/

LZO_PUBLIC(int)
DO_COMPRESS      ( const lzo_byte *in , lzo_uint  in_len,
                         lzo_byte *out, lzo_uint *out_len,
                         lzo_voidp wrkmem )
{
	lzo_byte *op = out;
	int r = LZO_E_OK;

	if (in_len <= 0)
		*out_len = 0;
	else if (in_len <= M2_MAX_LEN + 5)
	{
		*op++ = LZO_BYTE(17 + in_len);
		do *op++ = *in++; while (--in_len > 0);
		*out_len = op - out;
	}
	else
		r = do_compress(in,in_len,out,out_len,wrkmem);

	if (r == LZO_E_OK)
	{
		op = out + *out_len;
		*op++ = M4_MARKER | 1;
		*op++ = 0;
		*op++ = 0;
		*out_len += 3;
	}

	return r;
}


/*
vi:ts=4
*/

