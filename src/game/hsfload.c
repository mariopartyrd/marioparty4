#include "game/hsfload.h"
#include "game/EnvelopeExec.h"
#include "ctype.h"
#include "string.h"


#ifdef BYTESWAPPING
#include "game/memory.h"
#include "port/byteswap.h"
#endif

#define AS_S16(field) (*((s16 *)&(field)))
#define AS_U16(field) (*((u16 *)&(field)))

GXColor rgba[100];
HsfHeader head;
HsfData Model;

static BOOL MotionOnly;
static HsfData *MotionModel;
static void *VertexDataTop;
static void *NormalDataTop;
void *fileptr;
char *StringTable;
char *DicStringTable;
void **NSymIndex;
HsfObject *objtop;
HsfBuffer *vtxtop;
HsfCluster *ClusterTop;
HsfAttribute *AttributeTop;
HsfMaterial *MaterialTop;
#ifdef BYTESWAPPING
HsfBuffer *NormalTop;
HsfBuffer *StTop;
HsfBuffer *ColorTop;
HsfBuffer *FaceTop;
HsfCenv *CenvTop;
HsfPart *PartTop;
HsfBitmap *BitmapTop;
#endif

static void FileLoad(void *data);
static HsfData *SetHsfModel(void);
static void MaterialLoad(void);
static void AttributeLoad(void);
static void SceneLoad(void);
static void ColorLoad(void);
static void VertexLoad(void);
static void NormalLoad(void);
static void STLoad(void);
static void FaceLoad(void);
static void ObjectLoad(void);
static void CenvLoad(void);
static void SkeletonLoad(void);
static void PartLoad(void);
static void ClusterLoad(void);
static void ShapeLoad(void);
static void MapAttrLoad(void);
static void PaletteLoad(void);
static void BitmapLoad(void);
static void MotionLoad(void);
static void MatrixLoad(void);

static s32 SearchObjectSetName(HsfData *data, char *name);
static HsfBuffer *SearchVertexPtr(s32 id);
static HsfBuffer *SearchNormalPtr(s32 id);
static HsfBuffer *SearchStPtr(s32 id);
static HsfBuffer *SearchColorPtr(s32 id);
static HsfBuffer *SearchFacePtr(s32 id);
static HsfCenv *SearchCenvPtr(s32 id);
static HsfPart *SearchPartPtr(s32 id);
static HsfPalette *SearchPalettePtr(s32 id);

static HsfBitmap *SearchBitmapPtr(s32 id);
static char *GetString(u32 *str_ofs);
static char *GetMotionString(u16 *str_ofs);

HsfData *LoadHSF(void *data)
{
    HsfData *hsf;
    Model.root = NULL;
    objtop = NULL;
    FileLoad(data);
    SceneLoad();
    ColorLoad();
    PaletteLoad();
    BitmapLoad();
    MaterialLoad();
    AttributeLoad();
    VertexLoad();
    NormalLoad();
    STLoad();
    FaceLoad();
#ifndef BYTESWAPPING
    ObjectLoad();
#endif
    CenvLoad();
    SkeletonLoad();
    PartLoad();
    ClusterLoad();
    ShapeLoad();
    MapAttrLoad();
    MotionLoad();
    MatrixLoad();
#if BYTESWAPPING
    // to properly set pointers
    ObjectLoad();
#endif
    hsf = SetHsfModel();
    InitEnvelope(hsf);
    objtop = NULL;
    return hsf;
    
}

void ClusterAdjustObject(HsfData *model, HsfData *src_model)
{
    HsfCluster *cluster;
    s32 i;
    if(!src_model) {
        return;
    }
    if(src_model->clusterCnt == 0) {
        return;
    }
    cluster = src_model->cluster;
    if(cluster->adjusted) {
        return;
    }
    cluster->adjusted = 1;
    for(i=0; i<src_model->clusterCnt; i++, cluster++) {
        char *name = cluster->targetName;
        cluster->target = SearchObjectSetName(model, name);
    }
}

static void FileLoad(void *data)
{
#ifdef BYTESWAPPING
    s32 i;
#endif
    fileptr = data;
    memcpy(&head, fileptr, sizeof(HsfHeader));
    memset(&Model, 0, sizeof(HsfData));
#ifdef BYTESWAPPING
    byteswap_hsfheader(&head);
    NSymIndex = HuMemDirectMallocNum(HEAP_DATA, sizeof(void*) * head.symbol.count, MEMORY_DEFAULT_NUM);
    for (i = 0; i < head.symbol.count; i++) {
        u32 *file_symbol_real = (u32 *)((uintptr_t)fileptr + head.symbol.ofs);
        byteswap_u32(&file_symbol_real[i]);
        NSymIndex[i] = (void *)file_symbol_real[i];
    }
    StringTable = (char *)((uintptr_t)fileptr+head.string.ofs);
    ClusterTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfCluster) * head.cluster.count, MEMORY_DEFAULT_NUM);
    for (i = 0; i < head.cluster.count; i++) {
        HsfCluster32b *file_cluster_real = (HsfCluster32b *)((uintptr_t)fileptr + head.cluster.ofs);
        byteswap_hsfcluster(&file_cluster_real[i], &ClusterTop[i]);
    }
    AttributeTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfAttribute) * head.attribute.count, MEMORY_DEFAULT_NUM);
    for (i = 0; i < head.attribute.count; i++) {
        HsfAttribute32b *file_attribute_real = (HsfAttribute32b *)((uintptr_t)fileptr + head.attribute.ofs);
        byteswap_hsfattribute(&file_attribute_real[i], &AttributeTop[i]);
    }
    MaterialTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfMaterial) * head.material.count, MEMORY_DEFAULT_NUM);
    for (i = 0; i < head.material.count; i++) {
        HsfMaterial32b *file_material_real = (HsfMaterial32b *)((uintptr_t)fileptr + head.material.ofs);
        byteswap_hsfmaterial(&file_material_real[i], &MaterialTop[i]);
    }
#else
    NSymIndex = (void **)((uintptr_t)fileptr+head.symbol.ofs);
    StringTable = (char *)((uintptr_t)fileptr+head.string.ofs);
    ClusterTop = (HsfCluster *)((uintptr_t)fileptr+head.cluster.ofs);
    AttributeTop = (HsfAttribute *)((uintptr_t)fileptr + head.attribute.ofs);
    MaterialTop = (HsfMaterial *)((uintptr_t)fileptr + head.material.ofs);
#endif
}

static HsfData *SetHsfModel(void)
{
    HsfData *data = fileptr;
    data->scene = Model.scene;
    data->sceneCnt = Model.sceneCnt;
    data->attribute = Model.attribute;
    data->attributeCnt = Model.attributeCnt;
    data->bitmap = Model.bitmap;
    data->bitmapCnt = Model.bitmapCnt;
    data->cenv = Model.cenv;
    data->cenvCnt = Model.cenvCnt;
    data->skeleton = Model.skeleton;
    data->skeletonCnt = Model.skeletonCnt;
    data->face = Model.face;
    data->faceCnt = Model.faceCnt;
    data->material = Model.material;
    data->materialCnt = Model.materialCnt;
    data->motion = Model.motion;
    data->motionCnt = Model.motionCnt;
    data->normal = Model.normal;
    data->normalCnt = Model.normalCnt;
    data->root = Model.root;
    data->objectCnt = Model.objectCnt;
    data->object = objtop;
    data->matrix = Model.matrix;
    data->matrixCnt = Model.matrixCnt;
    data->palette = Model.palette;
    data->paletteCnt = Model.paletteCnt;
    data->st = Model.st;
    data->stCnt = Model.stCnt;
    data->vertex = Model.vertex;
    data->vertexCnt = Model.vertexCnt;
    data->cenv = Model.cenv;
    data->cenvCnt = Model.cenvCnt;
    data->cluster = Model.cluster;
    data->clusterCnt = Model.clusterCnt;
    data->part = Model.part;
    data->partCnt = Model.partCnt;
    data->shape = Model.shape;
    data->shapeCnt = Model.shapeCnt;
    data->mapAttr = Model.mapAttr;
    data->mapAttrCnt = Model.mapAttrCnt;
#ifdef BYTESWAPPING
    data->symbol = NSymIndex;
#endif
    return data;
}

