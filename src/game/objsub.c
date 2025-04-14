#include "game/objsub.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/window.h"


SHARED_SYM MgInfo mgInfoTbl[] = {
    {
        OVL_M401, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x01), // name_mess
        DATADIR_M401, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 0), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 0), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x00), // inst_mess[0]
        MAKE_MESSID(0x21, 0x01), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x03), // inst_mess[3]
    },
    {
        OVL_M402, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x02), // name_mess
        DATADIR_M402, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 1), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 1), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x04), // inst_mess[0]
        MAKE_MESSID(0x21, 0x05), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x07), // inst_mess[3]
    },
    {
        OVL_M403, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x03), // name_mess
        DATADIR_M403, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 2), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 2), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x08), // inst_mess[0]
        MAKE_MESSID(0x21, 0x09), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x0B), // inst_mess[3]
    },
    {
        OVL_M404, // ovl
        4, // type
        2, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x04), // name_mess
        DATADIR_M404, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 3), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 3), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x0C), // inst_mess[0]
        MAKE_MESSID(0x21, 0x0D), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x0F), // inst_mess[3]
    },
    {
        OVL_M405, // ovl
        0, // type
        2, // flag
        0, // record_idx
        MAKE_MESSID(0x17, 0x05), // name_mess
        DATADIR_M405, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 4), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 4), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x10), // inst_mess[0]
        MAKE_MESSID(0x21, 0x11), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x13), // inst_mess[3]
    },
    {
        OVL_M406, // ovl
        0, // type
        2, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x06), // name_mess
        DATADIR_M406, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 5), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 5), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x14), // inst_mess[0]
        MAKE_MESSID(0x21, 0x15), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x17), // inst_mess[3]
    },
    {
        OVL_M407, // ovl
        0, // type
        3, // flag
        1, // record_idx
        MAKE_MESSID(0x17, 0x07), // name_mess
        DATADIR_M407, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 6), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 6), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x18), // inst_mess[0]
        MAKE_MESSID(0x21, 0x19), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x1B), // inst_mess[3]
    },
    {
        OVL_M408, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x08), // name_mess
        DATADIR_M408, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 7), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 7), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x1C), // inst_mess[0]
        MAKE_MESSID(0x21, 0x1D), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x1F), // inst_mess[3]
    },
    {
        OVL_M409, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x09), // name_mess
        DATADIR_M409, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 8), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 8), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x20), // inst_mess[0]
        MAKE_MESSID(0x21, 0x21), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x23), // inst_mess[3]
    },
    {
        OVL_M410, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x0A), // name_mess
        DATADIR_M410, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 9), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 9), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x24), // inst_mess[0]
        MAKE_MESSID(0x21, 0x25), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x27), // inst_mess[3]
    },
    {
        OVL_M411, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x0B), // name_mess
        DATADIR_M411, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 10), // inst_pic[0]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 11), // inst_pic[1]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 12), // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 62), // mg_pic[0]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 11), // mg_pic[1]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 12), // mg_pic[2]
        MAKE_MESSID(0x21, 0x28), // inst_mess[0]
        MAKE_MESSID(0x21, 0x29), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x2B), // inst_mess[3]
    },
    {
        OVL_M412, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x0C), // name_mess
        DATADIR_M412, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 13), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 13), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x2C), // inst_mess[0]
        MAKE_MESSID(0x21, 0x2D), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x2F), // inst_mess[3]
    },
    {
        OVL_M413, // ovl
        0, // type
        2, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x0D), // name_mess
        DATADIR_M413, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 14), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 63), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x30), // inst_mess[0]
        MAKE_MESSID(0x21, 0x31), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x33), // inst_mess[3]
    },
    {
        OVL_M414, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x0E), // name_mess
        DATADIR_M414, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 15), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 15), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x34), // inst_mess[0]
        MAKE_MESSID(0x21, 0x35), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x37), // inst_mess[3]
    },
    {
        OVL_M415, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x0F), // name_mess
        DATADIR_M415, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 16), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 16), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x38), // inst_mess[0]
        MAKE_MESSID(0x21, 0x39), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x3B), // inst_mess[3]
    },
    {
        OVL_M416, // ovl
        1, // type
        1, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x10), // name_mess
        DATADIR_M416, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 17), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 17), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x3C), // inst_mess[0]
        MAKE_MESSID(0x21, 0x3D), // inst_mess[1]
        MAKE_MESSID(0x21, 0x3E), // inst_mess[2]
        MAKE_MESSID(0x21, 0x3F), // inst_mess[3]
    },
    {
        OVL_M417, // ovl
        1, // type
        1, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x11), // name_mess
        DATADIR_M417, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 18), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 18), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x40), // inst_mess[0]
        MAKE_MESSID(0x21, 0x41), // inst_mess[1]
        MAKE_MESSID(0x21, 0x42), // inst_mess[2]
        MAKE_MESSID(0x21, 0x43), // inst_mess[3]
    },
    {
        OVL_M418, // ovl
        1, // type
        1, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x12), // name_mess
        DATADIR_M418, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 19), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 19), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x44), // inst_mess[0]
        MAKE_MESSID(0x21, 0x45), // inst_mess[1]
        MAKE_MESSID(0x21, 0x46), // inst_mess[2]
        MAKE_MESSID(0x21, 0x47), // inst_mess[3]
    },
    {
        OVL_M419, // ovl
        1, // type
        1, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x13), // name_mess
        DATADIR_M419, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 20), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 20), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x48), // inst_mess[0]
        MAKE_MESSID(0x21, 0x49), // inst_mess[1]
        MAKE_MESSID(0x21, 0x4A), // inst_mess[2]
        MAKE_MESSID(0x21, 0x4B), // inst_mess[3]
    },
    {
        OVL_M420, // ovl
        1, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x14), // name_mess
        DATADIR_M420, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 21), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 21), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x4C), // inst_mess[0]
        MAKE_MESSID(0x21, 0x4D), // inst_mess[1]
        MAKE_MESSID(0x21, 0x4E), // inst_mess[2]
        MAKE_MESSID(0x21, 0x4F), // inst_mess[3]
    },
    {
        OVL_M421, // ovl
        1, // type
        1, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x15), // name_mess
        DATADIR_M421, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 22), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 22), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x50), // inst_mess[0]
        MAKE_MESSID(0x21, 0x51), // inst_mess[1]
        MAKE_MESSID(0x21, 0x52), // inst_mess[2]
        MAKE_MESSID(0x21, 0x53), // inst_mess[3]
    },
    {
        OVL_M422, // ovl
        1, // type
        1, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x16), // name_mess
        DATADIR_M422, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 23), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 23), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x54), // inst_mess[0]
        MAKE_MESSID(0x21, 0x55), // inst_mess[1]
        MAKE_MESSID(0x21, 0x56), // inst_mess[2]
        MAKE_MESSID(0x21, 0x57), // inst_mess[3]
    },
    {
        OVL_M423, // ovl
        1, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x17), // name_mess
        DATADIR_M423, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 24), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 24), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x58), // inst_mess[0]
        MAKE_MESSID(0x21, 0x59), // inst_mess[1]
        MAKE_MESSID(0x21, 0x5A), // inst_mess[2]
        MAKE_MESSID(0x21, 0x5B), // inst_mess[3]
    },
    {
        OVL_M424, // ovl
        1, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x18), // name_mess
        DATADIR_M424, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 25), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 25), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x5C), // inst_mess[0]
        MAKE_MESSID(0x21, 0x5D), // inst_mess[1]
        MAKE_MESSID(0x21, 0x5E), // inst_mess[2]
        MAKE_MESSID(0x21, 0x5F), // inst_mess[3]
    },
    {
        OVL_M425, // ovl
        2, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x19), // name_mess
        DATADIR_M425, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 26), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 26), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x60), // inst_mess[0]
        MAKE_MESSID(0x21, 0x61), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x63), // inst_mess[3]
    },
    {
        OVL_M426, // ovl
        2, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x1A), // name_mess
        DATADIR_M426, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 27), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 27), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x64), // inst_mess[0]
        MAKE_MESSID(0x21, 0x65), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x67), // inst_mess[3]
    },
    {
        OVL_M427, // ovl
        2, // type
        2, // flag
        2, // record_idx
        MAKE_MESSID(0x17, 0x1B), // name_mess
        DATADIR_M427, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 28), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 28), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x68), // inst_mess[0]
        MAKE_MESSID(0x21, 0x69), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x6B), // inst_mess[3]
    },
    {
        OVL_M428, // ovl
        2, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x1C), // name_mess
        DATADIR_M428, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 29), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 29), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x6C), // inst_mess[0]
        MAKE_MESSID(0x21, 0x6D), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x6F), // inst_mess[3]
    },
    {
        OVL_M429, // ovl
        2, // type
        2, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x1D), // name_mess
        DATADIR_M429, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 30), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 64), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x70), // inst_mess[0]
        MAKE_MESSID(0x21, 0x71), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x73), // inst_mess[3]
    },
    {
        OVL_M430, // ovl
        2, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x1E), // name_mess
        DATADIR_M430, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 31), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 31), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x74), // inst_mess[0]
        MAKE_MESSID(0x21, 0x75), // inst_mess[1]
        MAKE_MESSID(0x21, 0x76), // inst_mess[2]
        MAKE_MESSID(0x21, 0x77), // inst_mess[3]
    },
    {
        OVL_M431, // ovl
        2, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x1F), // name_mess
        DATADIR_M431, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 32), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 32), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x78), // inst_mess[0]
        MAKE_MESSID(0x21, 0x79), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x7B), // inst_mess[3]
    },
    {
        OVL_M432, // ovl
        2, // type
        3, // flag
        3, // record_idx
        MAKE_MESSID(0x17, 0x20), // name_mess
        DATADIR_M432, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 33), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 33), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x7C), // inst_mess[0]
        MAKE_MESSID(0x21, 0x7D), // inst_mess[1]
        MAKE_MESSID(0x21, 0x7E), // inst_mess[2]
        MAKE_MESSID(0x21, 0x7F), // inst_mess[3]
    },
    {
        OVL_M433, // ovl
        7, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x21), // name_mess
        DATADIR_M433, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 34), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 34), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x80), // inst_mess[0]
        MAKE_MESSID(0x37, 0x1F), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x83), // inst_mess[3]
    },
    {
        OVL_M434, // ovl
        2, // type
        2, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x22), // name_mess
        DATADIR_M434, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 35), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 35), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x84), // inst_mess[0]
        MAKE_MESSID(0x21, 0x85), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x87), // inst_mess[3]
    },
    {
        OVL_M435, // ovl
        3, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x23), // name_mess
        DATADIR_M435, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 36), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 36), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        MAKE_MESSID(0x21, 0x89), // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M436, // ovl
        3, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x24), // name_mess
        DATADIR_M436, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 37), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 37), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        MAKE_MESSID(0x21, 0x8D), // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M437, // ovl
        3, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x25), // name_mess
        DATADIR_M437, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 38), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 38), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        MAKE_MESSID(0x21, 0x91), // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M438, // ovl
        4, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x26), // name_mess
        DATADIR_M438, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 39), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 39), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x94), // inst_mess[0]
        MAKE_MESSID(0x21, 0x95), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x97), // inst_mess[3]
    },
    {
        OVL_M439, // ovl
        4, // type
        2, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x27), // name_mess
        DATADIR_M439, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 40), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 40), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x98), // inst_mess[0]
        MAKE_MESSID(0x21, 0x99), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x9B), // inst_mess[3]
    },
    {
        OVL_M440, // ovl
        4, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x28), // name_mess
        DATADIR_M440, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 41), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 41), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0x9C), // inst_mess[0]
        MAKE_MESSID(0x21, 0x9D), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0x9F), // inst_mess[3]
    },
    {
        OVL_M441, // ovl
        4, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x29), // name_mess
        DATADIR_M441, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 42), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 42), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xA0), // inst_mess[0]
        MAKE_MESSID(0x21, 0xA1), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xA3), // inst_mess[3]
    },
    {
        OVL_M442, // ovl
        7, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x2A), // name_mess
        DATADIR_M442, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 43), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 65), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xA4), // inst_mess[0]
        MAKE_MESSID(0x37, 0x10), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xA7), // inst_mess[3]
    },
    {
        OVL_M443, // ovl
        0, // type
        2, // flag
        5, // record_idx
        MAKE_MESSID(0x17, 0x2B), // name_mess
        DATADIR_M443, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 44), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 44), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xA8), // inst_mess[0]
        MAKE_MESSID(0x21, 0xA9), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xAB), // inst_mess[3]
    },
    {
        OVL_M444, // ovl
        5, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x2C), // name_mess
        DATADIR_M444, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 45), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 45), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        0, // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M445, // ovl
        6, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x2D), // name_mess
        DATADIR_M445, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 46), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 46), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xAC), // inst_mess[0]
        MAKE_MESSID(0x21, 0xAD), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xAF), // inst_mess[3]
    },
    {
        OVL_M446, // ovl
        6, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x2E), // name_mess
        DATADIR_M446, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 47), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 47), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xB0), // inst_mess[0]
        MAKE_MESSID(0x21, 0xB1), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xB3), // inst_mess[3]
    },
    {
        OVL_M447, // ovl
        6, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x2F), // name_mess
        DATADIR_M447, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 48), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 48), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xB4), // inst_mess[0]
        MAKE_MESSID(0x21, 0xB5), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xB7), // inst_mess[3]
    },
    {
        OVL_M448, // ovl
        6, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x30), // name_mess
        DATADIR_M448, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 49), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 49), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xB8), // inst_mess[0]
        MAKE_MESSID(0x21, 0xB9), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xBB), // inst_mess[3]
    },
    {
        OVL_M449, // ovl
        6, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x31), // name_mess
        DATADIR_M449, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xBC), // inst_mess[0]
        MAKE_MESSID(0x21, 0xBD), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xBF), // inst_mess[3]
    },
    {
        OVL_M450, // ovl
        8, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x32), // name_mess
        DATADIR_M450, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 51), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 51), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xC0), // inst_mess[0]
        MAKE_MESSID(0x21, 0xC1), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xC3), // inst_mess[3]
    },
    {
        OVL_M451, // ovl
        7, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x33), // name_mess
        DATADIR_M451, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 52), // inst_pic[0]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 53), // inst_pic[1]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 54), // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 52), // mg_pic[0]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 53), // mg_pic[1]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 54), // mg_pic[2]
        MAKE_MESSID(0x21, 0xC4), // inst_mess[0]
        MAKE_MESSID(0x37, 0x0D), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xC7), // inst_mess[3]
    },
    {
        OVL_M450, // ovl
        7, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x33), // name_mess
        DATADIR_M450, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 55), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 55), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        0, // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M453, // ovl
        7, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x34), // name_mess
        DATADIR_M450, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xC8), // inst_mess[0]
        MAKE_MESSID(0x37, 0x0A), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xCB), // inst_mess[3]
    },
    {
        OVL_M450, // ovl
        7, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x33), // name_mess
        DATADIR_M450, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 55), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 55), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        0, // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M455, // ovl
        4, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x35), // name_mess
        DATADIR_M455, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 56), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 56), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xCC), // inst_mess[0]
        MAKE_MESSID(0x21, 0xCD), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xCF), // inst_mess[3]
    },
    {
        OVL_M456, // ovl
        0, // type
        3, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x36), // name_mess
        DATADIR_M456, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 57), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 57), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        MAKE_MESSID(0x21, 0xD0), // inst_mess[0]
        MAKE_MESSID(0x21, 0xD1), // inst_mess[1]
        0, // inst_mess[2]
        MAKE_MESSID(0x21, 0xD3), // inst_mess[3]
    },
    {
        OVL_M457, // ovl
        8, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x37), // name_mess
        DATADIR_M457, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 58), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 58), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        0, // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M458, // ovl
        8, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x38), // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 59), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 59), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        0, // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M459, // ovl
        7, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x38), // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        MAKE_MESSID(0x37, 0x13), // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M460, // ovl
        7, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x38), // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        MAKE_MESSID(0x37, 0x16), // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M461, // ovl
        7, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x38), // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        MAKE_MESSID(0x37, 0x19), // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M462, // ovl
        7, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x38), // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        MAKE_MESSID(0x37, 0x1C), // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        OVL_M463, // ovl
        7, // type
        0, // flag
        255, // record_idx
        MAKE_MESSID(0x17, 0x38), // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        MAKE_MESSID(0x37, 0x07), // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
    {
        ((u16)OVL_INVALID), // ovl
        0, // type
        0, // flag
        255, // record_idx
        0, // name_mess
        0, // data_dir
        0, // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        0, // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // inst_mess[0]
        0, // inst_mess[1]
        0, // inst_mess[2]
        0, // inst_mess[3]
    },
};

