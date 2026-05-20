#include "game/hsfload.h"
#include "game/EnvelopeExec.h"
#include "ctype.h"
#include "game/hsfformat.h"
#include <string.h>

#define AS_S16(field) (*((s16 *)&(field)))
#define AS_U16(field) (*((u16 *)&(field)))

GXColor rgba[100];
HSFHEADER head;
HSFDATA Model;

static BOOL MotionOnly;
static HSFDATA *MotionModel;
static void *VertexDataTop;
static void *NormalDataTop;
void *fileptr;
char *StringTable;
char *DicStringTable;
void **NSymIndex;
HSFOBJECT *objtop;
HSFBUFFER *vtxtop;
HsfCluster *ClusterTop;
HSFATTRIBUTE *AttributeTop;
HSFMATERIAL *MaterialTop;

static void FileLoad(void *data);
static HSFDATA *SetHsfModel(void);
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

static s32 SearchObjectSetName(HSFDATA *data, char *name);
static HSFBUFFER *SearchVertexPtr(s32 id);
static HSFBUFFER *SearchNormalPtr(s32 id);
static HSFBUFFER *SearchStPtr(s32 id);
static HSFBUFFER *SearchColorPtr(s32 id);
static HSFBUFFER *SearchFacePtr(s32 id);
static HSFCENV *SearchCenvPtr(s32 id);
static HsfPart *SearchPartPtr(s32 id);
static HSFPALETTE *SearchPalettePtr(s32 id);

static HSFBITMAP *SearchBitmapPtr(s32 id);
static char *GetString(u32 *str_ofs);
static char *GetMotionString(u16 *str_ofs);

HSFDATA *LoadHSF(void *data)
{
    HSFDATA *hsf;
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

void ClusterAdjustObject(HSFDATA *model, HSFDATA *src_model)
{
    HsfCluster *cluster;
    s32 i;
    if(!src_model) {
        return;
    }
    if(src_model->clusterNum == 0) {
        return;
    }
    cluster = src_model->cluster;
    if(cluster->adjusted) {
        return;
    }
    cluster->adjusted = 1;
    for(i=0; i<src_model->clusterNum; i++, cluster++) {
        char *name = cluster->targetName;
        cluster->target = SearchObjectSetName(model, name);
    }
}

static void FileLoad(void *data)
{
    fileptr = data;
    memcpy(&head, fileptr, sizeof(HSFHEADER));
    memset(&Model, 0, sizeof(HSFDATA));
    NSymIndex = (void **)((u32)fileptr+head.symbol.ofs);
    StringTable = (char *)((u32)fileptr+head.string.ofs);
    ClusterTop = (HsfCluster *)((u32)fileptr+head.cluster.ofs);
    AttributeTop = (HSFATTRIBUTE *)((u32)fileptr+head.attribute.ofs);
    MaterialTop = (HSFMATERIAL *)((u32)fileptr+head.material.ofs);
}

static HSFDATA *SetHsfModel(void)
{
    HSFDATA *data = fileptr;
    data->scene = Model.scene;
    data->sceneNum = Model.sceneNum;
    data->attribute = Model.attribute;
    data->attributeNum = Model.attributeNum;
    data->bitmap = Model.bitmap;
    data->bitmapNum = Model.bitmapNum;
    data->cenv = Model.cenv;
    data->cenvNum = Model.cenvNum;
    data->skeleton = Model.skeleton;
    data->skeletonNum = Model.skeletonNum;
    data->face = Model.face;
    data->faceNum = Model.faceNum;
    data->material = Model.material;
    data->materialNum = Model.materialNum;
    data->motion = Model.motion;
    data->motionNum = Model.motionNum;
    data->normal = Model.normal;
    data->normalNum = Model.normalNum;
    data->root = Model.root;
    data->objectNum = Model.objectNum;
    data->object = objtop;
    data->matrix = Model.matrix;
    data->matrixNum = Model.matrixNum;
    data->palette = Model.palette;
    data->paletteNum = Model.paletteNum;
    data->st = Model.st;
    data->stNum = Model.stNum;
    data->vertex = Model.vertex;
    data->vertexNum = Model.vertexNum;
    data->cenv = Model.cenv;
    data->cenvNum = Model.cenvNum;
    data->cluster = Model.cluster;
    data->clusterNum = Model.clusterNum;
    data->part = Model.part;
    data->partNum = Model.partNum;
    data->shape = Model.shape;
    data->shapeNum = Model.shapeNum;
    data->mapAttr = Model.mapAttr;
    data->mapAttrNum = Model.mapAttrNum;
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
        HSFMATERIAL *file_mat = (HSFMATERIAL *)((u32)fileptr+head.material.ofs);
        HSFMATERIAL *curr_mat;
        HSFMATERIAL *new_mat;
        for(i=0; i<head.material.count; i++) {
            curr_mat = &file_mat[i];
        }
        new_mat = file_mat;
        Model.material = new_mat;
        Model.materialNum = head.material.count;
        file_mat = (HSFMATERIAL *)((u32)fileptr+head.material.ofs);
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
            new_mat->hiliteScale = curr_mat->hiliteScale;
            new_mat->unk18 = curr_mat->unk18;
            new_mat->invAlpha = curr_mat->invAlpha;
            new_mat->unk20[0] = curr_mat->unk20[0];
            new_mat->unk20[1] = curr_mat->unk20[1];
            new_mat->refAlpha = curr_mat->refAlpha;
            new_mat->unk2C = curr_mat->unk2C;
            new_mat->attrNum = curr_mat->attrNum;
            new_mat->attr = (s32 *)(NSymIndex+((u32)curr_mat->attr));
            rgba[i].r = new_mat->litColor[0];
            rgba[i].g = new_mat->litColor[1];
            rgba[i].b = new_mat->litColor[2];
            rgba[i].a = 255;
            for(j=0; j<new_mat->attrNum; j++) {
                new_mat->attr[j] = new_mat->attr[j];
            }
        }
    }
}

