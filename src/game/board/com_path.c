#include "game/board/com_path.h"
#include "game/board/space.h"
#include "game/flag.h"

#include <string.h>

#define NODE_INDEX(x) ((x) ? ((x) - pathNodeData) : -1)

typedef struct {
    /* 0x00 */ struct {
        u8 used : 1;
        u8 star : 1;
        u8 pipe : 1;
        u8 shop : 1;
        u8 boo : 1;
        u8 lottery : 1;
    };
    /* 0x01 */ s8 num_links;
    /* 0x02 */ s8 num_children;
    /* 0x03 */ s8 max_len;
    /* 0x04 */ s16 start;
    /* 0x06 */ s16 children[32];
    /* 0x46 */ s16 links[BOARD_SPACE_LINKMAX+1];
} PathNode; // Size 0x50

static PathNode *SearchPathNodeSpace(s16 arg0);
static s16 InitPathNode(PathNode *arg0);
static PathNode *FindChildNode(s16 arg0, PathNode *arg1);
static s32 GetNumValidLinks(BoardSpace *arg0, PathNode *arg1);
static void AddValidLinks(BoardSpace *arg0, PathNode *arg1);
static BOOL CheckPathSpace(BoardSpace *arg0);
static s16 FindValidLink(BoardSpace *arg0);
static BOOL CheckEndSpace(BoardSpace *arg0, PathNode *arg1);
static BOOL CheckPath(PathNode *arg0);
static BOOL CheckPathFlag(PathNode *arg0, u32 arg1);

static PathNode pathNodeData[16];
static PathNode *candidateNodes[16];
static s16 startPathSpaceSearch[16];
static s16 startPathSpace[16];

static s16 numCandidates;
static s16 childNodeCnt;

static PathNode *SearchPathNodeSpace(s16 space) {
    PathNode *node;
    s32 i;

    for (node = pathNodeData, i = 0; i < 16; i++, node++) {
        if (node->start == space) {
            break;
        }
    }
    if (i == 16) {
        node = NULL;
    }
    return node;
}

static s16 InitPathNode(PathNode *node) {
    BoardSpace *space_ptr;
    PathNode *child;
    s32 done;
    s16 i;
    s16 space;
    s16 num_links;
    s16 path_len;
    s16 space_link;

    space_link = node->start;
    done = 0;
    node->num_children = path_len = 0;
    do {
        space = space_link;
        space_ptr = BoardSpaceGet(0, space);
        node->children[node->num_children] = space;
        child = FindChildNode(space, node);
        if (child) {
            AddValidLinks(space_ptr, node);
            node->num_links = 1;
            node->links[0] = space;
            for (i = 1; i < 5; i++) {
                node->links[i] = 0;
            }
            return 0;
        }
        if (space_ptr->link_cnt == 0) {
            num_links = 0;
            done = 1;
        } else {
            num_links = GetNumValidLinks(space_ptr, node);
            if (num_links == 1) {
                space_link = FindValidLink(space_ptr);
            } else {
                done = 1;
            }
        }
        if (CheckEndSpace(space_ptr, node)) {
            path_len++;
            if (path_len >= node->max_len) {
                num_links = 0;
                done = 1;
            }
        }
        node->num_children++;
    } while (done == 0);
    AddValidLinks(space_ptr, node);
    node->num_links = num_links;
    return node->max_len - path_len;
}

static PathNode *FindChildNode(s16 arg0, PathNode *arg1) {
    PathNode *node;
    s32 node_idx;
    s32 i;
    s32 j;

    node_idx = NODE_INDEX(arg1);
    if (node_idx == -1) {
        return NULL;
    }
    for (i = 0; i < childNodeCnt; i++) {
        node = &pathNodeData[i];
        if (node != arg1) {
            for (j = 0; j < node->num_children; j++) {
                if (arg0 == node->children[j]) {
                    return node;
                }
            }
        }
    }
    return NULL;
}

static s32 GetNumValidLinks(BoardSpace *space, PathNode *node) {
    BoardSpace *link_space;
    s16 i;
    s16 invalid_links;

    for (invalid_links = i = 0; i < space->link_cnt; i++) {
        link_space = BoardSpaceGet(0, space->link[i]);
        if (!CheckPathSpace(link_space)) {
            invalid_links++;
        }
    }
    if (invalid_links >= space->link_cnt) {
        return 0;
    }
    return space->link_cnt - invalid_links;
}

static void AddValidLinks(BoardSpace *space, PathNode *node) {
    BoardSpace *link_space;
    s16 i;
    s16 link;

    for (link = i = 0; i < space->link_cnt; i++) {
        link_space = BoardSpaceGet(0, space->link[i]);
        if (CheckPathSpace(link_space)) {
            node->links[link] = space->link[i];
            link++;
        }
    }
    for (; link < BOARD_SPACE_LINKMAX+1; link++) {
        node->links[link] = 0;
    }
}

