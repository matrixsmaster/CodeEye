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
    bool binary;
    int appendix;
    int filter_id;
};

const CEFileType reg_types[] = {
    { "C",   "C Source File", false, 0, 0 },
    { "CPP", "C++ Source File", false, 0, 0 },
    { "H",   "C/C++ Header", false, 0, 0 },
    { "HPP", "C++ Header (HPP)", false, 0, 0 },
    { "ASM", "Assembly Code", false, 0, -1 },
    { "DFM", "Delphi Form File", false, 1, 1 },
    { "XFM", "CLX Form File", false, 1, 1 },
    { "BPR", "Borland Project File", false, 2, -1 },
    { "RC",  "Resource Script", false, 2, -1 },
    { "CLW", "MFC Class Wizard File", false, 2, -1 },
    { "DSW", "MS DevStudio Workspace", false, 2, -1 },
    { "DSP", "MS DevStudio Project File", false, 2, -1 },
    { "RES", "Resource file (binary)", true, 2, -1 },
};

#endif /*FileTypesH*/