char *SetName(u32 *str_ofs)
{
    char *ret = GetString(str_ofs);
    return ret;
}

static inline char *SetMotionName(u16 *str_ofs)
{
    char *ret = GetMotionString(str_ofs);
    return ret;
}

static void MaterialLoad(void)
{
    s32 i;
    s32 j;
    if(head.material.count) {
#ifdef BYTESWAPPING
        HsfMaterial *file_mat = MaterialTop;
#else
        HsfMaterial *file_mat = (HsfMaterial *)((uintptr_t)fileptr+head.material.ofs);
#endif
        HsfMaterial *curr_mat;
        HsfMaterial *new_mat;
        for(i=0; i<head.material.count; i++) {
            curr_mat = &file_mat[i];
        }
        new_mat = file_mat;
        Model.material = new_mat;
        Model.materialCnt = head.material.count;
#ifdef BYTESWAPPING
        file_mat = MaterialTop;
#else
        file_mat = (HsfMaterial *)((u32)fileptr+head.material.ofs);
#endif
        for(i=0; i<head.material.count; i++, new_mat++) {
            curr_mat = &file_mat[i];
            new_mat->name = SetName((u32 *)&curr_mat->name);
            new_mat->pass = curr_mat->pass;
            new_mat->vtxMode = curr_mat->vtxMode;
            new_mat->litColor[0] = curr_mat->litColor[0];
            new_mat->litColor[1] = curr_mat->litColor[1];
            new_mat->litColor[2] = curr_mat->litColor[2];
            new_mat->color[0] = curr_mat->color[0];
            new_mat->color[1] = curr_mat->color[1];
            new_mat->color[2] = curr_mat->color[2];
            new_mat->shadowColor[0] = curr_mat->shadowColor[0];
            new_mat->shadowColor[1] = curr_mat->shadowColor[1];
            new_mat->shadowColor[2] = curr_mat->shadowColor[2];
            new_mat->hilite_scale = curr_mat->hilite_scale;
            new_mat->unk18 = curr_mat->unk18;
            new_mat->invAlpha = curr_mat->invAlpha;
            new_mat->unk20[0] = curr_mat->unk20[0];
            new_mat->unk20[1] = curr_mat->unk20[1];
            new_mat->refAlpha = curr_mat->refAlpha;
            new_mat->unk2C = curr_mat->unk2C;
            new_mat->numAttrs = curr_mat->numAttrs;
            new_mat->attrs = (s32 *)(NSymIndex+((u32)curr_mat->attrs));
            rgba[i].r = new_mat->litColor[0];
            rgba[i].g = new_mat->litColor[1];
            rgba[i].b = new_mat->litColor[2];
            rgba[i].a = 255;
            for(j=0; j<new_mat->numAttrs; j++) {
                new_mat->attrs[j] = new_mat->attrs[j];
            }
        }
    }
}

static void AttributeLoad(void)
{
    HsfAttribute *file_attr;
    HsfAttribute *new_attr;
    HsfAttribute *temp_attr;
    s32 i;
    if(head.attribute.count) {
#ifdef BYTESWAPPING
        temp_attr = file_attr = AttributeTop;
#else
        temp_attr = file_attr = (HsfAttribute *)((u32)fileptr+head.attribute.ofs);
#endif
        new_attr = temp_attr;
        Model.attribute = new_attr;
        Model.attributeCnt = head.attribute.count;
        for(i=0; i<head.attribute.count; i++, new_attr++) {
            if((u32)file_attr[i].name != -1) {
                new_attr->name = SetName((u32 *)&file_attr[i].name);
            } else {
                new_attr->name = NULL;
            }
            new_attr->bitmap = SearchBitmapPtr((s32)file_attr[i].bitmap);
        }
    }
}

static void SceneLoad(void)
{
#ifdef BYTESWAPPING
    s32 i;
#endif
    HsfScene *file_scene;
    HsfScene *new_scene;
    if(head.scene.count) {
        file_scene = (HsfScene *)((uintptr_t)fileptr+head.scene.ofs);
#ifdef BYTESWAPPING
        for (i = 0; i < head.scene.count; i++) {
            byteswap_hsfscene(&file_scene[i]);
        }
#endif
        new_scene = file_scene;
        new_scene->end = file_scene->end;
        new_scene->start = file_scene->start;
        Model.scene = new_scene;
        Model.sceneCnt = head.scene.count;
    }
}

static void ColorLoad(void)
{
    s32 i;
    HsfBuffer *file_color;
    HsfBuffer *new_color;
    void *data;
    void *color_data;
    HsfBuffer *temp_color;
    
    if(head.color.count) {
#ifdef BYTESWAPPING
        HsfBuffer32b * file_color_real = (HsfBuffer32b *)((uintptr_t)fileptr + head.color.ofs);
        temp_color = file_color = ColorTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfBuffer) * head.color.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.color.count; i++) {
            byteswap_hsfbuffer(&file_color_real[i], &file_color[i]);
        }
#else
        temp_color = file_color = (HsfBuffer *)((u32)fileptr+head.color.ofs);
        data = &file_color[head.color.count];
        for(i=0; i<head.color.count; i++, file_color++);
#endif
        new_color = temp_color;
        Model.color = new_color;
        Model.colorCnt = head.color.count;
#ifdef BYTESWAPPING
        data = (u16 *)&file_color_real[head.color.count];
#else
        file_color = (HsfBuffer *)((u32)fileptr+head.color.ofs);
        data = &file_color[head.color.count];
#endif
        for(i=0; i<head.color.count; i++, new_color++, file_color++) {
            color_data = file_color->data;
            new_color->name = SetName((u32 *)&file_color->name);
            new_color->data = (void *)((uintptr_t)data+(uintptr_t)color_data);
        }
    }
}

static void VertexLoad(void)
{
    s32 i, j;
    HsfBuffer *file_vertex;
    HsfBuffer *new_vertex;
    void *data;
    HsfVector3f *data_elem;
    void *temp_data;
    
    if(head.vertex.count) {
#ifdef BYTESWAPPING
        HsfBuffer32b *file_vertex_real = (HsfBuffer32b *)((uintptr_t)fileptr + head.vertex.ofs);
        vtxtop = file_vertex = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfBuffer) * head.vertex.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.vertex.count; i++) {
            byteswap_hsfbuffer(&file_vertex_real[i], &file_vertex[i]);
        }
#else
        vtxtop = file_vertex = (HsfBuffer *)((u32)fileptr+head.vertex.ofs);
        data = (void *)&file_vertex[head.vertex.count];
        for(i=0; i<head.vertex.count; i++, file_vertex++) {
            for(j=0; j<(u32)file_vertex->count; j++) {
                data_elem = (HsfVector3f *)(((uintptr_t)data)+((uintptr_t)file_vertex->data)+(j*sizeof(HsfVector3f)));
            }
        }
#endif
        new_vertex = vtxtop;
        Model.vertex = new_vertex;
        Model.vertexCnt = head.vertex.count;
#ifdef BYTESWAPPING
        VertexDataTop = data = (void *)&file_vertex_real[head.vertex.count];
#else
        file_vertex = (HsfBuffer *)((u32)fileptr+head.vertex.ofs);
        VertexDataTop = data = (void *)&file_vertex[head.vertex.count];
#endif
        for(i=0; i<head.vertex.count; i++, new_vertex++, file_vertex++) {
            temp_data = file_vertex->data;
            new_vertex->count = file_vertex->count;
            new_vertex->name = SetName((u32 *)&file_vertex->name);
            new_vertex->data = (void *)((uintptr_t)data + (uintptr_t)temp_data);
            for(j=0; j<new_vertex->count; j++) {
                data_elem = (HsfVector3f *)((uintptr_t)data + (uintptr_t)temp_data + (j * sizeof(HsfVector3f)));
#ifdef BYTESWAPPING
                byteswap_hsfvec3f(data_elem);
#endif
                ((HsfVector3f *)new_vertex->data)[j].x = data_elem->x;
                ((HsfVector3f *)new_vertex->data)[j].y = data_elem->y;
                ((HsfVector3f *)new_vertex->data)[j].z = data_elem->z;
            }
        }
    }
}

