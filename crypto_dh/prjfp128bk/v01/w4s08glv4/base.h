#define WINDOW 4
#define CSIZE ((1 << WINDOW)*(64)) /*1 Point (q,r,s,t) takes 64 bytes.*/
#define SLICE 8
#define CACHE static const unsigned char D2[CSIZE*SLICE] = {\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	28,182,247,24,48,212,233,249,67,120,156,125,147,173,2,252,133,81,148,10,124,123,252,126,164,15,159,57,213,75,155,195,223,171,87,94,147,6,114,163,60,167,247,105,19,44,19,234,221,186,22,8,251,36,136,45,164,2,136,34,51,222,56,217,\
	137,103,93,190,1,81,7,36,65,16,238,168,125,4,19,101,136,131,29,18,250,58,53,30,159,196,125,158,166,186,133,152,126,223,186,70,145,171,149,213,75,129,118,69,198,132,202,241,115,204,12,4,179,190,220,25,111,119,231,55,127,48,213,188,\
	195,248,219,156,165,76,213,217,217,64,122,41,190,124,185,207,112,66,246,17,83,47,249,32,254,94,201,86,215,254,130,90,148,34,134,120,77,158,228,66,222,234,229,185,2,39,29,116,25,171,121,177,119,202,36,38,0,114,247,74,245,91,70,195,\
	152,148,78,184,225,199,163,82,100,231,142,195,173,11,4,194,18,49,154,27,37,152,248,133,137,209,93,125,162,119,46,208,69,77,152,91,196,92,91,39,68,32,88,71,114,98,29,193,56,74,18,201,173,131,55,30,40,215,150,87,23,102,211,255,\
	67,177,55,189,37,219,170,156,212,224,202,70,254,180,85,229,234,1,183,216,214,250,43,89,72,131,222,173,194,204,25,232,160,35,231,227,15,196,47,149,99,104,182,92,113,234,80,120,110,0,68,95,162,114,47,126,247,76,143,123,208,153,70,46,\
	173,88,250,234,167,252,12,149,20,12,62,131,246,64,198,230,250,242,208,39,127,253,69,36,222,224,8,143,249,167,230,115,132,96,83,51,119,77,64,255,221,248,17,249,106,203,230,10,207,243,113,200,122,16,117,216,247,133,178,96,53,50,200,98,\
	126,77,137,58,24,214,193,239,29,209,106,111,225,156,165,220,29,8,253,120,219,158,244,19,119,43,246,254,233,47,170,65,53,192,209,2,29,198,3,222,87,14,98,106,110,147,133,105,123,11,220,127,30,220,79,135,56,75,146,216,90,64,251,124,\
	6,203,28,200,73,168,161,70,121,65,44,163,199,48,10,59,78,211,110,153,59,97,125,89,255,72,214,32,86,82,140,5,146,235,53,0,20,42,31,228,194,141,145,118,73,217,66,173,201,94,58,191,104,218,86,211,227,28,39,193,175,193,246,42,\
	7,219,85,19,198,235,91,132,9,19,155,108,218,139,74,37,40,29,154,106,128,41,97,181,228,90,5,205,109,225,168,40,130,222,78,73,85,49,85,170,3,129,219,193,141,173,185,78,146,20,73,129,163,244,79,191,186,246,79,5,204,87,96,22,\
	159,237,166,201,124,138,136,134,170,160,109,225,53,20,113,217,105,61,20,56,164,107,145,95,45,131,163,58,155,42,116,155,129,33,205,40,91,102,120,12,77,220,235,191,9,215,54,255,55,238,9,21,9,176,60,202,232,206,204,143,112,204,71,152,\
	175,98,232,140,179,244,202,120,149,220,7,237,162,3,0,217,152,189,246,63,65,73,56,101,144,94,11,43,98,83,76,208,134,68,186,33,32,53,148,134,251,100,206,228,23,33,176,189,8,180,144,7,117,130,62,60,40,82,84,190,51,237,70,92,\
	105,132,118,7,144,29,78,247,217,153,13,29,2,35,236,30,121,162,98,123,204,221,195,32,133,150,121,109,228,197,99,63,149,134,173,129,136,165,59,67,90,221,95,22,2,125,221,221,116,12,253,202,23,10,117,136,221,248,20,207,239,74,106,166,\
	196,56,65,232,33,195,37,139,118,73,36,140,124,129,17,166,123,87,96,178,247,134,226,86,123,207,78,252,244,149,204,109,84,182,23,97,111,53,245,208,32,180,55,164,142,94,6,252,143,28,49,166,18,119,245,43,162,90,187,75,39,119,84,234,\
	59,85,189,197,57,26,116,29,229,16,191,13,154,104,158,133,249,54,236,130,77,199,206,94,246,116,17,20,163,92,217,158,247,55,182,178,86,15,31,151,183,211,36,38,231,231,14,157,169,223,97,136,163,166,204,77,144,146,76,160,126,71,70,139,\
	31,80,142,182,190,239,153,38,119,64,16,199,3,140,161,51,168,28,186,229,207,90,200,77,104,43,103,179,60,152,138,93,174,178,14,82,78,247,187,183,7,66,21,187,176,117,80,240,103,12,50,68,187,221,43,238,235,177,167,107,79,37,66,233,\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	149,249,214,36,209,91,116,234,52,70,124,119,113,55,181,163,62,181,143,111,6,244,208,31,23,107,140,9,134,99,140,206,243,250,247,201,79,141,215,150,121,164,86,246,122,141,29,155,20,6,215,168,40,137,130,48,83,216,241,114,95,125,175,198,\
	54,119,175,96,87,82,206,171,54,210,54,119,144,16,141,199,49,199,41,209,147,181,28,87,183,140,233,85,73,3,89,140,172,46,34,1,44,10,98,112,13,166,164,35,241,104,191,9,34,174,27,203,85,135,7,64,99,166,84,114,3,182,251,80,\
	61,216,250,119,111,94,24,162,133,97,31,220,158,119,181,196,229,11,36,76,217,183,163,94,134,45,10,254,65,238,75,39,149,113,134,137,5,157,70,138,49,56,214,162,126,38,132,60,229,65,186,148,205,197,11,201,72,133,242,177,81,31,120,166,\
	130,212,60,122,116,11,181,100,95,233,28,48,27,48,245,10,238,17,114,20,100,48,217,236,0,97,81,26,79,37,215,226,45,151,180,29,29,254,168,233,11,247,53,112,195,248,196,167,135,78,159,86,111,232,43,61,241,12,16,49,45,73,234,166,\
	173,54,55,75,211,153,206,63,116,227,62,16,171,204,132,46,46,86,184,86,103,67,239,63,63,45,71,91,127,25,109,126,138,244,104,205,101,241,22,181,96,147,31,244,238,88,157,75,111,195,48,51,155,228,95,23,92,132,122,153,222,205,110,197,\
	124,89,96,177,57,184,123,206,49,201,108,187,191,173,236,221,25,62,79,172,131,111,9,192,172,54,213,110,227,17,165,25,110,97,163,28,43,111,32,3,247,52,170,22,25,176,237,71,54,95,52,9,246,6,255,206,151,104,105,122,236,204,36,10,\
	195,120,245,234,208,103,233,209,228,254,157,80,3,120,147,31,164,62,139,254,179,89,142,97,245,82,10,77,49,219,244,232,125,28,39,104,183,212,241,223,156,11,198,65,205,180,14,142,156,254,89,206,81,8,242,67,178,130,8,83,152,67,33,228,\
	254,104,17,250,40,167,116,138,131,98,210,36,192,100,198,93,223,243,182,200,147,200,182,179,153,137,209,39,120,28,157,165,67,26,238,2,75,122,210,233,228,4,220,57,72,20,60,13,20,194,148,58,175,137,81,144,142,83,42,247,175,92,219,11,\
	117,65,2,38,237,163,102,13,11,222,189,194,166,163,62,200,161,27,80,35,34,11,67,5,202,75,204,92,242,53,40,228,74,225,200,4,82,182,229,110,43,236,176,132,125,231,55,135,35,220,176,77,79,114,108,8,208,136,127,247,12,77,1,53,\
	235,207,44,227,160,167,111,174,31,20,46,240,23,80,84,202,172,174,96,52,184,32,107,216,148,169,179,34,121,247,226,55,121,20,86,169,152,7,189,154,247,111,186,63,92,242,212,127,117,104,60,40,152,161,207,89,84,76,176,168,186,48,207,22,\
	111,219,146,237,13,40,148,212,174,24,1,143,149,95,145,106,222,138,34,141,103,138,246,49,31,44,86,105,29,18,228,233,240,35,219,252,125,143,21,7,53,185,15,231,94,46,112,210,31,174,156,249,147,163,18,5,58,186,114,152,176,115,112,110,\
	190,29,201,26,165,132,93,78,9,59,221,200,58,222,25,242,88,192,98,28,142,184,205,65,28,173,223,245,218,90,159,72,175,215,126,123,151,247,17,150,120,182,149,247,159,142,74,220,169,54,214,185,236,93,130,156,196,21,172,178,176,182,253,117,\
	101,65,201,123,157,176,204,222,165,65,30,76,27,41,88,160,96,35,245,148,87,149,135,173,49,185,25,197,86,88,42,26,81,158,199,11,24,106,222,221,172,250,178,238,126,87,159,193,151,53,102,191,71,174,63,205,26,18,199,222,100,30,97,13,\
	63,226,246,183,16,202,216,0,107,205,35,40,188,181,138,174,1,76,150,91,7,22,213,119,128,2,255,224,133,141,191,56,228,123,253,240,87,13,9,178,35,120,209,240,156,184,26,113,143,158,125,222,140,56,10,21,167,140,189,111,22,115,34,37,\
	69,144,88,4,110,160,128,149,98,139,173,75,223,37,3,102,207,199,192,170,75,141,152,212,45,18,45,3,104,241,218,75,204,249,125,88,218,190,13,66,138,198,202,15,61,219,101,79,131,224,229,215,247,251,80,22,169,250,204,9,205,159,153,255,\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	155,102,206,44,171,166,23,187,12,117,88,17,88,46,91,66,180,228,69,68,9,36,245,90,144,211,95,149,75,171,240,89,251,182,208,7,216,2,226,213,53,113,228,138,241,80,210,112,157,229,229,87,206,15,16,208,144,151,234,61,52,115,180,15,\
	95,238,120,102,78,211,67,223,215,9,228,240,229,166,159,57,158,157,169,189,217,133,125,7,240,148,130,251,194,174,28,142,140,186,38,7,172,77,58,120,23,13,157,74,121,211,186,35,25,166,89,158,244,172,64,87,215,130,22,229,195,134,21,109,\
	1,128,216,107,90,131,133,103,164,137,14,141,38,205,84,13,234,166,80,122,69,45,85,129,215,92,242,63,124,47,171,223,171,80,232,143,246,174,110,121,91,116,222,118,58,88,67,242,145,131,148,142,36,52,238,12,41,55,190,174,181,246,57,252,\
	218,122,124,23,19,219,201,62,81,102,221,160,186,55,103,32,212,87,205,219,133,240,154,173,173,138,185,135,151,212,74,191,180,78,133,229,50,253,0,192,74,243,29,2,73,244,99,66,58,207,138,194,209,186,109,31,91,164,12,6,163,184,164,222,\
	107,234,251,78,212,25,97,16,215,55,116,165,251,35,167,111,3,17,28,55,6,118,75,252,83,37,162,169,92,157,158,0,135,27,176,245,250,190,244,214,241,188,156,213,114,58,16,110,186,171,168,232,216,129,227,2,253,80,38,60,136,43,246,65,\
	69,186,222,42,227,225,132,57,159,183,46,57,180,64,50,28,159,197,64,13,19,1,90,158,216,213,154,98,20,233,83,160,116,209,250,11,171,142,255,206,144,171,122,64,213,119,73,176,77,118,121,115,79,172,120,75,238,178,109,73,65,22,169,108,\
	50,96,135,117,70,212,54,155,193,62,105,133,18,226,77,106,40,200,216,167,113,221,35,10,79,109,80,97,79,0,188,94,6,24,99,65,248,36,138,137,22,224,76,179,26,201,147,237,51,226,31,226,217,51,190,186,163,80,39,71,242,215,210,207,\
	155,155,144,6,6,191,232,130,155,206,97,24,68,216,89,219,223,4,1,171,149,169,41,215,155,254,164,34,192,113,188,237,158,166,179,5,226,66,167,168,165,163,234,218,123,152,69,166,123,3,190,142,208,58,83,230,181,42,235,51,254,127,71,23,\
	33,210,164,161,109,104,54,107,227,215,65,211,4,84,33,149,122,138,213,58,35,223,103,145,212,16,19,217,97,191,30,50,219,252,136,248,35,215,40,190,1,109,226,241,43,70,67,199,162,247,100,255,237,122,148,90,230,50,130,103,206,181,32,137,\
	81,7,34,212,77,66,45,62,183,100,45,184,8,112,199,218,135,155,145,150,2,110,97,53,127,138,40,90,83,21,16,213,90,198,23,131,93,35,168,109,120,165,252,226,18,130,104,11,251,103,26,151,177,226,200,42,227,90,147,97,162,171,151,172,\
	92,75,15,11,253,146,163,216,53,255,19,47,178,237,195,115,56,121,252,23,94,117,165,193,28,246,93,137,31,45,6,2,218,19,160,147,229,4,111,46,62,113,184,245,19,187,24,56,65,60,44,170,217,246,213,67,21,202,172,241,125,121,220,249,\
	97,212,224,121,41,254,78,219,161,30,59,89,188,136,206,240,157,181,176,216,36,225,82,184,157,212,246,175,134,77,79,244,41,80,9,34,202,146,30,241,239,200,214,184,35,144,246,249,108,88,195,254,188,252,155,57,226,114,49,112,20,154,163,73,\
	213,108,20,199,211,75,132,197,173,159,68,223,24,64,219,0,220,181,171,245,133,181,182,7,94,40,148,118,216,166,21,134,130,30,213,79,83,47,84,227,220,131,113,75,204,113,201,89,52,26,198,17,48,184,200,64,228,156,211,25,220,38,36,87,\
	116,29,55,126,22,1,164,87,169,202,112,12,101,183,239,18,247,38,117,223,73,39,150,207,25,44,98,231,145,138,219,66,188,116,148,229,103,205,26,102,186,106,185,124,53,152,166,153,234,72,245,254,13,16,10,208,88,14,20,146,10,159,218,203,\
	124,115,186,149,24,201,103,168,82,120,173,1,122,173,135,81,65,76,202,118,176,24,41,160,199,189,230,132,103,49,7,48,74,105,163,124,191,1,221,10,48,229,99,207,52,203,149,207,74,226,41,37,106,119,210,162,193,242,102,175,157,18,123,138,\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	41,181,131,17,1,100,140,240,132,102,204,17,91,120,217,222,43,82,15,63,212,114,222,163,56,128,179,139,140,103,4,95,13,76,51,101,135,173,132,152,0,85,65,109,33,185,143,47,244,54,224,23,19,34,98,227,194,172,145,208,64,41,183,245,\
	253,224,166,232,120,34,63,161,205,123,12,202,150,107,109,234,87,225,193,108,19,193,68,41,49,73,100,44,84,254,139,47,31,157,191,130,154,95,130,105,225,89,94,215,51,120,183,117,116,210,179,108,141,127,199,159,17,255,115,27,211,195,68,131,\
	251,174,251,141,188,34,129,94,124,134,132,128,85,21,147,214,84,244,52,79,22,38,224,150,146,26,15,115,76,97,153,5,29,64,93,199,110,34,141,75,40,236,121,74,132,230,128,172,155,128,66,151,59,37,240,100,123,226,230,145,7,238,59,218,\
	24,75,131,143,14,10,237,102,98,187,122,226,236,168,183,123,237,75,46,51,248,203,159,243,250,97,116,156,236,189,243,188,183,245,150,100,229,154,108,94,122,115,147,170,23,234,0,118,80,99,88,164,243,94,103,243,205,208,185,38,69,60,194,138,\
	107,89,67,240,51,91,175,149,232,5,167,218,136,201,22,60,250,172,211,110,107,181,23,103,165,52,198,181,45,249,184,13,108,148,130,197,203,201,10,31,148,146,45,62,176,122,197,38,58,216,0,204,171,168,131,201,62,145,184,196,69,107,203,185,\
	229,67,60,178,88,194,109,97,4,152,247,123,4,30,133,92,48,64,57,205,43,181,84,24,95,29,8,14,43,131,254,217,171,127,41,193,129,137,150,222,49,208,139,128,34,92,117,80,17,221,237,194,97,191,60,130,82,94,30,50,40,49,63,48,\
	102,96,74,38,171,38,31,234,136,111,36,44,103,221,21,160,58,79,216,95,173,156,124,124,63,203,224,176,239,220,14,180,131,78,154,154,96,132,233,123,194,77,97,243,6,192,65,26,99,145,194,184,82,60,151,235,100,47,216,210,165,144,200,31,\
	159,248,214,18,115,219,127,168,130,195,158,86,242,238,242,217,28,46,76,239,39,42,214,140,124,27,74,41,118,222,184,7,118,117,52,220,121,112,4,78,84,110,12,194,179,176,212,64,14,72,93,134,32,205,168,32,78,198,140,43,160,48,14,56,\
	114,189,2,12,235,237,244,166,244,44,26,214,10,26,233,152,182,151,122,139,80,197,128,19,230,142,91,20,184,166,71,204,96,143,130,225,167,43,40,128,83,70,93,164,139,65,160,251,174,140,202,27,163,107,240,175,31,18,44,101,19,66,97,16,\
	137,23,27,54,167,63,188,68,46,13,49,112,81,241,20,112,131,178,142,24,20,187,179,217,176,192,81,209,2,17,222,97,183,104,74,161,72,118,203,220,253,19,50,157,40,142,243,5,197,238,150,29,150,34,45,26,30,114,80,99,85,12,119,117,\
	131,142,190,245,44,81,249,228,221,125,197,48,152,91,91,124,161,168,170,172,115,196,253,208,211,114,37,54,255,239,76,87,95,204,148,205,8,244,90,159,76,89,56,132,161,138,132,110,179,106,93,68,132,175,244,129,162,216,9,172,167,198,52,59,\
	114,11,163,116,41,26,210,29,116,28,116,190,102,230,66,41,19,126,227,156,240,247,105,111,231,162,161,78,72,208,221,10,25,22,236,244,98,170,42,51,24,198,103,1,211,200,250,93,12,100,83,47,192,113,217,85,39,224,206,233,60,100,162,200,\
	40,62,105,161,118,156,38,155,206,52,73,172,245,241,242,240,83,173,25,106,163,48,235,208,82,232,3,61,14,227,132,255,39,41,167,249,202,227,90,146,151,223,120,76,61,146,1,239,185,216,152,159,72,96,142,11,177,194,26,107,11,118,2,213,\
	35,223,116,11,84,237,200,133,75,241,42,164,41,100,180,125,8,68,224,221,181,184,70,74,199,87,22,14,29,144,23,56,188,139,98,30,210,189,80,195,49,177,122,120,107,86,63,72,217,29,232,250,179,0,3,46,82,129,227,70,220,153,103,109,\
	206,45,7,247,233,162,139,102,11,67,109,68,210,34,149,162,254,149,54,76,190,109,58,124,84,194,218,222,106,170,8,38,17,46,134,97,250,156,198,127,133,27,98,203,88,55,28,119,210,2,76,228,188,208,168,49,174,45,84,94,169,212,102,138,\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	36,52,198,235,53,210,44,73,205,135,167,67,222,138,180,82,197,120,186,239,122,94,26,156,237,194,103,205,149,44,165,8,185,196,9,37,20,80,78,17,37,85,246,124,87,123,15,99,31,59,25,30,190,36,66,236,225,190,219,58,42,185,48,162,\
	27,162,139,171,193,92,155,191,219,114,124,232,56,228,88,14,12,67,72,243,169,4,102,195,12,227,160,108,25,199,149,1,185,1,130,109,189,137,237,179,31,62,98,52,228,127,34,52,101,189,174,188,128,49,234,253,154,38,111,24,228,40,194,241,\
	6,154,207,104,38,182,201,13,92,30,145,59,237,12,146,58,77,195,176,138,66,21,164,191,219,5,202,171,132,231,189,218,157,93,134,1,40,96,28,243,88,159,189,90,224,226,111,149,204,113,209,125,104,150,139,52,43,231,91,98,54,78,47,247,\
	146,54,123,249,18,82,247,16,56,244,240,5,85,71,107,0,65,96,121,41,27,35,185,111,82,220,109,44,49,153,213,154,204,106,51,232,129,229,238,77,185,226,58,188,174,213,68,51,206,219,8,54,98,216,13,98,254,8,182,53,242,60,182,171,\
	197,199,123,150,7,230,20,195,168,51,54,176,175,190,116,27,109,232,106,173,34,105,15,73,228,26,32,173,205,104,141,210,102,107,65,18,80,6,121,114,76,122,238,162,134,47,45,0,66,17,191,248,210,100,139,23,204,65,89,238,122,17,46,131,\
	29,128,91,72,150,146,78,75,231,31,242,207,0,205,2,215,29,130,169,205,172,196,43,132,106,41,177,17,43,112,147,121,64,102,190,20,11,181,177,11,249,126,96,11,97,144,38,54,9,202,95,242,97,96,227,252,136,65,192,109,156,51,56,212,\
	171,160,81,26,74,223,213,131,211,137,49,125,156,128,49,141,70,127,49,11,133,15,185,168,59,29,139,157,218,246,199,72,91,84,121,196,144,183,71,205,50,26,195,42,153,239,5,243,51,162,91,47,27,94,109,115,3,152,36,44,50,81,62,254,\
	131,33,242,81,159,16,32,101,157,25,126,148,28,166,0,186,62,149,138,105,73,56,182,245,139,186,87,203,207,188,101,162,189,149,178,41,165,177,102,19,23,238,178,119,180,144,109,47,76,145,230,105,24,136,174,29,42,61,48,25,83,199,12,139,\
	168,239,32,23,100,83,113,207,133,146,178,248,194,71,44,191,221,236,125,115,2,56,228,38,250,255,128,247,166,232,252,108,64,49,89,133,157,24,130,10,12,27,173,40,57,227,187,37,150,25,226,22,169,125,189,49,174,189,254,192,74,202,78,124,\
	111,187,24,129,181,168,176,138,26,70,160,174,56,81,28,26,0,245,81,185,44,159,131,22,211,207,135,60,4,120,206,173,185,131,155,201,248,251,198,21,42,132,135,8,121,102,85,54,156,220,39,64,165,149,76,99,88,89,190,227,131,197,151,109,\
	22,24,140,241,13,254,90,85,109,12,3,111,202,36,130,120,177,137,51,254,81,6,183,104,123,24,1,41,4,225,120,29,175,7,180,98,0,189,98,63,143,75,30,39,1,140,71,44,90,172,42,56,75,199,39,20,14,153,113,164,21,154,79,231,\
	131,182,68,12,255,6,10,244,18,80,219,183,78,75,114,160,112,143,66,230,214,235,209,28,233,94,237,183,250,236,208,221,12,108,61,179,117,52,207,217,16,145,222,31,69,195,136,189,9,147,97,84,93,235,0,144,86,63,195,89,150,225,128,89,\
	73,137,46,236,31,95,249,139,184,37,204,121,10,62,211,69,211,8,6,3,221,25,245,8,184,192,133,24,17,144,237,247,219,167,115,145,125,30,69,127,173,176,234,152,142,40,188,238,78,22,148,3,216,86,209,41,193,249,167,87,194,69,127,79,\
	86,46,164,92,186,248,203,124,255,52,116,54,198,117,62,166,223,134,185,144,48,117,168,223,157,205,116,139,89,129,43,86,143,87,132,233,82,174,41,209,52,157,3,200,235,7,15,96,23,64,242,209,82,241,150,26,220,155,139,183,159,92,21,70,\
	182,179,213,107,50,140,75,120,184,101,247,122,48,248,174,238,38,18,251,59,208,204,230,214,154,207,178,153,255,13,115,240,88,232,158,246,75,74,213,167,122,215,112,29,103,164,201,245,15,84,22,111,213,186,32,232,131,136,1,90,217,73,218,196,\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	29,187,250,156,124,118,37,16,220,148,211,194,225,201,237,72,54,149,89,32,222,79,253,47,50,192,13,106,241,252,100,235,25,132,77,37,249,24,169,198,38,28,234,80,160,255,255,177,17,100,65,11,12,8,68,33,31,78,45,38,224,217,233,159,\
	136,52,82,189,61,117,234,161,61,171,255,3,210,172,217,103,229,202,109,239,112,86,48,171,145,66,37,74,1,135,92,122,138,213,63,242,196,177,77,212,49,197,149,60,170,149,194,77,194,65,2,104,92,161,32,204,168,112,92,246,171,30,19,169,\
	250,22,113,239,21,180,162,135,202,145,169,79,57,178,193,70,139,41,208,254,27,10,108,252,57,37,172,85,77,114,3,86,237,236,235,191,253,4,228,230,191,194,219,44,159,129,138,37,136,113,213,46,112,61,1,102,133,183,53,57,148,231,49,26,\
	5,163,77,255,210,195,178,136,29,51,95,174,101,157,16,135,7,68,194,91,206,94,130,235,34,204,92,219,44,62,11,140,150,19,122,202,210,218,47,130,89,37,44,177,13,186,156,105,79,35,229,169,250,7,135,47,132,195,71,223,148,193,200,151,\
	70,12,202,38,4,225,84,170,158,186,104,191,10,7,216,97,5,231,23,42,176,142,101,30,229,179,184,205,152,44,119,45,241,136,236,115,111,245,0,222,170,159,191,164,149,43,168,198,93,13,88,80,124,236,68,141,1,3,190,40,156,227,78,242,\
	51,242,76,162,26,17,245,133,241,3,57,54,38,168,15,16,84,52,47,153,47,84,29,77,125,153,248,91,162,16,253,244,4,18,74,242,229,224,18,174,36,239,134,105,42,50,201,77,65,236,110,66,18,211,181,26,63,27,91,71,163,188,226,251,\
	51,255,96,37,231,57,147,159,250,121,55,154,85,101,94,79,85,42,64,4,83,166,21,78,48,23,132,41,254,121,54,196,239,202,82,80,122,43,64,141,226,202,135,42,66,186,29,15,23,207,25,115,249,231,187,250,64,228,168,204,16,108,207,78,\
	74,219,230,103,116,133,136,92,126,96,208,225,70,200,78,70,133,238,219,33,145,232,159,44,145,181,111,157,211,78,6,193,122,211,154,230,228,122,125,128,114,189,226,12,167,36,63,37,174,24,136,189,167,85,184,82,108,27,28,177,165,171,126,118,\
	19,255,229,123,57,200,84,48,227,139,142,110,172,84,51,69,221,111,30,62,27,70,94,13,37,167,236,52,211,232,82,155,226,42,88,138,165,212,203,211,165,193,7,158,109,92,132,97,192,21,240,154,235,62,83,36,184,98,178,171,173,49,152,127,\
	26,252,172,95,41,190,75,38,95,52,180,128,196,72,186,63,159,163,205,223,121,75,41,213,4,59,254,16,221,10,22,57,154,231,5,115,235,183,252,235,90,133,11,52,185,105,83,186,154,105,230,231,53,251,218,99,33,145,133,101,161,66,71,171,\
	161,181,209,254,189,108,248,78,240,7,222,174,98,244,168,140,56,221,101,150,82,14,99,219,185,25,253,41,3,225,37,21,62,255,229,16,230,248,4,124,151,186,184,149,140,224,206,153,72,198,204,25,60,111,234,112,139,90,80,34,163,110,161,87,\
	39,107,154,79,155,219,243,8,125,237,135,43,192,74,188,126,221,26,246,132,96,170,232,35,52,216,116,115,213,229,200,98,210,180,126,84,14,58,4,8,97,107,52,224,39,49,162,86,81,75,133,129,33,234,37,166,183,145,253,64,65,3,251,200,\
	183,162,16,213,47,166,207,92,18,232,7,98,143,122,205,125,94,67,100,247,149,38,96,41,52,220,85,182,63,167,162,99,240,123,166,195,195,187,54,108,109,189,231,58,157,99,57,207,47,249,49,73,130,153,63,92,186,113,245,247,156,138,171,106,\
	45,163,225,160,227,87,26,196,56,250,99,108,117,179,214,218,29,220,205,223,107,193,115,95,4,130,250,17,84,28,0,90,115,199,169,76,193,165,229,253,19,34,98,189,37,234,219,119,35,184,28,235,114,161,16,148,23,183,63,249,146,123,159,73,\
	186,157,33,90,254,66,22,238,198,42,118,98,47,236,169,2,250,174,40,88,46,199,30,20,222,10,181,14,239,56,44,89,30,21,85,202,118,107,140,30,92,59,149,126,223,0,105,149,124,26,237,32,221,9,61,209,106,208,73,219,113,48,153,11,\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	11,134,90,202,93,205,168,132,203,50,230,47,249,161,219,166,89,29,89,225,38,162,19,50,141,239,160,207,40,246,80,29,225,189,255,189,158,162,81,56,207,217,196,187,196,171,56,104,99,23,141,174,150,52,131,79,77,70,111,211,171,101,52,28,\
	248,88,165,112,210,92,198,100,61,196,54,216,149,58,169,58,179,36,175,206,140,76,126,253,160,0,61,29,61,254,221,244,215,151,36,222,7,39,173,51,158,9,136,223,193,7,225,2,160,120,7,55,4,21,44,148,242,101,61,176,58,113,57,162,\
	25,14,154,160,48,142,187,102,51,231,54,95,73,225,213,164,8,225,126,55,189,241,184,27,108,169,153,179,109,58,228,44,112,154,245,74,111,192,45,75,135,237,215,36,220,52,111,175,160,143,231,255,244,154,44,108,172,248,0,213,77,233,196,36,\
	237,119,1,240,41,163,68,219,210,60,255,242,105,165,165,6,192,223,77,177,167,135,168,136,186,208,61,81,159,84,140,29,158,21,117,209,216,83,66,185,8,250,209,159,69,230,188,80,173,141,66,54,9,100,78,20,91,77,113,128,148,9,239,32,\
	213,53,122,89,0,80,54,72,82,88,101,71,248,127,176,170,235,22,243,111,134,205,46,208,181,85,53,164,182,228,148,197,84,111,17,146,0,126,227,226,244,166,178,243,25,97,67,203,167,97,77,237,228,117,189,73,133,37,247,172,240,70,97,16,\
	175,40,93,50,0,26,250,96,134,236,202,154,86,251,154,199,172,192,8,0,13,116,201,208,208,249,25,26,126,50,226,101,124,252,108,87,232,142,107,117,204,225,11,193,42,248,158,166,154,216,101,89,170,205,2,131,120,98,132,30,9,152,72,189,\
	146,203,217,40,47,178,250,230,86,130,74,168,87,67,123,182,49,41,225,167,47,14,248,246,44,30,160,154,128,208,237,88,222,125,123,197,72,126,76,55,206,87,84,67,189,143,4,6,138,174,9,181,252,65,219,226,252,118,136,29,243,31,240,10,\
	212,189,162,100,220,63,203,179,46,74,205,9,110,110,48,104,190,120,193,200,51,212,241,57,137,221,61,24,88,38,122,46,227,20,15,231,1,83,9,237,16,161,18,17,3,36,214,55,103,86,220,160,133,195,173,92,118,15,152,249,2,81,234,162,\
	163,249,214,185,10,168,202,31,127,141,187,213,5,149,190,14,175,138,192,16,151,156,152,60,224,246,61,114,20,93,105,246,140,252,31,84,141,35,250,112,128,37,6,187,202,251,123,144,141,69,225,110,180,2,204,227,182,26,78,37,124,145,126,72,\
	42,246,65,116,107,116,141,120,4,163,128,90,159,225,236,54,211,114,60,49,169,103,22,227,15,147,69,223,115,123,84,180,137,14,64,8,88,26,157,54,127,41,149,41,99,44,217,166,185,70,94,142,174,189,53,91,51,75,201,147,218,236,205,177,\
	165,31,193,73,101,64,184,29,136,175,229,166,148,195,133,164,131,104,220,120,206,35,43,124,82,133,66,31,55,9,108,102,17,211,146,171,206,245,94,85,138,91,73,24,191,209,110,74,238,235,51,155,49,128,43,41,15,254,94,148,67,113,200,147,\
	194,150,249,115,25,201,115,246,47,45,222,208,243,148,67,128,126,195,100,24,15,184,148,112,185,132,78,104,59,167,199,27,219,227,244,65,183,85,47,163,124,199,193,13,53,110,126,246,159,20,212,40,59,234,233,140,249,248,98,111,60,205,123,35,\
	13,22,170,64,243,70,162,73,143,253,249,155,156,230,118,90,50,34,155,124,209,101,102,116,45,35,188,44,112,178,166,164,219,239,169,50,49,45,196,164,250,6,166,102,245,61,32,90,177,54,16,58,5,175,128,193,3,219,22,181,170,34,249,189,\
	80,246,127,146,79,44,229,19,41,154,69,115,41,200,25,156,188,41,90,68,21,254,181,168,211,11,141,198,167,85,1,97,239,156,187,106,199,23,70,175,251,153,146,46,222,16,120,159,76,198,144,122,197,87,247,124,226,233,212,249,67,49,198,155,\
	59,33,3,130,137,156,253,193,113,209,244,104,12,103,243,3,60,6,145,229,254,253,55,119,173,245,56,72,47,155,69,96,208,242,225,73,13,121,203,26,233,73,83,253,163,195,34,139,238,147,5,91,233,139,42,179,233,14,250,174,160,209,182,126,\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	183,143,31,41,18,240,219,148,33,252,47,250,69,160,139,216,252,68,150,237,94,233,137,214,244,23,33,138,146,212,13,19,102,122,229,172,89,248,216,184,152,149,115,252,242,225,94,116,224,130,96,119,9,53,213,50,53,54,78,113,169,243,144,153,\
	15,239,40,106,237,159,202,63,170,59,88,155,81,130,205,110,150,149,28,200,4,214,113,205,73,91,208,200,143,14,127,54,45,122,2,30,149,194,93,223,121,208,80,30,191,227,168,246,232,145,4,175,177,13,178,168,96,251,110,66,173,81,226,75,\
	81,201,233,250,193,1,76,150,36,81,56,131,53,89,170,184,124,179,88,116,22,136,123,25,205,137,234,37,219,170,30,236,184,19,180,74,158,179,149,29,108,164,51,188,90,61,25,152,70,123,170,61,239,210,214,54,237,235,69,175,44,129,250,213,\
	253,112,41,6,81,24,24,117,91,40,226,102,182,50,74,6,135,231,169,82,113,76,255,113,18,115,255,3,107,21,34,40,168,63,247,222,59,109,242,242,227,39,59,183,224,197,92,51,56,8,182,170,173,93,9,247,175,229,50,167,90,77,137,50,\
	23,24,17,24,131,237,62,179,87,202,148,49,36,32,66,23,236,249,145,17,39,56,96,54,1,157,84,224,203,215,4,98,111,109,144,88,174,43,195,149,102,203,244,74,3,74,64,26,250,62,137,83,208,50,65,112,220,31,85,89,7,150,74,64,\
	82,59,162,217,113,223,135,139,74,173,84,108,159,15,172,102,67,14,113,138,50,38,237,197,81,248,49,53,244,232,171,148,65,207,35,108,202,164,194,31,128,139,249,159,62,50,121,69,145,81,148,236,194,155,220,190,2,176,94,197,187,90,227,76,\
	137,197,59,8,189,172,51,63,50,223,82,213,11,243,46,40,224,180,151,98,169,32,94,151,12,144,146,209,84,196,237,132,32,25,68,217,216,121,68,10,99,182,39,182,183,88,149,116,159,122,162,142,89,93,107,242,2,141,44,58,196,124,101,3,\
	212,167,111,255,23,1,4,16,106,15,218,176,154,141,194,144,9,138,40,132,118,95,95,54,163,195,52,96,120,68,106,10,18,145,203,214,127,43,119,249,140,43,146,208,84,207,216,123,71,253,38,22,64,37,47,26,21,166,24,170,242,115,108,49,\
	132,146,208,117,57,32,196,90,176,34,69,160,6,143,73,187,196,225,242,133,2,244,209,84,19,219,231,71,23,33,160,75,205,14,87,251,39,11,164,98,181,113,116,51,162,90,52,15,30,169,90,207,130,164,26,140,28,57,117,223,92,89,5,180,\
	208,45,35,183,74,235,243,197,166,67,47,167,92,82,131,124,232,141,1,151,197,125,155,224,131,119,6,138,35,57,54,205,47,137,75,178,171,163,81,8,147,131,154,46,224,26,153,173,51,237,16,161,231,115,191,60,15,64,3,97,231,102,89,236,\
	104,132,45,182,69,161,105,12,155,84,237,35,185,92,154,43,244,49,81,104,92,58,205,89,94,63,157,150,120,55,130,246,193,249,208,178,101,26,254,65,201,127,166,132,0,178,242,251,175,181,201,114,200,236,137,20,29,203,46,210,45,132,223,208,\
	101,37,113,212,38,115,100,55,222,92,78,162,195,41,171,65,65,97,70,59,25,171,145,234,146,83,37,118,237,92,254,186,16,203,128,190,117,181,89,16,40,97,97,54,229,150,109,164,45,24,145,13,179,219,102,105,62,32,205,118,69,136,34,148,\
	232,162,175,212,226,173,2,168,50,238,42,36,142,33,69,220,247,56,170,151,125,16,235,133,216,167,65,160,208,205,208,218,151,60,241,118,16,37,244,247,67,26,218,72,149,234,91,83,211,178,127,174,20,92,34,219,246,115,139,215,148,195,145,88,\
	125,224,180,190,89,113,97,245,219,202,19,102,144,53,152,21,17,65,101,215,142,119,35,191,146,151,103,125,119,206,232,1,226,205,242,191,211,226,120,131,19,146,50,248,53,77,94,112,85,81,101,73,55,51,255,183,159,250,131,228,50,0,205,214,\
	17,169,142,251,94,244,161,240,204,23,131,140,208,161,41,77,84,197,104,189,85,49,105,87,193,23,132,216,201,169,108,116,64,252,78,11,237,59,40,33,211,138,18,44,190,21,225,86,7,221,53,39,72,222,13,238,82,158,43,116,231,140,24,117\
}
