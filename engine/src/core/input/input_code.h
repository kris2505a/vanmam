#pragma once
#include "core/types/types.h"

NS_VANMAM

enum class key_code : u8 {
	a, b, c, d, e, f,
	g, h, i, j, k, l,
	m, n, o, p, q, r, 
	s, t, u, v, w, x,
	y, z,

	n0, n1, n2, n3, n4,
	n5, n6, n7, n8, n9,

	np0, np1, np2, np3,
	np4, np5, np6, np7,
	np8, np9,

	ctrl, r_ctrl,
	alt, r_alt,
	shift, r_shift,
	caps, tab, space,

	f_slash, b_slash, comma, fullstop,
	hyphen, equal, apostrophe,
	open_bracket, close_bracket,
	enter, np_enter,

	home, ins, del, end, pg_up, pg_dn,

	left, right, up, down,

	none
};

enum class button_code : u8 {
	left_mouse,
	right_mouse,
	middle_mouse,
	x4_mouse,
	x5_mouse
};

END_NS