void MGSeqPracticeExitCheck(omObjData *);

SHARED_SYM s16 mgTypeCurr;
SHARED_SYM s16 mgBattleStar[4];
SHARED_SYM s16 mgBattleStarMax;
SHARED_SYM u8 lbl_801D3E94;
SHARED_SYM u32 mgRecordExtra;
SHARED_SYM s32 mgQuitExtraF;
SHARED_SYM s32 mgPracticeEnableF;
SHARED_SYM s32 mgInstExitEnableF;
SHARED_SYM u8 mgBoardHostEnableF;

SHARED_SYM s16 mgTicTacToeGrid[3][3];
SHARED_SYM u8 mgIndexList[256];
SHARED_SYM GameStat mgGameStatBackup;

s32 omMgIndexGet(s16 overlay)
{
    s32 i;
    MgInfo *info;

    info = mgInfoTbl;

    for (i = 0; info->ovl != ((u16)OVL_INVALID); i++) {
        if (info->ovl == overlay) {
            return (s16)i;
        }
        info++;
    }

    return -1;
}

void omGameSysInit(Process *objman)
{
    s32 i;
    omObjData *obj;

    omSystemKeyCheckSetup(objman);
    Hu3DCameraScissorSet(1, 0, 0, 0x280, 0x1E0);
    omSysPauseEnable(0);

    for (i = 0; i < 4; i++) {
        GWPlayerCoinWinSet(i, 0);
        GWPlayerCoinCollectSet(i, 0);
    }

    if (mgPracticeEnableF != 0) {
        obj = omAddObjEx(objman, 0x7FDC, 0, 0, -1, MGSeqPracticeExitCheck);
        omSetStatBit(obj, 0xA0U);
    }
}

void omVibrate(s16 player, s16 duration, s16 off, s16 on)
{

    if (GWRumbleGet() != 0 && GWPlayerCfg[player].iscom == 0) {
        HuPadRumbleSet(GWPlayerCfg[player].pad_idx, duration, off, on);
    }
}