static BOOL CheckPathSpace(BoardSpace *space) {
    if ((space->flag & 0x02000000) || (space->flag & 0x04000000)) {
        return FALSE;
    } else {
        return TRUE;
    }
}

static s16 FindValidLink(BoardSpace *space) {
    s16 space_link;
    s16 i;
    BoardSpace *space_ptr;

    for (space_link = i = 0; i < space->link_cnt; i++) {
        space_link = space->link[i];
        space_ptr = BoardSpaceGet(0, space_link);
        if (CheckPathSpace(space_ptr)) {
            break;
        }
    }
    return space_link;
}

static BOOL CheckEndSpace(BoardSpace *space, PathNode *node) {
    if (space->flag & 0x80000000) {
    }
    if (space->flag & 0x4000000) {
    }
    if (space->flag & 0x2000000) {
    }
    if (space->flag & 0x180000) {
        node->shop = 1;
    }
    if (space->flag & 0x48000000) {
        node->boo = 1;
    }
    if (space->flag & 0x20000000) {
        node->pipe = 1;
    }
    if (space->flag & 0x10000000) {
        node->lottery = 1;
    }
    switch (space->type) {
        case 8:
            node->star = 1;
            return FALSE;
        case 10:
            return FALSE;
        case 0:
            return FALSE;
    }
    return TRUE;
}

static inline void PushCandidate(PathNode *node) {
    if (numCandidates < 16) {
        candidateNodes[numCandidates] = node;
        numCandidates++;
    }
}

static inline PathNode *PopCandidate(void) {
    PathNode *node;

    numCandidates--;
    if (numCandidates < 0) {
        return NULL;
    } else {
        node = candidateNodes[numCandidates];
        candidateNodes[numCandidates] = NULL;
        return node;
    }
}

static inline PathNode *CreateNode(s16 start, s16 len) {
    PathNode *node;
    s32 i;

    node = pathNodeData;
    for (i = 0; i < 16; i++, node++) {
        if (node->used == 0) {
            break;
        }
    }
    if (i == 16) {
        return NULL;
    } else {
        node->used = 1;
        node->start = start;
        node->max_len = len;
        childNodeCnt++;
        return node;
    }
}

static inline void PopulateCandidates(s16 start, s16 len) {
    PathNode *node;
    s32 num_paths;
    s32 lookahead;
    s32 i;
    PathNode *new_node;

    memset(pathNodeData, 0, sizeof(pathNodeData));
    memset(candidateNodes, 0, sizeof(candidateNodes));
    numCandidates = 0;
    childNodeCnt = 0;
    new_node = CreateNode(start, len);
    PushCandidate(new_node);
    num_paths = 1;
    lookahead = len;
    while (1) {
        if (num_paths <= 0) {
            break;
        }
        node = PopCandidate();
        if (!node) {
            break;
        }
        num_paths--;
        lookahead = InitPathNode(node);
        if (lookahead != 0) {
            if (node->num_links <= 1) {
                break;
            }
            for (i = 0; i < node->num_links; num_paths++, i++) {
                new_node = CreateNode(node->links[i], lookahead);
                if (!new_node) {
                    break;
                }
                PushCandidate(new_node);
            }
        }
    }
}

s16 BoardComPathShortcutLenGet(s16 space, u32 type, s32 block_pipe) {
    s16 len_tbl[10];
    s16 node_tbl[10];
    PathNode *node_link;
    PathNode *node;
    s16 node_idx;
    s16 node_start_idx;
    s16 node_idx_link;
    s16 num_nodes;
    s16 len;
    s16 i;
    s32 search_child;

    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        return 0;
    }
    PopulateCandidates(space, 30);
    memset(startPathSpaceSearch, 0, sizeof(startPathSpaceSearch));
    memset(len_tbl, 0, sizeof(len_tbl));
    memset(candidateNodes, 0, sizeof(candidateNodes));
    numCandidates = 0;
    node = SearchPathNodeSpace(space);
    node_start_idx = NODE_INDEX(node);
    PushCandidate(node);
    len = 0;
    num_nodes = 0;
    startPathSpaceSearch[node_start_idx] = len;
    search_child = 0;
    while (1) {
        node = PopCandidate();
        node_idx = NODE_INDEX(node);
        if (node_idx == -1) {
            if (num_nodes != 0) {
                break;
            }
        } else {
            search_child = 0;
            len = startPathSpaceSearch[node_idx];
            for (i = 0; i < node->num_children; i++) {
                if (block_pipe == 0 && (BoardSpaceFlagGet(0, node->children[i]) & 0x20000000)) {
                    break;
                }
                if (type == BoardSpaceTypeGet(0, node->children[i])) {
                    len_tbl[num_nodes] = len;
                    node_tbl[num_nodes] = node_idx;
                    if (++num_nodes < 10) {
                        search_child = 1;
                        break;
                    } else {
                        goto done;
                    }
                }
                if (len++ >= 30) {
                    search_child = 1;
                    break;
                }
            }
            if (search_child == 0) {
                for (i = 0; i < node->num_links; i++) {
                    node_link = SearchPathNodeSpace(node->links[i]);
                    node_idx_link = NODE_INDEX(node_link);
                    if (node_idx_link != -1 && node_idx_link >= 0 && node_idx_link < 16) {
                        startPathSpaceSearch[node_idx_link] = len;
                        PushCandidate(node_link);
                    }
                }
            }
            continue;
        }
        return 0;
    }