static void NormalLoad(void)
{
    s32 i, j;
    void *temp_data;
    HsfBuffer *file_normal;
    HsfBuffer *new_normal;
    HsfBuffer *temp_normal;
    void *data;
    
    
    if(head.normal.count) {
        s32 cenv_count = head.cenv.count;
#ifdef BYTESWAPPING
        HsfBuffer32b *file_normal_real = (HsfBuffer32b *)((uintptr_t)fileptr + head.normal.ofs);
        temp_normal = file_normal = NormalTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfBuffer) * head.normal.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.normal.count; i++) {
            byteswap_hsfbuffer(&file_normal_real[i], &file_normal[i]);
        }
#else
        temp_normal = file_normal = (HsfBuffer *)((u32)fileptr+head.normal.ofs);
        data = (void *)&file_normal[head.normal.count];
#endif
        new_normal = temp_normal;
        Model.normal = new_normal;
        Model.normalCnt = head.normal.count;
#ifdef BYTESWAPPING
        NormalDataTop = data = (void *)&file_normal_real[head.normal.count];
#else
        file_normal = (HsfBuffer *)((u32)fileptr+head.normal.ofs);
        NormalDataTop = data = (void *)&file_normal[head.normal.count];
#endif
        for(i=0; i<head.normal.count; i++, new_normal++, file_normal++) {
            temp_data = file_normal->data;
            new_normal->count = file_normal->count;
            new_normal->name = SetName((u32 *)&file_normal->name);
            new_normal->data = (void *)((uintptr_t)data+(uintptr_t)temp_data);
#ifdef BYTESWAPPING
            if (cenv_count != 0) {
                for (j = 0; j < new_normal->count; j++) {
                    HsfVector3f *normalData = &((HsfVector3f *)new_normal->data)[j];
                    byteswap_hsfvec3f(normalData);
                }
            }
#endif
        }
    }
}

static void STLoad(void)
{
    s32 i, j;
    HsfBuffer *file_st;
    HsfBuffer *temp_st;
    HsfBuffer *new_st;
    void *data;
    HsfVector2f *data_elem;
    void *temp_data;
    
    if(head.st.count) {
#ifdef BYTESWAPPING
        HsfBuffer32b *file_st_real = (HsfBuffer32b *)((uintptr_t)fileptr + head.st.ofs);
        temp_st = file_st = StTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfBuffer) * head.st.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.st.count; i++) {
            byteswap_hsfbuffer(&file_st_real[i], &file_st[i]);
        }
#else
        temp_st = file_st = (HsfBuffer *)((u32)fileptr+head.st.ofs);
        data = (void *)&file_st[head.st.count];
        for(i=0; i<head.st.count; i++, file_st++) {
            for(j=0; j<(u32)file_st->count; j++) {
                data_elem = (HsfVector2f *)(((u32)data)+((u32)file_st->data)+(j*sizeof(HsfVector2f)));
            }
        }
#endif
        new_st = temp_st;
        Model.st = new_st;
        Model.stCnt = head.st.count;
#ifdef BYTESWAPPING
        data = (void *)&file_st_real[head.st.count];
#else
        file_st = (HsfBuffer *)((u32)fileptr+head.st.ofs);
        data = (void *)&file_st[head.st.count];
#endif
        for(i=0; i<head.st.count; i++, new_st++, file_st++) {
            temp_data = file_st->data;
            new_st->count = file_st->count;
            new_st->name = SetName((u32 *)&file_st->name);
            new_st->data = (void *)((uintptr_t)data + (uintptr_t)temp_data);
            for(j=0; j<new_st->count; j++) {
                data_elem = (HsfVector2f *)((uintptr_t)data + (uintptr_t)temp_data + (j*sizeof(HsfVector2f)));
#ifdef BYTESWAPPING
                byteswap_hsfvec2f(data_elem);
#endif
                ((HsfVector2f *)new_st->data)[j].x = data_elem->x;
                ((HsfVector2f *)new_st->data)[j].y = data_elem->y;
            }
        }
    }
}

static void FaceLoad(void)
{
    HsfBuffer *file_face;
    HsfBuffer *new_face;
    HsfBuffer *temp_face;
    HsfFace *temp_data;
    HsfFace *data;
    HsfFace *file_face_strip;
    HsfFace *new_face_strip;
    u8 *strip;
    s32 i;
    s32 j;
    
    if(head.face.count) {
#ifdef BYTESWAPPING
        HsfBuffer32b *file_face_real = (HsfBuffer32b *)((uintptr_t)fileptr + head.face.ofs);
        HsfFace32b *file_facedata_real = (HsfFace32b *)&file_face_real[head.face.count];
        temp_face = file_face = FaceTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfBuffer) * head.face.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.face.count; i++) {
            byteswap_hsfbuffer(&file_face_real[i], &file_face[i]);
        }
#else
        temp_face = file_face = (HsfBuffer *)((u32)fileptr+head.face.ofs);
        data = (HsfFace *)&file_face[head.face.count];
#endif
        new_face = temp_face;
        Model.face = new_face;
        Model.faceCnt = head.face.count;
#ifndef BYTESWAPPING
        file_face = (HsfBuffer *)((u32)fileptr+head.face.ofs);
        data = (HsfFace *)&file_face[head.face.count];
#endif
        for(i=0; i<head.face.count; i++, new_face++, file_face++) {
            temp_data = file_face->data;
            new_face->name = SetName((u32 *)&file_face->name);
            new_face->count = file_face->count;
#ifdef BYTESWAPPING
            {
                HsfFace32b *facedata_start = (HsfFace32b *)((uintptr_t)file_facedata_real + (uintptr_t)temp_data);
                data = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfFace) * new_face->count, MEMORY_DEFAULT_NUM);
                for (j = 0; j < new_face->count; j++) {
                    byteswap_hsfface(&facedata_start[j], &data[j]);
                }
                new_face->data = data;
                strip = (u8 *)(&facedata_start[new_face->count]);
            }
#else
            new_face->data = (void *)((uintptr_t)data+(uintptr_t)temp_data);
            strip = (u8 *)(&((HsfFace *)new_face->data)[new_face->count]);
#endif
        }
        new_face = temp_face;
        for(i=0; i<head.face.count; i++, new_face++) {
            file_face_strip = new_face_strip = new_face->data;
            for(j=0; j<new_face->count; j++, new_face_strip++, file_face_strip++) {
                if(AS_U16(file_face_strip->type) == 4) {
                    new_face_strip->strip.data = (s16 *)(strip+(uintptr_t)file_face_strip->strip.data*(sizeof(s16)*4));
#ifdef BYTESWAPPING
                    {
                        s32 k;
                        for (k = 0; k < new_face_strip->strip.count; k++) {
                            byteswap_s16(&new_face_strip->strip.data[k]);
                        }
                    }
#endif
                }
            }
        }
    }
}

