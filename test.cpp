#include <iostream>


// Chaque classe de caractère est un bit unique dans un octet.
// Cela nous permet de définir 8 classes distinctes.
typedef enum {
    C_INVALID       = 0,      // 00000000 -> Toujours invalide (ou non classé)
    C_TCHAR         = 1 << 0, // 00000001 -> Caractère pour un token/field-name
    C_VCHAR         = 1 << 1, // 00000010 -> Caractère ASCII visible (exclut l'espace)
    C_OBS_TEXT      = 1 << 2, // 00000100 -> Caractère étendu (valeurs 128-255)
    C_DIGIT         = 1 << 3, // 00001000 -> Chiffre [0-9]
    C_ALPHA         = 1 << 4, // 00010000 -> Lettre [a-zA-Z]
    C_HEXDIG        = 1 << 5, // 00100000 -> Chiffre hexadécimal [0-9a-fA-F]
    C_URI_UNRESERVED= 1 << 6  // 01000000 -> Caractères non-réservés des URIs
} char_class_t;

// Définition et initialisation "brute" pour C++98, avec une ligne par index
// pour une lisibilité maximale.
const unsigned char charLookupTable[256] = {
    C_INVALID, // 0 (NUL)
    C_INVALID, // 1 (SOH)
    C_INVALID, // 2 (STX)
    C_INVALID, // 3 (ETX)
    C_INVALID, // 4 (EOT)
    C_INVALID, // 5 (ENQ)
    C_INVALID, // 6 (ACK)
    C_INVALID, // 7 (BEL)
    C_INVALID, // 8 (BS)
    C_INVALID, // 9 (HT)
    C_INVALID, // 10 (LF)
    C_INVALID, // 11 (VT)
    C_INVALID, // 12 (FF)
    C_INVALID, // 13 (CR)
    C_INVALID, // 14 (SO)
    C_INVALID, // 15 (SI)
    C_INVALID, // 16 (DLE)
    C_INVALID, // 17 (DC1)
    C_INVALID, // 18 (DC2)
    C_INVALID, // 19 (DC3)
    C_INVALID, // 20 (DC4)
    C_INVALID, // 21 (NAK)
    C_INVALID, // 22 (SYN)
    C_INVALID, // 23 (ETB)
    C_INVALID, // 24 (CAN)
    C_INVALID, // 25 (EM)
    C_INVALID, // 26 (SUB)
    C_INVALID, // 27 (ESC)
    C_INVALID, // 28 (FS)
    C_INVALID, // 29 (GS)
    C_INVALID, // 30 (RS)
    C_INVALID, // 31 (US)
    C_INVALID, // 32 (' ')
    C_TCHAR | C_VCHAR, // 33 ('!')
    C_VCHAR, // 34 ('"')
    C_TCHAR | C_VCHAR, // 35 ('#')
    C_TCHAR | C_VCHAR, // 36 ('$')
    C_TCHAR | C_VCHAR, // 37 ('%')
    C_TCHAR | C_VCHAR, // 38 ('&')
    C_TCHAR | C_VCHAR, // 39 (''')
    C_VCHAR, // 40 ('(')
    C_VCHAR, // 41 (')')
    C_TCHAR | C_VCHAR, // 42 ('*')
    C_TCHAR | C_VCHAR, // 43 ('+')
    C_VCHAR, // 44 (',')
    C_TCHAR | C_VCHAR | C_URI_UNRESERVED, // 45 ('-')
    C_TCHAR | C_VCHAR | C_URI_UNRESERVED, // 46 ('.')
    C_VCHAR, // 47 ('/')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 48 ('0')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 49 ('1')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 50 ('2')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 51 ('3')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 52 ('4')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 53 ('5')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 54 ('6')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 55 ('7')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 56 ('8')
    C_TCHAR | C_VCHAR | C_DIGIT | C_HEXDIG | C_URI_UNRESERVED, // 57 ('9')
    C_VCHAR, // 58 (':')
    C_VCHAR, // 59 (';')
    C_VCHAR, // 60 ('<')
    C_VCHAR, // 61 ('=')
    C_VCHAR, // 62 ('>')
    C_VCHAR, // 63 ('?')
    C_VCHAR, // 64 ('@')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 65 ('A')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 66 ('B')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 67 ('C')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 68 ('D')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 69 ('E')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 70 ('F')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 71 ('G')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 72 ('H')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 73 ('I')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 74 ('J')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 75 ('K')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 76 ('L')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 77 ('M')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 78 ('N')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 79 ('O')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 80 ('P')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 81 ('Q')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 82 ('R')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 83 ('S')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 84 ('T')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 85 ('U')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 86 ('V')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 87 ('W')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 88 ('X')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 89 ('Y')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 90 ('Z')
    C_VCHAR, // 91 ('[')
    C_VCHAR, // 92 ('\')
    C_VCHAR, // 93 (']')
    C_TCHAR | C_VCHAR, // 94 ('^')
    C_TCHAR | C_VCHAR | C_URI_UNRESERVED, // 95 ('_')
    C_TCHAR | C_VCHAR, // 96 ('`')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 97 ('a')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 98 ('b')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 99 ('c')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 100 ('d')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 101 ('e')
    C_TCHAR | C_VCHAR | C_ALPHA | C_HEXDIG | C_URI_UNRESERVED, // 102 ('f')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 103 ('g')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 104 ('h')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 105 ('i')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 106 ('j')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 107 ('k')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 108 ('l')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 109 ('m')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 110 ('n')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 111 ('o')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 112 ('p')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 113 ('q')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 114 ('r')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 115 ('s')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 116 ('t')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 117 ('u')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 118 ('v')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 119 ('w')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 120 ('x')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 121 ('y')
    C_TCHAR | C_VCHAR | C_ALPHA | C_URI_UNRESERVED, // 122 ('z')
    C_VCHAR, // 123 ('{')
    C_TCHAR | C_VCHAR, // 124 ('|')
    C_VCHAR, // 125 ('}')
    C_TCHAR | C_VCHAR | C_URI_UNRESERVED, // 126 ('~')
    C_INVALID, // 127 (DEL)
    C_OBS_TEXT, // 128
    C_OBS_TEXT, // 129
    C_OBS_TEXT, // 130
    C_OBS_TEXT, // 131
    C_OBS_TEXT, // 132
    C_OBS_TEXT, // 133
    C_OBS_TEXT, // 134
    C_OBS_TEXT, // 135
    C_OBS_TEXT, // 136
    C_OBS_TEXT, // 137
    C_OBS_TEXT, // 138
    C_OBS_TEXT, // 139
    C_OBS_TEXT, // 140
    C_OBS_TEXT, // 141
    C_OBS_TEXT, // 142
    C_OBS_TEXT, // 143
    C_OBS_TEXT, // 144
    C_OBS_TEXT, // 145
    C_OBS_TEXT, // 146
    C_OBS_TEXT, // 147
    C_OBS_TEXT, // 148
    C_OBS_TEXT, // 149
    C_OBS_TEXT, // 150
    C_OBS_TEXT, // 151
    C_OBS_TEXT, // 152
    C_OBS_TEXT, // 153
    C_OBS_TEXT, // 154
    C_OBS_TEXT, // 155
    C_OBS_TEXT, // 156
    C_OBS_TEXT, // 157
    C_OBS_TEXT, // 158
    C_OBS_TEXT, // 159
    C_OBS_TEXT, // 160
    C_OBS_TEXT, // 161
    C_OBS_TEXT, // 162
    C_OBS_TEXT, // 163
    C_OBS_TEXT, // 164
    C_OBS_TEXT, // 165
    C_OBS_TEXT, // 166
    C_OBS_TEXT, // 167
    C_OBS_TEXT, // 168
    C_OBS_TEXT, // 169
    C_OBS_TEXT, // 170
    C_OBS_TEXT, // 171
    C_OBS_TEXT, // 172
    C_OBS_TEXT, // 173
    C_OBS_TEXT, // 174
    C_OBS_TEXT, // 175
    C_OBS_TEXT, // 176
    C_OBS_TEXT, // 177
    C_OBS_TEXT, // 178
    C_OBS_TEXT, // 179
    C_OBS_TEXT, // 180
    C_OBS_TEXT, // 181
    C_OBS_TEXT, // 182
    C_OBS_TEXT, // 183
    C_OBS_TEXT, // 184
    C_OBS_TEXT, // 185
    C_OBS_TEXT, // 186
    C_OBS_TEXT, // 187
    C_OBS_TEXT, // 188
    C_OBS_TEXT, // 189
    C_OBS_TEXT, // 190
    C_OBS_TEXT, // 191
    C_OBS_TEXT, // 192
    C_OBS_TEXT, // 193
    C_OBS_TEXT, // 194
    C_OBS_TEXT, // 195
    C_OBS_TEXT, // 196
    C_OBS_TEXT, // 197
    C_OBS_TEXT, // 198
    C_OBS_TEXT, // 199
    C_OBS_TEXT, // 200
    C_OBS_TEXT, // 201
    C_OBS_TEXT, // 202
    C_OBS_TEXT, // 203
    C_OBS_TEXT, // 204
    C_OBS_TEXT, // 205
    C_OBS_TEXT, // 206
    C_OBS_TEXT, // 207
    C_OBS_TEXT, // 208
    C_OBS_TEXT, // 209
    C_OBS_TEXT, // 210
    C_OBS_TEXT, // 211
    C_OBS_TEXT, // 212
    C_OBS_TEXT, // 213
    C_OBS_TEXT, // 214
    C_OBS_TEXT, // 215
    C_OBS_TEXT, // 216
    C_OBS_TEXT, // 217
    C_OBS_TEXT, // 218
    C_OBS_TEXT, // 219
    C_OBS_TEXT, // 220
    C_OBS_TEXT, // 221
    C_OBS_TEXT, // 222
    C_OBS_TEXT, // 223
    C_OBS_TEXT, // 224
    C_OBS_TEXT, // 225
    C_OBS_TEXT, // 226
    C_OBS_TEXT, // 227
    C_OBS_TEXT, // 228
    C_OBS_TEXT, // 229
    C_OBS_TEXT, // 230
    C_OBS_TEXT, // 231
    C_OBS_TEXT, // 232
    C_OBS_TEXT, // 233
    C_OBS_TEXT, // 234
    C_OBS_TEXT, // 235
    C_OBS_TEXT, // 236
    C_OBS_TEXT, // 237
    C_OBS_TEXT, // 238
    C_OBS_TEXT, // 239
    C_OBS_TEXT, // 240
    C_OBS_TEXT, // 241
    C_OBS_TEXT, // 242
    C_OBS_TEXT, // 243
    C_OBS_TEXT, // 244
    C_OBS_TEXT, // 245
    C_OBS_TEXT, // 246
    C_OBS_TEXT, // 247
    C_OBS_TEXT, // 248
    C_OBS_TEXT, // 249
    C_OBS_TEXT, // 250
    C_OBS_TEXT, // 251
    C_OBS_TEXT, // 252
    C_OBS_TEXT, // 253
    C_OBS_TEXT, // 254
    C_OBS_TEXT  // 255
};


int main() {
	unsigned char c = 0;
	unsigned char d = 0;
	while (1) {
		d = charLookupTable[c];
		std::cout << c << " ";
	       	for (size_t i = 1; i <= 8; i++) {
			std::cout << (d & (1 << i)) << " ";
		}
		std::cout << std::endl;
		if (c == 255)
			break;
		c++;
	}
}
