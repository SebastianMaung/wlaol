
#include "include/general.h"
#include "include/dconv.h"

static UINT32 DCNVnext = 1UL;

static UINT16 SinTable[1025] =
{
	0x0000,0x0064,0x00c9,0x012d,0x0192,0x01f6,0x025b,0x02bf,	/*  0.000 */
	0x0324,0x0388,0x03ed,0x0451,0x04b6,0x051a,0x057f,0x05e3,	/*  0.703 */
	0x0648,0x06ac,0x0711,0x0775,0x07da,0x083e,0x08a3,0x0907,	/*  1.406 */
	0x096c,0x09d0,0x0a35,0x0a99,0x0afe,0x0b62,0x0bc6,0x0c2b,	/*  2.109 */
	0x0c8f,0x0cf4,0x0d58,0x0dbc,0x0e21,0x0e85,0x0eea,0x0f4e,	/*  2.812 */
	0x0fb2,0x1017,0x107b,0x10df,0x1144,0x11a8,0x120c,0x1270,	/*  3.516 */
	0x12d5,0x1339,0x139d,0x1401,0x1466,0x14ca,0x152e,0x1592,	/*  4.219 */
	0x15f6,0x165a,0x16bf,0x1723,0x1787,0x17eb,0x184f,0x18b3,	/*  4.922 */
	0x1917,0x197b,0x19df,0x1a43,0x1aa7,0x1b0b,0x1b6f,0x1bd3,	/*  5.625 */
	0x1c37,0x1c9b,0x1cff,0x1d63,0x1dc7,0x1e2a,0x1e8e,0x1ef2,	/*  6.328 */
	0x1f56,0x1fba,0x201d,0x2081,0x20e5,0x2148,0x21ac,0x2210,	/*  7.031 */
	0x2273,0x22d7,0x233b,0x239e,0x2402,0x2465,0x24c9,0x252c,	/*  7.734 */
	0x2590,0x25f3,0x2656,0x26ba,0x271d,0x2781,0x27e4,0x2847,	/*  8.438 */
	0x28aa,0x290e,0x2971,0x29d4,0x2a37,0x2a9a,0x2afe,0x2b61,	/*  9.141 */
	0x2bc4,0x2c27,0x2c8a,0x2ced,0x2d50,0x2db3,0x2e15,0x2e78,	/*  9.844 */
	0x2edb,0x2f3e,0x2fa1,0x3004,0x3066,0x30c9,0x312c,0x318e,	/* 10.547 */
	0x31f1,0x3254,0x32b6,0x3319,0x337b,0x33de,0x3440,0x34a2,	/* 11.250 */
	0x3505,0x3567,0x35c9,0x362c,0x368e,0x36f0,0x3752,0x37b4,	/* 11.953 */
	0x3817,0x3879,0x38db,0x393d,0x399f,0x3a01,0x3a62,0x3ac4,	/* 12.656 */
	0x3b26,0x3b88,0x3bea,0x3c4b,0x3cad,0x3d0f,0x3d70,0x3dd2,	/* 13.359 */
	0x3e33,0x3e95,0x3ef6,0x3f58,0x3fb9,0x401b,0x407c,0x40dd,	/* 14.062 */
	0x413e,0x41a0,0x4201,0x4262,0x42c3,0x4324,0x4385,0x43e6,	/* 14.766 */
	0x4447,0x44a8,0x4508,0x4569,0x45ca,0x462b,0x468b,0x46ec,	/* 15.469 */
	0x474d,0x47ad,0x480e,0x486e,0x48ce,0x492f,0x498f,0x49ef,	/* 16.172 */
	0x4a50,0x4ab0,0x4b10,0x4b70,0x4bd0,0x4c30,0x4c90,0x4cf0,	/* 16.875 */
	0x4d50,0x4db0,0x4e0f,0x4e6f,0x4ecf,0x4f2e,0x4f8e,0x4fed,	/* 17.578 */
	0x504d,0x50ac,0x510c,0x516b,0x51ca,0x522a,0x5289,0x52e8,	/* 18.281 */
	0x5347,0x53a6,0x5405,0x5464,0x54c3,0x5522,0x5581,0x55df,	/* 18.984 */
	0x563e,0x569d,0x56fb,0x575a,0x57b8,0x5817,0x5875,0x58d3,	/* 19.688 */
	0x5931,0x5990,0x59ee,0x5a4c,0x5aaa,0x5b08,0x5b66,0x5bc4,	/* 20.391 */
	0x5c22,0x5c7f,0x5cdd,0x5d3b,0x5d98,0x5df6,0x5e53,0x5eb1,	/* 21.094 */
	0x5f0e,0x5f6b,0x5fc9,0x6026,0x6083,0x60e0,0x613d,0x619a,	/* 21.797 */
	0x61f7,0x6254,0x62b1,0x630d,0x636a,0x63c7,0x6423,0x6480,	/* 22.500 */
	0x64dc,0x6539,0x6595,0x65f1,0x664d,0x66a9,0x6705,0x6761,	/* 23.203 */
	0x67bd,0x6819,0x6875,0x68d1,0x692d,0x6988,0x69e4,0x6a3f,	/* 23.906 */
	0x6a9b,0x6af6,0x6b51,0x6bad,0x6c08,0x6c63,0x6cbe,0x6d19,	/* 24.609 */
	0x6d74,0x6dcf,0x6e29,0x6e84,0x6edf,0x6f39,0x6f94,0x6fee,	/* 25.312 */
	0x7049,0x70a3,0x70fd,0x7157,0x71b1,0x720c,0x7265,0x72bf,	/* 26.016 */
	0x7319,0x7373,0x73cd,0x7426,0x7480,0x74d9,0x7533,0x758c,	/* 26.719 */
	0x75e5,0x763f,0x7698,0x76f1,0x774a,0x77a3,0x77fb,0x7854,	/* 27.422 */
	0x78ad,0x7906,0x795e,0x79b7,0x7a0f,0x7a67,0x7ac0,0x7b18,	/* 28.125 */
	0x7b70,0x7bc8,0x7c20,0x7c78,0x7cd0,0x7d27,0x7d7f,0x7dd7,	/* 28.828 */
	0x7e2e,0x7e86,0x7edd,0x7f34,0x7f8b,0x7fe2,0x803a,0x8090,	/* 29.531 */
	0x80e7,0x813e,0x8195,0x81ec,0x8242,0x8299,0x82ef,0x8345,	/* 30.234 */
	0x839c,0x83f2,0x8448,0x849e,0x84f4,0x854a,0x85a0,0x85f5,	/* 30.938 */
	0x864b,0x86a1,0x86f6,0x874b,0x87a1,0x87f6,0x884b,0x88a0,	/* 31.641 */
	0x88f5,0x894a,0x899f,0x89f4,0x8a48,0x8a9d,0x8af1,0x8b46,	/* 32.344 */
	0x8b9a,0x8bee,0x8c42,0x8c96,0x8cea,0x8d3e,0x8d92,0x8de6,	/* 33.047 */
	0x8e39,0x8e8d,0x8ee0,0x8f34,0x8f87,0x8fda,0x902d,0x9080,	/* 33.750 */
	0x90d3,0x9126,0x9179,0x91cc,0x921e,0x9271,0x92c3,0x9315,	/* 34.453 */
	0x9368,0x93ba,0x940c,0x945e,0x94b0,0x9502,0x9553,0x95a5,	/* 35.156 */
	0x95f6,0x9648,0x9699,0x96ea,0x973c,0x978d,0x97de,0x982e,	/* 35.859 */
	0x987f,0x98d0,0x9921,0x9971,0x99c2,0x9a12,0x9a62,0x9ab2,	/* 36.562 */
	0x9b02,0x9b52,0x9ba2,0x9bf2,0x9c42,0x9c91,0x9ce1,0x9d30,	/* 37.266 */
	0x9d7f,0x9dcf,0x9e1e,0x9e6d,0x9ebc,0x9f0a,0x9f59,0x9fa8,	/* 37.969 */
	0x9ff6,0xa045,0xa093,0xa0e1,0xa12f,0xa17e,0xa1cb,0xa219,	/* 38.672 */
	0xa267,0xa2b5,0xa302,0xa350,0xa39d,0xa3ea,0xa438,0xa485,	/* 39.375 */
	0xa4d2,0xa51f,0xa56b,0xa5b8,0xa605,0xa651,0xa69d,0xa6ea,	/* 40.078 */
	0xa736,0xa782,0xa7ce,0xa81a,0xa866,0xa8b1,0xa8fd,0xa948,	/* 40.781 */
	0xa994,0xa9df,0xaa2a,0xaa75,0xaac0,0xab0b,0xab56,0xaba0,	/* 41.484 */
	0xabeb,0xac35,0xac80,0xacca,0xad14,0xad5e,0xada8,0xadf2,	/* 42.188 */
	0xae3b,0xae85,0xaece,0xaf18,0xaf61,0xafaa,0xaff3,0xb03c,	/* 42.891 */
	0xb085,0xb0ce,0xb117,0xb15f,0xb1a8,0xb1f0,0xb238,0xb280,	/* 43.594 */
	0xb2c8,0xb310,0xb358,0xb3a0,0xb3e7,0xb42f,0xb476,0xb4bd,	/* 44.297 */
	0xb504,0xb54b,0xb592,0xb5d9,0xb620,0xb667,0xb6ad,0xb6f3,	/* 45.000 */
	0xb73a,0xb780,0xb7c6,0xb80c,0xb852,0xb897,0xb8dd,0xb922,	/* 45.703 */
	0xb968,0xb9ad,0xb9f2,0xba37,0xba7c,0xbac1,0xbb06,0xbb4a,	/* 46.406 */
	0xbb8f,0xbbd3,0xbc17,0xbc5b,0xbca0,0xbce3,0xbd27,0xbd6b,	/* 47.109 */
	0xbdae,0xbdf2,0xbe35,0xbe78,0xbebc,0xbeff,0xbf41,0xbf84,	/* 47.812 */
	0xbfc7,0xc009,0xc04c,0xc08e,0xc0d0,0xc112,0xc154,0xc196,	/* 48.516 */
	0xc1d8,0xc21a,0xc25b,0xc29c,0xc2de,0xc31f,0xc360,0xc3a1,	/* 49.219 */
	0xc3e2,0xc422,0xc463,0xc4a3,0xc4e3,0xc524,0xc564,0xc5a4,	/* 49.922 */
	0xc5e4,0xc623,0xc663,0xc6a2,0xc6e2,0xc721,0xc760,0xc79f,	/* 50.625 */
	0xc7de,0xc81d,0xc85b,0xc89a,0xc8d8,0xc916,0xc955,0xc993,	/* 51.328 */
	0xc9d1,0xca0e,0xca4c,0xca8a,0xcac7,0xcb04,0xcb41,0xcb7f,	/* 52.031 */
	0xcbbb,0xcbf8,0xcc35,0xcc72,0xccae,0xccea,0xcd26,0xcd63,	/* 52.734 */
	0xcd9f,0xcdda,0xce16,0xce52,0xce8d,0xcec8,0xcf04,0xcf3f,	/* 53.438 */
	0xcf7a,0xcfb4,0xcfef,0xd02a,0xd064,0xd09f,0xd0d9,0xd113,	/* 54.141 */
	0xd14d,0xd187,0xd1c0,0xd1fa,0xd233,0xd26d,0xd2a6,0xd2df,	/* 54.844 */
	0xd318,0xd351,0xd389,0xd3c2,0xd3fa,0xd433,0xd46b,0xd4a3,	/* 55.547 */
	0xd4db,0xd512,0xd54a,0xd582,0xd5b9,0xd5f0,0xd627,0xd65f,	/* 56.250 */
	0xd695,0xd6cc,0xd703,0xd739,0xd770,0xd7a6,0xd7dc,0xd812,	/* 56.953 */
	0xd848,0xd87e,0xd8b3,0xd8e9,0xd91e,0xd953,0xd988,0xd9bd,	/* 57.656 */
	0xd9f2,0xda27,0xda5b,0xda90,0xdac4,0xdaf8,0xdb2c,0xdb60,	/* 58.359 */
	0xdb94,0xdbc7,0xdbfb,0xdc2e,0xdc61,0xdc94,0xdcc7,0xdcfa,	/* 59.062 */
	0xdd2d,0xdd5f,0xdd92,0xddc4,0xddf6,0xde28,0xde5a,0xde8c,	/* 59.766 */
	0xdebe,0xdeef,0xdf20,0xdf52,0xdf83,0xdfb4,0xdfe4,0xe015,	/* 60.469 */
	0xe046,0xe076,0xe0a6,0xe0d6,0xe106,0xe136,0xe166,0xe196,	/* 61.172 */
	0xe1c5,0xe1f4,0xe224,0xe253,0xe282,0xe2b0,0xe2df,0xe30d,	/* 61.875 */
	0xe33c,0xe36a,0xe398,0xe3c6,0xe3f4,0xe422,0xe44f,0xe47d,	/* 62.578 */
	0xe4aa,0xe4d7,0xe504,0xe531,0xe55e,0xe58a,0xe5b7,0xe5e3,	/* 63.281 */
	0xe60f,0xe63b,0xe667,0xe693,0xe6be,0xe6ea,0xe715,0xe740,	/* 63.984 */
	0xe76b,0xe796,0xe7c1,0xe7ec,0xe816,0xe841,0xe86b,0xe895,	/* 64.688 */
	0xe8bf,0xe8e9,0xe912,0xe93c,0xe965,0xe98e,0xe9b7,0xe9e0,	/* 65.391 */
	0xea09,0xea32,0xea5a,0xea83,0xeaab,0xead3,0xeafb,0xeb23,	/* 66.094 */
	0xeb4b,0xeb72,0xeb99,0xebc1,0xebe8,0xec0f,0xec36,0xec5c,	/* 66.797 */
	0xec83,0xeca9,0xecd0,0xecf6,0xed1c,0xed41,0xed67,0xed8d,	/* 67.500 */
	0xedb2,0xedd7,0xedfc,0xee21,0xee46,0xee6b,0xee8f,0xeeb4,	/* 68.203 */
	0xeed8,0xeefc,0xef20,0xef44,0xef68,0xef8b,0xefaf,0xefd2,	/* 68.906 */
	0xeff5,0xf018,0xf03b,0xf05d,0xf080,0xf0a2,0xf0c5,0xf0e7,	/* 69.609 */
	0xf109,0xf12a,0xf14c,0xf16d,0xf18f,0xf1b0,0xf1d1,0xf1f2,	/* 70.312 */
	0xf213,0xf233,0xf254,0xf274,0xf294,0xf2b5,0xf2d4,0xf2f4,	/* 71.016 */
	0xf314,0xf333,0xf353,0xf372,0xf391,0xf3b0,0xf3ce,0xf3ed,	/* 71.719 */
	0xf40b,0xf42a,0xf448,0xf466,0xf484,0xf4a1,0xf4bf,0xf4dc,	/* 72.422 */
	0xf4fa,0xf517,0xf534,0xf550,0xf56d,0xf58a,0xf5a6,0xf5c2,	/* 73.125 */
	0xf5de,0xf5fa,0xf616,0xf632,0xf64d,0xf668,0xf684,0xf69f,	/* 73.828 */
	0xf6ba,0xf6d4,0xf6ef,0xf709,0xf724,0xf73e,0xf758,0xf772,	/* 74.531 */
	0xf78b,0xf7a5,0xf7be,0xf7d7,0xf7f1,0xf80a,0xf822,0xf83b,	/* 75.234 */
	0xf853,0xf86c,0xf884,0xf89c,0xf8b4,0xf8cc,0xf8e3,0xf8fb,	/* 75.938 */
	0xf912,0xf929,0xf940,0xf957,0xf96e,0xf984,0xf99b,0xf9b1,	/* 76.641 */
	0xf9c7,0xf9dd,0xf9f3,0xfa09,0xfa1e,0xfa33,0xfa49,0xfa5e,	/* 77.344 */
	0xfa73,0xfa87,0xfa9c,0xfab0,0xfac5,0xfad9,0xfaed,0xfb01,	/* 78.047 */
	0xfb14,0xfb28,0xfb3b,0xfb4e,0xfb61,0xfb74,0xfb87,0xfb9a,	/* 78.750 */
	0xfbac,0xfbbf,0xfbd1,0xfbe3,0xfbf5,0xfc06,0xfc18,0xfc29,	/* 79.453 */
	0xfc3b,0xfc4c,0xfc5d,0xfc6e,0xfc7e,0xfc8f,0xfc9f,0xfcaf,	/* 80.156 */
	0xfcbf,0xfccf,0xfcdf,0xfcef,0xfcfe,0xfd0d,0xfd1c,0xfd2b,	/* 80.859 */
	0xfd3a,0xfd49,0xfd57,0xfd66,0xfd74,0xfd82,0xfd90,0xfd9e,	/* 81.562 */
	0xfdab,0xfdb9,0xfdc6,0xfdd3,0xfde0,0xfded,0xfdfa,0xfe06,	/* 82.266 */
	0xfe13,0xfe1f,0xfe2b,0xfe37,0xfe43,0xfe4e,0xfe5a,0xfe65,	/* 82.969 */
	0xfe70,0xfe7b,0xfe86,0xfe91,0xfe9b,0xfea6,0xfeb0,0xfeba,	/* 83.672 */
	0xfec4,0xfece,0xfed7,0xfee1,0xfeea,0xfef3,0xfefc,0xff05,	/* 84.375 */
	0xff0e,0xff16,0xff1f,0xff27,0xff2f,0xff37,0xff3f,0xff46,	/* 85.078 */
	0xff4e,0xff55,0xff5c,0xff63,0xff6a,0xff71,0xff78,0xff7e,	/* 85.781 */
	0xff84,0xff8a,0xff90,0xff96,0xff9c,0xffa1,0xffa6,0xffac,	/* 86.484 */
	0xffb1,0xffb5,0xffba,0xffbf,0xffc3,0xffc7,0xffcb,0xffcf,	/* 87.188 */
	0xffd3,0xffd7,0xffda,0xffdd,0xffe1,0xffe4,0xffe7,0xffe9,	/* 87.891 */
	0xffec,0xffee,0xfff0,0xfff2,0xfff4,0xfff6,0xfff8,0xfff9,	/* 88.594 */
	0xfffb,0xfffc,0xfffd,0xfffe,0xfffe,0xffff,0xffff,0xffff,	/* 89.297 */
	0x0000														/* 90.000 */
};