static void DispObject(HsfObject *parent, HsfObject *object)
{
    u32 i;
    HsfObject *child_obj;
    HsfObject *temp_object;
    struct {
        HsfObject *parent;
        HsfBuffer *shape;
        HsfCluster *cluster;
    } temp;
    
    temp.parent = parent;
    object->type = object->type;
    switch(object->type) {
        case HSF_OBJ_MESH:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(uintptr_t)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(uintptr_t)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            new_object->data.parent = parent;
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            new_object->type = HSF_OBJ_MESH;
            new_object->data.vertex = SearchVertexPtr((s32)data->vertex);
            new_object->data.normal = SearchNormalPtr((s32)data->normal);
            new_object->data.st = SearchStPtr((s32)data->st);
            new_object->data.color = SearchColorPtr((s32)data->color);
            new_object->data.face = SearchFacePtr((s32)data->face);
            new_object->data.vertexShape = (HsfBuffer **)&NSymIndex[(uintptr_t)data->vertexShape];
            for(i=0; i<new_object->data.vertexShapeCnt; i++) {
                temp.shape = &vtxtop[(uintptr_t)new_object->data.vertexShape[i]];
                new_object->data.vertexShape[i] = temp.shape;
            }
            new_object->data.cluster = (HsfCluster **)&NSymIndex[(uintptr_t)data->cluster];
            for(i=0; i<new_object->data.clusterCnt; i++) {
                temp.cluster = &ClusterTop[(uintptr_t)new_object->data.cluster[i]];
                new_object->data.cluster[i] = temp.cluster;
            }
            new_object->data.cenv = SearchCenvPtr((s32)data->cenv);
            new_object->data.material = Model.material;
            if((s32)data->attribute >= 0) {
                new_object->data.attribute = Model.attribute;
            } else {
                new_object->data.attribute = NULL;
            }
            new_object->data.vtxtop = (void *)((uintptr_t)fileptr + (uintptr_t)data->vtxtop);
            new_object->data.normtop = (void *)((uintptr_t)fileptr + (uintptr_t)data->normtop);
#ifdef BYTESWAPPING
            for (i = 0; i < new_object->data.vertex->count; i++) {
                byteswap_hsfvec3f(&new_object->data.vtxtop[i]);
            }
            for (i = 0; i < new_object->data.normal->count; i++) {
                byteswap_hsfvec3f(&new_object->data.normtop[i]);
            }
#endif
            new_object->data.base.pos.x = data->base.pos.x;
            new_object->data.base.pos.y = data->base.pos.y;
            new_object->data.base.pos.z = data->base.pos.z;
            new_object->data.base.rot.x = data->base.rot.x;
            new_object->data.base.rot.y = data->base.rot.y;
            new_object->data.base.rot.z = data->base.rot.z;
            new_object->data.base.scale.x = data->base.scale.x;
            new_object->data.base.scale.y = data->base.scale.y;
            new_object->data.base.scale.z = data->base.scale.z;
            new_object->data.mesh.min.x = data->mesh.min.x;
            new_object->data.mesh.min.y = data->mesh.min.y;
            new_object->data.mesh.min.z = data->mesh.min.z;
            new_object->data.mesh.max.x = data->mesh.max.x;
            new_object->data.mesh.max.y = data->mesh.max.y;
            new_object->data.mesh.max.z = data->mesh.max.z;
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
            
        case HSF_OBJ_NULL1:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(uintptr_t)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(uintptr_t)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        case HSF_OBJ_REPLICA:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(uintptr_t)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(uintptr_t)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            new_object->data.replica = &objtop[(uintptr_t)new_object->data.replica];
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;

        case HSF_OBJ_ROOT:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        case HSF_OBJ_JOINT:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        case HSF_OBJ_NULL2:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        case HSF_OBJ_MAP:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        default:
            break;
    }
}

static inline void FixupObject(HsfObject *object)
{
    HsfObjectData *objdata_8;
    HsfObjectData *objdata_7;
    
    s32 obj_type = object->type;
    switch(obj_type) {
        case 8:
        {
            objdata_8 = &object->data;
            object->type = HSF_OBJ_LIGHT;
        }
        break;
        
        case 7:
        {
            objdata_7 = &object->data;
            object->type = HSF_OBJ_CAMERA;
        }
        break;
        
        default:
            break;
            
    }
}

static void ObjectLoad(void)
{
    s32 i;
    HsfObject *object;
    HsfObject *new_object;
    s32 obj_type;

    if(head.object.count) {
#ifdef BYTESWAPPING
        HsfObject32b *file_object_real = (HsfObject32b *)((uintptr_t)fileptr + head.object.ofs);
        objtop = object = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfObject) * head.object.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.object.count; i++) {
            byteswap_hsfobject(&file_object_real[i], &objtop[i]);
        }
#else
        objtop = object = (HsfObject *)((u32)fileptr+head.object.ofs);
#endif
        for(i=0; i<head.object.count; i++, object++) {
            new_object = object;
            new_object->name = SetName((u32 *)&object->name);
        }
        object = objtop;
        for(i=0; i<head.object.count; i++, object++) {
            if((s32)object->data.parent == -1) {
                break;
            }
        }
        DispObject(NULL, object);
        Model.objectCnt = head.object.count;
        object = objtop;
        for(i=0; i<head.object.count; i++, object++) {
            FixupObject(object);
        }
    }
}

static void CenvLoad(void)
{
    HsfCenvMulti *multi_file;
    HsfCenvMulti *multi_new;
    HsfCenvSingle *single_new;
    HsfCenvSingle *single_file;
    HsfCenvDual *dual_file;
    HsfCenvDual *dual_new;

    HsfCenv *cenv_new;
    HsfCenv *cenv_file;
    void *data_base;
    void *weight_base;
    
    s32 j;
    s32 i;
    
    if(head.cenv.count) {
#ifdef BYTESWAPPING
        HsfCenv32b *file_cenv_real = (HsfCenv32b *)((uintptr_t)fileptr + head.cenv.ofs);
        cenv_file = CenvTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfCenv) * head.cenv.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.cenv.count; i++) {
            byteswap_hsfcenv(&file_cenv_real[i], &cenv_file[i]);
        }
        data_base = &file_cenv_real[head.cenv.count];
#else
        cenv_file = (HsfCenv *)((u32)fileptr+head.cenv.ofs);
        data_base = &cenv_file[head.cenv.count];