done:
    len = 10000;
    for (i = 0; i < 10; i++) {
        if (len > len_tbl[i] && len_tbl[i] != 0) {
            len = len_tbl[i];
        }
    }
    return len;
}

s16 BoardComPathBestGet(s16 space) {
    PathNode *link_node;
    PathNode *node;
    s32 i;

    PopulateCandidates(space, 30);
    node = SearchPathNodeSpace(space);
    if (node->star != 0) {
        return -1;
    }
    if (node->num_links <= 1) {
        return -1;
    }
    for (i = 0; i < node->num_links; i++) {
        link_node = SearchPathNodeSpace(node->links[i]);
        if (link_node && CheckPath(link_node)) {
            return node->links[i];
        }
    }
    return -1;
}

s16 BoardComPathLenGet(s16 space, s16 space_other) {
    PathNode *node;
    s16 link_node_idx;
    s16 len;
    s16 sp16;
    s16 node_idx;
    s16 node_start_idx;
    s16 i;
    s32 search_child;
    PathNode *link_node;

    PopulateCandidates(space, 30);
    memset(startPathSpace, 0, sizeof(startPathSpace));
    memset(candidateNodes, 0, sizeof(candidateNodes));
    numCandidates = 0;
    node = SearchPathNodeSpace(space);
    node_start_idx = NODE_INDEX(node);
    PushCandidate(node);
    len = 0;
    sp16 = 0;
    startPathSpace[node_start_idx] = len;
    search_child = 0;
    while (1) {
        node = PopCandidate();
        node_idx = NODE_INDEX(node);
        if (node_idx == -1) {
            if (sp16 != 0) {
                break;
            }
        } else {
            search_child = 0;
            len = startPathSpace[node_idx];
            for (i = 0; i < node->num_children; i++) {
                if (BoardSpaceFlagGet(0, node->children[i]) & 0x20000000) {
                    break;
                }
                if (node->children[i] == space_other) {
                    goto done;
                }
                if (len++ >= 30) {
                    search_child = 1;
                    break;
                }
            }
            if (search_child == 0) {
                for (i = 0; i < node->num_links; i++) {
                    link_node = SearchPathNodeSpace(node->links[i]);
                    link_node_idx = NODE_INDEX(link_node);
                    if (link_node_idx != -1 && link_node_idx >= 0 && link_node_idx < 16) {
                        startPathSpace[link_node_idx] = len;
                        PushCandidate(link_node);
                    }
                }
            }
            continue;
        }
        return 0;
    }
done:
    return len;
}

static BOOL CheckPath(PathNode *node) {
    s32 i;
    PathNode *link;

    if (node->star != 0) {
        return TRUE;
    }
    if (node->num_links <= 1) {
        return FALSE;
    }
    for (i = 0; i < node->num_links; i++) {
        link = SearchPathNodeSpace(node->links[i]);
        if (link && CheckPath(link)) {
            return TRUE;
        }
    }
    return FALSE;
}

s16 BoardComPathBestGetFlag(s16 space, u32 flag, s16 len) {
    PathNode *node;
    PathNode *node_link;
    s32 i;

    PopulateCandidates(space, len);
    node = SearchPathNodeSpace(space);
    if (flag & 0x180000) {
        if (node->star != 0) {
            return -1;
        }
    } else if (flag & 0x08000000) {
        if (node->boo != 0) {
            return -1;
        }
    } else if (flag & 0x10000000) {
        if (node->lottery != 0) {
            return -1;
        }
    }
    if (node->num_links <= 1) {
        return -1;
    }
    for (i = 0; i < node->num_links; i++) {
        node_link = SearchPathNodeSpace(node->links[i]);
        if (node_link && CheckPathFlag(node_link, flag)) {
            return node->links[i];
        }
    }
    return -1;
}

static BOOL CheckPathFlag(PathNode *node, u32 flag) {
    s32 i;
    PathNode *link_node;

    if (flag & 0x180000) {
        if (node->star != 0) {
            return TRUE;
        }
    } else if (flag & 0x08000000) {
        if (node->boo != 0) {
            return TRUE;
        }
    } else if (flag & 0x10000000) {
        if (node->lottery != 0) {
            return TRUE;
        }
    }
    if (node->num_links <= 1) {
        return FALSE;
    }
    for (i = 0; i < node->num_links; i++) {
        link_node = SearchPathNodeSpace(node->links[i]);
        if (link_node && CheckPathFlag(link_node, flag)) {
            return TRUE;
        }
    }
    return FALSE;
}