static UINT16 AtanTable[1025] =
{
	0x0000,0x000a,0x0014,0x001e,0x0028,0x0032,0x003d,0x0047,	 /*    0 0.000000 : 0.00 */
	0x0051,0x005b,0x0065,0x0070,0x007a,0x0084,0x008e,0x0098,	 /*    8 0.007813 : 0.45 */
	0x00a2,0x00ad,0x00b7,0x00c1,0x00cb,0x00d5,0x00e0,0x00ea,	 /*   16 0.015625 : 0.90 */
	0x00f4,0x00fe,0x0108,0x0112,0x011d,0x0127,0x0131,0x013b,	 /*   24 0.023438 : 1.34 */
	0x0145,0x0150,0x015a,0x0164,0x016e,0x0178,0x0182,0x018d,	 /*   32 0.031250 : 1.79 */
	0x0197,0x01a1,0x01ab,0x01b5,0x01bf,0x01ca,0x01d4,0x01de,	 /*   40 0.039063 : 2.24 */
	0x01e8,0x01f2,0x01fc,0x0207,0x0211,0x021b,0x0225,0x022f,	 /*   48 0.046875 : 2.68 */
	0x0239,0x0243,0x024e,0x0258,0x0262,0x026c,0x0276,0x0280,	 /*   56 0.054688 : 3.13 */
	0x028b,0x0295,0x029f,0x02a9,0x02b3,0x02bd,0x02c7,0x02d2,	 /*   64 0.062500 : 3.58 */
	0x02dc,0x02e6,0x02f0,0x02fa,0x0304,0x030e,0x0318,0x0323,	 /*   72 0.070313 : 4.02 */
	0x032d,0x0337,0x0341,0x034b,0x0355,0x035f,0x0369,0x0374,	 /*   80 0.078125 : 4.47 */
	0x037e,0x0388,0x0392,0x039c,0x03a6,0x03b0,0x03ba,0x03c4,	 /*   88 0.085938 : 4.91 */
	0x03ce,0x03d9,0x03e3,0x03ed,0x03f7,0x0401,0x040b,0x0415,	 /*   96 0.093750 : 5.36 */
	0x041f,0x0429,0x0433,0x043d,0x0448,0x0452,0x045c,0x0466,	 /*  104 0.101563 : 5.80 */
	0x0470,0x047a,0x0484,0x048e,0x0498,0x04a2,0x04ac,0x04b6,	 /*  112 0.109375 : 6.24 */
	0x04c0,0x04ca,0x04d4,0x04de,0x04e8,0x04f2,0x04fd,0x0507,	 /*  120 0.117188 : 6.68 */
	0x0511,0x051b,0x0525,0x052f,0x0539,0x0543,0x054d,0x0557,	 /*  128 0.125000 : 7.13 */
	0x0561,0x056b,0x0575,0x057f,0x0589,0x0593,0x059d,0x05a7,	 /*  136 0.132813 : 7.57 */
	0x05b1,0x05bb,0x05c5,0x05cf,0x05d9,0x05e3,0x05ed,0x05f7,	 /*  144 0.140625 : 8.00 */
	0x0601,0x060b,0x0614,0x061e,0x0628,0x0632,0x063c,0x0646,	 /*  152 0.148438 : 8.44 */
	0x0650,0x065a,0x0664,0x066e,0x0678,0x0682,0x068c,0x0696,	 /*  160 0.156250 : 8.88 */
	0x06a0,0x06aa,0x06b3,0x06bd,0x06c7,0x06d1,0x06db,0x06e5,	 /*  168 0.164063 : 9.32 */
	0x06ef,0x06f9,0x0703,0x070d,0x0716,0x0720,0x072a,0x0734,	 /*  176 0.171875 : 9.75 */
	0x073e,0x0748,0x0752,0x075c,0x0765,0x076f,0x0779,0x0783,	 /*  184 0.179688 : 10.19 */
	0x078d,0x0797,0x07a0,0x07aa,0x07b4,0x07be,0x07c8,0x07d2,	 /*  192 0.187500 : 10.62 */
	0x07db,0x07e5,0x07ef,0x07f9,0x0803,0x080c,0x0816,0x0820,	 /*  200 0.195313 : 11.05 */
	0x082a,0x0834,0x083d,0x0847,0x0851,0x085b,0x0864,0x086e,	 /*  208 0.203125 : 11.48 */
	0x0878,0x0882,0x088b,0x0895,0x089f,0x08a9,0x08b2,0x08bc,	 /*  216 0.210938 : 11.91 */
	0x08c6,0x08cf,0x08d9,0x08e3,0x08ed,0x08f6,0x0900,0x090a,	 /*  224 0.218750 : 12.34 */
	0x0913,0x091d,0x0927,0x0930,0x093a,0x0944,0x094d,0x0957,	 /*  232 0.226563 : 12.77 */
	0x0961,0x096a,0x0974,0x097e,0x0987,0x0991,0x099b,0x09a4,	 /*  240 0.234375 : 13.19 */
	0x09ae,0x09b8,0x09c1,0x09cb,0x09d4,0x09de,0x09e8,0x09f1,	 /*  248 0.242188 : 13.61 */
	0x09fb,0x0a04,0x0a0e,0x0a17,0x0a21,0x0a2b,0x0a34,0x0a3e,	 /*  256 0.250000 : 14.04 */
	0x0a47,0x0a51,0x0a5a,0x0a64,0x0a6d,0x0a77,0x0a80,0x0a8a,	 /*  264 0.257813 : 14.46 */
	0x0a94,0x0a9d,0x0aa7,0x0ab0,0x0aba,0x0ac3,0x0acd,0x0ad6,	 /*  272 0.265625 : 14.88 */
	0x0ae0,0x0ae9,0x0af2,0x0afc,0x0b05,0x0b0f,0x0b18,0x0b22,	 /*  280 0.273438 : 15.29 */
	0x0b2b,0x0b35,0x0b3e,0x0b47,0x0b51,0x0b5a,0x0b64,0x0b6d,	 /*  288 0.281250 : 15.71 */
	0x0b77,0x0b80,0x0b89,0x0b93,0x0b9c,0x0ba5,0x0baf,0x0bb8,	 /*  296 0.289063 : 16.12 */
	0x0bc2,0x0bcb,0x0bd4,0x0bde,0x0be7,0x0bf0,0x0bfa,0x0c03,	 /*  304 0.296875 : 16.53 */
	0x0c0c,0x0c16,0x0c1f,0x0c28,0x0c32,0x0c3b,0x0c44,0x0c4d,	 /*  312 0.304688 : 16.95 */
	0x0c57,0x0c60,0x0c69,0x0c73,0x0c7c,0x0c85,0x0c8e,0x0c98,	 /*  320 0.312500 : 17.35 */
	0x0ca1,0x0caa,0x0cb3,0x0cbc,0x0cc6,0x0ccf,0x0cd8,0x0ce1,	 /*  328 0.320313 : 17.76 */
	0x0ceb,0x0cf4,0x0cfd,0x0d06,0x0d0f,0x0d18,0x0d22,0x0d2b,	 /*  336 0.328125 : 18.17 */
	0x0d34,0x0d3d,0x0d46,0x0d4f,0x0d58,0x0d62,0x0d6b,0x0d74,	 /*  344 0.335938 : 18.57 */
	0x0d7d,0x0d86,0x0d8f,0x0d98,0x0da1,0x0daa,0x0db4,0x0dbd,	 /*  352 0.343750 : 18.97 */
	0x0dc6,0x0dcf,0x0dd8,0x0de1,0x0dea,0x0df3,0x0dfc,0x0e05,	 /*  360 0.351563 : 19.37 */
	0x0e0e,0x0e17,0x0e20,0x0e29,0x0e32,0x0e3b,0x0e44,0x0e4d,	 /*  368 0.359375 : 19.77 */
	0x0e56,0x0e5f,0x0e68,0x0e71,0x0e7a,0x0e83,0x0e8c,0x0e95,	 /*  376 0.367188 : 20.16 */
	0x0e9e,0x0ea7,0x0eaf,0x0eb8,0x0ec1,0x0eca,0x0ed3,0x0edc,	 /*  384 0.375000 : 20.56 */
	0x0ee5,0x0eee,0x0ef7,0x0eff,0x0f08,0x0f11,0x0f1a,0x0f23,	 /*  392 0.382813 : 20.95 */
	0x0f2c,0x0f35,0x0f3d,0x0f46,0x0f4f,0x0f58,0x0f61,0x0f69,	 /*  400 0.390625 : 21.34 */
	0x0f72,0x0f7b,0x0f84,0x0f8d,0x0f95,0x0f9e,0x0fa7,0x0fb0,	 /*  408 0.398438 : 21.72 */
	0x0fb8,0x0fc1,0x0fca,0x0fd3,0x0fdb,0x0fe4,0x0fed,0x0ff5,	 /*  416 0.406250 : 22.11 */
	0x0ffe,0x1007,0x1010,0x1018,0x1021,0x102a,0x1032,0x103b,	 /*  424 0.414063 : 22.49 */
	0x1044,0x104c,0x1055,0x105d,0x1066,0x106f,0x1077,0x1080,	 /*  432 0.421875 : 22.87 */
	0x1089,0x1091,0x109a,0x10a2,0x10ab,0x10b3,0x10bc,0x10c5,	 /*  440 0.429688 : 23.25 */
	0x10cd,0x10d6,0x10de,0x10e7,0x10ef,0x10f8,0x1100,0x1109,	 /*  448 0.437500 : 23.63 */
	0x1111,0x111a,0x1122,0x112b,0x1133,0x113c,0x1144,0x114d,	 /*  456 0.445313 : 24.00 */
	0x1155,0x115e,0x1166,0x116e,0x1177,0x117f,0x1188,0x1190,	 /*  464 0.453125 : 24.38 */
	0x1199,0x11a1,0x11a9,0x11b2,0x11ba,0x11c2,0x11cb,0x11d3,	 /*  472 0.460938 : 24.75 */
	0x11dc,0x11e4,0x11ec,0x11f5,0x11fd,0x1205,0x120e,0x1216,	 /*  480 0.468750 : 25.11 */
	0x121e,0x1226,0x122f,0x1237,0x123f,0x1248,0x1250,0x1258,	 /*  488 0.476563 : 25.48 */
	0x1260,0x1269,0x1271,0x1279,0x1281,0x1289,0x1292,0x129a,	 /*  496 0.484375 : 25.84 */
	0x12a2,0x12aa,0x12b3,0x12bb,0x12c3,0x12cb,0x12d3,0x12db,	 /*  504 0.492188 : 26.21 */
	0x12e4,0x12ec,0x12f4,0x12fc,0x1304,0x130c,0x1314,0x131c,	 /*  512 0.500000 : 26.57 */
	0x1325,0x132d,0x1335,0x133d,0x1345,0x134d,0x1355,0x135d,	 /*  520 0.507813 : 26.92 */
	0x1365,0x136d,0x1375,0x137d,0x1385,0x138d,0x1395,0x139d,	 /*  528 0.515625 : 27.28 */
	0x13a5,0x13ad,0x13b5,0x13bd,0x13c5,0x13cd,0x13d5,0x13dd,	 /*  536 0.523438 : 27.63 */
	0x13e5,0x13ed,0x13f5,0x13fd,0x1405,0x140d,0x1415,0x141c,	 /*  544 0.531250 : 27.98 */
	0x1424,0x142c,0x1434,0x143c,0x1444,0x144c,0x1454,0x145b,	 /*  552 0.539063 : 28.33 */
	0x1463,0x146b,0x1473,0x147b,0x1483,0x148a,0x1492,0x149a,	 /*  560 0.546875 : 28.67 */
	0x14a2,0x14aa,0x14b1,0x14b9,0x14c1,0x14c9,0x14d0,0x14d8,	 /*  568 0.554688 : 29.02 */
	0x14e0,0x14e8,0x14ef,0x14f7,0x14ff,0x1507,0x150e,0x1516,	 /*  576 0.562500 : 29.36 */
	0x151e,0x1525,0x152d,0x1535,0x153c,0x1544,0x154c,0x1553,	 /*  584 0.570313 : 29.70 */
	0x155b,0x1563,0x156a,0x1572,0x1579,0x1581,0x1589,0x1590,	 /*  592 0.578125 : 30.03 */
	0x1598,0x159f,0x15a7,0x15ae,0x15b6,0x15be,0x15c5,0x15cd,	 /*  600 0.585938 : 30.37 */
	0x15d4,0x15dc,0x15e3,0x15eb,0x15f2,0x15fa,0x1601,0x1609,	 /*  608 0.593750 : 30.70 */
	0x1610,0x1618,0x161f,0x1627,0x162e,0x1636,0x163d,0x1644,	 /*  616 0.601563 : 31.03 */
	0x164c,0x1653,0x165b,0x1662,0x166a,0x1671,0x1678,0x1680,	 /*  624 0.609375 : 31.36 */
	0x1687,0x168e,0x1696,0x169d,0x16a5,0x16ac,0x16b3,0x16bb,	 /*  632 0.617188 : 31.68 */
	0x16c2,0x16c9,0x16d1,0x16d8,0x16df,0x16e6,0x16ee,0x16f5,	 /*  640 0.625000 : 32.01 */
	0x16fc,0x1704,0x170b,0x1712,0x1719,0x1721,0x1728,0x172f,	 /*  648 0.632813 : 32.33 */
	0x1736,0x173d,0x1745,0x174c,0x1753,0x175a,0x1761,0x1769,	 /*  656 0.640625 : 32.64 */
	0x1770,0x1777,0x177e,0x1785,0x178c,0x1794,0x179b,0x17a2,	 /*  664 0.648438 : 32.96 */
	0x17a9,0x17b0,0x17b7,0x17be,0x17c5,0x17cd,0x17d4,0x17db,	 /*  672 0.656250 : 33.27 */
	0x17e2,0x17e9,0x17f0,0x17f7,0x17fe,0x1805,0x180c,0x1813,	 /*  680 0.664063 : 33.59 */
	0x181a,0x1821,0x1828,0x182f,0x1836,0x183d,0x1844,0x184b,	 /*  688 0.671875 : 33.90 */
	0x1852,0x1859,0x1860,0x1867,0x186e,0x1875,0x187c,0x1883,	 /*  696 0.679688 : 34.20 */
	0x188a,0x1890,0x1897,0x189e,0x18a5,0x18ac,0x18b3,0x18ba,	 /*  704 0.687500 : 34.51 */
	0x18c1,0x18c8,0x18ce,0x18d5,0x18dc,0x18e3,0x18ea,0x18f1,	 /*  712 0.695313 : 34.81 */
	0x18f7,0x18fe,0x1905,0x190c,0x1913,0x1919,0x1920,0x1927,	 /*  720 0.703125 : 35.11 */
	0x192e,0x1935,0x193b,0x1942,0x1949,0x1950,0x1956,0x195d,	 /*  728 0.710938 : 35.41 */
	0x1964,0x196a,0x1971,0x1978,0x197f,0x1985,0x198c,0x1993,	 /*  736 0.718750 : 35.71 */
	0x1999,0x19a0,0x19a7,0x19ad,0x19b4,0x19ba,0x19c1,0x19c8,	 /*  744 0.726563 : 36.00 */
	0x19ce,0x19d5,0x19dc,0x19e2,0x19e9,0x19ef,0x19f6,0x19fd,	 /*  752 0.734375 : 36.29 */
	0x1a03,0x1a0a,0x1a10,0x1a17,0x1a1d,0x1a24,0x1a2a,0x1a31,	 /*  760 0.742188 : 36.58 */
	0x1a37,0x1a3e,0x1a44,0x1a4b,0x1a51,0x1a58,0x1a5e,0x1a65,	 /*  768 0.750000 : 36.87 */
	0x1a6b,0x1a72,0x1a78,0x1a7f,0x1a85,0x1a8c,0x1a92,0x1a99,	 /*  776 0.757813 : 37.16 */
	0x1a9f,0x1aa5,0x1aac,0x1ab2,0x1ab9,0x1abf,0x1ac5,0x1acc,	 /*  784 0.765625 : 37.44 */
	0x1ad2,0x1ad9,0x1adf,0x1ae5,0x1aec,0x1af2,0x1af8,0x1aff,	 /*  792 0.773438 : 37.72 */
	0x1b05,0x1b0b,0x1b12,0x1b18,0x1b1e,0x1b25,0x1b2b,0x1b31,	 /*  800 0.781250 : 38.00 */
	0x1b37,0x1b3e,0x1b44,0x1b4a,0x1b50,0x1b57,0x1b5d,0x1b63,	 /*  808 0.789063 : 38.28 */
	0x1b69,0x1b70,0x1b76,0x1b7c,0x1b82,0x1b88,0x1b8f,0x1b95,	 /*  816 0.796875 : 38.55 */
	0x1b9b,0x1ba1,0x1ba7,0x1bae,0x1bb4,0x1bba,0x1bc0,0x1bc6,	 /*  824 0.804688 : 38.82 */
	0x1bcc,0x1bd2,0x1bd9,0x1bdf,0x1be5,0x1beb,0x1bf1,0x1bf7,	 /*  832 0.812500 : 39.09 */
	0x1bfd,0x1c03,0x1c09,0x1c0f,0x1c16,0x1c1c,0x1c22,0x1c28,	 /*  840 0.820313 : 39.36 */
	0x1c2e,0x1c34,0x1c3a,0x1c40,0x1c46,0x1c4c,0x1c52,0x1c58,	 /*  848 0.828125 : 39.63 */
	0x1c5e,0x1c64,0x1c6a,0x1c70,0x1c76,0x1c7c,0x1c82,0x1c88,	 /*  856 0.835938 : 39.89 */
	0x1c8e,0x1c94,0x1c9a,0x1ca0,0x1ca5,0x1cab,0x1cb1,0x1cb7,	 /*  864 0.843750 : 40.16 */
	0x1cbd,0x1cc3,0x1cc9,0x1ccf,0x1cd5,0x1cdb,0x1ce0,0x1ce6,	 /*  872 0.851563 : 40.42 */
	0x1cec,0x1cf2,0x1cf8,0x1cfe,0x1d04,0x1d09,0x1d0f,0x1d15,	 /*  880 0.859375 : 40.67 */
	0x1d1b,0x1d21,0x1d26,0x1d2c,0x1d32,0x1d38,0x1d3e,0x1d43,	 /*  888 0.867188 : 40.93 */
	0x1d49,0x1d4f,0x1d55,0x1d5a,0x1d60,0x1d66,0x1d6c,0x1d71,	 /*  896 0.875000 : 41.19 */
	0x1d77,0x1d7d,0x1d83,0x1d88,0x1d8e,0x1d94,0x1d99,0x1d9f,	 /*  904 0.882813 : 41.44 */
	0x1da5,0x1daa,0x1db0,0x1db6,0x1dbb,0x1dc1,0x1dc7,0x1dcc,	 /*  912 0.890625 : 41.69 */
	0x1dd2,0x1dd8,0x1ddd,0x1de3,0x1de9,0x1dee,0x1df4,0x1df9,	 /*  920 0.898438 : 41.94 */
	0x1dff,0x1e05,0x1e0a,0x1e10,0x1e15,0x1e1b,0x1e20,0x1e26,	 /*  928 0.906250 : 42.18 */
	0x1e2c,0x1e31,0x1e37,0x1e3c,0x1e42,0x1e47,0x1e4d,0x1e52,	 /*  936 0.914063 : 42.43 */
	0x1e58,0x1e5d,0x1e63,0x1e68,0x1e6e,0x1e73,0x1e79,0x1e7e,	 /*  944 0.921875 : 42.67 */
	0x1e84,0x1e89,0x1e8f,0x1e94,0x1e99,0x1e9f,0x1ea4,0x1eaa,	 /*  952 0.929688 : 42.91 */
	0x1eaf,0x1eb5,0x1eba,0x1ebf,0x1ec5,0x1eca,0x1ed0,0x1ed5,	 /*  960 0.937500 : 43.15 */
	0x1eda,0x1ee0,0x1ee5,0x1eea,0x1ef0,0x1ef5,0x1efb,0x1f00,	 /*  968 0.945313 : 43.39 */
	0x1f05,0x1f0b,0x1f10,0x1f15,0x1f1b,0x1f20,0x1f25,0x1f2a,	 /*  976 0.953125 : 43.63 */
	0x1f30,0x1f35,0x1f3a,0x1f40,0x1f45,0x1f4a,0x1f4f,0x1f55,	 /*  984 0.960938 : 43.86 */
	0x1f5a,0x1f5f,0x1f64,0x1f6a,0x1f6f,0x1f74,0x1f79,0x1f7f,	 /*  992 0.968750 : 44.09 */
	0x1f84,0x1f89,0x1f8e,0x1f93,0x1f99,0x1f9e,0x1fa3,0x1fa8,	 /* 1000 0.976563 : 44.32 */
	0x1fad,0x1fb3,0x1fb8,0x1fbd,0x1fc2,0x1fc7,0x1fcc,0x1fd1,	 /* 1008 0.984375 : 44.55 */
	0x1fd7,0x1fdc,0x1fe1,0x1fe6,0x1feb,0x1ff0,0x1ff5,0x1ffa,	 /* 1016 0.992188 : 44.78 */
	0x2000														 /* 1024 1.000000 : 45.00 */
};