static void AttributeLoad(void)
{
    HSFATTRIBUTE *file_attr;
    HSFATTRIBUTE *new_attr;
    HSFATTRIBUTE *temp_attr;
    s32 i;
    if(head.attribute.count) {
        temp_attr = file_attr = (HSFATTRIBUTE *)((u32)fileptr+head.attribute.ofs);
        new_attr = temp_attr;
        Model.attribute = new_attr;
        Model.attributeNum = head.attribute.count;
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
    HSFSCENE *file_scene;
    HSFSCENE *new_scene;
    if(head.scene.count) {
        file_scene = (HSFSCENE *)((u32)fileptr+head.scene.ofs);
        new_scene = file_scene;
        new_scene->fogEnd = file_scene->fogEnd;
        new_scene->fogStart = file_scene->fogStart;
        Model.scene = new_scene;
        Model.sceneNum = head.scene.count;
    }
}

static void ColorLoad(void)
{
    s32 i;
    HSFBUFFER *file_color;
    HSFBUFFER *new_color;
    void *data;
    void *color_data;
    HSFBUFFER *temp_color;
    
    if(head.color.count) {
        temp_color = file_color = (HSFBUFFER *)((u32)fileptr+head.color.ofs);
        data = &file_color[head.color.count];
        for(i=0; i<head.color.count; i++, file_color++);
        new_color = temp_color;
        Model.color = new_color;
        Model.colorNum = head.color.count;
        file_color = (HSFBUFFER *)((u32)fileptr+head.color.ofs);
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
    HSFBUFFER *file_vertex;
    HSFBUFFER *new_vertex;
    void *data;
    HuVecF *data_elem;
    void *temp_data;
    
    if(head.vertex.count) {
        vtxtop = file_vertex = (HSFBUFFER *)((u32)fileptr+head.vertex.ofs);
        data = (void *)&file_vertex[head.vertex.count];
        for(i=0; i<head.vertex.count; i++, file_vertex++) {
            for(j=0; j<(u32)file_vertex->count; j++) {
                data_elem = (HuVecF *)(((u32)data)+((u32)file_vertex->data)+(j*sizeof(HuVecF)));
            }
        }
        new_vertex = vtxtop;
        Model.vertex = new_vertex;
        Model.vertexNum = head.vertex.count;
        file_vertex = (HSFBUFFER *)((u32)fileptr+head.vertex.ofs);
        VertexDataTop = data = (void *)&file_vertex[head.vertex.count];
        for(i=0; i<head.vertex.count; i++, new_vertex++, file_vertex++) {
            temp_data = file_vertex->data;
            new_vertex->count = file_vertex->count;
            new_vertex->name = SetName((u32 *)&file_vertex->name);
            new_vertex->data = (void *)((u32)data+(u32)temp_data);
            for(j=0; j<new_vertex->count; j++) {
                data_elem = (HuVecF *)(((u32)data)+((u32)temp_data)+(j*sizeof(HuVecF)));
                ((HuVecF *)new_vertex->data)[j].x = data_elem->x;
                ((HuVecF *)new_vertex->data)[j].y = data_elem->y;
                ((HuVecF *)new_vertex->data)[j].z = data_elem->z;
            }
        }
    }
}

static void NormalLoad(void)
{
    s32 i, j;
    void *temp_data;
    HSFBUFFER *file_normal;
    HSFBUFFER *new_normal;
    HSFBUFFER *temp_normal;
    void *data;
    
    
    if(head.normal.count) {
        s32 cenv_count = head.cenv.count;
        temp_normal = file_normal = (HSFBUFFER *)((u32)fileptr+head.normal.ofs);
        data = (void *)&file_normal[head.normal.count];
        new_normal = temp_normal;
        Model.normal = new_normal;
        Model.normalNum = head.normal.count;
        file_normal = (HSFBUFFER *)((u32)fileptr+head.normal.ofs);
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
    HSFBUFFER *file_st;
    HSFBUFFER *temp_st;
    HSFBUFFER *new_st;
    void *data;
    HuVec2f *data_elem;
    void *temp_data;
    
    if(head.st.count) {
        temp_st = file_st = (HSFBUFFER *)((u32)fileptr+head.st.ofs);
        data = (void *)&file_st[head.st.count];
        for(i=0; i<head.st.count; i++, file_st++) {
            for(j=0; j<(u32)file_st->count; j++) {
                data_elem = (HuVec2f *)(((u32)data)+((u32)file_st->data)+(j*sizeof(HuVec2f)));
            }
        }
        new_st = temp_st;
        Model.st = new_st;
        Model.stNum = head.st.count;
        file_st = (HSFBUFFER *)((u32)fileptr+head.st.ofs);
        data = (void *)&file_st[head.st.count];
        for(i=0; i<head.st.count; i++, new_st++, file_st++) {
            temp_data = file_st->data;
            new_st->count = file_st->count;
            new_st->name = SetName((u32 *)&file_st->name);
            new_st->data = (void *)((u32)data+(u32)temp_data);
            for(j=0; j<new_st->count; j++) {
                data_elem = (HuVec2f *)(((u32)data)+((u32)temp_data)+(j*sizeof(HuVec2f)));
                ((HuVec2f *)new_st->data)[j].x = data_elem->x;
                ((HuVec2f *)new_st->data)[j].y = data_elem->y;
            }
        }
    }
}

static void FaceLoad(void)
{
    HSFBUFFER *file_face;
    HSFBUFFER *new_face;
    HSFBUFFER *temp_face;
    HSFFACE *temp_data;
    HSFFACE *data;
    HSFFACE *file_face_strip;
    HSFFACE *new_face_strip;
    u8 *strip;
    s32 i;
    s32 j;
    
    if(head.face.count) {
        temp_face = file_face = (HSFBUFFER *)((u32)fileptr+head.face.ofs);
        data = (HSFFACE *)&file_face[head.face.count];
        new_face = temp_face;
        Model.face = new_face;
        Model.faceNum = head.face.count;
        file_face = (HSFBUFFER *)((u32)fileptr+head.face.ofs);
        data = (HSFFACE *)&file_face[head.face.count];
        for(i=0; i<head.face.count; i++, new_face++, file_face++) {
            temp_data = file_face->data;
            new_face->name = SetName((u32 *)&file_face->name);
            new_face->count = file_face->count;
            new_face->data = (void *)((u32)data+(u32)temp_data);
            strip = (u8 *)(&((HSFFACE *)new_face->data)[new_face->count]);
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

static void DispObject(HSFOBJECT *parent, HSFOBJECT *object)
{
    u32 i;
    HSFOBJECT *child_obj;
    HSFOBJECT *temp_object;
    struct {
        HSFOBJECT *parent;
        HSFBUFFER *shape;
        HsfCluster *cluster;
    } temp;
    
    temp.parent = parent;
    object->type = object->type;
    switch(object->type) {
        case HSF_OBJ_MESH:
        {
            HSFMESH *data;
            HSFOBJECT *new_object;
            
            data = &object->mesh;
            new_object = temp_object = object;
            new_object->mesh.childrenCount = data->childrenCount;
            new_object->mesh.children = (HSFOBJECT **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->mesh.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->mesh.children[i]];
                new_object->mesh.children[i] = child_obj;
            }
            new_object->mesh.parent = parent;
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            new_object->type = HSF_OBJ_MESH;
            new_object->mesh.vertex = SearchVertexPtr((s32)data->vertex);
            new_object->mesh.normal = SearchNormalPtr((s32)data->normal);
            new_object->mesh.st = SearchStPtr((s32)data->st);
            new_object->mesh.color = SearchColorPtr((s32)data->color);
            new_object->mesh.face = SearchFacePtr((s32)data->face);
            new_object->mesh.shape = (HSFBUFFER **)&NSymIndex[(u32)data->shape];
            for(i=0; i<new_object->mesh.shapeNum; i++) {
                temp.shape = &vtxtop[(u32)new_object->mesh.shape[i]];
                new_object->mesh.shape[i] = temp.shape;
            }
            new_object->mesh.cluster = (HsfCluster **)&NSymIndex[(u32)data->cluster];
            for(i=0; i<new_object->mesh.clusterNum; i++) {
                temp.cluster = &ClusterTop[(u32)new_object->mesh.cluster[i]];
                new_object->mesh.cluster[i] = temp.cluster;
            }
            new_object->mesh.cenv = SearchCenvPtr((s32)data->cenv);
            new_object->mesh.material = Model.material;
            if((s32)data->attribute >= 0) {
                new_object->mesh.attribute = Model.attribute;
            } else {
                new_object->mesh.attribute = NULL;
            }
            new_object->mesh.file[0] = (void *)((u32)fileptr+(u32)data->file[0]);
            new_object->mesh.file[1] = (void *)((u32)fileptr+(u32)data->file[1]);
            new_object->mesh.base.pos.x = data->base.pos.x;
            new_object->mesh.base.pos.y = data->base.pos.y;
            new_object->mesh.base.pos.z = data->base.pos.z;
            new_object->mesh.base.rot.x = data->base.rot.x;
            new_object->mesh.base.rot.y = data->base.rot.y;
            new_object->mesh.base.rot.z = data->base.rot.z;
            new_object->mesh.base.scale.x = data->base.scale.x;
            new_object->mesh.base.scale.y = data->base.scale.y;
            new_object->mesh.base.scale.z = data->base.scale.z;
            new_object->mesh.mesh.min.x = data->mesh.min.x;
            new_object->mesh.mesh.min.y = data->mesh.min.y;
            new_object->mesh.mesh.min.z = data->mesh.min.z;
            new_object->mesh.mesh.max.x = data->mesh.max.x;
            new_object->mesh.mesh.max.y = data->mesh.max.y;
            new_object->mesh.mesh.max.z = data->mesh.max.z;
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->mesh.children[i]);
            }
        }
        break;
            
        case HSF_OBJ_NULL1:
        {
            HSFMESH *data;
            HSFOBJECT *new_object;
            data = &object->mesh;
            new_object = temp_object = object;
            new_object->mesh.parent = parent;
            new_object->mesh.childrenCount = data->childrenCount;
            new_object->mesh.children = (HSFOBJECT **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->mesh.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->mesh.children[i]];
                new_object->mesh.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->mesh.children[i]);
            }
        }
        break;
        
        case HSF_OBJ_REPLICA:
        {
            HSFMESH *data;
            HSFOBJECT *new_object;
            data = &object->mesh;
            new_object = temp_object = object;
            new_object->mesh.parent = parent;
            new_object->mesh.childrenCount = data->childrenCount;
            new_object->mesh.children = (HSFOBJECT **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->mesh.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->mesh.children[i]];
                new_object->mesh.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            new_object->mesh.replica = &objtop[(u32)new_object->mesh.replica];
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->mesh.children[i]);
            }
        }
        break;

        case HSF_OBJ_ROOT:
        {
            HSFMESH *data;
            HSFOBJECT *new_object;
            data = &object->mesh;
            new_object = temp_object = object;
            new_object->mesh.parent = parent;
            new_object->mesh.childrenCount = data->childrenCount;
            new_object->mesh.children = (HSFOBJECT **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->mesh.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->mesh.children[i]];
                new_object->mesh.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->mesh.children[i]);
            }
        }
        break;
        
        case HSF_OBJ_JOINT:
        {
            HSFMESH *data;
            HSFOBJECT *new_object;
            data = &object->mesh;
            new_object = temp_object = object;
            new_object->mesh.parent = parent;
            new_object->mesh.childrenCount = data->childrenCount;
            new_object->mesh.children = (HSFOBJECT **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->mesh.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->mesh.children[i]];
                new_object->mesh.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->mesh.children[i]);
            }
        }
        break;
        
        case HSF_OBJ_NULL2:
        {
            HSFMESH *data;
            HSFOBJECT *new_object;
            data = &object->mesh;
            new_object = temp_object = object;
            new_object->mesh.parent = parent;
            new_object->mesh.childrenCount = data->childrenCount;
            new_object->mesh.children = (HSFOBJECT **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->mesh.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->mesh.children[i]];
                new_object->mesh.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->mesh.children[i]);
            }
        }
        break;
        
        case HSF_OBJ_MAP:
        {
            HSFMESH *data;
            HSFOBJECT *new_object;
            data = &object->mesh;
            new_object = temp_object = object;
            new_object->mesh.parent = parent;
            new_object->mesh.childrenCount = data->childrenCount;
            new_object->mesh.children = (HSFOBJECT **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->mesh.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->mesh.children[i]];
                new_object->mesh.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->mesh.children[i]);
            }
        }
        break;
        
        default:
            break;
    }
}