#endif
        weight_base = data_base;
        cenv_new = cenv_file;
        Model.cenvCnt = head.cenv.count;
        Model.cenv = cenv_file;
        for(i=0; i<head.cenv.count; i++) {
            cenv_new[i].singleData = (HsfCenvSingle *)((uintptr_t)cenv_file[i].singleData + (uintptr_t)data_base);
#ifndef BYTESWAPPING
            cenv_new[i].dualData = (HsfCenvDual *)((uintptr_t)cenv_file[i].dualData + (uintptr_t)data_base);
            cenv_new[i].multiData = (HsfCenvMulti *)((uintptr_t)cenv_file[i].multiData + (uintptr_t)data_base);
#endif
            cenv_new[i].singleCount = cenv_file[i].singleCount;
            cenv_new[i].dualCount = cenv_file[i].dualCount;
            cenv_new[i].multiCount = cenv_file[i].multiCount;
            cenv_new[i].copyCount = cenv_file[i].copyCount;
            cenv_new[i].vtxCount = cenv_file[i].vtxCount;
#if BYTESWAPPING
            weight_base = (void *)((uintptr_t)weight_base + (cenv_new[i].singleCount * sizeof(HsfCenvSingle)));
            weight_base = (void *)((uintptr_t)weight_base + (cenv_new[i].dualCount * sizeof(HsfCenvDual32b)));
            weight_base = (void *)((uintptr_t)weight_base + (cenv_new[i].multiCount * sizeof(HsfCenvMulti32b)));
#else
            weight_base = (void *)((uintptr_t)weight_base + (cenv_new[i].singleCount * sizeof(HsfCenvSingle)));
            weight_base = (void *)((uintptr_t)weight_base + (cenv_new[i].dualCount * sizeof(HsfCenvDual)));
            weight_base = (void *)((uintptr_t)weight_base + (cenv_new[i].multiCount * sizeof(HsfCenvMulti)));
#endif
        }
        for(i=0; i<head.cenv.count; i++) {
#ifdef BYTESWAPPING
            HsfCenvDual32b *dual_data_real = (HsfCenvDual32b *)((uintptr_t)cenv_file[i].dualData + (uintptr_t)data_base);
            HsfCenvMulti32b *multi_data_real = (HsfCenvMulti32b *)((uintptr_t)cenv_file[i].multiData + (uintptr_t)data_base);
            cenv_new[i].dualData = HuMemDirectMallocNum(HEAP_DATA, cenv_file[i].dualCount * sizeof(HsfCenvDual), MEMORY_DEFAULT_NUM);
            cenv_new[i].multiData = HuMemDirectMallocNum(HEAP_DATA, cenv_file[i].multiCount * sizeof(HsfCenvMulti), MEMORY_DEFAULT_NUM);
#endif
            single_new = single_file = cenv_new[i].singleData;
            for(j=0; j<cenv_new[i].singleCount; j++) {
#ifdef BYTESWAPPING
                byteswap_hsfcenv_single(&single_new[j]);
#endif
                single_new[j].target = single_file[j].target;
                single_new[j].posCnt = single_file[j].posCnt;
                single_new[j].pos = single_file[j].pos;
                single_new[j].normalCnt = single_file[j].normalCnt;
                single_new[j].normal = single_file[j].normal;
            }
            dual_new = dual_file = cenv_new[i].dualData;
            for(j=0; j<cenv_new[i].dualCount; j++) {
#ifdef BYTESWAPPING
                s32 k;
                byteswap_hsfcenv_dual(&dual_data_real[j], &dual_new[j]);
#endif
                dual_new[j].target1 = dual_file[j].target1;
                dual_new[j].target2 = dual_file[j].target2;
                dual_new[j].weightCnt = dual_file[j].weightCnt;
                dual_new[j].weight = (HsfCenvDualWeight *)((uintptr_t)weight_base + (uintptr_t)dual_file[j].weight);
#ifdef BYTESWAPPING
                for (k = 0; k < dual_new[j].weightCnt; k++) {
                    byteswap_hsfcenv_dual_weight(&dual_new[j].weight[k]);
                }
#endif
            }
            multi_new = multi_file = cenv_new[i].multiData;
            for(j=0; j<cenv_new[i].multiCount; j++) {
#ifdef BYTESWAPPING
                s32 k;
                byteswap_hsfcenv_multi(&multi_data_real[j], &multi_new[j]);
#endif
                multi_new[j].weightCnt = multi_file[j].weightCnt;
                multi_new[j].pos = multi_file[j].pos;
                multi_new[j].posCnt = multi_file[j].posCnt;
                multi_new[j].normal = multi_file[j].normal;
                multi_new[j].normalCnt = multi_file[j].normalCnt;
                multi_new[j].weight = (HsfCenvMultiWeight *)((uintptr_t)weight_base + (uintptr_t)multi_file[j].weight);
#ifdef BYTESWAPPING
                for (k = 0; k < multi_new[j].weightCnt; k++) {
                    byteswap_hsfcenv_multi_weight(&multi_new[j].weight[k]);
                }
#endif
            }
            dual_new = dual_file = cenv_new[i].dualData;
            for(j=0; j<cenv_new[i].dualCount; j++) {
                HsfCenvDualWeight *discard = dual_new[j].weight;
            }
            multi_new = multi_file = cenv_new[i].multiData;
            for(j=0; j<cenv_new[i].multiCount; j++) {
                HsfCenvMultiWeight *weight = multi_new[j].weight;
                s32 k;
                for(k=0; k<multi_new[j].weightCnt; k++, weight++);
            }
        }
    }
}

static void SkeletonLoad(void)
{
    HsfSkeleton *skeleton_file;
    HsfSkeleton *skeleton_new;
    s32 i;
    
    if(head.skeleton.count) {
#ifdef BYTESWAPPING
        HsfSkeleton32b *file_skeleton_real = (HsfSkeleton32b *)((uintptr_t)fileptr + head.skeleton.ofs);
        skeleton_new = skeleton_file = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfSkeleton) * head.skeleton.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.skeleton.count; i++) {
            byteswap_hsfskeleton(&file_skeleton_real[i], &skeleton_file[i]);
        }
#else
        skeleton_new = skeleton_file = (HsfSkeleton *)((u32)fileptr+head.skeleton.ofs);
#endif
        Model.skeletonCnt = head.skeleton.count;
        Model.skeleton = skeleton_file;
        for(i=0; i<head.skeleton.count; i++) {
            skeleton_new[i].name = SetName((u32 *)&skeleton_file[i].name);
            skeleton_new[i].transform.pos.x = skeleton_file[i].transform.pos.x;
            skeleton_new[i].transform.pos.y = skeleton_file[i].transform.pos.y;
            skeleton_new[i].transform.pos.z = skeleton_file[i].transform.pos.z;
            skeleton_new[i].transform.rot.x = skeleton_file[i].transform.rot.x;
            skeleton_new[i].transform.rot.y = skeleton_file[i].transform.rot.y;
            skeleton_new[i].transform.rot.z = skeleton_file[i].transform.rot.z;
            skeleton_new[i].transform.scale.x = skeleton_file[i].transform.scale.x;
            skeleton_new[i].transform.scale.y = skeleton_file[i].transform.scale.y;
            skeleton_new[i].transform.scale.z = skeleton_file[i].transform.scale.z;
        }
    }
}

static void PartLoad(void)
{
    HsfPart *part_file;
    HsfPart *part_new;
    
    u16 *data;
    s32 i, j;
    
    if(head.part.count) {
#ifdef BYTESWAPPING
        HsfPart32b *file_part_real = (HsfPart32b *)((uintptr_t)fileptr + head.part.ofs);
        part_new = part_file = PartTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfPart) * head.part.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.part.count; i++) {
            byteswap_hsfpart(&file_part_real[i], &part_file[i]);
        }
#else
        part_new = part_file = (HsfPart *)((u32)fileptr+head.part.ofs);
#endif
        Model.partCnt = head.part.count;
        Model.part = part_file;
#ifdef BYTESWAPPING
        data = (u16 *)&file_part_real[head.part.count];
#else
        data = (u16 *)&part_file[head.part.count];
#endif
        for(i=0; i<head.part.count; i++, part_new++) {
            part_new->name = SetName((u32 *)&part_file[i].name);
            part_new->count = part_file[i].count;
            part_new->vertex = &data[(uintptr_t)part_file[i].vertex];
            for(j=0; j<part_new->count; j++) {
                part_new->vertex[j] = part_new->vertex[j];
#ifdef BYTESWAPPING
                byteswap_u16(&part_new->vertex[j]);
#endif
            }
        }
    }
}

static void ClusterLoad(void)
{
    HsfCluster *cluster_file;
    HsfCluster *cluster_new;
    
    s32 i, j;
    
    if(head.cluster.count) {
#ifdef BYTESWAPPING
        cluster_new = cluster_file = ClusterTop;
#else
        cluster_new = cluster_file = (HsfCluster *)((u32)fileptr+head.cluster.ofs);
#endif
        Model.clusterCnt = head.cluster.count;
        Model.cluster = cluster_file;
        for(i=0; i<head.cluster.count; i++) {
            HsfBuffer *vertex;
            u32 vertexSym;
            cluster_new[i].name[0] = SetName((u32 *)&cluster_file[i].name[0]);
            cluster_new[i].name[1] = SetName((u32 *)&cluster_file[i].name[1]);
            cluster_new[i].targetName = SetName((u32 *)&cluster_file[i].targetName);
            cluster_new[i].part = SearchPartPtr((s32)cluster_file[i].part);
            cluster_new[i].unk95 = cluster_file[i].unk95;
            cluster_new[i].type = cluster_file[i].type;
            cluster_new[i].vertexCnt = cluster_file[i].vertexCnt;
            vertexSym = (uintptr_t)cluster_file[i].vertex;
            cluster_new[i].vertex = (HsfBuffer **)&NSymIndex[vertexSym];
            for(j=0; j<cluster_new[i].vertexCnt; j++) {
                vertex = SearchVertexPtr((s32)cluster_new[i].vertex[j]);
                cluster_new[i].vertex[j] = vertex;
            }
        }
    }
}

static void ShapeLoad(void)
{
    s32 i, j;
    HsfShape *shape_new;
    HsfShape *shape_file;

    if(head.shape.count) {
#ifdef BYTESWAPPING
        HsfShape32b *file_shape_real = (HsfShape32b *)((uintptr_t)fileptr + head.shape.ofs);
        shape_new = shape_file = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfShape) * head.shape.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.shape.count; i++) {
            byteswap_hsfshape(&file_shape_real[i], &shape_file[i]);
        }