UINT16 DCNVrand(UINT16 max);
void DCNVinitRand(UINT16 seed);
void DCNVshuffleDim(int cnt, UINT16 *tbl);
void DCNVshuffleMain(int cnt, UINT16 *tbl);
SINT32 MOTsin(int16_t ang);
SINT32 MOTcos(int16_t ang);
SINT16 MOTatan(SINT32 posX,SINT32 posY);

static SINT16 MOTatanSub(SINT32 posX, SINT32 posY);

UINT16 DCNVrand(UINT16 max)
{
	DCNVnext = DCNVnext * 1103515245UL + 12345UL;

	if(max){
		return ((UINT16)(DCNVnext / 65536) % max);
	}else{
		return 0;
	}
}

void DCNVinitRand(UINT16 seed)
{
	DCNVnext = (UINT32)seed;
}

void DCNVshuffleDim(int cnt, UINT16 *tbl)
{
	int i;

	for(i = 0; i < cnt; i++){
		tbl[i] = i;
	}

	DCNVshuffleMain(cnt, tbl);
}

void DCNVshuffleMain(int cnt, UINT16 *tbl)
{
	int i;
	int seed;
	int tmp;

	for(i = cnt - 1; i > 0; i--)
	{
		seed = DCNVrand((UINT16)(i - 1));
		tmp = tbl[i];
		tbl[i] = tbl[seed];
		tbl[seed] = tmp;
	}
}

