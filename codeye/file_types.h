#ifndef FileTypesH
#define FileTypesH

struct CEFileType {
    const char* ext;
    const char* desc;
    int appendix;
    const char* filter[];
};

static const CEFileType reg_types[] = {
    { "cpp", "C++ Source File", 0, {
        "0123456789",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "abcdefghijklmnopqrstuvwxyz",
        "<>!@$%^&+-|" } },
};
/*
                if (fext.UpperCase()==".H") {
                        descr0 = "C/C++ Header";
                        merge = true;
                }
                if (fext.UpperCase()==".HPP") {
                        descr0 = "C++ Header (HPP)";
                        merge = true;
                }
                if (fext.UpperCase()==".ASM") {
                        descr0 = "Assembler Code";
                        merge = true;
                }
                if (fext.UpperCase()==".DFM") {
                        descr0 = "Delphi Form File";
                        formfile = true;
                        merge = true;
                }
                if (fext.UpperCase()==".XFM") {
                        descr0 = "CLX Form File";
                        formfile = true;
                        merge = true;
                }
                if (fext.UpperCase()==".BPR") {
                        descr0 = "BCB Project File";
                        apd2file = true;
                        merge = true;
                }
                if (fext.UpperCase()==".RC") {
                        descr0 = "Resource Script";
                        apd2file = true;
                        merge = true;
                }
                if (fext.UpperCase()==".CLW") {
                        descr0 = "MFC Class Wizard File";
                        apd2file = true;
                        merge = true;
                }
                if (fext.UpperCase()==".DSW") {
                        descr0 = "MS DevStudio Workspace";
                        apd2file = true;
                        merge = true;
                }
                if (fext.UpperCase()==".DSP") {
                        descr0 = "MS DevStudio Project File";
                        apd2file = true;
                        merge = true;
                }
*/
#endif /*FileTypesH*/

