#include "game/hsfload.h"
#include "string.h"
#include "ctype.h"

#ifdef TARGET_PC
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
    ObjectLoad();
    CenvLoad();
    SkeletonLoad();
    PartLoad();
    ClusterLoad();
    ShapeLoad();
    MapAttrLoad();
    MotionLoad();
    MatrixLoad();
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
    fileptr = data;
    memcpy(&head, fileptr, sizeof(HsfHeader));
    memset(&Model, 0, sizeof(HsfData));
#ifdef TARGET_PC
    byteswap_hsfheader(&head);
#endif
    NSymIndex = (void **)((uintptr_t)fileptr+head.symbol.ofs);
    StringTable = (char *)((uintptr_t)fileptr+head.string.ofs);
    ClusterTop = (HsfCluster *)((uintptr_t)fileptr+head.cluster.ofs);
    AttributeTop = (HsfAttribute *)((uintptr_t)fileptr + head.attribute.ofs);
    MaterialTop = (HsfMaterial *)((uintptr_t)fileptr + head.material.ofs);
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
        HsfMaterial *file_mat = (HsfMaterial *)((u32)fileptr+head.material.ofs);
        HsfMaterial *curr_mat;
        HsfMaterial *new_mat;
        for(i=0; i<head.material.count; i++) {
            curr_mat = &file_mat[i];
        }
        new_mat = file_mat;
        Model.material = new_mat;
        Model.materialCnt = head.material.count;
        file_mat = (HsfMaterial *)((u32)fileptr+head.material.ofs);
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
        temp_attr = file_attr = (HsfAttribute *)((u32)fileptr+head.attribute.ofs);
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
    HsfScene *file_scene;
    HsfScene *new_scene;
    if(head.scene.count) {
        file_scene = (HsfScene *)((u32)fileptr+head.scene.ofs);
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
        temp_color = file_color = (HsfBuffer *)((u32)fileptr+head.color.ofs);
        data = &file_color[head.color.count];
        for(i=0; i<head.color.count; i++, file_color++);
        new_color = temp_color;
        Model.color = new_color;
        Model.colorCnt = head.color.count;
        file_color = (HsfBuffer *)((u32)fileptr+head.color.ofs);
        data = &file_color[head.color.count];
        for(i=0; i<head.color.count; i++, new_color++, file_color++) {
            color_data = file_color->data;
            new_color->name = SetName((u32 *)&file_color->name);
            new_color->data = (void *)((u32)data+(u32)color_data);
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
        vtxtop = file_vertex = (HsfBuffer *)((u32)fileptr+head.vertex.ofs);
        data = (void *)&file_vertex[head.vertex.count];
        for(i=0; i<head.vertex.count; i++, file_vertex++) {
            for(j=0; j<(u32)file_vertex->count; j++) {
                data_elem = (HsfVector3f *)(((u32)data)+((u32)file_vertex->data)+(j*sizeof(HsfVector3f)));
            }
        }
        new_vertex = vtxtop;
        Model.vertex = new_vertex;
        Model.vertexCnt = head.vertex.count;
        file_vertex = (HsfBuffer *)((u32)fileptr+head.vertex.ofs);
        VertexDataTop = data = (void *)&file_vertex[head.vertex.count];
        for(i=0; i<head.vertex.count; i++, new_vertex++, file_vertex++) {
            temp_data = file_vertex->data;
            new_vertex->count = file_vertex->count;
            new_vertex->name = SetName((u32 *)&file_vertex->name);
            new_vertex->data = (void *)((u32)data+(u32)temp_data);
            for(j=0; j<new_vertex->count; j++) {
                data_elem = (HsfVector3f *)(((u32)data)+((u32)temp_data)+(j*sizeof(HsfVector3f)));
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
        temp_normal = file_normal = (HsfBuffer *)((u32)fileptr+head.normal.ofs);
        data = (void *)&file_normal[head.normal.count];
        new_normal = temp_normal;
        Model.normal = new_normal;
        Model.normalCnt = head.normal.count;
        file_normal = (HsfBuffer *)((u32)fileptr+head.normal.ofs);
        NormalDataTop = data = (void *)&file_normal[head.normal.count];
        for(i=0; i<head.normal.count; i++, new_normal++, file_normal++) {
            temp_data = file_normal->data;
            new_normal->count = file_normal->count;
            new_normal->name = SetName((u32 *)&file_normal->name);
            new_normal->data = (void *)((u32)data+(u32)temp_data);
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
        temp_st = file_st = (HsfBuffer *)((u32)fileptr+head.st.ofs);
        data = (void *)&file_st[head.st.count];
        for(i=0; i<head.st.count; i++, file_st++) {
            for(j=0; j<(u32)file_st->count; j++) {
                data_elem = (HsfVector2f *)(((u32)data)+((u32)file_st->data)+(j*sizeof(HsfVector2f)));
            }
        }
        new_st = temp_st;
        Model.st = new_st;
        Model.stCnt = head.st.count;
        file_st = (HsfBuffer *)((u32)fileptr+head.st.ofs);
        data = (void *)&file_st[head.st.count];
        for(i=0; i<head.st.count; i++, new_st++, file_st++) {
            temp_data = file_st->data;
            new_st->count = file_st->count;
            new_st->name = SetName((u32 *)&file_st->name);
            new_st->data = (void *)((u32)data+(u32)temp_data);
            for(j=0; j<new_st->count; j++) {
                data_elem = (HsfVector2f *)(((u32)data)+((u32)temp_data)+(j*sizeof(HsfVector2f)));
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
        temp_face = file_face = (HsfBuffer *)((u32)fileptr+head.face.ofs);
        data = (HsfFace *)&file_face[head.face.count];
        new_face = temp_face;
        Model.face = new_face;
        Model.faceCnt = head.face.count;
        file_face = (HsfBuffer *)((u32)fileptr+head.face.ofs);
        data = (HsfFace *)&file_face[head.face.count];
        for(i=0; i<head.face.count; i++, new_face++, file_face++) {
            temp_data = file_face->data;
            new_face->name = SetName((u32 *)&file_face->name);
            new_face->count = file_face->count;
            new_face->data = (void *)((u32)data+(u32)temp_data);
            strip = (u8 *)(&((HsfFace *)new_face->data)[new_face->count]);
        }
        new_face = temp_face;
        for(i=0; i<head.face.count; i++, new_face++) {
            file_face_strip = new_face_strip = new_face->data;
            for(j=0; j<new_face->count; j++, new_face_strip++, file_face_strip++) {
                if(AS_U16(file_face_strip->type) == 4) {
                    new_face_strip->strip.data = (s16 *)(strip+(u32)file_face_strip->strip.data*(sizeof(s16)*4));
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
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
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
            new_object->data.vertexShape = (HsfBuffer **)&NSymIndex[(u32)data->vertexShape];
            for(i=0; i<new_object->data.vertexShapeCnt; i++) {
                temp.shape = &vtxtop[(u32)new_object->data.vertexShape[i]];
                new_object->data.vertexShape[i] = temp.shape;
            }
            new_object->data.cluster = (HsfCluster **)&NSymIndex[(u32)data->cluster];
            for(i=0; i<new_object->data.clusterCnt; i++) {
                temp.cluster = &ClusterTop[(u32)new_object->data.cluster[i]];
                new_object->data.cluster[i] = temp.cluster;
            }
            new_object->data.cenv = SearchCenvPtr((s32)data->cenv);
            new_object->data.material = Model.material;
            if((s32)data->attribute >= 0) {
                new_object->data.attribute = Model.attribute;
            } else {
                new_object->data.attribute = NULL;
            }
            new_object->data.file[0] = (void *)((u32)fileptr+(u32)data->file[0]);
            new_object->data.file[1] = (void *)((u32)fileptr+(u32)data->file[1]);
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
        
        case HSF_OBJ_REPLICA:
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
            new_object->data.replica = &objtop[(u32)new_object->data.replica];
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
            object->type = HSF_OBJ_NONE2;
        }
        break;
        
        case 7:
        {
            objdata_7 = &object->data;
            object->type = HSF_OBJ_NONE1;
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
        objtop = object = (HsfObject *)((u32)fileptr+head.object.ofs);
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
        cenv_file = (HsfCenv *)((u32)fileptr+head.cenv.ofs);
        data_base = &cenv_file[head.cenv.count];
        weight_base = data_base;
        cenv_new = cenv_file;
        Model.cenvCnt = head.cenv.count;
        Model.cenv = cenv_file;
        for(i=0; i<head.cenv.count; i++) {
            cenv_new[i].singleData = (HsfCenvSingle *)((u32)cenv_file[i].singleData+(u32)data_base);
            cenv_new[i].dualData = (HsfCenvDual *)((u32)cenv_file[i].dualData+(u32)data_base);
            cenv_new[i].multiData = (HsfCenvMulti *)((u32)cenv_file[i].multiData+(u32)data_base);
            cenv_new[i].singleCount = cenv_file[i].singleCount;
            cenv_new[i].dualCount = cenv_file[i].dualCount;
            cenv_new[i].multiCount = cenv_file[i].multiCount;
            cenv_new[i].copyCount = cenv_file[i].copyCount;
            cenv_new[i].vtxCount = cenv_file[i].vtxCount;
            weight_base = (void *)((u32)weight_base+(cenv_new[i].singleCount*sizeof(HsfCenvSingle)));
            weight_base = (void *)((u32)weight_base+(cenv_new[i].dualCount*sizeof(HsfCenvDual)));
            weight_base = (void *)((u32)weight_base+(cenv_new[i].multiCount*sizeof(HsfCenvMulti)));
        }
        for(i=0; i<head.cenv.count; i++) {
            single_new = single_file = cenv_new[i].singleData;
            for(j=0; j<cenv_new[i].singleCount; j++) {
                single_new[j].target = single_file[j].target;
                single_new[j].posCnt = single_file[j].posCnt;
                single_new[j].pos = single_file[j].pos;
                single_new[j].normalCnt = single_file[j].normalCnt;
                single_new[j].normal = single_file[j].normal;
                
            }
            dual_new = dual_file = cenv_new[i].dualData;
            for(j=0; j<cenv_new[i].dualCount; j++) {
                dual_new[j].target1 = dual_file[j].target1;
                dual_new[j].target2 = dual_file[j].target2;
                dual_new[j].weightCnt = dual_file[j].weightCnt;
                dual_new[j].weight = (HsfCenvDualWeight *)((u32)weight_base+(u32)dual_file[j].weight);
            }
            multi_new = multi_file = cenv_new[i].multiData;
            for(j=0; j<cenv_new[i].multiCount; j++) {
                multi_new[j].weightCnt = multi_file[j].weightCnt;
                multi_new[j].pos = multi_file[j].pos;
                multi_new[j].posCnt = multi_file[j].posCnt;
                multi_new[j].normal = multi_file[j].normal;
                multi_new[j].normalCnt = multi_file[j].normalCnt;
                multi_new[j].weight = (HsfCenvMultiWeight *)((u32)weight_base+(u32)multi_file[j].weight);
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
        skeleton_new = skeleton_file = (HsfSkeleton *)((u32)fileptr+head.skeleton.ofs);
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
        part_new = part_file = (HsfPart *)((u32)fileptr+head.part.ofs);
        Model.partCnt = head.part.count;
        Model.part = part_file;
        data = (u16 *)&part_file[head.part.count];
        for(i=0; i<head.part.count; i++, part_new++) {
            part_new->name = SetName((u32 *)&part_file[i].name);
            part_new->count = part_file[i].count;
            part_new->vertex = &data[(u32)part_file[i].vertex];
            for(j=0; j<part_new->count; j++) {
                part_new->vertex[j] = part_new->vertex[j];
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
        cluster_new = cluster_file = (HsfCluster *)((u32)fileptr+head.cluster.ofs);
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
            vertexSym = (u32)cluster_file[i].vertex;
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
        shape_new = shape_file = (HsfShape *)((u32)fileptr+head.shape.ofs);
        Model.shapeCnt = head.shape.count;
        Model.shape = shape_file;
        for(i=0; i<Model.shapeCnt; i++) {
            u32 vertexSym;
            HsfBuffer *vertex;

            shape_new[i].name = SetName((u32 *)&shape_file[i].name);
            shape_new[i].count16[0] = shape_file[i].count16[0];
            shape_new[i].count16[1] = shape_file[i].count16[1];
            vertexSym = (u32)shape_file[i].vertex;
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
        mapattr_file = mapattr_base = (HsfMapAttr *)((u32)fileptr+head.mapAttr.ofs);
        mapattr_new = mapattr_base;
        Model.mapAttrCnt = head.mapAttr.count;
        Model.mapAttr = mapattr_base;
        data = (u16 *)&mapattr_base[head.mapAttr.count];
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
        bitmap_temp = bitmap_file = (HsfBitmap *)((u32)fileptr+head.bitmap.ofs);
        data = &bitmap_file[head.bitmap.count];
        for(i=0; i<head.bitmap.count; i++, bitmap_file++);
        bitmap_new = bitmap_temp;
        Model.bitmap = bitmap_file;
        Model.bitmapCnt = head.bitmap.count;
        bitmap_file = (HsfBitmap *)((u32)fileptr+head.bitmap.ofs);
        data = &bitmap_file[head.bitmap.count];
        for(i=0; i<head.bitmap.count; i++, bitmap_file++, bitmap_new++) {
            bitmap_new->name = SetName((u32 *)&bitmap_file->name);
            bitmap_new->dataFmt = bitmap_file->dataFmt;
            bitmap_new->pixSize = bitmap_file->pixSize;
            bitmap_new->sizeX = bitmap_file->sizeX;
            bitmap_new->sizeY = bitmap_file->sizeY;
            bitmap_new->palSize = bitmap_file->palSize;
            palette = SearchPalettePtr((u32)bitmap_file->palData);
            if(palette) {
                bitmap_new->palData = palette->data;
            }
            bitmap_new->data = (void *)((u32)data+(u32)bitmap_file->data);
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
        palette_temp = palette_file = (HsfPalette *)((u32)fileptr+head.palette.ofs);
        data_base = (u16 *)&palette_file[head.palette.count];
        for(i=0; i<head.palette.count; i++, palette_file++) {
            temp_data = (u16 *)((u32)data_base+(u32)palette_file->data);
        }
        Model.palette = palette_temp;
        Model.paletteCnt = head.palette.count;
        palette_new = palette_temp;
        palette_file = (HsfPalette *)((u32)fileptr+head.palette.ofs);
        data_base = (u16 *)&palette_file[head.palette.count];
        for(i=0; i<head.palette.count; i++, palette_file++, palette_new++) {
            temp_data = (u16 *)((u32)data_base+(u32)palette_file->data);
            data = temp_data;
            palette_new->name = SetName((u32 *)&palette_file->name);
            palette_new->data = data;
            palette_new->palSize = palette_file->palSize;
            for(j=0; j<palette_file->palSize; j++) {
                data[j] = data[j];
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
            step_data = (float *)((u32)data+(u32)track->data);
            out_track->data = step_data;
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((u32)data+(u32)track->data);
            out_track->data = linear_data;
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((u32)data+(u32)track->data);
            out_track->data = bezier_data;
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
            step_data = (float *)((u32)data+(u32)track->data);
            out_track->data = step_data;
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((u32)data+(u32)track->data);
            out_track->data = linear_data;
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((u32)data+(u32)track->data);
            out_track->data = bezier_data;
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
            step_data = (float *)((u32)data+(u32)track->data);
            out_track->data = step_data;
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((u32)data+(u32)track->data);
            out_track->data = linear_data;
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((u32)data+(u32)track->data);
            out_track->data = bezier_data;
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
            step_data = (float *)((u32)data+(u32)track->data);
            out_track->data = step_data;
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((u32)data+(u32)track->data);
            out_track->data = linear_data;
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((u32)data+(u32)track->data);
            out_track->data = bezier_data;
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
            step_data = (float *)((u32)data+(u32)track->data);
            out_track->data = step_data;
        }
        break;
        
        case HSF_CURVE_LINEAR:
        {
            linear_data = (float *)((u32)data+(u32)track->data);
            out_track->data = linear_data;
        }
        break;
        
        case HSF_CURVE_BEZIER:
        {
            bezier_data = (float *)((u32)data+(u32)track->data);
            out_track->data = bezier_data;
        }
        break;
        
        case HSF_CURVE_BITMAP:
        {
            new_frame = file_frame = (HsfBitmapKey *)((u32)data+(u32)track->data);
            out_track->data = file_frame;
            for(i=0; i<out_track->numKeyframes; i++, file_frame++, new_frame++) {
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
        temp_motion = file_motion = (HsfMotion *)((u32)fileptr+head.motion.ofs);
        new_motion = temp_motion;
        Model.motion = new_motion;
        Model.motionCnt = file_motion->numTracks;
        track_base = (HsfTrack *)&file_motion[head.motion.count];
        track_data = &track_base[file_motion->numTracks];
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
        matrix_file = (HsfMatrix *)((u32)fileptr+head.matrix.ofs);
        matrix_file->data = (Mtx *)((u32)fileptr+head.matrix.ofs+sizeof(HsfMatrix));
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
    vertex = (HsfBuffer *)((u32)fileptr+head.vertex.ofs);
    vertex += id;
    return vertex;
}

static HsfBuffer *SearchNormalPtr(s32 id)
{
    HsfBuffer *normal; 
    if(id == -1) {
        return NULL;
    }
    normal = (HsfBuffer *)((u32)fileptr+head.normal.ofs);
    normal += id;
    return normal;
}

static HsfBuffer *SearchStPtr(s32 id)
{
    HsfBuffer *st; 
    if(id == -1) {
        return NULL;
    }
    st = (HsfBuffer *)((u32)fileptr+head.st.ofs);
    st += id;
    return st;
}

static HsfBuffer *SearchColorPtr(s32 id)
{
    HsfBuffer *color; 
    if(id == -1) {
        return NULL;
    }
    color = (HsfBuffer *)((u32)fileptr+head.color.ofs);
    color += id;
    return color;
}

static HsfBuffer *SearchFacePtr(s32 id)
{
    HsfBuffer *face; 
    if(id == -1) {
        return NULL;
    }
    face = (HsfBuffer *)((u32)fileptr+head.face.ofs);
    face += id;
    return face;
}

static HsfCenv *SearchCenvPtr(s32 id)
{
    HsfCenv *cenv; 
    if(id == -1) {
        return NULL;
    }
    cenv = (HsfCenv *)((u32)fileptr+head.cenv.ofs);
    cenv += id;
    return cenv;
}

static HsfPart *SearchPartPtr(s32 id)
{
    HsfPart *part; 
    if(id == -1) {
        return NULL;
    }
    part = (HsfPart *)((u32)fileptr+head.part.ofs);
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
    bitmap = (HsfBitmap *)((u32)fileptr+head.bitmap.ofs);
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