SINT32 MOTsin(int16_t ang)
{
	UINT16 deg;

	deg = ang;
	deg  += 8;
	deg >>= 4;

	switch(deg & 0x0c00){
		case 0x0000 :
			return ((SINT32)(SinTable[deg]));
		case 0x0400 :
			if((deg = 2048 - deg) < 1024){
				return ((SINT32)(SinTable[deg]));
			}else{
				return (0x10000L);
			}
		case 0x0800 :
			return (0 - (SINT32)(SinTable[deg - 2048]));
		case 0x0c00 :
			if((deg = 4096 - deg) < 1024){
				return (0 - (SINT32)(SinTable[deg]));
			}else{
				return (0 - 0x10000L);
			}
	}

	return -1;
}

SINT32 MOTcos(int16_t ang)
{
	UINT16 deg;

	deg = ang;
	deg  += 8;
	deg >>= 4;

	switch(deg & 0x0c00){
		case 0x0000 :
			if(deg){
				return ((SINT32)(SinTable[1024 - deg]));
			}else{
				return (0x10000L);
			}
		case 0x0400 :
			return (0 - (SINT32)(SinTable[deg - 1024]));
		case 0x0800 :
			if((deg = 3072 - deg) < 1024){
				return (0 - (SINT32)(SinTable[deg]));
			}else{
				return (0 - 0x10000L);
			}
		case 0x0c00 :
			return ((SINT32)(SinTable[deg - 3072]));
	}

	return -1;
}

SINT16 MOTatan(SINT32 posX,SINT32 posY)
{
	if(posX >= 0){
		if(posY < 0){
			return (0x0000 + MOTatanSub(posX,posY));
		}else{
			return (0x8000 - MOTatanSub(posX,posY));
		}
	}else{
		if(posY >= 0){
			return (0x8000 + MOTatanSub(posX,posY));
		}else{
			return (0x0000 - MOTatanSub(posX,posY));
		}
	}
}

SINT16 MOTatanSub(SINT32 posX, SINT32 posY)
{
	SINT32 absX;
	SINT32 absY;

	if(abs(posX) < 256){
		return (0x0000);
	}

	if(!posY){
		return (0x4000);
	}

	absX = (posX < 0) ? -(posX) : posX;
	absY = (posY < 0) ? -(posY) : posY;

	if(absX > absY){
		return (0x4000 - AtanTable[(absY * 4)/(absX / 256)]);
	}else{
		return (0x0000 + AtanTable[(absX * 4)/(absY / 256)]);
	}
}
