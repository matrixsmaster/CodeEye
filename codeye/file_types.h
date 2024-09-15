#ifndef FileTypesH
#define FileTypesH

#define NUMITEMS(X) (sizeof(X) / sizeof((X)[0]))
#define MAXFILTERS 5

struct CEContentFilter {
    const char* f[MAXFILTERS];
};

const CEContentFilter cont_filters[] = {
    {
        "0123456789",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "abcdefghijklmnopqrstuvwxyz",
        "<>!@$%^&+-|",
        NULL
    },
    {
        "0123456789ABCDEF",
        NULL, NULL, NULL, NULL
    }
};

struct CEFileType {
    const char* ext;
    const char* desc;
    int appendix;
    int filter_id;
};

const CEFileType reg_types[] = {
    { "C",   "C Source File", 0, 0 },
    { "CPP", "C++ Source File", 0, 0 },
    { "H",   "C/C++ Header", 0, 0 },
    { "HPP", "C++ Header (HPP)", 0, 0 },
    { "ASM", "Assembly Code", 0, -1 },
    { "DFM", "Delphi Form File", 1, 1 },
    { "XFM", "CLX Form File", 1, 1 },
    { "BPR", "Borland Project File", 2, -1 },
    { "RC",  "Resource Script", 2, -1 },
    { "CLW", "MFC Class Wizard File", 2, -1 },
    { "DSW", "MS DevStudio Workspace", 2, -1 },
    { "DSP", "MS DevStudio Project File", 2, -1 },
};

#endif /*FileTypesH*/