#else
        shape_new = shape_file = (HsfShape *)((u32)fileptr+head.shape.ofs);
#endif
        Model.shapeCnt = head.shape.count;
        Model.shape = shape_file;
        for(i=0; i<Model.shapeCnt; i++) {
            u32 vertexSym;
            HsfBuffer *vertex;

            shape_new[i].name = SetName((u32 *)&shape_file[i].name);
            shape_new[i].count16[0] = shape_file[i].count16[0];
            shape_new[i].count16[1] = shape_file[i].count16[1];
            vertexSym = (uintptr_t)shape_file[i].vertex;
            shape_new[i].vertex = (HsfBuffer **)&NSymIndex[vertexSym];
            for(j=0; j<shape_new[i].count16[1]; j++) {
                vertex = &vtxtop[(u32)shape_new[i].vertex[j]];
                shape_new[i].vertex[j] = vertex;
            }
        }
    }
}

static void MapAttrLoad(void)
{
    s32 i;
    HsfMapAttr *mapattr_base;
    HsfMapAttr *mapattr_file;
    HsfMapAttr *mapattr_new;
    u16 *data;
    
    if(head.mapAttr.count) {
#ifdef BYTESWAPPING
        HsfMapAttr32b *file_mapattr_real = (HsfMapAttr32b *)((uintptr_t)fileptr + head.mapAttr.ofs);
        mapattr_file = mapattr_base = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfMapAttr) * head.mapAttr.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.mapAttr.count; i++) {
            byteswap_hsfmapattr(&file_mapattr_real[i], &mapattr_base[i]);
        }
#else
        mapattr_file = mapattr_base = (HsfMapAttr *)((u32)fileptr+head.mapAttr.ofs);
#endif
        mapattr_new = mapattr_base;
        Model.mapAttrCnt = head.mapAttr.count;
        Model.mapAttr = mapattr_base;
#ifdef BYTESWAPPING
        data = (u16 *)&file_mapattr_real[head.part.count];
#else
        data = (u16 *)&mapattr_base[head.mapAttr.count];
#endif
        for(i=0; i<head.mapAttr.count; i++, mapattr_file++, mapattr_new++) {
            mapattr_new->data = &data[(u32)mapattr_file->data];
        }
    }
}

static void BitmapLoad(void)
{
    HsfBitmap *bitmap_file;
    HsfBitmap *bitmap_temp;
    HsfBitmap *bitmap_new;
    HsfPalette *palette;
    void *data;
    s32 i;
    
    if(head.bitmap.count) {
#ifdef BYTESWAPPING
        HsfBitmap32b *file_bitmap_real = (HsfBitmap32b *)((uintptr_t)fileptr + head.bitmap.ofs);
        bitmap_temp = bitmap_file = BitmapTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfBitmap) * head.bitmap.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.bitmap.count; i++) {
            byteswap_hsfbitmap(&file_bitmap_real[i], &bitmap_file[i]);
        }
#else
        bitmap_temp = bitmap_file = (HsfBitmap *)((u32)fileptr+head.bitmap.ofs);
        data = &bitmap_file[head.bitmap.count];
        for(i=0; i<head.bitmap.count; i++, bitmap_file++);
#endif
        bitmap_new = bitmap_temp;
        Model.bitmap = bitmap_file;
        Model.bitmapCnt = head.bitmap.count;
#ifdef BYTESWAPPING
        data = (void *)&file_bitmap_real[head.st.count];
#else
        bitmap_file = (HsfBitmap *)((u32)fileptr+head.bitmap.ofs);
        data = &bitmap_file[head.bitmap.count];
#endif
        for(i=0; i<head.bitmap.count; i++, bitmap_file++, bitmap_new++) {
            bitmap_new->name = SetName((u32 *)&bitmap_file->name);
            bitmap_new->dataFmt = bitmap_file->dataFmt;
            bitmap_new->pixSize = bitmap_file->pixSize;
            bitmap_new->sizeX = bitmap_file->sizeX;
            bitmap_new->sizeY = bitmap_file->sizeY;
            bitmap_new->palSize = bitmap_file->palSize;
            palette = SearchPalettePtr((uintptr_t)bitmap_file->palData);
            if(palette) {
                bitmap_new->palData = palette->data;
            }
            bitmap_new->data = (void *)((uintptr_t)data+(uintptr_t)bitmap_file->data);
        }
    }
}

static void PaletteLoad(void)
{
    s32 i;
    s32 j;
    HsfPalette *palette_file;
    HsfPalette *palette_temp;
    HsfPalette *palette_new;
    
    void *data_base;
    u16 *temp_data;
    u16 *data;
    
    if(head.palette.count) {
#ifdef BYTESWAPPING
        HsfPalette32b *file_palette_real = (HsfPalette32b *)((uintptr_t)fileptr + head.palette.ofs);
        palette_temp = palette_file = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfPalette) * head.palette.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.palette.count; i++) {
            byteswap_hsfpalette(&file_palette_real[i], &palette_file[i]);
        }
#else
        palette_temp = palette_file = (HsfPalette *)((u32)fileptr+head.palette.ofs);
        data_base = (u16 *)&palette_file[head.palette.count];
        for(i=0; i<head.palette.count; i++, palette_file++) {
            temp_data = (u16 *)((uintptr_t)data_base+(uintptr_t)palette_file->data);
        }
#endif
        Model.palette = palette_temp;
        Model.paletteCnt = head.palette.count;
        palette_new = palette_temp;
#ifdef BYTESWAPPING
        data_base = (u16 *)&file_palette_real[head.palette.count];
#else
        palette_file = (HsfPalette *)((u32)fileptr+head.palette.ofs);
        data_base = (u16 *)&palette_file[head.palette.count];
#endif
        for(i=0; i<head.palette.count; i++, palette_file++, palette_new++) {
            temp_data = (u16 *)((uintptr_t)data_base+(uintptr_t)palette_file->data);
            data = temp_data;
            palette_new->name = SetName((u32 *)&palette_file->name);
            palette_new->data = data;
            palette_new->palSize = palette_file->palSize;
            for(j=0; j<palette_file->palSize; j++) {
                data[j] = data[j];
#ifdef BYTESWAPPING
                byteswap_u16(&data[j]);
#endif
            }
        }
    }
}

char *MakeObjectName(char *name)
{
    static char buf[768];
    s32 index, num_minus;
    char *temp_name;
    num_minus = 0;
    index = 0;
    temp_name = name;
    while(*temp_name) {
        if(*temp_name == '-') {
            name = temp_name+1;
            break;
        }
        temp_name++;
    }
    while(*name) {
        if(num_minus != 0) {
            break;
        }
        if(*name == '_' && !isalpha(name[1])) {
            num_minus++;
            break;
        }
        buf[index] = *name;
        name++;
        index++;
    }
    buf[index] = '\0';
    return buf;
}

s32 CmpObjectName(char *name1, char *name2)
{
    s32 temp = 0;
    return strcmp(name1, name2);
}

static inline char *MotionGetName(HsfTrack *track)
{
    char *ret;
    if(DicStringTable) {
        ret = &DicStringTable[track->target];
    } else {
        ret = GetMotionString(&track->target);
    }
    return ret;
}

static inline s32 FindObjectName(char *name)
{
    s32 i;
    HsfObject *object;
    
    object = objtop;
    for(i=0; i<head.object.count; i++, object++) {
        if(!CmpObjectName(object->name, name)) {
            return i;
        }
    }
    return -1;
}

static inline s32 FindClusterName(char *name)
{
    s32 i;
    HsfCluster *cluster;
    
    cluster = ClusterTop;
    for(i=0; i<head.cluster.count; i++, cluster++) {
        if(!strcmp(cluster->name[0], name)) {
            return i;
        }
    }
    return -1;
}

