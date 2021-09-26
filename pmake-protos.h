/* this file was generated from pmake.nw, please do not edit
 */

#ifndef MAKE_NATIVE
#undef __attribute__
#define __attribute__(x)
#endif

/* arch.c */
ReturnStatus Arch_ParseArchive(char **, Lst, GNode *);
void Arch_Touch(GNode *);
void Arch_TouchLib(GNode *);
time_t Arch_MTime(GNode *);
time_t Arch_MemMTime(GNode *);
void Arch_FindLib(GNode *, Lst);
Boolean Arch_LibOODate(GNode *);
void Arch_Init(void);
void Arch_End(void);
int Arch_IsLib(GNode *);
/* buf.c */
void Buf_OvAddByte(Buffer, int);
void Buf_AddBytes(Buffer, int, const Byte *);
Byte *Buf_GetAll(Buffer, int *);
void Buf_Discard(Buffer, int);
int Buf_Size(Buffer);
Buffer Buf_Init(int);
void Buf_Destroy(Buffer, Boolean);
void Buf_ReplaceLastByte(Buffer, int);
/* compat.c */
int CompatRunCommand(ClientData, ClientData);
void Compat_Run(Lst);
int Compat_Make(ClientData, ClientData);
/* cond.c */
int Cond_EvalExpression(int, char *, Boolean *, int);
int Cond_Eval(char *);
void Cond_End(void);
/* dir.c */
void Dir_Init(const char *);
void Dir_InitCur(const char *);
void Dir_InitDot(void);
void Dir_End(void);
void Dir_SetPATH(void);
Boolean Dir_HasWildcards(char *);
void Dir_Expand(const char *, Lst, Lst);
char *Dir_FindFile(const char *, Lst);
int Dir_FindHereOrAbove(char *, char *, char *, int);
int Dir_MTime(GNode *);
Path *Dir_AddDir(Lst, const char *);
char *Dir_MakeFlags(const char *, Lst);
void Dir_ClearPath(Lst);
void Dir_Concat(Lst, Lst);
void Dir_PrintDirectories(void);
void Dir_PrintPath(Lst);
void Dir_Destroy(ClientData);
ClientData Dir_CopyDir(ClientData);
/* for.c */
int For_Eval(char *);
void For_Run(int);
/* hash.c */
void Hash_InitTable(Hash_Table *, int);
void Hash_DeleteTable(Hash_Table *);
Hash_Entry *Hash_FindEntry(Hash_Table *, const char *);
Hash_Entry *Hash_CreateEntry(Hash_Table *, const char *, Boolean *);
void Hash_DeleteEntry(Hash_Table *, Hash_Entry *);
Hash_Entry *Hash_EnumFirst(Hash_Table *, Hash_Search *);
Hash_Entry *Hash_EnumNext(Hash_Search *);
/* job.c */
void Shell_Init(void);
void Job_Touch(GNode *, Boolean);
Boolean Job_CheckCommands(GNode *, void (*abortProc )(const char *, ...));
void Job_CatchChildren(Boolean);
void Job_CatchOutput(void);
void Job_Make(GNode *);
void Job_Init(int, int);
Boolean Job_Full(void);
Boolean Job_Empty(void);
ReturnStatus Job_ParseShell(char *);
int Job_Finish(void);
void Job_End(void);
void Job_Wait(void);
void Job_AbortAll(void);
void JobFlagForMigration(int);
void Job_TokenReturn(void);
void Job_TokenFlush(void);
Boolean Job_TokenWithdraw(void);
void Job_ServerStart(int);
/* main.c */
void Main_ExportMAKEFLAGS(Boolean);
Boolean Main_SetObjdir(const char *);
char * Check_Cwd_Cmd(const char *);
void Check_Cwd(const char **);
void PrintOnError(const char *);
void Main_ParseArgLine(char *);
int main(int, char **);
char *Cmd_Exec(const char *, const char **);
void Error(const char *, ...) __attribute__((__format__(__printf__, 1, 2)));
void Fatal(const char *, ...)
    __attribute__((__format__(__printf__, 1, 2),__noreturn__));
void Punt(const char *, ...)
    __attribute__((__format__(__printf__, 1, 2),__noreturn__));
void DieHorribly(void) __attribute__((__noreturn__));
int PrintAddr(ClientData, ClientData);
void Finish(int);
char *estrdup(const char *);
void *emalloc(size_t);
void *erealloc(void *, size_t);
void enomem(void);
int eunlink(const char *);
void execError(const char *, const char *);
/* make.c */
int Make_TimeStamp(GNode *, GNode *);
Boolean Make_OODate(GNode *);
Lst Make_ExpandUse(Lst);
time_t Make_Recheck(GNode *);
void Make_HandleUse(GNode *, GNode *);
void Make_Update(GNode *);
void Make_DoAllVar(GNode *);
Boolean Make_Run(Lst);
/* parse.c */
void Parse_Error(int, const char *, ...)
     __attribute__((__format__(__printf__, 2, 3)));
Boolean Parse_AnyExport(void);
Boolean Parse_IsVar(char *);
void Parse_DoVar(char *, GNode *);
void Parse_AddIncludeDir(char *);
void Parse_File(const char *, FILE *);
void Parse_Init(void);
void Parse_End(void);
void Parse_FromString(char *, int);
Lst Parse_MainName(void);
/* str.c */
char *str_concat(const char *, const char *, int);
char **brk_string(const char *, int *, Boolean, char **);
char *Str_FindSubstring(const char *, const char *);
int Str_Match(const char *, const char *);
char *Str_SYSVMatch(const char *, const char *, int *len);
void Str_SYSVSubst(Buffer, char *, char *, int);
/* suff.c */
void Suff_ClearSuffixes(void);
Boolean Suff_IsTransform(char *);
GNode *Suff_AddTransform(char *);
int Suff_EndTransform(ClientData, ClientData);
void Suff_AddSuffix(char *, GNode **);
Lst Suff_GetPath(char *);
void Suff_DoPaths(void);
void Suff_AddInclude(char *);
void Suff_AddLib(char *);
void Suff_FindDeps(GNode *);
Lst Suff_FindPath(GNode *);
void Suff_SetNull(char *);
void Suff_Init(void);
void Suff_End(void);
void Suff_PrintAll(void);
/* targ.c */
void Targ_Init(void);
void Targ_End(void);
Lst Targ_List(void);
GNode *Targ_NewGN(const char *);
GNode *Targ_FindNode(const char *, int);
Lst Targ_FindList(Lst, int);
Boolean Targ_Ignore(GNode *);
Boolean Targ_Silent(GNode *);
Boolean Targ_Precious(GNode *);
void Targ_SetMain(GNode *);
int Targ_PrintCmd(ClientData, ClientData);
char *Targ_FmtTime(time_t);
void Targ_PrintType(int);
void Targ_PrintGraph(int);
void Targ_Propagate(void);
/* trace.c */
void Trace_Init(const char *);
void Trace_Log(TrEvent, Job *);
void Trace_End(void);
/* var.c */
void Var_Delete(const char *, GNode *);
void Var_Set(const char *, const char *, GNode *, int);
void Var_Append(const char *, const char *, GNode *);
Boolean Var_Exists(const char *, GNode *);
char *Var_Value(const char *, GNode *, char **);
char *Var_Parse(const char *, GNode *, Boolean, int *, Boolean *);
char *Var_Subst(const char *, const char *, GNode *, Boolean);
char *Var_GetTail(const char *);
char *Var_GetHead(const char *);
void Var_Init(void);
void Var_End(void);
void Var_Dump(GNode *);