static inline void FixupObject(HSFOBJECT *object)
{
    HSFMESH *objdata_8;
    HSFMESH *objdata_7;
    
    s32 obj_type = object->type;
    switch(obj_type) {
        case 8:
        {
            objdata_8 = &object->mesh;
            object->type = HSF_OBJ_NONE2;
        }
        break;
        
        case 7:
        {
            objdata_7 = &object->mesh;
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
    HSFOBJECT *object;
    HSFOBJECT *new_object;
    s32 obj_type;

    if(head.object.count) {
        objtop = object = (HSFOBJECT *)((u32)fileptr+head.object.ofs);
        for(i=0; i<head.object.count; i++, object++) {
            new_object = object;
            new_object->name = SetName((u32 *)&object->name);
        }
        object = objtop;
        for(i=0; i<head.object.count; i++, object++) {
            if((s32)object->mesh.parent == -1) {
                break;
            }
        }
        DispObject(NULL, object);
        Model.objectNum = head.object.count;
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
    HSFCENVSINGLE *single_new;
    HSFCENVSINGLE *single_file;
    HSFCENVDUAL *dual_file;
    HSFCENVDUAL *dual_new;

    HSFCENV *cenv_new;
    HSFCENV *cenv_file;
    void *data_base;
    void *weight_base;
    
    s32 j;
    s32 i;
    
    if(head.cenv.count) {
        cenv_file = (HSFCENV *)((u32)fileptr+head.cenv.ofs);
        data_base = &cenv_file[head.cenv.count];
        weight_base = data_base;
        cenv_new = cenv_file;
        Model.cenvNum = head.cenv.count;
        Model.cenv = cenv_file;
        for(i=0; i<head.cenv.count; i++) {
            cenv_new[i].singleData = (HSFCENVSINGLE *)((u32)cenv_file[i].singleData+(u32)data_base);
            cenv_new[i].dualData = (HSFCENVDUAL *)((u32)cenv_file[i].dualData+(u32)data_base);
            cenv_new[i].multiData = (HsfCenvMulti *)((u32)cenv_file[i].multiData+(u32)data_base);
            cenv_new[i].singleCount = cenv_file[i].singleCount;
            cenv_new[i].dualCount = cenv_file[i].dualCount;
            cenv_new[i].multiCount = cenv_file[i].multiCount;
            cenv_new[i].copyCount = cenv_file[i].copyCount;
            cenv_new[i].vtxCount = cenv_file[i].vtxCount;
            weight_base = (void *)((u32)weight_base+(cenv_new[i].singleCount*sizeof(HSFCENVSINGLE)));
            weight_base = (void *)((u32)weight_base+(cenv_new[i].dualCount*sizeof(HSFCENVDUAL)));
            weight_base = (void *)((u32)weight_base+(cenv_new[i].multiCount*sizeof(HsfCenvMulti)));
        }
        for(i=0; i<head.cenv.count; i++) {
            single_new = single_file = cenv_new[i].singleData;
            for(j=0; j<cenv_new[i].singleCount; j++) {
                single_new[j].target = single_file[j].target;
                single_new[j].posNum = single_file[j].posNum;
                single_new[j].pos = single_file[j].pos;
                single_new[j].normalNum = single_file[j].normalNum;
                single_new[j].normal = single_file[j].normal;
                
            }
            dual_new = dual_file = cenv_new[i].dualData;
            for(j=0; j<cenv_new[i].dualCount; j++) {
                dual_new[j].target1 = dual_file[j].target1;
                dual_new[j].target2 = dual_file[j].target2;
                dual_new[j].weightNum = dual_file[j].weightNum;
                dual_new[j].weight = (HSFCENVDUALWEIGHT *)((u32)weight_base+(u32)dual_file[j].weight);
            }
            multi_new = multi_file = cenv_new[i].multiData;
            for(j=0; j<cenv_new[i].multiCount; j++) {
                multi_new[j].weightNum = multi_file[j].weightNum;
                multi_new[j].pos = multi_file[j].pos;
                multi_new[j].posNum = multi_file[j].posNum;
                multi_new[j].normal = multi_file[j].normal;
                multi_new[j].normalNum = multi_file[j].normalNum;
                multi_new[j].weight = (HSFCENVMULTIWEIGHT *)((u32)weight_base+(u32)multi_file[j].weight);
            }
            dual_new = dual_file = cenv_new[i].dualData;
            for(j=0; j<cenv_new[i].dualCount; j++) {
                HSFCENVDUALWEIGHT *discard = dual_new[j].weight;
            }
            multi_new = multi_file = cenv_new[i].multiData;
            for(j=0; j<cenv_new[i].multiCount; j++) {
                HSFCENVMULTIWEIGHT *weight = multi_new[j].weight;
                s32 k;
                for(k=0; k<multi_new[j].weightNum; k++, weight++);
            }
        }
    }
}

static void SkeletonLoad(void)
{
    HSFSKELETON *skeleton_file;
    HSFSKELETON *skeleton_new;
    s32 i;
    
    if(head.skeleton.count) {
        skeleton_new = skeleton_file = (HSFSKELETON *)((u32)fileptr+head.skeleton.ofs);
        Model.skeletonNum = head.skeleton.count;
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
        Model.partNum = head.part.count;
        Model.part = part_file;
        data = (u16 *)&part_file[head.part.count];
        for(i=0; i<head.part.count; i++, part_new++) {
            part_new->name = SetName((u32 *)&part_file[i].name);
            part_new->num = part_file[i].num;
            part_new->vertex = &data[(u32)part_file[i].vertex];
            for(j=0; j<part_new->num; j++) {
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
        Model.clusterNum = head.cluster.count;
        Model.cluster = cluster_file;
        for(i=0; i<head.cluster.count; i++) {
            HSFBUFFER *vertex;
            u32 vertexSym;
            cluster_new[i].name[0] = SetName((u32 *)&cluster_file[i].name[0]);
            cluster_new[i].name[1] = SetName((u32 *)&cluster_file[i].name[1]);
            cluster_new[i].targetName = SetName((u32 *)&cluster_file[i].targetName);
            cluster_new[i].part = SearchPartPtr((s32)cluster_file[i].part);
            cluster_new[i].unk95 = cluster_file[i].unk95;
            cluster_new[i].type = cluster_file[i].type;
            cluster_new[i].vertexNum = cluster_file[i].vertexNum;
            vertexSym = (u32)cluster_file[i].vertex;
            cluster_new[i].vertex = (HSFBUFFER **)&NSymIndex[vertexSym];
            for(j=0; j<cluster_new[i].vertexNum; j++) {
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
        Model.shapeNum = head.shape.count;
        Model.shape = shape_file;
        for(i=0; i<Model.shapeNum; i++) {
            u32 vertexSym;
            HSFBUFFER *vertex;

            shape_new[i].name = SetName((u32 *)&shape_file[i].name);
            shape_new[i].num16[0] = shape_file[i].num16[0];
            shape_new[i].num16[1] = shape_file[i].num16[1];
            vertexSym = (u32)shape_file[i].vertex;
            shape_new[i].vertex = (HSFBUFFER **)&NSymIndex[vertexSym];
            for(j=0; j<shape_new[i].num16[1]; j++) {
                vertex = &vtxtop[(u32)shape_new[i].vertex[j]];
                shape_new[i].vertex[j] = vertex;
            }
        }
    }
}

static void MapAttrLoad(void)
{
    s32 i;
    HSFMAPATTR *mapattr_base;
    HSFMAPATTR *mapattr_file;
    HSFMAPATTR *mapattr_new;
    u16 *data;
    
    if(head.mapAttr.count) {
        mapattr_file = mapattr_base = (HSFMAPATTR *)((u32)fileptr+head.mapAttr.ofs);
        mapattr_new = mapattr_base;
        Model.mapAttrNum = head.mapAttr.count;
        Model.mapAttr = mapattr_base;
        data = (u16 *)&mapattr_base[head.mapAttr.count];
        for(i=0; i<head.mapAttr.count; i++, mapattr_file++, mapattr_new++) {
            mapattr_new->data = &data[(u32)mapattr_file->data];
        }
    }
}

static void BitmapLoad(void)
{
    HSFBITMAP *bitmap_file;
    HSFBITMAP *bitmap_temp;
    HSFBITMAP *bitmap_new;
    HSFPALETTE *palette;
    void *data;
    s32 i;
    
    if(head.bitmap.count) {
        bitmap_temp = bitmap_file = (HSFBITMAP *)((u32)fileptr+head.bitmap.ofs);
        data = &bitmap_file[head.bitmap.count];
        for(i=0; i<head.bitmap.count; i++, bitmap_file++);
        bitmap_new = bitmap_temp;
        Model.bitmap = bitmap_file;
        Model.bitmapNum = head.bitmap.count;
        bitmap_file = (HSFBITMAP *)((u32)fileptr+head.bitmap.ofs);
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
    HSFPALETTE *palette_file;
    HSFPALETTE *palette_temp;
    HSFPALETTE *palette_new;
    
    void *data_base;
    u16 *temp_data;
    u16 *data;
    
    if(head.palette.count) {
        palette_temp = palette_file = (HSFPALETTE *)((u32)fileptr+head.palette.ofs);
        data_base = (u16 *)&palette_file[head.palette.count];
        for(i=0; i<head.palette.count; i++, palette_file++) {
            temp_data = (u16 *)((u32)data_base+(u32)palette_file->data);
        }
        Model.palette = palette_temp;
        Model.paletteNum = head.palette.count;
        palette_new = palette_temp;
        palette_file = (HSFPALETTE *)((u32)fileptr+head.palette.ofs);
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

static inline char *MotionGetName(HSFTRACK *track)
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
    HSFOBJECT *object;
    
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
    for(i=0; i<MotionModel->clusterNum; i++, cluster++) {
        if(!strcmp(cluster->name[0], name)) {
            return i;
        }
    }
    return -1;
}

static inline s32 FindAttributeName(char *name)
{
    s32 i;
    HSFATTRIBUTE *attribute;
    
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
    HSFATTRIBUTE *attribute;
    
    attribute = MotionModel->attribute;
    for(i=0; i<MotionModel->attributeNum; i++, attribute++) {
        if(!attribute->name) {
            continue;
        }
        if(!strcmp(attribute->name, name)) {
            return i;
        }
    }
    return -1;
}

static inline void MotionLoadTransform(HSFTRACK *track, void *data)
{
    float *step_data;
    float *linear_data;
    float *bezier_data;
    HSFTRACK *out_track;
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

static inline void MotionLoadCluster(HSFTRACK *track, void *data)
{
    s32 numKeyframes;
    float *step_data;
    float *linear_data;
    float *bezier_data;
    HSFTRACK *out_track;
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

static inline void MotionLoadClusterWeight(HSFTRACK *track, void *data)
{
    s32 numKeyframes;
    float *step_data;
    float *linear_data;
    float *bezier_data;
    HSFTRACK *out_track;
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

static inline void MotionLoadMaterial(HSFTRACK *track, void *data)
{
    float *step_data;
    float *linear_data;
    float *bezier_data;
    s32 numKeyframes;
    HSFTRACK *out_track;
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

static inline void MotionLoadAttribute(HSFTRACK *track, void *data)
{
    HSFBITMAPKEY *file_frame;
    HSFBITMAPKEY *new_frame;
    s32 i;
    float *step_data;
    float *linear_data;
    float *bezier_data;
    HSFTRACK *out_track;
    char *name;
    out_track = track;
    if(AS_S16(out_track->target) != -1) {
        name = SetMotionName(&track->target);
        if(!MotionOnly) {
            AS_S16(out_track->attrIdx) = FindAttributeName(name);
        } else {
            AS_S16(out_track->attrIdx) = FindMotionAttributeName(name);
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
            new_frame = file_frame = (HSFBITMAPKEY *)((u32)data+(u32)track->data);
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
    HSFMOTION *file_motion;
    HSFMOTION *temp_motion;
    HSFMOTION *new_motion;
    HSFTRACK *track_base;
    void *track_data;
    s32 i;
    
    MotionOnly = FALSE;
    MotionModel = NULL;
    if(head.motion.count) {
        temp_motion = file_motion = (HSFMOTION *)((u32)fileptr+head.motion.ofs);
        new_motion = temp_motion;
        Model.motion = new_motion;
        Model.motionNum = file_motion->numTracks;
        track_base = (HSFTRACK *)&file_motion[head.motion.count];
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
    HSFMATRIX *matrix_file;
    
    if(head.matrix.count) {
        matrix_file = (HSFMATRIX *)((u32)fileptr+head.matrix.ofs);
        matrix_file->data = (Mtx *)((u32)fileptr+head.matrix.ofs+sizeof(HSFMATRIX));
        Model.matrix = matrix_file;
        Model.matrixNum = head.matrix.count;
    }
}

static s32 SearchObjectSetName(HSFDATA *data, char *name)
{
    HSFOBJECT *object = data->object;
    s32 i;
    for(i=0; i<data->objectNum; i++, object++) {
        if(!CmpObjectName(object->name, name)) {
            return i;
        }
    }
    OSReport("Search Object Error %s\n", name);
    return -1;
}

static HSFBUFFER *SearchVertexPtr(s32 id)
{
    HSFBUFFER *vertex; 
    if(id == -1) {
        return NULL;
    }
    vertex = (HSFBUFFER *)((u32)fileptr+head.vertex.ofs);
    vertex += id;
    return vertex;
}

static HSFBUFFER *SearchNormalPtr(s32 id)
{
    HSFBUFFER *normal; 
    if(id == -1) {
        return NULL;
    }
    normal = (HSFBUFFER *)((u32)fileptr+head.normal.ofs);
    normal += id;
    return normal;
}

static HSFBUFFER *SearchStPtr(s32 id)
{
    HSFBUFFER *st; 
    if(id == -1) {
        return NULL;
    }
    st = (HSFBUFFER *)((u32)fileptr+head.st.ofs);
    st += id;
    return st;
}

static HSFBUFFER *SearchColorPtr(s32 id)
{
    HSFBUFFER *color; 
    if(id == -1) {
        return NULL;
    }
    color = (HSFBUFFER *)((u32)fileptr+head.color.ofs);
    color += id;
    return color;
}

static HSFBUFFER *SearchFacePtr(s32 id)
{
    HSFBUFFER *face; 
    if(id == -1) {
        return NULL;
    }
    face = (HSFBUFFER *)((u32)fileptr+head.face.ofs);
    face += id;
    return face;
}

static HSFCENV *SearchCenvPtr(s32 id)
{
    HSFCENV *cenv; 
    if(id == -1) {
        return NULL;
    }
    cenv = (HSFCENV *)((u32)fileptr+head.cenv.ofs);
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

static HSFPALETTE *SearchPalettePtr(s32 id)
{
    HSFPALETTE *palette; 
    if(id == -1) {
        return NULL;
    }
    palette = Model.palette;
    palette += id;
    return palette;
}

static HSFBITMAP *SearchBitmapPtr(s32 id)
{
    HSFBITMAP *bitmap; 
    if(id == -1) {
        return NULL;
    }
    bitmap = (HSFBITMAP *)((u32)fileptr+head.bitmap.ofs);
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