static inline s32 FindMotionClusterName(char *name)
{
    s32 i;
    HsfCluster *cluster;
    
    cluster = MotionModel->cluster;
    for(i=0; i<MotionModel->clusterCnt; i++, cluster++) {
        if(!strcmp(cluster->name[0], name)) {
            return i;
        }
    }
    return -1;
}

static inline s32 FindAttributeName(char *name)
{
    s32 i;
    HsfAttribute *attribute;
    
    attribute = AttributeTop;
    for(i=0; i<head.attribute.count; i++, attribute++) {
        if(!attribute->name) {
            continue;
        }
        if(!strcmp(attribute->name, name)) {
            return i;
        }
    }
    return -1;
}

static inline s32 FindMotionAttributeName(char *name)
{
    s32 i;
    HsfAttribute *attribute;
    
    attribute = MotionModel->attribute;
    for(i=0; i<MotionModel->attributeCnt; i++, attribute++) {
        if(!attribute->name) {
            continue;
        }
        if(!strcmp(attribute->name, name)) {
            return i;
        }
    }
    return -1;
}

#ifdef BYTESWAPPING
static void ByteSwapCurveStepOrLinearData(HsfTrack *track)
{
    int i;
    float *data = track->data;
    for (i = 0; i < track->numKeyframes; i++) {
        byteswap_float(data++);
        byteswap_float(data++);
    }
}

static void ByteSwapCurveBitmapData(HsfTrack *track)
{
    int i;
    float *data = track->data;
    for (i = 0; i < track->numKeyframes; i++) {
        byteswap_float(data++);
        byteswap_s32((s32*) data++);
    }
}

static void ByteSwapCurveBezierData(HsfTrack *track)
{
    int i;
    float *data = track->data;
    for (i = 0; i < track->numKeyframes; i++) {
        byteswap_float(data++);
        byteswap_float(data++);
        byteswap_float(data++);
        byteswap_float(data++);
    }
}
#endif

static inline void MotionLoadTransform(HsfTrack *track, void *data)
{
    float *step_data;
    float *linear_data;
    float *bezier_data;
    HsfTrack *out_track;
    char *name;
    s32 numKeyframes;
    out_track = track;
    name = MotionGetName(track);
    if(objtop) {
        out_track->target = FindObjectName(name);
    }
    numKeyframes = AS_S16(track->numKeyframes);
    switch(track->curveType) {
        case HSF_CURVE_STEP:
        {
            step_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = step_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = linear_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = bezier_data;
#ifdef BYTESWAPPING
            ByteSwapCurveBezierData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_CONST:
            break;
    }
}

static inline void MotionLoadCluster(HsfTrack *track, void *data)
{
    s32 numKeyframes;
    float *step_data;
    float *linear_data;
    float *bezier_data;
    HsfTrack *out_track;
    char *name;
    
    out_track = track;
    name = SetMotionName(&track->target);
    if(!MotionOnly) {
        AS_S16(out_track->target) = FindClusterName(name);
    } else {
        AS_S16(out_track->target) = FindMotionClusterName(name);
    }
    numKeyframes = AS_S16(track->numKeyframes);
    (void)out_track;
    switch(track->curveType) {
        case HSF_CURVE_STEP:
        {
            step_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = step_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = linear_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = bezier_data;
#ifdef BYTESWAPPING
            ByteSwapCurveBezierData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_CONST:
            break;
    }
}

static inline void MotionLoadClusterWeight(HsfTrack *track, void *data)
{
    s32 numKeyframes;
    float *step_data;
    float *linear_data;
    float *bezier_data;
    HsfTrack *out_track;
    char *name;
    
    out_track = track;
    name = SetMotionName(&track->target);
    if(!MotionOnly) {
        AS_S16(out_track->target) = FindClusterName(name);
    } else {
        AS_S16(out_track->target) = FindMotionClusterName(name);
    }
    numKeyframes = AS_S16(track->numKeyframes);
    (void)out_track;
    switch(track->curveType) {
        case HSF_CURVE_STEP:
        {
            step_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = step_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = linear_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = bezier_data;
#ifdef BYTESWAPPING
            ByteSwapCurveBezierData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_CONST:
            break;
    }
}

static inline void MotionLoadMaterial(HsfTrack *track, void *data)
{
    float *step_data;
    float *linear_data;
    float *bezier_data;
    s32 numKeyframes;
    HsfTrack *out_track;
    out_track = track;
    numKeyframes = AS_S16(track->numKeyframes);
    switch(track->curveType) {
        case HSF_CURVE_STEP:
        {
            step_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = step_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = linear_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = bezier_data;
#ifdef BYTESWAPPING
            ByteSwapCurveBezierData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_CONST:
            break;
    }
}

static inline void MotionLoadAttribute(HsfTrack *track, void *data)
{
    HsfBitmapKey *file_frame;
    HsfBitmapKey *new_frame;
    s32 i;
    float *step_data;
    float *linear_data;
    float *bezier_data;
    HsfTrack *out_track;
    char *name;
    out_track = track;
    if(AS_S16(out_track->target) != -1) {
        name = SetMotionName(&track->target);
        if(!MotionOnly) {
            AS_S16(out_track->param) = FindAttributeName(name);
        } else {
            AS_S16(out_track->param) = FindMotionAttributeName(name);
        }
    }
    
    switch(track->curveType) {
        case HSF_CURVE_STEP:
        {
            step_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = step_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = linear_data;
#ifdef BYTESWAPPING
            ByteSwapCurveStepOrLinearData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = bezier_data;
#ifdef BYTESWAPPING
            ByteSwapCurveBezierData(out_track);
#endif
        }
        break;
        
        case HSF_CURVE_BITMAP:
        {
#ifdef BYTESWAPPING
            HsfBitmapKey32b *file_frame_real = (HsfBitmapKey32b *)((uintptr_t)data + (uintptr_t)track->data);
            new_frame = file_frame = track->dataTop = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfBitmapKey) * track->numKeyframes, MEMORY_DEFAULT_NUM);
#else
            new_frame = file_frame = (HsfBitmapKey *)((uintptr_t)data + (uintptr_t)track->data);
            out_track->data = file_frame;
#endif
            for(i=0; i<out_track->numKeyframes; i++, file_frame++, new_frame++) {
#ifdef BYTESWAPPING
                byteswap_hsfbitmapkey(&file_frame_real[i], new_frame);
#endif
                new_frame->data = SearchBitmapPtr((s32)file_frame->data);
            }
        }
        break;
        case HSF_CURVE_CONST:
            break;
    }
}

static void MotionLoad(void)
{
    HsfMotion *file_motion;
    HsfMotion *temp_motion;
    HsfMotion *new_motion;
    HsfTrack *track_base;
    void *track_data;
    s32 i;
    
    MotionOnly = FALSE;
    MotionModel = NULL;
    if(head.motion.count) {
#ifdef BYTESWAPPING
        HsfMotion32b *file_motion_real = (HsfMotion32b *)((uintptr_t)fileptr + head.motion.ofs);
        temp_motion = file_motion = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfMotion) * head.motion.count, MEMORY_DEFAULT_NUM);
        for (i = 0; i < head.motion.count; i++) {
            byteswap_hsfmotion(&file_motion_real[i], &file_motion[i]);
        }
#else
        temp_motion = file_motion = (HsfMotion *)((uintptr_t)fileptr+head.motion.ofs);
#endif
        new_motion = temp_motion;
        Model.motion = new_motion;
        Model.motionCnt = file_motion->numTracks;
#ifdef BYTESWAPPING
        {
            HsfTrack32b *track_base_real = (HsfTrack32b *)&file_motion_real[head.motion.count];
            track_base = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfTrack) * file_motion->numTracks, MEMORY_DEFAULT_NUM);
            track_data = &track_base_real[file_motion->numTracks];
            for (i = 0; i < file_motion->numTracks; i++) {
                byteswap_hsftrack(&track_base_real[i], &track_base[i]);
            }
        }
#else
        track_base = (HsfTrack *)&file_motion[head.motion.count];
        track_data = &track_base[file_motion->numTracks];
