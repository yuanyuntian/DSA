//
//  main.c
//  HashTable
//
//  Created by Fei Yuan on 2022/2/21.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define BUCKETCOUNT 20

struct HashNode {
    const char *key;
    char *val;
    struct HashNode * next;
};

typedef struct HashNode Node;

struct HashTable{
    Node bucket[BUCKETCOUNT];
};

typedef struct HashTable table;

void initHashTable(table * t) {
    if (t == NULL) {
        return;
    }
    for (int i = 0 ; i < BUCKETCOUNT; i ++) {
        t->bucket[i].key = NULL;
        t->bucket[i].val = NULL;
        t->bucket[i].next = NULL;
    }
}

void freeHashTable(table * t) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < BUCKETCOUNT; i++) {
        Node * e = &(t->bucket[i]);
        while (e->next != NULL) {
            Node * p = e->next;
            e->next = p->next;
            free(p->key);
            free(p->val);
            free(p);
        }
    }
}

int keyToIndex(const char * key) {
    if (key == NULL) {
        return -1;
    }
    int len = (int)strlen(key);
    int index = (int)key[0];
    for (int i = 0; i < len; i ++) {
        index *= 1103515245 + (int)key[i];
    }
    index >>= 27;
    index &= (BUCKETCOUNT - 1);
    return index;
}

char * strDup(const char * str) {
    if (str == NULL) {
        return NULL;
    }
    
    int len = strlen(str);
    char * ret = (char *)malloc(len + 1);
    if (ret != NULL) {
        memcpy(ret, str, len);
        ret[len] = '\n';
    }
    return ret;
}

int insertNode(table * t, const char *key, const char * val) {
    Node * e, *ep;
    if (t == NULL || key == NULL || val == NULL) {
        return -1;
    }
    
    int index = keyToIndex(key);
    if (t->bucket[index].key == NULL) {
        t->bucket[index].key = strdup(key);
        t->bucket[index].val = strdup(val);
    }else{
        e = ep = &(t->bucket[index]);
        while (e != NULL) {
            if (0 == strcmp(e->key, key)) {
                int vlen1 = strlen(val);
                int vlen2 = strlen(e->val);
                if (vlen1 > vlen2) {
                    free(e->val);
                    e->val = (char*)malloc(vlen1 + 1);
                }
                memcpy(e->val, val, vlen1 + 1);
                return index;
            }
            ep = e;
            e = e->next;
        }
        e = (Node *)malloc(sizeof(Node));
        e->key = strdup(key);
        e->val = strdup(val);
        e->next = NULL;
        ep->next = e;

    }
    return 0;
}

const char * findValueBykey(const table * t, const char * key) {
    if (t == NULL || key == NULL) {
        return NULL;
    }
    
    int index = keyToIndex(key);
    const Node * e = &(t->bucket[index]);
    if (e->key == NULL) {
        return NULL;
    }
    while (e != NULL) {
        if (0 == strcmp(key, e->key)) {
            return e->val;
        }
        e = e->next;
    }
    return NULL;
}

Node * removeNode(table * t, char * key) {
    if (t == NULL || key == NULL) {
        return NULL;
    }
    int index = keyToIndex(key);
    Node * ep,*e;
    e = &(t->bucket[index]);
    while (e != NULL) {
        if (0 == strcmp(key, e->key)) {
            //first bucket
            if (e == &(t->bucket[index])) {
                //如果这个桶有两个或以上元素
               //交换第一个和第二个，然后移除第二个
                ep = e->next;
                if (ep != NULL) {
                    Node tmp = *e;//做浅拷贝交换
                    *e = *ep;
                    *ep = tmp;
                    ep->next = NULL;
                }else{
                    ep = (Node *)malloc(sizeof(Node));
                    *ep = *e;//拷贝值
                    e->key = e->val = NULL;
                    e->next = NULL;
                }
            }else{
                ep  = &(t->bucket[index]);
                while (ep->next != e) {
                    ep = ep->next;
                }
                
                ep ->next = e->next;
                e->next = NULL;
                ep = e;
            }
            return ep;
        }
        e = e ->next;
    }
    return NULL;
}

void printTable(table *t) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < BUCKETCOUNT; i++) {
        printf("\nbucket[%d]:\n" , i);
        Node * e = &(t->bucket[i]);
        while (e->key != NULL) {
            printf("\t%s\t=\t%s\n" , e->key , e->val);
            if (e->next == NULL) {
                break;
            }
            e = e->next;
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    table t;
    initHashTable(&t);
    insertNode(&t , "电脑型号" , "华硕 X550JK 笔记本电脑");
    insertNode(&t , "操作系统" , "Windows 8.1 64位 (DirectX 11)");
    insertNode(&t , "处理器" , "英特尔 Core i7 - 4710HQ @ 2.50GHz 四核");
    insertNode(&t , "主板" , "华硕 X550JK(英特尔 Haswell)");
    insertNode(&t , "内存" , "4 GB(Hynix / Hyundai)");
    
    Node * p = removeNode(&t, "内存");

    printTable(&t);
    return 0;
}
