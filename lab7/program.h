#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ��������������� ��������� � ���� // TO(int)(void* p) == *(int*)(void* p) */
#define TO(T) *(T*)

/* ��� ������ bool */
#define bool int
#define true 1
#define false 0

/* ������� ������������� ����� */
#define MAXINT 1000000000
#define MAXLL 1000000000000000000
#define INTBOUNDS -MAXINT, MAXINT
#define LLBOUNDS -MAXLL, MAXLL

/* ������� �������� � ��������� */
#define min(x,y) (((x) < (y)) ? (x) : (y))
#define max(x,y) (((x) > (y)) ? (x) : (y))

/* ���� ��������� ����������� ������ */
#define ESC 27
#define SPACE 32
#define ENTER 13
#define TAB 9

/* ����-������� */
void TestFunction(void); 

/* ������� ����������� ���������� ��������� */
void FatalError(const char* message);

/* ��������� ������ */
void* Malloc(long long ByteCount); /* ��������� ������ � ��������� */
void MallocCheck(void* ptr); /* �������� �� �������� ��������� ������ */

/* ���������� */
void swap(void* a, void* b, int size); /* ����� ������� ���� ��������� ������� size */
void sort(void* begin, void* end, int sizeof_element, bool (*comp) (void* a, void* b)); /* ���������� */

/* ������ */
typedef struct Vector Vector;
struct Vector {
    int elemsize;
    int size;
    void* begin;
    int alloc;
    bool (*comp) (void* a, void* b);
};

Vector* VectorNew(int sizeof_element); /* ������������ ������ � ���������� ��������� �� ���� */
void VectorDelete(Vector* that); /* ���������� ������� */
void VectorClear(Vector* that); /* ������� ������ */
void VectorAddElem(Vector* that, void* what); /* ��������� � ����� ������� ������� ���� ����������� */
void VectorDelElem(Vector* that, int index); /* ������� ������� ������� � ��������� �������� */
int VectorSize(Vector* that); /* ���������� ���������� ��������� ������� */
void* VectorBegin(Vector* that); /* ���������� ��������� �� ������ ������� */
void* VectorGetElem(Vector* that, int index); /* ���������� ��������� �� ������� � ��������� �������� // ����������� TO(type) */
void VectorSetElem(Vector* that, int index, void* what); /* �������� ������� � ��������� �������� ���� ����������� */
int VectorFindElem(Vector* that, void* what); /* ���������� ������ ������� ��������� �������� ��� -1 */
int VectorFindLastElem(Vector* that, void* what); /* ���������� ������ ���������� ��������� �������� ��� -1 */
bool VectorContainElem(Vector* that, void* what); /* ���������� ������������� ��������� �������� */
void* VectorGetComp(Vector* that); /* ���������� ���������� ������� */
void VectorSetComp(Vector* that, bool (*comp) (void* a, void* b)); /* ������������� ���������� ������� */
void VectorSort(Vector* that); /* ��������� ������ */
void VectorSortComp(Vector* that, bool (*comp) (void* a, void* b)); /* ��������� ������ � �������������� ����������� */
void VectorResize(Vector* that, int newsize); /* �������� ���������� ��������� ������� */
void VectorRealloc(Vector* that, int newalloc); /* �������� ���������� ������, ���������� ��� ������� */
/* ������ */

/* ������ */
typedef Vector String;
String* StringNew(void); /* ������������ ������ � ���������� ��������� �� �� */
void StringDelete(String* that); /* ���������� ������ */
void StringClear(String* that); /* ������� ������ */
void StringAddElem(String* that, char what); /* ��������� � ����� ������ ������ */
/*UPD*/void StringPutElem(String* that, int index, char what); /* ��������� ������ � ����� � ��������� �������� */
void StringDelElem(String* that, int index); /* ������� ������ � ��������� �������� */
char* StringBegin(String* that); /* ���������� ��������� �� ������ ������ */
int StringSize(String* that); /* ���������� ����� ������ */
char StringGetElem(String* that, int index); /* ���������� ������ ������ � ��������� �������� */
void StringSetElem(String* that, int index, char what); /* �������� ������ ������ � ��������� �������� */
int StringFindElem(String* that, char what); /* ���������� ������ ������� ��������� ������� ��� -1 */
int StringFindLastElem(String* that, char what); /* ���������� ������ ���������� ��������� ������� ��� -1 */
bool StringContainElem(String* that, char what); /* ���������� ������������� ��������� ������� */

void StringRead(String* that, char until, FILE* from); /* ������ ������ ����� ����� ���������, ����������� ���������, �������� ��� until-�������� */
void StringReadLn(String* that, FILE* from); /* ������ ������ ������ � ��������� ������ �� �������� */
void StringIgnore(FILE* from); /* ��������� ������ ������ �� ��������� ������ */

bool StringToInt(char* from, long long* towhat, long long MinBound, long long MaxBound); /* �������� ������������� ������ � ����� ����� � �������� [MinBound, MaxBound] */
bool StringToFloat(char* from, double* towhat); /* �������� ������������� ������ � ������������ ����� */

long long StringReadInt(FILE* from, long long MinBound, long long MaxBound); /* ����������� ����� ����� � �������� [MinBound, MaxBound] */
double StringReadFloat(FILE* from); /* ����������� ������������ ����� */
/* ������ */

/* ���������� */
double absf(double x); /* ���������� ������ ������������� ����� */
long long fact_int(int x); /* ���������� ������������� ��������� ����� x */
double fact_float(int x); /* ���������� ������������ ��������� ����� x */
/* ���������� */

/* ��������� ������ */
bool OperLess(void* a, void* b, bool (*cmp)(void*, void*));
bool OperEqual(void* a, void* b, bool (*cmp)(void*, void*));
bool OperGreat(void* a, void* b, bool (*cmp)(void*, void*));

bool CmpInt(void* a, void* b);
bool CmpDouble(void* a, void* b);
bool CmpChar(void* a, void* b);
bool CmpCharArray(void* a, void* b);
/* ��������� ������ */

/* AA-Tree */
typedef struct TreeVertex TreeVertex;
struct TreeVertex {
    void* key;
    void* value;
    int level;
    TreeVertex* left;
    TreeVertex* right;
};

typedef struct Tree Tree;
struct Tree {
    int keysize;
    int valuesize;
    int size;
    bool (*comp) (void* a, void* b);
    void (*nuller) (void* a);
    TreeVertex* root;
};

Tree* TreeNew(int sizeof_key, int sizeof_value, bool (*key_comparator) (void* a, void* b), void (*value_nullator) (void* a));
void TreeClear(Tree* that);
void TreeDelete(Tree* that);
void TreeErase(Tree* that, void* index);
void TreeInsert(Tree* that, void* index);
void* TreeGetElem(Tree* that, void* index);

TreeVertex* TreeBegin(Tree* that);
TreeVertex* TreeLast(Tree* that);
TreeVertex* TreeEnd(Tree* that);
TreeVertex* TreeNext(Tree* that, TreeVertex* it);
TreeVertex* TreePrev(Tree* that, TreeVertex* it);
TreeVertex* TreeFind(Tree* that, void* index);

void NullInt(void* a);
/* AA-Tree */

/* Set */
typedef Tree Set;

Set* SetNew(int sizeof_element, bool (*comparator) (void* a, void* b));
void SetClear(Set* that) ;
void SetDelete(Set* that);
void SetAddElem(Set* that, void* what);
void SetDelElem(Set* that, void* what);
bool SetContainElem(Set* that, void* what);
int SetSize(Set* that);
/* Set */

#endif