#endif
        new_motion->track = track_base;
        for(i=0; i<(s32)file_motion->numTracks; i++) {
            switch(track_base[i].type) {
                case HSF_TRACK_TRANSFORM:
                case HSF_TRACK_MORPH:
                    MotionLoadTransform(&track_base[i], track_data);
                    break;
                    
                case HSF_TRACK_CLUSTER:
                    MotionLoadCluster(&track_base[i], track_data);
                    break;
                    
                case HSF_TRACK_CLUSTER_WEIGHT:
                    MotionLoadClusterWeight(&track_base[i], track_data);
                    break;
                    
                case HSF_TRACK_MATERIAL:
                    MotionLoadMaterial(&track_base[i], track_data);
                    break;
                    
                case HSF_TRACK_ATTRIBUTE:
                    MotionLoadAttribute(&track_base[i], track_data);
                    break;
                    
                default:
                    break;
            }
        }
    }
    //HACK: Bump register of i to r31
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
    (void)i;
}

static void MatrixLoad(void)
{
    HsfMatrix *matrix_file;

    if(head.matrix.count) {
#ifdef BYTESWAPPING
        if (head.matrix.count > 1) {
            OSReport("MORE THAN ONE MATRIX, FIX PARSING!\n");
        }
        matrix_file = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfMatrix) * head.matrix.count, MEMORY_DEFAULT_NUM);
        byteswap_hsfmatrix((HsfMatrix32b *)((uintptr_t)fileptr + head.matrix.ofs), matrix_file);
#else
        matrix_file = (HsfMatrix *)((uintptr_t)fileptr+head.matrix.ofs);
        matrix_file->data = (Mtx *)((u32)fileptr+head.matrix.ofs+sizeof(HsfMatrix));
#endif
        Model.matrix = matrix_file;
        Model.matrixCnt = head.matrix.count;
    }
}

static s32 SearchObjectSetName(HsfData *data, char *name)
{
    HsfObject *object = data->object;
    s32 i;
    for(i=0; i<data->objectCnt; i++, object++) {
        if(!CmpObjectName(object->name, name)) {
            return i;
        }
    }
    OSReport("Search Object Error %s\n", name);
    return -1;
}

static HsfBuffer *SearchVertexPtr(s32 id)
{
    HsfBuffer *vertex; 
    if(id == -1) {
        return NULL;
    }
#ifdef BYTESWAPPING
    vertex = vtxtop;
#else
    vertex = (HsfBuffer *)((uintptr_t)fileptr+head.vertex.ofs);
#endif
    vertex += id;
    return vertex;
}

static HsfBuffer *SearchNormalPtr(s32 id)
{
    HsfBuffer *normal; 
    if(id == -1) {
        return NULL;
    }
#ifdef BYTESWAPPING
    normal = NormalTop;
#else
    normal = (HsfBuffer *)((uintptr_t)fileptr+head.normal.ofs);
#endif
    normal += id;
    return normal;
}

static HsfBuffer *SearchStPtr(s32 id)
{
    HsfBuffer *st; 
    if(id == -1) {
        return NULL;
    }
#ifdef BYTESWAPPING
    st = StTop;
#else
    st = (HsfBuffer *)((uintptr_t)fileptr+head.st.ofs);
#endif
    st += id;
    return st;
}

static HsfBuffer *SearchColorPtr(s32 id)
{
    HsfBuffer *color; 
    if(id == -1) {
        return NULL;
    }
#ifdef BYTESWAPPING
    color = ColorTop;
#else
    color = (HsfBuffer *)((uintptr_t)fileptr+head.color.ofs);
#endif
    color += id;
    return color;
}

static HsfBuffer *SearchFacePtr(s32 id)
{
    HsfBuffer *face; 
    if(id == -1) {
        return NULL;
    }
#ifdef BYTESWAPPING
    face = FaceTop;
#else
    face = (HsfBuffer *)((uintptr_t)fileptr+head.face.ofs);
#endif
    face += id;
    return face;
}

static HsfCenv *SearchCenvPtr(s32 id)
{
    HsfCenv *cenv; 
    if(id == -1) {
        return NULL;
    }
#ifdef BYTESWAPPING
    cenv = CenvTop;
#else
    cenv = (HsfCenv *)((uintptr_t)fileptr + head.cenv.ofs);
#endif
    cenv += id;
    return cenv;
}

static HsfPart *SearchPartPtr(s32 id)
{
    HsfPart *part; 
    if(id == -1) {
        return NULL;
    }
#ifdef BYTESWAPPING
    part = PartTop;
#else
    part = (HsfPart *)((uintptr_t)fileptr+head.part.ofs);
#endif
    part += id;
    return part;
}

static HsfPalette *SearchPalettePtr(s32 id)
{
    HsfPalette *palette; 
    if(id == -1) {
        return NULL;
    }
    palette = Model.palette;
    palette += id;
    return palette;
}

static HsfBitmap *SearchBitmapPtr(s32 id)
{
    HsfBitmap *bitmap; 
    if(id == -1) {
        return NULL;
    }
#ifdef BYTESWAPPING
    bitmap = BitmapTop;
#else
    bitmap = (HsfBitmap *)((uintptr_t)fileptr+head.bitmap.ofs);
#endif
    bitmap += id;
    return bitmap;
}

static char *GetString(u32 *str_ofs)
{
    char *ret = &StringTable[*str_ofs];
    return ret;
}

static char *GetMotionString(u16 *str_ofs)
{
    char *ret = &StringTable[*str_ofs];
    return ret;
}

#ifdef TARGET_PC
void KillHSF(HsfData *data)
{
    // TODO PC
    s32 i, j;
    // if (data->attributeCnt)
    //     HuMemDirectFree(data->attribute);
    // if (data->bitmapCnt)
    //     HuMemDirectFree(data->bitmap);
    // if (data->skeletonCnt)
    //     HuMemDirectFree(data->skeleton);
    // if (data->faceCnt) {
    //     for (i = 0; i < data->faceCnt; i++) {
    //         HuMemDirectFree(data->face[i].data);
    //     }
    //     HuMemDirectFree(data->face);
    // }
    // if (data->materialCnt)
    //     HuMemDirectFree(data->material);
    // if (data->motionCnt) {
    //     HsfMotion *motion = data->motion;
    //     for (j = 0; j < motion->numTracks; j++) {
    //         HsfTrack *track = motion->track;
    //         if (track->type == HSF_TRACK_ATTRIBUTE && track->curveType == HSF_CURVE_BITMAP) {
    //             // in this case we needed to allocate space for HsfBitmapKey structs
    //             HuMemDirectFree(track->dataTop);
    //         }
    //     }
    //     HuMemDirectFree(motion->track);
    //     HuMemDirectFree(data->motion);
    // }
    // if (data->normalCnt)
    //     HuMemDirectFree(data->normal);
    // if (data->objectCnt)
    //     HuMemDirectFree(data->object);
    // if (data->matrixCnt)
    //     HuMemDirectFree(data->matrix);
    // if (data->paletteCnt)
    //     HuMemDirectFree(data->palette);
    // if (data->stCnt)
    //     HuMemDirectFree(data->st);
    // if (data->vertexCnt)
    //     HuMemDirectFree(data->vertex);
    // if (data->cenvCnt) {
    //     for (i = 0; i < data->cenvCnt; i++) {
    //         HsfCenv *cenv = &data->cenv[i];
    //         HuMemDirectFree(cenv->dualData);
    //         HuMemDirectFree(cenv->multiData);
    //     }
    //     HuMemDirectFree(data->cenv);
    // }
    // if (data->clusterCnt)
    //     HuMemDirectFree(data->cluster);
    // if (data->partCnt)
    //     HuMemDirectFree(data->part);
    // if (data->shapeCnt)
    //     HuMemDirectFree(data->shape);
    // if (data->mapAttrCnt)
    //     HuMemDirectFree(data->mapAttr);
    // HuMemDirectFree(data->symbol);
}
#endif
