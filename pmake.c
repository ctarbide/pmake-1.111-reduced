/* this file was generated from pmake.nw, please do not edit
 */

#include <sys/types.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <sys/stat.h>

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include <ar.h>
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <utime.h>
#include <signal.h>
#include <dirent.h>
#include <unistd.h>

#include "sprite.h"
#include "config.h"

#ifdef MAKE_NATIVE
#include <sys/utsname.h>
#endif
#include <sys/wait.h>

#ifndef USE_SELECT
#include <poll.h>
#endif

#ifdef USE_IOVEC
#include <sys/uio.h>
#endif

#include "lst.h"

/* begin hash.h */
/*	$NetBSD: hash.h,v 1.8 2003/08/07 11:14:51 agc Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)hash.h	8.1 (Berkeley) 6/6/93
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)hash.h	8.1 (Berkeley) 6/6/93
 */

/* hash.h --
 *
 * 	This file contains definitions used by the hash module,
 * 	which maintains hash tables.
 */

#ifndef	_HASH_H_
#define	_HASH_H_

/*
 * The following defines one entry in the hash table.
 */

typedef struct Hash_Entry {
    struct Hash_Entry *next;		/* Used to link together all the
					 * entries associated with the same
					 * bucket. */
    ClientData	      clientData;	/* Arbitrary piece of data associated
					 * with key. */
    unsigned	      namehash;		/* hash value of key */
    char	      name[1];		/* key string */
} Hash_Entry;

typedef struct Hash_Table {
    struct Hash_Entry **bucketPtr;/* Pointers to Hash_Entry, one
				 * for each bucket in the table. */
    int 	size;		/* Actual size of array. */
    int 	numEntries;	/* Number of entries in the table. */
    int 	mask;		/* Used to select bits for hashing. */
} Hash_Table;

/*
 * The following structure is used by the searching routines
 * to record where we are in the search.
 */

typedef struct Hash_Search {
    Hash_Table  *tablePtr;	/* Table being searched. */
    int 	nextIndex;	/* Next bucket to check (after current). */
    Hash_Entry 	*hashEntryPtr;	/* Next entry to check in current bucket. */
} Hash_Search;

/*
 * Macros.
 */

/*
 * ClientData Hash_GetValue(h)
 *     Hash_Entry *h;
 */

#define Hash_GetValue(h) ((h)->clientData)

/*
 * Hash_SetValue(h, val);
 *     Hash_Entry *h;
 *     char *val;
 */

#define Hash_SetValue(h, val) ((h)->clientData = (ClientData) (val))

/*
 * Hash_Size(n) returns the number of words in an object of n bytes
 */

#define	Hash_Size(n)	(((n) + sizeof (int) - 1) / sizeof (int))

#endif /* _HASH_H_ */
/* end hash.h */

/* begin buf.h */
/*	$NetBSD: buf.h,v 1.10 2003/08/07 11:14:48 agc Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)buf.h	8.1 (Berkeley) 6/6/93
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)buf.h	8.1 (Berkeley) 6/6/93
 */

/*-
 * buf.h --
 *	Header for users of the buf library.
 */

#ifndef _BUF_H
#define _BUF_H

/* <<buf.h includes>> */

typedef char Byte;

typedef struct Buffer {
    int	    size; 	/* Current size of the buffer */
    int     left;	/* Space left (== size - (inPtr - buffer)) */
    Byte    *buffer;	/* The buffer itself */
    Byte    *inPtr;	/* Place to write to */
    Byte    *outPtr;	/* Place to read from */
} *Buffer;

/* Buf_AddByte adds a single byte to a buffer. */
#define	Buf_AddByte(bp, byte) \
	(void) (--(bp)->left <= 0 ? Buf_OvAddByte(bp, byte), 1 : \
		(*(bp)->inPtr++ = (byte), *(bp)->inPtr = 0), 1)

#define BUF_ERROR 256

#endif /* _BUF_H */
/* end buf.h */

/* begin dir.h */
/*	$NetBSD: dir.h,v 1.11 2004/02/03 19:25:29 chuck Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)dir.h	8.1 (Berkeley) 6/6/93
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)dir.h	8.1 (Berkeley) 6/6/93
 */

/* dir.h --
 */

#ifndef	_DIR_H_
#define	_DIR_H_

typedef struct Path {
    char         *name;	    	/* Name of directory */
    int	    	  refCount; 	/* Number of paths with this directory */
    int		  hits;	    	/* the number of times a file in this
				 * directory has been found */
    Hash_Table    files;    	/* Hash table of files in directory */
} Path;

#endif /* _DIR_H_ */
/* end dir.h */

/* begin make.h */
/*	$NetBSd: make.h,v 1.53 2005/05/01 01:25:36 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)make.h	8.3 (Berkeley) 6/13/95
 */

/*
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)make.h	8.3 (Berkeley) 6/13/95
 */

/*-
 * make.h --
 *	The global definitions for pmake
 */

#ifndef _MAKE_H_
#define _MAKE_H_

/* <<make.h includes>> */

#ifdef BSD4_4
# include <sys/cdefs.h>
#else
# ifndef __GNUC__
#  ifndef __inline
#   define __inline
#  endif
# endif
#endif

#if !defined(__GNUC_PREREQ__)
#if defined(__GNUC__)
#define	__GNUC_PREREQ__(x, y)						\
	((__GNUC__ == (x) && __GNUC_MINOR__ >= (y)) ||			\
	 (__GNUC__ > (x)))
#else /* defined(__GNUC__) */
#define	__GNUC_PREREQ__(x, y)	0
#endif /* defined(__GNUC__) */
#endif /* !defined(__GNUC_PREREQ__) */

#if !defined(__unused)
#if __GNUC_PREREQ__(2, 7)
#define __unused        __attribute__((__unused__))
#else
#define __unused        /* delete */
#endif
#endif

/*-
 * The structure for an individual graph node. Each node has several
 * pieces of data associated with it.
 *	1) the name of the target it describes
 *	2) the location of the target file in the file system.
 *	3) the type of operator used to define its sources (qv. parse.c)
 *	4) whether it is involved in this invocation of make
 *	5) whether the target has been remade
 *	6) whether any of its children has been remade
 *	7) the number of its children that are, as yet, unmade
 *	8) its modification time
 *	9) the modification time of its youngest child (qv. make.c)
 *	10) a list of nodes for which this is a source
 *	11) a list of nodes on which this depends
 *	12) a list of nodes that depend on this, as gleaned from the
 *	    transformation rules.
 *	13) a list of nodes of the same name created by the :: operator
 *	14) a list of nodes that must be made (if they're made) before
 *	    this node can be, but that do no enter into the datedness of
 *	    this node.
 *	15) a list of nodes that must be made (if they're made) after
 *	    this node is, but that do not depend on this node, in the
 *	    normal sense.
 *	16) a Lst of ``local'' variables that are specific to this target
 *	   and this target only (qv. var.c [$@ $< $?, etc.])
 *	17) a Lst of strings that are commands to be given to a shell
 *	   to create this target.
 */
typedef struct GNode {
    char            *name;     	/* The target's name */
    char            *uname;    	/* The unexpanded name of a .USE node */
    char    	    *path;     	/* The full pathname of the file */
    int             type;      	/* Its type (see the OP flags, below) */
    int		    order;	/* Its wait weight */

    int             flags;
#define REMAKE		0x1    	/* this target needs to be remade */
#define	CHILDMADE	0x2	/* children of this target were made */
#define FORCE		0x4	/* children don't exist, and we pretend made */
    enum {
	UNMADE, BEINGMADE, MADE, UPTODATE, ERROR, ABORTED,
	CYCLE, ENDCYCLE
    }	    	    made;    	/* Set to reflect the state of processing
				 * on this node:
				 *  UNMADE - Not examined yet
				 *  BEINGMADE - Target is already being made.
				 *  	Indicates a cycle in the graph. (compat
				 *  	mode only)
				 *  MADE - Was out-of-date and has been made
				 *  UPTODATE - Was already up-to-date
				 *  ERROR - An error occurred while it was being
				 *  	made (used only in compat mode)
				 *  ABORTED - The target was aborted due to
				 *  	an error making an inferior (compat).
				 *  CYCLE - Marked as potentially being part of
				 *  	a graph cycle. If we come back to a
				 *  	node marked this way, it is printed
				 *  	and 'made' is changed to ENDCYCLE.
				 *  ENDCYCLE - the cycle has been completely
				 *  	printed. Go back and unmark all its
				 *  	members.
				 */
    int             unmade;    	/* The number of unmade children */

    time_t          mtime;     	/* Its modification time */
    time_t     	    cmtime;    	/* The modification time of its youngest
				 * child */

    Lst     	    iParents;  	/* Links to parents for which this is an
				 * implied source, if any */
    Lst	    	    cohorts;  	/* Other nodes for the :: operator */
    Lst             parents;   	/* Nodes that depend on this one */
    Lst             children;  	/* Nodes on which this one depends */
    Lst	    	    successors;	/* Nodes that must be made after this one */
    Lst	    	    preds;  	/* Nodes that must be made before this one */
    int		    unmade_cohorts;/* # of unmade instances on the
				      cohorts list */
    struct GNode    *centurion;	/* Pointer to the first instance of a ::
				   node; only set when on a cohorts list */

    Hash_Table      context;	/* The local variables */
    Lst             commands;  	/* Creation commands */

    struct _Suff    *suffix;	/* Suffix for the node (determined by
				 * Suff_FindDeps and opaque to everyone
				 * but the Suff module) */
    char	    *fname;	/* filename where the GNode got defined */
    int		     lineno;	/* line number where the GNode got defined */
} GNode;

/*
 * Manifest constants
 */
#define NILGNODE	((GNode *) NIL)

/*
 * The OP_ constants are used when parsing a dependency line as a way of
 * communicating to other parts of the program the way in which a target
 * should be made. These constants are bitwise-OR'ed together and
 * placed in the 'type' field of each node. Any node that has
 * a 'type' field which satisfies the OP_NOP function was never never on
 * the lefthand side of an operator, though it may have been on the
 * righthand side...
 */
#define OP_DEPENDS	0x00000001  /* Execution of commands depends on
				     * kids (:) */
#define OP_FORCE	0x00000002  /* Always execute commands (!) */
#define OP_DOUBLEDEP	0x00000004  /* Execution of commands depends on kids
				     * per line (::) */
#define OP_OPMASK	(OP_DEPENDS|OP_FORCE|OP_DOUBLEDEP)

#define OP_OPTIONAL	0x00000008  /* Don't care if the target doesn't
				     * exist and can't be created */
#define OP_USE		0x00000010  /* Use associated commands for parents */
#define OP_EXEC	  	0x00000020  /* Target is never out of date, but always
				     * execute commands anyway. Its time
				     * doesn't matter, so it has none...sort
				     * of */
#define OP_IGNORE	0x00000040  /* Ignore errors when creating the node */
#define OP_PRECIOUS	0x00000080  /* Don't remove the target when
				     * interrupted */
#define OP_SILENT	0x00000100  /* Don't echo commands when executed */
#define OP_MAKE		0x00000200  /* Target is a recursive make so its
				     * commands should always be executed when
				     * it is out of date, regardless of the
				     * state of the -n or -t flags */
#define OP_JOIN 	0x00000400  /* Target is out-of-date only if any of its
				     * children was out-of-date */
#define	OP_MADE		0x00000800  /* Assume the children of the node have
				     * been already made */
#define OP_SPECIAL	0x00001000  /* Special .BEGIN, .END, .INTERRUPT */
#define	OP_USEBEFORE	0x00002000  /* Like .USE, only prepend commands */
#define OP_INVISIBLE	0x00004000  /* The node is invisible to its parents.
				     * I.e. it doesn't show up in the parents's
				     * local variables. */
#define OP_NOTMAIN	0x00008000  /* The node is exempt from normal 'main
				     * target' processing in parse.c */
#define OP_PHONY	0x00010000  /* Not a file target; run always */
#define OP_NOPATH	0x00020000  /* Don't search for file in the path */
/* Attributes applied by PMake */
#define OP_TRANSFORM	0x80000000  /* The node is a transformation rule */
#define OP_MEMBER 	0x40000000  /* Target is a member of an archive */
#define OP_LIB	  	0x20000000  /* Target is a library */
#define OP_ARCHV  	0x10000000  /* Target is an archive construct */
#define OP_HAS_COMMANDS	0x08000000  /* Target has all the commands it should.
				     * Used when parsing to catch multiple
				     * commands for a target */
/* #define OP_SAVE_CMDS	0x04000000 */  /* Saving commands on .END (Compat) */
#define OP_DEPS_FOUND	0x02000000  /* Already processed by Suff_FindDeps */
#define	OP_MARK		0x01000000  /* Node found while expanding .ALLSRC */

#define NoExecute(gn) ((gn->type & OP_MAKE) ? noRecursiveExecute : noExecute)
/*
 * OP_NOP will return TRUE if the node with the given type was not the
 * object of a dependency operator
 */
#define OP_NOP(t)	(((t) & OP_OPMASK) == 0x00000000)

#define OP_NOTARGET (OP_NOTMAIN|OP_USE|OP_EXEC|OP_TRANSFORM)

/*
 * The TARG_ constants are used when calling the Targ_FindNode and
 * Targ_FindList functions in targ.c. They simply tell the functions what to
 * do if the desired node(s) is (are) not found. If the TARG_CREATE constant
 * is given, a new, empty node will be created for the target, placed in the
 * table of all targets and its address returned. If TARG_NOCREATE is given,
 * a NIL pointer will be returned.
 */
#define TARG_CREATE	0x01	  /* create node if not found */
#define TARG_NOCREATE	0x00	  /* don't create it */

/*
 * There are several places where expandable buffers are used (parse.c and
 * var.c). This constant is merely the starting point for those buffers. If
 * lines tend to be much shorter than this, it would be best to reduce BSIZE.
 * If longer, it should be increased. Reducing it will cause more copying to
 * be done for longer lines, but will save space for shorter ones. In any
 * case, it ought to be a power of two simply because most storage allocation
 * schemes allocate in powers of two.
 */
#define MAKE_BSIZE		256	/* starting size for expandable buffers */

/*
 * These constants are all used by the Str_Concat function to decide how the
 * final string should look. If STR_ADDSPACE is given, a space will be
 * placed between the two strings. If STR_ADDSLASH is given, a '/' will
 * be used instead of a space. If neither is given, no intervening characters
 * will be placed between the two strings in the final output. If the
 * STR_DOFREE bit is set, the two input strings will be freed before
 * Str_Concat returns.
 */
#define STR_ADDSPACE	0x01	/* add a space when Str_Concat'ing */
#define STR_ADDSLASH	0x02	/* add a slash when Str_Concat'ing */

/*
 * Error levels for parsing. PARSE_FATAL means the process cannot continue
 * once the makefile has been parsed. PARSE_WARNING means it can. Passed
 * as the first argument to Parse_Error.
 */
#define PARSE_WARNING	2
#define PARSE_FATAL	1

/*
 * Values returned by Cond_Eval.
 */
#define COND_PARSE	0   	/* Parse the next lines */
#define COND_SKIP 	1   	/* Skip the next lines */
#define COND_INVALID	2   	/* Not a conditional statement */

/*
 * Definitions for the "local" variables. Used only for clarity.
 */
#define TARGET	  	  "@" 	/* Target of dependency */
#define OODATE	  	  "?" 	/* All out-of-date sources */
#define ALLSRC	  	  ">" 	/* All sources */
#define IMPSRC	  	  "<" 	/* Source implied by transformation */
#define PREFIX	  	  "*" 	/* Common prefix */
#define ARCHIVE	  	  "!" 	/* Archive in "archive(member)" syntax */
#define MEMBER	  	  "%" 	/* Member in "archive(member)" syntax */

#define FTARGET           "@F"  /* file part of TARGET */
#define DTARGET           "@D"  /* directory part of TARGET */
#define FIMPSRC           "<F"  /* file part of IMPSRC */
#define DIMPSRC           "<D"  /* directory part of IMPSRC */
#define FPREFIX           "*F"  /* file part of PREFIX */
#define DPREFIX           "*D"  /* directory part of PREFIX */

/*
 * Global Variables
 */
extern Lst  	create;	    	/* The list of target names specified on the
				 * command line. used to resolve #if
				 * make(...) statements */
extern Lst     	dirSearchPath; 	/* The list of directories to search when
				 * looking for targets */

extern Boolean	compatMake;	/* True if we are make compatible */
extern Boolean	ignoreErrors;  	/* True if should ignore all errors */
extern Boolean  beSilent;    	/* True if should print no commands */
extern Boolean  noExecute;    	/* True if should execute nothing */
extern Boolean  noRecursiveExecute;    	/* True if should execute nothing */
extern Boolean  allPrecious;   	/* True if every target is precious */
extern Boolean  keepgoing;    	/* True if should continue on unaffected
				 * portions of the graph when have an error
				 * in one portion */
extern Boolean 	touchFlag;    	/* TRUE if targets should just be 'touched'
				 * if out of date. Set by the -t flag */
extern Boolean  usePipes;    	/* TRUE if should capture the output of
				 * subshells by means of pipes. Otherwise it
				 * is routed to temporary files from which it
				 * is retrieved when the shell exits */
extern Boolean 	queryFlag;    	/* TRUE if we aren't supposed to really make
				 * anything, just see if the targets are out-
				 * of-date */

extern Boolean	checkEnvFirst;	/* TRUE if environment should be searched for
				 * variables before the global context */
extern Boolean	jobServer;	/* a jobServer already exists */

extern Boolean	parseWarnFatal;	/* TRUE if makefile parsing warnings are
				 * treated as errors */

extern Boolean	varNoExportEnv;	/* TRUE if we should not export variables
				 * set on the command line to the env. */

extern GNode    *DEFAULT;    	/* .DEFAULT rule */

extern GNode    *VAR_GLOBAL;   	/* Variables defined in a global context, e.g
				 * in the Makefile itself */
extern GNode    *VAR_CMD;    	/* Variables defined on the command line */
extern GNode	*VAR_FOR;	/* Iteration variables */
extern char    	var_Error[];   	/* Value returned by Var_Parse when an error
				 * is encountered. It actually points to
				 * an empty string, so naive callers needn't
				 * worry about it. */

extern time_t 	now;	    	/* The time at the start of this whole
				 * process */

extern Boolean	oldVars;    	/* Do old-style variable substitution */

extern Lst	sysIncPath;	/* The system include path. */
extern Lst	defIncPath;	/* The default include path. */

extern char	*progname;	/* The program name */

#define	MAKEFLAGS	".MAKEFLAGS"
#define	MAKEOVERRIDES	".MAKEOVERRIDES"

/*
 * debug control:
 *	There is one bit per module.  It is up to the module what debug
 *	information to print.
 */
extern int debug;
#define	DEBUG_ARCH	0x0001
#define	DEBUG_COND	0x0002
#define	DEBUG_DIR	0x0004
#define	DEBUG_GRAPH1	0x0008
#define	DEBUG_GRAPH2	0x0010
#define	DEBUG_JOB	0x0020
#define	DEBUG_MAKE	0x0040
#define	DEBUG_SUFF	0x0080
#define	DEBUG_TARG	0x0100
#define	DEBUG_VAR	0x0200
#define DEBUG_FOR	0x0400
#define DEBUG_SHELL	0x0800
#define DEBUG_ERROR	0x1000
#define	DEBUG_GRAPH3	0x10000
#define DEBUG_SCRIPT	0x20000

#define CONCAT(a,b)	a##b

#define	DEBUG(module)	(debug & CONCAT(DEBUG_,module))

#ifdef __GNUC__
union __unconst {
	const void *c;
	void *p;
};
#define UNCONST(ptr)	({union __unconst __d; __d.c = ptr, __d.p;})
#else
#define UNCONST(ptr)	(void *)(ptr)
#endif

#ifndef MIN
#define MIN(a, b) ((a < b) ? a : b)
#endif
#ifndef MAX
#define MAX(a, b) ((a > b) ? a : b)
#endif

#endif /* _MAKE_H_ */
/* end make.h */

/* begin job.h */
/*	$NetBSD: job.h,v 1.21 2003/12/20 00:18:22 jmc Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)job.h	8.1 (Berkeley) 6/6/93
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)job.h	8.1 (Berkeley) 6/6/93
 */

/*-
 * job.h --
 *	Definitions pertaining to the running of jobs in parallel mode.
 *	Exported from job.c for the use of remote-execution modules.
 */
#ifndef _JOB_H_
#define _JOB_H_

#define TMPPAT	"/tmp/makeXXXXXX"

#ifdef USE_SELECT
/*
 * Emulate poll() in terms of select().  This is not a complete
 * emulation but it is sufficient for make's purposes.
 */

#define poll emul_poll
#define pollfd emul_pollfd

struct emul_pollfd {
    int fd;
    short events;
    short revents;
};

#define	POLLIN		0x0001
#define	POLLOUT		0x0004

int
emul_poll(struct pollfd *fd, int nfd, int timeout);
#endif

/*
 * The POLL_MSEC constant determines the maximum number of milliseconds spent
 * in poll before coming out to see if a child has finished.
 */
#define POLL_MSEC	5000


/*-
 * Job Table definitions.
 *
 * Each job has several things associated with it:
 *	1) The process id of the child shell
 *	2) The graph node describing the target being made by this job
 *	3) A LstNode for the first command to be saved after the job
 *	   completes. This is NILLNODE if there was no "..." in the job's
 *	   commands.
 *	4) An FILE* for writing out the commands. This is only
 *	   used before the job is actually started.
 *	5) A union of things used for handling the shell's output. Different
 *	   parts of the union are used based on the value of the usePipes
 *	   flag. If it is true, the output is being caught via a pipe and
 *	   the descriptors of our pipe, an array in which output is line
 *	   buffered and the current position in that buffer are all
 *	   maintained for each job. If, on the other hand, usePipes is false,
 *	   the output is routed to a temporary file and all that is kept
 *	   is the name of the file and the descriptor open to the file.
 *	6) An identifier provided by and for the exclusive use of the
 *	   Rmt module.
 *	7) A word of flags which determine how the module handles errors,
 *	   echoing, etc. for the job
 *
 * The job "table" is kept as a linked Lst in 'jobs', with the number of
 * active jobs maintained in the 'nJobs' variable. At no time will this
 * exceed the value of 'maxJobs', initialized by the Job_Init function.
 *
 * When a job is finished, the Make_Update function is called on each of the
 * parents of the node which was just remade. This takes care of the upward
 * traversal of the dependency graph.
 */

#define JOB_BUFSIZE	1024
typedef struct Job {
    int       	pid;	    /* The child's process ID */
    GNode    	*node;      /* The target the child is making */
    LstNode 	tailCmds;   /* The node of the first command to be
			     * saved when the job has been run */
    FILE 	*cmdFILE;   /* When creating the shell script, this is
			     * where the commands go */
    int    	rmtID;     /* ID returned from Rmt module */
    short      	flags;	    /* Flags to control treatment of job */
#define	JOB_IGNERR	0x001	/* Ignore non-zero exits */
#define	JOB_SILENT	0x002	/* no output */
#define JOB_SPECIAL	0x004	/* Target is a special one. i.e. run it locally
				 * if we can't export it and maxLocal is 0 */
#define JOB_IGNDOTS	0x008  	/* Ignore "..." lines when processing
				 * commands */
#define JOB_REMOTE	0x010	/* Job is running remotely */
#define JOB_FIRST	0x020	/* Job is first job for the node */
#define JOB_REMIGRATE	0x040	/* Job needs to be remigrated */
#define JOB_RESTART	0x080	/* Job needs to be completely restarted */
#define JOB_RESUME	0x100	/* Job needs to be resumed b/c it stopped,
				 * for some reason */
#define JOB_CONTINUING	0x200	/* We are in the process of resuming this job.
				 * Used to avoid infinite recursion between
				 * JobFinish and JobRestart */
#define JOB_TRACED	0x400	/* we've sent 'set -x' */

    union {
	struct {
	    int	  	op_inPipe;	/* Input side of pipe associated
					 * with job's output channel */
	    struct pollfd *op_inPollfd;	/* pollfd associated with inPipe */
	    int   	op_outPipe;	/* Output side of pipe associated with
					 * job's output channel */
	    char  	op_outBuf[JOB_BUFSIZE + 1];
					/* Buffer for storing the output of the
					 * job, line by line */
	    int   	op_curPos;	/* Current position in op_outBuf */
	}   	    o_pipe;	    /* data used when catching the output via
				     * a pipe */
	struct {
	    char  	of_outFile[sizeof(TMPPAT)+2];
					/* Name of file to which shell output
					 * was rerouted */
	    int	    	of_outFd;	/* Stream open to the output
					 * file. Used to funnel all
					 * from a single job to one file
					 * while still allowing
					 * multiple shell invocations */
	}   	    o_file;	    /* Data used when catching the output in
				     * a temporary file */
    }       	output;	    /* Data for tracking a shell's output */
} Job;

#define outPipe	  	output.o_pipe.op_outPipe
#define inPipe	  	output.o_pipe.op_inPipe
#define inPollfd	output.o_pipe.op_inPollfd
#define outBuf		output.o_pipe.op_outBuf
#define curPos		output.o_pipe.op_curPos
#define outFile		output.o_file.of_outFile
#define outFd	  	output.o_file.of_outFd


/*-
 * Shell Specifications:
 * Each shell type has associated with it the following information:
 *	1) The string which must match the last character of the shell name
 *	   for the shell to be considered of this type. The longest match
 *	   wins.
 *	2) A command to issue to turn off echoing of command lines
 *	3) A command to issue to turn echoing back on again
 *	4) What the shell prints, and its length, when given the echo-off
 *	   command. This line will not be printed when received from the shell
 *	5) A boolean to tell if the shell has the ability to control
 *	   error checking for individual commands.
 *	6) The string to turn this checking on.
 *	7) The string to turn it off.
 *	8) The command-flag to give to cause the shell to start echoing
 *	   commands right away.
 *	9) The command-flag to cause the shell to Lib_Exit when an error is
 *	   detected in one of the commands.
 *
 * Some special stuff goes on if a shell doesn't have error control. In such
 * a case, errCheck becomes a printf template for echoing the command,
 * should echoing be on and ignErr becomes another printf template for
 * executing the command while ignoring the return status. Finally errOut
 * is a printf template for running the command and causing the shell to
 * exit on error. If any of these strings are empty when hasErrCtl is FALSE,
 * the command will be executed anyway as is and if it causes an error, so be
 * it. Any templates setup to echo the command will escape any '$ ` \ "'i
 * characters in the command string to avoid common problems with
 * echo "%s\n" as a template.
 */
typedef struct Shell {
    const char	 *name;		/* the name of the shell. For Bourne and C
				 * shells, this is used only to find the
				 * shell description when used as the single
				 * source of a .SHELL target. For user-defined
				 * shells, this is the full path of the shell.
				 */
    Boolean 	  hasEchoCtl;	/* True if both echoOff and echoOn defined */
    const char   *echoOff;	/* command to turn off echo */
    const char   *echoOn;	/* command to turn it back on again */
    const char   *noPrint;	/* command to skip when printing output from
				 * shell. This is usually the command which
				 * was executed to turn off echoing */
    int           noPLen;	/* length of noPrint command */
    Boolean	  hasErrCtl;	/* set if can control error checking for
				 * individual commands */
    const char	 *errCheck;	/* string to turn error checking on */
    const char	 *ignErr;	/* string to turn off error checking */
    const char	 *errOut;	/* string to use for testing exit code */
    char   commentChar;		/* character used by shell for comment lines */

    /*
     * command-line flags
     */
    const char   *echo;		/* echo commands */
    const char   *exit;		/* exit on error */
}               Shell;

extern const char *shellPath;
extern const char *shellName;

extern int	job_pipe[2];	/* token pipe for jobs. */
extern int	jobTokensRunning; /* tokens currently "out" */
extern int	jobTokensFree;	/* tokens free but not yet released to pipe */

#endif /* _JOB_H_ */
/* end job.h */

/* begin trace.h */
/*	$NetBSD: trace.h,v 1.1 2000/12/29 23:11:08 sommerfeld Exp $	*/

/*-
 * Copyright (c) 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Bill Sommerfeld
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*-
 * trace.h --
 *	Definitions pertaining to the tracing of jobs in parallel mode.
 */

#ifndef	_TRACE_H_
#define	_TRACE_H_

typedef enum {
	MAKESTART,
	MAKEEND,
	MAKEERROR,
	JOBSTART,
	JOBEND,
	MAKEINTR,
} TrEvent;

#endif /* _TRACE_H_ */
/* end trace.h */

/* begin pathnames.h */
/*	$NetBSD: pathnames.h,v 1.16 2005/06/24 04:33:25 lukem Exp $	*/

/*
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)pathnames.h	5.2 (Berkeley) 6/1/90
 */

#ifndef MAKE_NATIVE
#if HAVE_NBTOOL_CONFIG_H
#include "nbtool_config.h"
#endif
#else
#include <paths.h>
#endif

#define	_PATH_OBJDIR		"obj"
#define	_PATH_OBJDIRPREFIX	"/usr/obj"
#ifndef _PATH_DEFSHELLDIR
#define	_PATH_DEFSHELLDIR	"/bin"
#endif
#ifndef _PATH_DEFSYSPATH
#define	_PATH_DEFSYSPATH	"/usr/share/mk"
#endif
/* end pathnames.h */

#include "pmake-protos.h"

#ifndef __RCSID
#define __RCSID(x)
#endif

#ifndef __COPYRIGHT
#define __COPYRIGHT(x)
#endif

/* begin buf.c */
/*	$NetBSD: buf.c,v 1.16 2005/02/16 15:11:52 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: buf.c,v 1.16 2005/02/16 15:11:52 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)buf.c	8.1 (Berkeley) 6/6/93";
#else
__RCSID("$NetBSD: buf.c,v 1.16 2005/02/16 15:11:52 christos Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * buf.c --
 *	Functions for automatically-expanded buffers.
 */

/* <<buf.c includes>> */

#ifndef max
#define max(a,b)  ((a) > (b) ? (a) : (b))
#endif

/*
 * BufExpand --
 * 	Expand the given buffer to hold the given number of additional
 *	bytes.
 *	Makes sure there's room for an extra NULL byte at the end of the
 *	buffer in case it holds a string.
 */
#define BufExpand(bp,nb) \
 	while (bp->left < (nb)+1) {\
	    int newSize = (bp)->size * 2; \
	    Byte  *newBuf = (Byte *) erealloc((bp)->buffer, newSize); \
	    \
	    (bp)->inPtr = newBuf + ((bp)->inPtr - (bp)->buffer); \
	    (bp)->outPtr = newBuf + ((bp)->outPtr - (bp)->buffer);\
	    (bp)->buffer = newBuf;\
	    (bp)->size = newSize;\
	    (bp)->left = newSize - ((bp)->inPtr - (bp)->buffer);\
	}

#define BUF_DEF_SIZE	256 	/* Default buffer size */

/*-
 *-----------------------------------------------------------------------
 * Buf_OvAddByte --
 *	Add a single byte to the buffer.  left is zero or negative.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The buffer may be expanded.
 *
 *-----------------------------------------------------------------------
 */
void
Buf_OvAddByte(Buffer bp, int byte)
{
    int nbytes = 1;
    bp->left = 0;
    BufExpand (bp, nbytes);

    *bp->inPtr++ = byte;
    bp->left--;

    /*
     * Null-terminate
     */
    *bp->inPtr = 0;
}

/*-
 *-----------------------------------------------------------------------
 * Buf_AddBytes --
 *	Add a number of bytes to the buffer.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Guess what?
 *
 *-----------------------------------------------------------------------
 */
void
Buf_AddBytes(Buffer bp, int numBytes, const Byte *bytesPtr)
{

    BufExpand (bp, numBytes);

    memcpy (bp->inPtr, bytesPtr, numBytes);
    bp->inPtr += numBytes;
    bp->left -= numBytes;

    /*
     * Null-terminate
     */
    *bp->inPtr = 0;
}

/*-
 *-----------------------------------------------------------------------
 * Buf_GetAll --
 *	Get all the available data at once.
 *
 * Results:
 *	A pointer to the data and the number of bytes available.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
Byte *
Buf_GetAll(Buffer bp, int *numBytesPtr)
{

    if (numBytesPtr != (int *)NULL) {
	*numBytesPtr = bp->inPtr - bp->outPtr;
    }

    return (bp->outPtr);
}

/*-
 *-----------------------------------------------------------------------
 * Buf_Discard --
 *	Throw away bytes in a buffer.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The bytes are discarded.
 *
 *-----------------------------------------------------------------------
 */
void
Buf_Discard(Buffer bp, int numBytes)
{

    if (bp->inPtr - bp->outPtr <= numBytes) {
	bp->inPtr = bp->outPtr = bp->buffer;
	bp->left = bp->size;
	*bp->inPtr = 0;
    } else {
	bp->outPtr += numBytes;
    }
}

/*-
 *-----------------------------------------------------------------------
 * Buf_Size --
 *	Returns the number of bytes in the given buffer. Doesn't include
 *	the null-terminating byte.
 *
 * Results:
 *	The number of bytes.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
int
Buf_Size(Buffer buf)
{
    return (buf->inPtr - buf->outPtr);
}

/*-
 *-----------------------------------------------------------------------
 * Buf_Init --
 *	Initialize a buffer. If no initial size is given, a reasonable
 *	default is used.
 *
 * Input:
 *	size		Initial size for the buffer
 *
 * Results:
 *	A buffer to be given to other functions in this library.
 *
 * Side Effects:
 *	The buffer is created, the space allocated and pointers
 *	initialized.
 *
 *-----------------------------------------------------------------------
 */
Buffer
Buf_Init(int size)
{
    Buffer bp;	  	/* New Buffer */

    bp = emalloc(sizeof(*bp));

    if (size <= 0) {
	size = BUF_DEF_SIZE;
    }
    bp->left = bp->size = size;
    bp->buffer = emalloc(size);
    bp->inPtr = bp->outPtr = bp->buffer;
    *bp->inPtr = 0;

    return (bp);
}

/*-
 *-----------------------------------------------------------------------
 * Buf_Destroy --
 *	Nuke a buffer and all its resources.
 *
 * Input:
 *	buf		Buffer to destroy
 *	freeData	TRUE if the data should be destroyed
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The buffer is freed.
 *
 *-----------------------------------------------------------------------
 */
void
Buf_Destroy(Buffer buf, Boolean freeData)
{

    if (freeData) {
	free ((char *)buf->buffer);
    }
    free ((char *)buf);
}

/*-
 *-----------------------------------------------------------------------
 * Buf_ReplaceLastByte --
 *     Replace the last byte in a buffer.
 *
 * Input:
 *	buf		buffer to augment
 *	byte		byte to be written
 *
 * Results:
 *     None.
 *
 * Side Effects:
 *     If the buffer was empty intially, then a new byte will be added.
 *     Otherwise, the last byte is overwritten.
 *
 *-----------------------------------------------------------------------
 */
void
Buf_ReplaceLastByte(Buffer buf, int byte)
{
    if (buf->inPtr == buf->outPtr)
        Buf_AddByte(buf, byte);
    else
        *(buf->inPtr - 1) = byte;
}
/* end buf.c */

/* begin compat.c */
/*	$NetBSD: compat.c,v 1.58 2005/05/08 04:19:12 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: compat.c,v 1.58 2005/05/08 04:19:12 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)compat.c	8.2 (Berkeley) 3/19/94";
#else
__RCSID("$NetBSD: compat.c,v 1.58 2005/05/08 04:19:12 christos Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * compat.c --
 *	The routines in this file implement the full-compatibility
 *	mode of PMake. Most of the special functionality of PMake
 *	is available in this mode. Things not supported:
 *	    - different shells.
 *	    - friendly variable substitution.
 *
 * Interface:
 *	Compat_Run	    Initialize things for this module and recreate
 *	    	  	    thems as need creatin'
 */

/* <<compat.c includes>> */

/*
 * The following array is used to make a fast determination of which
 * characters are interpreted specially by the shell.  If a command
 * contains any of these characters, it is executed by the shell, not
 * directly by us.
 */

static char 	    meta[256];

static GNode	    *curTarg = NILGNODE;
static GNode	    *STAMPNode = NILGNODE;
static void CompatInterrupt(int);

static void
Compat_Init(void)
{
    const char *cp;

    Shell_Init();		/* setup default shell */

    for (cp = "#=|^(){};&<>*?[]:$`\\\n"; *cp != '\0'; cp++) {
	meta[(unsigned char) *cp] = 1;
    }
    /*
     * The null character serves as a sentinel in the string.
     */
    meta[0] = 1;
}

/*-
 *-----------------------------------------------------------------------
 * CompatInterrupt --
 *	Interrupt the creation of the current target and remove it if
 *	it ain't precious.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The target is removed and the process exits. If .INTERRUPT exists,
 *	its commands are run first WITH INTERRUPTS IGNORED..
 *
 *-----------------------------------------------------------------------
 */
static void
CompatInterrupt(int signo)
{
    if ((curTarg != NILGNODE) && !Targ_Precious (curTarg)) {
	char	  *p1;
	char 	  *file = Var_Value(TARGET, curTarg, &p1);

	if (!noExecute && eunlink(file) != -1) {
	    Error("*** %s removed", file);
	}
	if (p1) {
	    free(p1);
	}
    }
    exit (signo);
}

/*-
 *-----------------------------------------------------------------------
 * CompatRunCommand --
 *	Execute the next command for a target. If the command returns an
 *	error, the node's made field is set to ERROR and creation stops.
 *
 * Input:
 *	cmdp		Command to execute
 *	gnp		Node from which the command came
 *
 * Results:
 *	0 if the command succeeded, 1 if an error occurred.
 *
 * Side Effects:
 *	The node's 'made' field may be set to ERROR.
 *
 *-----------------------------------------------------------------------
 */
int
CompatRunCommand(ClientData cmdp, ClientData gnp)
{
    char    	  *cmdStart;	/* Start of expanded command */
    char 	  *cp, *bp;
    Boolean 	  silent,   	/* Don't print command */
	    	  doIt,		/* Execute even if -n */
		  errCheck; 	/* Check errors */
    int 	  reason;   	/* Reason for child's death */
    int	    	  status;   	/* Description of child's death */
    int	    	  cpid;	    	/* Child actually found */
    ReturnStatus  retstat;    	/* Status of fork */
    LstNode 	  cmdNode;  	/* Node where current command is located */
    const char  **av;	    	/* Argument vector for thing to exec */
    int	    	  argc;	    	/* Number of arguments in av or 0 if not
				 * dynamically allocated */
    Boolean 	  local;    	/* TRUE if command should be executed
				 * locally */
    char	  *cmd = (char *) cmdp;
    GNode	  *gn = (GNode *) gnp;

    /*
     * Avoid clobbered variable warnings by forcing the compiler
     * to ``unregister'' variables
     */
#if __GNUC__
    (void) &av;
    (void) &errCheck;
    (void) &cmd;
#endif
    silent = gn->type & OP_SILENT;
    errCheck = !(gn->type & OP_IGNORE);
    doIt = FALSE;

    cmdNode = Lst_Member(gn->commands, (ClientData)cmd);
    cmdStart = Var_Subst(NULL, cmd, gn, FALSE);

    /*
     * brk_string will return an argv with a NULL in av[0], thus causing
     * execvp to choke and die horribly. Besides, how can we execute a null
     * command? In any case, we warn the user that the command expanded to
     * nothing (is this the right thing to do?).
     */

    if (*cmdStart == '\0') {
	free(cmdStart);
	Error("%s expands to empty string", cmd);
	return(0);
    } else {
	cmd = cmdStart;
    }
    Lst_Replace(cmdNode, (ClientData)cmdStart);

    while ((*cmd == '@') || (*cmd == '-') || (*cmd == '+')) {
	switch (*cmd) {
	case '@':
	    silent = TRUE;
	    break;
	case '-':
	    errCheck = FALSE;
	    break;
	case '+':
	    doIt = TRUE;
	    if (!meta[0])		/* we came here from jobs */
		Compat_Init();
	    break;
	}
	cmd++;
    }

    while (isspace((unsigned char)*cmd))
	cmd++;

    /*
     * Search for meta characters in the command. If there are no meta
     * characters, there's no need to execute a shell to execute the
     * command.
     */
    for (cp = cmd; !meta[(unsigned char)*cp]; cp++) {
	continue;
    }

    /*
     * Print the command before echoing if we're not supposed to be quiet for
     * this one. We also print the command if -n given.
     */
    if (!silent || NoExecute(gn)) {
	printf ("%s\n", cmd);
	fflush(stdout);
    }

    /*
     * If we're not supposed to execute any commands, this is as far as
     * we go...
     */
    if (!doIt && NoExecute(gn)) {
	return (0);
    }

    if (*cp != '\0') {
	/*
	 * If *cp isn't the null character, we hit a "meta" character and
	 * need to pass the command off to the shell.
	 */
	static const char *shargv[4];

	shargv[0] = shellPath;
	/*
	 * The following work for any of the builtin shell specs.
	 */
	if (DEBUG(SHELL))
		shargv[1] = "-xc";
	else
		shargv[1] = "-c";
	shargv[2] = cmd;
	shargv[3] = (char *)NULL;
	av = shargv;
	argc = 0;
	bp = NULL;
    } else {
	/*
	 * No meta-characters, so no need to exec a shell. Break the command
	 * into words to form an argument vector we can execute.
	 */
	av = (const char **)brk_string(cmd, &argc, TRUE, &bp);
    }

    local = TRUE;

    /*
     * Fork and execute the single command. If the fork fails, we abort.
     */
    cpid = vfork();
    if (cpid < 0) {
	Fatal("Could not fork");
    }
    if (cpid == 0) {
	Check_Cwd(av);
	if (local)
	    (void)execvp(av[0], (char *const *)UNCONST(av));
	else
	    (void)execv(av[0], (char *const *)UNCONST(av));
	execError("exec", av[0]);
	_exit(1);
    }
    if (bp) {
	free(av);
	free(bp);
    }
    Lst_Replace(cmdNode, (ClientData) NULL);

    /*
     * The child is off and running. Now all we can do is wait...
     */
    while (1) {

	while ((retstat = wait(&reason)) != cpid) {
	    if (retstat == -1 && errno != EINTR) {
		break;
	    }
	}

	if (retstat > -1) {
	    if (WIFSTOPPED(reason)) {
		status = WSTOPSIG(reason);		/* stopped */
	    } else if (WIFEXITED(reason)) {
		status = WEXITSTATUS(reason);		/* exited */
		if (status != 0) {
		    if (DEBUG(ERROR)) {
		        printf("\n*** Failed target:  %s\n*** Failed command: ",
			    gn->name);
		        for (cp = cmd; *cp; ) {
    			    if (isspace((unsigned char)*cp)) {
			        putchar(' ');
			        while (isspace((unsigned char)*cp))
				    cp++;
			    } else {
			        putchar(*cp);
			        cp++;
			    }
		        }
			printf ("\n");
		    }
		    printf ("*** Error code %d", status);
		}
	    } else {
		status = WTERMSIG(reason);		/* signaled */
		printf ("*** Signal %d", status);
	    }


	    if (!WIFEXITED(reason) || (status != 0)) {
		if (errCheck) {
		    gn->made = ERROR;
		    if (keepgoing) {
			/*
			 * Abort the current target, but let others
			 * continue.
			 */
			printf (" (continuing)\n");
		    }
		} else {
		    /*
		     * Continue executing commands for this target.
		     * If we return 0, this will happen...
		     */
		    printf (" (ignored)\n");
		    status = 0;
		}
	    }
	    break;
	} else {
	    Fatal("error in wait: %d: %s", retstat, strerror(errno));
	    /*NOTREACHED*/
	}
    }
    free(cmdStart);

    return (status);
}

/*-
 *-----------------------------------------------------------------------
 * Compat_Make --
 *	Make a target.
 *
 * Input:
 *	gnp		The node to make
 *	pgnp		Parent to abort if necessary
 *
 * Results:
 *	0
 *
 * Side Effects:
 *	If an error is detected and not being ignored, the process exits.
 *
 *-----------------------------------------------------------------------
 */
int
Compat_Make(ClientData gnp, ClientData pgnp)
{
    GNode *gn = (GNode *) gnp;
    GNode *pgn = (GNode *) pgnp;

    if (!meta[0])		/* we came here from jobs */
	Compat_Init();
    if (gn->made == UNMADE && (gn == pgn || (pgn->type & OP_MADE) == 0)) {
	/*
	 * First mark ourselves to be made, then apply whatever transformations
	 * the suffix module thinks are necessary. Once that's done, we can
	 * descend and make all our children. If any of them has an error
	 * but the -k flag was given, our 'make' field will be set FALSE again.
	 * This is our signal to not attempt to do anything but abort our
	 * parent as well.
	 */
	gn->flags |= REMAKE;
	gn->made = BEINGMADE;
	if ((gn->type & OP_MADE) == 0)
	    Suff_FindDeps(gn);
	Lst_ForEach(gn->children, Compat_Make, (ClientData)gn);
	if ((gn->flags & REMAKE) == 0) {
	    gn->made = ABORTED;
	    pgn->flags &= ~REMAKE;
	    goto cohorts;
	}

	if (Lst_Member(gn->iParents, pgn) != NILLNODE) {
	    char *p1;
	    Var_Set(IMPSRC, Var_Value(TARGET, gn, &p1), pgn, 0);
	    if (p1)
		free(p1);
	}

	/*
	 * All the children were made ok. Now cmtime contains the modification
	 * time of the newest child, we need to find out if we exist and when
	 * we were modified last. The criteria for datedness are defined by the
	 * Make_OODate function.
	 */
	if (DEBUG(MAKE)) {
	    printf("Examining %s...", gn->name);
	}
	if (! Make_OODate(gn)) {
	    gn->made = UPTODATE;
	    if (DEBUG(MAKE)) {
		printf("up-to-date.\n");
	    }
	    goto cohorts;
	} else if (DEBUG(MAKE)) {
	    printf("out-of-date.\n");
	}

	/*
	 * If the user is just seeing if something is out-of-date, exit now
	 * to tell him/her "yes".
	 */
	if (queryFlag) {
	    exit (1);
	}

	/*
	 * We need to be re-made. We also have to make sure we've got a $?
	 * variable. To be nice, we also define the $> variable using
	 * Make_DoAllVar().
	 */
	Make_DoAllVar(gn);

	/*
	 * Alter our type to tell if errors should be ignored or things
	 * should not be printed so CompatRunCommand knows what to do.
	 */
	if (Targ_Ignore(gn)) {
	    gn->type |= OP_IGNORE;
	}
	if (Targ_Silent(gn)) {
	    gn->type |= OP_SILENT;
	}

	if (Job_CheckCommands(gn, Fatal)) {
	    /*
	     * Our commands are ok, but we still have to worry about the -t
	     * flag...
	     */
	    if (!touchFlag || (gn->type & OP_MAKE)) {
		curTarg = gn;
		Lst_ForEach(gn->commands, CompatRunCommand, (ClientData)gn);
		curTarg = NILGNODE;
	    } else {
		Job_Touch(gn, gn->type & OP_SILENT);
	    }
	} else {
	    gn->made = ERROR;
	}

	if (gn->made != ERROR) {
	    /*
	     * If the node was made successfully, mark it so, update
	     * its modification time and timestamp all its parents. Note
	     * that for .ZEROTIME targets, the timestamping isn't done.
	     * This is to keep its state from affecting that of its parent.
	     */
	    gn->made = MADE;
	    pgn->flags |= Make_Recheck(gn) == 0 ? FORCE : 0;
	    if (!(gn->type & OP_EXEC)) {
		pgn->flags |= CHILDMADE;
		Make_TimeStamp(pgn, gn);
	    }
	} else if (keepgoing) {
	    pgn->flags &= ~REMAKE;
	} else {
	    PrintOnError("\n\nStop.");
	    exit (1);
	}
    } else if (gn->made == ERROR) {
	/*
	 * Already had an error when making this beastie. Tell the parent
	 * to abort.
	 */
	pgn->flags &= ~REMAKE;
    } else {
	if (Lst_Member(gn->iParents, pgn) != NILLNODE) {
	    char *p1;
	    Var_Set(IMPSRC, Var_Value(TARGET, gn, &p1), pgn, 0);
	    if (p1)
		free(p1);
	}
	switch(gn->made) {
	    case BEINGMADE:
		Error("Graph cycles through %s", gn->name);
		gn->made = ERROR;
		pgn->flags &= ~REMAKE;
		break;
	    case MADE:
		if ((gn->type & OP_EXEC) == 0) {
		    pgn->flags |= CHILDMADE;
		    Make_TimeStamp(pgn, gn);
		}
		break;
	    case UPTODATE:
		if ((gn->type & OP_EXEC) == 0) {
		    Make_TimeStamp(pgn, gn);
		}
		break;
	    default:
		break;
	}
    }

cohorts:
    Lst_ForEach(gn->cohorts, Compat_Make, pgnp);
    return (0);
}

/*-
 *-----------------------------------------------------------------------
 * Compat_Run --
 *	Initialize this mode and start making.
 *
 * Input:
 *	targs		List of target nodes to re-create
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Guess what?
 *
 *-----------------------------------------------------------------------
 */
void
Compat_Run(Lst targs)
{
    GNode   	  *gn = NULL;/* Current root target */
    int	    	  errors;   /* Number of targets not remade due to errors */

    Compat_Init();

    if (signal(SIGINT, SIG_IGN) != SIG_IGN) {
	signal(SIGINT, CompatInterrupt);
    }
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN) {
	signal(SIGTERM, CompatInterrupt);
    }
    if (signal(SIGHUP, SIG_IGN) != SIG_IGN) {
	signal(SIGHUP, CompatInterrupt);
    }
    if (signal(SIGQUIT, SIG_IGN) != SIG_IGN) {
	signal(SIGQUIT, CompatInterrupt);
    }

    STAMPNode = Targ_FindNode(".STAMP", TARG_NOCREATE);

    /*
     * If the user has defined a .BEGIN target, execute the commands attached
     * to it.
     */
    if (!queryFlag) {
	gn = Targ_FindNode(".BEGIN", TARG_NOCREATE);
	if (gn != NILGNODE) {
	    Compat_Make(gn, gn);
            if (gn->made == ERROR) {
                PrintOnError("\n\nStop.");
                exit(1);
            }
	}
    }

    /*
     * Expand .USE nodes right now, because they can modify the structure
     * of the tree.
     */
    Lst_Destroy(Make_ExpandUse(targs), NOFREE);

    /*
     * For each entry in the list of targets to create, call Compat_Make on
     * it to create the thing. Compat_Make will leave the 'made' field of gn
     * in one of several states:
     *	    UPTODATE	    gn was already up-to-date
     *	    MADE  	    gn was recreated successfully
     *	    ERROR 	    An error occurred while gn was being created
     *	    ABORTED	    gn was not remade because one of its inferiors
     *	    	  	    could not be made due to errors.
     */
    errors = 0;
    while (!Lst_IsEmpty (targs)) {
	gn = (GNode *) Lst_DeQueue(targs);
	Compat_Make(gn, gn);

	if (gn->made == UPTODATE) {
	    printf ("`%s' is up to date.\n", gn->name);
	} else if (gn->made == ABORTED) {
	    printf ("`%s' not remade because of errors.\n", gn->name);
	    errors += 1;
	}
    }
}
/* end compat.c */

/* begin cond.c */
/*	$NetBSD: cond.c,v 1.27 2005/06/02 02:03:19 lukem Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: cond.c,v 1.27 2005/06/02 02:03:19 lukem Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)cond.c	8.2 (Berkeley) 1/2/94";
#else
__RCSID("$NetBSD: cond.c,v 1.27 2005/06/02 02:03:19 lukem Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * cond.c --
 *	Functions to handle conditionals in a makefile.
 *
 * Interface:
 *	Cond_Eval 	Evaluate the conditional in the passed line.
 *
 */

/* <<cond.c includes>> */

/*
 * The parsing of conditional expressions is based on this grammar:
 *	E -> F || E
 *	E -> F
 *	F -> T && F
 *	F -> T
 *	T -> defined(variable)
 *	T -> make(target)
 *	T -> exists(file)
 *	T -> empty(varspec)
 *	T -> target(name)
 *	T -> commands(name)
 *	T -> symbol
 *	T -> $(varspec) op value
 *	T -> $(varspec) == "string"
 *	T -> $(varspec) != "string"
 *	T -> "string"
 *	T -> ( E )
 *	T -> ! T
 *	op -> == | != | > | < | >= | <=
 *
 * 'symbol' is some other symbol to which the default function (condDefProc)
 * is applied.
 *
 * Tokens are scanned from the 'condExpr' string. The scanner (CondToken)
 * will return And for '&' and '&&', Or for '|' and '||', Not for '!',
 * LParen for '(', RParen for ')' and will evaluate the other terminal
 * symbols, using either the default function or the function given in the
 * terminal, and return the result as either True or False.
 *
 * All Non-Terminal functions (CondE, CondF and CondT) return Err on error.
 */
typedef enum {
    And, Or, TokenNot, True, False, LParen, RParen, EndOfFile, None, Err
} Token;

/*-
 * Structures to handle elegantly the different forms of #if's. The
 * last two fields are stored in condInvert and condDefProc, respectively.
 */
static void CondPushBack(Token);
static int CondGetArg(char **, char **, const char *, Boolean);
static Boolean CondDoDefined(int, char *);
static int CondStrMatch(ClientData, ClientData);
static Boolean CondDoMake(int, char *);
static Boolean CondDoExists(int, char *);
static Boolean CondDoTarget(int, char *);
static Boolean CondDoCommands(int, char *);
static char * CondCvtArg(char *, double *);
static Token CondToken(Boolean);
static Token CondT(Boolean);
static Token CondF(Boolean);
static Token CondE(Boolean);

static struct If {
    const char	*form;	      /* Form of if */
    int		formlen;      /* Length of form */
    Boolean	doNot;	      /* TRUE if default function should be negated */
    Boolean	(*defProc)(int, char *); /* Default function to apply */
} ifs[] = {
    { "ifdef",	  5,	  FALSE,  CondDoDefined },
    { "ifndef",	  6,	  TRUE,	  CondDoDefined },
    { "ifmake",	  6,	  FALSE,  CondDoMake },
    { "ifnmake",  7,	  TRUE,	  CondDoMake },
    { "if",	  2,	  FALSE,  CondDoDefined },
    { NULL,	  0,	  FALSE,  NULL }
};

static Boolean	  condInvert;	    	/* Invert the default function */
static Boolean	  (*condDefProc)(int, char *);	/* Default function to apply */
static char 	  *condExpr;	    	/* The expression to parse */
static Token	  condPushBack=None;	/* Single push-back token used in
					 * parsing */

#define	MAXIF		64	  /* greatest depth of #if'ing */

static Boolean	  finalElse[MAXIF+1][MAXIF+1]; /* Seen final else (stack) */
static Boolean	  condStack[MAXIF]; 	/* Stack of conditionals's values */
static int  	  condTop = MAXIF;  	/* Top-most conditional */
static int  	  skipIfLevel=0;    	/* Depth of skipped conditionals */
static Boolean	  skipLine = FALSE; 	/* Whether the parse module is skipping
					 * lines */

static int
istoken(const char *str, const char *tok, size_t len)
{
	return strncmp(str, tok, len) == 0 && !isalpha((unsigned char)str[len]);
}

/*-
 *-----------------------------------------------------------------------
 * CondPushBack --
 *	Push back the most recent token read. We only need one level of
 *	this, so the thing is just stored in 'condPushback'.
 *
 * Input:
 *	t		Token to push back into the "stream"
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	condPushback is overwritten.
 *
 *-----------------------------------------------------------------------
 */
static void
CondPushBack(Token t)
{
    condPushBack = t;
}

/*-
 *-----------------------------------------------------------------------
 * CondGetArg --
 *	Find the argument of a built-in function.
 *
 * Input:
 *	parens		TRUE if arg should be bounded by parens
 *
 * Results:
 *	The length of the argument and the address of the argument.
 *
 * Side Effects:
 *	The pointer is set to point to the closing parenthesis of the
 *	function call.
 *
 *-----------------------------------------------------------------------
 */
static int
CondGetArg(char **linePtr, char **argPtr, const char *func, Boolean parens)
{
    char	  *cp;
    int	    	  argLen;
    Buffer	  buf;

    cp = *linePtr;
    if (parens) {
	while (*cp != '(' && *cp != '\0') {
	    cp++;
	}
	if (*cp == '(') {
	    cp++;
	}
    }

    if (*cp == '\0') {
	/*
	 * No arguments whatsoever. Because 'make' and 'defined' aren't really
	 * "reserved words", we don't print a message. I think this is better
	 * than hitting the user with a warning message every time s/he uses
	 * the word 'make' or 'defined' at the beginning of a symbol...
	 */
	*argPtr = cp;
	return (0);
    }

    while (*cp == ' ' || *cp == '\t') {
	cp++;
    }

    /*
     * Create a buffer for the argument and start it out at 16 characters
     * long. Why 16? Why not?
     */
    buf = Buf_Init(16);

    while ((strchr(" \t)&|", *cp) == (char *)NULL) && (*cp != '\0')) {
	if (*cp == '$') {
	    /*
	     * Parse the variable spec and install it as part of the argument
	     * if it's valid. We tell Var_Parse to complain on an undefined
	     * variable, so we don't do it too. Nor do we return an error,
	     * though perhaps we should...
	     */
	    char  	*cp2;
	    int		len;
	    Boolean	doFree;

	    cp2 = Var_Parse(cp, VAR_CMD, TRUE, &len, &doFree);

	    Buf_AddBytes(buf, strlen(cp2), (Byte *)cp2);
	    if (doFree) {
		free(cp2);
	    }
	    cp += len;
	} else {
	    Buf_AddByte(buf, (Byte)*cp);
	    cp++;
	}
    }

    Buf_AddByte(buf, (Byte)'\0');
    *argPtr = (char *)Buf_GetAll(buf, &argLen);
    Buf_Destroy(buf, FALSE);

    while (*cp == ' ' || *cp == '\t') {
	cp++;
    }
    if (parens && *cp != ')') {
	Parse_Error(PARSE_WARNING, "Missing closing parenthesis for %s()",
		     func);
	return (0);
    } else if (parens) {
	/*
	 * Advance pointer past close parenthesis.
	 */
	cp++;
    }

    *linePtr = cp;
    return (argLen);
}

/*-
 *-----------------------------------------------------------------------
 * CondDoDefined --
 *	Handle the 'defined' function for conditionals.
 *
 * Results:
 *	TRUE if the given variable is defined.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
CondDoDefined(int argLen, char *arg)
{
    char    savec = arg[argLen];
    char    *p1;
    Boolean result;

    arg[argLen] = '\0';
    if (Var_Value(arg, VAR_CMD, &p1) != (char *)NULL) {
	result = TRUE;
    } else {
	result = FALSE;
    }
    if (p1)
	free(p1);
    arg[argLen] = savec;
    return (result);
}

/*-
 *-----------------------------------------------------------------------
 * CondStrMatch --
 *	Front-end for Str_Match so it returns 0 on match and non-zero
 *	on mismatch. Callback function for CondDoMake via Lst_Find
 *
 * Results:
 *	0 if string matches pattern
 *
 * Side Effects:
 *	None
 *
 *-----------------------------------------------------------------------
 */
static int
CondStrMatch(ClientData string, ClientData pattern)
{
    return(!Str_Match((char *) string,(char *) pattern));
}

/*-
 *-----------------------------------------------------------------------
 * CondDoMake --
 *	Handle the 'make' function for conditionals.
 *
 * Results:
 *	TRUE if the given target is being made.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
CondDoMake(int argLen, char *arg)
{
    char    savec = arg[argLen];
    Boolean result;

    arg[argLen] = '\0';
    if (Lst_Find(create, (ClientData)arg, CondStrMatch) == NILLNODE) {
	result = FALSE;
    } else {
	result = TRUE;
    }
    arg[argLen] = savec;
    return (result);
}

/*-
 *-----------------------------------------------------------------------
 * CondDoExists --
 *	See if the given file exists.
 *
 * Results:
 *	TRUE if the file exists and FALSE if it does not.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
CondDoExists(int argLen, char *arg)
{
    char    savec = arg[argLen];
    Boolean result;
    char    *path;

    arg[argLen] = '\0';
    path = Dir_FindFile(arg, dirSearchPath);
    if (path != (char *)NULL) {
	result = TRUE;
	free(path);
    } else {
	result = FALSE;
    }
    arg[argLen] = savec;
    return (result);
}

/*-
 *-----------------------------------------------------------------------
 * CondDoTarget --
 *	See if the given node exists and is an actual target.
 *
 * Results:
 *	TRUE if the node exists as a target and FALSE if it does not.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
CondDoTarget(int argLen, char *arg)
{
    char    savec = arg[argLen];
    Boolean result;
    GNode   *gn;

    arg[argLen] = '\0';
    gn = Targ_FindNode(arg, TARG_NOCREATE);
    if ((gn != NILGNODE) && !OP_NOP(gn->type)) {
	result = TRUE;
    } else {
	result = FALSE;
    }
    arg[argLen] = savec;
    return (result);
}

/*-
 *-----------------------------------------------------------------------
 * CondDoCommands --
 *	See if the given node exists and is an actual target with commands
 *	associated with it.
 *
 * Results:
 *	TRUE if the node exists as a target and has commands associated with
 *	it and FALSE if it does not.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
CondDoCommands(int argLen, char *arg)
{
    char    savec = arg[argLen];
    Boolean result;
    GNode   *gn;

    arg[argLen] = '\0';
    gn = Targ_FindNode(arg, TARG_NOCREATE);
    if ((gn != NILGNODE) && !OP_NOP(gn->type) && !Lst_IsEmpty(gn->commands)) {
	result = TRUE;
    } else {
	result = FALSE;
    }
    arg[argLen] = savec;
    return (result);
}

/*-
 *-----------------------------------------------------------------------
 * CondCvtArg --
 *	Convert the given number into a double. If the number begins
 *	with 0x, it is interpreted as a hexadecimal integer
 *	and converted to a double from there. All other strings just have
 *	strtod called on them.
 *
 * Results:
 *	Sets 'value' to double value of string.
 *	Returns NULL if string was fully consumed,
 *	else returns remaining input.
 *
 * Side Effects:
 *	Can change 'value' even if string is not a valid number.
 *
 *
 *-----------------------------------------------------------------------
 */
static char *
CondCvtArg(char *str, double *value)
{
    if ((*str == '0') && (str[1] == 'x')) {
	long i;

	for (str += 2, i = 0; *str; str++) {
	    int x;
	    if (isdigit((unsigned char) *str))
		x  = *str - '0';
	    else if (isxdigit((unsigned char) *str))
		x = 10 + *str - isupper((unsigned char) *str) ? 'A' : 'a';
	    else
		break;
	    i = (i << 4) + x;
	}
	*value = (double) i;
	return *str ? str : NULL;
    } else {
	char *eptr;
	*value = strtod(str, &eptr);
	return *eptr ? eptr : NULL;
    }
}

/*-
 *-----------------------------------------------------------------------
 * CondGetString --
 *	Get a string from a variable reference or an optionally quoted
 *	string.  This is called for the lhs and rhs of string compares.
 *
 * Results:
 *	Sets doFree if needed,
 *	Sets quoted if string was quoted,
 *	Returns NULL on error,
 *	else returns string - absent any quotes.
 *
 * Side Effects:
 *	Moves condExpr to end of this token.
 *
 *
 *-----------------------------------------------------------------------
 */
static char *
CondGetString(Boolean doEval, Boolean *quoted, Boolean *doFree)
{
    Buffer buf;
    char *cp;
    char *str;
    int	len;
    int qt;
    char *start;

    buf = Buf_Init(0);
    str = NULL;
    *quoted = qt = *condExpr == '"' ? 1 : 0;
    if (qt)
	condExpr++;
    for (start = condExpr; *condExpr && str == NULL; condExpr++) {
	switch (*condExpr) {
	case '\\':
	    if (condExpr[1] != '\0') {
		condExpr++;
		Buf_AddByte(buf, (Byte)*condExpr);
	    }
	    break;
	case '"':
	    if (qt) {
		condExpr++;		/* we don't want the quotes */
		goto got_str;
	    } else
		Buf_AddByte(buf, (Byte)*condExpr); /* likely? */
	    break;
	case ')':
	case '!':
	case '=':
	case '>':
	case '<':
	case ' ':
	case '\t':
	    if (!qt)
		goto got_str;
	    else
		Buf_AddByte(buf, (Byte)*condExpr);
	    break;
	case '$':
	    /* if we are in quotes, then an undefined variable is ok */
	    str = Var_Parse(condExpr, VAR_CMD, (qt ? 0 : doEval),
			    &len, doFree);
	    if (str == var_Error) {
		/*
		 * Even if !doEval, we still report syntax errors, which
		 * is what getting var_Error back with !doEval means.
		 */
		str = NULL;
		goto cleanup;
	    }
	    condExpr += len;
	    /*
	     * If the '$' was first char (no quotes), and we are
	     * followed by space, the operator or end of expression,
	     * we are done.
	     */
	    if ((condExpr == start + len) &&
		(*condExpr == '\0' ||
		 isspace((unsigned char) *condExpr) ||
		 strchr("!=><)", *condExpr))) {
		goto cleanup;
	    }
	    /*
	     * Nope, we better copy str to buf
	     */
	    for (cp = str; *cp; cp++) {
		Buf_AddByte(buf, (Byte)*cp);
	    }
	    if (*doFree)
		free(str);
	    *doFree = FALSE;
	    str = NULL;			/* not finished yet */
	    condExpr--;			/* don't skip over next char */
	    break;
	default:
	    Buf_AddByte(buf, (Byte)*condExpr);
	    break;
	}
    }
 got_str:
    Buf_AddByte(buf, (Byte)'\0');
    str = (char *)Buf_GetAll(buf, NULL);
    *doFree = TRUE;
 cleanup:
    Buf_Destroy(buf, FALSE);
    return str;
}

/*-
 *-----------------------------------------------------------------------
 * CondToken --
 *	Return the next token from the input.
 *
 * Results:
 *	A Token for the next lexical token in the stream.
 *
 * Side Effects:
 *	condPushback will be set back to None if it is used.
 *
 *-----------------------------------------------------------------------
 */
static Token
CondToken(Boolean doEval)
{
    Token	  t;

    if (condPushBack == None) {
	while (*condExpr == ' ' || *condExpr == '\t') {
	    condExpr++;
	}
	switch (*condExpr) {
	    case '(':
		t = LParen;
		condExpr++;
		break;
	    case ')':
		t = RParen;
		condExpr++;
		break;
	    case '|':
		if (condExpr[1] == '|') {
		    condExpr++;
		}
		condExpr++;
		t = Or;
		break;
	    case '&':
		if (condExpr[1] == '&') {
		    condExpr++;
		}
		condExpr++;
		t = And;
		break;
	    case '!':
		t = TokenNot;
		condExpr++;
		break;
	    case '#':
	    case '\n':
	    case '\0':
		t = EndOfFile;
		break;
	    case '"':
	    case '$': {
		char	*lhs;
		char	*rhs;
		char	*op;
		Boolean	lhsFree;
		Boolean	rhsFree;
		Boolean lhsQuoted;
		Boolean rhsQuoted;

		rhs = NULL;
		lhsFree = rhsFree = FALSE;
		lhsQuoted = rhsQuoted = FALSE;

		/*
		 * Parse the variable spec and skip over it, saving its
		 * value in lhs.
		 */
		t = Err;
		lhs = CondGetString(doEval, &lhsQuoted, &lhsFree);
		if (!lhs)
		    return Err;
		/*
		 * Skip whitespace to get to the operator
		 */
		while (isspace((unsigned char) *condExpr))
		    condExpr++;

		/*
		 * Make sure the operator is a valid one. If it isn't a
		 * known relational operator, pretend we got a
		 * != 0 comparison.
		 */
		op = condExpr;
		switch (*condExpr) {
		    case '!':
		    case '=':
		    case '<':
		    case '>':
			if (condExpr[1] == '=') {
			    condExpr += 2;
			} else {
			    condExpr += 1;
			}
			break;
		    default:
			op = UNCONST("!=");
			if (lhsQuoted)
			    rhs = UNCONST("");
			else
			    rhs = UNCONST("0");

			goto do_compare;
		}
		while (isspace((unsigned char) *condExpr)) {
		    condExpr++;
		}
		if (*condExpr == '\0') {
		    Parse_Error(PARSE_WARNING,
				"Missing right-hand-side of operator");
		    goto error;
		}
		rhs = CondGetString(doEval, &rhsQuoted, &rhsFree);
		if (!rhs)
		    return Err;
do_compare:
		if (rhsQuoted || lhsQuoted) {
do_string_compare:
		    if (((*op != '!') && (*op != '=')) || (op[1] != '=')) {
			Parse_Error(PARSE_WARNING,
		"String comparison operator should be either == or !=");
			goto error;
		    }

		    if (DEBUG(COND)) {
			printf("lhs = \"%s\", rhs = \"%s\", op = %.2s\n",
			       lhs, rhs, op);
		    }
		    /*
		     * Null-terminate rhs and perform the comparison.
		     * t is set to the result.
		     */
		    if (*op == '=') {
			t = strcmp(lhs, rhs) ? False : True;
		    } else {
			t = strcmp(lhs, rhs) ? True : False;
		    }
		} else {
		    /*
		     * rhs is either a float or an integer. Convert both the
		     * lhs and the rhs to a double and compare the two.
		     */
		    double  	left, right;
		    char	*cp;

		    if (CondCvtArg(lhs, &left))
			goto do_string_compare;
		    if ((cp = CondCvtArg(rhs, &right)) &&
			    cp == rhs)
			goto do_string_compare;

		    if (DEBUG(COND)) {
			printf("left = %f, right = %f, op = %.2s\n", left,
			       right, op);
		    }
		    switch(op[0]) {
		    case '!':
			if (op[1] != '=') {
			    Parse_Error(PARSE_WARNING,
					"Unknown operator");
			    goto error;
			}
			t = (left != right ? True : False);
			break;
		    case '=':
			if (op[1] != '=') {
			    Parse_Error(PARSE_WARNING,
					"Unknown operator");
			    goto error;
			}
			t = (left == right ? True : False);
			break;
		    case '<':
			if (op[1] == '=') {
			    t = (left <= right ? True : False);
			} else {
			    t = (left < right ? True : False);
			}
			break;
		    case '>':
			if (op[1] == '=') {
			    t = (left >= right ? True : False);
			} else {
			    t = (left > right ? True : False);
			}
			break;
		    }
		}
error:
		if (lhsFree)
		    free(lhs);
		if (rhsFree)
		    free(rhs);
		break;
	    }
	    default: {
		Boolean (*evalProc)(int, char *);
		Boolean invert = FALSE;
		char	*arg;
		int	arglen;

		if (istoken(condExpr, "defined", 7)) {
		    /*
		     * Use CondDoDefined to evaluate the argument and
		     * CondGetArg to extract the argument from the 'function
		     * call'.
		     */
		    evalProc = CondDoDefined;
		    condExpr += 7;
		    arglen = CondGetArg(&condExpr, &arg, "defined", TRUE);
		    if (arglen == 0) {
			condExpr -= 7;
			goto use_default;
		    }
		} else if (istoken(condExpr, "make", 4)) {
		    /*
		     * Use CondDoMake to evaluate the argument and
		     * CondGetArg to extract the argument from the 'function
		     * call'.
		     */
		    evalProc = CondDoMake;
		    condExpr += 4;
		    arglen = CondGetArg(&condExpr, &arg, "make", TRUE);
		    if (arglen == 0) {
			condExpr -= 4;
			goto use_default;
		    }
		} else if (istoken(condExpr, "exists", 6)) {
		    /*
		     * Use CondDoExists to evaluate the argument and
		     * CondGetArg to extract the argument from the
		     * 'function call'.
		     */
		    evalProc = CondDoExists;
		    condExpr += 6;
		    arglen = CondGetArg(&condExpr, &arg, "exists", TRUE);
		    if (arglen == 0) {
			condExpr -= 6;
			goto use_default;
		    }
		} else if (istoken(condExpr, "empty", 5)) {
		    /*
		     * Use Var_Parse to parse the spec in parens and return
		     * True if the resulting string is empty.
		     */
		    int	    length;
		    Boolean doFree;
		    char    *val;

		    condExpr += 5;

		    for (arglen = 0;
			 condExpr[arglen] != '(' && condExpr[arglen] != '\0';
			 arglen += 1)
			continue;

		    if (condExpr[arglen] != '\0') {
			val = Var_Parse(&condExpr[arglen - 1], VAR_CMD,
					FALSE, &length, &doFree);
			if (val == var_Error) {
			    t = Err;
			} else {
			    /*
			     * A variable is empty when it just contains
			     * spaces... 4/15/92, christos
			     */
			    char *p;
			    for (p = val; *p && isspace((unsigned char)*p); p++)
				continue;
			    t = (*p == '\0') ? True : False;
			}
			if (doFree) {
			    free(val);
			}
			/*
			 * Advance condExpr to beyond the closing ). Note that
			 * we subtract one from arglen + length b/c length
			 * is calculated from condExpr[arglen - 1].
			 */
			condExpr += arglen + length - 1;
		    } else {
			condExpr -= 5;
			goto use_default;
		    }
		    break;
		} else if (istoken(condExpr, "target", 6)) {
		    /*
		     * Use CondDoTarget to evaluate the argument and
		     * CondGetArg to extract the argument from the
		     * 'function call'.
		     */
		    evalProc = CondDoTarget;
		    condExpr += 6;
		    arglen = CondGetArg(&condExpr, &arg, "target", TRUE);
		    if (arglen == 0) {
			condExpr -= 6;
			goto use_default;
		    }
		} else if (istoken(condExpr, "commands", 8)) {
		    /*
		     * Use CondDoCommands to evaluate the argument and
		     * CondGetArg to extract the argument from the
		     * 'function call'.
		     */
		    evalProc = CondDoCommands;
		    condExpr += 8;
		    arglen = CondGetArg(&condExpr, &arg, "commands", TRUE);
		    if (arglen == 0) {
			condExpr -= 8;
			goto use_default;
		    }
		} else {
		    /*
		     * The symbol is itself the argument to the default
		     * function. We advance condExpr to the end of the symbol
		     * by hand (the next whitespace, closing paren or
		     * binary operator) and set to invert the evaluation
		     * function if condInvert is TRUE.
		     */
		use_default:
		    invert = condInvert;
		    evalProc = condDefProc;
		    arglen = CondGetArg(&condExpr, &arg, "", FALSE);
		}

		/*
		 * Evaluate the argument using the set function. If invert
		 * is TRUE, we invert the sense of the function.
		 */
		t = (!doEval || (* evalProc) (arglen, arg) ?
		     (invert ? False : True) :
		     (invert ? True : False));
		free(arg);
		break;
	    }
	}
    } else {
	t = condPushBack;
	condPushBack = None;
    }
    return (t);
}

/*-
 *-----------------------------------------------------------------------
 * CondT --
 *	Parse a single term in the expression. This consists of a terminal
 *	symbol or TokenNot and a terminal symbol (not including the binary
 *	operators):
 *	    T -> defined(variable) | make(target) | exists(file) | symbol
 *	    T -> ! T | ( E )
 *
 * Results:
 *	True, False or Err.
 *
 * Side Effects:
 *	Tokens are consumed.
 *
 *-----------------------------------------------------------------------
 */
static Token
CondT(Boolean doEval)
{
    Token   t;

    t = CondToken(doEval);

    if (t == EndOfFile) {
	/*
	 * If we reached the end of the expression, the expression
	 * is malformed...
	 */
	t = Err;
    } else if (t == LParen) {
	/*
	 * T -> ( E )
	 */
	t = CondE(doEval);
	if (t != Err) {
	    if (CondToken(doEval) != RParen) {
		t = Err;
	    }
	}
    } else if (t == TokenNot) {
	t = CondT(doEval);
	if (t == True) {
	    t = False;
	} else if (t == False) {
	    t = True;
	}
    }
    return (t);
}

/*-
 *-----------------------------------------------------------------------
 * CondF --
 *	Parse a conjunctive factor (nice name, wot?)
 *	    F -> T && F | T
 *
 * Results:
 *	True, False or Err
 *
 * Side Effects:
 *	Tokens are consumed.
 *
 *-----------------------------------------------------------------------
 */
static Token
CondF(Boolean doEval)
{
    Token   l, o;

    l = CondT(doEval);
    if (l != Err) {
	o = CondToken(doEval);

	if (o == And) {
	    /*
	     * F -> T && F
	     *
	     * If T is False, the whole thing will be False, but we have to
	     * parse the r.h.s. anyway (to throw it away).
	     * If T is True, the result is the r.h.s., be it an Err or no.
	     */
	    if (l == True) {
		l = CondF(doEval);
	    } else {
		(void) CondF(FALSE);
	    }
	} else {
	    /*
	     * F -> T
	     */
	    CondPushBack(o);
	}
    }
    return (l);
}

/*-
 *-----------------------------------------------------------------------
 * CondE --
 *	Main expression production.
 *	    E -> F || E | F
 *
 * Results:
 *	True, False or Err.
 *
 * Side Effects:
 *	Tokens are, of course, consumed.
 *
 *-----------------------------------------------------------------------
 */
static Token
CondE(Boolean doEval)
{
    Token   l, o;

    l = CondF(doEval);
    if (l != Err) {
	o = CondToken(doEval);

	if (o == Or) {
	    /*
	     * E -> F || E
	     *
	     * A similar thing occurs for ||, except that here we make sure
	     * the l.h.s. is False before we bother to evaluate the r.h.s.
	     * Once again, if l is False, the result is the r.h.s. and once
	     * again if l is True, we parse the r.h.s. to throw it away.
	     */
	    if (l == False) {
		l = CondE(doEval);
	    } else {
		(void) CondE(FALSE);
	    }
	} else {
	    /*
	     * E -> F
	     */
	    CondPushBack(o);
	}
    }
    return (l);
}

/*-
 *-----------------------------------------------------------------------
 * Cond_EvalExpression --
 *	Evaluate an expression in the passed line. The expression
 *	consists of &&, ||, !, make(target), defined(variable)
 *	and parenthetical groupings thereof.
 *
 * Results:
 *	COND_PARSE	if the condition was valid grammatically
 *	COND_INVALID  	if not a valid conditional.
 *
 *	(*value) is set to the boolean value of the condition
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
int
Cond_EvalExpression(int dosetup, char *line, Boolean *value, int eprint)
{
    if (dosetup) {
	condDefProc = CondDoDefined;
	condInvert = 0;
    }

    while (*line == ' ' || *line == '\t')
	line++;

    condExpr = line;
    condPushBack = None;

    switch (CondE(TRUE)) {
    case True:
	if (CondToken(TRUE) == EndOfFile) {
	    *value = TRUE;
	    break;
	}
	goto err;
	/*FALLTHRU*/
    case False:
	if (CondToken(TRUE) == EndOfFile) {
	    *value = FALSE;
	    break;
	}
	/*FALLTHRU*/
    case Err:
err:
	if (eprint)
	    Parse_Error(PARSE_FATAL, "Malformed conditional (%s)",
			 line);
	return (COND_INVALID);
    default:
	break;
    }

    return COND_PARSE;
}


/*-
 *-----------------------------------------------------------------------
 * Cond_Eval --
 *	Evaluate the conditional in the passed line. The line
 *	looks like this:
 *	    #<cond-type> <expr>
 *	where <cond-type> is any of if, ifmake, ifnmake, ifdef,
 *	ifndef, elif, elifmake, elifnmake, elifdef, elifndef
 *	and <expr> consists of &&, ||, !, make(target), defined(variable)
 *	and parenthetical groupings thereof.
 *
 * Input:
 *	line		Line to parse
 *
 * Results:
 *	COND_PARSE	if should parse lines after the conditional
 *	COND_SKIP	if should skip lines after the conditional
 *	COND_INVALID  	if not a valid conditional.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
int
Cond_Eval(char *line)
{
    struct If	    *ifp;
    Boolean 	    isElse;
    Boolean 	    value = FALSE;
    int	    	    level;  	/* Level at which to report errors. */

    level = PARSE_FATAL;

    for (line++; *line == ' ' || *line == '\t'; line++) {
	continue;
    }

    /*
     * Find what type of if we're dealing with. The result is left
     * in ifp and isElse is set TRUE if it's an elif line.
     */
    if (line[0] == 'e' && line[1] == 'l') {
	line += 2;
	isElse = TRUE;
    } else if (istoken(line, "endif", 5)) {
	/*
	 * End of a conditional section. If skipIfLevel is non-zero, that
	 * conditional was skipped, so lines following it should also be
	 * skipped. Hence, we return COND_SKIP. Otherwise, the conditional
	 * was read so succeeding lines should be parsed (think about it...)
	 * so we return COND_PARSE, unless this endif isn't paired with
	 * a decent if.
	 */
	finalElse[condTop][skipIfLevel] = FALSE;
	if (skipIfLevel != 0) {
	    skipIfLevel -= 1;
	    return (COND_SKIP);
	} else {
	    if (condTop == MAXIF) {
		Parse_Error(level, "if-less endif");
		return (COND_INVALID);
	    } else {
		skipLine = FALSE;
		condTop += 1;
		return (COND_PARSE);
	    }
	}
    } else {
	isElse = FALSE;
    }

    /*
     * Figure out what sort of conditional it is -- what its default
     * function is, etc. -- by looking in the table of valid "ifs"
     */
    for (ifp = ifs; ifp->form != (char *)0; ifp++) {
	if (istoken(ifp->form, line, ifp->formlen)) {
	    break;
	}
    }

    if (ifp->form == (char *) 0) {
	/*
	 * Nothing fit. If the first word on the line is actually
	 * "else", it's a valid conditional whose value is the inverse
	 * of the previous if we parsed.
	 */
	if (isElse && istoken(line, "se", 2)) {
	    if (finalElse[condTop][skipIfLevel]) {
		Parse_Error(PARSE_WARNING, "extra else");
	    } else {
		finalElse[condTop][skipIfLevel] = TRUE;
	    }
	    if (condTop == MAXIF) {
		Parse_Error(level, "if-less else");
		return (COND_INVALID);
	    } else if (skipIfLevel == 0) {
		value = !condStack[condTop];
	    } else {
		return (COND_SKIP);
	    }
	} else {
	    /*
	     * Not a valid conditional type. No error...
	     */
	    return (COND_INVALID);
	}
    } else {
	if (isElse) {
	    if (condTop == MAXIF) {
		Parse_Error(level, "if-less elif");
		return (COND_INVALID);
	    } else if (skipIfLevel != 0) {
		/*
		 * If skipping this conditional, just ignore the whole thing.
		 * If we don't, the user might be employing a variable that's
		 * undefined, for which there's an enclosing ifdef that
		 * we're skipping...
		 */
		return(COND_SKIP);
	    }
	} else if (skipLine) {
	    /*
	     * Don't even try to evaluate a conditional that's not an else if
	     * we're skipping things...
	     */
	    skipIfLevel += 1;
	    if (skipIfLevel >= MAXIF) {
		Parse_Error(PARSE_FATAL, "Too many nested if's. %d max.", MAXIF);
		return (COND_INVALID);
	    }
	    finalElse[condTop][skipIfLevel] = FALSE;
	    return(COND_SKIP);
	}

	/*
	 * Initialize file-global variables for parsing
	 */
	condDefProc = ifp->defProc;
	condInvert = ifp->doNot;

	line += ifp->formlen;
	if (Cond_EvalExpression(0, line, &value, 1) == COND_INVALID)
		return COND_INVALID;
    }
    if (!isElse) {
	condTop -= 1;
	finalElse[condTop][skipIfLevel] = FALSE;
    } else if ((skipIfLevel != 0) || condStack[condTop]) {
	/*
	 * If this is an else-type conditional, it should only take effect
	 * if its corresponding if was evaluated and FALSE. If its if was
	 * TRUE or skipped, we return COND_SKIP (and start skipping in case
	 * we weren't already), leaving the stack unmolested so later elif's
	 * don't screw up...
	 */
	skipLine = TRUE;
	return (COND_SKIP);
    }

    if (condTop < 0) {
	/*
	 * This is the one case where we can definitely proclaim a fatal
	 * error. If we don't, we're hosed.
	 */
	Parse_Error(PARSE_FATAL, "Too many nested if's. %d max.", MAXIF);
	return (COND_INVALID);
    } else {
	condStack[condTop] = value;
	skipLine = !value;
	return (value ? COND_PARSE : COND_SKIP);
    }
}



/*-
 *-----------------------------------------------------------------------
 * Cond_End --
 *	Make sure everything's clean at the end of a makefile.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Parse_Error will be called if open conditionals are around.
 *
 *-----------------------------------------------------------------------
 */
void
Cond_End(void)
{
    if (condTop != MAXIF) {
	Parse_Error(PARSE_FATAL, "%d open conditional%s", MAXIF-condTop,
		    MAXIF-condTop == 1 ? "" : "s");
    }
    condTop = MAXIF;
}
/* end cond.c */

/* begin dir.c */
/*	$NetBSD: dir.c,v 1.45 2005/02/16 15:11:52 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: dir.c,v 1.45 2005/02/16 15:11:52 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)dir.c	8.2 (Berkeley) 1/2/94";
#else
__RCSID("$NetBSD: dir.c,v 1.45 2005/02/16 15:11:52 christos Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * dir.c --
 *	Directory searching using wildcards and/or normal names...
 *	Used both for source wildcarding in the Makefile and for finding
 *	implicit sources.
 *
 * The interface for this module is:
 *	Dir_Init  	    Initialize the module.
 *
 *	Dir_InitCur	    Set the cur Path.
 *
 *	Dir_InitDot	    Set the dot Path.
 *
 *	Dir_End  	    Cleanup the module.
 *
 *	Dir_SetPATH	    Set ${.PATH} to reflect state of dirSearchPath.
 *
 *	Dir_HasWildcards    Returns TRUE if the name given it needs to
 *	    	  	    be wildcard-expanded.
 *
 *	Dir_Expand	    Given a pattern and a path, return a Lst of names
 *	    	  	    which match the pattern on the search path.
 *
 *	Dir_FindFile	    Searches for a file on a given search path.
 *	    	  	    If it exists, the entire path is returned.
 *	    	  	    Otherwise NULL is returned.
 *
 *	Dir_FindHereOrAbove Search for a path in the current directory and
 *			    then all the directories above it in turn until
 *			    the path is found or we reach the root ("/").
 *
 *	Dir_MTime 	    Return the modification time of a node. The file
 *	    	  	    is searched for along the default search path.
 *	    	  	    The path and mtime fields of the node are filled
 *	    	  	    in.
 *
 *	Dir_AddDir	    Add a directory to a search path.
 *
 *	Dir_MakeFlags	    Given a search path and a command flag, create
 *	    	  	    a string with each of the directories in the path
 *	    	  	    preceded by the command flag and all of them
 *	    	  	    separated by a space.
 *
 *	Dir_Destroy	    Destroy an element of a search path. Frees up all
 *	    	  	    things that can be freed for the element as long
 *	    	  	    as the element is no longer referenced by any other
 *	    	  	    search path.
 *	Dir_ClearPath	    Resets a search path to the empty list.
 *
 * For debugging:
 *	Dir_PrintDirectories	Print stats about the directory cache.
 */

/* <<dir.c includes>> */

/*
 *	A search path consists of a Lst of Path structures. A Path structure
 *	has in it the name of the directory and a hash table of all the files
 *	in the directory. This is used to cut down on the number of system
 *	calls necessary to find implicit dependents and their like. Since
 *	these searches are made before any actions are taken, we need not
 *	worry about the directory changing due to creation commands. If this
 *	hampers the style of some makefiles, they must be changed.
 *
 *	A list of all previously-read directories is kept in the
 *	openDirectories Lst. This list is checked first before a directory
 *	is opened.
 *
 *	The need for the caching of whole directories is brought about by
 *	the multi-level transformation code in suff.c, which tends to search
 *	for far more files than regular make does. In the initial
 *	implementation, the amount of time spent performing "stat" calls was
 *	truly astronomical. The problem with hashing at the start is,
 *	of course, that pmake doesn't then detect changes to these directories
 *	during the course of the make. Three possibilities suggest themselves:
 *
 *	    1) just use stat to test for a file's existence. As mentioned
 *	       above, this is very inefficient due to the number of checks
 *	       engendered by the multi-level transformation code.
 *	    2) use readdir() and company to search the directories, keeping
 *	       them open between checks. I have tried this and while it
 *	       didn't slow down the process too much, it could severely
 *	       affect the amount of parallelism available as each directory
 *	       open would take another file descriptor out of play for
 *	       handling I/O for another job. Given that it is only recently
 *	       that UNIX OS's have taken to allowing more than 20 or 32
 *	       file descriptors for a process, this doesn't seem acceptable
 *	       to me.
 *	    3) record the mtime of the directory in the Path structure and
 *	       verify the directory hasn't changed since the contents were
 *	       hashed. This will catch the creation or deletion of files,
 *	       but not the updating of files. However, since it is the
 *	       creation and deletion that is the problem, this could be
 *	       a good thing to do. Unfortunately, if the directory (say ".")
 *	       were fairly large and changed fairly frequently, the constant
 *	       rehashing could seriously degrade performance. It might be
 *	       good in such cases to keep track of the number of rehashes
 *	       and if the number goes over a (small) limit, resort to using
 *	       stat in its place.
 *
 *	An additional thing to consider is that pmake is used primarily
 *	to create C programs and until recently pcc-based compilers refused
 *	to allow you to specify where the resulting object file should be
 *	placed. This forced all objects to be created in the current
 *	directory. This isn't meant as a full excuse, just an explanation of
 *	some of the reasons for the caching used here.
 *
 *	One more note: the location of a target's file is only performed
 *	on the downward traversal of the graph and then only for terminal
 *	nodes in the graph. This could be construed as wrong in some cases,
 *	but prevents inadvertent modification of files when the "installed"
 *	directory for a file is provided in the search path.
 *
 *	Another data structure maintained by this module is an mtime
 *	cache used when the searching of cached directories fails to find
 *	a file. In the past, Dir_FindFile would simply perform an access()
 *	call in such a case to determine if the file could be found using
 *	just the name given. When this hit, however, all that was gained
 *	was the knowledge that the file existed. Given that an access() is
 *	essentially a stat() without the copyout() call, and that the same
 *	filesystem overhead would have to be incurred in Dir_MTime, it made
 *	sense to replace the access() with a stat() and record the mtime
 *	in a cache for when Dir_MTime was actually called.
 */

Lst          dirSearchPath;	/* main search path */

static Lst   openDirectories;	/* the list of all open directories */

/*
 * Variables for gathering statistics on the efficiency of the hashing
 * mechanism.
 */
static int    hits,	      /* Found in directory cache */
	      misses,	      /* Sad, but not evil misses */
	      nearmisses,     /* Found under search path */
	      bigmisses;      /* Sought by itself */

static Path    	  *dot;	    /* contents of current directory */
static Path    	  *cur;	    /* contents of current directory, if not dot */
static Path	  *dotLast; /* a fake path entry indicating we need to
			     * look for . last */
static Hash_Table mtimes;   /* Results of doing a last-resort stat in
			     * Dir_FindFile -- if we have to go to the
			     * system to find the file, we might as well
			     * have its mtime on record. XXX: If this is done
			     * way early, there's a chance other rules will
			     * have already updated the file, in which case
			     * we'll update it again. Generally, there won't
			     * be two rules to update a single file, so this
			     * should be ok, but... */


static int DirFindName(ClientData, ClientData);
static int DirMatchFiles(const char *, Path *, Lst);
static void DirExpandCurly(const char *, const char *, Lst, Lst);
static void DirExpandInt(const char *, Lst, Lst);
static int DirPrintWord(ClientData, ClientData);
static int DirPrintDir(ClientData, ClientData);
static char *DirLookup(Path *, const char *, const char *, Boolean);
static char *DirLookupSubdir(Path *, const char *);
static char *DirFindDot(Boolean, const char *, const char *);
static char *DirLookupAbs(Path *, const char *, const char *);

/*-
 *-----------------------------------------------------------------------
 * Dir_Init --
 *	initialize things for this module
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	some directories may be opened.
 *-----------------------------------------------------------------------
 */
void
Dir_Init(const char *cdname)
{
    dirSearchPath = Lst_Init(FALSE);
    openDirectories = Lst_Init(FALSE);
    Hash_InitTable(&mtimes, 0);

    Dir_InitCur(cdname);

    dotLast = emalloc(sizeof(Path));
    dotLast->refCount = 1;
    dotLast->hits = 0;
    dotLast->name = estrdup(".DOTLAST");
    Hash_InitTable(&dotLast->files, -1);
}

/*
 * Called by Dir_Init() and whenever .CURDIR is assigned to.
 */
void
Dir_InitCur(const char *cdname)
{
    Path *p;

    if (cdname != NULL) {
	/*
	 * Our build directory is not the same as our source directory.
	 * Keep this one around too.
	 */
	if ((p = Dir_AddDir(NULL, cdname))) {
	    p->refCount += 1;
	    if (cur && cur != p) {
		/*
		 * We've been here before, cleanup.
		 */
		cur->refCount -= 1;
		Dir_Destroy((ClientData) cur);
	    }
	    cur = p;
	}
    }
}

/*-
 *-----------------------------------------------------------------------
 * Dir_InitDot --
 *	(re)initialize "dot" (current/object directory) path hash
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	some directories may be opened.
 *-----------------------------------------------------------------------
 */
void
Dir_InitDot(void)
{
    if (dot != NULL) {
	LstNode ln;

	/* Remove old entry from openDirectories, but do not destroy. */
	ln = Lst_Member(openDirectories, (ClientData)dot);
	(void) Lst_Remove(openDirectories, ln);
    }

    dot = Dir_AddDir(NULL, ".");

    if (dot == NULL) {
	Error("Cannot open `.' (%s)", strerror(errno));
	exit(1);
    }

    /*
     * We always need to have dot around, so we increment its reference count
     * to make sure it's not destroyed.
     */
    dot->refCount += 1;
    Dir_SetPATH();			/* initialize */
}

/*-
 *-----------------------------------------------------------------------
 * Dir_End --
 *	cleanup things for this module
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	none
 *-----------------------------------------------------------------------
 */
void
Dir_End(void)
{
#ifdef CLEANUP
    if (cur) {
	cur->refCount -= 1;
	Dir_Destroy((ClientData) cur);
    }
    dot->refCount -= 1;
    dotLast->refCount -= 1;
    Dir_Destroy((ClientData) dotLast);
    Dir_Destroy((ClientData) dot);
    Dir_ClearPath(dirSearchPath);
    Lst_Destroy(dirSearchPath, NOFREE);
    Dir_ClearPath(openDirectories);
    Lst_Destroy(openDirectories, NOFREE);
    Hash_DeleteTable(&mtimes);
#endif
}

/*
 * We want ${.PATH} to indicate the order in which we will actually
 * search, so we rebuild it after any .PATH: target.
 * This is the simplest way to deal with the effect of .DOTLAST.
 */
void
Dir_SetPATH(void)
{
    LstNode       ln;		/* a list element */
    Path *p;
    Boolean	  hasLastDot = FALSE;	/* true we should search dot last */

    Var_Delete(".PATH", VAR_GLOBAL);

    if (Lst_Open(dirSearchPath) == SUCCESS) {
	if ((ln = Lst_First(dirSearchPath)) != NILLNODE) {
	    p = (Path *) Lst_Datum(ln);
	    if (p == dotLast) {
		hasLastDot = TRUE;
		Var_Append(".PATH", dotLast->name, VAR_GLOBAL);
	    }
	}

	if (!hasLastDot) {
	    if (dot)
		Var_Append(".PATH", dot->name, VAR_GLOBAL);
	    if (cur)
		Var_Append(".PATH", cur->name, VAR_GLOBAL);
	}

	while ((ln = Lst_Next(dirSearchPath)) != NILLNODE) {
	    p = (Path *) Lst_Datum(ln);
	    if (p == dotLast)
		continue;
	    if (p == dot && hasLastDot)
		continue;
	    Var_Append(".PATH", p->name, VAR_GLOBAL);
	}

	if (hasLastDot) {
	    if (dot)
		Var_Append(".PATH", dot->name, VAR_GLOBAL);
	    if (cur)
		Var_Append(".PATH", cur->name, VAR_GLOBAL);
	}
	Lst_Close(dirSearchPath);
    }
}

/*-
 *-----------------------------------------------------------------------
 * DirFindName --
 *	See if the Path structure describes the same directory as the
 *	given one by comparing their names. Called from Dir_AddDir via
 *	Lst_Find when searching the list of open directories.
 *
 * Input:
 *	p		Current name
 *	dname		Desired name
 *
 * Results:
 *	0 if it is the same. Non-zero otherwise
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static int
DirFindName(ClientData p, ClientData dname)
{
    return (strcmp (((Path *)p)->name, (char *) dname));
}

/*-
 *-----------------------------------------------------------------------
 * Dir_HasWildcards  --
 *	see if the given name has any wildcard characters in it
 *	be careful not to expand unmatching brackets or braces.
 *	XXX: This code is not 100% correct. ([^]] fails etc.)
 *	I really don't think that make(1) should be expanding
 *	patterns, because then you have to set a mechanism for
 *	escaping the expansion!
 *
 * Input:
 *	name		name to check
 *
 * Results:
 *	returns TRUE if the word should be expanded, FALSE otherwise
 *
 * Side Effects:
 *	none
 *-----------------------------------------------------------------------
 */
Boolean
Dir_HasWildcards(char *name)
{
    char *cp;
    int wild = 0, brace = 0, bracket = 0;

    for (cp = name; *cp; cp++) {
	switch(*cp) {
	case '{':
		brace++;
		wild = 1;
		break;
	case '}':
		brace--;
		break;
	case '[':
		bracket++;
		wild = 1;
		break;
	case ']':
		bracket--;
		break;
	case '?':
	case '*':
		wild = 1;
		break;
	default:
		break;
	}
    }
    return wild && bracket == 0 && brace == 0;
}

/*-
 *-----------------------------------------------------------------------
 * DirMatchFiles --
 * 	Given a pattern and a Path structure, see if any files
 *	match the pattern and add their names to the 'expansions' list if
 *	any do. This is incomplete -- it doesn't take care of patterns like
 *	src / *src / *.c properly (just *.c on any of the directories), but it
 *	will do for now.
 *
 * Input:
 *	pattern		Pattern to look for
 *	p		Directory to search
 *	expansion	Place to store the results
 *
 * Results:
 *	Always returns 0
 *
 * Side Effects:
 *	File names are added to the expansions lst. The directory will be
 *	fully hashed when this is done.
 *-----------------------------------------------------------------------
 */
static int
DirMatchFiles(const char *pattern, Path *p, Lst expansions)
{
    Hash_Search	  search;   	/* Index into the directory's table */
    Hash_Entry	  *entry;   	/* Current entry in the table */
    Boolean 	  isDot;    	/* TRUE if the directory being searched is . */

    isDot = (*p->name == '.' && p->name[1] == '\0');

    for (entry = Hash_EnumFirst(&p->files, &search);
	 entry != (Hash_Entry *)NULL;
	 entry = Hash_EnumNext(&search))
    {
	/*
	 * See if the file matches the given pattern. Note we follow the UNIX
	 * convention that dot files will only be found if the pattern
	 * begins with a dot (note also that as a side effect of the hashing
	 * scheme, .* won't match . or .. since they aren't hashed).
	 */
	if (Str_Match(entry->name, pattern) &&
	    ((entry->name[0] != '.') ||
	     (pattern[0] == '.')))
	{
	    (void)Lst_AtEnd(expansions,
			    (isDot ? estrdup(entry->name) :
			     str_concat(p->name, entry->name,
					STR_ADDSLASH)));
	}
    }
    return (0);
}

/*-
 *-----------------------------------------------------------------------
 * DirExpandCurly --
 *	Expand curly braces like the C shell. Does this recursively.
 *	Note the special case: if after the piece of the curly brace is
 *	done there are no wildcard characters in the result, the result is
 *	placed on the list WITHOUT CHECKING FOR ITS EXISTENCE.
 *
 * Input:
 *	word		Entire word to expand
 *	brace		First curly brace in it
 *	path		Search path to use
 *	expansions	Place to store the expansions
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The given list is filled with the expansions...
 *
 *-----------------------------------------------------------------------
 */
static void
DirExpandCurly(const char *word, const char *brace, Lst path, Lst expansions)
{
    const char   *end;	    	/* Character after the closing brace */
    const char   *cp;	    	/* Current position in brace clause */
    const char   *start;   	/* Start of current piece of brace clause */
    int	    	  bracelevel;	/* Number of braces we've seen. If we see a
				 * right brace when this is 0, we've hit the
				 * end of the clause. */
    char    	 *file;    	/* Current expansion */
    int	    	  otherLen; 	/* The length of the other pieces of the
				 * expansion (chars before and after the
				 * clause in 'word') */
    char    	 *cp2;	    	/* Pointer for checking for wildcards in
				 * expansion before calling Dir_Expand */

    start = brace+1;

    /*
     * Find the end of the brace clause first, being wary of nested brace
     * clauses.
     */
    for (end = start, bracelevel = 0; *end != '\0'; end++) {
	if (*end == '{') {
	    bracelevel++;
	} else if ((*end == '}') && (bracelevel-- == 0)) {
	    break;
	}
    }
    if (*end == '\0') {
	Error("Unterminated {} clause \"%s\"", start);
	return;
    } else {
	end++;
    }
    otherLen = brace - word + strlen(end);

    for (cp = start; cp < end; cp++) {
	/*
	 * Find the end of this piece of the clause.
	 */
	bracelevel = 0;
	while (*cp != ',') {
	    if (*cp == '{') {
		bracelevel++;
	    } else if ((*cp == '}') && (bracelevel-- <= 0)) {
		break;
	    }
	    cp++;
	}
	/*
	 * Allocate room for the combination and install the three pieces.
	 */
	file = emalloc(otherLen + cp - start + 1);
	if (brace != word) {
	    strncpy(file, word, brace-word);
	}
	if (cp != start) {
	    strncpy(&file[brace-word], start, cp-start);
	}
	strcpy(&file[(brace-word)+(cp-start)], end);

	/*
	 * See if the result has any wildcards in it. If we find one, call
	 * Dir_Expand right away, telling it to place the result on our list
	 * of expansions.
	 */
	for (cp2 = file; *cp2 != '\0'; cp2++) {
	    switch(*cp2) {
	    case '*':
	    case '?':
	    case '{':
	    case '[':
		Dir_Expand(file, path, expansions);
		goto next;
	    }
	}
	if (*cp2 == '\0') {
	    /*
	     * Hit the end w/o finding any wildcards, so stick the expansion
	     * on the end of the list.
	     */
	    (void)Lst_AtEnd(expansions, file);
	} else {
	next:
	    free(file);
	}
	start = cp+1;
    }
}


/*-
 *-----------------------------------------------------------------------
 * DirExpandInt --
 *	Internal expand routine. Passes through the directories in the
 *	path one by one, calling DirMatchFiles for each. NOTE: This still
 *	doesn't handle patterns in directories...
 *
 * Input:
 *	word		Word to expand
 *	path		Path on which to look
 *	expansions	Place to store the result
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Things are added to the expansions list.
 *
 *-----------------------------------------------------------------------
 */
static void
DirExpandInt(const char *word, Lst path, Lst expansions)
{
    LstNode 	  ln;	    	/* Current node */
    Path	  *p;	    	/* Directory in the node */

    if (Lst_Open(path) == SUCCESS) {
	while ((ln = Lst_Next(path)) != NILLNODE) {
	    p = (Path *)Lst_Datum(ln);
	    DirMatchFiles(word, p, expansions);
	}
	Lst_Close(path);
    }
}

/*-
 *-----------------------------------------------------------------------
 * DirPrintWord --
 *	Print a word in the list of expansions. Callback for Dir_Expand
 *	when DEBUG(DIR), via Lst_ForEach.
 *
 * Results:
 *	=== 0
 *
 * Side Effects:
 *	The passed word is printed, followed by a space.
 *
 *-----------------------------------------------------------------------
 */
static int
DirPrintWord(ClientData word, ClientData dummy)
{
    printf("%s ", (char *) word);

    return(dummy ? 0 : 0);
}

/*-
 *-----------------------------------------------------------------------
 * Dir_Expand  --
 *	Expand the given word into a list of words by globbing it looking
 *	in the directories on the given search path.
 *
 * Input:
 *	word		the word to expand
 *	path		the list of directories in which to find the
 *			resulting files
 *	expansions	the list on which to place the results
 *
 * Results:
 *	A list of words consisting of the files which exist along the search
 *	path matching the given pattern.
 *
 * Side Effects:
 *	Directories may be opened. Who knows?
 *-----------------------------------------------------------------------
 */
void
Dir_Expand(const char *word, Lst path, Lst expansions)
{
    const char    	  *cp;

    if (DEBUG(DIR)) {
	printf("Expanding \"%s\"... ", word);
    }

    cp = strchr(word, '{');
    if (cp) {
	DirExpandCurly(word, cp, path, expansions);
    } else {
	cp = strchr(word, '/');
	if (cp) {
	    /*
	     * The thing has a directory component -- find the first wildcard
	     * in the string.
	     */
	    for (cp = word; *cp; cp++) {
		if (*cp == '?' || *cp == '[' || *cp == '*' || *cp == '{') {
		    break;
		}
	    }
	    if (*cp == '{') {
		/*
		 * This one will be fun.
		 */
		DirExpandCurly(word, cp, path, expansions);
		return;
	    } else if (*cp != '\0') {
		/*
		 * Back up to the start of the component
		 */
		char  *dirpath;

		while (cp > word && *cp != '/') {
		    cp--;
		}
		if (cp != word) {
		    char sc;
		    /*
		     * If the glob isn't in the first component, try and find
		     * all the components up to the one with a wildcard.
		     */
		    sc = cp[1];
		    ((char *)UNCONST(cp))[1] = '\0';
		    dirpath = Dir_FindFile(word, path);
		    ((char *)UNCONST(cp))[1] = sc;
		    /*
		     * dirpath is null if can't find the leading component
		     * XXX: Dir_FindFile won't find internal components.
		     * i.e. if the path contains ../Etc/Object and we're
		     * looking for Etc, it won't be found. Ah well.
		     * Probably not important.
		     */
		    if (dirpath != (char *)NULL) {
			char *dp = &dirpath[strlen(dirpath) - 1];
			if (*dp == '/')
			    *dp = '\0';
			path = Lst_Init(FALSE);
			(void) Dir_AddDir(path, dirpath);
			DirExpandInt(cp+1, path, expansions);
			Lst_Destroy(path, NOFREE);
		    }
		} else {
		    /*
		     * Start the search from the local directory
		     */
		    DirExpandInt(word, path, expansions);
		}
	    } else {
		/*
		 * Return the file -- this should never happen.
		 */
		DirExpandInt(word, path, expansions);
	    }
	} else {
	    /*
	     * First the files in dot
	     */
	    DirMatchFiles(word, dot, expansions);

	    /*
	     * Then the files in every other directory on the path.
	     */
	    DirExpandInt(word, path, expansions);
	}
    }
    if (DEBUG(DIR)) {
	Lst_ForEach(expansions, DirPrintWord, (ClientData) 0);
	fputc('\n', stdout);
    }
}

/*-
 *-----------------------------------------------------------------------
 * DirLookup  --
 *	Find if the file with the given name exists in the given path.
 *
 * Results:
 *	The path to the file or NULL. This path is guaranteed to be in a
 *	different part of memory than name and so may be safely free'd.
 *
 * Side Effects:
 *	None.
 *-----------------------------------------------------------------------
 */
static char *
DirLookup(Path *p, const char *name __unused, const char *cp,
          Boolean hasSlash __unused)
{
    char *file;		/* the current filename to check */

    if (DEBUG(DIR)) {
	printf("   %s ...\n", p->name);
    }

    if (Hash_FindEntry(&p->files, cp) == (Hash_Entry *)NULL)
	return NULL;

    file = str_concat(p->name, cp, STR_ADDSLASH);
    if (DEBUG(DIR)) {
	printf("   returning %s\n", file);
    }
    p->hits += 1;
    hits += 1;
    return file;
}


/*-
 *-----------------------------------------------------------------------
 * DirLookupSubdir  --
 *	Find if the file with the given name exists in the given path.
 *
 * Results:
 *	The path to the file or NULL. This path is guaranteed to be in a
 *	different part of memory than name and so may be safely free'd.
 *
 * Side Effects:
 *	If the file is found, it is added in the modification times hash
 *	table.
 *-----------------------------------------------------------------------
 */
static char *
DirLookupSubdir(Path *p, const char *name)
{
    struct stat	  stb;		/* Buffer for stat, if necessary */
    Hash_Entry	 *entry;	/* Entry for mtimes table */
    char 	 *file;		/* the current filename to check */

    if (p != dot) {
	file = str_concat(p->name, name, STR_ADDSLASH);
    } else {
	/*
	 * Checking in dot -- DON'T put a leading ./ on the thing.
	 */
	file = estrdup(name);
    }

    if (DEBUG(DIR)) {
	printf("checking %s ...\n", file);
    }

    if (stat (file, &stb) == 0) {
	/*
	 * Save the modification time so if it's needed, we don't have
	 * to fetch it again.
	 */
	if (DEBUG(DIR)) {
	    printf("   Caching %s for %s\n", Targ_FmtTime(stb.st_mtime),
		    file);
	}
	entry = Hash_CreateEntry(&mtimes, (char *) file,
				 (Boolean *)NULL);
	Hash_SetValue(entry, (long)stb.st_mtime);
	nearmisses += 1;
	return (file);
    }
    free (file);
    return NULL;
}

/*-
 *-----------------------------------------------------------------------
 * DirLookupAbs  --
 *	Find if the file with the given name exists in the given path.
 *
 * Results:
 *	The path to the file, the empty string or NULL. If the file is
 *	the empty string, the search should be terminated.
 *	This path is guaranteed to be in a different part of memory
 *	than name and so may be safely free'd.
 *
 * Side Effects:
 *	None.
 *-----------------------------------------------------------------------
 */
static char *
DirLookupAbs(Path *p, const char *name, const char *cp)
{
	char *p1;		/* pointer into p->name */
	const char *p2;		/* pointer into name */

	if (DEBUG(DIR)) {
		printf("   %s ...\n", p->name);
	}

	/*
	 * If the file has a leading path component and that component
	 * exactly matches the entire name of the current search
	 * directory, we can attempt another cache lookup. And if we don't
	 * have a hit, we can safely assume the file does not exist at all.
	 */
	for (p1 = p->name, p2 = name; *p1 && *p1 == *p2; p1++, p2++) {
		continue;
	}
	if (*p1 != '\0' || p2 != cp - 1) {
		return NULL;
	}

	if (Hash_FindEntry(&p->files, cp) == (Hash_Entry *)NULL) {
		if (DEBUG(DIR)) {
			printf("   must be here but isn't -- returning\n");
		}
		/* Return empty string: terminates search */
		return estrdup("");
	}

	p->hits += 1;
	hits += 1;
	if (DEBUG(DIR)) {
		printf("   returning %s\n", name);
	}
	return (estrdup(name));
}

/*-
 *-----------------------------------------------------------------------
 * DirFindDot  --
 *	Find the file given on "." or curdir
 *
 * Results:
 *	The path to the file or NULL. This path is guaranteed to be in a
 *	different part of memory than name and so may be safely free'd.
 *
 * Side Effects:
 *	Hit counts change
 *-----------------------------------------------------------------------
 */
static char *
DirFindDot(Boolean hasSlash __unused, const char *name, const char *cp)
{

	if (Hash_FindEntry(&dot->files, cp) != (Hash_Entry *)NULL) {
	    if (DEBUG(DIR)) {
		printf("   in '.'\n");
	    }
	    hits += 1;
	    dot->hits += 1;
	    return (estrdup(name));
	}
	if (cur &&
	    Hash_FindEntry(&cur->files, cp) != (Hash_Entry *)NULL) {
	    if (DEBUG(DIR)) {
		printf("   in ${.CURDIR} = %s\n", cur->name);
	    }
	    hits += 1;
	    cur->hits += 1;
	    return str_concat(cur->name, cp, STR_ADDSLASH);
	}

	return NULL;
}

/*-
 *-----------------------------------------------------------------------
 * Dir_FindFile  --
 *	Find the file with the given name along the given search path.
 *
 * Input:
 *	name		the file to find
 *	path		the Lst of directories to search
 *
 * Results:
 *	The path to the file or NULL. This path is guaranteed to be in a
 *	different part of memory than name and so may be safely free'd.
 *
 * Side Effects:
 *	If the file is found in a directory which is not on the path
 *	already (either 'name' is absolute or it is a relative path
 *	[ dir1/.../dirn/file ] which exists below one of the directories
 *	already on the search path), its directory is added to the end
 *	of the path on the assumption that there will be more files in
 *	that directory later on. Sometimes this is true. Sometimes not.
 *-----------------------------------------------------------------------
 */
char *
Dir_FindFile(const char *name, Lst path)
{
    LstNode       ln;			/* a list element */
    char	  *file;		/* the current filename to check */
    Path	  *p;			/* current path member */
    const char	  *cp;			/* index of first slash, if any */
    Boolean	  hasLastDot = FALSE;	/* true we should search dot last */
    Boolean	  hasSlash;		/* true if 'name' contains a / */
    struct stat	  stb;			/* Buffer for stat, if necessary */
    Hash_Entry	  *entry;		/* Entry for mtimes table */

    /*
     * Find the final component of the name and note whether it has a
     * slash in it (the name, I mean)
     */
    cp = strrchr (name, '/');
    if (cp) {
	hasSlash = TRUE;
	cp += 1;
    } else {
	hasSlash = FALSE;
	cp = name;
    }

    if (DEBUG(DIR)) {
	printf("Searching for %s ...", name);
    }

    if (Lst_Open(path) == FAILURE) {
	if (DEBUG(DIR)) {
	    printf("couldn't open path, file not found\n");
	}
	misses += 1;
	return ((char *) NULL);
    }

    if ((ln = Lst_First(path)) != NILLNODE) {
	p = (Path *) Lst_Datum(ln);
	if (p == dotLast) {
	    hasLastDot = TRUE;
            if (DEBUG(DIR))
		printf("[dot last]...");
	}
    }
    if (DEBUG(DIR)) {
	printf("\n");
    }

    /*
     * If there's no leading directory components or if the leading
     * directory component is exactly `./', consult the cached contents
     * of each of the directories on the search path.
     */
    if ((!hasSlash || (cp - name == 2 && *name == '.'))) {
	    /*
	     * We look through all the directories on the path seeking one which
	     * contains the final component of the given name.  If such a beast
	     * is found, we concatenate the directory name and the final
	     * component and return the resulting string. If we don't find any
	     * such thing, we go on to phase two...
	     *
	     * No matter what, we always look for the file in the current
	     * directory before anywhere else (unless we found the magic
	     * DOTLAST path, in which case we search it last) and we *do not*
	     * add the ./ to it if it exists.
	     * This is so there are no conflicts between what the user
	     * specifies (fish.c) and what pmake finds (./fish.c).
	     */
	    if (!hasLastDot &&
			(file = DirFindDot(hasSlash, name, cp)) != NULL) {
		    Lst_Close(path);
		    return file;
	    }

	    while ((ln = Lst_Next(path)) != NILLNODE) {
		p = (Path *) Lst_Datum(ln);
		if (p == dotLast)
		    continue;
		if ((file = DirLookup(p, name, cp, hasSlash)) != NULL) {
		    Lst_Close(path);
			return file;
		}
	    }

	    if (hasLastDot &&
			(file = DirFindDot(hasSlash, name, cp)) != NULL) {
		    Lst_Close(path);
		    return file;
	    }
    }
    Lst_Close(path);

    /*
     * We didn't find the file on any directory in the search path.
     * If the name doesn't contain a slash, that means it doesn't exist.
     * If it *does* contain a slash, however, there is still hope: it
     * could be in a subdirectory of one of the members of the search
     * path. (eg. /usr/include and sys/types.h. The above search would
     * fail to turn up types.h in /usr/include, but it *is* in
     * /usr/include/sys/types.h).
     * [ This no longer applies: If we find such a beast, we assume there
     * will be more (what else can we assume?) and add all but the last
     * component of the resulting name onto the search path (at the
     * end).]
     * This phase is only performed if the file is *not* absolute.
     */
    if (!hasSlash) {
	if (DEBUG(DIR)) {
	    printf("   failed.\n");
	}
	misses += 1;
	return ((char *) NULL);
    }

    if (name[0] != '/') {
	Boolean	checkedDot = FALSE;

	if (DEBUG(DIR)) {
	    printf("   Trying subdirectories...\n");
	}

	if (!hasLastDot) {
		if (dot) {
			checkedDot = TRUE;
			if ((file = DirLookupSubdir(dot, name)) != NULL)
				return file;
		}
		if (cur && (file = DirLookupSubdir(cur, name)) != NULL)
			return file;
	}

	(void) Lst_Open(path);
	while ((ln = Lst_Next(path)) != NILLNODE) {
	    p = (Path *) Lst_Datum(ln);
	    if (p == dotLast)
		continue;
	    if (p == dot) {
		    if (checkedDot)
			    continue;
		checkedDot = TRUE;
	    }
	    if ((file = DirLookupSubdir(p, name)) != NULL) {
		Lst_Close(path);
		return file;
	    }
	}
	Lst_Close(path);

	if (hasLastDot) {
		if (dot && !checkedDot) {
			checkedDot = TRUE;
			if ((file = DirLookupSubdir(dot, name)) != NULL)
				return file;
		}
		if (cur && (file = DirLookupSubdir(cur, name)) != NULL)
			return file;
	}

	if (checkedDot) {
	    /*
	     * Already checked by the given name, since . was in the path,
	     * so no point in proceeding...
	     */
	    if (DEBUG(DIR)) {
		printf("   Checked . already, returning NULL\n");
	    }
	    return(NULL);
	}

    } else { /* name[0] == '/' */

	/*
	 * For absolute names, compare directory path prefix against the
	 * the directory path of each member on the search path for an exact
	 * match. If we have an exact match on any member of the search path,
	 * use the cached contents of that member to lookup the final file
	 * component. If that lookup fails we can safely assume that the
	 * file does not exist at all.  This is signified by DirLookupAbs()
	 * returning an empty string.
	 */
	if (DEBUG(DIR)) {
	    printf("   Trying exact path matches...\n");
	}

	if (!hasLastDot && cur && (file = DirLookupAbs(cur, name, cp)) != NULL)
	    return *file?file:NULL;

	(void) Lst_Open(path);
	while ((ln = Lst_Next(path)) != NILLNODE) {
	    p = (Path *) Lst_Datum(ln);
	    if (p == dotLast)
		continue;
	    if ((file = DirLookupAbs(p, name, cp)) != NULL) {
		Lst_Close(path);
		return *file?file:NULL;
	    }
	}
	Lst_Close(path);

	if (hasLastDot && cur && (file = DirLookupAbs(cur, name, cp)) != NULL)
	    return *file?file:NULL;
    }

    /*
     * Didn't find it that way, either. Sigh. Phase 3. Add its directory
     * onto the search path in any case, just in case, then look for the
     * thing in the hash table. If we find it, grand. We return a new
     * copy of the name. Otherwise we sadly return a NULL pointer. Sigh.
     * Note that if the directory holding the file doesn't exist, this will
     * do an extra search of the final directory on the path. Unless something
     * weird happens, this search won't succeed and life will be groovy.
     *
     * Sigh. We cannot add the directory onto the search path because
     * of this amusing case:
     * $(INSTALLDIR)/$(FILE): $(FILE)
     *
     * $(FILE) exists in $(INSTALLDIR) but not in the current one.
     * When searching for $(FILE), we will find it in $(INSTALLDIR)
     * b/c we added it here. This is not good...
     */
#ifdef notdef
    cp[-1] = '\0';
    (void) Dir_AddDir(path, name);
    cp[-1] = '/';

    bigmisses += 1;
    ln = Lst_Last(path);
    if (ln == NILLNODE) {
	return ((char *) NULL);
    } else {
	p = (Path *) Lst_Datum(ln);
    }

    if (Hash_FindEntry(&p->files, cp) != (Hash_Entry *)NULL) {
	return (estrdup(name));
    } else {
	return ((char *) NULL);
    }
#else /* !notdef */
    if (DEBUG(DIR)) {
	printf("   Looking for \"%s\" ...\n", name);
    }

    bigmisses += 1;
    entry = Hash_FindEntry(&mtimes, name);
    if (entry != (Hash_Entry *)NULL) {
	if (DEBUG(DIR)) {
	    printf("   got it (in mtime cache)\n");
	}
	return(estrdup(name));
    } else if (stat (name, &stb) == 0) {
	entry = Hash_CreateEntry(&mtimes, name, (Boolean *)NULL);
	if (DEBUG(DIR)) {
	    printf("   Caching %s for %s\n", Targ_FmtTime(stb.st_mtime),
		    name);
	}
	Hash_SetValue(entry, (long)stb.st_mtime);
	return (estrdup(name));
    } else {
	if (DEBUG(DIR)) {
	    printf("   failed. Returning NULL\n");
	}
	return ((char *)NULL);
    }
#endif /* notdef */
}


/*-
 *-----------------------------------------------------------------------
 * Dir_FindHereOrAbove  --
 *	search for a path starting at a given directory and then working
 *	our way up towards the root.
 *
 * Input:
 *	here		starting directory
 *	search_path	the path we are looking for
 *	result		the result of a successful search is placed here
 *	rlen		the length of the result buffer
 *			(typically MAXPATHLEN + 1)
 *
 * Results:
 *	0 on failure, 1 on success [in which case the found path is put
 *	in the result buffer].
 *
 * Side Effects:
 *-----------------------------------------------------------------------
 */
int
Dir_FindHereOrAbove(char *here, char *search_path, char *result, int rlen) {

	struct stat st;
	char dirbase[MAXPATHLEN + 1], *db_end;
        char try[MAXPATHLEN + 1], *try_end;

	/* copy out our starting point */
	snprintf(dirbase, sizeof(dirbase), "%s", here);
	db_end = dirbase + strlen(dirbase);

	/* loop until we determine a result */
	while (1) {

		/* try and stat(2) it ... */
		snprintf(try, sizeof(try), "%s/%s", dirbase, search_path);
		if (stat(try, &st) != -1) {
			/*
			 * success!  if we found a file, chop off
			 * the filename so we return a directory.
			 */
			if ((st.st_mode & S_IFMT) != S_IFDIR) {
				try_end = try + strlen(try);
				while (try_end > try && *try_end != '/')
					try_end--;
				if (try_end > try)
					*try_end = 0;	/* chop! */
			}

			/*
			 * done!
			 */
			snprintf(result, rlen, "%s", try);
			return(1);
		}

		/*
		 * nope, we didn't find it.  if we used up dirbase we've
		 * reached the root and failed.
		 */
		if (db_end == dirbase)
			break;		/* failed! */

		/*
		 * truncate dirbase from the end to move up a dir
		 */
		while (db_end > dirbase && *db_end != '/')
			db_end--;
		*db_end = 0;		/* chop! */

	} /* while (1) */

	/*
	 * we failed...
	 */
	return(0);
}

/*-
 *-----------------------------------------------------------------------
 * Dir_MTime  --
 *	Find the modification time of the file described by gn along the
 *	search path dirSearchPath.
 *
 * Input:
 *	gn		the file whose modification time is desired
 *
 * Results:
 *	The modification time or 0 if it doesn't exist
 *
 * Side Effects:
 *	The modification time is placed in the node's mtime slot.
 *	If the node didn't have a path entry before, and Dir_FindFile
 *	found one for it, the full name is placed in the path slot.
 *-----------------------------------------------------------------------
 */
int
Dir_MTime(GNode *gn)
{
    char          *fullName;  /* the full pathname of name */
    struct stat	  stb;	      /* buffer for finding the mod time */
    Hash_Entry	  *entry;

    if (gn->type & OP_ARCHV) {
	/* return Arch_MTime(gn); */
	fprintf(stderr, "OP_ARCHV is deprecated\n");
	exit(1);
    } else if (gn->type & OP_PHONY) {
	gn->mtime = 0;
	return 0;
    } else if (gn->path == (char *)NULL) {
	if (gn->type & OP_NOPATH)
	    fullName = NULL;
	else
	    fullName = Dir_FindFile(gn->name, Suff_FindPath(gn));
    } else {
	fullName = gn->path;
    }

    if (fullName == (char *)NULL) {
	fullName = estrdup(gn->name);
    }

    entry = Hash_FindEntry(&mtimes, fullName);
    if (entry != (Hash_Entry *)NULL) {
	/*
	 * Only do this once -- the second time folks are checking to
	 * see if the file was actually updated, so we need to actually go
	 * to the file system.
	 */
	if (DEBUG(DIR)) {
	    printf("Using cached time %s for %s\n",
		    Targ_FmtTime((time_t)(long)Hash_GetValue(entry)), fullName);
	}
	stb.st_mtime = (time_t)(long)Hash_GetValue(entry);
	Hash_DeleteEntry(&mtimes, entry);
    } else if (stat (fullName, &stb) < 0) {
	if (gn->type & OP_MEMBER) {
	    if (fullName != gn->path)
		free(fullName);
	    /* return Arch_MemMTime(gn); */
	    fprintf(stderr, "OP_ARCHV (OP_MEMBER) is deprecated\n");
	    exit(1);
	} else {
	    stb.st_mtime = 0;
	}
    }
    if (fullName && gn->path == (char *)NULL) {
	gn->path = fullName;
    }

    gn->mtime = stb.st_mtime;
    return (gn->mtime);
}

/*-
 *-----------------------------------------------------------------------
 * Dir_AddDir --
 *	Add the given name to the end of the given path. The order of
 *	the arguments is backwards so ParseDoDependency can do a
 *	Lst_ForEach of its list of paths...
 *
 * Input:
 *	path		the path to which the directory should be
 *			added
 *	name		the name of the directory to add
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	A structure is added to the list and the directory is
 *	read and hashed.
 *-----------------------------------------------------------------------
 */
Path *
Dir_AddDir(Lst path, const char *name)
{
    LstNode       ln = NILLNODE; /* node in case Path structure is found */
    Path	  *p = NULL;  /* pointer to new Path structure */
    DIR     	  *d;	      /* for reading directory */
    struct dirent *dp;	      /* entry in directory */

    if (strcmp(name, ".DOTLAST") == 0) {
	ln = Lst_Find(path, (ClientData)UNCONST(name), DirFindName);
	if (ln != NILLNODE)
	    return (Path *) Lst_Datum(ln);
	else {
	    dotLast->refCount += 1;
	    (void)Lst_AtFront(path, (ClientData)dotLast);
	}
    }

    if (path)
	ln = Lst_Find(openDirectories, (ClientData)UNCONST(name), DirFindName);
    if (ln != NILLNODE) {
	p = (Path *)Lst_Datum (ln);
	if (Lst_Member(path, (ClientData)p) == NILLNODE) {
	    p->refCount += 1;
	    (void)Lst_AtEnd (path, (ClientData)p);
	}
    } else {
	if (DEBUG(DIR)) {
	    printf("Caching %s ...", name);
	    fflush(stdout);
	}

	if ((d = opendir (name)) != (DIR *) NULL) {
	    p = emalloc(sizeof(Path));
	    p->name = estrdup(name);
	    p->hits = 0;
	    p->refCount = 1;
	    Hash_InitTable(&p->files, -1);

	    while ((dp = readdir (d)) != (struct dirent *) NULL) {
#if defined(sun) && defined(d_ino) /* d_ino is a sunos4 #define for d_fileno */
		/*
		 * The sun directory library doesn't check for a 0 inode
		 * (0-inode slots just take up space), so we have to do
		 * it ourselves.
		 */
		if (dp->d_fileno == 0) {
		    continue;
		}
#endif /* sun && d_ino */
		(void)Hash_CreateEntry(&p->files, dp->d_name, (Boolean *)NULL);
	    }
	    (void) closedir (d);
	    (void)Lst_AtEnd (openDirectories, (ClientData)p);
	    if (path != NULL)
		(void)Lst_AtEnd (path, (ClientData)p);
	}
	if (DEBUG(DIR)) {
	    printf("done\n");
	}
    }
    return p;
}

/*-
 *-----------------------------------------------------------------------
 * Dir_CopyDir --
 *	Callback function for duplicating a search path via Lst_Duplicate.
 *	Ups the reference count for the directory.
 *
 * Results:
 *	Returns the Path it was given.
 *
 * Side Effects:
 *	The refCount of the path is incremented.
 *
 *-----------------------------------------------------------------------
 */
ClientData
Dir_CopyDir(ClientData p)
{
    ((Path *) p)->refCount += 1;

    return ((ClientData)p);
}

/*-
 *-----------------------------------------------------------------------
 * Dir_MakeFlags --
 *	Make a string by taking all the directories in the given search
 *	path and preceding them by the given flag. Used by the suffix
 *	module to create variables for compilers based on suffix search
 *	paths.
 *
 * Input:
 *	flag		flag which should precede each directory
 *	path		list of directories
 *
 * Results:
 *	The string mentioned above. Note that there is no space between
 *	the given flag and each directory. The empty string is returned if
 *	Things don't go well.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
char *
Dir_MakeFlags(const char *flag, Lst path)
{
    char	  *str;	  /* the string which will be returned */
    char	  *s1, *s2;/* the current directory preceded by 'flag' */
    LstNode	  ln;	  /* the node of the current directory */
    Path	  *p;	  /* the structure describing the current directory */

    str = estrdup("");

    if (Lst_Open(path) == SUCCESS) {
	while ((ln = Lst_Next(path)) != NILLNODE) {
	    p = (Path *) Lst_Datum(ln);
	    s2 = str_concat(flag, p->name, 0);
	    str = str_concat(s1 = str, s2, STR_ADDSPACE);
	    free(s1);
	    free(s2);
	}
	Lst_Close(path);
    }

    return (str);
}

/*-
 *-----------------------------------------------------------------------
 * Dir_Destroy --
 *	Nuke a directory descriptor, if possible. Callback procedure
 *	for the suffixes module when destroying a search path.
 *
 * Input:
 *	pp		The directory descriptor to nuke
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	If no other path references this directory (refCount == 0),
 *	the Path and all its data are freed.
 *
 *-----------------------------------------------------------------------
 */
void
Dir_Destroy(ClientData pp)
{
    Path    	  *p = (Path *) pp;
    p->refCount -= 1;

    if (p->refCount == 0) {
	LstNode	ln;

	ln = Lst_Member(openDirectories, (ClientData)p);
	(void) Lst_Remove(openDirectories, ln);

	Hash_DeleteTable(&p->files);
	free((Address)p->name);
	free((Address)p);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Dir_ClearPath --
 *	Clear out all elements of the given search path. This is different
 *	from destroying the list, notice.
 *
 * Input:
 *	path		Path to clear
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The path is set to the empty list.
 *
 *-----------------------------------------------------------------------
 */
void
Dir_ClearPath(Lst path)
{
    Path    *p;
    while (!Lst_IsEmpty(path)) {
	p = (Path *)Lst_DeQueue(path);
	Dir_Destroy((ClientData) p);
    }
}


/*-
 *-----------------------------------------------------------------------
 * Dir_Concat --
 *	Concatenate two paths, adding the second to the end of the first.
 *	Makes sure to avoid duplicates.
 *
 * Input:
 *	path1		Dest
 *	path2		Source
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Reference counts for added dirs are upped.
 *
 *-----------------------------------------------------------------------
 */
void
Dir_Concat(Lst path1, Lst path2)
{
    LstNode ln;
    Path    *p;

    for (ln = Lst_First(path2); ln != NILLNODE; ln = Lst_Succ(ln)) {
	p = (Path *)Lst_Datum(ln);
	if (Lst_Member(path1, (ClientData)p) == NILLNODE) {
	    p->refCount += 1;
	    (void)Lst_AtEnd(path1, (ClientData)p);
	}
    }
}

/********** DEBUG INFO **********/
void
Dir_PrintDirectories(void)
{
    LstNode	ln;
    Path	*p;

    printf ("#*** Directory Cache:\n");
    printf ("# Stats: %d hits %d misses %d near misses %d losers (%d%%)\n",
	      hits, misses, nearmisses, bigmisses,
	      (hits+bigmisses+nearmisses ?
	       hits * 100 / (hits + bigmisses + nearmisses) : 0));
    printf ("# %-20s referenced\thits\n", "directory");
    if (Lst_Open(openDirectories) == SUCCESS) {
	while ((ln = Lst_Next(openDirectories)) != NILLNODE) {
	    p = (Path *) Lst_Datum(ln);
	    printf ("# %-20s %10d\t%4d\n", p->name, p->refCount, p->hits);
	}
	Lst_Close(openDirectories);
    }
}

static int
DirPrintDir(ClientData p, ClientData dummy)
{
    printf ("%s ", ((Path *) p)->name);
    return (dummy ? 0 : 0);
}

void
Dir_PrintPath(Lst path)
{
    Lst_ForEach(path, DirPrintDir, (ClientData)0);
}
/* end dir.c */

/* begin for.c */
/*	$NetBSD: for.c,v 1.18 2005/02/16 15:11:52 christos Exp $	*/

/*
 * Copyright (c) 1992, The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: for.c,v 1.18 2005/02/16 15:11:52 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)for.c	8.1 (Berkeley) 6/6/93";
#else
__RCSID("$NetBSD: for.c,v 1.18 2005/02/16 15:11:52 christos Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * for.c --
 *	Functions to handle loops in a makefile.
 *
 * Interface:
 *	For_Eval 	Evaluate the loop in the passed line.
 *	For_Run		Run accumulated loop
 *
 */

/* <<for.c includes>> */

/*
 * For statements are of the form:
 *
 * .for <variable> in <varlist>
 * ...
 * .endfor
 *
 * The trick is to look for the matching end inside for for loop
 * To do that, we count the current nesting level of the for loops.
 * and the .endfor statements, accumulating all the statements between
 * the initial .for loop and the matching .endfor;
 * then we evaluate the for loop for each variable in the varlist.
 *
 * Note that any nested fors are just passed through; they get handled
 * recursively in For_Eval when we're expanding the enclosing for in
 * For_Run.
 */

static int  	  forLevel = 0;  	/* Nesting level	*/

/*
 * State of a for loop.
 */
typedef struct _For {
    Buffer	  buf;			/* Body of loop		*/
    char	**vars;			/* Iteration variables	*/
    int           nvars;		/* # of iteration vars	*/
    Lst  	  lst;			/* List of items	*/
} For;

static For        accumFor;             /* Loop being accumulated */

static void ForAddVar(const char *, size_t);




/*-
 *-----------------------------------------------------------------------
 * ForAddVar --
 *	Add an iteration variable to the currently accumulating for.
 *
 * Results: none
 * Side effects: no additional side effects.
 *-----------------------------------------------------------------------
 */
static void
ForAddVar(const char *data, size_t len)
{
	Buffer buf;
	int varlen;

	buf = Buf_Init(0);
	Buf_AddBytes(buf, len, (Byte *)UNCONST(data));

	accumFor.nvars++;
	accumFor.vars = erealloc(accumFor.vars, accumFor.nvars*sizeof(char *));

	accumFor.vars[accumFor.nvars-1] = (char *) Buf_GetAll(buf, &varlen);

	Buf_Destroy(buf, FALSE);
}

/*-
 *-----------------------------------------------------------------------
 * For_Eval --
 *	Evaluate the for loop in the passed line. The line
 *	looks like this:
 *	    .for <variable> in <varlist>
 *
 * Input:
 *	line		Line to parse
 *
 * Results:
 *	TRUE: We found a for loop, or we are inside a for loop
 *	FALSE: We did not find a for loop, or we found the end of the for
 *	       for loop.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
int
For_Eval(char *line)
{
    char	    *ptr = line, *sub, *in, *wrd;
    int	    	    level;  	/* Level at which to report errors. */

    level = PARSE_FATAL;


    if (forLevel == 0) {
	Buffer	    buf;
	int	    varlen;
	static const char instr[] = "in";

	for (ptr++; *ptr && isspace((unsigned char) *ptr); ptr++)
	    continue;
	/*
	 * If we are not in a for loop quickly determine if the statement is
	 * a for.
	 */
	if (ptr[0] != 'f' || ptr[1] != 'o' || ptr[2] != 'r' ||
	    !isspace((unsigned char) ptr[3]))
	    return FALSE;
	ptr += 3;

	/*
	 * we found a for loop, and now we are going to parse it.
	 */
	while (*ptr && isspace((unsigned char) *ptr))
	    ptr++;

	/*
	 * Find the "in".
	 */
	for (in = ptr; *in; in++) {
	    if (isspace((unsigned char) in[0]) && in[1]== 'i' &&
		in[2] == 'n' &&
		(in[3] == '\0' || isspace((unsigned char) in[3])))
		break;
	}
	if (*in == '\0') {
	    Parse_Error(level, "missing `in' in for");
	    return 0;
	}

	/*
	 * Grab the variables.
	 */
	accumFor.vars = NULL;

	while (ptr < in) {
	    wrd = ptr;
	    while (*ptr && !isspace((unsigned char) *ptr))
	        ptr++;
	    ForAddVar(wrd, ptr - wrd);
	    while (*ptr && isspace((unsigned char) *ptr))
		ptr++;
	}

	if (accumFor.nvars == 0) {
	    Parse_Error(level, "no iteration variables in for");
	    return 0;
	}

	/* At this point we should be pointing right at the "in" */
	/*
	 * compensate for hp/ux's brain damaged assert macro that
	 * does not handle double quotes nicely.
	 */
	assert(!memcmp(ptr, instr, 2));
	ptr += 2;

	while (*ptr && isspace((unsigned char) *ptr))
	    ptr++;

	/*
	 * Make a list with the remaining words
	 */
	accumFor.lst = Lst_Init(FALSE);
	buf = Buf_Init(0);
	sub = Var_Subst(NULL, ptr, VAR_GLOBAL, FALSE);

#define ADDWORD() \
	Buf_AddBytes(buf, ptr - wrd, (Byte *) wrd), \
	Buf_AddByte(buf, (Byte) '\0'), \
	Lst_AtFront(accumFor.lst, (ClientData) Buf_GetAll(buf, &varlen)), \
	Buf_Destroy(buf, FALSE)

	for (ptr = sub; *ptr && isspace((unsigned char) *ptr); ptr++)
	    continue;

	for (wrd = ptr; *ptr; ptr++)
	    if (isspace((unsigned char) *ptr)) {
		ADDWORD();
		buf = Buf_Init(0);
		while (*ptr && isspace((unsigned char) *ptr))
		    ptr++;
		wrd = ptr--;
	    }
	if (DEBUG(FOR)) {
	    int i;
	    for (i = 0; i < accumFor.nvars; i++) {
		(void) fprintf(stderr, "For: variable %s\n", accumFor.vars[i]);
	    }
	    (void) fprintf(stderr, "For: list %s\n", sub);
	}
	if (ptr - wrd > 0)
	    ADDWORD();
	else
	    Buf_Destroy(buf, TRUE);
	free((Address) sub);

	accumFor.buf = Buf_Init(0);
	forLevel++;
	return 1;
    }
    else if (*ptr == '.') {

	for (ptr++; *ptr && isspace((unsigned char) *ptr); ptr++)
	    continue;

	if (strncmp(ptr, "endfor", 6) == 0 &&
	    (isspace((unsigned char) ptr[6]) || !ptr[6])) {
	    if (DEBUG(FOR))
		(void) fprintf(stderr, "For: end for %d\n", forLevel);
	    if (--forLevel < 0) {
		Parse_Error(level, "for-less endfor");
		return 0;
	    }
	}
	else if (strncmp(ptr, "for", 3) == 0 &&
		 isspace((unsigned char) ptr[3])) {
	    forLevel++;
	    if (DEBUG(FOR))
		(void) fprintf(stderr, "For: new loop %d\n", forLevel);
	}
    }

    if (forLevel != 0) {
	Buf_AddBytes(accumFor.buf, strlen(line), (Byte *) line);
	Buf_AddByte(accumFor.buf, (Byte) '\n');
	return 1;
    }
    else {
	return 0;
    }
}


/*-
 *-----------------------------------------------------------------------
 * For_Run --
 *	Run the for loop, imitating the actions of an include file
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
void
For_Run(int lineno)
{
    For arg;
    LstNode ln;
    char **values;
    int i, done = 0, len;
    char *guy, *orig_guy, *old_guy;

    if (accumFor.buf == NULL || accumFor.vars == NULL || accumFor.lst == NULL)
	return;
    arg = accumFor;
    accumFor.buf = NULL;
    accumFor.vars = NULL;
    accumFor.nvars = 0;
    accumFor.lst = NULL;

    if (Lst_Open(arg.lst) != SUCCESS)
	return;

    values = emalloc(arg.nvars * sizeof(char *));

    while (!done) {
	/*
	 * due to the dumb way this is set up, this loop must run
	 * backwards.
	 */
	for (i = arg.nvars - 1; i >= 0; i--) {
	    ln = Lst_Next(arg.lst);
	    if (ln == NILLNODE) {
		if (i != arg.nvars-1) {
		    Parse_Error(PARSE_FATAL,
			"Not enough words in for substitution list");
		}
		done = 1;
		break;
	    } else {
		values[i] = (char *) Lst_Datum(ln);
	    }
	}
	if (done)
	    break;

	for (i = 0; i < arg.nvars; i++) {
	    Var_Set(arg.vars[i], values[i], VAR_GLOBAL, 0);
	    if (DEBUG(FOR))
		(void) fprintf(stderr, "--- %s = %s\n", arg.vars[i],
		    values[i]);
	}

	/*
	 * Hack, hack, kludge.
	 * This is really ugly, but to do it any better way would require
	 * making major changes to var.c, which I don't want to get into
	 * yet. There is no mechanism for expanding some variables, only
	 * for expanding a single variable. That should be corrected, but
	 * not right away. (XXX)
	 */

	guy = (char *) Buf_GetAll(arg.buf, &len);
	orig_guy = guy;
	for (i = 0; i < arg.nvars; i++) {
	    old_guy = guy;
	    guy = Var_Subst(arg.vars[i], guy, VAR_GLOBAL, FALSE);
	    if (old_guy != orig_guy)
		free(old_guy);
	}
	Parse_FromString(guy, lineno);

	for (i = 0; i < arg.nvars; i++)
	    Var_Delete(arg.vars[i], VAR_GLOBAL);
    }

    free(values);

    Lst_Close(arg.lst);

    for (i=0; i<arg.nvars; i++) {
	free(arg.vars[i]);
    }
    free(arg.vars);

    Lst_Destroy(arg.lst, (void (*)(ClientData)) free);
    Buf_Destroy(arg.buf, TRUE);
}
/* end for.c */

/* begin hash.c */
/*	$NetBSD: hash.c,v 1.14 2005/02/16 15:11:52 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: hash.c,v 1.14 2005/02/16 15:11:52 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)hash.c	8.1 (Berkeley) 6/6/93";
#else
__RCSID("$NetBSD: hash.c,v 1.14 2005/02/16 15:11:52 christos Exp $");
#endif
#endif /* not lint */
#endif

/* hash.c --
 *
 * 	This module contains routines to manipulate a hash table.
 * 	See hash.h for a definition of the structure of the hash
 * 	table.  Hash tables grow automatically as the amount of
 * 	information increases.
 */

/* <<hash.c includes>> */

/*
 * Forward references to local procedures that are used before they're
 * defined:
 */

static void RebuildTable(Hash_Table *);

/*
 * The following defines the ratio of # entries to # buckets
 * at which we rebuild the table to make it larger.
 */

#define rebuildLimit 3

/*
 *---------------------------------------------------------
 *
 * Hash_InitTable --
 *
 *	This routine just sets up the hash table.
 *
 * Input:
 *	t		Structure to to hold table.
 *	numBuckets	How many buckets to create for starters. This
 *			number is rounded up to a power of two.   If
 *			<= 0, a reasonable default is chosen. The
 *			table will grow in size later as needed.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Memory is allocated for the initial bucket area.
 *
 *---------------------------------------------------------
 */

void
Hash_InitTable(Hash_Table *t, int numBuckets)
{
	int i;
	struct Hash_Entry **hp;

	/*
	 * Round up the size to a power of two.
	 */
	if (numBuckets <= 0)
		i = 16;
	else {
		for (i = 2; i < numBuckets; i <<= 1)
			 continue;
	}
	t->numEntries = 0;
	t->size = i;
	t->mask = i - 1;
	t->bucketPtr = hp = (struct Hash_Entry **)emalloc(sizeof(*hp) * i);
	while (--i >= 0)
		*hp++ = NULL;
}

/*
 *---------------------------------------------------------
 *
 * Hash_DeleteTable --
 *
 *	This routine removes everything from a hash table
 *	and frees up the memory space it occupied (except for
 *	the space in the Hash_Table structure).
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Lots of memory is freed up.
 *
 *---------------------------------------------------------
 */

void
Hash_DeleteTable(Hash_Table *t)
{
	struct Hash_Entry **hp, *h, *nexth = NULL;
	int i;

	for (hp = t->bucketPtr, i = t->size; --i >= 0;) {
		for (h = *hp++; h != NULL; h = nexth) {
			nexth = h->next;
			free((char *)h);
		}
	}
	free((char *)t->bucketPtr);

	/*
	 * Set up the hash table to cause memory faults on any future access
	 * attempts until re-initialization.
	 */
	t->bucketPtr = NULL;
}

/*
 *---------------------------------------------------------
 *
 * Hash_FindEntry --
 *
 * 	Searches a hash table for an entry corresponding to key.
 *
 * Input:
 *	t		Hash table to search.
 *	key		A hash key.
 *
 * Results:
 *	The return value is a pointer to the entry for key,
 *	if key was present in the table.  If key was not
 *	present, NULL is returned.
 *
 * Side Effects:
 *	None.
 *
 *---------------------------------------------------------
 */

Hash_Entry *
Hash_FindEntry(Hash_Table *t, const char *key)
{
	Hash_Entry *e;
	unsigned h;
	const char *p;

	for (h = 0, p = key; *p;)
		h = (h << 5) - h + *p++;
	p = key;
	for (e = t->bucketPtr[h & t->mask]; e != NULL; e = e->next)
		if (e->namehash == h && strcmp(e->name, p) == 0)
			return (e);
	return (NULL);
}

/*
 *---------------------------------------------------------
 *
 * Hash_CreateEntry --
 *
 *	Searches a hash table for an entry corresponding to
 *	key.  If no entry is found, then one is created.
 *
 * Input:
 *	t		Hash table to search.
 *	key		A hash key.
 *	newPtr		Filled in with TRUE if new entry created,
 *			FALSE otherwise.
 *
 * Results:
 *	The return value is a pointer to the entry.  If *newPtr
 *	isn't NULL, then *newPtr is filled in with TRUE if a
 *	new entry was created, and FALSE if an entry already existed
 *	with the given key.
 *
 * Side Effects:
 *	Memory may be allocated, and the hash buckets may be modified.
 *---------------------------------------------------------
 */

Hash_Entry *
Hash_CreateEntry(Hash_Table *t, const char *key, Boolean *newPtr)
{
	Hash_Entry *e;
	unsigned h;
	const char *p;
	int keylen;
	struct Hash_Entry **hp;

	/*
	 * Hash the key.  As a side effect, save the length (strlen) of the
	 * key in case we need to create the entry.
	 */
	for (h = 0, p = key; *p;)
		h = (h << 5) - h + *p++;
	keylen = p - key;
	p = key;
	for (e = t->bucketPtr[h & t->mask]; e != NULL; e = e->next) {
		if (e->namehash == h && strcmp(e->name, p) == 0) {
			if (newPtr != NULL)
				*newPtr = FALSE;
			return (e);
		}
	}

	/*
	 * The desired entry isn't there.  Before allocating a new entry,
	 * expand the table if necessary (and this changes the resulting
	 * bucket chain).
	 */
	if (t->numEntries >= rebuildLimit * t->size)
		RebuildTable(t);
	e = emalloc(sizeof(*e) + keylen);
	hp = &t->bucketPtr[h & t->mask];
	e->next = *hp;
	*hp = e;
	e->clientData = NULL;
	e->namehash = h;
	(void) strcpy(e->name, p);
	t->numEntries++;

	if (newPtr != NULL)
		*newPtr = TRUE;
	return (e);
}

/*
 *---------------------------------------------------------
 *
 * Hash_DeleteEntry --
 *
 * 	Delete the given hash table entry and free memory associated with
 *	it.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Hash chain that entry lives in is modified and memory is freed.
 *
 *---------------------------------------------------------
 */

void
Hash_DeleteEntry(Hash_Table *t, Hash_Entry *e)
{
	Hash_Entry **hp, *p;

	if (e == NULL)
		return;
	for (hp = &t->bucketPtr[e->namehash & t->mask];
	     (p = *hp) != NULL; hp = &p->next) {
		if (p == e) {
			*hp = p->next;
			free((char *)p);
			t->numEntries--;
			return;
		}
	}
	(void) write(2, "bad call to Hash_DeleteEntry\n", 29);
	abort();
}

/*
 *---------------------------------------------------------
 *
 * Hash_EnumFirst --
 *	This procedure sets things up for a complete search
 *	of all entries recorded in the hash table.
 *
 * Input:
 *	t		Table to be searched.
 *	searchPtr	Area in which to keep state about search.
 *
 * Results:
 *	The return value is the address of the first entry in
 *	the hash table, or NULL if the table is empty.
 *
 * Side Effects:
 *	The information in searchPtr is initialized so that successive
 *	calls to Hash_Next will return successive HashEntry's
 *	from the table.
 *
 *---------------------------------------------------------
 */

Hash_Entry *
Hash_EnumFirst(Hash_Table *t, Hash_Search *searchPtr)
{
	searchPtr->tablePtr = t;
	searchPtr->nextIndex = 0;
	searchPtr->hashEntryPtr = NULL;
	return Hash_EnumNext(searchPtr);
}

/*
 *---------------------------------------------------------
 *
 * Hash_EnumNext --
 *    This procedure returns successive entries in the hash table.
 *
 * Input:
 *	searchPtr	Area used to keep state about search.
 *
 * Results:
 *    The return value is a pointer to the next HashEntry
 *    in the table, or NULL when the end of the table is
 *    reached.
 *
 * Side Effects:
 *    The information in searchPtr is modified to advance to the
 *    next entry.
 *
 *---------------------------------------------------------
 */

Hash_Entry *
Hash_EnumNext(Hash_Search *searchPtr)
{
	Hash_Entry *e;
	Hash_Table *t = searchPtr->tablePtr;

	/*
	 * The hashEntryPtr field points to the most recently returned
	 * entry, or is nil if we are starting up.  If not nil, we have
	 * to start at the next one in the chain.
	 */
	e = searchPtr->hashEntryPtr;
	if (e != NULL)
		e = e->next;
	/*
	 * If the chain ran out, or if we are starting up, we need to
	 * find the next nonempty chain.
	 */
	while (e == NULL) {
		if (searchPtr->nextIndex >= t->size)
			return (NULL);
		e = t->bucketPtr[searchPtr->nextIndex++];
	}
	searchPtr->hashEntryPtr = e;
	return (e);
}

/*
 *---------------------------------------------------------
 *
 * RebuildTable --
 *	This local routine makes a new hash table that
 *	is larger than the old one.
 *
 * Results:
 * 	None.
 *
 * Side Effects:
 *	The entire hash table is moved, so any bucket numbers
 *	from the old table are invalid.
 *
 *---------------------------------------------------------
 */

static void
RebuildTable(Hash_Table *t)
{
	Hash_Entry *e, *next = NULL, **hp, **xp;
	int i, mask;
        Hash_Entry **oldhp;
	int oldsize;

	oldhp = t->bucketPtr;
	oldsize = i = t->size;
	i <<= 1;
	t->size = i;
	t->mask = mask = i - 1;
	t->bucketPtr = hp = (struct Hash_Entry **) emalloc(sizeof(*hp) * i);
	while (--i >= 0)
		*hp++ = NULL;
	for (hp = oldhp, i = oldsize; --i >= 0;) {
		for (e = *hp++; e != NULL; e = next) {
			next = e->next;
			xp = &t->bucketPtr[e->namehash & mask];
			e->next = *xp;
			*xp = e;
		}
	}
	free((char *)oldhp);
}
/* end hash.c */

/* begin job.c */
/*	$NetBSD: job.c,v 1.95 2005/06/29 19:59:42 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: job.c,v 1.95 2005/06/29 19:59:42 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)job.c	8.2 (Berkeley) 3/19/94";
#else
__RCSID("$NetBSD: job.c,v 1.95 2005/06/29 19:59:42 christos Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * job.c --
 *	handle the creation etc. of our child processes.
 *
 * Interface:
 *	Job_Make  	    	Start the creation of the given target.
 *
 *	Job_CatchChildren   	Check for and handle the termination of any
 *	    	  	    	children. This must be called reasonably
 *	    	  	    	frequently to keep the whole make going at
 *	    	  	    	a decent clip, since job table entries aren't
 *	    	  	    	removed until their process is caught this way.
 *	    	  	    	Its single argument is TRUE if the function
 *	    	  	    	should block waiting for a child to terminate.
 *
 *	Job_CatchOutput	    	Print any output our children have produced.
 *	    	  	    	Should also be called fairly frequently to
 *	    	  	    	keep the user informed of what's going on.
 *	    	  	    	If no output is waiting, it will block for
 *	    	  	    	a time given by the SEL_* constants, below,
 *	    	  	    	or until output is ready.
 *
 *	Job_Init  	    	Called to intialize this module. in addition,
 *	    	  	    	any commands attached to the .BEGIN target
 *	    	  	    	are executed before this function returns.
 *	    	  	    	Hence, the makefile must have been parsed
 *	    	  	    	before this function is called.
 *
 *	Job_End  	    	Cleanup any memory used.
 *
 *	Job_Empty 	    	Return TRUE if the job table is completely
 *	    	  	    	empty.
 *
 *	Job_ParseShell	    	Given the line following a .SHELL target, parse
 *	    	  	    	the line as a shell specification. Returns
 *	    	  	    	FAILURE if the spec was incorrect.
 *
 *	Job_Finish	    	Perform any final processing which needs doing.
 *	    	  	    	This includes the execution of any commands
 *	    	  	    	which have been/were attached to the .END
 *	    	  	    	target. It should only be called when the
 *	    	  	    	job table is empty.
 *
 *	Job_AbortAll	    	Abort all currently running jobs. It doesn't
 *	    	  	    	handle output or do anything for the jobs,
 *	    	  	    	just kills them. It should only be called in
 *	    	  	    	an emergency, as it were.
 *
 *	Job_CheckCommands   	Verify that the commands for a target are
 *	    	  	    	ok. Provide them if necessary and possible.
 *
 *	Job_Touch 	    	Update a target without really updating it.
 *
 *	Job_Wait  	    	Wait for all currently-running jobs to finish.
 */

/* <<job.c includes>> */

/*
 * error handling variables
 */
static int     	errors = 0;	    /* number of errors reported */
static int    	aborting = 0;	    /* why is the make aborting? */
#define ABORT_ERROR	1   	    /* Because of an error */
#define ABORT_INTERRUPT	2   	    /* Because it was interrupted */
#define ABORT_WAIT	3   	    /* Waiting for jobs to finish */

/*
 * XXX: Avoid SunOS bug... FILENO() is fp->_file, and file
 * is a char! So when we go above 127 we turn negative!
 */
#define FILENO(a) ((unsigned) fileno(a))

static int     	  numCommands; 	    /* The number of commands actually printed
				     * for a target. Should this number be
				     * 0, no shell will be executed. */

/*
 * Return values from JobStart.
 */
#define JOB_RUNNING	0   	/* Job is running */
#define JOB_ERROR 	1   	/* Error in starting the job */
#define JOB_FINISHED	2   	/* The job is already finished */
#define JOB_STOPPED	3   	/* The job is stopped */



/*
 * Descriptions for various shells.
 */
static Shell    shells[] = {
    /*
     * CSH description. The csh can do echo control by playing
     * with the setting of the 'echo' shell variable. Sadly,
     * however, it is unable to do error control nicely.
     */
{
    "csh",
    TRUE, "unset verbose", "set verbose", "unset verbose", 10,
    FALSE, "echo \"%s\"\n", "csh -c \"%s || exit 0\"\n", "", '#',
    "v", "e",
},
    /*
     * SH description. Echo control is also possible and, under
     * sun UNIX anyway, one can even control error checking.
     */
{
    "sh",
    FALSE, "", "", "", 0,
    FALSE, "echo \"%s\"\n", "%s\n", "{ %s \n} || exit $?\n", '#',
#ifdef __NetBSD__
    "q",
#else
    "",
#endif
    "",
},
    /*
     * KSH description.
     */
{
    "ksh",
    TRUE, "set +v", "set -v", "set +v", 6,
    FALSE, "echo \"%s\"\n", "%s\n", "{ %s \n} || exit $?\n", '#',
    "v",
    "",
},
    /*
     * UNKNOWN.
     */
{
    (char *) 0,
    FALSE, (char *) 0, (char *) 0, (char *) 0, 0,
    FALSE, (char *) 0, (char *) 0, (char *) 0, 0,
    (char *) 0, (char *) 0,
}
};
static Shell 	*commandShell = &shells[DEFSHELL];/* this is the shell to
						   * which we pass all
						   * commands in the Makefile.
						   * It is set by the
						   * Job_ParseShell function */
const char *shellPath = NULL,		  	  /* full pathname of
						   * executable image */
           *shellName = NULL;		      	  /* last component of shell */
static const char *shellArgv = NULL;		  /* Custom shell args */


static int  	maxJobs;    	/* The most children we can run at once */
static int  	maxLocal;    	/* The most local ones we can have */
static int     	nJobs;	    	/* The number of children currently running */
static int	nLocal;    	/* The number of local children */
static Lst     	jobs;		/* The structures that describe them */
static Boolean	wantToken;	/* we want a token */

/*
 * Set of descriptors of pipes connected to
 * the output channels of children
 */
static struct pollfd *fds = NULL;
static Job **jobfds = NULL;
static int nfds = 0;
static int maxfds = 0;
static void watchfd(Job *);
static void clearfd(Job *);
static int readyfd(Job *);
#define JBSTART 256
#define JBFACTOR 2

static GNode   	*lastNode;	/* The node for which output was most recently
				 * produced. */
static const char *targFmt;   	/* Format string to use to head output from a
				 * job when it's not the most-recent job heard
				 * from */
static Job tokenWaitJob;	/* token wait pseudo-job */
int	job_pipe[2] = { -1, -1 }; /* job server pipes. */

static Job childExitJob;	/* child exit pseudo-job */
int	exit_pipe[2] = { -1, -1 }; /* child exit signal pipe. */

# define TARG_FMT  "--- %s ---\n" /* Default format */
# define MESSAGE(fp, gn) \
	(void) fprintf(fp, targFmt, gn->name)

/*
 * When JobStart attempts to run a job remotely but can't, and isn't allowed
 * to run the job locally, or when Job_CatchChildren detects a job that has
 * been migrated home, the job is placed on the stoppedJobs queue to be run
 * when the next job finishes.
 */
static Lst	stoppedJobs;	/* Lst of Job structures describing
				 * jobs that were stopped due to concurrency
				 * limits or migration home */


sigset_t	caught_signals;	/* Set of signals we handle */
#if defined(USE_PGRP) && defined(SYSV)
# define KILL(pid, sig)		kill(-(pid), (sig))
#else
# if defined(USE_PGRP)
#  define KILL(pid, sig)	killpg((pid), (sig))
# else
#  define KILL(pid, sig)	kill((pid), (sig))
# endif
#endif

/*
 * Grmpf... There is no way to set bits of the wait structure
 * anymore with the stupid W*() macros. I liked the union wait
 * stuff much more. So, we devise our own macros... This is
 * really ugly, use dramamine sparingly. You have been warned.
 */
#ifndef W_STOPCODE
#define W_STOPCODE(sig) (((sig) << 8) | 0177)
#endif
#ifndef W_EXITCODE
#define W_EXITCODE(ret, sig) ((ret << 8) | (sig))
#endif

static int JobCondPassSig(ClientData, ClientData);
static void JobPassSig(int);
static void JobChildSig(int);
#ifdef USE_PGRP
static void JobContinueSig(int);
#endif
static int JobCmpPid(ClientData, ClientData);
static int JobPrintCommand(ClientData, ClientData);
static int JobSaveCommand(ClientData, ClientData);
static void JobClose(Job *);
static void JobFinish(Job *, int *);
static void JobExec(Job *, char **);
static void JobMakeArgv(Job *, char **);
static int JobRestart(Job *);
static int JobStart(GNode *, int, Job *);
static char *JobOutput(Job *, char *, char *, int);
static void JobDoOutput(Job *, Boolean);
static Shell *JobMatchShell(const char *);
static void JobInterrupt(int, int);
static void JobRestartJobs(void);
static void JobTokenAdd(void);
static void JobSigLock(sigset_t *);
static void JobSigUnlock(sigset_t *);
static void JobSigReset(void);



/*
 * JobSigLock/JobSigUnlock
 *
 * Signal lock routines to get exclusive access. Currently used to
 * protect `jobs' and `stoppedJobs' list manipulations.
 */
static void JobSigLock(sigset_t *omaskp)
{
	if (sigprocmask(SIG_BLOCK, &caught_signals, omaskp) != 0) {
		Punt("JobSigLock: sigprocmask: %s", strerror(errno));
	sigemptyset(omaskp);
	}
}

static void JobSigUnlock(sigset_t *omaskp)
{
	(void) sigprocmask(SIG_SETMASK, omaskp, NULL);
}

/*-
 *-----------------------------------------------------------------------
 * JobCondPassSig --
 *	Pass a signal to a job if the job is remote or if USE_PGRP
 *	is defined.
 *
 * Input:
 *	jobp		Job to biff
 *	signop		Signal to send it
 *
 * Results:
 *	=== 0
 *
 * Side Effects:
 *	None, except the job may bite it.
 *
 *-----------------------------------------------------------------------
 */
static int
JobCondPassSig(ClientData jobp, ClientData signop)
{
    Job	*job = (Job *) jobp;
    int	signo = *(int *) signop;
    /*
     * Assume that sending the signal to job->pid will signal any remote
     * job as well.
     */
    if (DEBUG(JOB)) {
	(void) fprintf(stdout,
		       "JobCondPassSig passing signal %d to child %d.\n",
		       signo, job->pid);
	(void) fflush(stdout);
    }
    KILL(job->pid, signo);
    return 0;
}

/*-
 *-----------------------------------------------------------------------
 * JobChldSig --
 *	SIGCHLD handler.
 *
 * Input:
 *	signo		The signal number we've received
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Sends a token on the child exit pipe to wake us up from
 *	select()/poll().
 *
 *-----------------------------------------------------------------------
 */
static void
JobChildSig(int signo __unused)
{
    write(exit_pipe[1], ".", 1);
}


#ifdef USE_PGRP
/*-
 *-----------------------------------------------------------------------
 * JobContinueSig --
 *	Resume all stopped jobs.
 *
 * Input:
 *	signo		The signal number we've received
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Jobs start running again.
 *
 *-----------------------------------------------------------------------
 */
static void
JobContinueSig(int signo __unused)
{
    JobRestartJobs();
}
#endif

/*-
 *-----------------------------------------------------------------------
 * JobPassSig --
 *	Pass a signal on to all remote jobs and to all local jobs if
 *	USE_PGRP is defined, then die ourselves.
 *
 * Input:
 *	signo		The signal number we've received
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	We die by the same signal.
 *
 *-----------------------------------------------------------------------
 */
static void
JobPassSig(int signo)
{
    sigset_t nmask, omask;
    struct sigaction act;
    int sigcont;

    if (DEBUG(JOB)) {
	(void) fprintf(stdout, "JobPassSig(%d) called.\n", signo);
	(void) fflush(stdout);
    }
    Lst_ForEach(jobs, JobCondPassSig, (ClientData) &signo);

    /*
     * Deal with proper cleanup based on the signal received. We only run
     * the .INTERRUPT target if the signal was in fact an interrupt. The other
     * three termination signals are more of a "get out *now*" command.
     */
    if (signo == SIGINT) {
	JobInterrupt(TRUE, signo);
    } else if ((signo == SIGHUP) || (signo == SIGTERM) || (signo == SIGQUIT)) {
	JobInterrupt(FALSE, signo);
    }

    /*
     * Leave gracefully if SIGQUIT, rather than core dumping.
     */
    if (signo == SIGQUIT) {
	Finish(0);
    }

    if (signo == SIGTSTP) {
	Job_CatchChildren(FALSE);
    }
    /*
     * Send ourselves the signal now we've given the message to everyone else.
     * Note we block everything else possible while we're getting the signal.
     * This ensures that all our jobs get continued when we wake up before
     * we take any other signal.
     */
    sigfillset(&nmask);
    sigdelset(&nmask, signo);
    (void) sigprocmask(SIG_SETMASK, &nmask, &omask);

    act.sa_handler = SIG_DFL;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    (void) sigaction(signo, &act, NULL);

    if (DEBUG(JOB)) {
	(void) fprintf(stdout,
		       "JobPassSig passing signal %d to self.\n", signo);
	(void) fflush(stdout);
    }

    (void) kill(getpid(), signo);
    if (signo != SIGTSTP) {
	sigcont = SIGCONT;
	Lst_ForEach(jobs, JobCondPassSig, (ClientData) &sigcont);
    }

    /* Restore handler and signal mask */
    act.sa_handler = JobPassSig;
    (void) sigaction(signo, &act, NULL);
    (void) sigprocmask(SIG_SETMASK, &omask, NULL);
}

/*-
 *-----------------------------------------------------------------------
 * JobCmpPid  --
 *	Compare the pid of the job with the given pid and return 0 if they
 *	are equal. This function is called from Job_CatchChildren via
 *	Lst_Find to find the job descriptor of the finished job.
 *
 * Input:
 *	job		job to examine
 *	pid		process id desired
 *
 * Results:
 *	0 if the pid's match
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static int
JobCmpPid(ClientData job, ClientData pid)
{
    return *(int *) pid - ((Job *) job)->pid;
}

/*-
 *-----------------------------------------------------------------------
 * JobPrintCommand  --
 *	Put out another command for the given job. If the command starts
 *	with an @ or a - we process it specially. In the former case,
 *	so long as the -s and -n flags weren't given to make, we stick
 *	a shell-specific echoOff command in the script. In the latter,
 *	we ignore errors for the entire job, unless the shell has error
 *	control.
 *	If the command is just "..." we take all future commands for this
 *	job to be commands to be executed once the entire graph has been
 *	made and return non-zero to signal that the end of the commands
 *	was reached. These commands are later attached to the postCommands
 *	node and executed by Job_End when all things are done.
 *	This function is called from JobStart via Lst_ForEach.
 *
 * Input:
 *	cmdp		command string to print
 *	jobp		job for which to print it
 *
 * Results:
 *	Always 0, unless the command was "..."
 *
 * Side Effects:
 *	If the command begins with a '-' and the shell has no error control,
 *	the JOB_IGNERR flag is set in the job descriptor.
 *	If the command is "..." and we're not ignoring such things,
 *	tailCmds is set to the successor node of the cmd.
 *	numCommands is incremented if the command is actually printed.
 *-----------------------------------------------------------------------
 */
static int
JobPrintCommand(ClientData cmdp, ClientData jobp)
{
    Boolean	  noSpecials;	    /* true if we shouldn't worry about
				     * inserting special commands into
				     * the input stream. */
    Boolean       shutUp = FALSE;   /* true if we put a no echo command
				     * into the command file */
    Boolean	  errOff = FALSE;   /* true if we turned error checking
				     * off before printing the command
				     * and need to turn it back on */
    const char    *cmdTemplate;	    /* Template to use when printing the
				     * command */
    char    	  *cmdStart;	    /* Start of expanded command */
    char	  *escCmd = NULL;    /* Command with quotes/backticks escaped */
    char     	  *cmd = (char *) cmdp;
    Job           *job = (Job *) jobp;
    char	  *cp, *tmp;
    int           i, j;

    noSpecials = NoExecute(job->node);

#define DBPRINTF(fmt, arg) if (DEBUG(JOB)) {	\
	(void) fprintf(stdout, fmt, arg); 	\
	(void) fflush(stdout); 			\
    }						\
   (void) fprintf(job->cmdFILE, fmt, arg);	\
   (void) fflush(job->cmdFILE);

    numCommands += 1;

    cmdStart = cmd = Var_Subst(NULL, cmd, job->node, FALSE);

    cmdTemplate = "%s\n";

    /*
     * Check for leading @' and -'s to control echoing and error checking.
     */
    while (*cmd == '@' || *cmd == '-' || (*cmd == '+')) {
	switch (*cmd) {
	case '@':
	    shutUp = TRUE;
	    break;
	case '-':
	    errOff = TRUE;
	    break;
	case '+':
	    if (noSpecials) {
		/*
		 * We're not actually executing anything...
		 * but this one needs to be - use compat mode just for it.
		 */
		CompatRunCommand(cmdp, (ClientData)job->node);
		return 0;
	    }
	    break;
	}
	cmd++;
    }

    while (isspace((unsigned char) *cmd))
	cmd++;

    /*
     * If the shell doesn't have error control the alternate echo'ing will
     * be done (to avoid showing additional error checking code)
     * and this will need the characters '$ ` \ "' escaped
     */

    if (!commandShell->hasErrCtl) {
	/* Worst that could happen is every char needs escaping. */
	escCmd = emalloc((strlen(cmd) * 2) + 1);
	for (i = 0, j= 0; cmd[i] != '\0'; i++, j++) {
		if (cmd[i] == '$' || cmd[i] == '`' || cmd[i] == '\\' ||
			cmd[i] == '"')
			escCmd[j++] = '\\';
		escCmd[j] = cmd[i];
	}
	escCmd[j] = 0;
    }

    if (shutUp) {
	if (!(job->flags & JOB_SILENT) && !noSpecials &&
	    commandShell->hasEchoCtl) {
		DBPRINTF("%s\n", commandShell->echoOff);
	} else {
	    if (commandShell->hasErrCtl)
		shutUp = FALSE;
	}
    }

    if (errOff) {
	if ( !(job->flags & JOB_IGNERR) && !noSpecials) {
	    if (commandShell->hasErrCtl) {
		/*
		 * we don't want the error-control commands showing
		 * up either, so we turn off echoing while executing
		 * them. We could put another field in the shell
		 * structure to tell JobDoOutput to look for this
		 * string too, but why make it any more complex than
		 * it already is?
		 */
		if (!(job->flags & JOB_SILENT) && !shutUp &&
		    commandShell->hasEchoCtl) {
			DBPRINTF("%s\n", commandShell->echoOff);
			DBPRINTF("%s\n", commandShell->ignErr);
			DBPRINTF("%s\n", commandShell->echoOn);
		} else {
			DBPRINTF("%s\n", commandShell->ignErr);
		}
	    } else if (commandShell->ignErr &&
		      (*commandShell->ignErr != '\0'))
	    {
		/*
		 * The shell has no error control, so we need to be
		 * weird to get it to ignore any errors from the command.
		 * If echoing is turned on, we turn it off and use the
		 * errCheck template to echo the command. Leave echoing
		 * off so the user doesn't see the weirdness we go through
		 * to ignore errors. Set cmdTemplate to use the weirdness
		 * instead of the simple "%s\n" template.
		 */
		if (!(job->flags & JOB_SILENT) && !shutUp) {
			if (commandShell->hasEchoCtl) {
				DBPRINTF("%s\n", commandShell->echoOff);
			}
			DBPRINTF(commandShell->errCheck, escCmd);
			shutUp = TRUE;
		} else {
			if (!shutUp) {
				DBPRINTF(commandShell->errCheck, escCmd);
			}
		}
		cmdTemplate = commandShell->ignErr;
		/*
		 * The error ignoration (hee hee) is already taken care
		 * of by the ignErr template, so pretend error checking
		 * is still on.
		 */
		errOff = FALSE;
	    } else {
		errOff = FALSE;
	    }
	} else {
	    errOff = FALSE;
	}
    } else {

	/*
	 * If errors are being checked and the shell doesn't have error control
	 * but does supply an errOut template, then setup commands to run
	 * through it.
	 */

	if (!commandShell->hasErrCtl && commandShell->errOut &&
	    (*commandShell->errOut != '\0')) {
		if (!(job->flags & JOB_SILENT) && !shutUp) {
			if (commandShell->hasEchoCtl) {
				DBPRINTF("%s\n", commandShell->echoOff);
			}
			DBPRINTF(commandShell->errCheck, escCmd);
			shutUp = TRUE;
		}
		/* If it's a comment line or blank, treat as an ignored error */
		if ((escCmd[0] == commandShell->commentChar) ||
		    (escCmd[0] == 0))
			cmdTemplate = commandShell->ignErr;
		else
			cmdTemplate = commandShell->errOut;
		errOff = FALSE;
	}
    }

    if (DEBUG(SHELL) && strcmp(shellName, "sh") == 0 &&
	(job->flags & JOB_TRACED) == 0) {
	    DBPRINTF("set -%s\n", "x");
	    job->flags |= JOB_TRACED;
    }

    if ((cp = Check_Cwd_Cmd(cmd)) != NULL) {
	    DBPRINTF("test -d %s && ", cp);
	    DBPRINTF("cd %s\n", cp);
    }

    DBPRINTF(cmdTemplate, cmd);
    free(cmdStart);
    if (escCmd)
        free(escCmd);
    if (errOff) {
	/*
	 * If echoing is already off, there's no point in issuing the
	 * echoOff command. Otherwise we issue it and pretend it was on
	 * for the whole command...
	 */
	if (!shutUp && !(job->flags & JOB_SILENT) && commandShell->hasEchoCtl){
	    DBPRINTF("%s\n", commandShell->echoOff);
	    shutUp = TRUE;
	}
	DBPRINTF("%s\n", commandShell->errCheck);
    }
    if (shutUp && commandShell->hasEchoCtl) {
	DBPRINTF("%s\n", commandShell->echoOn);
    }
    if (cp != NULL) {
	    DBPRINTF("test -d %s && ", cp);
	    DBPRINTF("cd %s\n", Var_Value(".OBJDIR", VAR_GLOBAL, &tmp));
    }
    return 0;
}

/*-
 *-----------------------------------------------------------------------
 * JobSaveCommand --
 *	Save a command to be executed when everything else is done.
 *	Callback function for JobFinish...
 *
 * Results:
 *	Always returns 0
 *
 * Side Effects:
 *	The command is tacked onto the end of postCommands's commands list.
 *
 *-----------------------------------------------------------------------
 */
static int
JobSaveCommand(ClientData cmd, ClientData gn)
{
	fprintf(stderr, "**************** WARN: JobSaveCommand: deprecated, doing nothing");
	return(0);
}


/*-
 *-----------------------------------------------------------------------
 * JobClose --
 *	Called to close both input and output pipes when a job is finished.
 *
 * Results:
 *	Nada
 *
 * Side Effects:
 *	The file descriptors associated with the job are closed.
 *
 *-----------------------------------------------------------------------
 */
static void
JobClose(Job *job)
{
    if (usePipes && (job->flags & JOB_FIRST)) {
	clearfd(job);
	if (job->outPipe != job->inPipe) {
	   (void) close(job->outPipe);
	}
	JobDoOutput(job, TRUE);
	(void) close(job->inPipe);
    } else {
	(void) close(job->outFd);
	JobDoOutput(job, TRUE);
    }
}

/*-
 *-----------------------------------------------------------------------
 * JobFinish  --
 *	Do final processing for the given job including updating
 *	parents and starting new jobs as available/necessary. Note
 *	that we pay no attention to the JOB_IGNERR flag here.
 *	This is because when we're called because of a noexecute flag
 *	or something, jstat.w_status is 0 and when called from
 *	Job_CatchChildren, the status is zeroed if it s/b ignored.
 *
 * Input:
 *	job		job to finish
 *	status		sub-why job went away
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Final commands for the job are placed on postCommands.
 *
 *	If we got an error and are aborting (aborting == ABORT_ERROR) and
 *	the job list is now empty, we are done for the day.
 *	If we recognized an error (errors !=0), we set the aborting flag
 *	to ABORT_ERROR so no more jobs will be started.
 *-----------------------------------------------------------------------
 */
/*ARGSUSED*/
static void
JobFinish(Job *job, int *status)
{
    Boolean 	 done;

    if ((WIFEXITED(*status) &&
	 (((WEXITSTATUS(*status) != 0) && !(job->flags & JOB_IGNERR)))) ||
	WIFSIGNALED(*status))
    {
	/*
	 * If it exited non-zero and either we're doing things our
	 * way or we're not ignoring errors, the job is finished.
	 * Similarly, if the shell died because of a signal
	 * the job is also finished. In these
	 * cases, finish out the job's output before printing the exit
	 * status...
	 */
	JobClose(job);
	if (job->cmdFILE != NULL && job->cmdFILE != stdout) {
	   (void) fclose(job->cmdFILE);
	   job->cmdFILE = NULL;
	}
	done = TRUE;
    } else if (WIFEXITED(*status)) {
	/*
	 * Deal with ignored errors in -B mode. We need to print a message
	 * telling of the ignored error as well as setting status.w_status
	 * to 0 so the next command gets run. To do this, we set done to be
	 * TRUE if in -B mode and the job exited non-zero.
	 */
	done = WEXITSTATUS(*status) != 0;
	/*
	 * Old comment said: "Note we don't
	 * want to close down any of the streams until we know we're at the
	 * end."
	 * But we do. Otherwise when are we going to print the rest of the
	 * stuff?
	 */
	JobClose(job);
    } else {
	/*
	 * No need to close things down or anything.
	 */
	done = FALSE;
    }

    if (done ||
	WIFSTOPPED(*status) ||
	(WIFSIGNALED(*status) && (WTERMSIG(*status) == SIGCONT)))
    {
	FILE	  *out;

	if (compatMake && !usePipes && (job->flags & JOB_IGNERR)) {
	    /*
	     * If output is going to a file and this job is ignoring
	     * errors, arrange to have the exit status sent to the
	     * output file as well.
	     */
	    out = fdopen(job->outFd, "w");
	    if (out == NULL)
		Punt("Cannot fdopen");
	} else {
	    out = stdout;
	}

	if (WIFEXITED(*status)) {
	    if (DEBUG(JOB)) {
		(void) fprintf(stdout, "Process %d [%s] exited.\n",
				job->pid, job->node->name);
		(void) fflush(stdout);
	    }
	    if (WEXITSTATUS(*status) != 0) {
		if (usePipes && job->node != lastNode) {
		    MESSAGE(out, job->node);
		    lastNode = job->node;
		}
		(void) fprintf(out, "*** [%s] Error code %d%s\n",
				job->node->name,
			       WEXITSTATUS(*status),
			       (job->flags & JOB_IGNERR) ? "(ignored)" : "");

		if (job->flags & JOB_IGNERR) {
		    *status = 0;
		}
	    } else if (DEBUG(JOB)) {
		if (usePipes && job->node != lastNode) {
		    MESSAGE(out, job->node);
		    lastNode = job->node;
		}
		(void) fprintf(out, "*** [%s] Completed successfully\n",
				job->node->name);
	    }
	} else if (WIFSTOPPED(*status) && WSTOPSIG(*status) != SIGCONT) {
	    if (DEBUG(JOB)) {
		(void) fprintf(stdout, "Process %d (%s) stopped.\n",
				job->pid, job->node->name);
		(void) fflush(stdout);
	    }
	    if (usePipes && job->node != lastNode) {
		MESSAGE(out, job->node);
		lastNode = job->node;
	    }
	    if (!(job->flags & JOB_REMIGRATE)) {
		switch (WSTOPSIG(*status)) {
		case SIGTSTP:
		    (void) fprintf(out, "*** [%s] Suspended\n",
				job->node->name);
		    break;
		case SIGSTOP:
		    (void) fprintf(out, "*** [%s] Stopped\n",
				job->node->name);
		    break;
		default:
		    (void) fprintf(out, "*** [%s] Stopped -- signal %d\n",
			job->node->name, WSTOPSIG(*status));
		}
	    }
	    job->flags |= JOB_RESUME;
	    (void)Lst_AtEnd(stoppedJobs, (ClientData)job);
	    (void) fflush(out);
	    return;
	} else if (WIFSTOPPED(*status) &&  WSTOPSIG(*status) == SIGCONT) {
	    /*
	     * If the beastie has continued, shift the Job from the stopped
	     * list to the running one (or re-stop it if concurrency is
	     * exceeded) and go and get another child.
	     */
	    if (job->flags & (JOB_RESUME|JOB_REMIGRATE|JOB_RESTART)) {
		if (usePipes && job->node != lastNode) {
		    MESSAGE(out, job->node);
		    lastNode = job->node;
		}
		(void) fprintf(out, "*** [%s] Continued\n", job->node->name);
	    }
	    if (!(job->flags & JOB_CONTINUING)) {
		if (DEBUG(JOB)) {
		    (void) fprintf(stdout,
			   "Warning: process %d [%s] was not continuing.\n",
			   job->pid, job->node->name);
		    (void) fflush(stdout);
		}
#ifdef notdef
		/*
		 * We don't really want to restart a job from scratch just
		 * because it continued, especially not without killing the
		 * continuing process!  That's why this is ifdef'ed out.
		 * FD - 9/17/90
		 */
		JobRestart(job);
#endif
	    }
	    job->flags &= ~JOB_CONTINUING;
 	    Lst_AtEnd(jobs, (ClientData)job);
	    nJobs += 1;
	    if (!(job->flags & JOB_REMOTE)) {
		if (DEBUG(JOB)) {
		    (void) fprintf(stdout,
				   "Process %d is continuing locally.\n",
				   job->pid);
		    (void) fflush(stdout);
  		}
		nLocal += 1;
	    }
	    (void) fflush(out);
  	    return;
	} else {
	    if (usePipes && job->node != lastNode) {
		MESSAGE(out, job->node);
		lastNode = job->node;
	    }
	    (void) fprintf(out, "*** [%s] Signal %d\n",
			job->node->name, WTERMSIG(*status));
	}

	(void) fflush(out);
    }

    /*
     * Now handle the -B-mode stuff. If the beast still isn't finished,
     * try and restart the job on the next command. If JobStart says it's
     * ok, it's ok. If there's an error, this puppy is done.
     */
    if (compatMake && (WIFEXITED(*status) &&
	!Lst_IsAtEnd(job->node->commands))) {
	switch (JobStart(job->node, job->flags & JOB_IGNDOTS, job)) {
	case JOB_RUNNING:
	    done = FALSE;
	    break;
	case JOB_ERROR:
	    done = TRUE;
	    *status = W_EXITCODE(1, 0);
	    break;
	case JOB_FINISHED:
	    /*
	     * If we got back a JOB_FINISHED code, JobStart has already
	     * called Make_Update and freed the job descriptor. We set
	     * done to false here to avoid fake cycles and double frees.
	     * JobStart needs to do the update so we can proceed up the
	     * graph when given the -n flag..
	     */
	    done = FALSE;
	    break;
	}
    } else {
	done = TRUE;
    }

    if (done) {
	Trace_Log(JOBEND, job);
	if (!compatMake && !(job->flags & JOB_SPECIAL)) {
	    if ((*status != 0) ||
	        (aborting == ABORT_ERROR) ||
	        (aborting == ABORT_INTERRUPT))
		Job_TokenReturn();
	}

    }

    if (done &&
	(aborting != ABORT_ERROR) &&
	(aborting != ABORT_INTERRUPT) &&
	(*status == 0))
    {
	/*
	 * As long as we aren't aborting and the job didn't return a non-zero
	 * status that we shouldn't ignore, we call Make_Update to update
	 * the parents. In addition, any saved commands for the node are placed
	 * on the .END target.
	 */
	if (job->tailCmds != NILLNODE) {
	    Lst_ForEachFrom(job->node->commands, job->tailCmds,
			     JobSaveCommand,
			    (ClientData)job->node);
	}
	job->node->made = MADE;
	if (!(job->flags & JOB_SPECIAL))
	    Job_TokenReturn();
	Make_Update(job->node);
	free((Address)job);
    } else if (*status != 0) {
	errors += 1;
	free((Address)job);
    }
    JobRestartJobs();

    /*
     * Set aborting if any error.
     */
    if (errors && !keepgoing && (aborting != ABORT_INTERRUPT)) {
	/*
	 * If we found any errors in this batch of children and the -k flag
	 * wasn't given, we set the aborting flag so no more jobs get
	 * started.
	 */
	aborting = ABORT_ERROR;
    }

    if ((aborting == ABORT_ERROR) && Job_Empty()) {
	/*
	 * If we are aborting and the job table is now empty, we finish.
	 */
	Finish(errors);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Job_Touch --
 *	Touch the given target. Called by JobStart when the -t flag was
 *	given
 *
 * Input:
 *	gn		the node of the file to touch
 *	silent		TRUE if should not print message
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The data modification of the file is changed. In addition, if the
 *	file did not exist, it is created.
 *-----------------------------------------------------------------------
 */
void
Job_Touch(GNode *gn, Boolean silent)
{
    int		  streamID;   	/* ID of stream opened to do the touch */
    struct utimbuf times;	/* Times for utime() call */

    if (gn->type & (OP_JOIN|OP_USE|OP_USEBEFORE|OP_EXEC|OP_OPTIONAL|OP_PHONY)) {
	/*
	 * .JOIN, .USE, .ZEROTIME and .OPTIONAL targets are "virtual" targets
	 * and, as such, shouldn't really be created.
	 */
	return;
    }

    if (!silent || NoExecute(gn)) {
	(void) fprintf(stdout, "touch %s\n", gn->name);
	(void) fflush(stdout);
    }

    if (NoExecute(gn)) {
	return;
    }

    if (gn->type & OP_ARCHV) {
	/* Arch_Touch(gn); */
	fprintf(stderr, "OP_ARCHV is deprecated\n");
	exit(1);
    } else if (gn->type & OP_LIB) {
	/* Arch_TouchLib(gn); */
	fprintf(stderr, "OP_ARCHV (OP_LIB) is deprecated\n");
	exit(1);
    } else {
	char	*file = gn->path ? gn->path : gn->name;

	times.actime = times.modtime = now;
	if (utime(file, &times) < 0){
	    streamID = open(file, O_RDWR | O_CREAT, 0666);

	    if (streamID >= 0) {
		char	c;

		/*
		 * Read and write a byte to the file to change the
		 * modification time, then close the file.
		 */
		if (read(streamID, &c, 1) == 1) {
		    (void) lseek(streamID, (off_t)0, SEEK_SET);
		    (void) write(streamID, &c, 1);
		}

		(void) close(streamID);
	    } else {
		(void) fprintf(stdout, "*** couldn't touch %s: %s",
			       file, strerror(errno));
		(void) fflush(stdout);
	    }
	}
    }
}

/*-
 *-----------------------------------------------------------------------
 * Job_CheckCommands --
 *	Make sure the given node has all the commands it needs.
 *
 * Input:
 *	gn		The target whose commands need verifying
 *	abortProc	Function to abort with message
 *
 * Results:
 *	TRUE if the commands list is/was ok.
 *
 * Side Effects:
 *	The node will have commands from the .DEFAULT rule added to it
 *	if it needs them.
 *-----------------------------------------------------------------------
 */
Boolean
Job_CheckCommands(GNode *gn, void (*abortProc)(const char *, ...))
{
    if (OP_NOP(gn->type) && Lst_IsEmpty(gn->commands) &&
	((gn->type & OP_LIB) == 0 || Lst_IsEmpty(gn->children))) {
	/*
	 * No commands. Look for .DEFAULT rule from which we might infer
	 * commands
	 */
	if ((DEFAULT != NILGNODE) && !Lst_IsEmpty(DEFAULT->commands) &&
	    (gn->type & OP_SPECIAL) == 0) {
	    char *p1;
	    /*
	     * Make only looks for a .DEFAULT if the node was never the
	     * target of an operator, so that's what we do too. If
	     * a .DEFAULT was given, we substitute its commands for gn's
	     * commands and set the IMPSRC variable to be the target's name
	     * The DEFAULT node acts like a transformation rule, in that
	     * gn also inherits any attributes or sources attached to
	     * .DEFAULT itself.
	     */
	    Make_HandleUse(DEFAULT, gn);
	    Var_Set(IMPSRC, Var_Value(TARGET, gn, &p1), gn, 0);
	    if (p1)
		free(p1);
	} else if (Dir_MTime(gn) == 0 && (gn->type & OP_SPECIAL) == 0) {
	    /*
	     * The node wasn't the target of an operator we have no .DEFAULT
	     * rule to go on and the target doesn't already exist. There's
	     * nothing more we can do for this branch. If the -k flag wasn't
	     * given, we stop in our tracks, otherwise we just don't update
	     * this node's parents so they never get examined.
	     */
	    static const char msg[] = ": don't know how to make";

	    if (gn->type & OP_OPTIONAL) {
		(void) fprintf(stdout, "%s%s %s(ignored)\n", progname,
		    msg, gn->name);
		(void) fflush(stdout);
	    } else if (keepgoing) {
		(void) fprintf(stdout, "%s%s %s(continuing)\n", progname,
		    msg, gn->name);
		(void) fflush(stdout);
  		return FALSE;
	    } else {
		(*abortProc)("%s%s %s. Stop", progname, msg, gn->name);
		return FALSE;
	    }
	}
    }
    return TRUE;
}

/*-
 *-----------------------------------------------------------------------
 * JobExec --
 *	Execute the shell for the given job. Called from JobStart and
 *	JobRestart.
 *
 * Input:
 *	job		Job to execute
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	A shell is executed, outputs is altered and the Job structure added
 *	to the job table.
 *
 *-----------------------------------------------------------------------
 */
static void
JobExec(Job *job, char **argv)
{
    int	    	  cpid;	    	/* ID of new child */
    sigset_t	  mask;

    job->flags &= ~JOB_TRACED;

    if (DEBUG(JOB)) {
	int 	  i;

	(void) fprintf(stdout, "Running %s %sly\n", job->node->name,
		       job->flags&JOB_REMOTE?"remote":"local");
	(void) fprintf(stdout, "\tCommand: ");
	for (i = 0; argv[i] != NULL; i++) {
	    (void) fprintf(stdout, "%s ", argv[i]);
	}
 	(void) fprintf(stdout, "\n");
 	(void) fflush(stdout);
    }

    /*
     * Some jobs produce no output and it's disconcerting to have
     * no feedback of their running (since they produce no output, the
     * banner with their name in it never appears). This is an attempt to
     * provide that feedback, even if nothing follows it.
     */
    if ((lastNode != job->node) && (job->flags & JOB_FIRST) &&
	!(job->flags & JOB_SILENT)) {
	MESSAGE(stdout, job->node);
	lastNode = job->node;
    }

    /* No interruptions until this job is on the `jobs' list */
    JobSigLock(&mask);

    if ((cpid = vfork()) == -1) {
	Punt("Cannot vfork: %s", strerror(errno));
    } else if (cpid == 0) {

	/*
	 * Reset all signal handlers; this is necessary because we also
	 * need to unblock signals before we exec(2).
	 */
	JobSigReset();

	/* Now unblock signals */
	sigemptyset(&mask);
	JobSigUnlock(&mask);

	/*
	 * Must duplicate the input stream down to the child's input and
	 * reset it to the beginning (again). Since the stream was marked
	 * close-on-exec, we must clear that bit in the new input.
	 */
	if (dup2(FILENO(job->cmdFILE), 0) == -1) {
	    execError("dup2", "job->cmdFILE");
	    _exit(1);
	}
	(void) fcntl(0, F_SETFD, 0);
	(void) lseek(0, (off_t)0, SEEK_SET);

	if (job->node->type & OP_MAKE) {
		/*
		 * Pass job token pipe to submakes.
		 */
		fcntl(job_pipe[0], F_SETFD, 0);
		fcntl(job_pipe[1], F_SETFD, 0);
	}

	if (usePipes) {
	    /*
	     * Set up the child's output to be routed through the pipe
	     * we've created for it.
	     */
	    if (dup2(job->outPipe, 1) == -1) {
		execError("dup2", "job->outPipe");
		_exit(1);
	    }
	} else {
	    /*
	     * We're capturing output in a file, so we duplicate the
	     * descriptor to the temporary file into the standard
	     * output.
	     */
	    if (dup2(job->outFd, 1) == -1) {
		execError("dup2", "job->outFd");
		_exit(1);
	    }
	}
	/*
	 * The output channels are marked close on exec. This bit was
	 * duplicated by the dup2 (on some systems), so we have to clear
	 * it before routing the shell's error output to the same place as
	 * its standard output.
	 */
	(void) fcntl(1, F_SETFD, 0);
	if (dup2(1, 2) == -1) {
	    execError("dup2", "1, 2");
	    _exit(1);
	}

#ifdef USE_PGRP
	/*
	 * We want to switch the child into a different process family so
	 * we can kill it and all its descendants in one fell swoop,
	 * by killing its process family, but not commit suicide.
	 */
# if defined(SYSV)
	(void) setsid();
# else
	(void) setpgid(0, getpid());
# endif
#endif /* USE_PGRP */

	(void) execv(shellPath, argv);
	execError("exec", shellPath);
	_exit(1);
    } else {
	job->pid = cpid;

	Trace_Log(JOBSTART, job);

	if (usePipes && (job->flags & JOB_FIRST)) {
	    /*
	     * The first time a job is run for a node, we set the current
	     * position in the buffer to the beginning and mark another
	     * stream to watch in the outputs mask
	     */
	    job->curPos = 0;
	    watchfd(job);
	}

	if (job->flags & JOB_REMOTE) {
	    job->rmtID = 0;
	} else {
	    nLocal += 1;
	    /*
	     * XXX: Used to not happen if REMOTE. Why?
	     */
	    if (job->cmdFILE != NULL && job->cmdFILE != stdout) {
		(void) fclose(job->cmdFILE);
		job->cmdFILE = NULL;
	    }
	}
    }

    /*
     * Now the job is actually running, add it to the table.
     */
    if (DEBUG(JOB)) {
	printf("JobExec(%s): pid %d added to jobs table\n",
		job->node->name, job->pid);
    }
    nJobs += 1;
    (void) Lst_AtEnd(jobs, (ClientData)job);
    JobSigUnlock(&mask);
}

/*-
 *-----------------------------------------------------------------------
 * JobMakeArgv --
 *	Create the argv needed to execute the shell for a given job.
 *
 *
 * Results:
 *
 * Side Effects:
 *
 *-----------------------------------------------------------------------
 */
static void
JobMakeArgv(Job *job, char **argv)
{
    int	    	  argc;
    static char args[10]; 	/* For merged arguments */

    argv[0] = UNCONST(shellName);
    argc = 1;

    if ((commandShell->exit && (*commandShell->exit != '-')) ||
	(commandShell->echo && (*commandShell->echo != '-')))
    {
	/*
	 * At least one of the flags doesn't have a minus before it, so
	 * merge them together. Have to do this because the *(&(@*#*&#$#
	 * Bourne shell thinks its second argument is a file to source.
	 * Grrrr. Note the ten-character limitation on the combined arguments.
	 */
	(void)snprintf(args, sizeof(args), "-%s%s",
		      ((job->flags & JOB_IGNERR) ? "" :
		       (commandShell->exit ? commandShell->exit : "")),
		      ((job->flags & JOB_SILENT) ? "" :
		       (commandShell->echo ? commandShell->echo : "")));

	if (args[1]) {
	    argv[argc] = args;
	    argc++;
	}
    } else {
	if (!(job->flags & JOB_IGNERR) && commandShell->exit) {
	    argv[argc] = UNCONST(commandShell->exit);
	    argc++;
	}
	if (!(job->flags & JOB_SILENT) && commandShell->echo) {
	    argv[argc] = UNCONST(commandShell->echo);
	    argc++;
	}
    }
    argv[argc] = NULL;
}

/*-
 *-----------------------------------------------------------------------
 * JobRestart --
 *	Restart a job that stopped for some reason.
 *
 * Input:
 *	job		Job to restart
 *
 * Results:
 *	1 if max number of running jobs has been reached, 0 otherwise.
 *
 *-----------------------------------------------------------------------
 */
static int
JobRestart(Job *job)
{
    if (job->flags & JOB_REMIGRATE) {
	if (
	    DEBUG(JOB)) {
	   (void) fprintf(stdout, "*** remigrating %x(%s)\n",
			   job->pid, job->node->name);
	   (void) fflush(stdout);
	}

	    if (nLocal != maxLocal) {
		/*
		 * Job cannot be remigrated, but there's room on the local
		 * machine, so resume the job and note that another
		 * local job has started.
		 */
		if (
		    DEBUG(JOB)) {
		    (void) fprintf(stdout, "*** resuming on local machine\n");
		    (void) fflush(stdout);
		}
		KILL(job->pid, SIGCONT);
		nLocal +=1;
		job->flags &= ~(JOB_REMIGRATE|JOB_RESUME);
	    } else {
		/*
		 * Job cannot be restarted. Mark the table as full and
		 * place the job back on the list of stopped jobs.
		 */
		if (
		    DEBUG(JOB)) {
		   (void) fprintf(stdout, "*** holding\n");
		   (void) fflush(stdout);
  		}
		(void)Lst_AtFront(stoppedJobs, (ClientData)job);
		return 1;
	    }

	(void)Lst_AtEnd(jobs, (ClientData)job);
	nJobs += 1;
    } else if (job->flags & JOB_RESTART) {
	/*
	 * Set up the control arguments to the shell. This is based on the
	 * flags set earlier for this job. If the JOB_IGNERR flag is clear,
	 * the 'exit' flag of the commandShell is used to cause it to exit
	 * upon receiving an error. If the JOB_SILENT flag is clear, the
	 * 'echo' flag of the commandShell is used to get it to start echoing
	 * as soon as it starts processing commands.
	 */
	char	  *argv[10];

	JobMakeArgv(job, argv);

	if (DEBUG(JOB)) {
	    (void) fprintf(stdout, "Restarting %s...", job->node->name);
	    (void) fflush(stdout);
	}
	{
	    if (((nLocal >= maxLocal) && !(job->flags & JOB_SPECIAL))) {
		/*
		 * Can't be exported and not allowed to run locally -- put it
		 * back on the hold queue and mark the table full
		 */
		if (DEBUG(JOB)) {
		    (void) fprintf(stdout, "holding\n");
		    (void) fflush(stdout);
		}
		(void)Lst_AtFront(stoppedJobs, (ClientData)job);
		return 1;
	    } else {
		/*
		 * Job may be run locally.
		 */
		if (DEBUG(JOB)) {
		    (void) fprintf(stdout, "running locally\n");
		    (void) fflush(stdout);
		}
		job->flags &= ~JOB_REMOTE;
	    }
	}
	JobExec(job, argv);
    } else {
	/*
	 * The job has stopped and needs to be restarted. Why it stopped,
	 * we don't know...
	 */
	if (DEBUG(JOB)) {
	   (void) fprintf(stdout, "Resuming %s...", job->node->name);
	   (void) fflush(stdout);
	}
	if ((nJobs != maxJobs) &&
	    ((job->flags & JOB_REMOTE) ||
	     (nLocal < maxLocal) ||
	     ((maxLocal == 0) &&
		((job->flags & JOB_SPECIAL)
	    ))))
	{
	    /*
	     * If the job is remote, it's ok to resume it as long as the
	     * maximum concurrency won't be exceeded. If it's local and
	     * we haven't reached the local concurrency limit already (or the
	     * job must be run locally and maxLocal is 0), it's also ok to
	     * resume it.
	     */
	    Boolean error;
	    int status;

	    error = (KILL(job->pid, SIGCONT) != 0);

	    if (!error) {
		/*
		 * Make sure the user knows we've continued the beast and
		 * actually put the thing in the job table.
		 */
		job->flags |= JOB_CONTINUING;
		status = W_STOPCODE(SIGCONT);
		JobFinish(job, &status);

		job->flags &= ~(JOB_RESUME|JOB_CONTINUING);
		if (DEBUG(JOB)) {
		   (void) fprintf(stdout, "done\n");
		   (void) fflush(stdout);
		}
	    } else {
		Error("couldn't resume %s: %s",
		    job->node->name, strerror(errno));
		status = W_EXITCODE(1, 0);
		JobFinish(job, &status);
	    }
	} else {
	    /*
	     * Job cannot be restarted. Mark the table as full and
	     * place the job back on the list of stopped jobs.
	     */
	    if (DEBUG(JOB)) {
		(void) fprintf(stdout, "table full\n");
		(void) fflush(stdout);
	    }
	    (void) Lst_AtFront(stoppedJobs, (ClientData)job);
	    return 1;
	}
    }
    return 0;
}

/*-
 *-----------------------------------------------------------------------
 * JobStart  --
 *	Start a target-creation process going for the target described
 *	by the graph node gn.
 *
 * Input:
 *	gn		target to create
 *	flags		flags for the job to override normal ones.
 *			e.g. JOB_SPECIAL or JOB_IGNDOTS
 *	previous	The previous Job structure for this node, if any.
 *
 * Results:
 *	JOB_ERROR if there was an error in the commands, JOB_FINISHED
 *	if there isn't actually anything left to do for the job and
 *	JOB_RUNNING if the job has been started.
 *
 * Side Effects:
 *	A new Job node is created and added to the list of running
 *	jobs. PMake is forked and a child shell created.
 *-----------------------------------------------------------------------
 */
static int
JobStart(GNode *gn, int flags, Job *previous)
{
    Job		  *job;       /* new job descriptor */
    char	  *argv[10];  /* Argument vector to shell */
    Boolean	  cmdsOK;     /* true if the nodes commands were all right */
    Boolean 	  local;      /* Set true if the job was run locally */
    Boolean 	  noExec;     /* Set true if we decide not to run the job */
    int		  tfd;	      /* File descriptor to the temp file */

    if (previous != NULL) {
	previous->flags &= ~(JOB_FIRST|JOB_IGNERR|JOB_SILENT|JOB_REMOTE);
	job = previous;
    } else {
	job = emalloc(sizeof(Job));
	if (job == NULL) {
	    Punt("JobStart out of memory");
	}
	flags |= JOB_FIRST;
    }
    if (gn->type & OP_SPECIAL)
	flags |= JOB_SPECIAL;

    job->node = gn;
    job->tailCmds = NILLNODE;

    /*
     * Set the initial value of the flags for this job based on the global
     * ones and the node's attributes... Any flags supplied by the caller
     * are also added to the field.
     */
    job->flags = 0;
    if (Targ_Ignore(gn)) {
	job->flags |= JOB_IGNERR;
    }
    if (Targ_Silent(gn)) {
	job->flags |= JOB_SILENT;
    }
    job->flags |= flags;

    /*
     * Check the commands now so any attributes from .DEFAULT have a chance
     * to migrate to the node
     */
    if (!compatMake && job->flags & JOB_FIRST) {
	cmdsOK = Job_CheckCommands(gn, Error);
    } else {
	cmdsOK = TRUE;
    }

    job->inPollfd = NULL;

    /*
     * If the -n flag wasn't given, we open up OUR (not the child's)
     * temporary file to stuff commands in it. The thing is rd/wr so we don't
     * need to reopen it to feed it to the shell. If the -n flag *was* given,
     * we just set the file to be stdout. Cute, huh?
     */
    if (((gn->type & OP_MAKE) && !(noRecursiveExecute)) ||
	(!noExecute && !touchFlag)) {
	/*
	 * tfile is the name of a file into which all shell commands are
	 * put. It is used over by removing it before the child shell is
	 * executed. The XXXXXX in the string are replaced by the pid of
	 * the make process in a 6-character field with leading zeroes.
	 */
	char     tfile[sizeof(TMPPAT)];
	sigset_t mask;
	/*
	 * We're serious here, but if the commands were bogus, we're
	 * also dead...
	 */
	if (!cmdsOK) {
	    DieHorribly();
	}

	JobSigLock(&mask);
	(void)strcpy(tfile, TMPPAT);
	if ((tfd = mkstemp(tfile)) == -1)
	    Punt("Could not create temporary file %s", strerror(errno));
	if (!DEBUG(SCRIPT))
		(void) eunlink(tfile);
	JobSigUnlock(&mask);

	job->cmdFILE = fdopen(tfd, "w+");
	if (job->cmdFILE == NULL) {
	    Punt("Could not fdopen %s", tfile);
	}
	(void) fcntl(FILENO(job->cmdFILE), F_SETFD, 1);
	/*
	 * Send the commands to the command file, flush all its buffers then
	 * rewind and remove the thing.
	 */
	noExec = FALSE;

	/*
	 * used to be backwards; replace when start doing multiple commands
	 * per shell.
	 */
	if (compatMake) {
	    /*
	     * Be compatible: If this is the first time for this node,
	     * verify its commands are ok and open the commands list for
	     * sequential access by later invocations of JobStart.
	     * Once that is done, we take the next command off the list
	     * and print it to the command file. If the command was an
	     * ellipsis, note that there's nothing more to execute.
	     */
	    if ((job->flags&JOB_FIRST) && (Lst_Open(gn->commands) != SUCCESS)){
		cmdsOK = FALSE;
	    } else {
		LstNode	ln = Lst_Next(gn->commands);

		if ((ln == NILLNODE) ||
		    JobPrintCommand((ClientData) Lst_Datum(ln),
				    (ClientData) job))
		{
		    noExec = TRUE;
		    Lst_Close(gn->commands);
		}
		if (noExec && !(job->flags & JOB_FIRST)) {
		    /*
		     * If we're not going to execute anything, the job
		     * is done and we need to close down the various
		     * file descriptors we've opened for output, then
		     * call JobDoOutput to catch the final characters or
		     * send the file to the screen... Note that the i/o streams
		     * are only open if this isn't the first job.
		     * Note also that this could not be done in
		     * Job_CatchChildren b/c it wasn't clear if there were
		     * more commands to execute or not...
		     */
		    JobClose(job);
		}
	    }
	} else {
	    /*
	     * We can do all the commands at once. hooray for sanity
	     */
	    numCommands = 0;
	    Lst_ForEach(gn->commands, JobPrintCommand, (ClientData)job);

	    /*
	     * If we didn't print out any commands to the shell script,
	     * there's not much point in executing the shell, is there?
	     */
	    if (numCommands == 0) {
		noExec = TRUE;
	    }
	}
    } else if (NoExecute(gn)) {
	/*
	 * Not executing anything -- just print all the commands to stdout
	 * in one fell swoop. This will still set up job->tailCmds correctly.
	 */
	if (lastNode != gn) {
	    MESSAGE(stdout, gn);
	    lastNode = gn;
	}
	job->cmdFILE = stdout;
	/*
	 * Only print the commands if they're ok, but don't die if they're
	 * not -- just let the user know they're bad and keep going. It
	 * doesn't do any harm in this case and may do some good.
	 */
	if (cmdsOK) {
	    Lst_ForEach(gn->commands, JobPrintCommand, (ClientData)job);
	}
	/*
	 * Don't execute the shell, thank you.
	 */
	noExec = TRUE;
    } else {
	/*
	 * Just touch the target and note that no shell should be executed.
	 * Set cmdFILE to stdout to make life easier. Check the commands, too,
	 * but don't die if they're no good -- it does no harm to keep working
	 * up the graph.
	 */
	job->cmdFILE = stdout;
    	Job_Touch(gn, job->flags&JOB_SILENT);
	noExec = TRUE;
    }

    /*
     * If we're not supposed to execute a shell, don't.
     */
    if (noExec) {
	/*
	 * Unlink and close the command file if we opened one
	 */
	if (job->cmdFILE != stdout) {
	    if (job->cmdFILE != NULL) {
		(void) fclose(job->cmdFILE);
		job->cmdFILE = NULL;
	    }
	} else {
	     (void) fflush(stdout);
	}

	/*
	 * We only want to work our way up the graph if we aren't here because
	 * the commands for the job were no good.
	 */
	if (cmdsOK) {
	    if (aborting == 0) {
		if (job->tailCmds != NILLNODE) {
		    Lst_ForEachFrom(job->node->commands, job->tailCmds,
				    JobSaveCommand,
				   (ClientData)job->node);
		}
		if (!(job->flags & JOB_SPECIAL))
		    Job_TokenReturn();
		job->node->made = MADE;
		Make_Update(job->node);
	    }
	    free((Address)job);
	    return(JOB_FINISHED);
	} else {
	    free((Address)job);
	    return(JOB_ERROR);
	}
    } else {
	(void) fflush(job->cmdFILE);
    }

    /*
     * Set up the control arguments to the shell. This is based on the flags
     * set earlier for this job.
     */
    JobMakeArgv(job, argv);

    /*
     * If we're using pipes to catch output, create the pipe by which we'll
     * get the shell's output. If we're using files, print out that we're
     * starting a job and then set up its temporary-file name.
     */
    if (!compatMake || (job->flags & JOB_FIRST)) {
	if (usePipes) {
	    int fd[2];
	    if (pipe(fd) == -1)
		Punt("Cannot create pipe: %s", strerror(errno));
	    job->inPipe = fd[0];
	    job->outPipe = fd[1];
	    (void) fcntl(job->inPipe, F_SETFD, 1);
	    (void) fcntl(job->outPipe, F_SETFD, 1);
	} else {
	    (void) fprintf(stdout, "Remaking `%s'\n", gn->name);
  	    (void) fflush(stdout);
	    (void) strcpy(job->outFile, TMPPAT);
	    job->outFd = mkstemp(job->outFile);
	    (void) fcntl(job->outFd, F_SETFD, 1);
	}
    }

    local = TRUE;

    if (local && (((nLocal >= maxLocal) &&
	!(job->flags & JOB_SPECIAL) &&
	(maxLocal != 0)
	)))
    {
	/*
	 * The job can only be run locally, but we've hit the limit of
	 * local concurrency, so put the job on hold until some other job
	 * finishes. Note that the special jobs (.BEGIN, .INTERRUPT and .END)
	 * may be run locally even when the local limit has been reached
	 * (e.g. when maxLocal == 0), though they will be exported if at
	 * all possible. In addition, any target marked with .NOEXPORT will
	 * be run locally if maxLocal is 0.
	 */
	job->flags |= JOB_RESTART;
	(void) Lst_AtEnd(stoppedJobs, (ClientData)job);
    } else {
	JobExec(job, argv);
    }
    return(JOB_RUNNING);
}

static char *
JobOutput(Job *job, char *cp, char *endp, int msg)
{
    char *ecp;

    if (commandShell->noPrint) {
	ecp = Str_FindSubstring(cp, commandShell->noPrint);
	while (ecp != NULL) {
	    if (cp != ecp) {
		*ecp = '\0';
		if (msg && job->node != lastNode) {
		    MESSAGE(stdout, job->node);
		    lastNode = job->node;
		}
		/*
		 * The only way there wouldn't be a newline after
		 * this line is if it were the last in the buffer.
		 * however, since the non-printable comes after it,
		 * there must be a newline, so we don't print one.
		 */
		(void) fprintf(stdout, "%s", cp);
		(void) fflush(stdout);
	    }
	    cp = ecp + commandShell->noPLen;
	    if (cp != endp) {
		/*
		 * Still more to print, look again after skipping
		 * the whitespace following the non-printable
		 * command....
		 */
		cp++;
		while (*cp == ' ' || *cp == '\t' || *cp == '\n') {
		    cp++;
		}
		ecp = Str_FindSubstring(cp, commandShell->noPrint);
	    } else {
		return cp;
	    }
	}
    }
    return cp;
}

/*-
 *-----------------------------------------------------------------------
 * JobDoOutput  --
 *	This function is called at different times depending on
 *	whether the user has specified that output is to be collected
 *	via pipes or temporary files. In the former case, we are called
 *	whenever there is something to read on the pipe. We collect more
 *	output from the given job and store it in the job's outBuf. If
 *	this makes up a line, we print it tagged by the job's identifier,
 *	as necessary.
 *	If output has been collected in a temporary file, we open the
 *	file and read it line by line, transfering it to our own
 *	output channel until the file is empty. At which point we
 *	remove the temporary file.
 *	In both cases, however, we keep our figurative eye out for the
 *	'noPrint' line for the shell from which the output came. If
 *	we recognize a line, we don't print it. If the command is not
 *	alone on the line (the character after it is not \0 or \n), we
 *	do print whatever follows it.
 *
 * Input:
 *	job		the job whose output needs printing
 *	finish		TRUE if this is the last time we'll be called
 *			for this job
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	curPos may be shifted as may the contents of outBuf.
 *-----------------------------------------------------------------------
 */
static void
JobDoOutput(Job *job, Boolean finish)
{
    Boolean       gotNL = FALSE;  /* true if got a newline */
    Boolean       fbuf;  	  /* true if our buffer filled up */
    int		  nr;	      	  /* number of bytes read */
    int		  i;	      	  /* auxiliary index into outBuf */
    int		  max;	      	  /* limit for i (end of current data) */
    int		  nRead;      	  /* (Temporary) number of bytes read */

    FILE      	  *oFILE;	  /* Stream pointer to shell's output file */
    char          inLine[132];


    if (usePipes) {
	/*
	 * Read as many bytes as will fit in the buffer.
	 */
end_loop:
	gotNL = FALSE;
	fbuf = FALSE;

	nRead = read(job->inPipe, &job->outBuf[job->curPos],
			 JOB_BUFSIZE - job->curPos);
	if (nRead < 0) {
	    if (DEBUG(JOB)) {
		perror("JobDoOutput(piperead)");
	    }
	    nr = 0;
	} else {
	    nr = nRead;
	}

	/*
	 * If we hit the end-of-file (the job is dead), we must flush its
	 * remaining output, so pretend we read a newline if there's any
	 * output remaining in the buffer.
	 * Also clear the 'finish' flag so we stop looping.
	 */
	if ((nr == 0) && (job->curPos != 0)) {
	    job->outBuf[job->curPos] = '\n';
	    nr = 1;
	    finish = FALSE;
	} else if (nr == 0) {
	    finish = FALSE;
	}

	/*
	 * Look for the last newline in the bytes we just got. If there is
	 * one, break out of the loop with 'i' as its index and gotNL set
	 * TRUE.
	 */
	max = job->curPos + nr;
	for (i = job->curPos + nr - 1; i >= job->curPos; i--) {
	    if (job->outBuf[i] == '\n') {
		gotNL = TRUE;
		break;
	    } else if (job->outBuf[i] == '\0') {
		/*
		 * Why?
		 */
		job->outBuf[i] = ' ';
	    }
	}

	if (!gotNL) {
	    job->curPos += nr;
	    if (job->curPos == JOB_BUFSIZE) {
		/*
		 * If we've run out of buffer space, we have no choice
		 * but to print the stuff. sigh.
		 */
		fbuf = TRUE;
		i = job->curPos;
	    }
	}
	if (gotNL || fbuf) {
	    /*
	     * Need to send the output to the screen. Null terminate it
	     * first, overwriting the newline character if there was one.
	     * So long as the line isn't one we should filter (according
	     * to the shell description), we print the line, preceded
	     * by a target banner if this target isn't the same as the
	     * one for which we last printed something.
	     * The rest of the data in the buffer are then shifted down
	     * to the start of the buffer and curPos is set accordingly.
	     */
	    job->outBuf[i] = '\0';
	    if (i >= job->curPos) {
		char *cp;

		cp = JobOutput(job, job->outBuf, &job->outBuf[i], FALSE);

		/*
		 * There's still more in that thar buffer. This time, though,
		 * we know there's no newline at the end, so we add one of
		 * our own free will.
		 */
		if (*cp != '\0') {
		    if (job->node != lastNode) {
			MESSAGE(stdout, job->node);
			lastNode = job->node;
		    }
		    (void) fprintf(stdout, "%s%s", cp, gotNL ? "\n" : "");
		    (void) fflush(stdout);
		}
	    }
	    if (i < max - 1) {
		/* shift the remaining characters down */
		(void) memcpy(job->outBuf, &job->outBuf[i + 1], max - (i + 1));
		job->curPos = max - (i + 1);

	    } else {
		/*
		 * We have written everything out, so we just start over
		 * from the start of the buffer. No copying. No nothing.
		 */
		job->curPos = 0;
	    }
	}
	if (finish) {
	    /*
	     * If the finish flag is true, we must loop until we hit
	     * end-of-file on the pipe. This is guaranteed to happen
	     * eventually since the other end of the pipe is now closed
	     * (we closed it explicitly and the child has exited). When
	     * we do get an EOF, finish will be set FALSE and we'll fall
	     * through and out.
	     */
	    goto end_loop;
	}
    } else {
	/*
	 * We've been called to retrieve the output of the job from the
	 * temporary file where it's been squirreled away. This consists of
	 * opening the file, reading the output line by line, being sure not
	 * to print the noPrint line for the shell we used, then close and
	 * remove the temporary file. Very simple.
	 *
	 * Change to read in blocks and do FindSubString type things as for
	 * pipes? That would allow for "@echo -n..."
	 */
	oFILE = fopen(job->outFile, "r");
	if (oFILE != NULL) {
	    (void) fprintf(stdout, "Results of making %s:\n", job->node->name);
	    (void) fflush(stdout);
	    while (fgets(inLine, sizeof(inLine), oFILE) != NULL) {
		char	*cp, *endp, *oendp;

		cp = inLine;
		oendp = endp = inLine + strlen(inLine);
		if (endp[-1] == '\n') {
		    *--endp = '\0';
		}
		cp = JobOutput(job, inLine, endp, FALSE);

		/*
		 * There's still more in that thar buffer. This time, though,
		 * we know there's no newline at the end, so we add one of
		 * our own free will.
		 */
		(void) fprintf(stdout, "%s", cp);
		(void) fflush(stdout);
		if (endp != oendp) {
		    (void) fprintf(stdout, "\n");
		    (void) fflush(stdout);
		}
	    }
	    (void) fclose(oFILE);
	    (void) eunlink(job->outFile);
	} else {
	    Punt("Cannot open `%s'", job->outFile);
	}
    }
}

/*-
 *-----------------------------------------------------------------------
 * Job_CatchChildren --
 *	Handle the exit of a child. Called from Make_Make.
 *
 * Input:
 *	block		TRUE if should block on the wait
 *
 * Results:
 *	none.
 *
 * Side Effects:
 *	The job descriptor is removed from the list of children.
 *
 * Notes:
 *	We do waits, blocking or not, according to the wisdom of our
 *	caller, until there are no more children to report. For each
 *	job, call JobFinish to finish things off. This will take care of
 *	putting jobs on the stoppedJobs queue.
 *
 *-----------------------------------------------------------------------
 */
void
Job_CatchChildren(Boolean block)
{
    int    	  pid;	    	/* pid of dead child */
    Job		  *job;	    	/* job descriptor for dead child */
    LstNode       jnode;    	/* list element for finding job */
    int	  	  status;   	/* Exit/termination status */

    /*
     * Don't even bother if we know there's no one around.
     */
    if (nLocal == 0) {
	return;
    }

    while ((pid = waitpid((pid_t) -1, &status,
			  (block?0:WNOHANG)|WUNTRACED)) > 0)
    {
	if (DEBUG(JOB)) {
	    (void) fprintf(stdout, "Process %d exited or stopped %x.\n", pid,
	      status);
	    (void) fflush(stdout);
	}

	jnode = Lst_Find(jobs, (ClientData)&pid, JobCmpPid);
	if (jnode == NILLNODE) {
	    if (WIFSTOPPED(status) && (WSTOPSIG(status) == SIGCONT)) {
		jnode = Lst_Find(stoppedJobs, (ClientData) &pid, JobCmpPid);
		if (jnode == NILLNODE) {
		    Error("Resumed child (%d) not in table", pid);
		    continue;
		}
		job = (Job *)Lst_Datum(jnode);
		(void) Lst_Remove(stoppedJobs, jnode);
	    } else {
		Error("Child (%d) not in table?", pid);
		continue;
	    }
	} else {
	    job = (Job *) Lst_Datum(jnode);
	    (void) Lst_Remove(jobs, jnode);
	    nJobs -= 1;
	    nLocal -= 1;
	}

	JobFinish(job, &status);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Job_CatchOutput --
 *	Catch the output from our children, if we're using
 *	pipes do so. Otherwise just block time until we get a
 *	signal (most likely a SIGCHLD) since there's no point in
 *	just spinning when there's nothing to do and the reaping
 *	of a child can wait for a while.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Output is read from pipes if we're piping.
 * -----------------------------------------------------------------------
 */
void
Job_CatchOutput(void)
{
    int           	  nready;
    LstNode		  ln;
    Job  	 	  *job;
    (void) fflush(stdout);
    Job_TokenFlush();
    if (usePipes) {
	if ((nready = poll((wantToken ? fds : (fds + 1)),
	  		   (wantToken ? nfds : (nfds - 1)), POLL_MSEC)) <= 0) {
	    return;
	} else {
	    sigset_t	mask;
	    JobSigLock(&mask);
	    if (Lst_Open(jobs) == FAILURE) {
		Punt("Cannot open job table");
	    }

	    if (readyfd(&childExitJob)) {
		char token;
		(void) read(childExitJob.inPipe, &token, 1);
		nready -= 1;
	    }

	    while (nready && (ln = Lst_Next(jobs)) != NILLNODE) {
		job = (Job *) Lst_Datum(ln);
		if (readyfd(job)) {
		    JobDoOutput(job, FALSE);
		    nready -= 1;
		}
	    }
	    Lst_Close(jobs);
	    JobSigUnlock(&mask);
	}
    }
}

/*-
 *-----------------------------------------------------------------------
 * Job_Make --
 *	Start the creation of a target. Basically a front-end for
 *	JobStart used by the Make module.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Another job is started.
 *
 *-----------------------------------------------------------------------
 */
void
Job_Make(GNode *gn)
{
    (void) JobStart(gn, 0, NULL);
}

void
Shell_Init()
{
    if (shellPath == NULL) {
	/*
	 * The user didn't specify a shell to use, so we are using the
	 * default one... Both the absolute path and the last component
	 * must be set. The last component is taken from the 'name' field
	 * of the default shell description pointed-to by commandShell.
	 * All default shells are located in _PATH_DEFSHELLDIR.
	 */
	shellName = commandShell->name;
	shellPath = str_concat(_PATH_DEFSHELLDIR, shellName, STR_ADDSLASH);
    }
    if (commandShell->exit == NULL) {
	commandShell->exit = "";
    }
    if (commandShell->echo == NULL) {
	commandShell->echo = "";
    }
}

/*-
 *-----------------------------------------------------------------------
 * Job_Init --
 *	Initialize the process module
 *
 * Input:
 *	maxproc		the greatest number of jobs which may be running
 *			at one time
 *	maxlocal	the greatest number of jobs which may be running
 *			at once
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	lists and counters are initialized
 *-----------------------------------------------------------------------
 */
void
Job_Init(int maxproc, int maxlocal)
{
    jobs =  	  Lst_Init(FALSE);
    stoppedJobs = Lst_Init(FALSE);
    maxJobs = 	  maxproc;
    maxLocal = 	  maxlocal;
    nJobs = 	  0;
    nLocal = 	  0;
    wantToken =	  FALSE;

    aborting = 	  0;
    errors = 	  0;

    lastNode =	  NILGNODE;

    if (maxJobs == 1
		     ) {
	/*
	 * If only one job can run at a time, there's no need for a banner,
	 * is there?
	 */
	targFmt = "";
    } else {
	targFmt = TARG_FMT;
    }

    Shell_Init();

    if (pipe(exit_pipe) < 0)
	Fatal("error in pipe: %s", strerror(errno));
    fcntl(exit_pipe[0], F_SETFD, 1);
    fcntl(exit_pipe[1], F_SETFD, 1);

    childExitJob.inPipe = exit_pipe[0];

    sigemptyset(&caught_signals);
    /*
     * Install a SIGCHLD handler.
     */
    (void)signal(SIGCHLD, JobChildSig);
    sigaddset(&caught_signals, SIGCHLD);

#define ADDSIG(s,h)				\
    if (signal(s, SIG_IGN) != SIG_IGN) {	\
	sigaddset(&caught_signals, s);		\
	(void) signal(s, h);			\
    }

    /*
     * Catch the four signals that POSIX specifies if they aren't ignored.
     * JobPassSig will take care of calling JobInterrupt if appropriate.
     */
    ADDSIG(SIGINT, JobPassSig)
    ADDSIG(SIGHUP, JobPassSig)
    ADDSIG(SIGTERM, JobPassSig)
    ADDSIG(SIGQUIT, JobPassSig)

    /*
     * There are additional signals that need to be caught and passed if
     * either the export system wants to be told directly of signals or if
     * we're giving each job its own process group (since then it won't get
     * signals from the terminal driver as we own the terminal)
     */
#if defined(USE_PGRP)
    ADDSIG(SIGTSTP, JobPassSig)
    ADDSIG(SIGTTOU, JobPassSig)
    ADDSIG(SIGTTIN, JobPassSig)
    ADDSIG(SIGWINCH, JobPassSig)
    ADDSIG(SIGCONT, JobContinueSig)
#endif
#undef ADDSIG
}

static void JobSigReset(void)
{
#define DELSIG(s)					\
    if (sigismember(&caught_signals, s)) {		\
	(void) signal(SIGINT, SIG_DFL);			\
    }

    DELSIG(SIGINT)
    DELSIG(SIGHUP)
    DELSIG(SIGQUIT)
    DELSIG(SIGTERM)
#if defined(USE_PGRP)
    DELSIG(SIGTSTP)
    DELSIG(SIGTTOU)
    DELSIG(SIGTTIN)
    DELSIG(SIGWINCH)
    DELSIG(SIGCONT)
#endif
#undef DELSIG
    (void)signal(SIGCHLD, SIG_DFL);
}

/*-
 *-----------------------------------------------------------------------
 * Job_Empty --
 *	See if the job table is empty.  Because the local concurrency may
 *	be set to 0, it is possible for the job table to become empty,
 *	while the list of stoppedJobs remains non-empty. In such a case,
 *	we want to restart as many jobs as we can.
 *
 * Results:
 *	TRUE if it is. FALSE if it ain't.
 *
 * Side Effects:
 *	None.
 *
 * -----------------------------------------------------------------------
 */
Boolean
Job_Empty(void)
{
    if (nJobs == 0) {
	if (!Lst_IsEmpty(stoppedJobs) && !aborting) {
	    /*
	     * The job table is obviously not full if it has no jobs in
	     * it...Try and restart the stopped jobs.
	     */
	    JobRestartJobs();
	    return(FALSE);
	} else {
	    return(TRUE);
	}
    } else {
	return(FALSE);
    }
}

/*-
 *-----------------------------------------------------------------------
 * JobMatchShell --
 *	Find a shell in 'shells' given its name.
 *
 * Results:
 *	A pointer to the Shell structure.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Shell *
JobMatchShell(const char *name)
{
    Shell	*sh;

    for (sh = shells; sh->name != NULL; sh++) {
	if (strcmp(name, sh->name) == 0)
		return (sh);
    }
    return (NULL);
}

/*-
 *-----------------------------------------------------------------------
 * Job_ParseShell --
 *	Parse a shell specification and set up commandShell, shellPath
 *	and shellName appropriately.
 *
 * Input:
 *	line		The shell spec
 *
 * Results:
 *	FAILURE if the specification was incorrect.
 *
 * Side Effects:
 *	commandShell points to a Shell structure (either predefined or
 *	created from the shell spec), shellPath is the full path of the
 *	shell described by commandShell, while shellName is just the
 *	final component of shellPath.
 *
 * Notes:
 *	A shell specification consists of a .SHELL target, with dependency
 *	operator, followed by a series of blank-separated words. Double
 *	quotes can be used to use blanks in words. A backslash escapes
 *	anything (most notably a double-quote and a space) and
 *	provides the functionality it does in C. Each word consists of
 *	keyword and value separated by an equal sign. There should be no
 *	unnecessary spaces in the word. The keywords are as follows:
 *	    name  	    Name of shell.
 *	    path  	    Location of shell.
 *	    quiet 	    Command to turn off echoing.
 *	    echo  	    Command to turn echoing on
 *	    filter	    Result of turning off echoing that shouldn't be
 *	    	  	    printed.
 *	    echoFlag	    Flag to turn echoing on at the start
 *	    errFlag	    Flag to turn error checking on at the start
 *	    hasErrCtl	    True if shell has error checking control
 *	    check 	    Command to turn on error checking if hasErrCtl
 *	    	  	    is TRUE or template of command to echo a command
 *	    	  	    for which error checking is off if hasErrCtl is
 *	    	  	    FALSE.
 *	    ignore	    Command to turn off error checking if hasErrCtl
 *	    	  	    is TRUE or template of command to execute a
 *	    	  	    command so as to ignore any errors it returns if
 *	    	  	    hasErrCtl is FALSE.
 *
 *-----------------------------------------------------------------------
 */
ReturnStatus
Job_ParseShell(char *line)
{
    char	**words;
    char	**argv;
    int		argc;
    char	*path;
    Shell	newShell;
    Boolean	fullSpec = FALSE;
    Shell	*sh;

    while (isspace((unsigned char)*line)) {
	line++;
    }

    if (shellArgv)
	free(UNCONST(shellArgv));

    memset((Address)&newShell, 0, sizeof(newShell));

    /*
     * Parse the specification by keyword
     */
    words = brk_string(line, &argc, TRUE, &path);
    shellArgv = path;

    for (path = NULL, argv = words; argc != 0; argc--, argv++) {
	    if (strncmp(*argv, "path=", 5) == 0) {
		path = &argv[0][5];
	    } else if (strncmp(*argv, "name=", 5) == 0) {
		newShell.name = &argv[0][5];
	    } else {
		if (strncmp(*argv, "quiet=", 6) == 0) {
		    newShell.echoOff = &argv[0][6];
		} else if (strncmp(*argv, "echo=", 5) == 0) {
		    newShell.echoOn = &argv[0][5];
		} else if (strncmp(*argv, "filter=", 7) == 0) {
		    newShell.noPrint = &argv[0][7];
		    newShell.noPLen = strlen(newShell.noPrint);
		} else if (strncmp(*argv, "echoFlag=", 9) == 0) {
		    newShell.echo = &argv[0][9];
		} else if (strncmp(*argv, "errFlag=", 8) == 0) {
		    newShell.exit = &argv[0][8];
		} else if (strncmp(*argv, "hasErrCtl=", 10) == 0) {
		    char c = argv[0][10];
		    newShell.hasErrCtl = !((c != 'Y') && (c != 'y') &&
					   (c != 'T') && (c != 't'));
		} else if (strncmp(*argv, "check=", 6) == 0) {
		    newShell.errCheck = &argv[0][6];
		} else if (strncmp(*argv, "ignore=", 7) == 0) {
		    newShell.ignErr = &argv[0][7];
		} else if (strncmp(*argv, "errout=", 7) == 0) {
		    newShell.errOut = &argv[0][7];
		} else if (strncmp(*argv, "comment=", 8) == 0) {
		    newShell.commentChar = argv[0][8];
		} else {
		    Parse_Error(PARSE_FATAL, "Unknown keyword \"%s\"",
				*argv);
		    free(words);
		    return(FAILURE);
		}
		fullSpec = TRUE;
	    }
    }

    if (path == NULL) {
	/*
	 * If no path was given, the user wants one of the pre-defined shells,
	 * yes? So we find the one s/he wants with the help of JobMatchShell
	 * and set things up the right way. shellPath will be set up by
	 * Job_Init.
	 */
	if (newShell.name == NULL) {
	    Parse_Error(PARSE_FATAL, "Neither path nor name specified");
	    free(words);
	    return(FAILURE);
	} else {
	    if ((sh = JobMatchShell(newShell.name)) == NULL) {
		    Parse_Error(PARSE_WARNING, "%s: No matching shell",
				newShell.name);
		    free(words);
		    return(FAILURE);
	    }
	    commandShell = sh;
	    shellName = newShell.name;
	}
    } else {
	/*
	 * The user provided a path. If s/he gave nothing else (fullSpec is
	 * FALSE), try and find a matching shell in the ones we know of.
	 * Else we just take the specification at its word and copy it
	 * to a new location. In either case, we need to record the
	 * path the user gave for the shell.
	 */
	shellPath = path;
	path = strrchr(path, '/');
	if (path == NULL) {
	    path = UNCONST(shellPath);
	} else {
	    path += 1;
	}
	if (newShell.name != NULL) {
	    shellName = newShell.name;
	} else {
	    shellName = path;
	}
	if (!fullSpec) {
	    if ((sh = JobMatchShell(shellName)) == NULL) {
		    Parse_Error(PARSE_WARNING, "%s: No matching shell",
				shellName);
		    free(words);
		    return(FAILURE);
	    }
	    commandShell = sh;
	} else {
	    commandShell = emalloc(sizeof(Shell));
	    *commandShell = newShell;
	}
    }

    if (commandShell->echoOn && commandShell->echoOff) {
	commandShell->hasEchoCtl = TRUE;
    }

    if (!commandShell->hasErrCtl) {
	if (commandShell->errCheck == NULL) {
	    commandShell->errCheck = "";
	}
	if (commandShell->ignErr == NULL) {
	    commandShell->ignErr = "%s\n";
	}
    }

    /*
     * Do not free up the words themselves, since they might be in use by the
     * shell specification.
     */
    free(words);
    return SUCCESS;
}

/*-
 *-----------------------------------------------------------------------
 * JobInterrupt --
 *	Handle the receipt of an interrupt.
 *
 * Input:
 *	runINTERRUPT	Non-zero if commands for the .INTERRUPT target
 *			should be executed
 *	signo		signal received
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	All children are killed. Another job will be started if the
 *	.INTERRUPT target was given.
 *-----------------------------------------------------------------------
 */
static void
JobInterrupt(int runINTERRUPT, int signo)
{
    LstNode	ln;		/* element in job table */
    Job		*job;		/* job descriptor in that element */
    sigset_t	mask;

    aborting = ABORT_INTERRUPT;

    JobSigLock(&mask);

    (void) Lst_Open(jobs);
    while ((ln = Lst_Next(jobs)) != NILLNODE) {
	GNode *gn;

	job = (Job *) Lst_Datum(ln);
	gn = job->node;

	if ((gn->type & (OP_JOIN|OP_PHONY)) == 0 && !Targ_Precious(gn)) {
	    char *file = (gn->path == NULL ? gn->name : gn->path);
	    if (!noExecute && eunlink(file) != -1) {
		Error("*** %s removed", file);
	    }
	}
	if (job->pid) {
	    if (DEBUG(JOB)) {
		(void) fprintf(stdout,
			   "JobInterrupt passing signal %d to child %d.\n",
			   signo, job->pid);
		(void) fflush(stdout);
	    }
	    KILL(job->pid, signo);
	}
    }
    Lst_Close(jobs);

    JobSigUnlock(&mask);

    Trace_Log(MAKEINTR, 0);
    exit(signo);
}

/*
 *-----------------------------------------------------------------------
 * Job_Finish --
 *	Do final processing such as the running of the commands
 *	attached to the .END target.
 *
 * Results:
 *	Number of errors reported.
 *
 * Side Effects:
 *	None.
 *-----------------------------------------------------------------------
 */
int
Job_Finish(void)
{
    Job_TokenFlush();
    return(errors);
}

/*-
 *-----------------------------------------------------------------------
 * Job_End --
 *	Cleanup any memory used by the jobs module
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Memory is freed
 *-----------------------------------------------------------------------
 */
void
Job_End(void)
{
#ifdef CLEANUP
    if (shellArgv)
	free(shellArgv);
#endif
}

/*-
 *-----------------------------------------------------------------------
 * Job_Wait --
 *	Waits for all running jobs to finish and returns. Sets 'aborting'
 *	to ABORT_WAIT to prevent other jobs from starting.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Currently running jobs finish.
 *
 *-----------------------------------------------------------------------
 */
void
Job_Wait(void)
{
    aborting = ABORT_WAIT;
    while (nJobs != 0) {
	Job_CatchOutput();
	Job_CatchChildren(!usePipes);
    }
    Job_TokenFlush();
    aborting = 0;
}

/*-
 *-----------------------------------------------------------------------
 * Job_AbortAll --
 *	Abort all currently running jobs without handling output or anything.
 *	This function is to be called only in the event of a major
 *	error. Most definitely NOT to be called from JobInterrupt.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	All children are killed, not just the firstborn
 *-----------------------------------------------------------------------
 */
void
Job_AbortAll(void)
{
    LstNode	ln;	/* element in job table */
    Job		*job;	/* the job descriptor in that element */
    int		foo;
    sigset_t	mask;

    aborting = ABORT_ERROR;

    if (nJobs) {

	JobSigLock(&mask);
	(void) Lst_Open(jobs);
	while ((ln = Lst_Next(jobs)) != NILLNODE) {
	    job = (Job *) Lst_Datum(ln);

	    /*
	     * kill the child process with increasingly drastic signals to make
	     * darn sure it's dead.
	     */
	    KILL(job->pid, SIGINT);
	    KILL(job->pid, SIGKILL);
	}
	Lst_Close(jobs);
	JobSigUnlock(&mask);
    }

    /*
     * Catch as many children as want to report in at first, then give up
     */
    while (waitpid((pid_t) -1, &foo, WNOHANG) > 0)
	continue;
}


/*-
 *-----------------------------------------------------------------------
 * JobRestartJobs --
 *	Tries to restart stopped jobs if there are slots available.
 *	Note that this tries to restart them regardless of pending errors.
 *	It's not good to leave stopped jobs lying around!
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Resumes(and possibly migrates) jobs.
 *
 *-----------------------------------------------------------------------
 */
static void
JobRestartJobs(void)
{
    sigset_t	mask;

    JobSigLock(&mask);
    while (!Lst_IsEmpty(stoppedJobs)) {
	if (DEBUG(JOB)) {
	    (void) fprintf(stdout, "Restarting a stopped job.\n");
	    (void) fflush(stdout);
	}
	if (JobRestart((Job *)Lst_DeQueue(stoppedJobs)) != 0)
		break;
    }
    JobSigUnlock(&mask);
}

static void
watchfd(Job *job)
{
    int i;
    if (job->inPollfd != NULL)
	Punt("Watching watched job");
    if (fds == NULL) {
	maxfds = JBSTART;
	fds = emalloc(sizeof(struct pollfd) * maxfds);
	jobfds = emalloc(sizeof(Job **) * maxfds);

	fds[0].fd = job_pipe[0];
	fds[0].events = POLLIN;
	jobfds[0] = &tokenWaitJob;
	tokenWaitJob.inPollfd = &fds[0];
	nfds++;

	fds[1].fd = exit_pipe[0];
	fds[1].events = POLLIN;
	jobfds[1] = &childExitJob;
	childExitJob.inPollfd = &fds[1];
	nfds++;
    } else if (nfds == maxfds) {
	maxfds *= JBFACTOR;
	fds = erealloc(fds, sizeof(struct pollfd) * maxfds);
	jobfds = erealloc(jobfds, sizeof(Job **) * maxfds);
	for (i = 0; i < nfds; i++)
	    jobfds[i]->inPollfd = &fds[i];
    }

    fds[nfds].fd = job->inPipe;
    fds[nfds].events = POLLIN;
    jobfds[nfds] = job;
    job->inPollfd = &fds[nfds];
    nfds++;
}

static void
clearfd(Job *job)
{
    int i;
    if (job->inPollfd == NULL)
	Punt("Unwatching unwatched job");
    i = job->inPollfd - fds;
    nfds--;
    /*
     * Move last job in table into hole made by dead job.
     */
    if (nfds != i) {
	fds[i] = fds[nfds];
	jobfds[i] = jobfds[nfds];
	jobfds[i]->inPollfd = &fds[i];
    }
    job->inPollfd = NULL;
}

static int
readyfd(Job *job)
{
    if (job->inPollfd == NULL)
	Punt("Polling unwatched job");
    return (job->inPollfd->revents & POLLIN) != 0;
}

/*-
 *-----------------------------------------------------------------------
 * JobTokenAdd --
 *	Put a token into the job pipe so that some make process can start
 *	another job.
 *
 * Side Effects:
 *	Allows more build jobs to be spawned somewhere.
 *
 *-----------------------------------------------------------------------
 */

static void
JobTokenAdd(void)
{

    if (DEBUG(JOB))
	printf("deposit token\n");
    write(job_pipe[1], "+", 1);
}

/*-
 *-----------------------------------------------------------------------
 * Job_ServerStartTokenAdd --
 *	Prep the job token pipe in the root make process.
 *
 *-----------------------------------------------------------------------
 */

void
Job_ServerStart(int maxproc)
{
    int i, flags;
    char jobarg[64];

    if (pipe(job_pipe) < 0)
	Fatal("error in pipe: %s", strerror(errno));

    /*
     * We mark the input side of the pipe non-blocking; we poll(2) the
     * pipe when we're waiting for a job token, but we might lose the
     * race for the token when a new one becomes available, so the read
     * from the pipe should not block.
     */
    flags = fcntl(job_pipe[0], F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(job_pipe[0], F_SETFL, flags);

    /*
     * Mark job pipes as close-on-exec.
     * Note that we will clear this when executing submakes.
     */
    fcntl(job_pipe[0], F_SETFD, 1);
    fcntl(job_pipe[1], F_SETFD, 1);

    snprintf(jobarg, sizeof(jobarg), "%d,%d", job_pipe[0], job_pipe[1]);

    Var_Append(MAKEFLAGS, "-J", VAR_GLOBAL);
    Var_Append(MAKEFLAGS, jobarg, VAR_GLOBAL);

    /*
     * Preload job_pipe with one token per job, save the one
     * "extra" token for the primary job.
     *
     * XXX should clip maxJobs against PIPE_BUF -- if maxJobs is
     * larger than the write buffer size of the pipe, we will
     * deadlock here.
     */
    for (i=1; i < maxproc; i++)
	JobTokenAdd();
}

/*
 * this tracks the number of tokens currently "out" to build jobs.
 */
int jobTokensRunning = 0;
int jobTokensFree = 0;
/*-
 *-----------------------------------------------------------------------
 * Job_TokenReturn --
 *	Return a withdrawn token to the pool.
 *
 *-----------------------------------------------------------------------
 */

void
Job_TokenReturn(void)
{
    jobTokensRunning--;
    if (jobTokensRunning < 0)
	Punt("token botch");
    if (jobTokensRunning)
	jobTokensFree++;
}

/*-
 *-----------------------------------------------------------------------
 * Job_TokenWithdraw --
 *	Attempt to withdraw a token from the pool.
 *
 * Results:
 *	Returns TRUE if a token was withdrawn, and FALSE if the pool
 *	is currently empty.
 *
 * Side Effects:
 * 	If pool is empty, set wantToken so that we wake up
 *	when a token is released.
 *
 *-----------------------------------------------------------------------
 */


Boolean
Job_TokenWithdraw(void)
{
    char tok;
    int count;

    wantToken = FALSE;

    if (aborting)
	    return FALSE;

    if (jobTokensRunning == 0) {
	if (DEBUG(JOB))
	    printf("first one's free\n");
	jobTokensRunning++;
	return TRUE;
    }
    if (jobTokensFree > 0) {
	jobTokensFree--;
	jobTokensRunning++;
	return TRUE;
    }
    count = read(job_pipe[0], &tok, 1);
    if (count == 0)
	Fatal("eof on job pipe!");
    else if (count < 0) {
	if (errno != EAGAIN) {
	    Fatal("job pipe read: %s", strerror(errno));
	}
	if (DEBUG(JOB))
	    printf("blocked for token\n");
	wantToken = TRUE;
	return FALSE;
    }
    jobTokensRunning++;
    if (DEBUG(JOB))
	printf("withdrew token\n");
    return TRUE;
}

/*-
 *-----------------------------------------------------------------------
 * Job_TokenFlush --
 *	Return free tokens to the pool.
 *
 *-----------------------------------------------------------------------
 */

void
Job_TokenFlush(void)
{
    if (compatMake) return;

    while (jobTokensFree > 0) {
	JobTokenAdd();
	jobTokensFree--;
    }
}

#ifdef USE_SELECT
int
emul_poll(struct pollfd *fd, int nfd, int timeout)
{
    fd_set rfds, wfds;
    int i, maxfd, nselect, npoll;
    struct timeval tv, *tvp;
    long usecs;

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);

    maxfd = -1;
    for (i = 0; i < nfd; i++) {
	fd[i].revents = 0;

	if (fd[i].events & POLLIN)
	    FD_SET(fd[i].fd, &rfds);

	if (fd[i].events & POLLOUT)
	    FD_SET(fd[i].fd, &wfds);

	if (fd[i].fd > maxfd)
	    maxfd = fd[i].fd;
    }

    if (maxfd >= FD_SETSIZE) {
	Punt("Ran out of fd_set slots; "
	     "recompile with a larger FD_SETSIZE.");
    }

    if (timeout < 0) {
	tvp = NULL;
    } else {
	usecs = timeout * 1000;
	tv.tv_sec = usecs / 1000000;
	tv.tv_usec = usecs % 1000000;
        tvp = &tv;
    }

    nselect = select(maxfd + 1, &rfds, &wfds, 0, tvp);

    if (nselect <= 0)
	return nselect;

    npoll = 0;
    for (i = 0; i < nfd; i++) {
	if (FD_ISSET(fd[i].fd, &rfds))
	    fd[i].revents |= POLLIN;

	if (FD_ISSET(fd[i].fd, &wfds))
	    fd[i].revents |= POLLOUT;

	if (fd[i].revents)
	    npoll++;
    }

    return npoll;
}
#endif /* USE_SELECT */
/* end job.c */

/* begin make.c */
/*	$NetBSD: make.c,v 1.56 2005/02/16 15:11:52 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: make.c,v 1.56 2005/02/16 15:11:52 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)make.c	8.1 (Berkeley) 6/6/93";
#else
__RCSID("$NetBSD: make.c,v 1.56 2005/02/16 15:11:52 christos Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * make.c --
 *	The functions which perform the examination of targets and
 *	their suitability for creation
 *
 * Interface:
 *	Make_Run 	    	Initialize things for the module and recreate
 *	    	  	    	whatever needs recreating. Returns TRUE if
 *	    	    	    	work was (or would have been) done and FALSE
 *	    	  	    	otherwise.
 *
 *	Make_Update	    	Update all parents of a given child. Performs
 *	    	  	    	various bookkeeping chores like the updating
 *	    	  	    	of the cmtime field of the parent, filling
 *	    	  	    	of the IMPSRC context variable, etc. It will
 *	    	  	    	place the parent on the toBeMade queue if it
 *	    	  	    	should be.
 *
 *	Make_TimeStamp	    	Function to set the parent's cmtime field
 *	    	  	    	based on a child's modification time.
 *
 *	Make_DoAllVar	    	Set up the various local variables for a
 *	    	  	    	target, including the .ALLSRC variable, making
 *	    	  	    	sure that any variable that needs to exist
 *	    	  	    	at the very least has the empty value.
 *
 *	Make_OODate 	    	Determine if a target is out-of-date.
 *
 *	Make_HandleUse	    	See if a child is a .USE node for a parent
 *				and perform the .USE actions if so.
 *
 *	Make_ExpandUse	    	Expand .USE nodes and return the new list of
 *				targets.
 */

/* <<make.c includes>> */

static Lst     	toBeMade;	/* The current fringe of the graph. These
				 * are nodes which await examination by
				 * MakeOODate. It is added to by
				 * Make_Update and subtracted from by
				 * MakeStartJobs */
static int  	numNodes;   	/* Number of nodes to be processed. If this
				 * is non-zero when Job_Empty() returns
				 * TRUE, there's a cycle in the graph */

static int MakeAddChild(ClientData, ClientData);
static int MakeFindChild(ClientData, ClientData);
static int MakeUnmark(ClientData, ClientData);
static int MakeAddAllSrc(ClientData, ClientData);
static int MakeTimeStamp(ClientData, ClientData);
static int MakeHandleUse(ClientData, ClientData);
static Boolean MakeStartJobs(void);
static int MakePrintStatus(ClientData, ClientData);
/*-
 *-----------------------------------------------------------------------
 * Make_TimeStamp --
 *	Set the cmtime field of a parent node based on the mtime stamp in its
 *	child. Called from MakeOODate via Lst_ForEach.
 *
 * Input:
 *	pgn		the current parent
 *	cgn		the child we've just examined
 *
 * Results:
 *	Always returns 0.
 *
 * Side Effects:
 *	The cmtime of the parent node will be changed if the mtime
 *	field of the child is greater than it.
 *-----------------------------------------------------------------------
 */
int
Make_TimeStamp(GNode *pgn, GNode *cgn)
{
    if (cgn->mtime > pgn->cmtime) {
	pgn->cmtime = cgn->mtime;
    }
    return (0);
}

/*
 * Input:
 *	pgn		the current parent
 *	cgn		the child we've just examined
 *
 */
static int
MakeTimeStamp(ClientData pgn, ClientData cgn)
{
    return Make_TimeStamp((GNode *) pgn, (GNode *) cgn);
}

/*-
 *-----------------------------------------------------------------------
 * Make_OODate --
 *	See if a given node is out of date with respect to its sources.
 *	Used by Make_Run when deciding which nodes to place on the
 *	toBeMade queue initially and by Make_Update to screen out USE and
 *	EXEC nodes. In the latter case, however, any other sort of node
 *	must be considered out-of-date since at least one of its children
 *	will have been recreated.
 *
 * Input:
 *	gn		the node to check
 *
 * Results:
 *	TRUE if the node is out of date. FALSE otherwise.
 *
 * Side Effects:
 *	The mtime field of the node and the cmtime field of its parents
 *	will/may be changed.
 *-----------------------------------------------------------------------
 */
Boolean
Make_OODate(GNode *gn)
{
	Boolean         oodate;

	/*
	 * Certain types of targets needn't even be sought as their datedness
	 * doesn't depend on their modification time...
	 */
	if ((gn->type & (OP_JOIN|OP_USE|OP_USEBEFORE|OP_EXEC)) == 0) {
		(void) Dir_MTime(gn);
		if (DEBUG(MAKE)) {
			if (gn->mtime != 0) {
				printf ("modified %s...", Targ_FmtTime(gn->mtime));
			} else {
				printf ("non-existent...");
			}
		}
	}

	/*
	 * A target is remade in one of the following circumstances:
	 *	its modification time is smaller than that of its youngest child
	 *	    and it would actually be run (has commands or type OP_NOP)
	 *	it's the object of a force operator (!)
	 *	it has no children, was on the lhs of an operator and doesn't exist
	 *	    already.
	 *
	 * Libraries are only considered out-of-date if the archive module says
	 * they are.
	 *
	 * These weird rules are brought to you by Backward-Compatibility and
	 * the strange people who wrote 'Make'.
	 */
	if (gn->type & (OP_USE|OP_USEBEFORE)) {
		/*
		 * If the node is a USE node it is *never* out of date
		 * no matter *what*.
		 */
		if (DEBUG(MAKE)) {
			printf(".USE node...");
		}
		oodate = FALSE;
	} else if (gn->type & OP_JOIN) {
		/*
		 * A target with the .JOIN attribute is only considered
		 * out-of-date if any of its children was out-of-date.
		 */
		if (DEBUG(MAKE)) {
			printf(".JOIN node...");
		}
		if (DEBUG(MAKE)) {
			printf("source %smade...", gn->flags & CHILDMADE ? "" : "not ");
		}
		oodate = (gn->flags & CHILDMADE) ? TRUE : FALSE;
	} else if (gn->type & (OP_FORCE|OP_EXEC|OP_PHONY)) {
		/*
		 * A node which is the object of the force (!) operator or which has
		 * the .EXEC attribute is always considered out-of-date.
		 */
		if (DEBUG(MAKE)) {
			if (gn->type & OP_FORCE) {
				printf("! operator...");
			} else if (gn->type & OP_PHONY) {
				printf(".PHONY node...");
			} else {
				printf(".EXEC node...");
			}
		}
		oodate = TRUE;
	} else if (gn->mtime < gn->cmtime ||
		(gn->cmtime == 0 &&
		((gn->mtime == 0 && !(gn->type & OP_OPTIONAL))
		|| gn->type & OP_DOUBLEDEP)))
	{
		/*
		 * A node whose modification time is less than that of its
		 * youngest child or that has no children (cmtime == 0) and
		 * either doesn't exist (mtime == 0) and it isn't optional
		 * or was the object of a * :: operator is out-of-date.
		 * Why? Because that's the way Make does it.
		 */
		if (DEBUG(MAKE)) {
			if (gn->mtime < gn->cmtime) {
				printf("modified before source...");
			} else if (gn->mtime == 0) {
				printf("non-existent and no sources...");
			} else {
				printf(":: operator and no sources...");
			}
		}
		if (gn->mtime) {
			GNode *sgn;
			char try[MAXPATHLEN + 1];
			snprintf(try, sizeof(try), "%s.stamp", gn->name);
			sgn = Targ_FindNode(try, TARG_NOCREATE);
			if (sgn != NILGNODE && Lst_Member(sgn->parents, (ClientData)STAMPNode) != NILLNODE) {
				oodate = Dir_MTime(sgn) < gn->cmtime;
			} else {
				oodate = TRUE;
			}
		} else {
			oodate = TRUE;
		}
	} else {
		/*
		 * When a non-existing child with no sources
		 * (such as a typically used FORCE source) has been made and
		 * the target of the child (usually a directory) has the same
		 * timestamp as the timestamp just given to the non-existing child
		 * after it was considered made.
		 */
		if (DEBUG(MAKE)) {
			if (gn->flags & FORCE)
				printf("non existing child...");
		}
		oodate = (gn->flags & FORCE) ? TRUE : FALSE;
	}

	/*
	 * If the target isn't out-of-date, the parents need to know its
	 * modification time. Note that targets that appear to be out-of-date
	 * but aren't, because they have no commands and aren't of type OP_NOP,
	 * have their mtime stay below their children's mtime to keep parents from
	 * thinking they're out-of-date.
	 */
	if (!oodate) {
		Lst_ForEach(gn->parents, MakeTimeStamp, (ClientData)gn);
	}

	return (oodate);
}

/*-
 *-----------------------------------------------------------------------
 * MakeAddChild  --
 *	Function used by Make_Run to add a child to the list l.
 *	It will only add the child if its make field is FALSE.
 *
 * Input:
 *	gnp		the node to add
 *	lp		the list to which to add it
 *
 * Results:
 *	Always returns 0
 *
 * Side Effects:
 *	The given list is extended
 *-----------------------------------------------------------------------
 */
static int
MakeAddChild(ClientData gnp, ClientData lp)
{
    GNode          *gn = (GNode *) gnp;
    Lst            l = (Lst) lp;

    if ((gn->flags & REMAKE) == 0 && !(gn->type & (OP_USE|OP_USEBEFORE))) {
	(void)Lst_EnQueue (l, (ClientData)gn);
    }
    return (0);
}

/*-
 *-----------------------------------------------------------------------
 * MakeFindChild  --
 *	Function used by Make_Run to find the pathname of a child
 *	that was already made.
 *
 * Input:
 *	gnp		the node to find
 *
 * Results:
 *	Always returns 0
 *
 * Side Effects:
 *	The path and mtime of the node and the cmtime of the parent are
 *	updated; the unmade children count of the parent is decremented.
 *-----------------------------------------------------------------------
 */
static int
MakeFindChild(ClientData gnp, ClientData pgnp)
{
    GNode          *gn = (GNode *) gnp;
    GNode          *pgn = (GNode *) pgnp;

    (void) Dir_MTime(gn);
    Make_TimeStamp(pgn, gn);
    pgn->unmade--;

    return (0);
}

/*-
 *-----------------------------------------------------------------------
 * Make_HandleUse --
 *	Function called by Make_Run and SuffApplyTransform on the downward
 *	pass to handle .USE and transformation nodes. It implements the
 *	.USE and transformation functionality by copying the node's commands,
 *	type flags and children to the parent node.
 *
 *	A .USE node is much like an explicit transformation rule, except
 *	its commands are always added to the target node, even if the
 *	target already has commands.
 *
 * Input:
 *	cgn		The .USE node
 *	pgn		The target of the .USE node
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	Children and commands may be added to the parent and the parent's
 *	type may be changed.
 *
 *-----------------------------------------------------------------------
 */
void
Make_HandleUse(GNode *cgn, GNode *pgn)
{
    LstNode	ln; 	/* An element in the children list */

#ifdef DEBUG_SRC
    if ((cgn->type & (OP_USE|OP_USEBEFORE|OP_TRANSFORM)) == 0) {
	printf("Make_HandleUse: called for plain node %s\n", cgn->name);
	return;
    }
#endif

    if ((cgn->type & (OP_USE|OP_USEBEFORE)) || Lst_IsEmpty(pgn->commands)) {
	    if (cgn->type & OP_USEBEFORE) {
		/*
		 * .USEBEFORE --
		 *	prepend the child's commands to the parent.
		 */
		Lst cmds = pgn->commands;
		pgn->commands = Lst_Duplicate(cgn->commands, NOCOPY);
		(void) Lst_Concat(pgn->commands, cmds, LST_CONCNEW);
		Lst_Destroy(cmds, NOFREE);
	    } else {
		/*
		 * .USE or target has no commands --
		 *	append the child's commands to the parent.
		 */
		(void) Lst_Concat(pgn->commands, cgn->commands, LST_CONCNEW);
	    }
    }

    if (Lst_Open(cgn->children) == SUCCESS) {
	while ((ln = Lst_Next(cgn->children)) != NILLNODE) {
	    GNode *tgn, *gn = (GNode *)Lst_Datum (ln);

	    /*
	     * Expand variables in the .USE node's name
	     * and save the unexpanded form.
	     * We don't need to do this for commands.
	     * They get expanded properly when we execute.
	     */
	    if (gn->uname == NULL) {
		gn->uname = gn->name;
	    } else {
		if (gn->name)
		    free(gn->name);
	    }
	    gn->name = Var_Subst(NULL, gn->uname, pgn, FALSE);
	    if (gn->name && gn->uname && strcmp(gn->name, gn->uname) != 0) {
		/* See if we have a target for this node. */
		tgn = Targ_FindNode(gn->name, TARG_NOCREATE);
		if (tgn != NILGNODE)
		    gn = tgn;
	    }

	    (void) Lst_AtEnd(pgn->children, gn);
	    (void) Lst_AtEnd(gn->parents, pgn);
	    pgn->unmade += 1;
	}
	Lst_Close(cgn->children);
    }

    pgn->type |= cgn->type & ~(OP_OPMASK|OP_USE|OP_USEBEFORE|OP_TRANSFORM);
}

/*-
 *-----------------------------------------------------------------------
 * MakeHandleUse --
 *	Callback function for Lst_ForEach, used by Make_Run on the downward
 *	pass to handle .USE nodes. Should be called before the children
 *	are enqueued to be looked at by MakeAddChild.
 *	This function calls Make_HandleUse to copy the .USE node's commands,
 *	type flags and children to the parent node.
 *
 * Input:
 *	cgnp		the child we've just examined
 *	pgnp		the current parent
 *
 * Results:
 *	returns 0.
 *
 * Side Effects:
 *	After expansion, .USE child nodes are removed from the parent
 *
 *-----------------------------------------------------------------------
 */
static int
MakeHandleUse(ClientData cgnp, ClientData pgnp)
{
    GNode	*cgn = (GNode *) cgnp;
    GNode	*pgn = (GNode *) pgnp;
    LstNode	ln; 	/* An element in the children list */
    int		unmarked;

    unmarked = ((cgn->type & OP_MARK) == 0);
    cgn->type |= OP_MARK;

    if ((cgn->type & (OP_USE|OP_USEBEFORE)) == 0)
	return (0);

    if (unmarked)
	Make_HandleUse(cgn, pgn);

    /*
     * This child node is now "made", so we decrement the count of
     * unmade children in the parent... We also remove the child
     * from the parent's list to accurately reflect the number of decent
     * children the parent has. This is used by Make_Run to decide
     * whether to queue the parent or examine its children...
     */
    if ((ln = Lst_Member(pgn->children, (ClientData) cgn)) != NILLNODE) {
	Lst_Remove(pgn->children, ln);
	pgn->unmade--;
    }
    return (0);
}
/*-
 *-----------------------------------------------------------------------
 * Make_Recheck --
 *	Check the modification time of a gnode, and update it as described
 *	in the comments below.
 *
 * Results:
 *	returns 0 if the gnode does not exist, or it's filesystem
 *	time if it does.
 *
 * Side Effects:
 *	the gnode's modification time and path name are affected.
 *
 *-----------------------------------------------------------------------
 */
time_t
Make_Recheck(GNode *gn)
{
    time_t mtime = Dir_MTime(gn);

#ifndef RECHECK
    /*
     * We can't re-stat the thing, but we can at least take care of rules
     * where a target depends on a source that actually creates the
     * target, but only if it has changed, e.g.
     *
     * parse.h : parse.o
     *
     * parse.o : parse.y
     *  	yacc -d parse.y
     *  	cc -c y.tab.c
     *  	mv y.tab.o parse.o
     *  	cmp -s y.tab.h parse.h || mv y.tab.h parse.h
     *
     * In this case, if the definitions produced by yacc haven't changed
     * from before, parse.h won't have been updated and gn->mtime will
     * reflect the current modification time for parse.h. This is
     * something of a kludge, I admit, but it's a useful one..
     * XXX: People like to use a rule like
     *
     * FRC:
     *
     * To force things that depend on FRC to be made, so we have to
     * check for gn->children being empty as well...
     */
    if (!Lst_IsEmpty(gn->commands) || Lst_IsEmpty(gn->children)) {
	gn->mtime = now;
    }
#else
    /*
     * This is what Make does and it's actually a good thing, as it
     * allows rules like
     *
     *	cmp -s y.tab.h parse.h || cp y.tab.h parse.h
     *
     * to function as intended. Unfortunately, thanks to the stateless
     * nature of NFS (by which I mean the loose coupling of two clients
     * using the same file from a common server), there are times
     * when the modification time of a file created on a remote
     * machine will not be modified before the local stat() implied by
     * the Dir_MTime occurs, thus leading us to believe that the file
     * is unchanged, wreaking havoc with files that depend on this one.
     *
     * I have decided it is better to make too much than to make too
     * little, so this stuff is commented out unless you're sure it's ok.
     * -- ardeb 1/12/88
     */
    /*
     * Christos, 4/9/92: If we are  saving commands pretend that
     * the target is made now. Otherwise archives with ... rules
     * don't work!
     */
    if (NoExecute(gn) || mtime == 0) {
	if (DEBUG(MAKE)) {
	    printf(" recheck(%s): update time to now: %s\n",
		   gn->name, Targ_FmtTime(gn->mtime));
	}
	gn->mtime = now;
    }
    else {
	if (DEBUG(MAKE)) {
	    printf(" recheck(%s): current update time: %s\n",
		   gn->name, Targ_FmtTime(gn->mtime));
	}
    }
#endif
    return mtime;
}

/*-
 *-----------------------------------------------------------------------
 * Make_Update  --
 *	Perform update on the parents of a node. Used by JobFinish once
 *	a node has been dealt with and by MakeStartJobs if it finds an
 *	up-to-date node.
 *
 * Input:
 *	cgn		the child node
 *
 * Results:
 *	Always returns 0
 *
 * Side Effects:
 *	The unmade field of pgn is decremented and pgn may be placed on
 *	the toBeMade queue if this field becomes 0.
 *
 * 	If the child was made, the parent's flag CHILDMADE field will be
 *	set true and its cmtime set to now.
 *
 *	If the child is not up-to-date and still does not exist,
 *	set the FORCE flag on the parents.
 *
 *	If the child wasn't made, the cmtime field of the parent will be
 *	altered if the child's mtime is big enough.
 *
 *	Finally, if the child is the implied source for the parent, the
 *	parent's IMPSRC variable is set appropriately.
 *
 *-----------------------------------------------------------------------
 */
void
Make_Update(GNode *cgn)
{
    GNode 	*pgn;	/* the parent node */
    char  	*cname;	/* the child's name */
    LstNode	ln; 	/* Element in parents and iParents lists */
    time_t	mtime = -1;
    char	*p1;
    Lst		parents;
    GNode	*centurion;

    cname = Var_Value(TARGET, cgn, &p1);
    if (p1)
	free(p1);

    /*
     * If the child was actually made, see what its modification time is
     * now -- some rules won't actually update the file. If the file still
     * doesn't exist, make its mtime now.
     */
    if (cgn->made != UPTODATE) {
	mtime = Make_Recheck(cgn);
    }

    /*
     * If this is a `::' node, we must consult its first instance
     * which is where all parents are linked.
     */
    if ((centurion = cgn->centurion) != NULL) {
	if (!Lst_IsEmpty(cgn->parents))
		Punt("%s: cohort has parents", cgn->name);
	centurion->unmade_cohorts -= 1;
	if (centurion->unmade_cohorts < 0)
	    Error("Graph cycles through centurion %s", centurion->name);
	parents = centurion->parents;
    } else {
	centurion = cgn;
	parents = cgn->parents;
    }
    if (Lst_Open(parents) == SUCCESS) {
	while ((ln = Lst_Next(parents)) != NILLNODE) {
	    pgn = (GNode *)Lst_Datum (ln);
	    if (mtime == 0)
		pgn->flags |= FORCE;
	    /*
	     * If the parent has the .MADE attribute, it has already
	     * been queued on the `toBeMade' list in Make_ExpandUse()
	     * and its unmade children counter is zero.
	     */
	    if ((pgn->flags & REMAKE) == 0 || (pgn->type & OP_MADE) != 0)
		continue;

	    if ( ! (cgn->type & (OP_EXEC|OP_USE|OP_USEBEFORE))) {
		if (cgn->made == MADE)
		    pgn->flags |= CHILDMADE;
		(void)Make_TimeStamp (pgn, cgn);
	    }

	    /*
	     * A parent must wait for the completion of all instances
	     * of a `::' dependency.
	     */
	    if (centurion->unmade_cohorts != 0 || centurion->made == UNMADE)
		continue;

	    /* One more child of this parent is now made */
	    pgn->unmade -= 1;
	    if (pgn->unmade == 0) {
		/*
		 * Queue the node up -- any unmade predecessors will
		 * be dealt with in MakeStartJobs.
		 */
		(void)Lst_EnQueue (toBeMade, (ClientData)pgn);
	    } else if (pgn->unmade < 0) {
		Error("Graph cycles through %s", pgn->name);
	    }
	}
	Lst_Close(parents);
    }
    /*
     * Deal with successor nodes. If any is marked for making and has an unmade
     * count of 0, has not been made and isn't in the examination queue,
     * it means we need to place it in the queue as it restrained itself
     * before.
     */
    for (ln = Lst_First(centurion->successors); ln != NILLNODE;
	 ln = Lst_Succ(ln)) {
	GNode	*succ = (GNode *)Lst_Datum(ln);

	if ((succ->flags & REMAKE) != 0 && succ->unmade == 0 &&
	    succ->made == UNMADE &&
	    Lst_Member(toBeMade, (ClientData)succ) == NILLNODE)
	{
	    (void)Lst_EnQueue(toBeMade, (ClientData)succ);
	}
    }

    /*
     * Set the .PREFIX and .IMPSRC variables for all the implied parents
     * of this node.
     */
    if (Lst_Open(cgn->iParents) == SUCCESS) {
	char	*cpref = Var_Value(PREFIX, cgn, &p1);

	while ((ln = Lst_Next(cgn->iParents)) != NILLNODE) {
	    pgn = (GNode *)Lst_Datum (ln);
	    if (pgn->flags & REMAKE) {
		Var_Set(IMPSRC, cname, pgn, 0);
		if (cpref != NULL)
		    Var_Set(PREFIX, cpref, pgn, 0);
	    }
	}
	if (p1)
	    free(p1);
	Lst_Close(cgn->iParents);
    }
}

/*-
 *-----------------------------------------------------------------------
 * MakeAddAllSrc --
 *	Add a child's name to the ALLSRC and OODATE variables of the given
 *	node. Called from Make_DoAllVar via Lst_ForEach. A child is added only
 *	if it has not been given the .EXEC, .USE or .INVISIBLE attributes.
 *	.EXEC and .USE children are very rarely going to be files, so...
 *	If the child is a .JOIN node, its ALLSRC is propagated to the parent.
 *
 *	A child is added to the OODATE variable if its modification time is
 *	later than that of its parent, as defined by Make, except if the
 *	parent is a .JOIN node. In that case, it is only added to the OODATE
 *	variable if it was actually made (since .JOIN nodes don't have
 *	modification times, the comparison is rather unfair...)..
 *
 * Results:
 *	Always returns 0
 *
 * Side Effects:
 *	The ALLSRC variable for the given node is extended.
 *-----------------------------------------------------------------------
 */
static int
MakeUnmark(ClientData cgnp, ClientData pgnp __unused)
{
    GNode	*cgn = (GNode *) cgnp;

    cgn->type &= ~OP_MARK;
    return (0);
}

/*
 * Input:
 *	cgnp		The child to add
 *	pgnp		The parent to whose ALLSRC variable it should
 *			be added
 *
 */
static int
MakeAddAllSrc(ClientData cgnp, ClientData pgnp)
{
    GNode	*cgn = (GNode *) cgnp;
    GNode	*pgn = (GNode *) pgnp;

    if (cgn->type & OP_MARK)
	return (0);
    cgn->type |= OP_MARK;

    if ((cgn->type & (OP_EXEC|OP_USE|OP_USEBEFORE|OP_INVISIBLE)) == 0) {
	char *child, *allsrc;
	char *p1 = NULL, *p2 = NULL;

	if (cgn->type & OP_ARCHV)
	    child = Var_Value(MEMBER, cgn, &p1);
	else
	    child = cgn->path ? cgn->path : cgn->name;
	if (cgn->type & OP_JOIN) {
	    allsrc = Var_Value(ALLSRC, cgn, &p2);
	} else {
	    allsrc = child;
	}
	if (allsrc != NULL)
		Var_Append(ALLSRC, allsrc, pgn);
	if (p2)
	    free(p2);
	if (pgn->type & OP_JOIN) {
	    if (cgn->made == MADE) {
		Var_Append(OODATE, child, pgn);
	    }
	} else if ((pgn->mtime < cgn->mtime) ||
		   (cgn->mtime >= now && cgn->made == MADE))
	{
	    /*
	     * It goes in the OODATE variable if the parent is younger than the
	     * child or if the child has been modified more recently than
	     * the start of the make. This is to keep pmake from getting
	     * confused if something else updates the parent after the
	     * make starts (shouldn't happen, I know, but sometimes it
	     * does). In such a case, if we've updated the kid, the parent
	     * is likely to have a modification time later than that of
	     * the kid and anything that relies on the OODATE variable will
	     * be hosed.
	     *
	     * XXX: This will cause all made children to go in the OODATE
	     * variable, even if they're not touched, if RECHECK isn't defined,
	     * since cgn->mtime is set to now in Make_Update. According to
	     * some people, this is good...
	     */
	    Var_Append(OODATE, child, pgn);
	}
	if (p1)
	    free(p1);
    }
    return (0);
}

/*-
 *-----------------------------------------------------------------------
 * Make_DoAllVar --
 *	Set up the ALLSRC and OODATE variables. Sad to say, it must be
 *	done separately, rather than while traversing the graph. This is
 *	because Make defined OODATE to contain all sources whose modification
 *	times were later than that of the target, *not* those sources that
 *	were out-of-date. Since in both compatibility and native modes,
 *	the modification time of the parent isn't found until the child
 *	has been dealt with, we have to wait until now to fill in the
 *	variable. As for ALLSRC, the ordering is important and not
 *	guaranteed when in native mode, so it must be set here, too.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The ALLSRC and OODATE variables of the given node is filled in.
 *	If the node is a .JOIN node, its TARGET variable will be set to
 * 	match its ALLSRC variable.
 *-----------------------------------------------------------------------
 */
void
Make_DoAllVar(GNode *gn)
{
    Lst_ForEach(gn->children, MakeUnmark, (ClientData) gn);
    Lst_ForEach(gn->children, MakeAddAllSrc, (ClientData) gn);

    if (!Var_Exists (OODATE, gn)) {
	Var_Set(OODATE, "", gn, 0);
    }
    if (!Var_Exists (ALLSRC, gn)) {
	Var_Set(ALLSRC, "", gn, 0);
    }

    if (gn->type & OP_JOIN) {
	char *p1;
	Var_Set(TARGET, Var_Value(ALLSRC, gn, &p1), gn, 0);
	if (p1)
	    free(p1);
    }
}

/*-
 *-----------------------------------------------------------------------
 * MakeStartJobs --
 *	Start as many jobs as possible.
 *
 * Results:
 *	If the query flag was given to pmake, no job will be started,
 *	but as soon as an out-of-date target is found, this function
 *	returns TRUE. At all other times, this function returns FALSE.
 *
 * Side Effects:
 *	Nodes are removed from the toBeMade queue and job table slots
 *	are filled.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
MakeStartJobs(void)
{
    GNode	*gn;

    while (!Lst_IsEmpty (toBeMade)) {
	gn = (GNode *) Lst_DeQueue(toBeMade);
	if (DEBUG(MAKE)) {
	    printf ("Examining %s...", gn->name);
	}
	/*
	 * Make sure any and all predecessors that are going to be made,
	 * have been.
	 */
	if (!Lst_IsEmpty(gn->preds)) {
	    LstNode ln;

	    for (ln = Lst_First(gn->preds); ln != NILLNODE; ln = Lst_Succ(ln)){
		GNode	*pgn = (GNode *)Lst_Datum(ln);

		if ((pgn->flags & REMAKE) &&
		    (pgn->made == UNMADE || pgn->unmade_cohorts != 0)) {
		    if (DEBUG(MAKE)) {
			printf("predecessor %s not made yet.\n", pgn->name);
		    }
		    break;
		}
	    }
	    /*
	     * If ln isn't nil, there's a predecessor as yet unmade, so we
	     * just drop this node on the floor. When the node in question
	     * has been made, it will notice this node as being ready to
	     * make but as yet unmade and will place the node on the queue.
	     */
	    if (ln != NILLNODE) {
		continue;
	    }
	}

	if (!Job_TokenWithdraw()) {
	    Lst_AtFront(toBeMade, gn);
	    break;
	}

	numNodes--;
	if (Make_OODate(gn)) {
	    if (DEBUG(MAKE)) {
		printf ("out-of-date\n");
	    }
	    if (queryFlag) {
		return (TRUE);
	    }
	    Make_DoAllVar(gn);
	    Job_Make(gn);
	} else {
	    if (DEBUG(MAKE)) {
		printf ("up-to-date\n");
	    }
	    gn->made = UPTODATE;
	    if (gn->type & OP_JOIN) {
		/*
		 * Even for an up-to-date .JOIN node, we need it to have its
		 * context variables so references to it get the correct
		 * value for .TARGET when building up the context variables
		 * of its parent(s)...
		 */
		Make_DoAllVar(gn);
	    }
	    Job_TokenReturn();
	    Make_Update(gn);
	}
    }
    return (FALSE);
}

/*-
 *-----------------------------------------------------------------------
 * MakePrintStatus --
 *	Print the status of a top-level node, viz. it being up-to-date
 *	already or not created due to an error in a lower level.
 *	Callback function for Make_Run via Lst_ForEach.
 *
 * Input:
 *	gnp		Node to examine
 *	cyclep		True if gn->unmade being non-zero implies a
 *			cycle in the graph, not an error in an
 *			inferior.
 *
 * Results:
 *	Always returns 0.
 *
 * Side Effects:
 *	A message may be printed.
 *
 *-----------------------------------------------------------------------
 */
static int
MakePrintStatus(ClientData gnp, ClientData cyclep)
{
    GNode   	*gn = (GNode *) gnp;
    Boolean 	cycle = *(Boolean *) cyclep;
    if (gn->made == UPTODATE) {
	printf ("`%s' is up to date.\n", gn->name);
    } else if (gn->unmade != 0) {
	if (cycle) {
	    Boolean t = TRUE;
	    /*
	     * If printing cycles and came to one that has unmade children,
	     * print out the cycle by recursing on its children. Note a
	     * cycle like:
	     *	a : b
	     *	b : c
	     *	c : b
	     * will cause this to erroneously complain about a being in
	     * the cycle, but this is a good approximation.
	     */
	    if (gn->made == CYCLE) {
		Error("Graph cycles through `%s'", gn->name);
		gn->made = ENDCYCLE;
		Lst_ForEach(gn->children, MakePrintStatus, (ClientData) &t);
		gn->made = UNMADE;
	    } else if (gn->made != ENDCYCLE) {
		gn->made = CYCLE;
		Lst_ForEach(gn->children, MakePrintStatus, (ClientData) &t);
	    }
	} else {
	    printf ("`%s' not remade because of errors.\n", gn->name);
	}
    }
    return (0);
}


/*-
 *-----------------------------------------------------------------------
 * Make_ExpandUse --
 *	Expand .USE nodes and create a new targets list
 *
 * Input:
 *	targs		the initial list of targets
 *
 * Results:
 *	The new list of targets.
 *
 * Side Effects:
 *	numNodes is set to the number of elements in the list of targets.
 *-----------------------------------------------------------------------
 */
Lst
Make_ExpandUse(Lst targs)
{
    GNode  *gn;		/* a temporary pointer */
    Lst    examine; 	/* List of targets to examine */
    Lst    ntargs;	/* List of new targets to be made */

    ntargs = Lst_Init(FALSE);

    examine = Lst_Duplicate(targs, NOCOPY);
    numNodes = 0;

    /*
     * Make an initial downward pass over the graph, marking nodes to be made
     * as we go down. We call Suff_FindDeps to find where a node is and
     * to get some children for it if it has none and also has no commands.
     * If the node is a leaf, we stick it on the toBeMade queue to
     * be looked at in a minute, otherwise we add its children to our queue
     * and go on about our business.
     */
    while (!Lst_IsEmpty (examine)) {
	gn = (GNode *) Lst_DeQueue(examine);

	if ((gn->type & OP_DOUBLEDEP) && !Lst_IsEmpty (gn->cohorts)) {
	    Lst new;
	    new = Lst_Duplicate(gn->cohorts, NOCOPY);
	    Lst_Concat(new, examine, LST_CONCLINK);
	    examine = new;
	}

	if ((gn->flags & REMAKE) == 0) {
	    gn->flags |= REMAKE;
	    numNodes++;

	    /*
	     * Apply any .USE rules before looking for implicit dependencies
	     * to make sure everything has commands that should...
	     * Make sure that the TARGET is set, so that we can make
	     * expansions.
	     */
	    if (gn->type & OP_ARCHV) {
		char *eoa, *eon;
		eoa = strchr(gn->name, '(');
		eon = strchr(gn->name, ')');
		if (eoa == NULL || eon == NULL)
		    continue;
		*eoa = '\0';
		*eon = '\0';
		Var_Set(MEMBER, eoa + 1, gn, 0);
		Var_Set(ARCHIVE, gn->name, gn, 0);
		*eoa = '(';
		*eon = ')';
	    }

	    (void)Dir_MTime(gn);
	    Var_Set(TARGET, gn->path ? gn->path : gn->name, gn, 0);
	    Lst_ForEach(gn->children, MakeUnmark, (ClientData)gn);
	    Lst_ForEach(gn->children, MakeHandleUse, (ClientData)gn);

	    if ((gn->type & OP_MADE) == 0)
		Suff_FindDeps(gn);
	    else {
		/* Pretend we made all this node's children */
		Lst_ForEach(gn->children, MakeFindChild, (ClientData)gn);
		if (gn->unmade != 0)
			printf("Warning: %s still has %d unmade children\n",
				gn->name, gn->unmade);
	    }

	    if (gn->unmade != 0) {
		Lst_ForEach(gn->children, MakeAddChild, (ClientData)examine);
	    } else {
		(void)Lst_EnQueue (ntargs, (ClientData)gn);
	    }
	}
    }

    Lst_Destroy(examine, NOFREE);
    return ntargs;
}

/*-
 *-----------------------------------------------------------------------
 * Make_Run --
 *	Initialize the nodes to remake and the list of nodes which are
 *	ready to be made by doing a breadth-first traversal of the graph
 *	starting from the nodes in the given list. Once this traversal
 *	is finished, all the 'leaves' of the graph are in the toBeMade
 *	queue.
 *	Using this queue and the Job module, work back up the graph,
 *	calling on MakeStartJobs to keep the job table as full as
 *	possible.
 *
 * Input:
 *	targs		the initial list of targets
 *
 * Results:
 *	TRUE if work was done. FALSE otherwise.
 *
 * Side Effects:
 *	The make field of all nodes involved in the creation of the given
 *	targets is set to 1. The toBeMade list is set to contain all the
 *	'leaves' of these subgraphs.
 *-----------------------------------------------------------------------
 */
Boolean
Make_Run(Lst targs)
{
    int	    	    errors; 	/* Number of errors the Job module reports */

    toBeMade = Make_ExpandUse(targs);

    if (queryFlag) {
	/*
	 * We wouldn't do any work unless we could start some jobs in the
	 * next loop... (we won't actually start any, of course, this is just
	 * to see if any of the targets was out of date)
	 */
	return (MakeStartJobs());
    } else {
	/*
	 * Initialization. At the moment, no jobs are running and until some
	 * get started, nothing will happen since the remaining upward
	 * traversal of the graph is performed by the routines in job.c upon
	 * the finishing of a job. So we fill the Job table as much as we can
	 * before going into our loop.
	 */
	(void) MakeStartJobs();
    }

    /*
     * Main Loop: The idea here is that the ending of jobs will take
     * care of the maintenance of data structures and the waiting for output
     * will cause us to be idle most of the time while our children run as
     * much as possible. Because the job table is kept as full as possible,
     * the only time when it will be empty is when all the jobs which need
     * running have been run, so that is the end condition of this loop.
     * Note that the Job module will exit if there were any errors unless the
     * keepgoing flag was given.
     */
    while (!Lst_IsEmpty(toBeMade) || !Job_Empty ()) {
	Job_CatchOutput();
	Job_CatchChildren(!usePipes);
	(void)MakeStartJobs();
    }

    errors = Job_Finish();

    /*
     * Print the final status of each target. E.g. if it wasn't made
     * because some inferior reported an error.
     */
    errors = ((errors == 0) && (numNodes != 0));
    Lst_ForEach(targs, MakePrintStatus, (ClientData) &errors);

    return (TRUE);
}
/* end make.c */

/* begin parse.c */
/*	$NetBSD: parse.c,v 1.102 2005/06/18 14:32:04 rpaulo Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: parse.c,v 1.102 2005/06/18 14:32:04 rpaulo Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)parse.c	8.3 (Berkeley) 3/19/94";
#else
__RCSID("$NetBSD: parse.c,v 1.102 2005/06/18 14:32:04 rpaulo Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * parse.c --
 *	Functions to parse a makefile.
 *
 *	One function, Parse_Init, must be called before any functions
 *	in this module are used. After that, the function Parse_File is the
 *	main entry point and controls most of the other functions in this
 *	module.
 *
 *	Most important structures are kept in Lsts. Directories for
 *	the #include "..." function are kept in the 'parseIncPath' Lst, while
 *	those for the #include <...> are kept in the 'sysIncPath' Lst. The
 *	targets currently being defined are kept in the 'targets' Lst.
 *
 *	The variables 'fname' and 'lineno' are used to track the name
 *	of the current file and the line number in that file so that error
 *	messages can be more meaningful.
 *
 * Interface:
 *	Parse_Init	    	    Initialization function which must be
 *	    	  	    	    called before anything else in this module
 *	    	  	    	    is used.
 *
 *	Parse_End		    Cleanup the module
 *
 *	Parse_File	    	    Function used to parse a makefile. It must
 *	    	  	    	    be given the name of the file, which should
 *	    	  	    	    already have been opened, and a function
 *	    	  	    	    to call to read a character from the file.
 *
 *	Parse_IsVar	    	    Returns TRUE if the given line is a
 *	    	  	    	    variable assignment. Used by MainParseArgs
 *	    	  	    	    to determine if an argument is a target
 *	    	  	    	    or a variable assignment. Used internally
 *	    	  	    	    for pretty much the same thing...
 *
 *	Parse_Error	    	    Function called when an error occurs in
 *	    	  	    	    parsing. Used by the variable and
 *	    	  	    	    conditional modules.
 *	Parse_MainName	    	    Returns a Lst of the main target to create.
 */

/* <<parse.c includes>> */

/*
 * These values are returned by ParseEOF to tell Parse_File whether to
 * CONTINUE parsing, i.e. it had only reached the end of an include file,
 * or if it's DONE.
 */
#define	CONTINUE	1
#define	DONE		0
static Lst     	    targets;	/* targets we're working on */
#ifdef CLEANUP
static Lst     	    targCmds;	/* command lines for targets */
#endif
static Boolean	    inLine;	/* true if currently in a dependency
				 * line or its commands */
typedef struct {
    char *str;
    char *ptr;
} PTR;

static int	    fatals = 0;

static GNode	    *mainNode;	/* The main target to create. This is the
				 * first target on the first dependency
				 * line in the first makefile */
typedef struct IFile {
    char           *fname;	    /* name of previous file */
    int             lineno;	    /* saved line number */
    FILE *          F;		    /* the open stream */
    PTR *	    P;	    	    /* the char pointer */
} IFile;

static IFile	    curFile;


/*
 * Definitions for handling #include specifications
 */

static Lst      includes;  	/* stack of IFiles generated by
				 * #includes */
Lst         	parseIncPath;	/* list of directories for "..." includes */
Lst         	sysIncPath;	/* list of directories for <...> includes */
Lst         	defIncPath;	/* default directories for <...> includes */

/*-
 * specType contains the SPECial TYPE of the current target. It is
 * Not if the target is unspecial. If it *is* special, however, the children
 * are linked as children of the parent but not vice versa. This variable is
 * set in ParseDoDependency
 */
typedef enum {
    Begin,  	    /* .BEGIN */
    Default,	    /* .DEFAULT */
    End,    	    /* .END */
    Ignore,	    /* .IGNORE */
    Includes,	    /* .INCLUDES */
    Interrupt,	    /* .INTERRUPT */
    Libs,	    /* .LIBS */
    MFlags,	    /* .MFLAGS or .MAKEFLAGS */
    Main,	    /* .MAIN and we don't have anything user-specified to
		     * make */
    NoExport,	    /* .NOEXPORT */
    NoPath,	    /* .NOPATH */
    Not,	    /* Not special */
    NotParallel,    /* .NOTPARALLEL */
    Null,   	    /* .NULL */
    ExObjdir,	    /* .OBJDIR */
    Order,  	    /* .ORDER */
    Parallel,	    /* .PARALLEL */
    ExPath,	    /* .PATH */
    Phony,	    /* .PHONY */
#ifdef POSIX
    Posix,	    /* .POSIX */
#endif
    Precious,	    /* .PRECIOUS */
    ExShell,	    /* .SHELL */
    Silent,	    /* .SILENT */
    SingleShell,    /* .SINGLESHELL */
    Suffixes,	    /* .SUFFIXES */
    Wait,	    /* .WAIT */
    Attribute	    /* Generic attribute */
} ParseSpecial;

static ParseSpecial specType;
static int waiting;

#define	LPAREN	'('
#define	RPAREN	')'
/*
 * Predecessor node for handling .ORDER. Initialized to NILGNODE when .ORDER
 * seen, then set to each successive source on the line.
 */
static GNode	*predecessor;

/*
 * The parseKeywords table is searched using binary search when deciding
 * if a target or source is special. The 'spec' field is the ParseSpecial
 * type of the keyword ("Not" if the keyword isn't special as a target) while
 * the 'op' field is the operator to apply to the list of targets if the
 * keyword is used as a source ("0" if the keyword isn't special as a source)
 */
static struct {
    const char   *name;    	/* Name of keyword */
    ParseSpecial  spec;	    	/* Type when used as a target */
    int	    	  op;	    	/* Operator when used as a source */
} parseKeywords[] = {
{ ".BEGIN", 	  Begin,    	0 },
{ ".DEFAULT",	  Default,  	0 },
{ ".END",   	  End,	    	0 },
{ ".EXEC",	  Attribute,   	OP_EXEC },
{ ".IGNORE",	  Ignore,   	OP_IGNORE },
{ ".INCLUDES",	  Includes, 	0 },
{ ".INTERRUPT",	  Interrupt,	0 },
{ ".INVISIBLE",	  Attribute,   	OP_INVISIBLE },
{ ".JOIN",  	  Attribute,   	OP_JOIN },
{ ".LIBS",  	  Libs,	    	0 },
{ ".MADE",	  Attribute,	OP_MADE },
{ ".MAIN",	  Main,		0 },
{ ".MAKE",  	  Attribute,   	OP_MAKE },
{ ".MAKEFLAGS",	  MFlags,   	0 },
{ ".MFLAGS",	  MFlags,   	0 },
{ ".NOPATH",	  NoPath,	OP_NOPATH },
{ ".NOTMAIN",	  Attribute,   	OP_NOTMAIN },
{ ".NOTPARALLEL", NotParallel,	0 },
{ ".NO_PARALLEL", NotParallel,	0 },
{ ".NULL",  	  Null,	    	0 },
{ ".OBJDIR",	  ExObjdir,	0 },
{ ".OPTIONAL",	  Attribute,   	OP_OPTIONAL },
{ ".ORDER", 	  Order,    	0 },
{ ".PARALLEL",	  Parallel,	0 },
{ ".PATH",	  ExPath,	0 },
{ ".PHONY",	  Phony,	OP_PHONY },
#ifdef POSIX
{ ".POSIX",	  Posix,	0 },
#endif
{ ".PRECIOUS",	  Precious, 	OP_PRECIOUS },
{ ".RECURSIVE",	  Attribute,	OP_MAKE },
{ ".SHELL", 	  ExShell,    	0 },
{ ".SILENT",	  Silent,   	OP_SILENT },
{ ".SINGLESHELL", SingleShell,	0 },
{ ".SUFFIXES",	  Suffixes, 	0 },
{ ".USE",   	  Attribute,   	OP_USE },
{ ".USEBEFORE",   Attribute,   	OP_USEBEFORE },
{ ".WAIT",	  Wait, 	0 },
};

/*
 * Used by ParseDoSpecialSrc()
 */
typedef struct {
    int		op;
    char	*src;
    Lst		allsrc;
} SpecialSrc;

static int ParseIsEscaped(const char *, const char *);
static void ParseErrorInternal(char *, size_t, int, const char *, ...)
     __attribute__((__format__(__printf__, 4, 5)));
static void ParseVErrorInternal(char *, size_t, int, const char *, va_list)
     __attribute__((__format__(__printf__, 4, 0)));
static int ParseFindKeyword(char *);
static int ParseLinkSrc(ClientData, ClientData);
static int ParseDoOp(ClientData, ClientData);
static int ParseAddDep(ClientData, ClientData);
static int ParseDoSpecialSrc(ClientData, ClientData);
static void ParseDoSrc(int, char *, Lst, Boolean);
static int ParseFindMain(ClientData, ClientData);
static int ParseAddDir(ClientData, ClientData);
static int ParseClearPath(ClientData, ClientData);
static void ParseDoDependency(char *);
static int ParseAddCmd(ClientData, ClientData);
static __inline int ParseReadc(void);
static void ParseUnreadc(int);
static void ParseHasCommands(ClientData);
static void ParseDoInclude(char *);
static void ParseSetParseFile(char *);
#ifdef SYSVINCLUDE
static void ParseTraditionalInclude(char *);
#endif
static int ParseEOF(int);
static char *ParseReadLine(void);
static char *ParseSkipLine(int, int);
static void ParseFinishLine(void);
static void ParseMark(GNode *);

extern int  maxJobs;


/*-
 *----------------------------------------------------------------------
 * ParseIsEscaped --
 *	Check if the current character is escaped on the current line
 *
 * Results:
 *	0 if the character is not backslash escaped, 1 otherwise
 *
 * Side Effects:
 *	None
 *----------------------------------------------------------------------
 */
static int
ParseIsEscaped(const char *line, const char *c)
{
    int active = 0;
    for (;;) {
	if (line == c)
	    return active;
	if (*--c != '\\')
	    return active;
	active = !active;
    }
}

/*-
 *----------------------------------------------------------------------
 * ParseFindKeyword --
 *	Look in the table of keywords for one matching the given string.
 *
 * Input:
 *	str		String to find
 *
 * Results:
 *	The index of the keyword, or -1 if it isn't there.
 *
 * Side Effects:
 *	None
 *----------------------------------------------------------------------
 */
static int
ParseFindKeyword(char *str)
{
    int    start, end, cur;
    int    diff;

    start = 0;
    end = (sizeof(parseKeywords)/sizeof(parseKeywords[0])) - 1;

    do {
	cur = start + ((end - start) / 2);
	diff = strcmp (str, parseKeywords[cur].name);

	if (diff == 0) {
	    return (cur);
	} else if (diff < 0) {
	    end = cur - 1;
	} else {
	    start = cur + 1;
	}
    } while (start <= end);
    return (-1);
}

/*-
 * ParseVErrorInternal  --
 *	Error message abort function for parsing. Prints out the context
 *	of the error (line number and file) as well as the message with
 *	two optional arguments.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	"fatals" is incremented if the level is PARSE_FATAL.
 */
/* VARARGS */
static void
ParseVErrorInternal(char *cfname, size_t clineno, int type, const char *fmt,
    va_list ap)
{
	static Boolean fatal_warning_error_printed = FALSE;

	(void)fprintf(stderr, "%s: \"", progname);

	if (*cfname != '/') {
		char *cp;
		const char *dir;

		/*
		 * Nothing is more anoying than not knowing which Makefile
		 * is the culprit.
		 */
		dir = Var_Value(".PARSEDIR", VAR_GLOBAL, &cp);
		if (dir == NULL || *dir == '\0' ||
		    (*dir == '.' && dir[1] == '\0'))
			dir = Var_Value(".CURDIR", VAR_GLOBAL, &cp);
		if (dir == NULL)
			dir = ".";

		(void)fprintf(stderr, "%s/%s", dir, cfname);
	} else
		(void)fprintf(stderr, "%s", cfname);

	(void)fprintf(stderr, "\" line %d: ", (int)clineno);
	if (type == PARSE_WARNING)
		(void)fprintf(stderr, "warning: ");
	(void)vfprintf(stderr, fmt, ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);
	if (type == PARSE_FATAL || parseWarnFatal)
		fatals += 1;
	if (parseWarnFatal && !fatal_warning_error_printed) {
		Error("parsing warnings being treated as errors");
		fatal_warning_error_printed = TRUE;
	}
}

/*-
 * ParseErrorInternal  --
 *	Error function
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	None
 */
/* VARARGS */
static void
ParseErrorInternal(char *cfname, size_t clineno, int type, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	ParseVErrorInternal(cfname, clineno, type, fmt, ap);
	va_end(ap);
}

/*-
 * Parse_Error  --
 *	External interface to ParseErrorInternal; uses the default filename
 *	Line number.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	None
 */
/* VARARGS */
void
Parse_Error(int type, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	ParseVErrorInternal(curFile.fname, curFile.lineno, type, fmt, ap);
	va_end(ap);
}

/*-
 *---------------------------------------------------------------------
 * ParseLinkSrc  --
 *	Link the parent node to its new child. Used in a Lst_ForEach by
 *	ParseDoDependency. If the specType isn't 'Not', the parent
 *	isn't linked as a parent of the child.
 *
 * Input:
 *	pgnp		The parent node
 *	cgpn		The child node
 *
 * Results:
 *	Always = 0
 *
 * Side Effects:
 *	New elements are added to the parents list of cgn and the
 *	children list of cgn. the unmade field of pgn is updated
 *	to reflect the additional child.
 *---------------------------------------------------------------------
 */
static int
ParseLinkSrc(ClientData pgnp, ClientData cgnp)
{
    GNode          *pgn = (GNode *) pgnp;
    GNode          *cgn = (GNode *) cgnp;

    if ((pgn->type & OP_DOUBLEDEP) && !Lst_IsEmpty (pgn->cohorts))
	pgn = (GNode *) Lst_Datum(Lst_Last(pgn->cohorts));
    (void)Lst_AtEnd (pgn->children, (ClientData)cgn);
    if (specType == Not)
	    (void)Lst_AtEnd (cgn->parents, (ClientData)pgn);
    pgn->unmade += 1;
    return (0);
}

/*-
 *---------------------------------------------------------------------
 * ParseDoOp  --
 *	Apply the parsed operator to the given target node. Used in a
 *	Lst_ForEach call by ParseDoDependency once all targets have
 *	been found and their operator parsed. If the previous and new
 *	operators are incompatible, a major error is taken.
 *
 * Input:
 *	gnp		The node to which the operator is to be applied
 *	opp		The operator to apply
 *
 * Results:
 *	Always 0
 *
 * Side Effects:
 *	The type field of the node is altered to reflect any new bits in
 *	the op.
 *---------------------------------------------------------------------
 */
static int
ParseDoOp(ClientData gnp, ClientData opp)
{
    GNode          *gn = (GNode *) gnp;
    int             op = *(int *) opp;
    /*
     * If the dependency mask of the operator and the node don't match and
     * the node has actually had an operator applied to it before, and
     * the operator actually has some dependency information in it, complain.
     */
    if (((op & OP_OPMASK) != (gn->type & OP_OPMASK)) &&
	!OP_NOP(gn->type) && !OP_NOP(op))
    {
	Parse_Error(PARSE_FATAL, "Inconsistent operator for %s", gn->name);
	return (1);
    }

    if ((op == OP_DOUBLEDEP) && ((gn->type & OP_OPMASK) == OP_DOUBLEDEP)) {
	/*
	 * If the node was the object of a :: operator, we need to create a
	 * new instance of it for the children and commands on this dependency
	 * line. The new instance is placed on the 'cohorts' list of the
	 * initial one (note the initial one is not on its own cohorts list)
	 * and the new instance is linked to all parents of the initial
	 * instance.
	 */
	GNode	*cohort;

	/*
	 * Propagate copied bits to the initial node.  They'll be propagated
	 * back to the rest of the cohorts later.
	 */
	gn->type |= op & ~OP_OPMASK;

	cohort = Targ_NewGN(gn->name);
	/*
	 * Make the cohort invisible as well to avoid duplicating it into
	 * other variables. True, parents of this target won't tend to do
	 * anything with their local variables, but better safe than
	 * sorry. (I think this is pointless now, since the relevant list
	 * traversals will no longer see this node anyway. -mycroft)
	 */
	cohort->type = op | OP_INVISIBLE;
	(void)Lst_AtEnd(gn->cohorts, (ClientData)cohort);
	cohort->centurion = gn;
	gn->unmade_cohorts += 1;
    } else {
	/*
	 * We don't want to nuke any previous flags (whatever they were) so we
	 * just OR the new operator into the old
	 */
	gn->type |= op;
    }

    return (0);
}

/*-
 *---------------------------------------------------------------------
 * ParseAddDep  --
 *	Check if the pair of GNodes given needs to be synchronized.
 *	This has to be when two nodes are on different sides of a
 *	.WAIT directive.
 *
 * Results:
 *	Returns 1 if the two targets need to be ordered, 0 otherwise.
 *	If it returns 1, the search can stop
 *
 * Side Effects:
 *	A dependency can be added between the two nodes.
 *
 *---------------------------------------------------------------------
 */
static int
ParseAddDep(ClientData pp, ClientData sp)
{
    GNode *p = (GNode *) pp;
    GNode *s = (GNode *) sp;

    if (p->order < s->order) {
	/*
	 * XXX: This can cause loops, and loops can cause unmade targets,
	 * but checking is tedious, and the debugging output can show the
	 * problem
	 */
	(void)Lst_AtEnd(p->successors, (ClientData)s);
	(void)Lst_AtEnd(s->preds, (ClientData)p);
	return 0;
    }
    else
	return 1;
}

/* -
 *---------------------------------------------------------------------
 * ParseDoSpecialSrc  --
 *	ParseDoSrc struck an unexpanded variable in a src.
 *	The most likely reason is a src that refers to .TARGET or
 *	.PREFIX so we get called to set those for each target
 *	and then call ParseDoSrc again to do the real work.
 *
 * Input:
 *	tp		A target GNode *
 *	sp		A SpecialSrc * which contains the args we need
 *			for ParseDoSrc.
 *
 * Results:
 *	Goodness
 *
 * Side Effects:
 *	The target GNode will have .TARGET and .PREFIX set, this seems
 *	harmless.
 */
static int
ParseDoSpecialSrc(ClientData tp, ClientData sp)
{
    GNode *tn = (GNode *) tp;
    GNode *gn;
    SpecialSrc *ss = (SpecialSrc *) sp;
    char *cp;
    char *cp2;
    char *pref;

    /*
     * If the target is a suffix rule, leave it alone.
     */
    if (Suff_IsTransform(tn->name)) {
	ParseDoSrc(ss->op, ss->src, ss->allsrc, FALSE); /* don't come back */
	return 0;
    }
    Var_Set(TARGET, tn->name, tn, 0);
    if ((pref = strrchr(tn->name, '/')))
	pref++;
    else
	pref = tn->name;
    if ((cp2 = strchr(pref, '.')) > pref) {
	cp = estrdup(pref);
	cp[cp2 - pref] = '\0';
	Var_Set(PREFIX, cp, tn, 0);
	free(cp);
    } else
	Var_Set(PREFIX, pref, tn, 0);
    cp = Var_Subst(NULL, ss->src, tn, FALSE);
    if (strchr(cp, '$')) {
	Parse_Error(PARSE_WARNING, "Cannot resolve '%s' here", ss->src);
	ParseDoSrc(ss->op, ss->src, ss->allsrc, FALSE); /* don't come back */
	return 1;			/* stop list traversal */
    }
    /*
     * We don't want to make every target dependent on sources for
     * other targets.  This is the bit of ParseDoSrc which is relevant.
     * The main difference is we don't link the resolved src to all targets.
     */
    gn = Targ_FindNode(cp, TARG_CREATE);
    if (ss->op) {
	gn->type |= ss->op;
    } else {
	ParseLinkSrc((ClientData)tn, (ClientData)gn);
    }
    gn->order = waiting;
    (void)Lst_AtEnd(ss->allsrc, (ClientData)gn);
    if (waiting) {
	Lst_ForEach(ss->allsrc, ParseAddDep, (ClientData)gn);
    }
    return 0;
}


/*-
 *---------------------------------------------------------------------
 * ParseDoSrc  --
 *	Given the name of a source, figure out if it is an attribute
 *	and apply it to the targets if it is. Else decide if there is
 *	some attribute which should be applied *to* the source because
 *	of some special target and apply it if so. Otherwise, make the
 *	source be a child of the targets in the list 'targets'
 *
 * Input:
 *	tOp		operator (if any) from special targets
 *	src		name of the source to handle
 *	allsrc		List of all sources to wait for
 *	resolve		boolean - should we try and resolve .TARGET refs.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Operator bits may be added to the list of targets or to the source.
 *	The targets may have a new source added to their lists of children.
 *---------------------------------------------------------------------
 */
static void
ParseDoSrc(int tOp, char *src, Lst allsrc, Boolean resolve)
{
    GNode	*gn = NULL;

    if (*src == '.' && isupper ((unsigned char)src[1])) {
	int keywd = ParseFindKeyword(src);
	if (keywd != -1) {
	    int op = parseKeywords[keywd].op;
	    if (op != 0) {
		Lst_ForEach(targets, ParseDoOp, (ClientData)&op);
		return;
	    }
	    if (parseKeywords[keywd].spec == Wait) {
		waiting++;
		return;
	    }
	}
    }

    switch (specType) {
    case Main:
	/*
	 * If we have noted the existence of a .MAIN, it means we need
	 * to add the sources of said target to the list of things
	 * to create. The string 'src' is likely to be free, so we
	 * must make a new copy of it. Note that this will only be
	 * invoked if the user didn't specify a target on the command
	 * line. This is to allow #ifmake's to succeed, or something...
	 */
	(void) Lst_AtEnd(create, (ClientData)estrdup(src));
	/*
	 * Add the name to the .TARGETS variable as well, so the user cna
	 * employ that, if desired.
	 */
	Var_Append(".TARGETS", src, VAR_GLOBAL);
	return;

    case Order:
	/*
	 * Create proper predecessor/successor links between the previous
	 * source and the current one.
	 */
	gn = Targ_FindNode(src, TARG_CREATE);
	if (predecessor != NILGNODE) {
	    (void)Lst_AtEnd(predecessor->successors, (ClientData)gn);
	    (void)Lst_AtEnd(gn->preds, (ClientData)predecessor);
	}
	/*
	 * The current source now becomes the predecessor for the next one.
	 */
	predecessor = gn;
	break;

    default:
	/*
	 * If the source is not an attribute, we need to find/create
	 * a node for it. After that we can apply any operator to it
	 * from a special target or link it to its parents, as
	 * appropriate.
	 *
	 * In the case of a source that was the object of a :: operator,
	 * the attribute is applied to all of its instances (as kept in
	 * the 'cohorts' list of the node) or all the cohorts are linked
	 * to all the targets.
	 */
	if (resolve && strchr(src, '$')) {
	    SpecialSrc ss;

	    ss.op = tOp;
	    ss.src = src;
	    ss.allsrc = allsrc;

	    /*
	     * If src cannot be fully resolved, we'll be called again
	     * with resolve==FALSE.
	     */
	    Lst_ForEach(targets, ParseDoSpecialSrc, (ClientData)&ss);
	    return;
	}
	gn = Targ_FindNode(src, TARG_CREATE);
	if (tOp) {
	    gn->type |= tOp;
	} else {
	    Lst_ForEach(targets, ParseLinkSrc, (ClientData)gn);
	}
	break;
    }

    gn->order = waiting;
    (void)Lst_AtEnd(allsrc, (ClientData)gn);
    if (waiting) {
	Lst_ForEach(allsrc, ParseAddDep, (ClientData)gn);
    }
}

/*-
 *-----------------------------------------------------------------------
 * ParseFindMain --
 *	Find a real target in the list and set it to be the main one.
 *	Called by ParseDoDependency when a main target hasn't been found
 *	yet.
 *
 * Input:
 *	gnp		Node to examine
 *
 * Results:
 *	0 if main not found yet, 1 if it is.
 *
 * Side Effects:
 *	mainNode is changed and Targ_SetMain is called.
 *
 *-----------------------------------------------------------------------
 */
static int
ParseFindMain(ClientData gnp, ClientData dummy)
{
    GNode   	  *gn = (GNode *) gnp;
    if ((gn->type & OP_NOTARGET) == 0) {
	mainNode = gn;
	Targ_SetMain(gn);
	return (dummy ? 1 : 1);
    } else {
	return (dummy ? 0 : 0);
    }
}

/*-
 *-----------------------------------------------------------------------
 * ParseAddDir --
 *	Front-end for Dir_AddDir to make sure Lst_ForEach keeps going
 *
 * Results:
 *	=== 0
 *
 * Side Effects:
 *	See Dir_AddDir.
 *
 *-----------------------------------------------------------------------
 */
static int
ParseAddDir(ClientData path, ClientData name)
{
    (void) Dir_AddDir((Lst) path, (char *) name);
    return(0);
}

/*-
 *-----------------------------------------------------------------------
 * ParseClearPath --
 *	Front-end for Dir_ClearPath to make sure Lst_ForEach keeps going
 *
 * Results:
 *	=== 0
 *
 * Side Effects:
 *	See Dir_ClearPath
 *
 *-----------------------------------------------------------------------
 */
static int
ParseClearPath(ClientData path, ClientData dummy)
{
    Dir_ClearPath((Lst) path);
    return(dummy ? 0 : 0);
}

/*-
 *---------------------------------------------------------------------
 * ParseDoDependency  --
 *	Parse the dependency line in line.
 *
 * Input:
 *	line		the line to parse
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The nodes of the sources are linked as children to the nodes of the
 *	targets. Some nodes may be created.
 *
 *	We parse a dependency line by first extracting words from the line and
 * finding nodes in the list of all targets with that name. This is done
 * until a character is encountered which is an operator character. Currently
 * these are only ! and :. At this point the operator is parsed and the
 * pointer into the line advanced until the first source is encountered.
 * 	The parsed operator is applied to each node in the 'targets' list,
 * which is where the nodes found for the targets are kept, by means of
 * the ParseDoOp function.
 *	The sources are read in much the same way as the targets were except
 * that now they are expanded using the wildcarding scheme of the C-Shell
 * and all instances of the resulting words in the list of all targets
 * are found. Each of the resulting nodes is then linked to each of the
 * targets as one of its children.
 *	Certain targets are handled specially. These are the ones detailed
 * by the specType variable.
 *	The storing of transformation rules is also taken care of here.
 * A target is recognized as a transformation rule by calling
 * Suff_IsTransform. If it is a transformation rule, its node is gotten
 * from the suffix module via Suff_AddTransform rather than the standard
 * Targ_FindNode in the target module.
 *---------------------------------------------------------------------
 */
static void
ParseDoDependency(char *line)
{
    char  	   *cp;		/* our current position */
    GNode 	   *gn = NULL;	/* a general purpose temporary node */
    int             op;		/* the operator on the line */
    char            savec;	/* a place to save a character */
    Lst    	    paths;   	/* List of search paths to alter when parsing
				 * a list of .PATH targets */
    int	    	    tOp;    	/* operator from special target */
    /*Lst	    	    sources;*/	/* list of archive source names after
				 * expansion */
    Lst 	    curTargs;	/* list of target names to be found and added
				 * to the targets list */
    Lst		    curSrcs;	/* list of sources in order */
    char	   *lstart = line;
    Boolean	    hasWait;	/* is .WAIT present in srcs */

    tOp = 0;

    specType = Not;
    waiting = 0;
    paths = (Lst)NULL;

    curTargs = Lst_Init(FALSE);
    curSrcs = Lst_Init(FALSE);

    do {
	for (cp = line;
	     *cp && (ParseIsEscaped(lstart, cp) ||
	     (!isspace ((unsigned char)*cp) &&
	     (*cp != '!') && (*cp != ':') && (*cp != LPAREN)));
	     cp++)
	{
	    if (*cp == '$') {
		/*
		 * Must be a dynamic source (would have been expanded
		 * otherwise), so call the Var module to parse the puppy
		 * so we can safely advance beyond it...There should be
		 * no errors in this, as they would have been discovered
		 * in the initial Var_Subst and we wouldn't be here.
		 */
		int 	length;
		Boolean	freeIt;
		char	*result;

		result=Var_Parse(cp, VAR_CMD, TRUE, &length, &freeIt);

		if (freeIt) {
		    free(result);
		}
		cp += length-1;
	    }
	    continue;
	}
	if (!ParseIsEscaped(lstart, cp) && *cp == LPAREN) {
	    /*
	     * Archives must be handled specially to make sure the OP_ARCHV
	     * flag is set in their 'type' field, for one thing, and because
	     * things like "archive(file1.o file2.o file3.o)" are permissible.
	     * Arch_ParseArchive will set 'line' to be the first non-blank
	     * after the archive-spec. It creates/finds nodes for the members
	     * and places them on the given list, returning SUCCESS if all
	     * went well and FAILURE if there was an error in the
	     * specification. On error, line should remain untouched.
	     */
	    /*if (Arch_ParseArchive(&line, targets, VAR_CMD) != SUCCESS) {
		Parse_Error(PARSE_FATAL,
			     "Error in archive specification: \"%s\"", line);
		return;
	    } else {
		continue;
	    }*/
	    fprintf(stderr, "OP_ARCHV is deprecated\n");
	    exit(1);
	}
	savec = *cp;

	if (!*cp) {
	    /*
	     * Ending a dependency line without an operator is a Bozo
	     * no-no.  As a heuristic, this is also often triggered by
	     * undetected conflicts from cvs/rcs merges.
	     */
	    if ((strncmp(line, "<<<<<<", 6) == 0) ||
		(strncmp(line, "======", 6) == 0) ||
		(strncmp(line, ">>>>>>", 6) == 0))
		Parse_Error(PARSE_FATAL,
		    "Makefile appears to contain unresolved cvs/rcs/??? merge conflicts");
	    else
		Parse_Error(PARSE_FATAL, "Need an operator");
	    return;
	}
	*cp = '\0';
	/*
	 * Have a word in line. See if it's a special target and set
	 * specType to match it.
	 */
	if (*line == '.' && isupper ((unsigned char)line[1])) {
	    /*
	     * See if the target is a special target that must have it
	     * or its sources handled specially.
	     */
	    int keywd = ParseFindKeyword(line);
	    if (keywd != -1) {
		if (specType == ExPath && parseKeywords[keywd].spec != ExPath) {
		    Parse_Error(PARSE_FATAL, "Mismatched special targets");
		    return;
		}

		specType = parseKeywords[keywd].spec;
		tOp = parseKeywords[keywd].op;

		/*
		 * Certain special targets have special semantics:
		 *	.PATH		Have to set the dirSearchPath
		 *			variable too
		 *	.MAIN		Its sources are only used if
		 *			nothing has been specified to
		 *			create.
		 *	.DEFAULT    	Need to create a node to hang
		 *			commands on, but we don't want
		 *			it in the graph, nor do we want
		 *			it to be the Main Target, so we
		 *			create it, set OP_NOTMAIN and
		 *			add it to the list, setting
		 *			DEFAULT to the new node for
		 *			later use. We claim the node is
		 *	    	    	A transformation rule to make
		 *	    	    	life easier later, when we'll
		 *	    	    	use Make_HandleUse to actually
		 *	    	    	apply the .DEFAULT commands.
		 *	.PHONY		The list of targets
		 *	.NOPATH		Don't search for file in the path
		 *	.BEGIN
		 *	.END
		 *	.INTERRUPT  	Are not to be considered the
		 *			main target.
		 *  	.NOTPARALLEL	Make only one target at a time.
		 *  	.SINGLESHELL	Create a shell for each command.
		 *  	.ORDER	    	Must set initial predecessor to NIL
		 */
		switch (specType) {
		    case ExPath:
			if (paths == NULL) {
			    paths = Lst_Init(FALSE);
			}
			(void)Lst_AtEnd(paths, (ClientData)dirSearchPath);
			break;
		    case Main:
			if (!Lst_IsEmpty(create)) {
			    specType = Not;
			}
			break;
		    case Begin:
		    case End:
		    case Interrupt:
			gn = Targ_FindNode(line, TARG_CREATE);
			gn->type |= OP_NOTMAIN|OP_SPECIAL;
			(void)Lst_AtEnd(targets, (ClientData)gn);
			break;
		    case Default:
			gn = Targ_NewGN(".DEFAULT");
			gn->type |= (OP_NOTMAIN|OP_TRANSFORM);
			(void)Lst_AtEnd(targets, (ClientData)gn);
			DEFAULT = gn;
			break;
		    case NotParallel:
		    {
			maxJobs = 1;
			break;
		    }
		    case SingleShell:
			compatMake = TRUE;
			break;
		    case Order:
			predecessor = NILGNODE;
			break;
		    default:
			break;
		}
	    } else if (strncmp (line, ".PATH", 5) == 0) {
		/*
		 * .PATH<suffix> has to be handled specially.
		 * Call on the suffix module to give us a path to
		 * modify.
		 */
		Lst 	path;

		specType = ExPath;
		path = Suff_GetPath(&line[5]);
		if (path == NILLST) {
		    Parse_Error(PARSE_FATAL,
				 "Suffix '%s' not defined (yet)",
				 &line[5]);
		    return;
		} else {
		    if (paths == (Lst)NULL) {
			paths = Lst_Init(FALSE);
		    }
		    (void)Lst_AtEnd(paths, (ClientData)path);
		}
	    }
	}

	/*
	 * Have word in line. Get or create its node and stick it at
	 * the end of the targets list
	 */
	if ((specType == Not) && (*line != '\0')) {
	    if (Dir_HasWildcards(line)) {
		/*
		 * Targets are to be sought only in the current directory,
		 * so create an empty path for the thing. Note we need to
		 * use Dir_Destroy in the destruction of the path as the
		 * Dir module could have added a directory to the path...
		 */
		Lst	    emptyPath = Lst_Init(FALSE);

		Dir_Expand(line, emptyPath, curTargs);

		Lst_Destroy(emptyPath, Dir_Destroy);
	    } else {
		/*
		 * No wildcards, but we want to avoid code duplication,
		 * so create a list with the word on it.
		 */
		(void)Lst_AtEnd(curTargs, (ClientData)line);
	    }

	    while(!Lst_IsEmpty(curTargs)) {
		char	*targName = (char *)Lst_DeQueue(curTargs);

		if (!Suff_IsTransform (targName)) {
		    gn = Targ_FindNode(targName, TARG_CREATE);
		} else {
		    gn = Suff_AddTransform(targName);
		}

		(void)Lst_AtEnd (targets, (ClientData)gn);
	    }
	} else if (specType == ExPath && *line != '.' && *line != '\0') {
	    Parse_Error(PARSE_WARNING, "Extra target (%s) ignored", line);
	}

	*cp = savec;
	/*
	 * If it is a special type and not .PATH, it's the only target we
	 * allow on this line...
	 */
	if (specType != Not && specType != ExPath) {
	    Boolean warn = FALSE;

	    while (*cp && (ParseIsEscaped(lstart, cp) ||
		((*cp != '!') && (*cp != ':')))) {
		if (ParseIsEscaped(lstart, cp) ||
		    (*cp != ' ' && *cp != '\t')) {
		    warn = TRUE;
		}
		cp++;
	    }
	    if (warn) {
		Parse_Error(PARSE_WARNING, "Extra target ignored");
	    }
	} else {
	    while (*cp && isspace ((unsigned char)*cp)) {
		cp++;
	    }
	}
	line = cp;
    } while (*line && (ParseIsEscaped(lstart, line) ||
	((*line != '!') && (*line != ':'))));

    /*
     * Don't need the list of target names anymore...
     */
    Lst_Destroy(curTargs, NOFREE);

    if (!Lst_IsEmpty(targets)) {
	switch(specType) {
	    default:
		Parse_Error(PARSE_WARNING, "Special and mundane targets don't mix. Mundane ones ignored");
		break;
	    case Default:
	    case Begin:
	    case End:
	    case Interrupt:
		/*
		 * These four create nodes on which to hang commands, so
		 * targets shouldn't be empty...
		 */
	    case Not:
		/*
		 * Nothing special here -- targets can be empty if it wants.
		 */
		break;
	}
    }

    /*
     * Have now parsed all the target names. Must parse the operator next. The
     * result is left in  op .
     */
    if (*cp == '!') {
	op = OP_FORCE;
    } else if (*cp == ':') {
	if (cp[1] == ':') {
	    op = OP_DOUBLEDEP;
	    cp++;
	} else {
	    op = OP_DEPENDS;
	}
    } else {
	Parse_Error(PARSE_FATAL, "Missing dependency operator");
	return;
    }

    cp++;			/* Advance beyond operator */

    Lst_ForEach(targets, ParseDoOp, (ClientData)&op);

    /*
     * Get to the first source
     */
    while (*cp && isspace ((unsigned char)*cp)) {
	cp++;
    }
    line = cp;

    /*
     * Several special targets take different actions if present with no
     * sources:
     *	a .SUFFIXES line with no sources clears out all old suffixes
     *	a .PRECIOUS line makes all targets precious
     *	a .IGNORE line ignores errors for all targets
     *	a .SILENT line creates silence when making all targets
     *	a .PATH removes all directories from the search path(s).
     */
    if (!*line) {
	switch (specType) {
	    case Suffixes:
		Suff_ClearSuffixes();
		break;
	    case Precious:
		allPrecious = TRUE;
		break;
	    case Ignore:
		ignoreErrors = TRUE;
		break;
	    case Silent:
		beSilent = TRUE;
		break;
	    case ExPath:
		Lst_ForEach(paths, ParseClearPath, (ClientData)NULL);
		Dir_SetPATH();
		break;
#ifdef POSIX
            case Posix:
                Var_Set("%POSIX", "1003.2", VAR_GLOBAL, 0);
                break;
#endif
	    default:
		break;
	}
    } else if (specType == MFlags) {
	/*
	 * Call on functions in main.c to deal with these arguments and
	 * set the initial character to a null-character so the loop to
	 * get sources won't get anything
	 */
	Main_ParseArgLine(line);
	*line = '\0';
    } else if (specType == ExShell) {
	if (Job_ParseShell(line) != SUCCESS) {
	    Parse_Error(PARSE_FATAL, "improper shell specification");
	    return;
	}
	*line = '\0';
    } else if ((specType == NotParallel) || (specType == SingleShell)) {
	*line = '\0';
    }

    /*
     * NOW GO FOR THE SOURCES
     */
    if ((specType == Suffixes) || (specType == ExPath) ||
	(specType == Includes) || (specType == Libs) ||
	(specType == Null) || (specType == ExObjdir))
    {
	while (*line) {
	    /*
	     * If the target was one that doesn't take files as its sources
	     * but takes something like suffixes, we take each
	     * space-separated word on the line as a something and deal
	     * with it accordingly.
	     *
	     * If the target was .SUFFIXES, we take each source as a
	     * suffix and add it to the list of suffixes maintained by the
	     * Suff module.
	     *
	     * If the target was a .PATH, we add the source as a directory
	     * to search on the search path.
	     *
	     * If it was .INCLUDES, the source is taken to be the suffix of
	     * files which will be #included and whose search path should
	     * be present in the .INCLUDES variable.
	     *
	     * If it was .LIBS, the source is taken to be the suffix of
	     * files which are considered libraries and whose search path
	     * should be present in the .LIBS variable.
	     *
	     * If it was .NULL, the source is the suffix to use when a file
	     * has no valid suffix.
	     *
	     * If it was .OBJDIR, the source is a new definition for .OBJDIR,
	     * and will cause make to do a new chdir to that path.
	     */
	    while (*cp && !isspace ((unsigned char)*cp)) {
		cp++;
	    }
	    savec = *cp;
	    *cp = '\0';
	    switch (specType) {
		case Suffixes:
		    Suff_AddSuffix(line, &mainNode);
		    break;
		case ExPath:
		    Lst_ForEach(paths, ParseAddDir, (ClientData)line);
		    break;
		case Includes:
		    Suff_AddInclude(line);
		    break;
		case Libs:
		    Suff_AddLib(line);
		    break;
		case Null:
		    Suff_SetNull(line);
		    break;
		case ExObjdir:
		    Main_SetObjdir(line);
		    break;
		default:
		    break;
	    }
	    *cp = savec;
	    if (savec != '\0') {
		cp++;
	    }
	    while (*cp && isspace ((unsigned char)*cp)) {
		cp++;
	    }
	    line = cp;
	}
	if (paths) {
	    Lst_Destroy(paths, NOFREE);
	}
	if (specType == ExPath)
	    Dir_SetPATH();
    } else {
	/*
	 * We don't need ParseDoSpecialSrc unless .WAIT is present.
	 */
	hasWait = (strstr(line, ".WAIT") != NULL);

	while (*line) {
	    /*
	     * The targets take real sources, so we must beware of archive
	     * specifications (i.e. things with left parentheses in them)
	     * and handle them accordingly.
	     */
	    while (*cp && !isspace ((unsigned char)*cp)) {
		if ((*cp == LPAREN) && (cp > line) && (cp[-1] != '$')) {
		    /*
		     * Only stop for a left parenthesis if it isn't at the
		     * start of a word (that'll be for variable changes
		     * later) and isn't preceded by a dollar sign (a dynamic
		     * source).
		     */
		    break;
		} else {
		    cp++;
		}
	    }

	    if (*cp == LPAREN) {
		/* sources = Lst_Init(FALSE);
		if (Arch_ParseArchive(&line, sources, VAR_CMD) != SUCCESS) {
		    Parse_Error(PARSE_FATAL,
				 "Error in source archive spec \"%s\"", line);
		    return;
		}

		while (!Lst_IsEmpty (sources)) {
		    gn = (GNode *) Lst_DeQueue(sources);
		    ParseDoSrc(tOp, gn->name, curSrcs, hasWait);
		}
		Lst_Destroy(sources, NOFREE);
		cp = line; */

		fprintf(stderr, "%s: %d: OP_ARCHV is deprecated\n", __FILE__, __LINE__);
		exit(1);
	    } else {
		if (*cp) {
		    *cp = '\0';
		    cp += 1;
		}

		ParseDoSrc(tOp, line, curSrcs, hasWait);
	    }
	    while (*cp && isspace ((unsigned char)*cp)) {
		cp++;
	    }
	    line = cp;
	}
    }

    if (mainNode == NILGNODE) {
	/*
	 * If we have yet to decide on a main target to make, in the
	 * absence of any user input, we want the first target on
	 * the first dependency line that is actually a real target
	 * (i.e. isn't a .USE or .EXEC rule) to be made.
	 */
	Lst_ForEach(targets, ParseFindMain, (ClientData)0);
    }

    /*
     * Finally, destroy the list of sources
     */
    Lst_Destroy(curSrcs, NOFREE);
}

/*-
 *---------------------------------------------------------------------
 * Parse_IsVar  --
 *	Return TRUE if the passed line is a variable assignment. A variable
 *	assignment consists of a single word followed by optional whitespace
 *	followed by either a += or an = operator.
 *	This function is used both by the Parse_File function and main when
 *	parsing the command-line arguments.
 *
 * Input:
 *	line		the line to check
 *
 * Results:
 *	TRUE if it is. FALSE if it ain't
 *
 * Side Effects:
 *	none
 *---------------------------------------------------------------------
 */
Boolean
Parse_IsVar(char *line)
{
    Boolean wasSpace = FALSE;	/* set TRUE if found a space */
    Boolean haveName = FALSE;	/* Set TRUE if have a variable name */
    int level = 0;
#define ISEQOPERATOR(c) \
	(((c) == '+') || ((c) == ':') || ((c) == '?') || ((c) == '!'))

    /*
     * Skip to variable name
     */
    for (;(*line == ' ') || (*line == '\t'); line++)
	continue;

    for (; *line != '=' || level != 0; line++)
	switch (*line) {
	case '\0':
	    /*
	     * end-of-line -- can't be a variable assignment.
	     */
	    return FALSE;

	case ' ':
	case '\t':
	    /*
	     * there can be as much white space as desired so long as there is
	     * only one word before the operator
	     */
	    wasSpace = TRUE;
	    break;

	case LPAREN:
	case '{':
	    level++;
	    break;

	case '}':
	case RPAREN:
	    level--;
	    break;

	default:
	    if (wasSpace && haveName) {
		    if (ISEQOPERATOR(*line)) {
			/*
			 * We must have a finished word
			 */
			if (level != 0)
			    return FALSE;

			/*
			 * When an = operator [+?!:] is found, the next
			 * character must be an = or it ain't a valid
			 * assignment.
			 */
			if (line[1] == '=')
			    return haveName;
#ifdef SUNSHCMD
			/*
			 * This is a shell command
			 */
			if (strncmp(line, ":sh", 3) == 0)
			    return haveName;
#endif
		    }
		    /*
		     * This is the start of another word, so not assignment.
		     */
		    return FALSE;
	    }
	    else {
		haveName = TRUE;
		wasSpace = FALSE;
	    }
	    break;
	}

    return haveName;
}

/*-
 *---------------------------------------------------------------------
 * Parse_DoVar  --
 *	Take the variable assignment in the passed line and do it in the
 *	global context.
 *
 *	Note: There is a lexical ambiguity with assignment modifier characters
 *	in variable names. This routine interprets the character before the =
 *	as a modifier. Therefore, an assignment like
 *	    C++=/usr/bin/CC
 *	is interpreted as "C+ +=" instead of "C++ =".
 *
 * Input:
 *	line		a line guaranteed to be a variable assignment.
 *			This reduces error checks
 *	ctxt		Context in which to do the assignment
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	the variable structure of the given variable name is altered in the
 *	global context.
 *---------------------------------------------------------------------
 */
void
Parse_DoVar(char *line, GNode *ctxt)
{
    char	   *cp;	/* pointer into line */
    enum {
	VAR_SUBST, VAR_APPEND, VAR_SHELL, VAR_NORMAL
    }	    	    type;   	/* Type of assignment */
    char            *opc;	/* ptr to operator character to
				 * null-terminate the variable name */
    Boolean	   freeCp = FALSE; /* TRUE if cp needs to be freed,
				    * i.e. if any variable expansion was
				    * performed */
    /*
     * Avoid clobbered variable warnings by forcing the compiler
     * to ``unregister'' variables
     */
#if __GNUC__
    (void) &cp;
    (void) &line;
#endif

    /*
     * Skip to variable name
     */
    while ((*line == ' ') || (*line == '\t')) {
	line++;
    }

    /*
     * Skip to operator character, nulling out whitespace as we go
     */
    for (cp = line + 1; *cp != '='; cp++) {
	if (isspace ((unsigned char)*cp)) {
	    *cp = '\0';
	}
    }
    opc = cp-1;		/* operator is the previous character */
    *cp++ = '\0';	/* nuke the = */

    /*
     * Check operator type
     */
    switch (*opc) {
	case '+':
	    type = VAR_APPEND;
	    *opc = '\0';
	    break;

	case '?':
	    /*
	     * If the variable already has a value, we don't do anything.
	     */
	    *opc = '\0';
	    if (Var_Exists(line, ctxt)) {
		return;
	    } else {
		type = VAR_NORMAL;
	    }
	    break;

	case ':':
	    type = VAR_SUBST;
	    *opc = '\0';
	    break;

	case '!':
	    type = VAR_SHELL;
	    *opc = '\0';
	    break;

	default:
#ifdef SUNSHCMD
	    while (opc > line && *opc != ':')
		opc--;

	    if (strncmp(opc, ":sh", 3) == 0) {
		type = VAR_SHELL;
		*opc = '\0';
		break;
	    }
#endif
	    type = VAR_NORMAL;
	    break;
    }

    while (isspace ((unsigned char)*cp)) {
	cp++;
    }

    if (type == VAR_APPEND) {
	Var_Append(line, cp, ctxt);
    } else if (type == VAR_SUBST) {
	/*
	 * Allow variables in the old value to be undefined, but leave their
	 * invocation alone -- this is done by forcing oldVars to be false.
	 * XXX: This can cause recursive variables, but that's not hard to do,
	 * and this allows someone to do something like
	 *
	 *  CFLAGS = $(.INCLUDES)
	 *  CFLAGS := -I.. $(CFLAGS)
	 *
	 * And not get an error.
	 */
	Boolean	  oldOldVars = oldVars;

	oldVars = FALSE;

	/*
	 * make sure that we set the variable the first time to nothing
	 * so that it gets substituted!
	 */
	if (!Var_Exists(line, ctxt))
	    Var_Set(line, "", ctxt, 0);

	cp = Var_Subst(NULL, cp, ctxt, FALSE);
	oldVars = oldOldVars;
	freeCp = TRUE;

	Var_Set(line, cp, ctxt, 0);
    } else if (type == VAR_SHELL) {
	char *res;
	const char *err;

	if (strchr(cp, '$') != NULL) {
	    /*
	     * There's a dollar sign in the command, so perform variable
	     * expansion on the whole thing. The resulting string will need
	     * freeing when we're done, so set freeCmd to TRUE.
	     */
	    cp = Var_Subst(NULL, cp, VAR_CMD, TRUE);
	    freeCp = TRUE;
	}

	res = Cmd_Exec(cp, &err);
	Var_Set(line, res, ctxt, 0);
	free(res);

	if (err)
	    Parse_Error(PARSE_WARNING, err, cp);
    } else {
	/*
	 * Normal assignment -- just do it.
	 */
	Var_Set(line, cp, ctxt, 0);
    }
    if (strcmp(line, MAKEOVERRIDES) == 0)
	Main_ExportMAKEFLAGS(FALSE);	/* re-export MAKEFLAGS */
    else if (strcmp(line, ".CURDIR") == 0) {
	/*
	 * Somone is being (too?) clever...
	 * Let's pretend they know what they are doing and
	 * re-initialize the 'cur' Path.
	 */
	Dir_InitCur(cp);
	Dir_SetPATH();
    }
    if (freeCp)
	free(cp);
}


/*-
 * ParseAddCmd  --
 *	Lst_ForEach function to add a command line to all targets
 *
 * Input:
 *	gnp		the node to which the command is to be added
 *	cmd		the command to add
 *
 * Results:
 *	Always 0
 *
 * Side Effects:
 *	A new element is added to the commands list of the node.
 */
static int
ParseAddCmd(ClientData gnp, ClientData cmd)
{
    GNode *gn = (GNode *) gnp;
    /* if target already supplied, ignore commands */
    if ((gn->type & OP_DOUBLEDEP) && !Lst_IsEmpty (gn->cohorts))
	gn = (GNode *) Lst_Datum(Lst_Last(gn->cohorts));
    if (!(gn->type & OP_HAS_COMMANDS)) {
	(void)Lst_AtEnd(gn->commands, cmd);
	ParseMark(gn);
    } else {
#ifdef notyet
	/* XXX: We cannot do this until we fix the tree */
	(void)Lst_AtEnd(gn->commands, cmd);
	Parse_Error(PARSE_WARNING,
		     "overriding commands for target \"%s\"; "
		     "previous commands defined at %s: %d ignored",
		     gn->name, gn->fname, gn->lineno);
#else
	Parse_Error(PARSE_WARNING,
		     "duplicate script for target \"%s\" ignored",
		     gn->name);
	ParseErrorInternal(gn->fname, gn->lineno, PARSE_WARNING,
			    "using previous script for \"%s\" defined here",
			    gn->name);
#endif
    }
    return(0);
}

/*-
 *-----------------------------------------------------------------------
 * ParseHasCommands --
 *	Callback procedure for Parse_File when destroying the list of
 *	targets on the last dependency line. Marks a target as already
 *	having commands if it does, to keep from having shell commands
 *	on multiple dependency lines.
 *
 * Input:
 *	gnp		Node to examine
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	OP_HAS_COMMANDS may be set for the target.
 *
 *-----------------------------------------------------------------------
 */
static void
ParseHasCommands(ClientData gnp)
{
    GNode *gn = (GNode *) gnp;
    if (!Lst_IsEmpty(gn->commands)) {
	gn->type |= OP_HAS_COMMANDS;
    }
}

/*-
 *-----------------------------------------------------------------------
 * Parse_AddIncludeDir --
 *	Add a directory to the path searched for included makefiles
 *	bracketed by double-quotes. Used by functions in main.c
 *
 * Input:
 *	dir		The name of the directory to add
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The directory is appended to the list.
 *
 *-----------------------------------------------------------------------
 */
void
Parse_AddIncludeDir(char *dir)
{
    (void) Dir_AddDir(parseIncPath, dir);
}

/*-
 *---------------------------------------------------------------------
 * ParseDoInclude  --
 *	Push to another file.
 *
 *	The input is the line minus the `.'. A file spec is a string
 *	enclosed in <> or "". The former is looked for only in sysIncPath.
 *	The latter in . and the directories specified by -I command line
 *	options
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A structure is added to the includes Lst and readProc, lineno,
 *	fname and curFILE are altered for the new file
 *---------------------------------------------------------------------
 */
static void
ParseDoInclude(char *line)
{
    char          *fullname;	/* full pathname of file */
    IFile         *oldFile;	/* state associated with current file */
    char          endc;	    	/* the character which ends the file spec */
    char          *cp;		/* current position in file spec */
    Boolean 	  isSystem; 	/* TRUE if makefile is a system makefile */
    int		  silent = (*line != 'i') ? 1 : 0;
    char	  *file = &line[7 + silent];

    /*
     * Skip to delimiter character so we know where to look
     */
    while ((*file == ' ') || (*file == '\t')) {
	file++;
    }

    if ((*file != '"') && (*file != '<')) {
	Parse_Error(PARSE_FATAL,
	    ".include filename must be delimited by '\"' or '<'");
	return;
    }

    /*
     * Set the search path on which to find the include file based on the
     * characters which bracket its name. Angle-brackets imply it's
     * a system Makefile while double-quotes imply it's a user makefile
     */
    if (*file == '<') {
	isSystem = TRUE;
	endc = '>';
    } else {
	isSystem = FALSE;
	endc = '"';
    }

    /*
     * Skip to matching delimiter
     */
    for (cp = ++file; *cp && *cp != endc; cp++) {
	continue;
    }

    if (*cp != endc) {
	Parse_Error(PARSE_FATAL,
		     "Unclosed %cinclude filename. '%c' expected",
		     '.', endc);
	return;
    }
    *cp = '\0';

    /*
     * Substitute for any variables in the file name before trying to
     * find the thing.
     */
    file = Var_Subst(NULL, file, VAR_CMD, FALSE);

    /*
     * Now we know the file's name and its search path, we attempt to
     * find the durn thing. A return of NULL indicates the file don't
     * exist.
     */
    fullname = (char *)NULL;

    if (!isSystem) {
	/*
	 * Include files contained in double-quotes are first searched for
	 * relative to the including file's location. We don't want to
	 * cd there, of course, so we just tack on the old file's
	 * leading path components and call Dir_FindFile to see if
	 * we can locate the beast.
	 */
	char	  *prefEnd, *Fname;

	/* Make a temporary copy of this, to be safe. */
	Fname = estrdup(curFile.fname);

	prefEnd = strrchr (Fname, '/');
	if (prefEnd != (char *)NULL) {
	    char  	*newName;

	    *prefEnd = '\0';
	    if (file[0] == '/')
		newName = estrdup(file);
	    else
		newName = str_concat(Fname, file, STR_ADDSLASH);
	    fullname = Dir_FindFile(newName, parseIncPath);
	    if (fullname == (char *)NULL) {
		fullname = Dir_FindFile(newName, dirSearchPath);
	    }
	    free (newName);
	    *prefEnd = '/';
	} else {
	    fullname = (char *)NULL;
	}
	free (Fname);
        if (fullname == (char *)NULL) {
	    /*
    	     * Makefile wasn't found in same directory as included makefile.
	     * Search for it first on the -I search path,
	     * then on the .PATH search path, if not found in a -I directory.
	     * XXX: Suffix specific?
	     */
	    fullname = Dir_FindFile(file, parseIncPath);
	    if (fullname == (char *)NULL) {
	        fullname = Dir_FindFile(file, dirSearchPath);
	    }
        }
    }

    /* Looking for a system file or file still not found */
    if (fullname == (char *)NULL) {
	/*
	 * Look for it on the system path
	 */
	fullname = Dir_FindFile(file, Lst_IsEmpty(sysIncPath) ? defIncPath : sysIncPath);
    }

    if (fullname == (char *) NULL) {
	*cp = endc;
	if (!silent)
	    Parse_Error(PARSE_FATAL, "Could not find %s", file);
	return;
    }

    free(file);

    /*
     * Once we find the absolute path to the file, we get to save all the
     * state from the current file before we can start reading this
     * include file. The state is stored in an IFile structure which
     * is placed on a list with other IFile structures. The list makes
     * a very nice stack to track how we got here...
     */
    oldFile = emalloc(sizeof(IFile));

    memcpy(oldFile, &curFile, sizeof (IFile));

    (void) Lst_AtFront(includes, (ClientData)oldFile);

    /*
     * Once the previous state has been saved, we can get down to reading
     * the new file. We set up the name of the file to be the absolute
     * name of the include file so error messages refer to the right
     * place. Naturally enough, we start reading at line number 0.
     */
    curFile.fname = fullname;
    curFile.lineno = 0;

    ParseSetParseFile(curFile.fname);

    curFile.F = fopen (fullname, "r");
    curFile.P = NULL;

    if (curFile.F == (FILE * ) NULL) {
	if (!silent)
	    Parse_Error(PARSE_FATAL, "Cannot open %s", fullname);
	/*
	 * Pop to previous file
	 */
	(void) ParseEOF(0);
    }
}


/*-
 *---------------------------------------------------------------------
 * ParseSetParseFile  --
 *	Set the .PARSEDIR and .PARSEFILE variables to the dirname and
 *	basename of the given filename
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The .PARSEDIR and .PARSEFILE variables are overwritten by the
 *	dirname and basename of the given filename.
 *---------------------------------------------------------------------
 */
static void
ParseSetParseFile(char *filename)
{
    char *slash;

    slash = strrchr(filename, '/');
    if (slash == 0) {
	Var_Set(".PARSEDIR", ".", VAR_GLOBAL, 0);
	Var_Set(".PARSEFILE", filename, VAR_GLOBAL, 0);
    } else {
	*slash = '\0';
	Var_Set(".PARSEDIR", filename, VAR_GLOBAL, 0);
	Var_Set(".PARSEFILE", slash+1, VAR_GLOBAL, 0);
	*slash = '/';
    }
}


/*-
 *---------------------------------------------------------------------
 * Parse_FromString  --
 *	Start Parsing from the given string
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A structure is added to the includes Lst and readProc, lineno,
 *	fname and curFILE are altered for the new file
 *---------------------------------------------------------------------
 */
void
Parse_FromString(char *str, int lineno)
{
    IFile         *oldFile;	/* state associated with this file */

    if (DEBUG(FOR))
	(void) fprintf(stderr, "%s\n---- at line %d\n", str, lineno);

    oldFile = emalloc(sizeof(IFile));
    memcpy(oldFile, &curFile, sizeof (IFile));

    (void) Lst_AtFront(includes, (ClientData)oldFile);

    curFile.F = NULL;
    curFile.P = emalloc(sizeof(PTR));
    curFile.P->str = curFile.P->ptr = str;
    curFile.lineno = lineno;
    curFile.fname = estrdup(curFile.fname);
}


#ifdef SYSVINCLUDE
/*-
 *---------------------------------------------------------------------
 * ParseTraditionalInclude  --
 *	Push to another file.
 *
 *	The input is the current line. The file name(s) are
 *	following the "include".
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A structure is added to the includes Lst and readProc, lineno,
 *	fname and curFILE are altered for the new file
 *---------------------------------------------------------------------
 */
static void
ParseTraditionalInclude(char *line)
{
    char          *fullname;	/* full pathname of file */
    IFile         *oldFile;	/* state associated with current file */
    char          *cp;		/* current position in file spec */
    char	  *prefEnd;
    int		   done = 0;
    int		   silent = (line[0] != 'i') ? 1 : 0;
    char	  *file = &line[silent + 7];
    char	  *cfname;
    size_t	   clineno;

    cfname  = curFile.fname;
    clineno = curFile.lineno;

    /*
     * Skip over whitespace
     */
    while (isspace((unsigned char)*file))
	file++;

    if (*file == '\0') {
	Parse_Error(PARSE_FATAL,
		     "Filename missing from \"include\"");
	return;
    }

    for (; !done; file = cp + 1) {
	/*
	 * Skip to end of line or next whitespace
	 */
	for (cp = file; *cp && !isspace((unsigned char) *cp); cp++)
	    continue;

	if (*cp)
	    *cp = '\0';
	else
	    done = 1;

	/*
	 * Substitute for any variables in the file name before trying to
	 * find the thing.
	 */
	file = Var_Subst(NULL, file, VAR_CMD, FALSE);

	/*
	 * Now we know the file's name, we attempt to find the durn thing.
	 * A return of NULL indicates the file don't exist.
	 *
	 * Include files are first searched for relative to the including
	 * file's location. We don't want to cd there, of course, so we
	 * just tack on the old file's leading path components and call
	 * Dir_FindFile to see if we can locate the beast.
	 * XXX - this *does* search in the current directory, right?
	 */

	prefEnd = strrchr(cfname, '/');
	if (prefEnd != NULL) {
	    char  	*newName;

	    *prefEnd = '\0';
	    newName = str_concat(cfname, file, STR_ADDSLASH);
	    fullname = Dir_FindFile(newName, parseIncPath);
	    if (fullname == NULL) {
		fullname = Dir_FindFile(newName, dirSearchPath);
	    }
	    free (newName);
	    *prefEnd = '/';
	} else {
	    fullname = NULL;
	}

	if (fullname == NULL) {
	    /*
	     * System makefile or makefile wasn't found in same directory as
	     * included makefile. Search for it first on the -I search path,
	     * then on the .PATH search path, if not found in a
	     * -I directory. XXX: Suffix specific?
	     */
	    fullname = Dir_FindFile(file, parseIncPath);
	    if (fullname == NULL) {
		fullname = Dir_FindFile(file, dirSearchPath);
	    }
	}

	if (fullname == NULL) {
	    /*
	     * Still haven't found the makefile. Look for it on the system
	     * path as a last resort.
	     */
	    fullname = Dir_FindFile(file,
			Lst_IsEmpty(sysIncPath) ? defIncPath : sysIncPath);
	}

	if (fullname == NULL) {
	    if (!silent)
		ParseErrorInternal(cfname, clineno, PARSE_FATAL,
		    "Could not find %s", file);
	    free(file);
	    continue;
	}

	free(file);

	/*
	 * Once we find the absolute path to the file, we get to save all
	 * the state from the current file before we can start reading this
	 * include file. The state is stored in an IFile structure which
	 * is placed on a list with other IFile structures. The list makes
	 * a very nice stack to track how we got here...
	 */
	oldFile = emalloc(sizeof(IFile));
	memcpy(oldFile, &curFile, sizeof (IFile));

	(void) Lst_AtFront(includes, (ClientData)oldFile);

	/*
	 * Once the previous state has been saved, we can get down to
	 * reading the new file. We set up the name of the file to be the
	 * absolute name of the include file so error messages refer to the
	 * right place. Naturally enough, we start reading at line number 0.
	 */
	curFile.fname = fullname;
	curFile.lineno = 0;

	curFile.F = fopen(fullname, "r");
	curFile.P = NULL;

	if (curFile.F == NULL) {
	    if (!silent)
		ParseErrorInternal(cfname, clineno, PARSE_FATAL,
		    "Cannot open %s", fullname);
	    /*
	     * Pop to previous file
	     */
	    (void) ParseEOF(1);
	}
    }
}
#endif

/*-
 *---------------------------------------------------------------------
 * ParseEOF  --
 *	Called when EOF is reached in the current file. If we were reading
 *	an include file, the includes stack is popped and things set up
 *	to go back to reading the previous file at the previous location.
 *
 * Results:
 *	CONTINUE if there's more to do. DONE if not.
 *
 * Side Effects:
 *	The old curFILE, is closed. The includes list is shortened.
 *	lineno, curFILE, and fname are changed if CONTINUE is returned.
 *---------------------------------------------------------------------
 */
static int
ParseEOF(int opened)
{
    IFile     *ifile;	/* the state on the top of the includes stack */

    if (Lst_IsEmpty(includes)) {
	Var_Delete(".PARSEDIR", VAR_GLOBAL);
	Var_Delete(".PARSEFILE", VAR_GLOBAL);
	return (DONE);
    }

    ifile = (IFile *) Lst_DeQueue(includes);

    /* XXX dispose of curFile info */
    free ((Address) curFile.fname);
    if (opened && curFile.F)
	(void) fclose (curFile.F);
    if (curFile.P) {
	free((Address) curFile.P->str);
	free((Address) curFile.P);
    }

    memcpy(&curFile, ifile, sizeof (IFile));

    free ((Address)ifile);

    /* pop the PARSEDIR/PARSEFILE variables */
    ParseSetParseFile(curFile.fname);
    return (CONTINUE);
}

/*-
 *---------------------------------------------------------------------
 * ParseReadc  --
 *	Read a character from the current file
 *
 * Results:
 *	The character that was read
 *
 * Side Effects:
 *---------------------------------------------------------------------
 */
static __inline int
ParseReadc(void)
{
    if (curFile.F)
	return fgetc(curFile.F);

    if (curFile.P && *curFile.P->ptr)
	return *curFile.P->ptr++;
    return EOF;
}


/*-
 *---------------------------------------------------------------------
 * ParseUnreadc  --
 *	Put back a character to the current file
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *---------------------------------------------------------------------
 */
static void
ParseUnreadc(int c)
{
    if (curFile.F) {
	ungetc(c, curFile.F);
	return;
    }
    if (curFile.P) {
	*--(curFile.P->ptr) = c;
	return;
    }
}


/* ParseSkipLine():
 *	Grab the next line
 *
 * Input:
 *	skip		Skip lines that don't start with .
 *	keep_newline	Keep newline character as is.
 *
 */
static char *
ParseSkipLine(int skip, int keep_newline)
{
    char *line;
    int c, lastc, lineLength = 0;
    Buffer buf;

    buf = Buf_Init(MAKE_BSIZE);

    do {
        Buf_Discard(buf, lineLength);
        lastc = '\0';

        while (((c = ParseReadc()) != '\n' || lastc == '\\')
               && c != EOF) {
            if (c == '\n') {
                if (keep_newline)
                    Buf_AddByte(buf, (Byte)c);
                else
                    Buf_ReplaceLastByte(buf, (Byte)' ');
                curFile.lineno++;

                while ((c = ParseReadc()) == ' ' || c == '\t');

                if (c == EOF)
                    break;
            }

            Buf_AddByte(buf, (Byte)c);
            lastc = c;
        }

        if (c == EOF) {
            Parse_Error(PARSE_FATAL, "Unclosed conditional/for loop");
            Buf_Destroy(buf, TRUE);
            return((char *)NULL);
        }

        curFile.lineno++;
        Buf_AddByte(buf, (Byte)'\0');
        line = (char *)Buf_GetAll(buf, &lineLength);
    } while (skip == 1 && line[0] != '.');

    Buf_Destroy(buf, FALSE);
    return line;
}


/*-
 *---------------------------------------------------------------------
 * ParseReadLine --
 *	Read an entire line from the input file. Called only by Parse_File.
 *	To facilitate escaped newlines and what have you, a character is
 *	buffered in 'lastc', which is '\0' when no characters have been
 *	read. When we break out of the loop, c holds the terminating
 *	character and lastc holds a character that should be added to
 *	the line (unless we don't read anything but a terminator).
 *
 * Results:
 *	A line w/o its newline
 *
 * Side Effects:
 *	Only those associated with reading a character
 *---------------------------------------------------------------------
 */
static char *
ParseReadLine(void)
{
    Buffer  	  buf;	    	/* Buffer for current line */
    int		  c;	      	/* the current character */
    int		  lastc;    	/* The most-recent character */
    Boolean	  semiNL;     	/* treat semi-colons as newlines */
    Boolean	  ignDepOp;   	/* TRUE if should ignore dependency operators
				 * for the purposes of setting semiNL */
    Boolean 	  ignComment;	/* TRUE if should ignore comments (in a
				 * shell command */
    char 	  *line;    	/* Result */
    char          *ep;		/* to strip trailing blanks */
    int	    	  lineLength;	/* Length of result */
    int	    	  lineno;	/* Saved line # */

    semiNL = FALSE;
    ignDepOp = FALSE;
    ignComment = FALSE;

    /*
     * Handle special-characters at the beginning of the line. Either a
     * leading tab (shell command) or pound-sign (possible conditional)
     * forces us to ignore comments and dependency operators and treat
     * semi-colons as semi-colons (by leaving semiNL FALSE). This also
     * discards completely blank lines.
     */
    for (;;) {
	c = ParseReadc();

	if (c == '\t') {
	    ignComment = ignDepOp = TRUE;
	    break;
	} else if (c == '\n') {
	    curFile.lineno++;
	} else if (c == '#') {
	    ParseUnreadc(c);
	    break;
	} else {
	    /*
	     * Anything else breaks out without doing anything
	     */
	    break;
	}
    }

    if (c != EOF) {
	lastc = c;
	buf = Buf_Init(MAKE_BSIZE);

	while (((c = ParseReadc ()) != '\n' || (lastc == '\\')) &&
	       (c != EOF))
	{
test_char:
	    switch(c) {
	    case '\n':
		/*
		 * Escaped newline: read characters until a non-space or an
		 * unescaped newline and replace them all by a single space.
		 * This is done by storing the space over the backslash and
		 * dropping through with the next nonspace. If it is a
		 * semi-colon and semiNL is TRUE, it will be recognized as a
		 * newline in the code below this...
		 */
		curFile.lineno++;
		lastc = ' ';
		while ((c = ParseReadc ()) == ' ' || c == '\t') {
		    continue;
		}
		if (c == EOF || c == '\n') {
		    goto line_read;
		} else {
		    /*
		     * Check for comments, semiNL's, etc. -- easier than
		     * ParseUnreadc(c); continue;
		     */
		    goto test_char;
		}
		/*NOTREACHED*/
		break;

	    case ';':
		/*
		 * Semi-colon: Need to see if it should be interpreted as a
		 * newline
		 */
		if (semiNL) {
		    /*
		     * To make sure the command that may be following this
		     * semi-colon begins with a tab, we push one back into the
		     * input stream. This will overwrite the semi-colon in the
		     * buffer. If there is no command following, this does no
		     * harm, since the newline remains in the buffer and the
		     * whole line is ignored.
		     */
		    ParseUnreadc('\t');
		    goto line_read;
		}
		break;
	    case '=':
		if (!semiNL) {
		    /*
		     * Haven't seen a dependency operator before this, so this
		     * must be a variable assignment -- don't pay attention to
		     * dependency operators after this.
		     */
		    ignDepOp = TRUE;
		} else if (lastc == ':' || lastc == '!') {
		    /*
		     * Well, we've seen a dependency operator already, but it
		     * was the previous character, so this is really just an
		     * expanded variable assignment. Revert semi-colons to
		     * being just semi-colons again and ignore any more
		     * dependency operators.
		     *
		     * XXX: Note that a line like "foo : a:=b" will blow up,
		     * but who'd write a line like that anyway?
		     */
		    ignDepOp = TRUE; semiNL = FALSE;
		}
		break;
	    case '#':
		if (!ignComment) {
		    if (
#if 0
		    compatMake &&
#endif
		    (lastc != '\\')) {
			/*
			 * If the character is a hash mark and it isn't escaped
			 * (or we're being compatible), the thing is a comment.
			 * Skip to the end of the line.
			 */
			do {
			    c = ParseReadc();
			    /*
			     * If we found a backslash not escaped
			     * itself it means that the comment is
			     * going to continue in the next line.
			     */
			    if (c == '\\')
				ParseReadc();
			} while ((c != '\n') && (c != EOF));
			goto line_read;
		    } else {
			/*
			 * Don't add the backslash. Just let the # get copied
			 * over.
			 */
			lastc = c;
			continue;
		    }
		}
		break;
	    case ':':
	    case '!':
		if (!ignDepOp && (c == ':' || c == '!')) {
		    /*
		     * A semi-colon is recognized as a newline only on
		     * dependency lines. Dependency lines are lines with a
		     * colon or an exclamation point. Ergo...
		     */
		    semiNL = TRUE;
		}
		break;
	    }
	    /*
	     * Copy in the previous character and save this one in lastc.
	     */
	    Buf_AddByte (buf, (Byte)lastc);
	    lastc = c;

	}
    line_read:
	curFile.lineno++;

	if (lastc != '\0') {
	    Buf_AddByte (buf, (Byte)lastc);
	}
	Buf_AddByte (buf, (Byte)'\0');
	line = (char *)Buf_GetAll (buf, &lineLength);
	Buf_Destroy(buf, FALSE);

	/*
	 * Strip trailing blanks and tabs from the line.
	 * Do not strip a blank or tab that is preceded by
	 * a '\'
	 */
	ep = line;
	while (*ep)
	    ++ep;
	while (ep > line + 1 && (ep[-1] == ' ' || ep[-1] == '\t')) {
	    if (ep > line + 1 && ep[-2] == '\\')
		break;
	    --ep;
	}
	*ep = 0;

	if (line[0] == '.') {
	    /*
	     * The line might be a conditional. Ask the conditional module
	     * about it and act accordingly
	     */
	    switch (Cond_Eval(line)) {
	    case COND_SKIP:
		/*
		 * Skip to next conditional that evaluates to COND_PARSE.
		 */
		do {
		    free (line);
		    line = ParseSkipLine(1, 0);
		} while (line && Cond_Eval(line) != COND_PARSE);
		if (line == NULL)
		    break;
		/*FALLTHRU*/
	    case COND_PARSE:
		free ((Address) line);
		line = ParseReadLine();
		break;
	    case COND_INVALID:
		lineno = curFile.lineno;
		if (For_Eval(line)) {
		    int ok;
		    free(line);
		    do {
			/*
			 * Skip after the matching end
			 */
			line = ParseSkipLine(0, 1);
			if (line == NULL) {
			    Parse_Error(PARSE_FATAL,
				     "Unexpected end of file in for loop.\n");
			    break;
			}
			ok = For_Eval(line);
			free(line);
		    }
		    while (ok);
		    if (line != NULL)
			For_Run(lineno);
		    line = ParseReadLine();
		}
		break;
	    }
	}
	return (line);

    } else {
	/*
	 * Hit end-of-file, so return a NULL line to indicate this.
	 */
	return((char *)NULL);
    }
}

/*-
 *-----------------------------------------------------------------------
 * ParseFinishLine --
 *	Handle the end of a dependency group.
 *
 * Results:
 *	Nothing.
 *
 * Side Effects:
 *	inLine set FALSE. 'targets' list destroyed.
 *
 *-----------------------------------------------------------------------
 */
static void
ParseFinishLine(void)
{
    if (inLine) {
	Lst_ForEach(targets, Suff_EndTransform, (ClientData)NULL);
	Lst_Destroy(targets, ParseHasCommands);
	targets = NULL;
	inLine = FALSE;
    }
}


/*-
 *---------------------------------------------------------------------
 * Parse_File --
 *	Parse a file into its component parts, incorporating it into the
 *	current dependency graph. This is the main function and controls
 *	almost every other function in this module
 *
 * Input:
 *	name		the name of the file being read
 *	stream		Stream open to makefile to parse
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Loads. Nodes are added to the list of all targets, nodes and links
 *	are added to the dependency graph. etc. etc. etc.
 *---------------------------------------------------------------------
 */
void
Parse_File(const char *name, FILE *stream)
{
    char	  *cp,		/* pointer into the line */
                  *line;	/* the line we're working on */

    inLine = FALSE;
    fatals = 0;

    curFile.fname = UNCONST(name);
    curFile.F = stream;
    curFile.lineno = 0;

    ParseSetParseFile(curFile.fname);

    do {
	while ((line = ParseReadLine()) != NULL) {
	    if (*line == '.') {
		/*
		 * Lines that begin with the special character are either
		 * include or undef directives.
		 */
		for (cp = line + 1; isspace ((unsigned char)*cp); cp++) {
		    continue;
		}
		if (strncmp(cp, "include", 7) == 0 ||
	    	    ((cp[0] == 's' || cp[0] == '-') &&
		    strncmp(&cp[1], "include", 7) == 0)) {
		    ParseDoInclude(cp);
		    goto nextLine;
		} else if (strncmp(cp, "undef", 5) == 0) {
		    char *cp2;
		    for (cp += 5; isspace((unsigned char) *cp); cp++) {
			continue;
		    }

		    for (cp2 = cp; !isspace((unsigned char) *cp2) &&
				   (*cp2 != '\0'); cp2++) {
			continue;
		    }

		    *cp2 = '\0';

		    Var_Delete(cp, VAR_GLOBAL);
		    goto nextLine;
		}
	    }
	    if (*line == '#') {
		/* If we're this far, the line must be a comment. */
		goto nextLine;
	    }

	    if (*line == '\t') {
		/*
		 * If a line starts with a tab, it can only hope to be
		 * a creation command.
		 */
#ifndef POSIX
	    shellCommand:
#endif
		for (cp = line + 1; isspace ((unsigned char)*cp); cp++) {
		    continue;
		}
		if (*cp) {
		    if (inLine) {
			/*
			 * So long as it's not a blank line and we're actually
			 * in a dependency spec, add the command to the list of
			 * commands of all targets in the dependency spec
			 */
			Lst_ForEach(targets, ParseAddCmd, cp);
#ifdef CLEANUP
			Lst_AtEnd(targCmds, (ClientData) line);
#endif
			continue;
		    } else {
			Parse_Error(PARSE_FATAL,
				     "Unassociated shell command \"%s\"",
				     cp);
		    }
		}
#ifdef SYSVINCLUDE
	    } else if (((strncmp(line, "include", 7) == 0 &&
	        isspace((unsigned char) line[7])) ||
	        ((line[0] == 's' || line[0] == '-') &&
	        strncmp(&line[1], "include", 7) == 0 &&
	        isspace((unsigned char) line[8]))) &&
	        strchr(line, ':') == NULL) {
		/*
		 * It's an S3/S5-style "include".
		 */
		ParseTraditionalInclude(line);
		goto nextLine;
#endif
	    } else if (Parse_IsVar(line)) {
		ParseFinishLine();
		Parse_DoVar(line, VAR_GLOBAL);
	    } else {
		/*
		 * We now know it's a dependency line so it needs to have all
		 * variables expanded before being parsed. Tell the variable
		 * module to complain if some variable is undefined...
		 * To make life easier on novices, if the line is indented we
		 * first make sure the line has a dependency operator in it.
		 * If it doesn't have an operator and we're in a dependency
		 * line's script, we assume it's actually a shell command
		 * and add it to the current list of targets.
		 */
#ifndef POSIX
		Boolean	nonSpace = FALSE;
#endif

		cp = line;
		if (isspace((unsigned char) line[0])) {
		    while ((*cp != '\0') && isspace((unsigned char) *cp)) {
			cp++;
		    }
		    if (*cp == '\0') {
			goto nextLine;
		    }
#ifndef POSIX
		    while (*cp && (ParseIsEscaped(line, cp) ||
			(*cp != ':') && (*cp != '!'))) {
			nonSpace = TRUE;
			cp++;
		    }
#endif
		}

#ifndef POSIX
		if (*cp == '\0') {
		    if (inLine) {
			Parse_Error(PARSE_WARNING,
				     "Shell command needs a leading tab");
			goto shellCommand;
		    } else if (nonSpace) {
			Parse_Error(PARSE_FATAL, "Missing operator");
		    }
		} else {
#endif
		    ParseFinishLine();

		    cp = Var_Subst(NULL, line, VAR_CMD, TRUE);
		    free (line);
		    line = cp;

		    /*
		     * Need a non-circular list for the target nodes
		     */
		    if (targets)
			Lst_Destroy(targets, NOFREE);

		    targets = Lst_Init(FALSE);
		    inLine = TRUE;

		    ParseDoDependency(line);
#ifndef POSIX
		}
#endif
	    }

	    nextLine:

	    free (line);
	}
	/*
	 * Reached EOF, but it may be just EOF of an include file...
	 */
    } while (ParseEOF(1) == CONTINUE);

    /*
     * Make sure conditionals are clean
     */
    Cond_End();

    if (fatals) {
	(void)fprintf(stderr,
	    "%s: Fatal errors encountered -- cannot continue\n",
	    progname);
	PrintOnError(NULL);
	exit (1);
    }
}

/*-
 *---------------------------------------------------------------------
 * Parse_Init --
 *	initialize the parsing module
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	the parseIncPath list is initialized...
 *---------------------------------------------------------------------
 */
void
Parse_Init(void)
{
    mainNode = NILGNODE;
    parseIncPath = Lst_Init(FALSE);
    sysIncPath = Lst_Init(FALSE);
    defIncPath = Lst_Init(FALSE);
    includes = Lst_Init(FALSE);
#ifdef CLEANUP
    targCmds = Lst_Init(FALSE);
#endif
}

void
Parse_End(void)
{
#ifdef CLEANUP
    Lst_Destroy(targCmds, (void (*)(ClientData))) free;
    if (targets)
	Lst_Destroy(targets, NOFREE);
    Lst_Destroy(defIncPath, Dir_Destroy);
    Lst_Destroy(sysIncPath, Dir_Destroy);
    Lst_Destroy(parseIncPath, Dir_Destroy);
    Lst_Destroy(includes, NOFREE);	/* Should be empty now */
#endif
}


/*-
 *-----------------------------------------------------------------------
 * Parse_MainName --
 *	Return a Lst of the main target to create for main()'s sake. If
 *	no such target exists, we Punt with an obnoxious error message.
 *
 * Results:
 *	A Lst of the single node to create.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
Lst
Parse_MainName(void)
{
    Lst           mainList;	/* result list */

    mainList = Lst_Init(FALSE);

    if (mainNode == NILGNODE) {
	Punt("no target to make.");
    	/*NOTREACHED*/
    } else if (mainNode->type & OP_DOUBLEDEP) {
	(void) Lst_AtEnd(mainList, (ClientData)mainNode);
	Lst_Concat(mainList, mainNode->cohorts, LST_CONCNEW);
    }
    else
	(void) Lst_AtEnd(mainList, (ClientData)mainNode);
    Var_Append(".TARGETS", mainNode->name, VAR_GLOBAL);
    return (mainList);
}

/*-
 *-----------------------------------------------------------------------
 * ParseMark --
 *	Add the filename and lineno to the GNode so that we remember
 *	where it was first defined.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static void
ParseMark(GNode *gn)
{
    gn->fname = strdup(curFile.fname);
    gn->lineno = curFile.lineno;
}
/* end parse.c */

/* begin str.c */
/*	$NetBSD: str.c,v 1.23 2005/02/16 15:11:52 christos Exp $	*/

/*-
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*-
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: str.c,v 1.23 2005/02/16 15:11:52 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char     sccsid[] = "@(#)str.c	5.8 (Berkeley) 6/1/90";
#else
__RCSID("$NetBSD: str.c,v 1.23 2005/02/16 15:11:52 christos Exp $");
#endif
#endif				/* not lint */
#endif

/* <<str.c includes>> */

/*-
 * str_concat --
 *	concatenate the two strings, inserting a space or slash between them,
 *	freeing them if requested.
 *
 * returns --
 *	the resulting string in allocated space.
 */
char *
str_concat(const char *s1, const char *s2, int flags)
{
	int len1, len2;
	char *result;

	/* get the length of both strings */
	len1 = strlen(s1);
	len2 = strlen(s2);

	/* allocate length plus separator plus EOS */
	result = emalloc((u_int)(len1 + len2 + 2));

	/* copy first string into place */
	memcpy(result, s1, len1);

	/* add separator character */
	if (flags & STR_ADDSPACE) {
		result[len1] = ' ';
		++len1;
	} else if (flags & STR_ADDSLASH) {
		result[len1] = '/';
		++len1;
	}

	/* copy second string plus EOS into place */
	memcpy(result + len1, s2, len2 + 1);

	return(result);
}

/*-
 * brk_string --
 *	Fracture a string into an array of words (as delineated by tabs or
 *	spaces) taking quotation marks into account.  Leading tabs/spaces
 *	are ignored.
 *
 * returns --
 *	Pointer to the array of pointers to the words.
 */
char **
brk_string(const char *str, int *store_argc, Boolean expand, char **buffer)
{
	int argc, ch;
	char inquote, *start, *t;
	const char *p;
	int len;
	int argmax = 50, curlen = 0;
    	char **argv = emalloc((argmax + 1) * sizeof(char *));

	/* skip leading space chars. */
	for (; *str == ' ' || *str == '\t'; ++str)
		continue;

	/* allocate room for a copy of the string */
	if ((len = strlen(str) + 1) > curlen)
		*buffer = emalloc(curlen = len);

	/*
	 * copy the string; at the same time, parse backslashes,
	 * quotes and build the argument list.
	 */
	argc = 0;
	inquote = '\0';
	for (p = str, start = t = *buffer;; ++p) {
		switch(ch = *p) {
		case '"':
		case '\'':
			if (inquote) {
				if (inquote == ch)
					inquote = '\0';
				else
					break;
			}
			else {
				inquote = (char) ch;
				/* Don't miss "" or '' */
				if (start == NULL && p[1] == inquote) {
					start = t + 1;
					break;
				}
			}
			if (!expand) {
				if (!start)
					start = t;
				*t++ = ch;
			}
			continue;
		case ' ':
		case '\t':
		case '\n':
			if (inquote)
				break;
			if (!start)
				continue;
			/* FALLTHROUGH */
		case '\0':
			/*
			 * end of a token -- make sure there's enough argv
			 * space and save off a pointer.
			 */
			if (!start)
			    goto done;

			*t++ = '\0';
			if (argc == argmax) {
				argmax *= 2;		/* ramp up fast */
				argv = (char **)erealloc(argv,
				    (argmax + 1) * sizeof(char *));
			}
			argv[argc++] = start;
			start = (char *)NULL;
			if (ch == '\n' || ch == '\0')
				goto done;
			continue;
		case '\\':
			if (!expand) {
				if (!start)
					start = t;
				*t++ = '\\';
				ch = *++p;
				break;
			}

			switch (ch = *++p) {
			case '\0':
			case '\n':
				/* hmmm; fix it up as best we can */
				ch = '\\';
				--p;
				break;
			case 'b':
				ch = '\b';
				break;
			case 'f':
				ch = '\f';
				break;
			case 'n':
				ch = '\n';
				break;
			case 'r':
				ch = '\r';
				break;
			case 't':
				ch = '\t';
				break;
			}
			break;
		}
		if (!start)
			start = t;
		*t++ = (char) ch;
	}
done:	argv[argc] = (char *)NULL;
	*store_argc = argc;
	return(argv);
}

/*
 * Str_FindSubstring -- See if a string contains a particular substring.
 *
 * Input:
 *	string		String to search.
 *	substring	Substring to find in string.
 *
 * Results: If string contains substring, the return value is the location of
 * the first matching instance of substring in string.  If string doesn't
 * contain substring, the return value is NULL.  Matching is done on an exact
 * character-for-character basis with no wildcards or special characters.
 *
 * Side effects: None.
 */
char *
Str_FindSubstring(const char *string, const char *substring)
{
	const char *a, *b;

	/*
	 * First scan quickly through the two strings looking for a single-
	 * character match.  When it's found, then compare the rest of the
	 * substring.
	 */

	for (b = substring; *string != 0; string += 1) {
		if (*string != *b)
			continue;
		a = string;
		for (;;) {
			if (*b == 0)
				return UNCONST(string);
			if (*a++ != *b++)
				break;
		}
		b = substring;
	}
	return NULL;
}

/*
 * Str_Match --
 *
 * See if a particular string matches a particular pattern.
 *
 * Results: Non-zero is returned if string matches pattern, 0 otherwise. The
 * matching operation permits the following special characters in the
 * pattern: *?\[] (see the man page for details on what these mean).
 *
 * Side effects: None.
 */
int
Str_Match(const char *string, const char *pattern)
{
	char c2;

	for (;;) {
		/*
		 * See if we're at the end of both the pattern and the
		 * string. If, we succeeded.  If we're at the end of the
		 * pattern but not at the end of the string, we failed.
		 */
		if (*pattern == 0)
			return(!*string);
		if (*string == 0 && *pattern != '*')
			return(0);
		/*
		 * Check for a "*" as the next pattern character.  It matches
		 * any substring.  We handle this by calling ourselves
		 * recursively for each postfix of string, until either we
		 * match or we reach the end of the string.
		 */
		if (*pattern == '*') {
			pattern += 1;
			if (*pattern == 0)
				return(1);
			while (*string != 0) {
				if (Str_Match(string, pattern))
					return(1);
				++string;
			}
			return(0);
		}
		/*
		 * Check for a "?" as the next pattern character.  It matches
		 * any single character.
		 */
		if (*pattern == '?')
			goto thisCharOK;
		/*
		 * Check for a "[" as the next pattern character.  It is
		 * followed by a list of characters that are acceptable, or
		 * by a range (two characters separated by "-").
		 */
		if (*pattern == '[') {
			++pattern;
			for (;;) {
				if ((*pattern == ']') || (*pattern == 0))
					return(0);
				if (*pattern == *string)
					break;
				if (pattern[1] == '-') {
					c2 = pattern[2];
					if (c2 == 0)
						return(0);
					if ((*pattern <= *string) &&
					    (c2 >= *string))
						break;
					if ((*pattern >= *string) &&
					    (c2 <= *string))
						break;
					pattern += 2;
				}
				++pattern;
			}
			while ((*pattern != ']') && (*pattern != 0))
				++pattern;
			goto thisCharOK;
		}
		/*
		 * If the next pattern character is '/', just strip off the
		 * '/' so we do exact matching on the character that follows.
		 */
		if (*pattern == '\\') {
			++pattern;
			if (*pattern == 0)
				return(0);
		}
		/*
		 * There's no special character.  Just make sure that the
		 * next characters of each string match.
		 */
		if (*pattern != *string)
			return(0);
thisCharOK:	++pattern;
		++string;
	}
}


/*-
 *-----------------------------------------------------------------------
 * Str_SYSVMatch --
 *	Check word against pattern for a match (% is wild),
 *
 * Input:
 *	word		Word to examine
 *	pattern		Pattern to examine against
 *	len		Number of characters to substitute
 *
 * Results:
 *	Returns the beginning position of a match or null. The number
 *	of characters matched is returned in len.
 *
 * Side Effects:
 *	None
 *
 *-----------------------------------------------------------------------
 */
char *
Str_SYSVMatch(const char *word, const char *pattern, int *len)
{
    const char *p = pattern;
    const char *w = word;
    const char *m;

    if (*p == '\0') {
	/* Null pattern is the whole string */
	*len = strlen(w);
	return UNCONST(w);
    }

    if ((m = strchr(p, '%')) != NULL) {
	/* check that the prefix matches */
	for (; p != m && *w && *w == *p; w++, p++)
	     continue;

	if (p != m)
	    return NULL;	/* No match */

	if (*++p == '\0') {
	    /* No more pattern, return the rest of the string */
	    *len = strlen(w);
	    return UNCONST(w);
	}
    }

    m = w;

    /* Find a matching tail */
    do
	if (strcmp(p, w) == 0) {
	    *len = w - m;
	    return UNCONST(m);
	}
    while (*w++ != '\0');

    return NULL;
}


/*-
 *-----------------------------------------------------------------------
 * Str_SYSVSubst --
 *	Substitute '%' on the pattern with len characters from src.
 *	If the pattern does not contain a '%' prepend len characters
 *	from src.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Places result on buf
 *
 *-----------------------------------------------------------------------
 */
void
Str_SYSVSubst(Buffer buf, char *pat, char *src, int len)
{
    char *m;

    if ((m = strchr(pat, '%')) != NULL) {
	/* Copy the prefix */
	Buf_AddBytes(buf, m - pat, (Byte *) pat);
	/* skip the % */
	pat = m + 1;
    }

    /* Copy the pattern */
    Buf_AddBytes(buf, len, (Byte *) src);

    /* append the rest */
    Buf_AddBytes(buf, strlen(pat), (Byte *) pat);
}
/* end str.c */

/* begin suff.c */
/*	$NetBSD: suff.c,v 1.48 2005/02/16 15:11:52 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: suff.c,v 1.48 2005/02/16 15:11:52 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)suff.c	8.4 (Berkeley) 3/21/94";
#else
__RCSID("$NetBSD: suff.c,v 1.48 2005/02/16 15:11:52 christos Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * suff.c --
 *	Functions to maintain suffix lists and find implicit dependents
 *	using suffix transformation rules
 *
 * Interface:
 *	Suff_Init 	    	Initialize all things to do with suffixes.
 *
 *	Suff_End 	    	Cleanup the module
 *
 *	Suff_DoPaths	    	This function is used to make life easier
 *	    	  	    	when searching for a file according to its
 *	    	  	    	suffix. It takes the global search path,
 *	    	  	    	as defined using the .PATH: target, and appends
 *	    	  	    	its directories to the path of each of the
 *	    	  	    	defined suffixes, as specified using
 *	    	  	    	.PATH<suffix>: targets. In addition, all
 *	    	  	    	directories given for suffixes labeled as
 *	    	  	    	include files or libraries, using the .INCLUDES
 *	    	  	    	or .LIBS targets, are played with using
 *	    	  	    	Dir_MakeFlags to create the .INCLUDES and
 *	    	  	    	.LIBS global variables.
 *
 *	Suff_ClearSuffixes  	Clear out all the suffixes and defined
 *	    	  	    	transformations.
 *
 *	Suff_IsTransform    	Return TRUE if the passed string is the lhs
 *	    	  	    	of a transformation rule.
 *
 *	Suff_AddSuffix	    	Add the passed string as another known suffix.
 *
 *	Suff_GetPath	    	Return the search path for the given suffix.
 *
 *	Suff_AddInclude	    	Mark the given suffix as denoting an include
 *	    	  	    	file.
 *
 *	Suff_AddLib	    	Mark the given suffix as denoting a library.
 *
 *	Suff_AddTransform   	Add another transformation to the suffix
 *	    	  	    	graph. Returns  GNode suitable for framing, I
 *	    	  	    	mean, tacking commands, attributes, etc. on.
 *
 *	Suff_SetNull	    	Define the suffix to consider the suffix of
 *	    	  	    	any file that doesn't have a known one.
 *
 *	Suff_FindDeps	    	Find implicit sources for and the location of
 *	    	  	    	a target based on its suffix. Returns the
 *	    	  	    	bottom-most node added to the graph or NILGNODE
 *	    	  	    	if the target had no implicit sources.
 *
 *	Suff_FindPath	    	Return the appropriate path to search in
 *				order to find the node.
 */

/* <<suff.c includes>> */

static Lst       sufflist;	/* Lst of suffixes */
#ifdef CLEANUP
static Lst	 suffClean;	/* Lst of suffixes to be cleaned */
#endif
static Lst	 srclist;	/* Lst of sources */
static Lst       transforms;	/* Lst of transformation rules */

static int        sNum = 0;	/* Counter for assigning suffix numbers */

/*
 * Structure describing an individual suffix.
 */
typedef struct _Suff {
    char         *name;	    	/* The suffix itself */
    int		 nameLen;	/* Length of the suffix */
    short	 flags;      	/* Type of suffix */
#define SUFF_INCLUDE	  0x01	    /* One which is #include'd */
#define SUFF_LIBRARY	  0x02	    /* One which contains a library */
#define SUFF_NULL 	  0x04	    /* The empty suffix */
    Lst    	 searchPath;	/* The path along which files of this suffix
				 * may be found */
    int          sNum;	      	/* The suffix number */
    int		 refCount;	/* Reference count of list membership */
    Lst          parents;	/* Suffixes we have a transformation to */
    Lst          children;	/* Suffixes we have a transformation from */
    Lst		 ref;		/* List of lists this suffix is referenced */
} Suff;

/*
 * for SuffSuffIsSuffix
 */
typedef struct {
    char	*ename;		/* The end of the name */
    int		 len;		/* Length of the name */
} SuffixCmpData;

/*
 * Structure used in the search for implied sources.
 */
typedef struct _Src {
    char            *file;	/* The file to look for */
    char    	    *pref;  	/* Prefix from which file was formed */
    Suff            *suff;	/* The suffix on the file */
    struct _Src     *parent;	/* The Src for which this is a source */
    GNode           *node;	/* The node describing the file */
    int	    	    children;	/* Count of existing children (so we don't free
				 * this thing too early or never nuke it) */
#ifdef DEBUG_SRC
    Lst		    cp;		/* Debug; children list */
#endif
} Src;

/*
 * A structure for passing more than one argument to the Lst-library-invoked
 * function...
 */
typedef struct {
    Lst            l;
    Src            *s;
} LstSrc;

typedef struct {
    GNode	  **gn;
    Suff	   *s;
    Boolean	    r;
} GNodeSuff;

static Suff 	    *suffNull;	/* The NULL suffix for this run */
static Suff 	    *emptySuff;	/* The empty suffix required for POSIX
				 * single-suffix transformation rules */


static char *SuffStrIsPrefix(char *, char *);
static char *SuffSuffIsSuffix(Suff *, SuffixCmpData *);
static int SuffSuffIsSuffixP(ClientData, ClientData);
static int SuffSuffHasNameP(ClientData, ClientData);
static int SuffSuffIsPrefix(ClientData, ClientData);
static int SuffGNHasNameP(ClientData, ClientData);
static void SuffUnRef(ClientData, ClientData);
static void SuffFree(ClientData);
static void SuffInsert(Lst, Suff *);
static void SuffRemove(Lst, Suff *);
static Boolean SuffParseTransform(char *, Suff **, Suff **);
static int SuffRebuildGraph(ClientData, ClientData);
static int SuffScanTargets(ClientData, ClientData);
static int SuffAddSrc(ClientData, ClientData);
static int SuffRemoveSrc(Lst);
static void SuffAddLevel(Lst, Src *);
static Src *SuffFindThem(Lst, Lst);
static Src *SuffFindCmds(Src *, Lst);
static int SuffExpandChildren(LstNode, GNode *);
static Boolean SuffApplyTransform(GNode *, GNode *, Suff *, Suff *);
static void SuffFindDeps(GNode *, Lst);
/* static void SuffFindArchiveDeps(GNode *, Lst); */
static void SuffFindNormalDeps(GNode *, Lst);
static int SuffPrintName(ClientData, ClientData);
static int SuffPrintSuff(ClientData, ClientData);
static int SuffPrintTrans(ClientData, ClientData);

	/*************** Lst Predicates ****************/
/*-
 *-----------------------------------------------------------------------
 * SuffStrIsPrefix  --
 *	See if pref is a prefix of str.
 *
 * Input:
 *	pref		possible prefix
 *	str		string to check
 *
 * Results:
 *	NULL if it ain't, pointer to character in str after prefix if so
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static char    *
SuffStrIsPrefix(char *pref, char *str)
{
    while (*str && *pref == *str) {
	pref++;
	str++;
    }

    return (*pref ? NULL : str);
}

/*-
 *-----------------------------------------------------------------------
 * SuffSuffIsSuffix  --
 *	See if suff is a suffix of str. sd->ename should point to THE END
 *	of the string to check. (THE END == the null byte)
 *
 * Input:
 *	s		possible suffix
 *	sd		string to examine
 *
 * Results:
 *	NULL if it ain't, pointer to character in str before suffix if
 *	it is.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static char *
SuffSuffIsSuffix(Suff *s, SuffixCmpData *sd)
{
    char  *p1;	    	/* Pointer into suffix name */
    char  *p2;	    	/* Pointer into string being examined */

    if (sd->len < s->nameLen)
	return NULL;		/* this string is shorter than the suffix */

    p1 = s->name + s->nameLen;
    p2 = sd->ename;

    while (p1 >= s->name && *p1 == *p2) {
	p1--;
	p2--;
    }

    return (p1 == s->name - 1 ? p2 : NULL);
}

/*-
 *-----------------------------------------------------------------------
 * SuffSuffIsSuffixP --
 *	Predicate form of SuffSuffIsSuffix. Passed as the callback function
 *	to Lst_Find.
 *
 * Results:
 *	0 if the suffix is the one desired, non-zero if not.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static int
SuffSuffIsSuffixP(ClientData s, ClientData sd)
{
    return(!SuffSuffIsSuffix((Suff *) s, (SuffixCmpData *) sd));
}

/*-
 *-----------------------------------------------------------------------
 * SuffSuffHasNameP --
 *	Callback procedure for finding a suffix based on its name. Used by
 *	Suff_GetPath.
 *
 * Input:
 *	s		Suffix to check
 *	sd		Desired name
 *
 * Results:
 *	0 if the suffix is of the given name. non-zero otherwise.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static int
SuffSuffHasNameP(ClientData s, ClientData sname)
{
    return (strcmp ((char *) sname, ((Suff *) s)->name));
}

/*-
 *-----------------------------------------------------------------------
 * SuffSuffIsPrefix  --
 *	See if the suffix described by s is a prefix of the string. Care
 *	must be taken when using this to search for transformations and
 *	what-not, since there could well be two suffixes, one of which
 *	is a prefix of the other...
 *
 * Input:
 *	s		suffix to compare
 *	str		string to examine
 *
 * Results:
 *	0 if s is a prefix of str. non-zero otherwise
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static int
SuffSuffIsPrefix(ClientData s, ClientData str)
{
    return (SuffStrIsPrefix(((Suff *) s)->name, (char *) str) == NULL ? 1 : 0);
}

/*-
 *-----------------------------------------------------------------------
 * SuffGNHasNameP  --
 *	See if the graph node has the desired name
 *
 * Input:
 *	gn		current node we're looking at
 *	name		name we're looking for
 *
 * Results:
 *	0 if it does. non-zero if it doesn't
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static int
SuffGNHasNameP(ClientData gn, ClientData name)
{
    return (strcmp ((char *) name, ((GNode *) gn)->name));
}

 	    /*********** Maintenance Functions ************/

static void
SuffUnRef(ClientData lp, ClientData sp)
{
    Lst l = (Lst) lp;

    LstNode ln = Lst_Member(l, sp);
    if (ln != NILLNODE) {
	Lst_Remove(l, ln);
	((Suff *) sp)->refCount--;
    }
}

/*-
 *-----------------------------------------------------------------------
 * SuffFree  --
 *	Free up all memory associated with the given suffix structure.
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	the suffix entry is detroyed
 *-----------------------------------------------------------------------
 */
static void
SuffFree(ClientData sp)
{
    Suff           *s = (Suff *) sp;

    if (s == suffNull)
	suffNull = NULL;

    if (s == emptySuff)
	emptySuff = NULL;

#ifdef notdef
    /* We don't delete suffixes in order, so we cannot use this */
    if (s->refCount)
	Punt("Internal error deleting suffix `%s' with refcount = %d", s->name,
	    s->refCount);
#endif

    Lst_Destroy(s->ref, NOFREE);
    Lst_Destroy(s->children, NOFREE);
    Lst_Destroy(s->parents, NOFREE);
    Lst_Destroy(s->searchPath, Dir_Destroy);

    free ((Address)s->name);
    free ((Address)s);
}

/*-
 *-----------------------------------------------------------------------
 * SuffRemove  --
 *	Remove the suffix into the list
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The reference count for the suffix is decremented and the
 *	suffix is possibly freed
 *-----------------------------------------------------------------------
 */
static void
SuffRemove(Lst l, Suff *s)
{
    SuffUnRef((ClientData) l, (ClientData) s);
    if (s->refCount == 0) {
	SuffUnRef((ClientData) sufflist, (ClientData) s);
	SuffFree((ClientData) s);
    }
}

/*-
 *-----------------------------------------------------------------------
 * SuffInsert  --
 *	Insert the suffix into the list keeping the list ordered by suffix
 *	numbers.
 *
 * Input:
 *	l		the list where in s should be inserted
 *	s		the suffix to insert
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The reference count of the suffix is incremented
 *-----------------------------------------------------------------------
 */
static void
SuffInsert(Lst l, Suff *s)
{
    LstNode 	  ln;		/* current element in l we're examining */
    Suff          *s2 = NULL;	/* the suffix descriptor in this element */

    if (Lst_Open(l) == FAILURE) {
	return;
    }
    while ((ln = Lst_Next(l)) != NILLNODE) {
	s2 = (Suff *) Lst_Datum(ln);
	if (s2->sNum >= s->sNum) {
	    break;
	}
    }

    Lst_Close(l);
    if (DEBUG(SUFF)) {
	printf("inserting %s(%d)...", s->name, s->sNum);
    }
    if (ln == NILLNODE) {
	if (DEBUG(SUFF)) {
	    printf("at end of list\n");
	}
	(void)Lst_AtEnd (l, (ClientData)s);
	s->refCount++;
	(void)Lst_AtEnd(s->ref, (ClientData) l);
    } else if (s2->sNum != s->sNum) {
	if (DEBUG(SUFF)) {
	    printf("before %s(%d)\n", s2->name, s2->sNum);
	}
	(void)Lst_Insert (l, ln, (ClientData)s);
	s->refCount++;
	(void)Lst_AtEnd(s->ref, (ClientData) l);
    } else if (DEBUG(SUFF)) {
	printf("already there\n");
    }
}

/*-
 *-----------------------------------------------------------------------
 * Suff_ClearSuffixes --
 *	This is gross. Nuke the list of suffixes but keep all transformation
 *	rules around. The transformation graph is destroyed in this process,
 *	but we leave the list of rules so when a new graph is formed the rules
 *	will remain.
 *	This function is called from the parse module when a
 *	.SUFFIXES:\n line is encountered.
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	the sufflist and its graph nodes are destroyed
 *-----------------------------------------------------------------------
 */
void
Suff_ClearSuffixes(void)
{
#ifdef CLEANUP
    Lst_Concat(suffClean, sufflist, LST_CONCLINK);
#endif
    sufflist = Lst_Init(FALSE);
    sNum = 0;
    suffNull = emptySuff;
}

/*-
 *-----------------------------------------------------------------------
 * SuffParseTransform --
 *	Parse a transformation string to find its two component suffixes.
 *
 * Input:
 *	str		String being parsed
 *	srcPtr		Place to store source of trans.
 *	targPtr		Place to store target of trans.
 *
 * Results:
 *	TRUE if the string is a valid transformation and FALSE otherwise.
 *
 * Side Effects:
 *	The passed pointers are overwritten.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
SuffParseTransform(char *str, Suff **srcPtr, Suff **targPtr)
{
    LstNode		srcLn;	    /* element in suffix list of trans source*/
    Suff		*src;	    /* Source of transformation */
    LstNode		targLn;	    /* element in suffix list of trans target*/
    char		*str2;	    /* Extra pointer (maybe target suffix) */
    LstNode 	    	singleLn;   /* element in suffix list of any suffix
				     * that exactly matches str */
    Suff    	    	*single = NULL;/* Source of possible transformation to
				     * null suffix */

    srcLn = NILLNODE;
    singleLn = NILLNODE;

    /*
     * Loop looking first for a suffix that matches the start of the
     * string and then for one that exactly matches the rest of it. If
     * we can find two that meet these criteria, we've successfully
     * parsed the string.
     */
    for (;;) {
	if (srcLn == NILLNODE) {
	    srcLn = Lst_Find(sufflist, (ClientData)str, SuffSuffIsPrefix);
	} else {
	    srcLn = Lst_FindFrom(sufflist, Lst_Succ(srcLn), (ClientData)str,
				  SuffSuffIsPrefix);
	}
	if (srcLn == NILLNODE) {
	    /*
	     * Ran out of source suffixes -- no such rule
	     */
	    if (singleLn != NILLNODE) {
		/*
		 * Not so fast Mr. Smith! There was a suffix that encompassed
		 * the entire string, so we assume it was a transformation
		 * to the null suffix (thank you POSIX). We still prefer to
		 * find a double rule over a singleton, hence we leave this
		 * check until the end.
		 *
		 * XXX: Use emptySuff over suffNull?
		 */
		*srcPtr = single;
		*targPtr = suffNull;
		return(TRUE);
	    }
	    return (FALSE);
	}
	src = (Suff *) Lst_Datum(srcLn);
	str2 = str + src->nameLen;
	if (*str2 == '\0') {
	    single = src;
	    singleLn = srcLn;
	} else {
	    targLn = Lst_Find(sufflist, (ClientData)str2, SuffSuffHasNameP);
	    if (targLn != NILLNODE) {
		*srcPtr = src;
		*targPtr = (Suff *)Lst_Datum(targLn);
		return (TRUE);
	    }
	}
    }
}

/*-
 *-----------------------------------------------------------------------
 * Suff_IsTransform  --
 *	Return TRUE if the given string is a transformation rule
 *
 *
 * Input:
 *	str		string to check
 *
 * Results:
 *	TRUE if the string is a concatenation of two known suffixes.
 *	FALSE otherwise
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Suff_IsTransform(char *str)
{
    Suff    	  *src, *targ;

    return (SuffParseTransform(str, &src, &targ));
}

/*-
 *-----------------------------------------------------------------------
 * Suff_AddTransform --
 *	Add the transformation rule described by the line to the
 *	list of rules and place the transformation itself in the graph
 *
 * Input:
 *	line		name of transformation to add
 *
 * Results:
 *	The node created for the transformation in the transforms list
 *
 * Side Effects:
 *	The node is placed on the end of the transforms Lst and links are
 *	made between the two suffixes mentioned in the target name
 *-----------------------------------------------------------------------
 */
GNode *
Suff_AddTransform(char *line)
{
    GNode         *gn;		/* GNode of transformation rule */
    Suff          *s,		/* source suffix */
                  *t;		/* target suffix */
    LstNode 	  ln;	    	/* Node for existing transformation */

    ln = Lst_Find(transforms, (ClientData)line, SuffGNHasNameP);
    if (ln == NILLNODE) {
	/*
	 * Make a new graph node for the transformation. It will be filled in
	 * by the Parse module.
	 */
	gn = Targ_NewGN(line);
	(void)Lst_AtEnd (transforms, (ClientData)gn);
    } else {
	/*
	 * New specification for transformation rule. Just nuke the old list
	 * of commands so they can be filled in again... We don't actually
	 * free the commands themselves, because a given command can be
	 * attached to several different transformations.
	 */
	gn = (GNode *) Lst_Datum(ln);
	Lst_Destroy(gn->commands, NOFREE);
	Lst_Destroy(gn->children, NOFREE);
	gn->commands = Lst_Init(FALSE);
	gn->children = Lst_Init(FALSE);
    }

    gn->type = OP_TRANSFORM;

    (void)SuffParseTransform(line, &s, &t);

    /*
     * link the two together in the proper relationship and order
     */
    if (DEBUG(SUFF)) {
	printf("defining transformation from `%s' to `%s'\n",
		s->name, t->name);
    }
    SuffInsert(t->children, s);
    SuffInsert(s->parents, t);

    return (gn);
}

/*-
 *-----------------------------------------------------------------------
 * Suff_EndTransform --
 *	Handle the finish of a transformation definition, removing the
 *	transformation from the graph if it has neither commands nor
 *	sources. This is a callback procedure for the Parse module via
 *	Lst_ForEach
 *
 * Input:
 *	gnp		Node for transformation
 *	dummy		Node for transformation
 *
 * Results:
 *	=== 0
 *
 * Side Effects:
 *	If the node has no commands or children, the children and parents
 *	lists of the affected suffixes are altered.
 *
 *-----------------------------------------------------------------------
 */
int
Suff_EndTransform(ClientData gnp, ClientData dummy)
{
    GNode *gn = (GNode *) gnp;

    if ((gn->type & OP_DOUBLEDEP) && !Lst_IsEmpty (gn->cohorts))
	gn = (GNode *) Lst_Datum(Lst_Last(gn->cohorts));
    if ((gn->type & OP_TRANSFORM) && Lst_IsEmpty(gn->commands) &&
	Lst_IsEmpty(gn->children))
    {
	Suff	*s, *t;

	/*
	 * SuffParseTransform() may fail for special rules which are not
	 * actual transformation rules. (e.g. .DEFAULT)
	 */
	if (SuffParseTransform(gn->name, &s, &t)) {
	    Lst	 p;

	    if (DEBUG(SUFF)) {
		printf("deleting transformation from `%s' to `%s'\n",
		s->name, t->name);
	    }

	    /*
	     * Store s->parents because s could be deleted in SuffRemove
	     */
	    p = s->parents;

	    /*
	     * Remove the source from the target's children list. We check for a
	     * nil return to handle a beanhead saying something like
	     *  .c.o .c.o:
	     *
	     * We'll be called twice when the next target is seen, but .c and .o
	     * are only linked once...
	     */
	    SuffRemove(t->children, s);

	    /*
	     * Remove the target from the source's parents list
	     */
	    SuffRemove(p, t);
	}
    } else if ((gn->type & OP_TRANSFORM) && DEBUG(SUFF)) {
	printf("transformation %s complete\n", gn->name);
    }

    return(dummy ? 0 : 0);
}

/*-
 *-----------------------------------------------------------------------
 * SuffRebuildGraph --
 *	Called from Suff_AddSuffix via Lst_ForEach to search through the
 *	list of existing transformation rules and rebuild the transformation
 *	graph when it has been destroyed by Suff_ClearSuffixes. If the
 *	given rule is a transformation involving this suffix and another,
 *	existing suffix, the proper relationship is established between
 *	the two.
 *
 * Input:
 *	transformp	Transformation to test
 *	sp		Suffix to rebuild
 *
 * Results:
 *	Always 0.
 *
 * Side Effects:
 *	The appropriate links will be made between this suffix and
 *	others if transformation rules exist for it.
 *
 *-----------------------------------------------------------------------
 */
static int
SuffRebuildGraph(ClientData transformp, ClientData sp)
{
    GNode   	*transform = (GNode *) transformp;
    Suff    	*s = (Suff *) sp;
    char 	*cp;
    LstNode	ln;
    Suff  	*s2;
    SuffixCmpData sd;

    /*
     * First see if it is a transformation from this suffix.
     */
    cp = SuffStrIsPrefix(s->name, transform->name);
    if (cp != (char *)NULL) {
	ln = Lst_Find(sufflist, (ClientData)cp, SuffSuffHasNameP);
	if (ln != NILLNODE) {
	    /*
	     * Found target. Link in and return, since it can't be anything
	     * else.
	     */
	    s2 = (Suff *)Lst_Datum(ln);
	    SuffInsert(s2->children, s);
	    SuffInsert(s->parents, s2);
	    return(0);
	}
    }

    /*
     * Not from, maybe to?
     */
    sd.len = strlen(transform->name);
    sd.ename = transform->name + sd.len;
    cp = SuffSuffIsSuffix(s, &sd);
    if (cp != (char *)NULL) {
	/*
	 * Null-terminate the source suffix in order to find it.
	 */
	cp[1] = '\0';
	ln = Lst_Find(sufflist, (ClientData)transform->name, SuffSuffHasNameP);
	/*
	 * Replace the start of the target suffix
	 */
	cp[1] = s->name[0];
	if (ln != NILLNODE) {
	    /*
	     * Found it -- establish the proper relationship
	     */
	    s2 = (Suff *)Lst_Datum(ln);
	    SuffInsert(s->children, s2);
	    SuffInsert(s2->parents, s);
	}
    }
    return(0);
}

/*-
 *-----------------------------------------------------------------------
 * SuffScanTargets --
 *	Called from Suff_AddSuffix via Lst_ForEach to search through the
 *	list of existing targets and find if any of the existing targets
 *	can be turned into a transformation rule.
 *
 * Results:
 *	1 if a new main target has been selected, 0 otherwise.
 *
 * Side Effects:
 *	If such a target is found and the target is the current main
 *	target, the main target is set to NULL and the next target
 *	examined (if that exists) becomes the main target.
 *
 *-----------------------------------------------------------------------
 */
static int
SuffScanTargets(ClientData targetp, ClientData gsp)
{
    GNode   	*target = (GNode *) targetp;
    GNodeSuff	*gs = (GNodeSuff *) gsp;
    Suff	*s, *t;
    char 	*ptr;

    if (*gs->gn == NILGNODE && gs->r && (target->type & OP_NOTARGET) == 0) {
	*gs->gn = target;
	Targ_SetMain(target);
	return 1;
    }

    if (target->type == OP_TRANSFORM)
	return 0;

    if ((ptr = strstr(target->name, gs->s->name)) == NULL ||
	ptr == target->name)
	return 0;

    if (SuffParseTransform(target->name, &s, &t)) {
	if (*gs->gn == target) {
	    gs->r = TRUE;
	    *gs->gn = NILGNODE;
	    Targ_SetMain(NILGNODE);
	}
	Lst_Destroy(target->children, NOFREE);
	target->children = Lst_Init(FALSE);
	target->type = OP_TRANSFORM;
	/*
	 * link the two together in the proper relationship and order
	 */
	if (DEBUG(SUFF)) {
	    printf("defining transformation from `%s' to `%s'\n",
		s->name, t->name);
	}
	SuffInsert(t->children, s);
	SuffInsert(s->parents, t);
    }
    return 0;
}

/*-
 *-----------------------------------------------------------------------
 * Suff_AddSuffix --
 *	Add the suffix in string to the end of the list of known suffixes.
 *	Should we restructure the suffix graph? Make doesn't...
 *
 * Input:
 *	str		the name of the suffix to add
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A GNode is created for the suffix and a Suff structure is created and
 *	added to the suffixes list unless the suffix was already known.
 *	The mainNode passed can be modified if a target mutated into a
 *	transform and that target happened to be the main target.
 *-----------------------------------------------------------------------
 */
void
Suff_AddSuffix(char *str, GNode **gn)
{
    Suff          *s;	    /* new suffix descriptor */
    LstNode 	  ln;
    GNodeSuff	  gs;

    ln = Lst_Find(sufflist, (ClientData)str, SuffSuffHasNameP);
    if (ln == NILLNODE) {
	s = emalloc(sizeof(Suff));

	s->name =   	estrdup(str);
	s->nameLen = 	strlen (s->name);
	s->searchPath = Lst_Init(FALSE);
	s->children = 	Lst_Init(FALSE);
	s->parents = 	Lst_Init(FALSE);
	s->ref = 	Lst_Init(FALSE);
	s->sNum =   	sNum++;
	s->flags =  	0;
	s->refCount =	1;

	(void)Lst_AtEnd (sufflist, (ClientData)s);
	/*
	 * We also look at our existing targets list to see if adding
	 * this suffix will make one of our current targets mutate into
	 * a suffix rule. This is ugly, but other makes treat all targets
	 * that start with a . as suffix rules.
	 */
	gs.gn = gn;
	gs.s  = s;
	gs.r  = FALSE;
	Lst_ForEach(Targ_List(), SuffScanTargets, (ClientData) &gs);
	/*
	 * Look for any existing transformations from or to this suffix.
	 * XXX: Only do this after a Suff_ClearSuffixes?
	 */
	Lst_ForEach(transforms, SuffRebuildGraph, (ClientData) s);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Suff_GetPath --
 *	Return the search path for the given suffix, if it's defined.
 *
 * Results:
 *	The searchPath for the desired suffix or NILLST if the suffix isn't
 *	defined.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Lst
Suff_GetPath(char *sname)
{
    LstNode   	  ln;
    Suff    	  *s;

    ln = Lst_Find(sufflist, (ClientData)sname, SuffSuffHasNameP);
    if (ln == NILLNODE) {
	return (NILLST);
    } else {
	s = (Suff *) Lst_Datum(ln);
	return (s->searchPath);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Suff_DoPaths --
 *	Extend the search paths for all suffixes to include the default
 *	search path.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The searchPath field of all the suffixes is extended by the
 *	directories in dirSearchPath. If paths were specified for the
 *	".h" suffix, the directories are stuffed into a global variable
 *	called ".INCLUDES" with each directory preceded by a -I. The same
 *	is done for the ".a" suffix, except the variable is called
 *	".LIBS" and the flag is -L.
 *-----------------------------------------------------------------------
 */
void
Suff_DoPaths(void)
{
    Suff	   	*s;
    LstNode  		ln;
    char		*ptr;
    Lst	    	    	inIncludes; /* Cumulative .INCLUDES path */
    Lst	    	    	inLibs;	    /* Cumulative .LIBS path */

    if (Lst_Open(sufflist) == FAILURE) {
	return;
    }

    inIncludes = Lst_Init(FALSE);
    inLibs = Lst_Init(FALSE);

    while ((ln = Lst_Next(sufflist)) != NILLNODE) {
	s = (Suff *) Lst_Datum(ln);
	if (!Lst_IsEmpty (s->searchPath)) {
#ifdef INCLUDES
	    if (s->flags & SUFF_INCLUDE) {
		Dir_Concat(inIncludes, s->searchPath);
	    }
#endif /* INCLUDES */
#ifdef LIBRARIES
	    if (s->flags & SUFF_LIBRARY) {
		Dir_Concat(inLibs, s->searchPath);
	    }
#endif /* LIBRARIES */
	    Dir_Concat(s->searchPath, dirSearchPath);
	} else {
	    Lst_Destroy(s->searchPath, Dir_Destroy);
	    s->searchPath = Lst_Duplicate(dirSearchPath, Dir_CopyDir);
	}
    }

    Var_Set(".INCLUDES", ptr = Dir_MakeFlags("-I", inIncludes), VAR_GLOBAL, 0);
    free(ptr);
    Var_Set(".LIBS", ptr = Dir_MakeFlags("-L", inLibs), VAR_GLOBAL, 0);
    free(ptr);

    Lst_Destroy(inIncludes, Dir_Destroy);
    Lst_Destroy(inLibs, Dir_Destroy);

    Lst_Close(sufflist);
}

/*-
 *-----------------------------------------------------------------------
 * Suff_AddInclude --
 *	Add the given suffix as a type of file which gets included.
 *	Called from the parse module when a .INCLUDES line is parsed.
 *	The suffix must have already been defined.
 *
 * Input:
 *	sname		Name of the suffix to mark
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The SUFF_INCLUDE bit is set in the suffix's flags field
 *
 *-----------------------------------------------------------------------
 */
void
Suff_AddInclude(char *sname)
{
    LstNode	  ln;
    Suff	  *s;

    ln = Lst_Find(sufflist, (ClientData)sname, SuffSuffHasNameP);
    if (ln != NILLNODE) {
	s = (Suff *) Lst_Datum(ln);
	s->flags |= SUFF_INCLUDE;
    }
}

/*-
 *-----------------------------------------------------------------------
 * Suff_AddLib --
 *	Add the given suffix as a type of file which is a library.
 *	Called from the parse module when parsing a .LIBS line. The
 *	suffix must have been defined via .SUFFIXES before this is
 *	called.
 *
 * Input:
 *	sname		Name of the suffix to mark
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The SUFF_LIBRARY bit is set in the suffix's flags field
 *
 *-----------------------------------------------------------------------
 */
void
Suff_AddLib(char *sname)
{
    LstNode	  ln;
    Suff	  *s;

    ln = Lst_Find(sufflist, (ClientData)sname, SuffSuffHasNameP);
    if (ln != NILLNODE) {
	s = (Suff *) Lst_Datum(ln);
	s->flags |= SUFF_LIBRARY;
    }
}

 	  /********** Implicit Source Search Functions *********/

/*-
 *-----------------------------------------------------------------------
 * SuffAddSrc  --
 *	Add a suffix as a Src structure to the given list with its parent
 *	being the given Src structure. If the suffix is the null suffix,
 *	the prefix is used unaltered as the file name in the Src structure.
 *
 * Input:
 *	sp		suffix for which to create a Src structure
 *	lsp		list and parent for the new Src
 *
 * Results:
 *	always returns 0
 *
 * Side Effects:
 *	A Src structure is created and tacked onto the end of the list
 *-----------------------------------------------------------------------
 */
static int
SuffAddSrc(ClientData sp, ClientData lsp)
{
    Suff	*s = (Suff *) sp;
    LstSrc      *ls = (LstSrc *) lsp;
    Src         *s2;	    /* new Src structure */
    Src    	*targ; 	    /* Target structure */

    targ = ls->s;

    if ((s->flags & SUFF_NULL) && (*s->name != '\0')) {
	/*
	 * If the suffix has been marked as the NULL suffix, also create a Src
	 * structure for a file with no suffix attached. Two birds, and all
	 * that...
	 */
	s2 = emalloc(sizeof(Src));
	s2->file =  	estrdup(targ->pref);
	s2->pref =  	targ->pref;
	s2->parent = 	targ;
	s2->node =  	NILGNODE;
	s2->suff =  	s;
	s->refCount++;
	s2->children =	0;
	targ->children += 1;
	(void)Lst_AtEnd (ls->l, (ClientData)s2);
#ifdef DEBUG_SRC
	s2->cp = Lst_Init(FALSE);
	Lst_AtEnd(targ->cp, (ClientData) s2);
	printf("1 add %x %x to %x:", targ, s2, ls->l);
	Lst_ForEach(ls->l, PrintAddr, (ClientData) 0);
	printf("\n");
#endif
    }
    s2 = emalloc(sizeof(Src));
    s2->file = 	    str_concat(targ->pref, s->name, 0);
    s2->pref =	    targ->pref;
    s2->parent =    targ;
    s2->node = 	    NILGNODE;
    s2->suff = 	    s;
    s->refCount++;
    s2->children =  0;
    targ->children += 1;
    (void)Lst_AtEnd (ls->l, (ClientData)s2);
#ifdef DEBUG_SRC
    s2->cp = Lst_Init(FALSE);
    Lst_AtEnd(targ->cp, (ClientData) s2);
    printf("2 add %x %x to %x:", targ, s2, ls->l);
    Lst_ForEach(ls->l, PrintAddr, (ClientData) 0);
    printf("\n");
#endif

    return(0);
}

/*-
 *-----------------------------------------------------------------------
 * SuffAddLevel  --
 *	Add all the children of targ as Src structures to the given list
 *
 * Input:
 *	l		list to which to add the new level
 *	targ		Src structure to use as the parent
 *
 * Results:
 *	None
 *
 * Side Effects:
 * 	Lots of structures are created and added to the list
 *-----------------------------------------------------------------------
 */
static void
SuffAddLevel(Lst l, Src *targ)
{
    LstSrc         ls;

    ls.s = targ;
    ls.l = l;

    Lst_ForEach(targ->suff->children, SuffAddSrc, (ClientData)&ls);
}

/*-
 *----------------------------------------------------------------------
 * SuffRemoveSrc --
 *	Free all src structures in list that don't have a reference count
 *
 * Results:
 *	Ture if an src was removed
 *
 * Side Effects:
 *	The memory is free'd.
 *----------------------------------------------------------------------
 */
static int
SuffRemoveSrc(Lst l)
{
    LstNode ln;
    Src *s;
    int t = 0;

    if (Lst_Open(l) == FAILURE) {
	return 0;
    }
#ifdef DEBUG_SRC
    printf("cleaning %lx: ", (unsigned long) l);
    Lst_ForEach(l, PrintAddr, (ClientData) 0);
    printf("\n");
#endif


    while ((ln = Lst_Next(l)) != NILLNODE) {
	s = (Src *) Lst_Datum(ln);
	if (s->children == 0) {
	    free ((Address)s->file);
	    if (!s->parent)
		free((Address)s->pref);
	    else {
#ifdef DEBUG_SRC
		LstNode ln = Lst_Member(s->parent->cp, (ClientData)s);
		if (ln != NILLNODE)
		    Lst_Remove(s->parent->cp, ln);
#endif
		--s->parent->children;
	    }
#ifdef DEBUG_SRC
	    printf("free: [l=%x] p=%x %d\n", l, s, s->children);
	    Lst_Destroy(s->cp, NOFREE);
#endif
	    Lst_Remove(l, ln);
	    free ((Address)s);
	    t |= 1;
	    Lst_Close(l);
	    return TRUE;
	}
#ifdef DEBUG_SRC
	else {
	    printf("keep: [l=%x] p=%x %d: ", l, s, s->children);
	    Lst_ForEach(s->cp, PrintAddr, (ClientData) 0);
	    printf("\n");
	}
#endif
    }

    Lst_Close(l);

    return t;
}

/*-
 *-----------------------------------------------------------------------
 * SuffFindThem --
 *	Find the first existing file/target in the list srcs
 *
 * Input:
 *	srcs		list of Src structures to search through
 *
 * Results:
 *	The lowest structure in the chain of transformations
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static Src *
SuffFindThem(Lst srcs, Lst slst)
{
    Src            *s;		/* current Src */
    Src		   *rs;		/* returned Src */
    char	   *ptr;

    rs = (Src *) NULL;

    while (!Lst_IsEmpty (srcs)) {
	s = (Src *) Lst_DeQueue(srcs);

	if (DEBUG(SUFF)) {
	    printf ("\ttrying %s...", s->file);
	}

	/*
	 * A file is considered to exist if either a node exists in the
	 * graph for it or the file actually exists.
	 */
	if (Targ_FindNode(s->file, TARG_NOCREATE) != NILGNODE) {
#ifdef DEBUG_SRC
	    printf("remove %x from %x\n", s, srcs);
#endif
	    rs = s;
	    break;
	}

	if ((ptr = Dir_FindFile(s->file, s->suff->searchPath)) != NULL) {
	    rs = s;
#ifdef DEBUG_SRC
	    printf("remove %x from %x\n", s, srcs);
#endif
	    free(ptr);
	    break;
	}

	if (DEBUG(SUFF)) {
	    printf ("not there\n");
	}

	SuffAddLevel(srcs, s);
	Lst_AtEnd(slst, (ClientData) s);
    }

    if (DEBUG(SUFF) && rs) {
	printf ("got it\n");
    }
    return (rs);
}

/*-
 *-----------------------------------------------------------------------
 * SuffFindCmds --
 *	See if any of the children of the target in the Src structure is
 *	one from which the target can be transformed. If there is one,
 *	a Src structure is put together for it and returned.
 *
 * Input:
 *	targ		Src structure to play with
 *
 * Results:
 *	The Src structure of the "winning" child, or NIL if no such beast.
 *
 * Side Effects:
 *	A Src structure may be allocated.
 *
 *-----------------------------------------------------------------------
 */
static Src *
SuffFindCmds(Src *targ, Lst slst)
{
    LstNode 	  	ln; 	/* General-purpose list node */
    GNode		*t, 	/* Target GNode */
	    	  	*s; 	/* Source GNode */
    int	    	  	prefLen;/* The length of the defined prefix */
    Suff    	  	*suff;	/* Suffix on matching beastie */
    Src	    	  	*ret;	/* Return value */
    char    	  	*cp;

    t = targ->node;
    (void) Lst_Open(t->children);
    prefLen = strlen (targ->pref);

    for (;;) {
	ln = Lst_Next(t->children);
	if (ln == NILLNODE) {
	    Lst_Close(t->children);
	    return NULL;
	}
	s = (GNode *)Lst_Datum (ln);

	cp = strrchr (s->name, '/');
	if (cp == (char *)NULL) {
	    cp = s->name;
	} else {
	    cp++;
	}
	if (strncmp (cp, targ->pref, prefLen) != 0)
	    continue;
	/*
	 * The node matches the prefix ok, see if it has a known
	 * suffix.
	 */
	ln = Lst_Find(sufflist, (ClientData)&cp[prefLen],
		       SuffSuffHasNameP);
	if (ln == NILLNODE)
	    continue;
	/*
	 * It even has a known suffix, see if there's a transformation
	 * defined between the node's suffix and the target's suffix.
	 *
	 * XXX: Handle multi-stage transformations here, too.
	 */
	suff = (Suff *)Lst_Datum (ln);

	if (Lst_Member(suff->parents, (ClientData)targ->suff) != NILLNODE)
	    break;
    }

    /*
     * Hot Damn! Create a new Src structure to describe
     * this transformation (making sure to duplicate the
     * source node's name so Suff_FindDeps can free it
     * again (ick)), and return the new structure.
     */
    ret = emalloc(sizeof(Src));
    ret->file = estrdup(s->name);
    ret->pref = targ->pref;
    ret->suff = suff;
    suff->refCount++;
    ret->parent = targ;
    ret->node = s;
    ret->children = 0;
    targ->children += 1;
#ifdef DEBUG_SRC
    ret->cp = Lst_Init(FALSE);
    printf("3 add %x %x\n", targ, ret);
    Lst_AtEnd(targ->cp, (ClientData) ret);
#endif
    Lst_AtEnd(slst, (ClientData) ret);
    if (DEBUG(SUFF)) {
	printf ("\tusing existing source %s\n", s->name);
    }
    return (ret);
}

/*-
 *-----------------------------------------------------------------------
 * SuffExpandChildren --
 *	Expand the names of any children of a given node that contain
 *	variable invocations or file wildcards into actual targets.
 *
 * Input:
 *	prevLN		Child to examine
 *	pgn		Parent node being processed
 *
 * Results:
 *	=== 0 (continue)
 *
 * Side Effects:
 *	The expanded node is removed from the parent's list of children,
 *	and the parent's unmade counter is decremented, but other nodes
 * 	may be added.
 *
 *-----------------------------------------------------------------------
 */
static int
SuffExpandChildren(LstNode prevLN, GNode *pgn)
{
    GNode   	*cgn = (GNode *) Lst_Datum(prevLN);
    GNode	*gn;	    /* New source 8) */
    char	*cp;	    /* Expanded value */

    /*
     * First do variable expansion -- this takes precedence over
     * wildcard expansion. If the result contains wildcards, they'll be gotten
     * to later since the resulting words are tacked on to the end of
     * the children list.
     */
    if (strchr(cgn->name, '$') != (char *)NULL) {
	if (DEBUG(SUFF)) {
	    printf("Expanding \"%s\"...", cgn->name);
	}
	cp = Var_Subst(NULL, cgn->name, pgn, TRUE);

	if (cp != (char *)NULL) {
	    Lst	    members = Lst_Init(FALSE);

	    if (cgn->type & OP_ARCHV) {
		/*
		 * Node was an archive(member) target, so we want to call
		 * on the Arch module to find the nodes for us, expanding
		 * variables in the parent's context.
		 */
		/* char	*sacrifice = cp; */

		/* (void)Arch_ParseArchive(&sacrifice, members, pgn); */
		fprintf(stderr, "OP_ARCHV is deprecated\n");
		exit(1);
	    } else {
		/*
		 * Break the result into a vector of strings whose nodes
		 * we can find, then add those nodes to the members list.
		 * Unfortunately, we can't use brk_string b/c it
		 * doesn't understand about variable specifications with
		 * spaces in them...
		 */
		char	    *start;
		char	    *initcp = cp;   /* For freeing... */

		for (start = cp; *start == ' ' || *start == '\t'; start++)
		    continue;
		for (cp = start; *cp != '\0'; cp++) {
		    if (*cp == ' ' || *cp == '\t') {
			/*
			 * White-space -- terminate element, find the node,
			 * add it, skip any further spaces.
			 */
			*cp++ = '\0';
			gn = Targ_FindNode(start, TARG_CREATE);
			(void)Lst_AtEnd(members, (ClientData)gn);
			while (*cp == ' ' || *cp == '\t') {
			    cp++;
			}
			/*
			 * Adjust cp for increment at start of loop, but
			 * set start to first non-space.
			 */
			start = cp--;
		    } else if (*cp == '$') {
			/*
			 * Start of a variable spec -- contact variable module
			 * to find the end so we can skip over it.
			 */
			char	*junk;
			int 	len;
			Boolean	doFree;

			junk = Var_Parse(cp, pgn, TRUE, &len, &doFree);
			if (junk != var_Error) {
			    cp += len - 1;
			}

			if (doFree) {
			    free(junk);
			}
		    } else if (*cp == '\\' && *cp != '\0') {
			/*
			 * Escaped something -- skip over it
			 */
			cp++;
		    }
		}

		if (cp != start) {
		    /*
		     * Stuff left over -- add it to the list too
		     */
		    gn = Targ_FindNode(start, TARG_CREATE);
		    (void)Lst_AtEnd(members, (ClientData)gn);
		}
		/*
		 * Point cp back at the beginning again so the variable value
		 * can be freed.
		 */
		cp = initcp;
	    }
	    /*
	     * Add all elements of the members list to the parent node.
	     */
	    while(!Lst_IsEmpty(members)) {
		gn = (GNode *)Lst_DeQueue(members);

		if (DEBUG(SUFF)) {
		    printf("%s...", gn->name);
		}
		if (Lst_Member(pgn->children, (ClientData)gn) == NILLNODE) {
		    (void)Lst_Append(pgn->children, prevLN, (ClientData)gn);
		    prevLN = Lst_Succ(prevLN);
		    (void)Lst_AtEnd(gn->parents, (ClientData)pgn);
		    pgn->unmade++;
		}
	    }
	    Lst_Destroy(members, NOFREE);
	    /*
	     * Free the result
	     */
	    free((char *)cp);
	}
	/*
	 * Now the source is expanded, remove it from the list of children to
	 * keep it from being processed.
	 */
	if (DEBUG(SUFF)) {
	    printf("\n");
	}
	return(1);
    } else if (Dir_HasWildcards(cgn->name)) {
	Lst 	explist;    /* List of expansions */

	/*
	 * Expand the word along the chosen path
	 */
	explist = Lst_Init(FALSE);
	Dir_Expand(cgn->name, Suff_FindPath(cgn), explist);

	while (!Lst_IsEmpty(explist)) {
	    /*
	     * Fetch next expansion off the list and find its GNode
	     */
	    cp = (char *)Lst_DeQueue(explist);

	    if (DEBUG(SUFF)) {
		printf("%s...", cp);
	    }
	    gn = Targ_FindNode(cp, TARG_CREATE);

	    /*
	     * If gn isn't already a child of the parent, make it so and
	     * up the parent's count of unmade children.
	     */
	    if (Lst_Member(pgn->children, (ClientData)gn) == NILLNODE) {
		(void)Lst_Append(pgn->children, prevLN, (ClientData)gn);
		prevLN = Lst_Succ(prevLN);
		(void)Lst_AtEnd(gn->parents, (ClientData)pgn);
		pgn->unmade++;
	    }
	}

	/*
	 * Nuke what's left of the list
	 */
	Lst_Destroy(explist, NOFREE);

	/*
	 * Now the source is expanded, remove it from the list of children to
	 * keep it from being processed.
	 */
	if (DEBUG(SUFF)) {
	    printf("\n");
	}
	return(1);
    }

    return(0);
}

/*-
 *-----------------------------------------------------------------------
 * Suff_FindPath --
 *	Find a path along which to expand the node.
 *
 *	If the word has a known suffix, use that path.
 *	If it has no known suffix, use the default system search path.
 *
 * Input:
 *	gn		Node being examined
 *
 * Results:
 *	The appropriate path to search for the GNode.
 *
 * Side Effects:
 *	XXX: We could set the suffix here so that we don't have to scan
 *	again.
 *
 *-----------------------------------------------------------------------
 */
Lst
Suff_FindPath(GNode* gn)
{
    Suff *suff = gn->suffix;

    if (suff == NULL) {
	SuffixCmpData sd;   /* Search string data */
	LstNode ln;
	sd.len = strlen(gn->name);
	sd.ename = gn->name + sd.len;
	ln = Lst_Find(sufflist, (ClientData)&sd, SuffSuffIsSuffixP);

	if (DEBUG(SUFF)) {
	    printf("Wildcard expanding \"%s\"...", gn->name);
	}
	if (ln != NILLNODE)
	    suff = (Suff *)Lst_Datum(ln);
	/* XXX: Here we can save the suffix so we don't have to do this again */
    }

    if (suff != NULL) {
	if (DEBUG(SUFF)) {
	    printf("suffix is \"%s\"...", suff->name);
	}
	return suff->searchPath;
    } else {
	/*
	 * Use default search path
	 */
	return dirSearchPath;
    }
}

/*-
 *-----------------------------------------------------------------------
 * SuffApplyTransform --
 *	Apply a transformation rule, given the source and target nodes
 *	and suffixes.
 *
 * Input:
 *	tGn		Target node
 *	sGn		Source node
 *	t		Target suffix
 *	s		Source suffix
 *
 * Results:
 *	TRUE if successful, FALSE if not.
 *
 * Side Effects:
 *	The source and target are linked and the commands from the
 *	transformation are added to the target node's commands list.
 *	All attributes but OP_DEPMASK and OP_TRANSFORM are applied
 *	to the target. The target also inherits all the sources for
 *	the transformation rule.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
SuffApplyTransform(GNode *tGn, GNode *sGn, Suff *t, Suff *s)
{
    LstNode 	ln, nln;    /* General node */
    char    	*tname;	    /* Name of transformation rule */
    GNode   	*gn;	    /* Node for same */

    /*
     * Form the proper links between the target and source.
     */
    (void)Lst_AtEnd(tGn->children, (ClientData)sGn);
    (void)Lst_AtEnd(sGn->parents, (ClientData)tGn);
    tGn->unmade += 1;

    /*
     * Locate the transformation rule itself
     */
    tname = str_concat(s->name, t->name, 0);
    ln = Lst_Find(transforms, (ClientData)tname, SuffGNHasNameP);
    free(tname);

    if (ln == NILLNODE) {
	/*
	 * Not really such a transformation rule (can happen when we're
	 * called to link an OP_MEMBER and OP_ARCHV node), so return
	 * FALSE.
	 */
	return(FALSE);
    }

    gn = (GNode *)Lst_Datum(ln);

    if (DEBUG(SUFF)) {
	printf("\tapplying %s -> %s to \"%s\"\n", s->name, t->name, tGn->name);
    }

    /*
     * Record last child for expansion purposes
     */
    ln = Lst_Last(tGn->children);

    /*
     * Pass the buck to Make_HandleUse to apply the rule
     */
    (void)Make_HandleUse(gn, tGn);

    /*
     * Deal with wildcards and variables in any acquired sources
     */
    ln = Lst_Succ(ln);
    while (ln != NILLNODE) {
	if (SuffExpandChildren(ln, tGn)) {
	    nln = Lst_Succ(ln);
	    tGn->unmade--;
	    Lst_Remove(tGn->children, ln);
	    ln = nln;
	} else
	    ln = Lst_Succ(ln);
    }

    /*
     * Keep track of another parent to which this beast is transformed so
     * the .IMPSRC variable can be set correctly for the parent.
     */
    (void)Lst_AtEnd(sGn->iParents, (ClientData)tGn);

    return(TRUE);
}
/*-
 *-----------------------------------------------------------------------
 * SuffFindNormalDeps --
 *	Locate implicit dependencies for regular targets.
 *
 * Input:
 *	gn		Node for which to find sources
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Same as Suff_FindDeps...
 *
 *-----------------------------------------------------------------------
 */
static void
SuffFindNormalDeps(GNode *gn, Lst slst)
{
    char    	*eoname;    /* End of name */
    char    	*sopref;    /* Start of prefix */
    LstNode 	ln, nln;    /* Next suffix node to check */
    Lst	    	srcs;	    /* List of sources at which to look */
    Lst	    	targs;	    /* List of targets to which things can be
			     * transformed. They all have the same file,
			     * but different suff and pref fields */
    Src	    	*bottom;    /* Start of found transformation path */
    Src 	*src;	    /* General Src pointer */
    char    	*pref;	    /* Prefix to use */
    Src	    	*targ;	    /* General Src target pointer */
    SuffixCmpData sd;	    /* Search string data */


    sd.len = strlen(gn->name);
    sd.ename = eoname = gn->name + sd.len;

    sopref = gn->name;

    /*
     * Begin at the beginning...
     */
    ln = Lst_First(sufflist);
    srcs = Lst_Init(FALSE);
    targs = Lst_Init(FALSE);

    /*
     * We're caught in a catch-22 here. On the one hand, we want to use any
     * transformation implied by the target's sources, but we can't examine
     * the sources until we've expanded any variables/wildcards they may hold,
     * and we can't do that until we've set up the target's local variables
     * and we can't do that until we know what the proper suffix for the
     * target is (in case there are two suffixes one of which is a suffix of
     * the other) and we can't know that until we've found its implied
     * source, which we may not want to use if there's an existing source
     * that implies a different transformation.
     *
     * In an attempt to get around this, which may not work all the time,
     * but should work most of the time, we look for implied sources first,
     * checking transformations to all possible suffixes of the target,
     * use what we find to set the target's local variables, expand the
     * children, then look for any overriding transformations they imply.
     * Should we find one, we discard the one we found before.
     */

    while (ln != NILLNODE) {
	/*
	 * Look for next possible suffix...
	 */
	ln = Lst_FindFrom(sufflist, ln, &sd, SuffSuffIsSuffixP);

	if (ln != NILLNODE) {
	    int	    prefLen;	    /* Length of the prefix */

	    /*
	     * Allocate a Src structure to which things can be transformed
	     */
	    targ = emalloc(sizeof(Src));
	    targ->file = estrdup(gn->name);
	    targ->suff = (Suff *)Lst_Datum(ln);
	    targ->suff->refCount++;
	    targ->node = gn;
	    targ->parent = (Src *)NULL;
	    targ->children = 0;
#ifdef DEBUG_SRC
	    targ->cp = Lst_Init(FALSE);
#endif

	    /*
	     * Allocate room for the prefix, whose end is found by subtracting
	     * the length of the suffix from the end of the name.
	     */
	    prefLen = (eoname - targ->suff->nameLen) - sopref;
	    targ->pref = emalloc(prefLen + 1);
	    memcpy(targ->pref, sopref, prefLen);
	    targ->pref[prefLen] = '\0';

	    /*
	     * Add nodes from which the target can be made
	     */
	    SuffAddLevel(srcs, targ);

	    /*
	     * Record the target so we can nuke it
	     */
	    (void)Lst_AtEnd(targs, (ClientData)targ);

	    /*
	     * Search from this suffix's successor...
	     */
	    ln = Lst_Succ(ln);
	}
    }

    /*
     * Handle target of unknown suffix...
     */
    if (Lst_IsEmpty(targs) && suffNull != NULL) {
	if (DEBUG(SUFF)) {
	    printf("\tNo known suffix on %s. Using .NULL suffix\n", gn->name);
	}

	targ = emalloc(sizeof(Src));
	targ->file = estrdup(gn->name);
	targ->suff = suffNull;
	targ->suff->refCount++;
	targ->node = gn;
	targ->parent = (Src *)NULL;
	targ->children = 0;
	targ->pref = estrdup(sopref);
#ifdef DEBUG_SRC
	targ->cp = Lst_Init(FALSE);
#endif

	/*
	 * Only use the default suffix rules if we don't have commands
	 * defined for this gnode; traditional make programs used to
	 * not define suffix rules if the gnode had children but we
	 * don't do this anymore.
	 */
	if (Lst_IsEmpty(gn->commands))
	    SuffAddLevel(srcs, targ);
	else {
	    if (DEBUG(SUFF))
		printf("not ");
	}

	if (DEBUG(SUFF))
	    printf("adding suffix rules\n");

	(void)Lst_AtEnd(targs, (ClientData)targ);
    }

    /*
     * Using the list of possible sources built up from the target suffix(es),
     * try and find an existing file/target that matches.
     */
    bottom = SuffFindThem(srcs, slst);

    if (bottom == (Src *)NULL) {
	/*
	 * No known transformations -- use the first suffix found for setting
	 * the local variables.
	 */
	if (!Lst_IsEmpty(targs)) {
	    targ = (Src *)Lst_Datum(Lst_First(targs));
	} else {
	    targ = (Src *)NULL;
	}
    } else {
	/*
	 * Work up the transformation path to find the suffix of the
	 * target to which the transformation was made.
	 */
	for (targ = bottom; targ->parent != NULL; targ = targ->parent)
	    continue;
    }

    Var_Set(TARGET, gn->path ? gn->path : gn->name, gn, 0);

    pref = (targ != NULL) ? targ->pref : gn->name;
    Var_Set(PREFIX, pref, gn, 0);

    /*
     * Now we've got the important local variables set, expand any sources
     * that still contain variables or wildcards in their names.
     */
    ln = Lst_First(gn->children);
    while (ln != NILLNODE) {
	if (SuffExpandChildren(ln, gn)) {
	    nln = Lst_Succ(ln);
	    gn->unmade--;
	    Lst_Remove(gn->children, ln);
	    ln = nln;
	} else
	    ln = Lst_Succ(ln);
    }

    if (targ == NULL) {
	if (DEBUG(SUFF)) {
	    printf("\tNo valid suffix on %s\n", gn->name);
	}

sfnd_abort:
	/*
	 * Deal with finding the thing on the default search path. We
	 * always do that, not only if the node is only a source (not
	 * on the lhs of a dependency operator or [XXX] it has neither
	 * children or commands) as the old pmake did.
	 */
	if ((gn->type & (OP_PHONY|OP_NOPATH)) == 0) {
	    free(gn->path);
	    gn->path = Dir_FindFile(gn->name,
				    (targ == NULL ? dirSearchPath :
				     targ->suff->searchPath));
	    if (gn->path != NULL) {
		char *ptr;
		Var_Set(TARGET, gn->path, gn, 0);

		if (targ != NULL) {
		    /*
		     * Suffix known for the thing -- trim the suffix off
		     * the path to form the proper .PREFIX variable.
		     */
		    int     savep = strlen(gn->path) - targ->suff->nameLen;
		    char    savec;

		    if (gn->suffix)
			gn->suffix->refCount--;
		    gn->suffix = targ->suff;
		    gn->suffix->refCount++;

		    savec = gn->path[savep];
		    gn->path[savep] = '\0';

		    if ((ptr = strrchr(gn->path, '/')) != NULL)
			ptr++;
		    else
			ptr = gn->path;

		    Var_Set(PREFIX, ptr, gn, 0);

		    gn->path[savep] = savec;
		} else {
		    /*
		     * The .PREFIX gets the full path if the target has
		     * no known suffix.
		     */
		    if (gn->suffix)
			gn->suffix->refCount--;
		    gn->suffix = NULL;

		    if ((ptr = strrchr(gn->path, '/')) != NULL)
			ptr++;
		    else
			ptr = gn->path;

		    Var_Set(PREFIX, ptr, gn, 0);
		}
	    }
	}

	goto sfnd_return;
    }

    /*
     * If the suffix indicates that the target is a library, mark that in
     * the node's type field.
     */
    if (targ->suff->flags & SUFF_LIBRARY) {
	gn->type |= OP_LIB;
    }

    /*
     * Check for overriding transformation rule implied by sources
     */
    if (!Lst_IsEmpty(gn->children)) {
	src = SuffFindCmds(targ, slst);

	if (src != (Src *)NULL) {
	    /*
	     * Free up all the Src structures in the transformation path
	     * up to, but not including, the parent node.
	     */
	    while (bottom && bottom->parent != NULL) {
		if (Lst_Member(slst, (ClientData) bottom) == NILLNODE) {
		    Lst_AtEnd(slst, (ClientData) bottom);
		}
		bottom = bottom->parent;
	    }
	    bottom = src;
	}
    }

    if (bottom == NULL) {
	/*
	 * No idea from where it can come -- return now.
	 */
	goto sfnd_abort;
    }

    /*
     * We now have a list of Src structures headed by 'bottom' and linked via
     * their 'parent' pointers. What we do next is create links between
     * source and target nodes (which may or may not have been created)
     * and set the necessary local variables in each target. The
     * commands for each target are set from the commands of the
     * transformation rule used to get from the src suffix to the targ
     * suffix. Note that this causes the commands list of the original
     * node, gn, to be replaced by the commands of the final
     * transformation rule. Also, the unmade field of gn is incremented.
     * Etc.
     */
    if (bottom->node == NILGNODE) {
	bottom->node = Targ_FindNode(bottom->file, TARG_CREATE);
    }

    for (src = bottom; src->parent != (Src *)NULL; src = src->parent) {
	targ = src->parent;

	if (src->node->suffix)
	    src->node->suffix->refCount--;
	src->node->suffix = src->suff;
	src->node->suffix->refCount++;

	if (targ->node == NILGNODE) {
	    targ->node = Targ_FindNode(targ->file, TARG_CREATE);
	}

	SuffApplyTransform(targ->node, src->node,
			   targ->suff, src->suff);

	if (targ->node != gn) {
	    /*
	     * Finish off the dependency-search process for any nodes
	     * between bottom and gn (no point in questing around the
	     * filesystem for their implicit source when it's already
	     * known). Note that the node can't have any sources that
	     * need expanding, since SuffFindThem will stop on an existing
	     * node, so all we need to do is set the standard and System V
	     * variables.
	     */
	    targ->node->type |= OP_DEPS_FOUND;

	    Var_Set(PREFIX, targ->pref, targ->node, 0);

	    Var_Set(TARGET, targ->node->name, targ->node, 0);
	}
    }

    if (gn->suffix)
	gn->suffix->refCount--;
    gn->suffix = src->suff;
    gn->suffix->refCount++;

    /*
     * Nuke the transformation path and the Src structures left over in the
     * two lists.
     */
sfnd_return:
    if (bottom)
	if (Lst_Member(slst, (ClientData) bottom) == NILLNODE)
	    Lst_AtEnd(slst, (ClientData) bottom);

    while (SuffRemoveSrc(srcs) || SuffRemoveSrc(targs))
	continue;

    Lst_Concat(slst, srcs, LST_CONCLINK);
    Lst_Concat(slst, targs, LST_CONCLINK);
}


/*-
 *-----------------------------------------------------------------------
 * Suff_FindDeps  --
 *	Find implicit sources for the target described by the graph node
 *	gn
 *
 * Results:
 *	Nothing.
 *
 * Side Effects:
 *	Nodes are added to the graph below the passed-in node. The nodes
 *	are marked to have their IMPSRC variable filled in. The
 *	PREFIX variable is set for the given node and all its
 *	implied children.
 *
 * Notes:
 *	The path found by this target is the shortest path in the
 *	transformation graph, which may pass through non-existent targets,
 *	to an existing target. The search continues on all paths from the
 *	root suffix until a file is found. I.e. if there's a path
 *	.o -> .c -> .l -> .l,v from the root and the .l,v file exists but
 *	the .c and .l files don't, the search will branch out in
 *	all directions from .o and again from all the nodes on the
 *	next level until the .l,v node is encountered.
 *
 *-----------------------------------------------------------------------
 */

void
Suff_FindDeps(GNode *gn)
{

    SuffFindDeps(gn, srclist);
    while (SuffRemoveSrc(srclist))
	continue;
}


/*
 * Input:
 *	gn		node we're dealing with
 *
 */
static void
SuffFindDeps(GNode *gn, Lst slst)
{
    if (gn->type & (OP_DEPS_FOUND|OP_PHONY)) {
	/*
	 * If dependencies already found, no need to do it again...
	 * If this is a .PHONY target, we do not apply suffix rules.
	 */
	return;
    } else {
	gn->type |= OP_DEPS_FOUND;
    }

    if (DEBUG(SUFF)) {
	printf ("SuffFindDeps (%s)\n", gn->name);
    }

    if (gn->type & OP_ARCHV) {
	/* SuffFindArchiveDeps(gn, slst); */
	fprintf(stderr, "OP_ARCHV is deprecated\n");
	exit(1);
    } else if (gn->type & OP_LIB) {
	/*
	 * If the node is a library, it is the arch module's job to find it
	 * and set the TARGET variable accordingly. We merely provide the
	 * search path, assuming all libraries end in ".a" (if the suffix
	 * hasn't been defined, there's nothing we can do for it, so we just
	 * set the TARGET variable to the node's name in order to give it a
	 * value).
	 */
	LstNode	ln;
	/*Suff	*s;*/

	ln = Lst_Find(sufflist, (ClientData)UNCONST(LIBSUFF),
	    SuffSuffHasNameP);
	if (gn->suffix)
	    gn->suffix->refCount--;
	if (ln != NILLNODE) {
	    /* gn->suffix = s = (Suff *) Lst_Datum(ln);
	    gn->suffix->refCount++;
	    Arch_FindLib(gn, s->searchPath);		*/
	    fprintf(stderr, "%s: %d: OP_ARCHV is deprecated\n", __FILE__, __LINE__);
	    exit(1);
	} else {
	    gn->suffix = NULL;
	    Var_Set(TARGET, gn->name, gn, 0);
	}
	/*
	 * Because a library (-lfoo) target doesn't follow the standard
	 * filesystem conventions, we don't set the regular variables for
	 * the thing. .PREFIX is simply made empty...
	 */
	Var_Set(PREFIX, "", gn, 0);
    } else {
	SuffFindNormalDeps(gn, slst);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Suff_SetNull --
 *	Define which suffix is the null suffix.
 *
 * Input:
 *	name		Name of null suffix
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	'suffNull' is altered.
 *
 * Notes:
 *	Need to handle the changing of the null suffix gracefully so the
 *	old transformation rules don't just go away.
 *
 *-----------------------------------------------------------------------
 */
void
Suff_SetNull(char *name)
{
    Suff    *s;
    LstNode ln;

    ln = Lst_Find(sufflist, (ClientData)name, SuffSuffHasNameP);
    if (ln != NILLNODE) {
	s = (Suff *)Lst_Datum(ln);
	if (suffNull != (Suff *)NULL) {
	    suffNull->flags &= ~SUFF_NULL;
	}
	s->flags |= SUFF_NULL;
	/*
	 * XXX: Here's where the transformation mangling would take place
	 */
	suffNull = s;
    } else {
	Parse_Error(PARSE_WARNING, "Desired null suffix %s not defined.",
		     name);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Suff_Init --
 *	Initialize suffixes module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Many
 *-----------------------------------------------------------------------
 */
void
Suff_Init(void)
{
    sufflist = Lst_Init(FALSE);
#ifdef CLEANUP
    suffClean = Lst_Init(FALSE);
#endif
    srclist = Lst_Init(FALSE);
    transforms = Lst_Init(FALSE);

    sNum = 0;
    /*
     * Create null suffix for single-suffix rules (POSIX). The thing doesn't
     * actually go on the suffix list or everyone will think that's its
     * suffix.
     */
    emptySuff = suffNull = emalloc(sizeof(Suff));

    suffNull->name =   	    estrdup("");
    suffNull->nameLen =     0;
    suffNull->searchPath =  Lst_Init(FALSE);
    Dir_Concat(suffNull->searchPath, dirSearchPath);
    suffNull->children =    Lst_Init(FALSE);
    suffNull->parents =	    Lst_Init(FALSE);
    suffNull->ref =	    Lst_Init(FALSE);
    suffNull->sNum =   	    sNum++;
    suffNull->flags =  	    SUFF_NULL;
    suffNull->refCount =    1;

}


/*-
 *----------------------------------------------------------------------
 * Suff_End --
 *	Cleanup the this module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The memory is free'd.
 *----------------------------------------------------------------------
 */

void
Suff_End(void)
{
#ifdef CLEANUP
    Lst_Destroy(sufflist, SuffFree);
    Lst_Destroy(suffClean, SuffFree);
    if (suffNull)
	SuffFree(suffNull);
    Lst_Destroy(srclist, NOFREE);
    Lst_Destroy(transforms, NOFREE);
#endif
}


/********************* DEBUGGING FUNCTIONS **********************/

static int SuffPrintName(ClientData s, ClientData dummy)
{
    printf ("%s ", ((Suff *) s)->name);
    return (dummy ? 0 : 0);
}

static int
SuffPrintSuff(ClientData sp, ClientData dummy)
{
    Suff    *s = (Suff *) sp;
    int	    flags;
    int	    flag;

    printf ("# `%s' [%d] ", s->name, s->refCount);

    flags = s->flags;
    if (flags) {
	fputs (" (", stdout);
	while (flags) {
	    flag = 1 << (ffs(flags) - 1);
	    flags &= ~flag;
	    switch (flag) {
		case SUFF_NULL:
		    printf ("NULL");
		    break;
		case SUFF_INCLUDE:
		    printf ("INCLUDE");
		    break;
		case SUFF_LIBRARY:
		    printf ("LIBRARY");
		    break;
	    }
	    fputc(flags ? '|' : ')', stdout);
	}
    }
    fputc ('\n', stdout);
    printf ("#\tTo: ");
    Lst_ForEach(s->parents, SuffPrintName, (ClientData)0);
    fputc ('\n', stdout);
    printf ("#\tFrom: ");
    Lst_ForEach(s->children, SuffPrintName, (ClientData)0);
    fputc ('\n', stdout);
    printf ("#\tSearch Path: ");
    Dir_PrintPath(s->searchPath);
    fputc ('\n', stdout);
    return (dummy ? 0 : 0);
}

static int
SuffPrintTrans(ClientData tp, ClientData dummy)
{
    GNode   *t = (GNode *) tp;

    printf ("%-16s: ", t->name);
    Targ_PrintType(t->type);
    fputc ('\n', stdout);
    Lst_ForEach(t->commands, Targ_PrintCmd, (ClientData)0);
    fputc ('\n', stdout);
    return(dummy ? 0 : 0);
}

void
Suff_PrintAll(void)
{
    printf ("#*** Suffixes:\n");
    Lst_ForEach(sufflist, SuffPrintSuff, (ClientData)0);

    printf ("#*** Transformations:\n");
    Lst_ForEach(transforms, SuffPrintTrans, (ClientData)0);
}
/* end suff.c */

/* begin targ.c */
/*	$NetBSD: targ.c,v 1.34 2005/02/16 15:11:53 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: targ.c,v 1.34 2005/02/16 15:11:53 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)targ.c	8.2 (Berkeley) 3/19/94";
#else
__RCSID("$NetBSD: targ.c,v 1.34 2005/02/16 15:11:53 christos Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * targ.c --
 *	Functions for maintaining the Lst allTargets. Target nodes are
 * kept in two structures: a Lst, maintained by the list library, and a
 * hash table, maintained by the hash library.
 *
 * Interface:
 *	Targ_Init 	    	Initialization procedure.
 *
 *	Targ_End 	    	Cleanup the module
 *
 *	Targ_List 	    	Return the list of all targets so far.
 *
 *	Targ_NewGN	    	Create a new GNode for the passed target
 *	    	  	    	(string). The node is *not* placed in the
 *	    	  	    	hash table, though all its fields are
 *	    	  	    	initialized.
 *
 *	Targ_FindNode	    	Find the node for a given target, creating
 *	    	  	    	and storing it if it doesn't exist and the
 *	    	  	    	flags are right (TARG_CREATE)
 *
 *	Targ_FindList	    	Given a list of names, find nodes for all
 *	    	  	    	of them. If a name doesn't exist and the
 *	    	  	    	TARG_NOCREATE flag was given, an error message
 *	    	  	    	is printed. Else, if a name doesn't exist,
 *	    	  	    	its node is created.
 *
 *	Targ_Ignore	    	Return TRUE if errors should be ignored when
 *	    	  	    	creating the given target.
 *
 *	Targ_Silent	    	Return TRUE if we should be silent when
 *	    	  	    	creating the given target.
 *
 *	Targ_Precious	    	Return TRUE if the target is precious and
 *	    	  	    	should not be removed if we are interrupted.
 *
 * Debugging:
 *	Targ_PrintGraph	    	Print out the entire graphm all variables
 *	    	  	    	and statistics for the directory cache. Should
 *	    	  	    	print something for suffixes, too, but...
 */

/* <<targ.c includes>> */

static Lst        allTargets;	/* the list of all targets found so far */
#ifdef CLEANUP
static Lst	  allGNs;	/* List of all the GNodes */
#endif
static Hash_Table targetsSame;	/* a hash table of same */

#define HTSIZE	191		/* initial size of hash table */

static int TargPrintOnlySrc(ClientData, ClientData);
static int TargPrintName(ClientData, ClientData);
static int TargPrintNode(ClientData, ClientData);
#ifdef CLEANUP
static void TargFreeGN(ClientData);
#endif
static int TargPropagateCohort(ClientData, ClientData);
static int TargPropagateNode(ClientData, ClientData);

/*-
 *-----------------------------------------------------------------------
 * Targ_Init --
 *	Initialize this module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The allTargets list and the targets hash table are initialized
 *-----------------------------------------------------------------------
 */
void
Targ_Init(void)
{
    allTargets = Lst_Init(FALSE);
    Hash_InitTable(&targetsSame, HTSIZE);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_End --
 *	Finalize this module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	All lists and gnodes are cleared
 *-----------------------------------------------------------------------
 */
void
Targ_End(void)
{
#ifdef CLEANUP
    Lst_Destroy(allTargets, NOFREE);
    if (allGNs)
	Lst_Destroy(allGNs, TargFreeGN);
    Hash_DeleteTable(&targetsSame);
#endif
}

/*-
 *-----------------------------------------------------------------------
 * Targ_List --
 *	Return the list of all targets
 *
 * Results:
 *	The list of all targets.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Lst
Targ_List(void)
{
    return allTargets;
}

/*-
 *-----------------------------------------------------------------------
 * Targ_NewGN  --
 *	Create and initialize a new graph node
 *
 * Input:
 *	name		the name to stick in the new node
 *
 * Results:
 *	An initialized graph node with the name field filled with a copy
 *	of the passed name
 *
 * Side Effects:
 *	The gnode is added to the list of all gnodes.
 *-----------------------------------------------------------------------
 */
GNode *
Targ_NewGN(const char *name)
{
    GNode *gn;

    gn = emalloc(sizeof(GNode));
    gn->name = estrdup(name);
    gn->uname = NULL;
    gn->path = NULL;
    if (name[0] == '-' && name[1] == 'l') {
	gn->type = OP_LIB;
    } else {
	gn->type = 0;
    }
    gn->unmade =    	0;
    gn->unmade_cohorts = 0;
    gn->centurion =    	NULL;
    gn->made = 	    	UNMADE;
    gn->flags = 	0;
    gn->order =		0;
    gn->mtime = gn->cmtime = 0;
    gn->iParents =  	Lst_Init(FALSE);
    gn->cohorts =   	Lst_Init(FALSE);
    gn->parents =   	Lst_Init(FALSE);
    gn->children =  	Lst_Init(FALSE);
    gn->successors = 	Lst_Init(FALSE);
    gn->preds =     	Lst_Init(FALSE);
    Hash_InitTable(&gn->context, 0);
    gn->commands =  	Lst_Init(FALSE);
    gn->suffix =	NULL;
    gn->lineno =	0;
    gn->fname = 	NULL;

#ifdef CLEANUP
    if (allGNs == NULL)
	allGNs = Lst_Init(FALSE);
    Lst_AtEnd(allGNs, (ClientData) gn);
#endif

    return (gn);
}

#ifdef CLEANUP
/*-
 *-----------------------------------------------------------------------
 * TargFreeGN  --
 *	Destroy a GNode
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	None.
 *-----------------------------------------------------------------------
 */
static void
TargFreeGN(ClientData gnp)
{
    GNode *gn = (GNode *) gnp;


    free(gn->name);
    if (gn->uname)
	free(gn->uname);
    if (gn->path)
	free(gn->path);
    if (gn->fname)
	free(gn->fname);

    Lst_Destroy(gn->iParents, NOFREE);
    Lst_Destroy(gn->cohorts, NOFREE);
    Lst_Destroy(gn->parents, NOFREE);
    Lst_Destroy(gn->children, NOFREE);
    Lst_Destroy(gn->successors, NOFREE);
    Lst_Destroy(gn->preds, NOFREE);
    Hash_DeleteTable(&gn->context);
    Lst_Destroy(gn->commands, NOFREE);
    free((Address)gn);
}
#endif


/*-
 *-----------------------------------------------------------------------
 * Targ_FindNode  --
 *	Find a node in the list using the given name for matching
 *
 * Input:
 *	name		the name to find
 *	flags		flags governing events when target not
 *			found
 *
 * Results:
 *	The node in the list if it was. If it wasn't, return NILGNODE of
 *	flags was TARG_NOCREATE or the newly created and initialized node
 *	if it was TARG_CREATE
 *
 * Side Effects:
 *	Sometimes a node is created and added to the list
 *-----------------------------------------------------------------------
 */
GNode *
Targ_FindNode(const char *name, int flags)
{
    GNode         *gn;	      /* node in that element */
    Hash_Entry	  *he;	      /* New or used hash entry for node */
    Boolean	  isNew;      /* Set TRUE if Hash_CreateEntry had to create */
			      /* an entry for the node */


    if (flags & TARG_CREATE) {
	he = Hash_CreateEntry(&targetsSame, name, &isNew);
	if (isNew) {
	    gn = Targ_NewGN(name);
	    Hash_SetValue (he, gn);
	    Var_Append(".ALLTARGETS", name, VAR_GLOBAL);
	    (void) Lst_AtEnd(allTargets, (ClientData)gn);
	}
    } else {
	he = Hash_FindEntry(&targetsSame, name);
    }

    if (he == (Hash_Entry *) NULL) {
	return (NILGNODE);
    } else {
	return ((GNode *) Hash_GetValue (he));
    }
}

/*-
 *-----------------------------------------------------------------------
 * Targ_FindList --
 *	Make a complete list of GNodes from the given list of names
 *
 * Input:
 *	name		list of names to find
 *	flags		flags used if no node is found for a given name
 *
 * Results:
 *	A complete list of graph nodes corresponding to all instances of all
 *	the names in names.
 *
 * Side Effects:
 *	If flags is TARG_CREATE, nodes will be created for all names in
 *	names which do not yet have graph nodes. If flags is TARG_NOCREATE,
 *	an error message will be printed for each name which can't be found.
 * -----------------------------------------------------------------------
 */
Lst
Targ_FindList(Lst names, int flags)
{
    Lst            nodes;	/* result list */
    LstNode	   ln;		/* name list element */
    GNode	   *gn;		/* node in tLn */
    char    	   *name;

    nodes = Lst_Init(FALSE);

    if (Lst_Open(names) == FAILURE) {
	return (nodes);
    }
    while ((ln = Lst_Next(names)) != NILLNODE) {
	name = (char *)Lst_Datum(ln);
	gn = Targ_FindNode(name, flags);
	if (gn != NILGNODE) {
	    /*
	     * Note: Lst_AtEnd must come before the Lst_Concat so the nodes
	     * are added to the list in the order in which they were
	     * encountered in the makefile.
	     */
	    (void) Lst_AtEnd(nodes, (ClientData)gn);
	} else if (flags == TARG_NOCREATE) {
	    Error("\"%s\" -- target unknown.", name);
	}
    }
    Lst_Close(names);
    return (nodes);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_Ignore  --
 *	Return true if should ignore errors when creating gn
 *
 * Input:
 *	gn		node to check for
 *
 * Results:
 *	TRUE if should ignore errors
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Targ_Ignore(GNode *gn)
{
    if (ignoreErrors || gn->type & OP_IGNORE) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Targ_Silent  --
 *	Return true if be silent when creating gn
 *
 * Input:
 *	gn		node to check for
 *
 * Results:
 *	TRUE if should be silent
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Targ_Silent(GNode *gn)
{
    if (beSilent || gn->type & OP_SILENT) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Targ_Precious --
 *	See if the given target is precious
 *
 * Input:
 *	gn		the node to check
 *
 * Results:
 *	TRUE if it is precious. FALSE otherwise
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Targ_Precious(GNode *gn)
{
    if (allPrecious || (gn->type & (OP_PRECIOUS|OP_DOUBLEDEP))) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}

/******************* DEBUG INFO PRINTING ****************/

static GNode	  *mainTarg;	/* the main target, as set by Targ_SetMain */
/*-
 *-----------------------------------------------------------------------
 * Targ_SetMain --
 *	Set our idea of the main target we'll be creating. Used for
 *	debugging output.
 *
 * Input:
 *	gn		The main target we'll create
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	"mainTarg" is set to the main target's node.
 *-----------------------------------------------------------------------
 */
void
Targ_SetMain(GNode *gn)
{
    mainTarg = gn;
}

static int
TargPrintName(ClientData gnp, ClientData ppath)
{
    GNode *gn = (GNode *) gnp;
    printf ("%s ", gn->name);
#ifdef notdef
    if (ppath) {
	if (gn->path) {
	    printf ("[%s]  ", gn->path);
	}
	if (gn == mainTarg) {
	    printf ("(MAIN NAME)  ");
	}
    }
#endif /* notdef */
    return (ppath ? 0 : 0);
}


int
Targ_PrintCmd(ClientData cmd, ClientData dummy)
{
    printf ("\t%s\n", (char *) cmd);
    return (dummy ? 0 : 0);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_FmtTime --
 *	Format a modification time in some reasonable way and return it.
 *
 * Results:
 *	The time reformatted.
 *
 * Side Effects:
 *	The time is placed in a static area, so it is overwritten
 *	with each call.
 *
 *-----------------------------------------------------------------------
 */
char *
Targ_FmtTime(time_t tm)
{
    struct tm	  	*parts;
    static char	  	buf[128];

    parts = localtime(&tm);
    (void)strftime(buf, sizeof buf, "%k:%M:%S %b %d, %Y", parts);
    return(buf);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_PrintType --
 *	Print out a type field giving only those attributes the user can
 *	set.
 *
 * Results:
 *
 * Side Effects:
 *
 *-----------------------------------------------------------------------
 */
void
Targ_PrintType(int type)
{
    int    tbit;

#define PRINTBIT(attr)	case CONCAT(OP_,attr): printf("." #attr " "); break
#define PRINTDBIT(attr) case CONCAT(OP_,attr): if (DEBUG(TARG)) printf("." #attr " "); break

    type &= ~OP_OPMASK;

    while (type) {
	tbit = 1 << (ffs(type) - 1);
	type &= ~tbit;

	switch(tbit) {
	    PRINTBIT(OPTIONAL);
	    PRINTBIT(USE);
	    PRINTBIT(EXEC);
	    PRINTBIT(IGNORE);
	    PRINTBIT(PRECIOUS);
	    PRINTBIT(SILENT);
	    PRINTBIT(MAKE);
	    PRINTBIT(JOIN);
	    PRINTBIT(INVISIBLE);
	    PRINTBIT(NOTMAIN);
	    PRINTDBIT(LIB);
	    /*XXX: MEMBER is defined, so CONCAT(OP_,MEMBER) gives OP_"%" */
	    case OP_MEMBER: if (DEBUG(TARG)) printf(".MEMBER "); break;
	    PRINTDBIT(ARCHV);
	    PRINTDBIT(MADE);
	    PRINTDBIT(PHONY);
	}
    }
}

/*-
 *-----------------------------------------------------------------------
 * TargPrintNode --
 *	print the contents of a node
 *-----------------------------------------------------------------------
 */
static int
TargPrintNode(ClientData gnp, ClientData passp)
{
    GNode         *gn = (GNode *) gnp;
    int	    	  pass = *(int *) passp;
    if (!OP_NOP(gn->type)) {
	printf("#\n");
	if (gn == mainTarg) {
	    printf("# *** MAIN TARGET ***\n");
	}
	if (pass == 2) {
	    if (gn->unmade) {
		printf("# %d unmade children\n", gn->unmade);
	    } else {
		printf("# No unmade children\n");
	    }
	    if (! (gn->type & (OP_JOIN|OP_USE|OP_USEBEFORE|OP_EXEC))) {
		if (gn->mtime != 0) {
		    printf("# last modified %s: %s\n",
			      Targ_FmtTime(gn->mtime),
			      (gn->made == UNMADE ? "unmade" :
			       (gn->made == MADE ? "made" :
				(gn->made == UPTODATE ? "up-to-date" :
				 "error when made"))));
		} else if (gn->made != UNMADE) {
		    printf("# non-existent (maybe): %s\n",
			      (gn->made == MADE ? "made" :
			       (gn->made == UPTODATE ? "up-to-date" :
				(gn->made == ERROR ? "error when made" :
				 "aborted"))));
		} else {
		    printf("# unmade\n");
		}
	    }
	    if (!Lst_IsEmpty (gn->iParents)) {
		printf("# implicit parents: ");
		Lst_ForEach(gn->iParents, TargPrintName, (ClientData)0);
		fputc ('\n', stdout);
	    }
	}
	if (!Lst_IsEmpty (gn->parents)) {
	    printf("# parents: ");
	    Lst_ForEach(gn->parents, TargPrintName, (ClientData)0);
	    fputc ('\n', stdout);
	}

	printf("%-16s", gn->name);
	switch (gn->type & OP_OPMASK) {
	    case OP_DEPENDS:
		printf(": "); break;
	    case OP_FORCE:
		printf("! "); break;
	    case OP_DOUBLEDEP:
		printf(":: "); break;
	}
	Targ_PrintType(gn->type);
	Lst_ForEach(gn->children, TargPrintName, (ClientData)0);
	fputc ('\n', stdout);
	Lst_ForEach(gn->commands, Targ_PrintCmd, (ClientData)0);
	printf("\n\n");
	if (gn->type & OP_DOUBLEDEP) {
	    Lst_ForEach(gn->cohorts, TargPrintNode, (ClientData)&pass);
	}
    }
    return (0);
}

/*-
 *-----------------------------------------------------------------------
 * TargPrintOnlySrc --
 *	Print only those targets that are just a source.
 *
 * Results:
 *	0.
 *
 * Side Effects:
 *	The name of each file is printed preceded by #\t
 *
 *-----------------------------------------------------------------------
 */
static int
TargPrintOnlySrc(ClientData gnp, ClientData dummy)
{
    GNode   	  *gn = (GNode *) gnp;
    if (OP_NOP(gn->type))
	printf("#\t%s [%s]\n", gn->name, gn->path ? gn->path : gn->name);

    return (dummy ? 0 : 0);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_PrintGraph --
 *	print the entire graph. heh heh
 *
 * Input:
 *	pass		Which pass this is. 1 => no processing
 *			2 => processing done
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	lots o' output
 *-----------------------------------------------------------------------
 */
void
Targ_PrintGraph(int pass)
{
    printf("#*** Input graph:\n");
    Lst_ForEach(allTargets, TargPrintNode, (ClientData)&pass);
    printf("\n\n");
    printf("#\n#   Files that are only sources:\n");
    Lst_ForEach(allTargets, TargPrintOnlySrc, (ClientData) 0);
    printf("#*** Global Variables:\n");
    Var_Dump(VAR_GLOBAL);
    printf("#*** Command-line Variables:\n");
    Var_Dump(VAR_CMD);
    printf("\n");
    Dir_PrintDirectories();
    printf("\n");
    Suff_PrintAll();
}

static int
TargPropagateCohort(ClientData cgnp, ClientData pgnp)
{
    GNode	  *cgn = (GNode *) cgnp;
    GNode	  *pgn = (GNode *) pgnp;

    cgn->type |= pgn->type & ~OP_OPMASK;
    return (0);
}

static int
TargPropagateNode(ClientData gnp, ClientData junk __unused)
{
    GNode	  *gn = (GNode *) gnp;
    if (gn->type & OP_DOUBLEDEP)
	Lst_ForEach(gn->cohorts, TargPropagateCohort, gnp);
    return (0);
}

void
Targ_Propagate(void)
{
    Lst_ForEach(allTargets, TargPropagateNode, (ClientData)0);
}
/* end targ.c */

/* begin trace.c */
/*	$NetBSD: trace.c,v 1.6 2004/05/07 00:04:40 ross Exp $	*/

/*-
 * Copyright (c) 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Bill Sommerfeld
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: trace.c,v 1.6 2004/05/07 00:04:40 ross Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
__RCSID("$NetBSD: trace.c,v 1.6 2004/05/07 00:04:40 ross Exp $");
#endif /* not lint */
#endif

/*-
 * trace.c --
 *	handle logging of trace events generated by various parts of make.
 *
 * Interface:
 *	Trace_Init		Initialize tracing (called once during
 *				the lifetime of the process)
 *
 *	Trace_End		Finalize tracing (called before make exits)
 *
 *	Trace_Log		Log an event about a particular make job.
 */

/* <<trace.c includes>> */

static FILE *trfile;
static pid_t trpid;
char *trwd;

static const char *evname[] = {
	"BEG",
	"END",
	"ERR",
	"JOB",
	"DON",
	"INT",
};

void
Trace_Init(const char *pathname)
{
	char *p1;
	if (pathname != NULL) {
		trpid = getpid();
		trwd = Var_Value(".CURDIR", VAR_GLOBAL, &p1);

		trfile = fopen(pathname, "a");
	}
}

void
Trace_Log(TrEvent event, Job *job)
{
	struct timeval rightnow;

	if (trfile == NULL)
		return;

	gettimeofday(&rightnow, NULL);

	fprintf(trfile, "%ld.%06d %d %d %s %d %s",
	    rightnow.tv_sec, (int)rightnow.tv_usec,
	    jobTokensRunning, jobTokensFree,
	    evname[event], trpid, trwd);
	if (job != NULL) {
		fprintf(trfile, " %s %d %x %x", job->node->name,
		    job->pid, job->flags, job->node->type);
	}
	fputc('\n', trfile);
	fflush(trfile);
}

void
Trace_End(void)
{
	if (trfile != NULL)
		fclose(trfile);
}
/* end trace.c */

/* begin var.c */
/*	$NetBSD: var.c,v 1.96 2005/07/01 16:45:38 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: var.c,v 1.96 2005/07/01 16:45:38 christos Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)var.c	8.3 (Berkeley) 3/19/94";
#else
__RCSID("$NetBSD: var.c,v 1.96 2005/07/01 16:45:38 christos Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * var.c --
 *	Variable-handling functions
 *
 * Interface:
 *	Var_Set	  	    Set the value of a variable in the given
 *	    	  	    context. The variable is created if it doesn't
 *	    	  	    yet exist. The value and variable name need not
 *	    	  	    be preserved.
 *
 *	Var_Append	    Append more characters to an existing variable
 *	    	  	    in the given context. The variable needn't
 *	    	  	    exist already -- it will be created if it doesn't.
 *	    	  	    A space is placed between the old value and the
 *	    	  	    new one.
 *
 *	Var_Exists	    See if a variable exists.
 *
 *	Var_Value 	    Return the value of a variable in a context or
 *	    	  	    NULL if the variable is undefined.
 *
 *	Var_Subst 	    Substitute named variable, or all variables if
 *			    NULL in a string using
 *	    	  	    the given context as the top-most one. If the
 *	    	  	    third argument is non-zero, Parse_Error is
 *	    	  	    called if any variables are undefined.
 *
 *	Var_Parse 	    Parse a variable expansion from a string and
 *	    	  	    return the result and the number of characters
 *	    	  	    consumed.
 *
 *	Var_Delete	    Delete a variable in a context.
 *
 *	Var_Init  	    Initialize this module.
 *
 * Debugging:
 *	Var_Dump  	    Print out all variables defined in the given
 *	    	  	    context.
 *
 * XXX: There's a lot of duplication in these functions.
 */

/* <<var.c includes>> */

/*
 * This is a harmless return value for Var_Parse that can be used by Var_Subst
 * to determine if there was an error in parsing -- easier than returning
 * a flag, as things outside this module don't give a hoot.
 */
char 	var_Error[] = "";

/*
 * Similar to var_Error, but returned when the 'err' flag for Var_Parse is
 * set false. Why not just use a constant? Well, gcc likes to condense
 * identical string instances...
 */
static char	varNoError[] = "";

/*
 * Internally, variables are contained in four different contexts.
 *	1) the environment. They may not be changed. If an environment
 *	    variable is appended-to, the result is placed in the global
 *	    context.
 *	2) the global context. Variables set in the Makefile are located in
 *	    the global context. It is the penultimate context searched when
 *	    substituting.
 *	3) the command-line context. All variables set on the command line
 *	   are placed in this context. They are UNALTERABLE once placed here.
 *	4) the local context. Each target has associated with it a context
 *	   list. On this list are located the structures describing such
 *	   local variables as $(@) and $(*)
 * The four contexts are searched in the reverse order from which they are
 * listed.
 */
GNode          *VAR_GLOBAL;   /* variables from the makefile */
GNode          *VAR_CMD;      /* variables defined on the command-line */

#define FIND_CMD	0x1   /* look in VAR_CMD when searching */
#define FIND_GLOBAL	0x2   /* look in VAR_GLOBAL as well */
#define FIND_ENV  	0x4   /* look in the environment also */

typedef struct Var {
    char          *name;	/* the variable's name */
    Buffer	  val;	    	/* its value */
    int	    	  flags;    	/* miscellaneous status flags */
#define VAR_IN_USE	1   	    /* Variable's value currently being used.
				     * Used to avoid recursion */
#define VAR_FROM_ENV	2   	    /* Variable comes from the environment */
#define VAR_JUNK  	4   	    /* Variable is a junk variable that
				     * should be destroyed when done with
				     * it. Used by Var_Parse for undefined,
				     * modified variables */
#define VAR_KEEP	8	    /* Variable is VAR_JUNK, but we found
				     * a use for it in some modifier and
				     * the value is therefore valid */
}  Var;


/* Var*Pattern flags */
#define VAR_SUB_GLOBAL	0x01	/* Apply substitution globally */
#define VAR_SUB_ONE	0x02	/* Apply substitution to one word */
#define VAR_SUB_MATCHED	0x04	/* There was a match */
#define VAR_MATCH_START	0x08	/* Match at start of word */
#define VAR_MATCH_END	0x10	/* Match at end of word */
#define VAR_NOSUBST	0x20	/* don't expand vars in VarGetPattern */

/* Var_Set flags */
#define VAR_NO_EXPORT	0x01	/* do not export */

typedef struct {
    /*
     * The following fields are set by Var_Parse() when it
     * encounters modifiers that need to keep state for use by
     * subsequent modifiers within the same variable expansion.
     */
    Byte	varSpace;	/* Word separator in expansions */
    Boolean	oneBigWord;	/* TRUE if we will treat the variable as a
				 * single big word, even if it contains
				 * embedded spaces (as opposed to the
				 * usual behaviour of treating it as
				 * several space-separated words). */
} Var_Parse_State;

/* struct passed as ClientData to VarSubstitute() for ":S/lhs/rhs/",
 * to VarSYSVMatch() for ":lhs=rhs". */
typedef struct {
    const char   *lhs;	    /* String to match */
    int	    	  leftLen; /* Length of string */
    const char   *rhs;	    /* Replacement string (w/ &'s removed) */
    int	    	  rightLen; /* Length of replacement */
    int	    	  flags;
} VarPattern;

/* struct passed as ClientData to VarLoopExpand() for ":@tvar@str@" */
typedef struct {
    GNode	*ctxt;		/* variable context */
    char	*tvar;		/* name of temp var */
    int		tvarLen;
    char	*str;		/* string to expand */
    int		strLen;
    int		err;		/* err for not defined */
} VarLoop_t;

/* struct passed to VarSelectWords() for ":[start..end]" */
typedef struct {
    int		start;		/* first word to select */
    int		end;		/* last word to select */
} VarSelectWords_t;

static Var *VarFind(const char *, GNode *, int);
static void VarAdd(const char *, const char *, GNode *);
static Boolean VarHead(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarTail(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarSuffix(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarRoot(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarMatch(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
#ifdef SYSVVARSUB
static Boolean VarSYSVMatch(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
#endif
static Boolean VarNoMatch(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarSubstitute(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarLoopExpand(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static char *VarGetPattern(GNode *, Var_Parse_State *,
			   int, const char **, int, int *, int *,
			   VarPattern *);
static char *VarQuote(char *);
static char *VarChangeCase(char *, int);
static char *VarModify(GNode *, Var_Parse_State *,
    const char *,
    Boolean (*)(GNode *, Var_Parse_State *, char *, Boolean, Buffer, ClientData),
    ClientData);
static char *VarOrder(const char *, const char);
static char *VarUniq(const char *);
static int VarWordCompare(const void *, const void *);
static void VarPrintVar(ClientData);

#define WR(a)	((char *)UNCONST(a))

/*-
 *-----------------------------------------------------------------------
 * VarFind --
 *	Find the given variable in the given context and any other contexts
 *	indicated.
 *
 * Input:
 *	name		name to find
 *	ctxt		context in which to find it
 *	flags		FIND_GLOBAL set means to look in the
 *			VAR_GLOBAL context as well. FIND_CMD set means
 *			to look in the VAR_CMD context also. FIND_ENV
 *			set means to look in the environment
 *
 * Results:
 *	A pointer to the structure describing the desired variable or
 *	NIL if the variable does not exist.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static Var *
VarFind(const char *name, GNode *ctxt, int flags)
{
    Hash_Entry         	*var;
    Var		  	*v;

	/*
	 * If the variable name begins with a '.', it could very well be one of
	 * the local ones.  We check the name against all the local variables
	 * and substitute the short version in for 'name' if it matches one of
	 * them.
	 */
	if (*name == '.' && isupper((unsigned char) name[1]))
		switch (name[1]) {
		case 'A':
			if (!strcmp(name, ".ALLSRC"))
				name = ALLSRC;
			if (!strcmp(name, ".ARCHIVE"))
				name = ARCHIVE;
			break;
		case 'I':
			if (!strcmp(name, ".IMPSRC"))
				name = IMPSRC;
			break;
		case 'M':
			if (!strcmp(name, ".MEMBER"))
				name = MEMBER;
			break;
		case 'O':
			if (!strcmp(name, ".OODATE"))
				name = OODATE;
			break;
		case 'P':
			if (!strcmp(name, ".PREFIX"))
				name = PREFIX;
			break;
		case 'T':
			if (!strcmp(name, ".TARGET"))
				name = TARGET;
			break;
		}
    /*
     * First look for the variable in the given context. If it's not there,
     * look for it in VAR_CMD, VAR_GLOBAL and the environment, in that order,
     * depending on the FIND_* flags in 'flags'
     */
    var = Hash_FindEntry(&ctxt->context, name);

    if ((var == NULL) && (flags & FIND_CMD) && (ctxt != VAR_CMD)) {
	var = Hash_FindEntry(&VAR_CMD->context, name);
    }
    if (!checkEnvFirst && (var == NULL) && (flags & FIND_GLOBAL) &&
	(ctxt != VAR_GLOBAL))
    {
	var = Hash_FindEntry(&VAR_GLOBAL->context, name);
    }
    if ((var == NULL) && (flags & FIND_ENV)) {
	char *env;

	if ((env = getenv (name)) != NULL) {
	    int	  	len;

	    v = emalloc(sizeof(Var));
	    v->name = estrdup(name);

	    len = strlen(env);

	    v->val = Buf_Init(len);
	    Buf_AddBytes(v->val, len, (Byte *)env);

	    v->flags = VAR_FROM_ENV;
	    return (v);
	} else if (checkEnvFirst && (flags & FIND_GLOBAL) &&
		   (ctxt != VAR_GLOBAL))
	{
	    var = Hash_FindEntry(&VAR_GLOBAL->context, name);
	    if (var == NULL) {
		return ((Var *) NIL);
	    } else {
		return ((Var *)Hash_GetValue(var));
	    }
	} else {
	    return((Var *)NIL);
	}
    } else if (var == NULL) {
	return ((Var *) NIL);
    } else {
	return ((Var *) Hash_GetValue(var));
    }
}

/*-
 *-----------------------------------------------------------------------
 * VarAdd  --
 *	Add a new variable of name name and value val to the given context
 *
 * Input:
 *	name		name of variable to add
 *	val		value to set it to
 *	ctxt		context in which to set it
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The new variable is placed at the front of the given context
 *	The name and val arguments are duplicated so they may
 *	safely be freed.
 *-----------------------------------------------------------------------
 */
static void
VarAdd(const char *name, const char *val, GNode *ctxt)
{
    Var   	  *v;
    int	    	  len;
    Hash_Entry    *h;

    v = emalloc(sizeof(Var));

    len = val ? strlen(val) : 0;
    v->val = Buf_Init(len+1);
    Buf_AddBytes(v->val, len, (const Byte *)val);

    v->flags = 0;

    h = Hash_CreateEntry(&ctxt->context, name, NULL);
    Hash_SetValue(h, v);
    v->name = h->name;
    if (DEBUG(VAR)) {
	printf("%s:%s = %s\n", ctxt->name, name, val);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Var_Delete --
 *	Remove a variable from a context.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The Var structure is removed and freed.
 *
 *-----------------------------------------------------------------------
 */
void
Var_Delete(const char *name, GNode *ctxt)
{
    Hash_Entry 	  *ln;

    if (DEBUG(VAR)) {
	printf("%s:delete %s\n", ctxt->name, name);
    }
    ln = Hash_FindEntry(&ctxt->context, name);
    if (ln != NULL) {
	Var 	  *v;

	v = (Var *)Hash_GetValue(ln);
	if (v->name != ln->name)
		free(v->name);
	Hash_DeleteEntry(&ctxt->context, ln);
	Buf_Destroy(v->val, TRUE);
	free((Address) v);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Var_Set --
 *	Set the variable name to the value val in the given context.
 *
 * Input:
 *	name		name of variable to set
 *	val		value to give to the variable
 *	ctxt		context in which to set it
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	If the variable doesn't yet exist, a new record is created for it.
 *	Else the old value is freed and the new one stuck in its place
 *
 * Notes:
 *	The variable is searched for only in its context before being
 *	created in that context. I.e. if the context is VAR_GLOBAL,
 *	only VAR_GLOBAL->context is searched. Likewise if it is VAR_CMD, only
 *	VAR_CMD->context is searched. This is done to avoid the literally
 *	thousands of unnecessary strcmp's that used to be done to
 *	set, say, $(@) or $(<).
 *-----------------------------------------------------------------------
 */
void
Var_Set(const char *name, const char *val, GNode *ctxt, int flags)
{
    Var   *v;
    const char *cp = name;

    /*
     * We only look for a variable in the given context since anything set
     * here will override anything in a lower context, so there's not much
     * point in searching them all just to save a bit of memory...
     */
    if ((name = strchr(cp, '$'))) {
	name = Var_Subst(NULL, cp, ctxt, 0);
    } else
	name = cp;
    v = VarFind(name, ctxt, 0);
    if (v == (Var *) NIL) {
	VarAdd(name, val, ctxt);
    } else {
	Buf_Discard(v->val, Buf_Size(v->val));
	Buf_AddBytes(v->val, strlen(val), (const Byte *)val);

	if (DEBUG(VAR)) {
	    printf("%s:%s = %s\n", ctxt->name, name, val);
	}
    }
    /*
     * Any variables given on the command line are automatically exported
     * to the environment (as per POSIX standard)
     */
    if (ctxt == VAR_CMD && (flags & VAR_NO_EXPORT) == 0) {

	/*
	 * If requested, don't export these in the environment
	 * individually.  We still put them in MAKEOVERRIDES so
	 * that the command-line settings continue to override
	 * Makefile settings.
	 */
	if (varNoExportEnv != TRUE)
	    setenv(name, val, 1);

	Var_Append(MAKEOVERRIDES, name, VAR_GLOBAL);
    }
    if (name != cp)
	free(UNCONST(name));
}

/*-
 *-----------------------------------------------------------------------
 * Var_Append --
 *	The variable of the given name has the given value appended to it in
 *	the given context.
 *
 * Input:
 *	name		name of variable to modify
 *	val		String to append to it
 *	ctxt		Context in which this should occur
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	If the variable doesn't exist, it is created. Else the strings
 *	are concatenated (with a space in between).
 *
 * Notes:
 *	Only if the variable is being sought in the global context is the
 *	environment searched.
 *	XXX: Knows its calling circumstances in that if called with ctxt
 *	an actual target, it will only search that context since only
 *	a local variable could be being appended to. This is actually
 *	a big win and must be tolerated.
 *-----------------------------------------------------------------------
 */
void
Var_Append(const char *name, const char *val, GNode *ctxt)
{
    Var		   *v;
    Hash_Entry	   *h;
    const char *cp = name;

    if ((name = strchr(cp, '$'))) {
	name = Var_Subst(NULL, cp, ctxt, 0);
    } else
	name = cp;

    v = VarFind(name, ctxt, (ctxt == VAR_GLOBAL) ? FIND_ENV : 0);

    if (v == (Var *) NIL) {
	VarAdd(name, val, ctxt);
    } else {
	Buf_AddByte(v->val, (Byte)' ');
	Buf_AddBytes(v->val, strlen(val), (const Byte *)val);

	if (DEBUG(VAR)) {
	    printf("%s:%s = %s\n", ctxt->name, name,
		   (char *) Buf_GetAll(v->val, (int *)NULL));
	}

	if (v->flags & VAR_FROM_ENV) {
	    /*
	     * If the original variable came from the environment, we
	     * have to install it in the global context (we could place
	     * it in the environment, but then we should provide a way to
	     * export other variables...)
	     */
	    v->flags &= ~VAR_FROM_ENV;
	    h = Hash_CreateEntry(&ctxt->context, name, NULL);
	    Hash_SetValue(h, v);
	}
    }
    if (name != cp)
	free(UNCONST(name));
}

/*-
 *-----------------------------------------------------------------------
 * Var_Exists --
 *	See if the given variable exists.
 *
 * Input:
 *	name		Variable to find
 *	ctxt		Context in which to start search
 *
 * Results:
 *	TRUE if it does, FALSE if it doesn't
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
Boolean
Var_Exists(const char *name, GNode *ctxt)
{
    Var	    	  *v;

    v = VarFind(name, ctxt, FIND_CMD|FIND_GLOBAL|FIND_ENV);

    if (v == (Var *)NIL) {
	return(FALSE);
    } else if (v->flags & VAR_FROM_ENV) {
	free(v->name);
	Buf_Destroy(v->val, TRUE);
	free((char *)v);
    }
    return(TRUE);
}

/*-
 *-----------------------------------------------------------------------
 * Var_Value --
 *	Return the value of the named variable in the given context
 *
 * Input:
 *	name		name to find
 *	ctxt		context in which to search for it
 *
 * Results:
 *	The value if the variable exists, NULL if it doesn't
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
char *
Var_Value(const char *name, GNode *ctxt, char **frp)
{
    Var            *v;

    v = VarFind(name, ctxt, FIND_ENV | FIND_GLOBAL | FIND_CMD);
    *frp = NULL;
    if (v != (Var *) NIL) {
	char *p = ((char *)Buf_GetAll(v->val, (int *)NULL));
	if (v->flags & VAR_FROM_ENV) {
	    free(v->name);
	    Buf_Destroy(v->val, FALSE);
	    free((Address) v);
	    *frp = p;
	}
	return p;
    } else {
	return ((char *) NULL);
    }
}

/*-
 *-----------------------------------------------------------------------
 * VarHead --
 *	Remove the tail of the given word and place the result in the given
 *	buffer.
 *
 * Input:
 *	word		Word to trim
 *	addSpace	True if need to add a space to the buffer
 *			before sticking in the head
 *	buf		Buffer in which to store it
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The trimmed word is added to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarHead(GNode *ctx __unused, Var_Parse_State *vpstate,
	char *word, Boolean addSpace, Buffer buf,
	ClientData dummy)
{
    char *slash;

    slash = strrchr (word, '/');
    if (slash != (char *)NULL) {
	if (addSpace && vpstate->varSpace) {
	    Buf_AddByte (buf, vpstate->varSpace);
	}
	*slash = '\0';
	Buf_AddBytes(buf, strlen (word), (Byte *)word);
	*slash = '/';
	return (TRUE);
    } else {
	/*
	 * If no directory part, give . (q.v. the POSIX standard)
	 */
	if (addSpace && vpstate->varSpace)
	    Buf_AddByte(buf, vpstate->varSpace);
	Buf_AddByte(buf, (Byte)'.');
    }
    return(dummy ? TRUE : TRUE);
}

/*-
 *-----------------------------------------------------------------------
 * VarTail --
 *	Remove the head of the given word and place the result in the given
 *	buffer.
 *
 * Input:
 *	word		Word to trim
 *	addSpace	True if need to add a space to the buffer
 *			before adding the tail
 *	buf		Buffer in which to store it
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The trimmed word is added to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarTail(GNode *ctx __unused, Var_Parse_State *vpstate,
	char *word, Boolean addSpace, Buffer buf,
	ClientData dummy)
{
    char *slash;

    if (addSpace && vpstate->varSpace) {
	Buf_AddByte (buf, vpstate->varSpace);
    }

    slash = strrchr (word, '/');
    if (slash != (char *)NULL) {
	*slash++ = '\0';
	Buf_AddBytes(buf, strlen(slash), (Byte *)slash);
	slash[-1] = '/';
    } else {
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return (dummy ? TRUE : TRUE);
}

/*-
 *-----------------------------------------------------------------------
 * VarSuffix --
 *	Place the suffix of the given word in the given buffer.
 *
 * Input:
 *	word		Word to trim
 *	addSpace	TRUE if need to add a space before placing the
 *			suffix in the buffer
 *	buf		Buffer in which to store it
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The suffix from the word is placed in the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarSuffix(GNode *ctx __unused, Var_Parse_State *vpstate,
	  char *word, Boolean addSpace, Buffer buf,
	  ClientData dummy)
{
    char *dot;

    dot = strrchr (word, '.');
    if (dot != (char *)NULL) {
	if (addSpace && vpstate->varSpace) {
	    Buf_AddByte (buf, vpstate->varSpace);
	}
	*dot++ = '\0';
	Buf_AddBytes(buf, strlen (dot), (Byte *)dot);
	dot[-1] = '.';
	addSpace = TRUE;
    }
    return (dummy ? addSpace : addSpace);
}

/*-
 *-----------------------------------------------------------------------
 * VarRoot --
 *	Remove the suffix of the given word and place the result in the
 *	buffer.
 *
 * Input:
 *	word		Word to trim
 *	addSpace	TRUE if need to add a space to the buffer
 *			before placing the root in it
 *	buf		Buffer in which to store it
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The trimmed word is added to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarRoot(GNode *ctx __unused, Var_Parse_State *vpstate,
	char *word, Boolean addSpace, Buffer buf,
	ClientData dummy)
{
    char *dot;

    if (addSpace && vpstate->varSpace) {
	Buf_AddByte (buf, vpstate->varSpace);
    }

    dot = strrchr (word, '.');
    if (dot != (char *)NULL) {
	*dot = '\0';
	Buf_AddBytes(buf, strlen (word), (Byte *)word);
	*dot = '.';
    } else {
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return (dummy ? TRUE : TRUE);
}

/*-
 *-----------------------------------------------------------------------
 * VarMatch --
 *	Place the word in the buffer if it matches the given pattern.
 *	Callback function for VarModify to implement the :M modifier.
 *
 * Input:
 *	word		Word to examine
 *	addSpace	TRUE if need to add a space to the buffer
 *			before adding the word, if it matches
 *	buf		Buffer in which to store it
 *	pattern		Pattern the word must match
 *
 * Results:
 *	TRUE if a space should be placed in the buffer before the next
 *	word.
 *
 * Side Effects:
 *	The word may be copied to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarMatch(GNode *ctx __unused, Var_Parse_State *vpstate,
	 char *word, Boolean addSpace, Buffer buf,
	 ClientData pattern)
{
    if (Str_Match(word, (char *) pattern)) {
	if (addSpace && vpstate->varSpace) {
	    Buf_AddByte(buf, vpstate->varSpace);
	}
	addSpace = TRUE;
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return(addSpace);
}

#ifdef SYSVVARSUB
/*-
 *-----------------------------------------------------------------------
 * VarSYSVMatch --
 *	Place the word in the buffer if it matches the given pattern.
 *	Callback function for VarModify to implement the System V %
 *	modifiers.
 *
 * Input:
 *	word		Word to examine
 *	addSpace	TRUE if need to add a space to the buffer
 *			before adding the word, if it matches
 *	buf		Buffer in which to store it
 *	patp		Pattern the word must match
 *
 * Results:
 *	TRUE if a space should be placed in the buffer before the next
 *	word.
 *
 * Side Effects:
 *	The word may be copied to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarSYSVMatch(GNode *ctx, Var_Parse_State *vpstate,
	     char *word, Boolean addSpace, Buffer buf,
	     ClientData patp)
{
    int len;
    char *ptr;
    VarPattern 	  *pat = (VarPattern *) patp;
    char *varexp;

    if (addSpace && vpstate->varSpace)
	Buf_AddByte(buf, vpstate->varSpace);

    addSpace = TRUE;

    if ((ptr = Str_SYSVMatch(word, pat->lhs, &len)) != NULL) {
        varexp = Var_Subst(NULL, pat->rhs, ctx, 0);
	Str_SYSVSubst(buf, varexp, ptr, len);
	free(varexp);
    } else {
	Buf_AddBytes(buf, strlen(word), (Byte *) word);
    }

    return(addSpace);
}
#endif


/*-
 *-----------------------------------------------------------------------
 * VarNoMatch --
 *	Place the word in the buffer if it doesn't match the given pattern.
 *	Callback function for VarModify to implement the :N modifier.
 *
 * Input:
 *	word		Word to examine
 *	addSpace	TRUE if need to add a space to the buffer
 *			before adding the word, if it matches
 *	buf		Buffer in which to store it
 *	pattern		Pattern the word must match
 *
 * Results:
 *	TRUE if a space should be placed in the buffer before the next
 *	word.
 *
 * Side Effects:
 *	The word may be copied to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarNoMatch(GNode *ctx __unused, Var_Parse_State *vpstate,
	   char *word, Boolean addSpace, Buffer buf,
	   ClientData pattern)
{
    if (!Str_Match(word, (char *) pattern)) {
	if (addSpace && vpstate->varSpace) {
	    Buf_AddByte(buf, vpstate->varSpace);
	}
	addSpace = TRUE;
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return(addSpace);
}


/*-
 *-----------------------------------------------------------------------
 * VarSubstitute --
 *	Perform a string-substitution on the given word, placing the
 *	result in the passed buffer.
 *
 * Input:
 *	word		Word to modify
 *	addSpace	True if space should be added before
 *			other characters
 *	buf		Buffer for result
 *	patternp	Pattern for substitution
 *
 * Results:
 *	TRUE if a space is needed before more characters are added.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarSubstitute(GNode *ctx __unused, Var_Parse_State *vpstate,
	      char *word, Boolean addSpace, Buffer buf,
	      ClientData patternp)
{
    int  	wordLen;    /* Length of word */
    char 	*cp;	    /* General pointer */
    VarPattern	*pattern = (VarPattern *) patternp;

    wordLen = strlen(word);
    if ((pattern->flags & (VAR_SUB_ONE|VAR_SUB_MATCHED)) !=
	(VAR_SUB_ONE|VAR_SUB_MATCHED)) {
	/*
	 * Still substituting -- break it down into simple anchored cases
	 * and if none of them fits, perform the general substitution case.
	 */
	if ((pattern->flags & VAR_MATCH_START) &&
	    (strncmp(word, pattern->lhs, pattern->leftLen) == 0)) {
		/*
		 * Anchored at start and beginning of word matches pattern
		 */
		if ((pattern->flags & VAR_MATCH_END) &&
		    (wordLen == pattern->leftLen)) {
			/*
			 * Also anchored at end and matches to the end (word
			 * is same length as pattern) add space and rhs only
			 * if rhs is non-null.
			 */
			if (pattern->rightLen != 0) {
			    if (addSpace && vpstate->varSpace) {
				Buf_AddByte(buf, vpstate->varSpace);
			    }
			    addSpace = TRUE;
			    Buf_AddBytes(buf, pattern->rightLen,
					 (const Byte *)pattern->rhs);
			}
			pattern->flags |= VAR_SUB_MATCHED;
		} else if (pattern->flags & VAR_MATCH_END) {
		    /*
		     * Doesn't match to end -- copy word wholesale
		     */
		    goto nosub;
		} else {
		    /*
		     * Matches at start but need to copy in trailing characters
		     */
		    if ((pattern->rightLen + wordLen - pattern->leftLen) != 0){
			if (addSpace && vpstate->varSpace) {
			    Buf_AddByte(buf, vpstate->varSpace);
			}
			addSpace = TRUE;
		    }
		    Buf_AddBytes(buf, pattern->rightLen,
			(const Byte *)pattern->rhs);
		    Buf_AddBytes(buf, wordLen - pattern->leftLen,
				 (Byte *)(word + pattern->leftLen));
		    pattern->flags |= VAR_SUB_MATCHED;
		}
	} else if (pattern->flags & VAR_MATCH_START) {
	    /*
	     * Had to match at start of word and didn't -- copy whole word.
	     */
	    goto nosub;
	} else if (pattern->flags & VAR_MATCH_END) {
	    /*
	     * Anchored at end, Find only place match could occur (leftLen
	     * characters from the end of the word) and see if it does. Note
	     * that because the $ will be left at the end of the lhs, we have
	     * to use strncmp.
	     */
	    cp = word + (wordLen - pattern->leftLen);
	    if ((cp >= word) &&
		(strncmp(cp, pattern->lhs, pattern->leftLen) == 0)) {
		/*
		 * Match found. If we will place characters in the buffer,
		 * add a space before hand as indicated by addSpace, then
		 * stuff in the initial, unmatched part of the word followed
		 * by the right-hand-side.
		 */
		if (((cp - word) + pattern->rightLen) != 0) {
		    if (addSpace && vpstate->varSpace) {
			Buf_AddByte(buf, vpstate->varSpace);
		    }
		    addSpace = TRUE;
		}
		Buf_AddBytes(buf, cp - word, (const Byte *)word);
		Buf_AddBytes(buf, pattern->rightLen,
		    (const Byte *)pattern->rhs);
		pattern->flags |= VAR_SUB_MATCHED;
	    } else {
		/*
		 * Had to match at end and didn't. Copy entire word.
		 */
		goto nosub;
	    }
	} else {
	    /*
	     * Pattern is unanchored: search for the pattern in the word using
	     * String_FindSubstring, copying unmatched portions and the
	     * right-hand-side for each match found, handling non-global
	     * substitutions correctly, etc. When the loop is done, any
	     * remaining part of the word (word and wordLen are adjusted
	     * accordingly through the loop) is copied straight into the
	     * buffer.
	     * addSpace is set FALSE as soon as a space is added to the
	     * buffer.
	     */
	    Boolean done;
	    int origSize;

	    done = FALSE;
	    origSize = Buf_Size(buf);
	    while (!done) {
		cp = Str_FindSubstring(word, pattern->lhs);
		if (cp != (char *)NULL) {
		    if (addSpace && (((cp - word) + pattern->rightLen) != 0)){
			Buf_AddByte(buf, vpstate->varSpace);
			addSpace = FALSE;
		    }
		    Buf_AddBytes(buf, cp-word, (const Byte *)word);
		    Buf_AddBytes(buf, pattern->rightLen,
			(const Byte *)pattern->rhs);
		    wordLen -= (cp - word) + pattern->leftLen;
		    word = cp + pattern->leftLen;
		    if (wordLen == 0) {
			done = TRUE;
		    }
		    if ((pattern->flags & VAR_SUB_GLOBAL) == 0) {
			done = TRUE;
		    }
		    pattern->flags |= VAR_SUB_MATCHED;
		} else {
		    done = TRUE;
		}
	    }
	    if (wordLen != 0) {
		if (addSpace && vpstate->varSpace) {
		    Buf_AddByte(buf, vpstate->varSpace);
		}
		Buf_AddBytes(buf, wordLen, (Byte *)word);
	    }
	    /*
	     * If added characters to the buffer, need to add a space
	     * before we add any more. If we didn't add any, just return
	     * the previous value of addSpace.
	     */
	    return ((Buf_Size(buf) != origSize) || addSpace);
	}
	return (addSpace);
    }
 nosub:
    if (addSpace && vpstate->varSpace) {
	Buf_AddByte(buf, vpstate->varSpace);
    }
    Buf_AddBytes(buf, wordLen, (Byte *)word);
    return(TRUE);
}

/*-
 *-----------------------------------------------------------------------
 * VarLoopExpand --
 *	Implements the :@<temp>@<string>@ modifier of ODE make.
 *	We set the temp variable named in pattern.lhs to word and expand
 *	pattern.rhs storing the result in the passed buffer.
 *
 * Input:
 *	word		Word to modify
 *	addSpace	True if space should be added before
 *			other characters
 *	buf		Buffer for result
 *	pattern		Datafor substitution
 *
 * Results:
 *	TRUE if a space is needed before more characters are added.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarLoopExpand(GNode *ctx __unused, Var_Parse_State *vpstate __unused,
	      char *word, Boolean addSpace, Buffer buf,
	      ClientData loopp)
{
    VarLoop_t	*loop = (VarLoop_t *) loopp;
    char *s;
    int slen;

    if (word && *word) {
        Var_Set(loop->tvar, word, loop->ctxt, VAR_NO_EXPORT);
        s = Var_Subst(NULL, loop->str, loop->ctxt, loop->err);
        if (s != NULL && *s != '\0') {
            if (addSpace && *s != '\n')
                Buf_AddByte(buf, ' ');
            Buf_AddBytes(buf, (slen = strlen(s)), (Byte *)s);
            addSpace = (slen > 0 && s[slen - 1] != '\n');
            free(s);
        }
    }
    return addSpace;
}


/*-
 *-----------------------------------------------------------------------
 * VarSelectWords --
 *	Implements the :[start..end] modifier.
 *	This is a special case of VarModify since we want to be able
 *	to scan the list backwards if start > end.
 *
 * Input:
 *	str		String whose words should be trimmed
 *	seldata		words to select
 *
 * Results:
 *	A string of all the words selected.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarSelectWords(GNode *ctx __unused, Var_Parse_State *vpstate,
	       const char *str, VarSelectWords_t *seldata)
{
    Buffer  	  buf;	    	    /* Buffer for the new string */
    Boolean 	  addSpace; 	    /* TRUE if need to add a space to the
				     * buffer before adding the trimmed
				     * word */
    char **av;			    /* word list */
    char *as;			    /* word list memory */
    int ac, i;
    int start, end, step;

    buf = Buf_Init(0);
    addSpace = FALSE;

    if (vpstate->oneBigWord) {
	/* fake what brk_string() would do if there were only one word */
	ac = 1;
    	av = emalloc((ac + 1) * sizeof(char *));
	as = strdup(str);
	av[0] = as;
	av[1] = NULL;
    } else {
	av = brk_string(str, &ac, FALSE, &as);
    }

    /*
     * Now sanitize seldata.
     * If seldata->start or seldata->end are negative, convert them to
     * the positive equivalents (-1 gets converted to argc, -2 gets
     * converted to (argc-1), etc.).
     */
    if (seldata->start < 0)
	seldata->start = ac + seldata->start + 1;
    if (seldata->end < 0)
	seldata->end = ac + seldata->end + 1;

    /*
     * We avoid scanning more of the list than we need to.
     */
    if (seldata->start > seldata->end) {
	start = MIN(ac, seldata->start) - 1;
	end = MAX(0, seldata->end - 1);
	step = -1;
    } else {
	start = MAX(0, seldata->start - 1);
	end = MIN(ac, seldata->end);
	step = 1;
    }

    for (i = start;
	 (step < 0 && i >= end) || (step > 0 && i < end);
	 i += step) {
	if (av[i] && *av[i]) {
	    if (addSpace && vpstate->varSpace) {
		Buf_AddByte(buf, vpstate->varSpace);
	    }
	    Buf_AddBytes(buf, strlen(av[i]), (Byte *)av[i]);
	    addSpace = TRUE;
	}
    }

    free(as);
    free(av);

    Buf_AddByte (buf, '\0');
    as = (char *)Buf_GetAll (buf, (int *)NULL);
    Buf_Destroy(buf, FALSE);
    return (as);
}

/*-
 *-----------------------------------------------------------------------
 * VarModify --
 *	Modify each of the words of the passed string using the given
 *	function. Used to implement all modifiers.
 *
 * Input:
 *	str		String whose words should be trimmed
 *	modProc		Function to use to modify them
 *	datum		Datum to pass it
 *
 * Results:
 *	A string of all the words modified appropriately.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarModify(GNode *ctx, Var_Parse_State *vpstate,
    const char *str,
    Boolean (*modProc)(GNode *, Var_Parse_State *, char *,
		       Boolean, Buffer, ClientData),
    ClientData datum)
{
    Buffer  	  buf;	    	    /* Buffer for the new string */
    Boolean 	  addSpace; 	    /* TRUE if need to add a space to the
				     * buffer before adding the trimmed
				     * word */
    char **av;			    /* word list */
    char *as;			    /* word list memory */
    int ac, i;

    buf = Buf_Init(0);
    addSpace = FALSE;

    if (vpstate->oneBigWord) {
	/* fake what brk_string() would do if there were only one word */
	ac = 1;
    	av = emalloc((ac + 1) * sizeof(char *));
	as = strdup(str);
	av[0] = as;
	av[1] = NULL;
    } else {
	av = brk_string(str, &ac, FALSE, &as);
    }

    for (i = 0; i < ac; i++) {
	addSpace = (*modProc)(ctx, vpstate, av[i], addSpace, buf, datum);
    }

    free(as);
    free(av);

    Buf_AddByte (buf, '\0');
    as = (char *)Buf_GetAll (buf, (int *)NULL);
    Buf_Destroy(buf, FALSE);
    return (as);
}


static int
VarWordCompare(const void *a, const void *b)
{
	int r = strcmp(*(const char * const *)a, *(const char * const *)b);
	return r;
}

/*-
 *-----------------------------------------------------------------------
 * VarOrder --
 *	Order the words in the string.
 *
 * Input:
 *	str		String whose words should be sorted.
 *	otype		How to order: s - sort, x - random.
 *
 * Results:
 *	A string containing the words ordered.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarOrder(const char *str, const char otype)
{
    Buffer  	  buf;	    	    /* Buffer for the new string */
    char **av;			    /* word list [first word does not count] */
    char *as;			    /* word list memory */
    int ac, i;

    buf = Buf_Init(0);

    av = brk_string(str, &ac, FALSE, &as);

    if (ac > 0)
	switch (otype) {
	case 's':	/* sort alphabetically */
	    qsort(av, ac, sizeof(char *), VarWordCompare);
	    break;
	case 'x':	/* randomize */
	{
	    int rndidx;
	    char *t;

	    /*
	     * We will use [ac..2] range for mod factors. This will produce
	     * random numbers in [(ac-1)..0] interval, and minimal
	     * reasonable value for mod factor is 2 (the mod 1 will produce
	     * 0 with probability 1).
	     */
	    for (i = ac-1; i > 0; i--) {
		rndidx = random() % (i + 1);
		if (i != rndidx) {
		    t = av[i];
		    av[i] = av[rndidx];
		    av[rndidx] = t;
		}
	    }
	}
	} /* end of switch */

    for (i = 0; i < ac; i++) {
	Buf_AddBytes(buf, strlen(av[i]), (Byte *) av[i]);
	if (i != ac - 1)
	    Buf_AddByte (buf, ' ');
    }

    free(as);
    free(av);

    Buf_AddByte (buf, '\0');
    as = (char *)Buf_GetAll (buf, (int *)NULL);
    Buf_Destroy(buf, FALSE);
    return (as);
}


/*-
 *-----------------------------------------------------------------------
 * VarUniq --
 *	Remove adjacent duplicate words.
 *
 * Input:
 *	str		String whose words should be sorted
 *
 * Results:
 *	A string containing the resulting words.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarUniq(const char *str)
{
    Buffer	  buf;	    	    /* Buffer for new string */
    char 	**av;		    /* List of words to affect */
    char 	 *as;		    /* Word list memory */
    int 	  ac, i, j;

    buf = Buf_Init(0);
    av = brk_string(str, &ac, FALSE, &as);

    if (ac > 1) {
	for (j = 0, i = 1; i < ac; i++)
	    if (strcmp(av[i], av[j]) != 0 && (++j != i))
		av[j] = av[i];
	ac = j + 1;
    }

    for (i = 0; i < ac; i++) {
	Buf_AddBytes(buf, strlen(av[i]), (Byte *)av[i]);
	if (i != ac - 1)
	    Buf_AddByte(buf, ' ');
    }

    free(as);
    free(av);

    Buf_AddByte(buf, '\0');
    as = (char *)Buf_GetAll(buf, (int *)NULL);
    Buf_Destroy(buf, FALSE);
    return as;
}


/*-
 *-----------------------------------------------------------------------
 * VarGetPattern --
 *	Pass through the tstr looking for 1) escaped delimiters,
 *	'$'s and backslashes (place the escaped character in
 *	uninterpreted) and 2) unescaped $'s that aren't before
 *	the delimiter (expand the variable substitution unless flags
 *	has VAR_NOSUBST set).
 *	Return the expanded string or NULL if the delimiter was missing
 *	If pattern is specified, handle escaped ampersands, and replace
 *	unescaped ampersands with the lhs of the pattern.
 *
 * Results:
 *	A string of all the words modified appropriately.
 *	If length is specified, return the string length of the buffer
 *	If flags is specified and the last character of the pattern is a
 *	$ set the VAR_MATCH_END bit of flags.
 *
 * Side Effects:
 *	None.
 *-----------------------------------------------------------------------
 */
static char *
VarGetPattern(GNode *ctxt, Var_Parse_State *vpstate __unused,
	      int err, const char **tstr, int delim, int *flags,
	      int *length, VarPattern *pattern)
{
    const char *cp;
    Buffer buf = Buf_Init(0);
    int junk;
    if (length == NULL)
	length = &junk;

#define IS_A_MATCH(cp, delim) \
    ((cp[0] == '\\') && ((cp[1] == delim) ||  \
     (cp[1] == '\\') || (cp[1] == '$') || (pattern && (cp[1] == '&'))))

    /*
     * Skim through until the matching delimiter is found;
     * pick up variable substitutions on the way. Also allow
     * backslashes to quote the delimiter, $, and \, but don't
     * touch other backslashes.
     */
    for (cp = *tstr; *cp && (*cp != delim); cp++) {
	if (IS_A_MATCH(cp, delim)) {
	    Buf_AddByte(buf, (Byte) cp[1]);
	    cp++;
	} else if (*cp == '$') {
	    if (cp[1] == delim) {
		if (flags == NULL)
		    Buf_AddByte(buf, (Byte) *cp);
		else
		    /*
		     * Unescaped $ at end of pattern => anchor
		     * pattern at end.
		     */
		    *flags |= VAR_MATCH_END;
	    } else {
		if (flags == NULL || (*flags & VAR_NOSUBST) == 0) {
		    char   *cp2;
		    int     len;
		    Boolean freeIt;

		    /*
		     * If unescaped dollar sign not before the
		     * delimiter, assume it's a variable
		     * substitution and recurse.
		     */
		    cp2 = Var_Parse(cp, ctxt, err, &len, &freeIt);
		    Buf_AddBytes(buf, strlen(cp2), (Byte *) cp2);
		    if (freeIt)
			free(cp2);
		    cp += len - 1;
		} else {
		    const char *cp2 = &cp[1];

		    if (*cp2 == '(' || *cp2 == '{') {
			/*
			 * Find the end of this variable reference
			 * and suck it in without further ado.
			 * It will be interperated later.
			 */
			int have = *cp2;
			int want = (*cp2 == '(') ? ')' : '}';
			int depth = 1;

			for (++cp2; *cp2 != '\0' && depth > 0; ++cp2) {
			    if (cp2[-1] != '\\') {
				if (*cp2 == have)
				    ++depth;
				if (*cp2 == want)
				    --depth;
			    }
			}
			Buf_AddBytes(buf, cp2 - cp, (const Byte *)cp);
			cp = --cp2;
		    } else
			Buf_AddByte(buf, (Byte) *cp);
		}
	    }
	}
	else if (pattern && *cp == '&')
	    Buf_AddBytes(buf, pattern->leftLen, (const Byte *)pattern->lhs);
	else
	    Buf_AddByte(buf, (Byte) *cp);
    }

    Buf_AddByte(buf, (Byte) '\0');

    if (*cp != delim) {
	*tstr = cp;
	*length = 0;
	return NULL;
    }
    else {
	char *rstr;
	*tstr = ++cp;
	rstr = (char *) Buf_GetAll(buf, length);
	*length -= 1;	/* Don't count the NULL */
	Buf_Destroy(buf, FALSE);
	return rstr;
    }
}

/*-
 *-----------------------------------------------------------------------
 * VarQuote --
 *	Quote shell meta-characters in the string
 *
 * Results:
 *	The quoted string
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarQuote(char *str)
{

    Buffer  	  buf;
    /* This should cover most shells :-( */
    static char meta[] = "\n \t'`\";&<>()|*?{}[]\\$!#^~";

    buf = Buf_Init(MAKE_BSIZE);
    for (; *str; str++) {
	if (strchr(meta, *str) != NULL)
	    Buf_AddByte(buf, (Byte)'\\');
	Buf_AddByte(buf, (Byte)*str);
    }
    Buf_AddByte(buf, (Byte) '\0');
    str = (char *)Buf_GetAll (buf, (int *)NULL);
    Buf_Destroy(buf, FALSE);
    return str;
}

/*-
 *-----------------------------------------------------------------------
 * VarChangeCase --
 *      Change the string to all uppercase or all lowercase
 *
 * Input:
 *	str		String to modify
 *	upper		TRUE -> uppercase, else lowercase
 *
 * Results:
 *      The string with case changed
 *
 * Side Effects:
 *      None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarChangeCase(char *str, int upper)
{
   Buffer         buf;
   int            (*modProc)(int);

   modProc = (upper ? toupper : tolower);
   buf = Buf_Init(MAKE_BSIZE);
   for (; *str ; str++) {
       Buf_AddByte(buf, (Byte) modProc(*str));
   }
   Buf_AddByte(buf, (Byte) '\0');
   str = (char *) Buf_GetAll(buf, (int *) NULL);
   Buf_Destroy(buf, FALSE);
   return str;
}

/*-
 *-----------------------------------------------------------------------
 * Var_Parse --
 *	Given the start of a variable invocation, extract the variable
 *	name and find its value, then modify it according to the
 *	specification.
 *
 * Input:
 *	str		The string to parse
 *	ctxt		The context for the variable
 *	err		TRUE if undefined variables are an error
 *	lengthPtr	OUT: The length of the specification
 *	freePtr		OUT: TRUE if caller should free result
 *
 * Results:
 *	The (possibly-modified) value of the variable or var_Error if the
 *	specification is invalid. The length of the specification is
 *	placed in *lengthPtr (for invalid specifications, this is just
 *	2...?).
 *	A Boolean in *freePtr telling whether the returned string should
 *	be freed by the caller.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
char *
Var_Parse(const char *str, GNode *ctxt, Boolean err, int *lengthPtr,
	  Boolean *freePtr)
{
    const char	   *tstr;    	/* Pointer into str */
    Var	    	   *v;	    	/* Variable in invocation */
    const char     *cp;    	/* Secondary pointer into str (place marker
				 * for tstr) */
    Boolean 	    haveModifier;/* TRUE if have modifiers for the variable */
    char	    endc;    	/* Ending character when variable in parens
				 * or braces */
    char	    startc=0;	/* Starting character when variable in parens
				 * or braces */
    int             cnt;	/* Used to count brace pairs when variable in
				 * in parens or braces */
    int		    vlen;	/* Length of variable name */
    const char 	   *start;
    char	    delim;
    char	   *nstr;
    Boolean 	    dynamic;	/* TRUE if the variable is local and we're
				 * expanding it in a non-local context. This
				 * is done to support dynamic sources. The
				 * result is just the invocation, unaltered */
    Var_Parse_State parsestate; /* Flags passed to helper functions */

    *freePtr = FALSE;
    dynamic = FALSE;
    start = str;
    parsestate.oneBigWord = FALSE;
    parsestate.varSpace = ' ';	/* word separator */

    if (str[1] != '(' && str[1] != '{') {
	/*
	 * If it's not bounded by braces of some sort, life is much simpler.
	 * We just need to check for the first character and return the
	 * value if it exists.
	 */
	char	  name[2];

	name[0] = str[1];
	name[1] = '\0';

	v = VarFind(name, ctxt, FIND_ENV | FIND_GLOBAL | FIND_CMD);
	if (v == (Var *)NIL) {
	    *lengthPtr = 2;

	    if ((ctxt == VAR_CMD) || (ctxt == VAR_GLOBAL)) {
		/*
		 * If substituting a local variable in a non-local context,
		 * assume it's for dynamic source stuff. We have to handle
		 * this specially and return the longhand for the variable
		 * with the dollar sign escaped so it makes it back to the
		 * caller. Only four of the local variables are treated
		 * specially as they are the only four that will be set
		 * when dynamic sources are expanded.
		 */
		switch (str[1]) {
		    case '@':
			return UNCONST("$(.TARGET)");
		    case '%':
			return UNCONST("$(.ARCHIVE)");
		    case '*':
			return UNCONST("$(.PREFIX)");
		    case '!':
			return UNCONST("$(.MEMBER)");
		}
	    }
	    /*
	     * Error
	     */
	    return (err ? var_Error : varNoError);
	} else {
	    haveModifier = FALSE;
	    tstr = &str[1];
	    endc = str[1];
	}
    } else {
	Buffer buf;	/* Holds the variable name */

	startc = str[1];
	endc = startc == '(' ? ')' : '}';
	buf = Buf_Init(MAKE_BSIZE);

	/*
	 * Skip to the end character or a colon, whichever comes first.
	 */
	for (tstr = str + 2;
	     *tstr != '\0' && *tstr != endc && *tstr != ':';
	     tstr++)
	{
	    /*
	     * A variable inside a variable, expand
	     */
	    if (*tstr == '$') {
		int rlen;
		Boolean rfree;
		char *rval = Var_Parse(tstr, ctxt, err, &rlen, &rfree);
		if (rval != NULL) {
		    Buf_AddBytes(buf, strlen(rval), (Byte *) rval);
		    if (rfree)
			free(rval);
		}
		tstr += rlen - 1;
	    }
	    else
		Buf_AddByte(buf, (Byte) *tstr);
	}
	if (*tstr == ':') {
	    haveModifier = TRUE;
	} else if (*tstr != '\0') {
	    haveModifier = FALSE;
	} else {
	    /*
	     * If we never did find the end character, return NULL
	     * right now, setting the length to be the distance to
	     * the end of the string, since that's what make does.
	     */
	    *lengthPtr = tstr - str;
	    return (var_Error);
	}
	*WR(tstr) = '\0';
	Buf_AddByte(buf, (Byte) '\0');
	str = Buf_GetAll(buf, (int *) NULL);
	vlen = strlen(str);

	v = VarFind(str, ctxt, FIND_ENV | FIND_GLOBAL | FIND_CMD);
	if ((v == (Var *)NIL) && (ctxt != VAR_CMD) && (ctxt != VAR_GLOBAL) &&
	    (vlen == 2) && (str[1] == 'F' || str[1] == 'D'))
	{
	    /*
	     * Check for bogus D and F forms of local variables since we're
	     * in a local context and the name is the right length.
	     */
	    switch(*str) {
		case '@':
		case '%':
		case '*':
		case '!':
		case '>':
		case '<':
		{
		    char    vname[2];
		    char    *val;

		    /*
		     * Well, it's local -- go look for it.
		     */
		    vname[0] = *str;
		    vname[1] = '\0';
		    v = VarFind(vname, ctxt, 0);

		    if (v != (Var *)NIL) {
			/*
			 * No need for nested expansion or anything, as we're
			 * the only one who sets these things and we sure don't
			 * but nested invocations in them...
			 */
			val = (char *)Buf_GetAll(v->val, (int *)NULL);

			if (str[1] == 'D') {
			    val = VarModify(ctxt, &parsestate, val, VarHead,
					    (ClientData)0);
			} else {
			    val = VarModify(ctxt, &parsestate, val, VarTail,
					    (ClientData)0);
			}
			/*
			 * Resulting string is dynamically allocated, so
			 * tell caller to free it.
			 */
			*freePtr = TRUE;
			*lengthPtr = tstr-start+1;
			*WR(tstr) = endc;
			Buf_Destroy(buf, TRUE);
			return(val);
		    }
		    break;
		}
	    }
	}

	if (v == (Var *)NIL) {
	    if (((vlen == 1) ||
		 (((vlen == 2) && (str[1] == 'F' ||
					 str[1] == 'D')))) &&
		((ctxt == VAR_CMD) || (ctxt == VAR_GLOBAL)))
	    {
		/*
		 * If substituting a local variable in a non-local context,
		 * assume it's for dynamic source stuff. We have to handle
		 * this specially and return the longhand for the variable
		 * with the dollar sign escaped so it makes it back to the
		 * caller. Only four of the local variables are treated
		 * specially as they are the only four that will be set
		 * when dynamic sources are expanded.
		 */
		switch (*str) {
		    case '@':
		    case '%':
		    case '*':
		    case '!':
			dynamic = TRUE;
			break;
		}
	    } else if ((vlen > 2) && (*str == '.') &&
		       isupper((unsigned char) str[1]) &&
		       ((ctxt == VAR_CMD) || (ctxt == VAR_GLOBAL)))
	    {
		int	len;

		len = vlen - 1;
		if ((strncmp(str, ".TARGET", len) == 0) ||
		    (strncmp(str, ".ARCHIVE", len) == 0) ||
		    (strncmp(str, ".PREFIX", len) == 0) ||
		    (strncmp(str, ".MEMBER", len) == 0))
		{
		    dynamic = TRUE;
		}
	    }

	    if (!haveModifier) {
		/*
		 * No modifiers -- have specification length so we can return
		 * now.
		 */
		*lengthPtr = tstr - start + 1;
		*WR(tstr) = endc;
		if (dynamic) {
		    char *pstr = emalloc(*lengthPtr + 1);
		    strncpy(pstr, start, *lengthPtr);
		    pstr[*lengthPtr] = '\0';
		    *freePtr = TRUE;
		    Buf_Destroy(buf, TRUE);
		    return(pstr);
		} else {
		    Buf_Destroy(buf, TRUE);
		    return (err ? var_Error : varNoError);
		}
	    } else {
		/*
		 * Still need to get to the end of the variable specification,
		 * so kludge up a Var structure for the modifications
		 */
		v = emalloc(sizeof(Var));
		v->name = UNCONST(str);
		v->val = Buf_Init(1);
		v->flags = VAR_JUNK;
		Buf_Destroy(buf, FALSE);
	    }
	} else
	    Buf_Destroy(buf, TRUE);
    }


    if (v->flags & VAR_IN_USE) {
	Fatal("Variable %s is recursive.", v->name);
	/*NOTREACHED*/
    } else {
	v->flags |= VAR_IN_USE;
    }
    /*
     * Before doing any modification, we have to make sure the value
     * has been fully expanded. If it looks like recursion might be
     * necessary (there's a dollar sign somewhere in the variable's value)
     * we just call Var_Subst to do any other substitutions that are
     * necessary. Note that the value returned by Var_Subst will have
     * been dynamically-allocated, so it will need freeing when we
     * return.
     */
    nstr = (char *)Buf_GetAll(v->val, (int *)NULL);
    if (strchr (nstr, '$') != (char *)NULL) {
	nstr = Var_Subst(NULL, nstr, ctxt, err);
	*freePtr = TRUE;
    }

    v->flags &= ~VAR_IN_USE;

    /*
     * Now we need to apply any modifiers the user wants applied.
     * These are:
     *  	  :M<pattern>	words which match the given <pattern>.
     *  	  	    	<pattern> is of the standard file
     *  	  	    	wildcarding form.
     *  	  :N<pattern>	words which do not match the given <pattern>.
     *  	  :S<d><pat1><d><pat2><d>[1gW]
     *  	  	    	Substitute <pat2> for <pat1> in the value
     *  	  :C<d><pat1><d><pat2><d>[1gW]
     *  	  	    	Substitute <pat2> for regex <pat1> in the value
     *  	  :H	    	Substitute the head of each word
     *  	  :T	    	Substitute the tail of each word
     *  	  :E	    	Substitute the extension (minus '.') of
     *  	  	    	each word
     *  	  :R	    	Substitute the root of each word
     *  	  	    	(pathname minus the suffix).
     *		  :O		("Order") Alphabeticaly sort words in variable.
     *		  :Ox		("intermiX") Randomize words in variable.
     *		  :u		("uniq") Remove adjacent duplicate words.
     *		  :tu		Converts the variable contents to uppercase.
     *		  :tl		Converts the variable contents to lowercase.
     *		  :ts[c]	Sets varSpace - the char used to
     *				separate words to 'c'. If 'c' is
     *				omitted then no separation is used.
     *		  :tW		Treat the variable contents as a single
     *				word, even if it contains spaces.
     *				(Mnemonic: one big 'W'ord.)
     *		  :tw		Treat the variable contents as multiple
     *				space-separated words.
     *				(Mnemonic: many small 'w'ords.)
     *		  :[index]	Select a single word from the value.
     *		  :[start..end]	Select multiple words from the value.
     *		  :[*] or :[0]	Select the entire value, as a single
     *				word.  Equivalent to :tW.
     *		  :[@]		Select the entire value, as multiple
     *				words.	Undoes the effect of :[*].
     *				Equivalent to :tw.
     *		  :[#]		Returns the number of words in the value.
     *
     *		  :?<true-value>:<false-value>
     *				If the variable evaluates to true, return
     *				true value, else return the second value.
     *	    	  :lhs=rhs  	Like :S, but the rhs goes to the end of
     *	    	    	    	the invocation.
     *		  :sh		Treat the current value as a command
     *				to be run, new value is its output.
     * The following added so we can handle ODE makefiles.
     *		  :@<tmpvar>@<newval>@
     *				Assign a temporary local variable <tmpvar>
     *				to the current value of each word in turn
     *				and replace each word with the result of
     *				evaluating <newval>
     *		  :D<newval>	Use <newval> as value if variable defined
     *		  :U<newval>	Use <newval> as value if variable undefined
     *		  :L		Use the name of the variable as the value.
     *		  :P		Use the path of the node that has the same
     *				name as the variable as the value.  This
     *				basically includes an implied :L so that
     *				the common method of refering to the path
     *				of your dependent 'x' in a rule is to use
     *				the form '${x:P}'.
     *		  :!<cmd>!	Run cmd much the same as :sh run's the
     *				current value of the variable.
     * The ::= modifiers, actually assign a value to the variable.
     * Their main purpose is in supporting modifiers of .for loop
     * iterators and other obscure uses.  They always expand to
     * nothing.  In a target rule that would otherwise expand to an
     * empty line they can be preceded with @: to keep make happy.
     * Eg.
     *
     * foo:	.USE
     * .for i in ${.TARGET} ${.TARGET:R}.gz
     * 		@: ${t::=$i}
     *		@echo blah ${t:T}
     * .endfor
     *
     *		  ::=<str>	Assigns <str> as the new value of variable.
     *		  ::?=<str>	Assigns <str> as value of variable if
     *				it was not already set.
     *		  ::+=<str>	Appends <str> to variable.
     *		  ::!=<cmd>	Assigns output of <cmd> as the new value of
     *				variable.
     */
    if ((nstr != (char *)NULL) && haveModifier) {
	/*
	 * Skip initial colon while putting it back.
	 */
	*WR(tstr) = ':';
	tstr++;
	delim = '\0';

	while (*tstr && *tstr != endc) {
	    char	*newStr;    /* New value to return */
	    char	termc;	    /* Character which terminated scan */

	    if (DEBUG(VAR)) {
		printf("Applying :%c to \"%s\"\n", *tstr, nstr);
	    }
	    newStr = var_Error;
	    switch (*tstr) {
	        case ':':
		{
		if (tstr[1] == '=' ||
		    (tstr[2] == '=' &&
		     (tstr[1] == '!' || tstr[1] == '+' || tstr[1] == '?'))) {
		    /*
		     * "::=", "::!=", "::+=", or "::?="
		     */
		    GNode *v_ctxt;		/* context where v belongs */
		    const char *emsg;
		    char *sv_name;
		    VarPattern	pattern;
		    int	how;

		    v_ctxt = ctxt;
		    sv_name = NULL;
		    ++tstr;
		    if (v->flags & VAR_JUNK) {
			/*
			 * We need to strdup() it incase
			 * VarGetPattern() recurses.
			 */
			sv_name = v->name;
			v->name = strdup(v->name);
		    } else if (ctxt != VAR_GLOBAL) {
			if (VarFind(v->name, ctxt, 0) == (Var *)NIL)
			    v_ctxt = VAR_GLOBAL;
		    }

		    switch ((how = *tstr)) {
		    case '+':
		    case '?':
		    case '!':
			cp = &tstr[2];
			break;
		    default:
			cp = ++tstr;
			break;
		    }
			/* XXX: appease vi sm: '{' */
		    delim = '}';
		    pattern.flags = 0;

		    pattern.rhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim, NULL,
						     &pattern.rightLen,
						     NULL);
		    if (v->flags & VAR_JUNK) {
			/* restore original name */
			free(v->name);
			v->name = sv_name;
		    }
		    if (pattern.rhs == NULL)
			goto cleanup;

		    termc = *--cp;
		    delim = '\0';

		    switch (how) {
		    case '+':
			Var_Append(v->name, pattern.rhs, v_ctxt);
			break;
		    case '!':
			newStr = Cmd_Exec(pattern.rhs, &emsg);
			if (emsg)
			    Error(emsg, nstr);
			else
			   Var_Set(v->name, newStr,  v_ctxt, 0);
			if (newStr)
			    free(newStr);
			break;
		    case '?':
			if ((v->flags & VAR_JUNK) == 0)
			    break;
			/* FALLTHROUGH */
		    default:
			Var_Set(v->name, pattern.rhs, v_ctxt, 0);
			break;
		    }
		    free(UNCONST(pattern.rhs));
		    newStr = var_Error;
		    break;
		}
		goto default_case; /* "::<unrecognised>" */
		}
	        case '@':
		{
		    VarLoop_t	loop;
		    int flags = VAR_NOSUBST;

		    cp = ++tstr;
		    delim = '@';
		    if ((loop.tvar = VarGetPattern(ctxt, &parsestate, err,
						   &cp, delim,
						   &flags, &loop.tvarLen,
						   NULL)) == NULL)
			goto cleanup;

		    if ((loop.str = VarGetPattern(ctxt, &parsestate, err,
						  &cp, delim,
						  &flags, &loop.strLen,
						  NULL)) == NULL)
			goto cleanup;

		    termc = *cp;
		    delim = '\0';

		    loop.err = err;
		    loop.ctxt = ctxt;
		    newStr = VarModify(ctxt, &parsestate, nstr, VarLoopExpand,
				       (ClientData)&loop);
		    free(loop.tvar);
		    free(loop.str);
		    break;
		}
	        case 'D':
	        case 'U':
		{
		    Buffer  buf;    	/* Buffer for patterns */
		    int	    wantit;	/* want data in buffer */

		    /*
		     * Pass through tstr looking for 1) escaped delimiters,
		     * '$'s and backslashes (place the escaped character in
		     * uninterpreted) and 2) unescaped $'s that aren't before
		     * the delimiter (expand the variable substitution).
		     * The result is left in the Buffer buf.
		     */
		    buf = Buf_Init(0);
		    for (cp = tstr + 1;
			 *cp != endc && *cp != ':' && *cp != '\0';
			 cp++) {
			if ((*cp == '\\') &&
			    ((cp[1] == ':') ||
			     (cp[1] == '$') ||
			     (cp[1] == endc) ||
			     (cp[1] == '\\')))
			{
			    Buf_AddByte(buf, (Byte) cp[1]);
			    cp++;
			} else if (*cp == '$') {
			    /*
			     * If unescaped dollar sign, assume it's a
			     * variable substitution and recurse.
			     */
			    char    *cp2;
			    int	    len;
			    Boolean freeIt;

			    cp2 = Var_Parse(cp, ctxt, err, &len, &freeIt);
			    Buf_AddBytes(buf, strlen(cp2), (Byte *) cp2);
			    if (freeIt)
				free(cp2);
			    cp += len - 1;
			} else {
			    Buf_AddByte(buf, (Byte) *cp);
			}
		    }
		    Buf_AddByte(buf, (Byte) '\0');

		    termc = *cp;

		    if (*tstr == 'U')
			wantit = ((v->flags & VAR_JUNK) != 0);
		    else
			wantit = ((v->flags & VAR_JUNK) == 0);
		    if ((v->flags & VAR_JUNK) != 0)
			v->flags |= VAR_KEEP;
		    if (wantit) {
			newStr = (char *)Buf_GetAll(buf, (int *)NULL);
			Buf_Destroy(buf, FALSE);
		    } else {
			newStr = nstr;
			Buf_Destroy(buf, TRUE);
		    }
		    break;
		}
	        case 'L':
		{
		    if ((v->flags & VAR_JUNK) != 0)
			v->flags |= VAR_KEEP;
		    newStr = strdup(v->name);
		    cp = ++tstr;
		    termc = *tstr;
		    break;
		}
	        case 'P':
		{
		    GNode *gn;

		    if ((v->flags & VAR_JUNK) != 0)
			v->flags |= VAR_KEEP;
		    gn = Targ_FindNode(v->name, TARG_NOCREATE);
		    if (gn == NILGNODE || gn->path == NULL)
			newStr = strdup(v->name);
		    else
			newStr = strdup(gn->path);
		    cp = ++tstr;
		    termc = *tstr;
		    break;
		}
	        case '!':
		{
		    const char *emsg;
		    VarPattern 	    pattern;
		    pattern.flags = 0;

		    delim = '!';

		    cp = ++tstr;
		    if ((pattern.rhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim,
						     NULL, &pattern.rightLen,
						     NULL)) == NULL)
			goto cleanup;
		    newStr = Cmd_Exec(pattern.rhs, &emsg);
		    free(UNCONST(pattern.rhs));
		    if (emsg)
			Error(emsg, nstr);
		    termc = *cp;
		    delim = '\0';
		    if (v->flags & VAR_JUNK) {
			v->flags |= VAR_KEEP;
		    }
		    break;
		}
		case '[':
		{
		    /*
		     * Look for the closing ']', recursively
		     * expanding any embedded variables.
		     *
		     * estr is a pointer to the expanded result,
		     * which we must free().
		     */
		    char *estr;

		    cp = tstr+1; /* point to char after '[' */
		    delim = ']'; /* look for closing ']' */
		    estr = VarGetPattern(ctxt, &parsestate,
					 err, &cp, delim,
					 NULL, NULL, NULL);
		    if (estr == NULL)
			goto cleanup; /* report missing ']' */
		    /* now cp points just after the closing ']' */
		    delim = '\0';
		    if (cp[0] != ':' && cp[0] != endc) {
			/* Found junk after ']' */
			free(estr);
			goto bad_modifier;
		    }
		    if (estr[0] == '\0') {
			/* Found empty square brackets in ":[]". */
			free(estr);
			goto bad_modifier;
		    } else if (estr[0] == '#' && estr[1] == '\0') {
			/* Found ":[#]" */

			/*
			 * We will need enough space for the decimal
			 * representation of an int.  We calculate the
			 * space needed for the octal representation,
			 * and add enough slop to cope with a '-' sign
			 * (which should never be needed) and a '\0'
			 * string terminator.
			 */
			 int newStrSize =
				 (sizeof(int) * CHAR_BIT + 2) / 3 + 2;

			newStr = emalloc(newStrSize);
			if (parsestate.oneBigWord) {
				strncpy(newStr, "1", newStrSize);
			} else {
			    /* XXX: brk_string() is a rather expensive
			     * way of counting words. */
			    char **av;
			    char *as;
			    int ac;

			    av = brk_string(nstr, &ac, FALSE, &as);
			    snprintf(newStr, newStrSize,  "%d", ac);
			    free(as);
			    free(av);
			}
			termc = *cp;
			free(estr);
			break;
		    } else if (estr[0] == '*' && estr[1] == '\0') {
			/* Found ":[*]" */
			parsestate.oneBigWord = TRUE;
			newStr = nstr;
			termc = *cp;
			free(estr);
			break;
		    } else if (estr[0] == '@' && estr[1] == '\0') {
			/* Found ":[@]" */
			parsestate.oneBigWord = FALSE;
			newStr = nstr;
			termc = *cp;
			free(estr);
			break;
		    } else {
			/*
			 * We expect estr to contain a single
			 * integer for :[N], or two integers
			 * separated by ".." for :[start..end].
			 */
			char *ep;

			VarSelectWords_t seldata = { 0, 0 };

			seldata.start = strtol(estr, &ep, 0);
			if (ep == estr) {
			    /* Found junk instead of a number */
			    free(estr);
			    goto bad_modifier;
			} else if (ep[0] == '\0') {
			    /* Found only one integer in :[N] */
			    seldata.end = seldata.start;
			} else if (ep[0] == '.' && ep[1] == '.' &&
				   ep[2] != '\0') {
			    /* Expecting another integer after ".." */
			    ep += 2;
			    seldata.end = strtol(ep, &ep, 0);
			    if (ep[0] != '\0') {
				/* Found junk after ".." */
				free(estr);
				goto bad_modifier;
			    }
			} else {
			    /* Found junk instead of ".." */
			    free(estr);
			    goto bad_modifier;
			}
			/*
			 * Now seldata is properly filled in,
			 * but we still have to check for 0 as
			 * a special case.
			 */
			if (seldata.start == 0 && seldata.end == 0) {
			    /* ":[0]" or perhaps ":[0..0]" */
			    parsestate.oneBigWord = TRUE;
			    newStr = nstr;
			    termc = *cp;
			    free(estr);
			    break;
			} else if (seldata.start == 0 ||
				   seldata.end == 0) {
			    /* ":[0..N]" or ":[N..0]" */
			    free(estr);
			    goto bad_modifier;
			}
			/*
			 * Normal case: select the words
			 * described by seldata.
			 */
			newStr = VarSelectWords(ctxt, &parsestate,
						nstr, &seldata);

			termc = *cp;
			free(estr);
			break;
		    }

		}
	        case 't':
		{
		    cp = tstr + 1;	/* make sure it is set */
		    if (tstr[1] != endc && tstr[1] != ':') {
			if (tstr[1] == 's') {
			    /*
			     * Use the char (if any) at tstr[2]
			     * as the word separator.
			     */
			    VarPattern pattern;

			    if (tstr[2] != endc &&
				(tstr[3] == endc || tstr[3] == ':')) {
				/* ":ts<unrecognised><endc>" or
				 * ":ts<unrecognised>:" */
				parsestate.varSpace = tstr[2];
				cp = tstr + 3;
			    } else if (tstr[2] == endc || tstr[2] == ':') {
				/* ":ts<endc>" or ":ts:" */
				parsestate.varSpace = 0; /* no separator */
				cp = tstr + 2;
			    } else if (tstr[2] == '\\') {
				switch (tstr[3]) {
				case 'n':
				    parsestate.varSpace = '\n';
				    cp = tstr + 4;
				    break;
				case 't':
				    parsestate.varSpace = '\t';
				    cp = tstr + 4;
				    break;
				default:
				    if (isdigit((unsigned char)tstr[3])) {
					char *ep;

					parsestate.varSpace =
						strtoul(&tstr[3], &ep, 0);
					if (*ep != ':' && *ep != endc)
					    goto bad_modifier;
					cp = ep;
				    } else {
					/*
					 * ":ts<backslash><unrecognised>".
					 */
					goto bad_modifier;
				    }
				    break;
				}
			    } else {
				/*
				 * Found ":ts<unrecognised><unrecognised>".
				 */
				goto bad_modifier;
			    }

			    termc = *cp;

			    /*
			     * We cannot be certain that VarModify
			     * will be used - even if there is a
			     * subsequent modifier, so do a no-op
			     * VarSubstitute now to for str to be
			     * re-expanded without the spaces.
			     */
			    pattern.flags = VAR_SUB_ONE;
			    pattern.lhs = pattern.rhs = "\032";
			    pattern.leftLen = pattern.rightLen = 1;

			    newStr = VarModify(ctxt, &parsestate, nstr,
					       VarSubstitute,
					       (ClientData)&pattern);
			} else if (tstr[2] == endc || tstr[2] == ':') {
			    /*
			     * Check for two-character options:
			     * ":tu", ":tl"
			     */
                            if (tstr[1] == 'u' || tstr[1] == 'l') {
                                newStr = VarChangeCase(nstr, (tstr[1] == 'u'));
                                cp = tstr + 2;
                                termc = *cp;
                            } else if (tstr[1] == 'W' || tstr[1] == 'w') {
				parsestate.oneBigWord = (tstr[1] == 'W');
				newStr = nstr;
				cp = tstr + 2;
				termc = *cp;
                            } else {
				/* Found ":t<unrecognised>:" or
				 * ":t<unrecognised><endc>". */
				goto bad_modifier;
			    }
			} else {
			    /*
			     * Found ":t<unrecognised><unrecognised>".
			     */
			    goto bad_modifier;
			}
		    } else {
			/*
			 * Found ":t<endc>" or ":t:".
			 */
			goto bad_modifier;
		    }
		    break;
		}
		case 'N':
		case 'M':
		{
		    char    *pattern;
		    char    *cp2;
		    Boolean copy;
		    int nest;

		    copy = FALSE;
		    nest = 1;
		    /*
		     * In the loop below, ignore ':' unless we are at
		     * (or back to) the original brace level.
		     * XXX This will likely not work right if $() and ${}
		     * are intermixed.
		     */
		    for (cp = tstr + 1;
			 *cp != '\0' && !(*cp == ':' && nest == 1);
			 cp++)
		    {
			if (*cp == '\\' &&
			    (cp[1] == ':' ||
			     cp[1] == endc || cp[1] == startc)) {
			    copy = TRUE;
			    cp++;
			    continue;
			}
			if (*cp == startc)
			    ++nest;
			if (*cp == endc) {
			    --nest;
			    if (nest == 0)
				break;
			}
		    }
		    termc = *cp;
		    *WR(cp) = '\0';
		    if (copy) {
			/*
			 * Need to compress the \:'s out of the pattern, so
			 * allocate enough room to hold the uncompressed
			 * pattern (note that cp started at tstr+1, so
			 * cp - tstr takes the null byte into account) and
			 * compress the pattern into the space.
			 */
			pattern = emalloc(cp - tstr);
			for (cp2 = pattern, cp = tstr + 1;
			     *cp != '\0';
			     cp++, cp2++)
			{
			    if ((*cp == '\\') &&
				(cp[1] == ':' || cp[1] == endc)) {
				    cp++;
			    }
			    *cp2 = *cp;
			}
			*cp2 = '\0';
		    } else {
			pattern = UNCONST(&tstr[1]);
		    }
		    if ((cp2 = strchr(pattern, '$'))) {
			cp2 = pattern;
			pattern = Var_Subst(NULL, cp2, ctxt, err);
			if (copy)
			    free(cp2);
			copy = TRUE;
		    }
		    if (*tstr == 'M' || *tstr == 'm') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarMatch,
					   (ClientData)pattern);
		    } else {
			newStr = VarModify(ctxt, &parsestate, nstr, VarNoMatch,
					   (ClientData)pattern);
		    }
		    if (copy) {
			free(pattern);
		    }
		    break;
		}
		case 'S':
		{
		    VarPattern 	    pattern;
		    Var_Parse_State tmpparsestate;

		    pattern.flags = 0;
		    tmpparsestate = parsestate;
		    delim = tstr[1];
		    tstr += 2;

		    /*
		     * If pattern begins with '^', it is anchored to the
		     * start of the word -- skip over it and flag pattern.
		     */
		    if (*tstr == '^') {
			pattern.flags |= VAR_MATCH_START;
			tstr += 1;
		    }

		    cp = tstr;
		    if ((pattern.lhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim,
						     &pattern.flags,
						     &pattern.leftLen,
						     NULL)) == NULL)
			goto cleanup;

		    if ((pattern.rhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim, NULL,
						     &pattern.rightLen,
						     &pattern)) == NULL)
			goto cleanup;

		    /*
		     * Check for global substitution. If 'g' after the final
		     * delimiter, substitution is global and is marked that
		     * way.
		     */
		    for (;; cp++) {
			switch (*cp) {
			case 'g':
			    pattern.flags |= VAR_SUB_GLOBAL;
			    continue;
			case '1':
			    pattern.flags |= VAR_SUB_ONE;
			    continue;
			case 'W':
			    tmpparsestate.oneBigWord = TRUE;
			    continue;
			}
			break;
		    }

		    termc = *cp;
		    newStr = VarModify(ctxt, &tmpparsestate, nstr,
				       VarSubstitute,
				       (ClientData)&pattern);

		    /*
		     * Free the two strings.
		     */
		    free(UNCONST(pattern.lhs));
		    free(UNCONST(pattern.rhs));
		    delim = '\0';
		    break;
		}
		case '?':
		{
		    VarPattern 	pattern;
		    Boolean	value;

		    /* find ':', and then substitute accordingly */

		    pattern.flags = 0;

		    cp = ++tstr;
		    delim = ':';
		    if ((pattern.lhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim, NULL,
						     &pattern.leftLen,
						     NULL)) == NULL)
			goto cleanup;

			/* '{' or '(' */
		    delim = endc;
		    if ((pattern.rhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim, NULL,
						     &pattern.rightLen,
						     NULL)) == NULL)
			goto cleanup;
			/* XXX: appease vi sm: ')' '}' */

		    termc = *--cp;
		    delim = '\0';
		    if (Cond_EvalExpression(1, v->name, &value, 0)
			== COND_INVALID) {
			Error("Bad conditional expression `%s' in %s?%s:%s",
			      v->name, v->name, pattern.lhs, pattern.rhs);
			goto cleanup;
		    }

		    if (value) {
			newStr = UNCONST(pattern.lhs);
			free(UNCONST(pattern.rhs));
		    } else {
			newStr = UNCONST(pattern.rhs);
			free(UNCONST(pattern.lhs));
		    }
		    if (v->flags & VAR_JUNK) {
			v->flags |= VAR_KEEP;
		    }
		    break;
		}
		case 'Q':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarQuote(nstr);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'T':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarTail,
					   (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'H':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarHead,
					   (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'E':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarSuffix,
					   (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'R':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarRoot,
					   (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'O':
		{
		    char otype;

		    cp = tstr + 1;	/* skip to the rest in any case */
		    if (tstr[1] == endc || tstr[1] == ':') {
			otype = 's';
			termc = *cp;
		    } else if ( (tstr[1] == 'x') &&
		    		(tstr[2] == endc || tstr[2] == ':') ) {
			otype = tstr[1];
			cp = tstr + 2;
			termc = *cp;
		    } else {
			goto bad_modifier;
		    }
		    newStr = VarOrder(nstr, otype);
		    break;
		}
		case 'u':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarUniq(nstr);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
#ifdef SUNSHCMD
		case 's':
		    if (tstr[1] == 'h' && (tstr[2] == endc || tstr[2] == ':')) {
			const char *emsg;
			newStr = Cmd_Exec(nstr, &emsg);
			if (emsg)
			    Error(emsg, nstr);
			cp = tstr + 2;
			termc = *cp;
			break;
		    }
		    goto default_case;
#endif
                default:
		default_case:
		{
#ifdef SYSVVARSUB
		    /*
		     * This can either be a bogus modifier or a System-V
		     * substitution command.
		     */
		    VarPattern      pattern;
		    Boolean         eqFound;

		    pattern.flags = 0;
		    eqFound = FALSE;
		    /*
		     * First we make a pass through the string trying
		     * to verify it is a SYSV-make-style translation:
		     * it must be: <string1>=<string2>)
		     */
		    cp = tstr;
		    cnt = 1;
		    while (*cp != '\0' && cnt) {
			if (*cp == '=') {
			    eqFound = TRUE;
			    /* continue looking for endc */
			}
			else if (*cp == endc)
			    cnt--;
			else if (*cp == startc)
			    cnt++;
			if (cnt)
			    cp++;
		    }
		    if (*cp == endc && eqFound) {

			/*
			 * Now we break this sucker into the lhs and
			 * rhs. We must null terminate them of course.
			 */
			delim='=';
			cp = tstr;
			if ((pattern.lhs = VarGetPattern(ctxt, &parsestate,
				err, &cp, delim, &pattern.flags,
				&pattern.leftLen, NULL)) == NULL)
				goto cleanup;
			delim = endc;
			if ((pattern.rhs = VarGetPattern(ctxt, &parsestate,
				err, &cp, delim, NULL, &pattern.rightLen,
				&pattern)) == NULL)
				goto cleanup;

			/*
			 * SYSV modifications happen through the whole
			 * string. Note the pattern is anchored at the end.
			 */
			termc = *--cp;
			delim = '\0';
			newStr = VarModify(ctxt, &parsestate, nstr,
					   VarSYSVMatch,
					   (ClientData)&pattern);
			free(UNCONST(pattern.lhs));
			free(UNCONST(pattern.rhs));
		    } else
#endif
		    {
			Error("Unknown modifier '%c'", *tstr);
			for (cp = tstr+1;
			     *cp != ':' && *cp != endc && *cp != '\0';
			     cp++)
				 continue;
			termc = *cp;
			newStr = var_Error;
		    }
		}
	    }
	    if (DEBUG(VAR)) {
		printf("Result is \"%s\"\n", newStr);
	    }

	    if (newStr != nstr) {
		if (*freePtr) {
		    free (nstr);
		}
		nstr = newStr;
		if (nstr != var_Error && nstr != varNoError) {
		    *freePtr = TRUE;
		} else {
		    *freePtr = FALSE;
		}
	    }
	    if (termc == '\0') {
		Error("Unclosed variable specification for %s", v->name);
	    } else if (termc == ':') {
		*WR(cp) = termc;
		cp++;
	    } else {
		*WR(cp) = termc;
	    }
	    tstr = cp;
	}
	*lengthPtr = tstr - start + 1;
    } else {
	*lengthPtr = tstr - start + 1;
	*WR(tstr) = endc;
    }

    if (v->flags & VAR_FROM_ENV) {
	Boolean	  destroy = FALSE;

	if (nstr != (char *)Buf_GetAll(v->val, (int *)NULL)) {
	    destroy = TRUE;
	} else {
	    /*
	     * Returning the value unmodified, so tell the caller to free
	     * the thing.
	     */
	    *freePtr = TRUE;
	}
	if (nstr != (char *)Buf_GetAll(v->val, (int *)NULL))
	    Buf_Destroy(v->val, destroy);
	free((Address)v->name);
	free((Address)v);
    } else if (v->flags & VAR_JUNK) {
	/*
	 * Perform any free'ing needed and set *freePtr to FALSE so the caller
	 * doesn't try to free a static pointer.
	 * If VAR_KEEP is also set then we want to keep str as is.
	 */
	if (!(v->flags & VAR_KEEP)) {
	    if (*freePtr) {
		free(nstr);
	    }
	    *freePtr = FALSE;
	    if (dynamic) {
		nstr = emalloc(*lengthPtr + 1);
		strncpy(nstr, start, *lengthPtr);
		nstr[*lengthPtr] = '\0';
		*freePtr = TRUE;
	    } else {
		nstr = var_Error;
	    }
	}
	if (nstr != (char *)Buf_GetAll(v->val, (int *)NULL))
	    Buf_Destroy(v->val, TRUE);
	free((Address)v->name);
	free((Address)v);
    }
    return (nstr);

 bad_modifier:
							/* "{(" */
    Error("Bad modifier `:%.*s' for %s", (int)strcspn(tstr, ":)}"), tstr,
	  v->name);

cleanup:
    *lengthPtr = cp - start + 1;
    if (*freePtr)
	free(nstr);
    if (delim != '\0')
	Error("Unclosed substitution for %s (%c missing)",
	      v->name, delim);
    return (var_Error);
}

/*-
 *-----------------------------------------------------------------------
 * Var_Subst  --
 *	Substitute for all variables in the given string in the given context
 *	If undefErr is TRUE, Parse_Error will be called when an undefined
 *	variable is encountered.
 *
 * Input:
 *	var		Named variable || NULL for all
 *	str		the string which to substitute
 *	ctxt		the context wherein to find variables
 *	undefErr	TRUE if undefineds are an error
 *
 * Results:
 *	The resulting string.
 *
 * Side Effects:
 *	None. The old string must be freed by the caller
 *-----------------------------------------------------------------------
 */
char *
Var_Subst(const char *var, const char *str, GNode *ctxt, Boolean undefErr)
{
    Buffer  	  buf;	    	    /* Buffer for forming things */
    char    	  *val;		    /* Value to substitute for a variable */
    int	    	  length;   	    /* Length of the variable invocation */
    Boolean	  trailingBslash;   /* variable ends in \ */
    Boolean 	  doFree;   	    /* Set true if val should be freed */
    static Boolean errorReported;   /* Set true if an error has already
				     * been reported to prevent a plethora
				     * of messages when recursing */

    buf = Buf_Init(MAKE_BSIZE);
    errorReported = FALSE;
    trailingBslash = FALSE;

    while (*str) {
	if (*str == '\n' && trailingBslash)
	    Buf_AddByte(buf, ' ');
	if (var == NULL && (*str == '$') && (str[1] == '$')) {
	    /*
	     * A dollar sign may be escaped either with another dollar sign.
	     * In such a case, we skip over the escape character and store the
	     * dollar sign into the buffer directly.
	     */
	    str++;
	    Buf_AddByte(buf, (Byte)*str);
	    str++;
	} else if (*str != '$') {
	    /*
	     * Skip as many characters as possible -- either to the end of
	     * the string or to the next dollar sign (variable invocation).
	     */
	    const char  *cp;

	    for (cp = str++; *str != '$' && *str != '\0'; str++)
		continue;
	    Buf_AddBytes(buf, str - cp, (const Byte *)cp);
	} else {
	    if (var != NULL) {
		int expand;
		for (;;) {
		    if (str[1] != '(' && str[1] != '{') {
			if (str[1] != *var || strlen(var) > 1) {
			    Buf_AddBytes(buf, 2, (const Byte *)str);
			    str += 2;
			    expand = FALSE;
			}
			else
			    expand = TRUE;
			break;
		    }
		    else {
			const char *p;

			/*
			 * Scan up to the end of the variable name.
			 */
			for (p = &str[2]; *p &&
			     *p != ':' && *p != ')' && *p != '}'; p++)
			    if (*p == '$')
				break;
			/*
			 * A variable inside the variable. We cannot expand
			 * the external variable yet, so we try again with
			 * the nested one
			 */
			if (*p == '$') {
			    Buf_AddBytes(buf, p - str, (const Byte *)str);
			    str = p;
			    continue;
			}

			if (strncmp(var, str + 2, p - str - 2) != 0 ||
			    var[p - str - 2] != '\0') {
			    /*
			     * Not the variable we want to expand, scan
			     * until the next variable
			     */
			    for (;*p != '$' && *p != '\0'; p++)
				continue;
			    Buf_AddBytes(buf, p - str, (const Byte *)str);
			    str = p;
			    expand = FALSE;
			}
			else
			    expand = TRUE;
			break;
		    }
		}
		if (!expand)
		    continue;
	    }

	    val = Var_Parse(str, ctxt, undefErr, &length, &doFree);

	    /*
	     * When we come down here, val should either point to the
	     * value of this variable, suitably modified, or be NULL.
	     * Length should be the total length of the potential
	     * variable invocation (from $ to end character...)
	     */
	    if (val == var_Error || val == varNoError) {
		/*
		 * If performing old-time variable substitution, skip over
		 * the variable and continue with the substitution. Otherwise,
		 * store the dollar sign and advance str so we continue with
		 * the string...
		 */
		if (oldVars) {
		    str += length;
		} else if (undefErr) {
		    /*
		     * If variable is undefined, complain and skip the
		     * variable. The complaint will stop us from doing anything
		     * when the file is parsed.
		     */
		    if (!errorReported) {
			Parse_Error(PARSE_FATAL,
				     "Undefined variable \"%.*s\"",length,str);
		    }
		    str += length;
		    errorReported = TRUE;
		} else {
		    Buf_AddByte (buf, (Byte)*str);
		    str += 1;
		}
	    } else {
		/*
		 * We've now got a variable structure to store in. But first,
		 * advance the string pointer.
		 */
		str += length;

		/*
		 * Copy all the characters from the variable value straight
		 * into the new string.
		 */
		length = strlen(val);
		Buf_AddBytes(buf, length, (Byte *)val);
		trailingBslash = length > 0 && val[length - 1] == '\\';
		if (doFree) {
		    free ((Address)val);
		}
	    }
	}
    }

    Buf_AddByte (buf, '\0');
    val = (char *)Buf_GetAll (buf, (int *)NULL);
    Buf_Destroy(buf, FALSE);
    return (val);
}

/*-
 *-----------------------------------------------------------------------
 * Var_GetTail --
 *	Return the tail from each of a list of words. Used to set the
 *	System V local variables.
 *
 * Input:
 *	file		Filename to modify
 *
 * Results:
 *	The resulting string.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
#if 0
char *
Var_GetTail(char *file)
{
    return(VarModify(file, VarTail, (ClientData)0));
}

/*-
 *-----------------------------------------------------------------------
 * Var_GetHead --
 *	Find the leading components of a (list of) filename(s).
 *	XXX: VarHead does not replace foo by ., as (sun) System V make
 *	does.
 *
 * Input:
 *	file		Filename to manipulate
 *
 * Results:
 *	The leading components.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
char *
Var_GetHead(char *file)
{
    return(VarModify(file, VarHead, (ClientData)0));
}
#endif

/*-
 *-----------------------------------------------------------------------
 * Var_Init --
 *	Initialize the module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The VAR_CMD and VAR_GLOBAL contexts are created
 *-----------------------------------------------------------------------
 */
void
Var_Init(void)
{
    VAR_GLOBAL = Targ_NewGN("Global");
    VAR_CMD = Targ_NewGN("Command");

}


void
Var_End(void)
{
}


/****************** PRINT DEBUGGING INFO *****************/
static void
VarPrintVar(ClientData vp)
{
    Var    *v = (Var *) vp;
    printf ("%-16s = %s\n", v->name, (char *) Buf_GetAll(v->val, (int *)NULL));
}

/*-
 *-----------------------------------------------------------------------
 * Var_Dump --
 *	print all variables in a context
 *-----------------------------------------------------------------------
 */
void
Var_Dump(GNode *ctxt)
{
    Hash_Search search;
    Hash_Entry *h;

    for (h = Hash_EnumFirst(&ctxt->context, &search);
	 h != NULL;
	 h = Hash_EnumNext(&search)) {
	    VarPrintVar(Hash_GetValue(h));
    }
}
/* end var.c */

/* begin main.c */
/*	$NetBSD: main.c,v 1.111 2005/06/24 02:53:27 lukem Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: main.c,v 1.111 2005/06/24 02:53:27 lukem Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
__COPYRIGHT("@(#) Copyright (c) 1988, 1989, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
#endif /* not lint */

#ifndef lint
#if 0
static char sccsid[] = "@(#)main.c	8.3 (Berkeley) 3/19/94";
#else
__RCSID("$NetBSD: main.c,v 1.111 2005/06/24 02:53:27 lukem Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * main.c --
 *	The main file for this entire program. Exit routines etc
 *	reside here.
 *
 * Utility functions defined in this file:
 *	Main_ParseArgLine	Takes a line of arguments, breaks them and
 *				treats them as if they were given when first
 *				invoked. Used by the parse module to implement
 *				the .MFLAGS target.
 *
 *	Error			Print a tagged error message. The global
 *				MAKE variable must have been defined. This
 *				takes a format string and two optional
 *				arguments for it.
 *
 *	Fatal			Print an error message and exit. Also takes
 *				a format string and two arguments.
 *
 *	Punt			Aborts all jobs and exits with a message. Also
 *				takes a format string and two arguments.
 *
 *	Finish			Finish things up by printing the number of
 *				errors which occurred, as passed to it, and
 *				exiting.
 */

/* <<main.c includes>> */

#ifndef	DEFMAXLOCAL
#define	DEFMAXLOCAL DEFMAXJOBS
#endif	/* DEFMAXLOCAL */

Lst			create;		/* Targets to be made */
time_t			now;		/* Time at start of make */
GNode			*DEFAULT;	/* .DEFAULT node */
Boolean			allPrecious;	/* .PRECIOUS given on line by itself */

static Lst		makefiles;	/* ordered list of makefiles to read */
static Boolean		printVars;	/* print value of one or more vars */
static Lst		variables;	/* list of variables to print */
Boolean			compatMake;	/* -B argument */
Boolean			debug;		/* -d flag */
Boolean			noExecute;	/* -n flag */
Boolean			noRecursiveExecute;	/* -N flag */
Boolean			keepgoing;	/* -k flag */
Boolean			queryFlag;	/* -q flag */
Boolean			touchFlag;	/* -t flag */
Boolean			usePipes;	/* !-P flag */
Boolean			ignoreErrors;	/* -i flag */
Boolean			beSilent;	/* -s flag */
Boolean			oldVars;	/* variable substitution style */
Boolean			checkEnvFirst;	/* -e flag */
Boolean			parseWarnFatal;	/* -W flag */
Boolean			jobServer; 	/* -J flag */
Boolean			varNoExportEnv;	/* -X flag */
static Boolean		jobsRunning;	/* TRUE if the jobs might be running */
static const char *	tracefile;
static char *		Check_Cwd_av(int, char **, int);
static void		MainParseArgs(int, char **);
static Boolean		ReadMakefile(ClientData);
static void		usage(void);

static char curdir[MAXPATHLEN + 1];	/* startup directory */
static char objdir[MAXPATHLEN + 1];	/* where we chdir'ed to */
char *progname;				/* the program name */

Boolean forceJobs = FALSE;

extern Lst parseIncPath;

/*-
 * MainParseArgs --
 *	Parse a given argument vector. Called from main() and from
 *	Main_ParseArgLine() when the .MAKEFLAGS target is used.
 *
 *	XXX: Deal with command line overriding .MAKEFLAGS in makefile
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Various global and local flags will be set depending on the flags
 *	given
 */
static void
MainParseArgs(int argc, char **argv)
{
	char *p;
	int c;
	int arginc;
	char *argvalue;
	const char *getopt_def;
	char *optscan;
	Boolean inOption, dashDash = FALSE;

#define OPTFLAGS "BC:D:I:J:NPST:V:WXd:ef:ij:knqst"
#undef optarg
#define optarg argvalue
/* Can't actually use getopt(3) because rescanning is not portable */

	getopt_def = OPTFLAGS;
rearg:
	inOption = FALSE;
	optscan = NULL;
	while(argc > 1) {
		char *getopt_spec;
		if(!inOption)
			optscan = argv[1];
		c = *optscan++;
		arginc = 0;
		if(inOption) {
			if(c == '\0') {
				++argv;
				--argc;
				inOption = FALSE;
				continue;
			}
		} else {
			if (c != '-' || dashDash)
				break;
			inOption = TRUE;
			c = *optscan++;
		}
		/* '-' found at some earlier point */
		getopt_spec = strchr(getopt_def, c);
		if(c != '\0' && getopt_spec != NULL && getopt_spec[1] == ':') {
			/* -<something> found, and <something> should have an arg */
			inOption = FALSE;
			arginc = 1;
			argvalue = optscan;
			if(*argvalue == '\0') {
				if (argc < 3) {
					(void)fprintf(stderr,
					    "%s: option requires "
					    "an argument -- %c\n",
					    progname, c);
					usage();
				}
				argvalue = argv[2];
				arginc = 2;
			}
		} else {
			argvalue = NULL;
		}
		switch(c) {
		case '\0':
			arginc = 1;
			inOption = FALSE;
			break;
		case 'B':
			compatMake = TRUE;
			Var_Append(MAKEFLAGS, "-B", VAR_GLOBAL);
			break;
		case 'C':
			if (chdir(optarg)) {
				(void)fprintf(stderr, "%s: %s: %s.\n",
					      progname, optarg,
					      strerror(errno));
				usage();
			}
			break;
		case 'D':
			Var_Set(optarg, "1", VAR_GLOBAL, 0);
			Var_Append(MAKEFLAGS, "-D", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'I':
			Parse_AddIncludeDir(optarg);
			Var_Append(MAKEFLAGS, "-I", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'J':
			if (sscanf(optarg, "%d,%d", &job_pipe[0], &job_pipe[1]) != 2) {
			    /* backslash to avoid trigraph ??) */
			    (void)fprintf(stderr,
				"%s: internal error -- J option malformed (%s?\?)\n",
				progname, optarg);
				usage();
			}
			if ((fcntl(job_pipe[0], F_GETFD, 0) < 0) ||
			    (fcntl(job_pipe[1], F_GETFD, 0) < 0)) {
#if 0
			    (void)fprintf(stderr,
				"%s: warning -- J descriptors were closed!\n",
				progname);
#endif
			    job_pipe[0] = -1;
			    job_pipe[1] = -1;
			    compatMake = TRUE;
			} else {
			    Var_Append(MAKEFLAGS, "-J", VAR_GLOBAL);
			    Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			    jobServer = TRUE;
			}
			break;
		case 'N':
			noExecute = TRUE;
			noRecursiveExecute = TRUE;
			Var_Append(MAKEFLAGS, "-N", VAR_GLOBAL);
			break;
		case 'P':
			usePipes = FALSE;
			Var_Append(MAKEFLAGS, "-P", VAR_GLOBAL);
			break;
		case 'S':
			keepgoing = FALSE;
			Var_Append(MAKEFLAGS, "-S", VAR_GLOBAL);
			break;
		case 'T':
			tracefile = estrdup(optarg);
			Var_Append(MAKEFLAGS, "-T", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'V':
			printVars = TRUE;
			(void)Lst_AtEnd(variables, (ClientData)optarg);
			Var_Append(MAKEFLAGS, "-V", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'W':
			parseWarnFatal = TRUE;
			break;
		case 'X':
			varNoExportEnv = TRUE;
			Var_Append(MAKEFLAGS, "-X", VAR_GLOBAL);
			break;
		case 'd': {
			char *modules = optarg;

			for (; *modules; ++modules)
				switch (*modules) {
				case 'A':
					debug = ~0;
					break;
				case 'a':
					debug |= DEBUG_ARCH;
					break;
				case 'c':
					debug |= DEBUG_COND;
					break;
				case 'd':
					debug |= DEBUG_DIR;
					break;
				case 'e':
					debug |= DEBUG_ERROR;
					break;
				case 'f':
					debug |= DEBUG_FOR;
					break;
				case 'g':
					if (modules[1] == '1') {
						debug |= DEBUG_GRAPH1;
						++modules;
					}
					else if (modules[1] == '2') {
						debug |= DEBUG_GRAPH2;
						++modules;
					}
					else if (modules[1] == '3') {
						debug |= DEBUG_GRAPH3;
						++modules;
					}
					break;
				case 'j':
					debug |= DEBUG_JOB;
					break;
				case 'm':
					debug |= DEBUG_MAKE;
					break;
				case 'n':
					debug |= DEBUG_SCRIPT;
					break;
				case 's':
					debug |= DEBUG_SUFF;
					break;
				case 't':
					debug |= DEBUG_TARG;
					break;
				case 'v':
					debug |= DEBUG_VAR;
					break;
				case 'x':
					debug |= DEBUG_SHELL;
					break;
				default:
					(void)fprintf(stderr,
				"%s: illegal argument to d option -- %c\n",
					    progname, *modules);
					usage();
				}
			Var_Append(MAKEFLAGS, "-d", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		}
		case 'e':
			checkEnvFirst = TRUE;
			Var_Append(MAKEFLAGS, "-e", VAR_GLOBAL);
			break;
		case 'f':
			(void)Lst_AtEnd(makefiles, (ClientData)optarg);
			break;
		case 'i':
			ignoreErrors = TRUE;
			Var_Append(MAKEFLAGS, "-i", VAR_GLOBAL);
			break;
		case 'j':
			forceJobs = TRUE;
			maxJobs = strtol(optarg, &p, 0);
			if (*p != '\0' || maxJobs < 1) {
				(void) fprintf(stderr, "%s: illegal argument to -j -- must be positive integer!\n",
				    progname);
				exit(1);
			}
			maxLocal = maxJobs;
			Var_Append(MAKEFLAGS, "-j", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'k':
			keepgoing = TRUE;
			Var_Append(MAKEFLAGS, "-k", VAR_GLOBAL);
			break;
		case 'n':
			noExecute = TRUE;
			Var_Append(MAKEFLAGS, "-n", VAR_GLOBAL);
			break;
		case 'q':
			queryFlag = TRUE;
			/* Kind of nonsensical, wot? */
			Var_Append(MAKEFLAGS, "-q", VAR_GLOBAL);
			break;
		case 's':
			beSilent = TRUE;
			Var_Append(MAKEFLAGS, "-s", VAR_GLOBAL);
			break;
		case 't':
			touchFlag = TRUE;
			Var_Append(MAKEFLAGS, "-t", VAR_GLOBAL);
			break;
		case '-':
			dashDash = TRUE;
			break;
		default:
		case '?':
			usage();
		}
		argv += arginc;
		argc -= arginc;
	}

	oldVars = TRUE;

	/*
	 * See if the rest of the arguments are variable assignments and
	 * perform them if so. Else take them to be targets and stuff them
	 * on the end of the "create" list.
	 */
	for (; argc > 1; ++argv, --argc)
		if (Parse_IsVar(argv[1])) {
			Parse_DoVar(argv[1], VAR_CMD);
		} else {
			if (!*argv[1])
				Punt("illegal (null) argument.");
			if (*argv[1] == '-' && !dashDash)
				goto rearg;
			(void)Lst_AtEnd(create, (ClientData)estrdup(argv[1]));
		}
}

/*-
 * Main_ParseArgLine --
 *  	Used by the parse module when a .MFLAGS or .MAKEFLAGS target
 *	is encountered and by main() when reading the .MAKEFLAGS envariable.
 *	Takes a line of arguments and breaks it into its
 * 	component words and passes those words and the number of them to the
 *	MainParseArgs function.
 *	The line should have all its leading whitespace removed.
 *
 * Input:
 *	line		Line to fracture
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Only those that come from the various arguments.
 */
void
Main_ParseArgLine(char *line)
{
	char **argv;			/* Manufactured argument vector */
	int argc;			/* Number of arguments in argv */
	char *args;			/* Space used by the args */
	char *buf, *p1;
	char *argv0 = Var_Value(".MAKE", VAR_GLOBAL, &p1);
	size_t len;

	if (line == NULL)
		return;
	for (; *line == ' '; ++line)
		continue;
	if (!*line)
		return;

	buf = emalloc(len = strlen(line) + strlen(argv0) + 2);
	(void)snprintf(buf, len, "%s %s", argv0, line);
	if (p1)
		free(p1);

	argv = brk_string(buf, &argc, TRUE, &args);
	free(buf);
	MainParseArgs(argc, argv);

	free(args);
	free(argv);
}

Boolean
Main_SetObjdir(const char *path)
{
	struct stat sb;
	char *p = NULL;
	char buf[MAXPATHLEN + 1];
	Boolean rc = FALSE;

	/* expand variable substitutions */
	if (strchr(path, '$') != 0) {
		snprintf(buf, MAXPATHLEN, "%s", path);
		path = p = Var_Subst(NULL, buf, VAR_GLOBAL, 0);
	}

	if (path[0] != '/') {
		snprintf(buf, MAXPATHLEN, "%s/%s", curdir, path);
		path = buf;
	}

	/* look for the directory and try to chdir there */
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		if (chdir(path)) {
			(void)fprintf(stderr, "make warning: %s: %s.\n",
				      path, strerror(errno));
		} else {
			strncpy(objdir, path, MAXPATHLEN);
			Var_Set(".OBJDIR", objdir, VAR_GLOBAL, 0);
			setenv("PWD", objdir, 1);
			Dir_InitDot();
			rc = TRUE;
		}
	}

	if (p)
		free(p);
	return rc;
}


/*-
 * main --
 *	The main function, for obvious reasons. Initializes variables
 *	and a few modules, then parses the arguments give it in the
 *	environment and on the command line. Reads the system makefile
 *	followed by either Makefile, makefile or the file given by the
 *	-f argument. Sets the .MAKEFLAGS PMake variable based on all the
 *	flags it has received by then uses either the Make or the Compat
 *	module to create the initial list of targets.
 *
 * Results:
 *	If -q was given, exits -1 if anything was out-of-date. Else it exits
 *	0.
 *
 * Side Effects:
 *	The program exits when done. Targets are created. etc. etc. etc.
 */
int
main(int argc, char **argv)
{
	Lst targs;	/* target nodes to create -- passed to Make_Init */
	Boolean outOfDate = TRUE; 	/* FALSE if all targets up to date */
	struct stat sb, sa;
	char *p1, *path, *pwd;
	char mdpath[MAXPATHLEN];
	char *cp = NULL;
					/* avoid faults on read-only strings */
	struct timeval rightnow;		/* to initialize random seed */

	/*
	 * Set the seed to produce a different random sequences
	 * on each program execution.
	 */
	gettimeofday(&rightnow, NULL);
	srandom(rightnow.tv_sec + rightnow.tv_usec);

	if ((progname = strrchr(argv[0], '/')) != NULL)
		progname++;
	else
		progname = argv[0];
#ifdef RLIMIT_NOFILE
	/*
	 * get rid of resource limit on file descriptors
	 */
	{
		struct rlimit rl;
		if (getrlimit(RLIMIT_NOFILE, &rl) != -1 &&
		    rl.rlim_cur != rl.rlim_max) {
			rl.rlim_cur = rl.rlim_max;
			(void) setrlimit(RLIMIT_NOFILE, &rl);
		}
	}
#endif
	/*
	 * Find where we are and take care of PWD for the automounter...
	 * All this code is so that we know where we are when we start up
	 * on a different machine with pmake.
	 */
	if (getcwd(curdir, MAXPATHLEN) == NULL) {
		(void)fprintf(stderr, "%s: %s.\n", progname, strerror(errno));
		exit(2);
	}

	if (stat(curdir, &sa) == -1) {
	    (void)fprintf(stderr, "%s: %s: %s.\n",
		 progname, curdir, strerror(errno));
	    exit(2);
	}

	/*
	 * Overriding getcwd() with $PWD totally breaks MAKEOBJDIRPREFIX
	 * since the value of curdir can very depending on how we got
	 * here.  Ie sitting at a shell prompt (shell that provides $PWD)
	 * or via subdir.mk in which case its likely a shell which does
	 * not provide it.
	 * So, to stop it breaking this case only, we ignore PWD if
	 * MAKEOBJDIRPREFIX is set or MAKEOBJDIR contains a transform.
	 */
	if ((pwd = getenv("PWD")) != NULL && getenv("MAKEOBJDIRPREFIX") == NULL) {
		const char *makeobjdir = getenv("MAKEOBJDIR");

		if (makeobjdir == NULL || !strchr(makeobjdir, '$')) {
			if (stat(pwd, &sb) == 0 && sa.st_ino == sb.st_ino &&
			    sa.st_dev == sb.st_dev)
				(void) strncpy(curdir, pwd, MAXPATHLEN);
		}
	}

	/*
	 * Just in case MAKEOBJDIR wants us to do something tricky.
	 */
	Var_Init();		/* Initialize the lists of variables for
				 * parsing arguments */
	Var_Set(".CURDIR", curdir, VAR_GLOBAL, 0);
#ifdef MAKE_VERSION
	Var_Set("MAKE_VERSION", MAKE_VERSION, VAR_GLOBAL, 0);
#endif
	Var_Set(".newline", "\n", VAR_GLOBAL, 0); /* handy for :@ loops */

	/*
	 * Find the .OBJDIR.  If MAKEOBJDIRPREFIX, or failing that,
	 * MAKEOBJDIR is set in the environment, try only that value
	 * and fall back to .CURDIR if it does not exist.
	 *
	 * Otherwise, try _PATH_OBJDIR and finally _PATH_OBJDIRPREFIX`pwd`,
	 * in that order.  If none of these paths exist, just use .CURDIR.
	 *
	 */

	Dir_Init(curdir);
	(void) Main_SetObjdir(curdir);

	if ((path = getenv("MAKEOBJDIRPREFIX")) != NULL) {
		(void) snprintf(mdpath, MAXPATHLEN, "%s%s", path, curdir);
		(void) Main_SetObjdir(mdpath);
	} else if ((path = getenv("MAKEOBJDIR")) != NULL) {
		(void) Main_SetObjdir(path);
	} else {
		if (!Main_SetObjdir(_PATH_OBJDIR)) {
			(void) snprintf(mdpath, MAXPATHLEN, "%s%s",
					_PATH_OBJDIRPREFIX, curdir);
			(void) Main_SetObjdir(mdpath);
		}
	}

	create = Lst_Init(FALSE);
	makefiles = Lst_Init(FALSE);
	printVars = FALSE;
	variables = Lst_Init(FALSE);
	beSilent = FALSE;		/* Print commands as executed */
	ignoreErrors = FALSE;		/* Pay attention to non-zero returns */
	noExecute = FALSE;		/* Execute all commands */
	noRecursiveExecute = FALSE;	/* Execute all .MAKE targets */
	keepgoing = FALSE;		/* Stop on error */
	allPrecious = FALSE;		/* Remove targets when interrupted */
	queryFlag = FALSE;		/* This is not just a check-run */
	touchFlag = FALSE;		/* Actually update targets */
	usePipes = TRUE;		/* Catch child output in pipes */
	debug = 0;			/* No debug verbosity, please. */
	jobsRunning = FALSE;

	maxLocal = DEFMAXLOCAL;		/* Set default local max concurrency */
	maxJobs = maxLocal;
	compatMake = FALSE;		/* No compat mode */


	/*
	 * Initialize the parsing, directory and variable modules to prepare
	 * for the reading of inclusion paths and variable settings on the
	 * command line
	 */

	/*
	 * Initialize various variables.
	 *	MAKE also gets this name, for compatibility
	 *	.MAKEFLAGS gets set to the empty string just in case.
	 *	MFLAGS also gets initialized empty, for compatibility.
	 */
	Parse_Init();
	Var_Set("MAKE", argv[0], VAR_GLOBAL, 0);
	Var_Set(".MAKE", argv[0], VAR_GLOBAL, 0);
	Var_Set(MAKEFLAGS, "", VAR_GLOBAL, 0);
	Var_Set(MAKEOVERRIDES, "", VAR_GLOBAL, 0);
	Var_Set("MFLAGS", "", VAR_GLOBAL, 0);
	Var_Set(".ALLTARGETS", "", VAR_GLOBAL, 0);

	/*
	 * First snag any flags out of the MAKE environment variable.
	 * (Note this is *not* MAKEFLAGS since /bin/make uses that and it's
	 * in a different format).
	 */
#ifdef POSIX
	Main_ParseArgLine(getenv("MAKEFLAGS"));
#else
	Main_ParseArgLine(getenv("MAKE"));
#endif

	MainParseArgs(argc, argv);

	/*
	 * Be compatible if user did not specify -j and did not explicitly
	 * turned compatibility on
	 */
	if (!compatMake && !forceJobs) {
		compatMake = TRUE;
	}

	/*
	 * Initialize archive, target and suffix modules in preparation for
	 * parsing the makefile(s)
	 */
	/* Arch_Init(); */
	Targ_Init();
	Suff_Init();
	Trace_Init(tracefile);

	DEFAULT = NILGNODE;
	(void)time(&now);

	Trace_Log(MAKESTART, NULL);

	/*
	 * Set up the .TARGETS variable to contain the list of targets to be
	 * created. If none specified, make the variable empty -- the parser
	 * will fill the thing in with the default or .MAIN target.
	 */
	if (!Lst_IsEmpty(create)) {
		LstNode ln;

		for (ln = Lst_First(create); ln != NILLNODE;
		    ln = Lst_Succ(ln)) {
			char *name = (char *)Lst_Datum(ln);

			Var_Append(".TARGETS", name, VAR_GLOBAL);
		}
	} else {
		Var_Set(".TARGETS", "", VAR_GLOBAL, 0);
	}

	if (!Lst_IsEmpty(makefiles)) {
		LstNode ln, tln;
		ln = tln = Lst_First(makefiles);
		do {
			if (!ReadMakefile(Lst_Datum(tln))) {
				Fatal("%s: cannot open %s.", progname, (char *)(Lst_Datum(tln)));
				break;
			}
			tln = Lst_Succ(tln);
		} while (tln != ln && tln != NILLNODE);
	} else if (!ReadMakefile(UNCONST("makefile")) &&
		   !ReadMakefile(UNCONST("Makefile"))) {
		Fatal("%s: cannot open \"makefile\" nor \"Makefile\".", progname);
	}

	Var_Append("MFLAGS", Var_Value(MAKEFLAGS, VAR_GLOBAL, &p1), VAR_GLOBAL);
	if (p1)
	    free(p1);

	if (!jobServer && !compatMake)
	    Job_ServerStart(maxJobs);
	if (DEBUG(JOB))
	    printf("job_pipe %d %d, maxjobs %d maxlocal %d compat %d\n", job_pipe[0], job_pipe[1], maxJobs,
	           maxLocal, compatMake);

	Main_ExportMAKEFLAGS(TRUE);	/* initial export */

	Check_Cwd_av(0, NULL, 0);	/* initialize it */


	/*
	 * For compatibility, look at the directories in the VPATH variable
	 * and add them to the search path, if the variable is defined. The
	 * variable's value is in the same format as the PATH envariable, i.e.
	 * <directory>:<directory>:<directory>...
	 */
	if (Var_Exists("VPATH", VAR_CMD)) {
		char *vpath, savec;
		/*
		 * GCC stores string constants in read-only memory, but
		 * Var_Subst will want to write this thing, so store it
		 * in an array
		 */
		static char VPATH[] = "${VPATH}";

		vpath = Var_Subst(NULL, VPATH, VAR_CMD, FALSE);
		path = vpath;
		do {
			/* skip to end of directory */
			for (cp = path; *cp != ':' && *cp != '\0'; cp++)
				continue;
			/* Save terminator character so know when to stop */
			savec = *cp;
			*cp = '\0';
			/* Add directory to search path */
			(void) Dir_AddDir(dirSearchPath, path);
			*cp = savec;
			path = cp + 1;
		} while (savec == ':');
		(void)free((Address)vpath);
	}

	/*
	 * Now that all search paths have been read for suffixes et al, it's
	 * time to add the default search path to their lists...
	 */
	Suff_DoPaths();

	/*
	 * Propagate attributes through :: dependency lists.
	 */
	Targ_Propagate();

	/* print the initial graph, if the user requested it */
	if (DEBUG(GRAPH1))
		Targ_PrintGraph(1);

	/* print the values of any variables requested by the user */
	if (printVars) {
		LstNode ln;

		for (ln = Lst_First(variables); ln != NILLNODE;
		    ln = Lst_Succ(ln)) {
			char *var = (char *)Lst_Datum(ln);
			char *value;

			if (strchr(var, '$')) {
				value = p1 = Var_Subst(NULL, var, VAR_GLOBAL, 0);
			} else {
				value = Var_Value(var, VAR_GLOBAL, &p1);
			}
			printf("%s\n", value ? value : "");
			if (p1)
				free(p1);
		}
	}

	/*
	 * Have now read the entire graph and need to make a list of targets
	 * to create. If none was given on the command line, we consult the
	 * parsing module to find the main target(s) to create.
	 */
	if (Lst_IsEmpty(create))
		targs = Parse_MainName();
	else
		targs = Targ_FindList(create, TARG_CREATE);

	if (!compatMake && !printVars) {
		/*
		 * Initialize job module before traversing the graph, now that
		 * any .BEGIN and .END targets have been read.  This is done
		 * only if the -q flag wasn't given (to prevent the .BEGIN from
		 * being executed should it exist).
		 */
		if (!queryFlag) {
			if (maxLocal == -1)
				maxLocal = maxJobs;
			Job_Init(maxJobs, maxLocal);
			jobsRunning = TRUE;
		}

		/* Traverse the graph, checking on all the targets */
		outOfDate = Make_Run(targs);
	} else if (!printVars) {
		/*
		 * Compat_Init will take care of creating all the targets as
		 * well as initializing the module.
		 */
		Compat_Run(targs);
	}

#ifdef CLEANUP
	Lst_Destroy(targs, NOFREE);
	Lst_Destroy(variables, NOFREE);
	Lst_Destroy(makefiles, NOFREE);
	Lst_Destroy(create, (void (*)(ClientData))) free;
#endif

	/* print the graph now it's been processed if the user requested it */
	if (DEBUG(GRAPH2))
		Targ_PrintGraph(2);

	Trace_Log(MAKEEND, 0);

	Suff_End();
        Targ_End();
	/* Arch_End(); */
	Var_End();
	Parse_End();
	Dir_End();
	Job_End();
	Trace_End();

	if (queryFlag && outOfDate)
		return(1);
	else
		return(0);
}

/*-
 * ReadMakefile  --
 *	Open and parse the given makefile.
 *
 * Results:
 *	TRUE if ok. FALSE if couldn't open file.
 *
 * Side Effects:
 *	lots
 */
static Boolean
ReadMakefile(ClientData p)
{
	char *fname = p;		/* makefile to read */
	FILE *stream;
	size_t len = MAXPATHLEN;
	char *name, *path = emalloc(len);

	if (DEBUG(MAKE)) {
		(void) fprintf(stderr, "Reading Makefile \"%s\"\n", fname);
	}

	if (!strcmp(fname, "-")) {
		Parse_File("(stdin)", stdin);
		Var_Set("MAKEFILE", "", VAR_GLOBAL, 0);
	} else {
		/* if we've chdir'd, rebuild the path name */
		if (strcmp(curdir, objdir) && *fname != '/') {
			size_t plen = strlen(curdir) + strlen(fname) + 2;
			if (len < plen)
				path = erealloc(path, len = 2 * plen);

			(void)snprintf(path, len, "%s/%s", curdir, fname);
			if ((stream = fopen(path, "r")) != NULL) {
				fname = path;
				goto found;
			}

			/* If curdir failed, try objdir (ala .depend) */
			plen = strlen(objdir) + strlen(fname) + 2;
			if (len < plen)
				path = erealloc(path, len = 2 * plen);
			(void)snprintf(path, len, "%s/%s", objdir, fname);
			if ((stream = fopen(path, "r")) != NULL) {
				fname = path;
				goto found;
			}
		} else if ((stream = fopen(fname, "r")) != NULL) {
			goto found;
		}
		/* look in -I and system include directories. */
		name = Dir_FindFile(fname, parseIncPath);
		if (!name)
			name = Dir_FindFile(fname,
				Lst_IsEmpty(sysIncPath) ? defIncPath : sysIncPath);
		if (!name || !(stream = fopen(name, "r"))) {
			free(path);
			return(FALSE);
		}
		fname = name;
		/*
		 * set the MAKEFILE variable desired by System V fans -- the
		 * placement of the setting here means it gets set to the last
		 * makefile specified, as it is set by SysV make.
		 */
found:
		Var_Set("MAKEFILE", fname, VAR_GLOBAL, 0);
		Parse_File(fname, stream);
		(void)fclose(stream);
	}
	free(path);
	return(TRUE);
}


/*
 * If MAKEOBJDIRPREFIX is in use, make ends up not in .CURDIR
 * in situations that would not arrise with ./obj (links or not).
 * This tends to break things like:
 *
 * build:
 * 	${MAKE} includes
 *
 * This function spots when ${.MAKE:T} or ${.MAKE} is a command (as
 * opposed to an argument) in a command line and if so returns
 * ${.CURDIR} so caller can chdir() so that the assumptions made by
 * the Makefile hold true.
 *
 * If ${.MAKE} does not contain any '/', then ${.MAKE:T} is skipped.
 *
 * The chdir() only happens in the child process, and does nothing if
 * MAKEOBJDIRPREFIX and MAKEOBJDIR are not in the environment so it
 * should not break anything.  Also if NOCHECKMAKECHDIR is set we
 * do nothing - to ensure historic semantics can be retained.
 */
static int  Check_Cwd_Off = 0;

static char *
Check_Cwd_av(int ac, char **av, int copy)
{
    static char *make[4];
    static char *cur_dir = NULL;
    char **mp;
    char *cp;
    int is_cmd, next_cmd;
    int i;
    int n;

    if (Check_Cwd_Off)
	return NULL;

    if (make[0] == NULL) {
	if (Var_Exists("NOCHECKMAKECHDIR", VAR_GLOBAL)) {
	    Check_Cwd_Off = 1;
	    return NULL;
	}

        make[1] = Var_Value(".MAKE", VAR_GLOBAL, &cp);
        if ((make[0] = strrchr(make[1], '/')) == NULL) {
            make[0] = make[1];
            make[1] = NULL;
        } else
            ++make[0];
        make[2] = NULL;
        cur_dir = Var_Value(".CURDIR", VAR_GLOBAL, &cp);
    }
    if (ac == 0 || av == NULL)
        return NULL;			/* initialization only */

    if (getenv("MAKEOBJDIR") == NULL &&
        getenv("MAKEOBJDIRPREFIX") == NULL)
        return NULL;


    next_cmd = 1;
    for (i = 0; i < ac; ++i) {
	is_cmd = next_cmd;

	n = strlen(av[i]);
	cp = &(av[i])[n - 1];
	if (strspn(av[i], "|&;") == n) {
	    next_cmd = 1;
	    continue;
	} else if (*cp == ';' || *cp == '&' || *cp == '|' || *cp == ')') {
	    next_cmd = 1;
	    if (copy) {
		do {
		    *cp-- = '\0';
		} while (*cp == ';' || *cp == '&' || *cp == '|' ||
			 *cp == ')' || *cp == '}') ;
	    } else {
		/*
		 * XXX this should not happen.
		 */
		fprintf(stderr, "WARNING: raw arg ends in shell meta '%s'\n",
			av[i]);
	    }
	} else
	    next_cmd = 0;

	cp = av[i];
	if (*cp == ';' || *cp == '&' || *cp == '|')
	    is_cmd = 1;

#ifdef check_cwd_debug
	fprintf(stderr, "av[%d] == %s '%s'",
		i, (is_cmd) ? "cmd" : "arg", av[i]);
#endif
	if (is_cmd != 0) {
	    if (*cp == '(' || *cp == '{' ||
		*cp == ';' || *cp == '&' || *cp == '|') {
		do {
		    ++cp;
		} while (*cp == '(' || *cp == '{' ||
			 *cp == ';' || *cp == '&' || *cp == '|');
		if (*cp == '\0') {
		    next_cmd = 1;
		    continue;
		}
	    }
	    if (strcmp(cp, "cd") == 0 || strcmp(cp, "chdir") == 0) {
#ifdef check_cwd_debug
		fprintf(stderr, " == cd, done.\n");
#endif
		return NULL;
	    }
	    for (mp = make; *mp != NULL; ++mp) {
		n = strlen(*mp);
		if (strcmp(cp, *mp) == 0) {
#ifdef check_cwd_debug
		    fprintf(stderr, " %s == '%s', chdir(%s)\n",
			    cp, *mp, cur_dir);
#endif
		    return cur_dir;
		}
	    }
	}
#ifdef check_cwd_debug
	fprintf(stderr, "\n");
#endif
    }
    return NULL;
}

char *
Check_Cwd_Cmd(const char *cmd)
{
    char *cp, *bp;
    char **av;
    int ac;

    if (Check_Cwd_Off)
	return NULL;

    if (cmd) {
	av = brk_string(cmd, &ac, TRUE, &bp);
#ifdef check_cwd_debug
	fprintf(stderr, "splitting: '%s' -> %d words\n",
		cmd, ac);
#endif
    } else {
	ac = 0;
	av = NULL;
	bp = NULL;
    }
    cp = Check_Cwd_av(ac, av, 1);
    if (bp) {
	free(av);
	free(bp);
    }
    return cp;
}

void
Check_Cwd(const char **argv)
{
    char *cp;
    int ac;

    if (Check_Cwd_Off)
	return;

    for (ac = 0; argv[ac] != NULL; ++ac)
	/* NOTHING */;
    if (ac == 3 && *argv[1] == '-') {
	cp =  Check_Cwd_Cmd(argv[2]);
    } else {
	cp = Check_Cwd_av(ac, UNCONST(argv), 0);
    }
    if (cp) {
	chdir(cp);
    }
}

/*-
 * Cmd_Exec --
 *	Execute the command in cmd, and return the output of that command
 *	in a string.
 *
 * Results:
 *	A string containing the output of the command, or the empty string
 *	If err is not NULL, it contains the reason for the command failure
 *
 * Side Effects:
 *	The string must be freed by the caller.
 */
char *
Cmd_Exec(const char *cmd, const char **err)
{
    const char	*args[4];   	/* Args for invoking the shell */
    int 	fds[2];	    	/* Pipe streams */
    int 	cpid;	    	/* Child PID */
    int 	pid;	    	/* PID from wait() */
    char	*res;		/* result */
    int		status;		/* command exit status */
    Buffer	buf;		/* buffer to store the result */
    char	*cp;
    int		cc;


    *err = NULL;

    if (!shellName)
	Shell_Init();
    /*
     * Set up arguments for shell
     */
    args[0] = shellName;
    args[1] = "-c";
    args[2] = cmd;
    args[3] = NULL;

    /*
     * Open a pipe for fetching its output
     */
    if (pipe(fds) == -1) {
	*err = "Couldn't create pipe for \"%s\"";
	goto bad;
    }

    /*
     * Fork
     */
    switch (cpid = vfork()) {
    case 0:
	/*
	 * Close input side of pipe
	 */
	(void) close(fds[0]);

	/*
	 * Duplicate the output stream to the shell's output, then
	 * shut the extra thing down. Note we don't fetch the error
	 * stream...why not? Why?
	 */
	(void) dup2(fds[1], 1);
	(void) close(fds[1]);

	(void) execv(shellPath, UNCONST(args));
	_exit(1);
	/*NOTREACHED*/

    case -1:
	*err = "Couldn't exec \"%s\"";
	goto bad;

    default:
	/*
	 * No need for the writing half
	 */
	(void) close(fds[1]);

	buf = Buf_Init(MAKE_BSIZE);

	do {
	    char   result[BUFSIZ];
	    cc = read(fds[0], result, sizeof(result));
	    if (cc > 0)
		Buf_AddBytes(buf, cc, (Byte *) result);
	}
	while (cc > 0 || (cc == -1 && errno == EINTR));

	/*
	 * Close the input side of the pipe.
	 */
	(void) close(fds[0]);

	/*
	 * Wait for the process to exit.
	 */
	while(((pid = wait(&status)) != cpid) && (pid >= 0))
	    continue;

	res = (char *)Buf_GetAll (buf, &cc);
	Buf_Destroy(buf, FALSE);

	if (cc == 0)
	    *err = "Couldn't read shell's output for \"%s\"";

	if (status)
	    *err = "\"%s\" returned non-zero status";

	/*
	 * Null-terminate the result, convert newlines to spaces and
	 * install it in the variable.
	 */
	res[cc] = '\0';
	cp = &res[cc];

	if (cc > 0 && *--cp == '\n') {
	    /*
	     * A final newline is just stripped
	     */
	    *cp-- = '\0';
	}
	while (cp >= res) {
	    if (*cp == '\n') {
		*cp = ' ';
	    }
	    cp--;
	}
	break;
    }
    return res;
bad:
    res = emalloc(1);
    *res = '\0';
    return res;
}

/*-
 * Error --
 *	Print an error message given its format.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The message is printed.
 */
/* VARARGS */
void
Error(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	fprintf(stderr, "%s: ", progname);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);
}

/*-
 * Fatal --
 *	Produce a Fatal error message. If jobs are running, waits for them
 *	to finish.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The program exits
 */
/* VARARGS */
void
Fatal(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	if (jobsRunning)
		Job_Wait();
	Job_TokenFlush();

	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);

	PrintOnError(NULL);

	if (DEBUG(GRAPH2) || DEBUG(GRAPH3))
		Targ_PrintGraph(2);
	Trace_Log(MAKEERROR, 0);
	exit(2);		/* Not 1 so -q can distinguish error */
}

/*
 * Punt --
 *	Major exception once jobs are being created. Kills all jobs, prints
 *	a message and exits.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	All children are killed indiscriminately and the program Lib_Exits
 */
/* VARARGS */
void
Punt(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	(void)fprintf(stderr, "%s: ", progname);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);

	PrintOnError(NULL);

	DieHorribly();
}

/*-
 * DieHorribly --
 *	Exit without giving a message.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A big one...
 */
void
DieHorribly(void)
{
	if (jobsRunning)
		Job_AbortAll();
	if (DEBUG(GRAPH2))
		Targ_PrintGraph(2);
	Trace_Log(MAKEERROR, 0);
	exit(2);		/* Not 1, so -q can distinguish error */
}

/*
 * Finish --
 *	Called when aborting due to errors in child shell to signal
 *	abnormal exit.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The program exits
 */
void
Finish(int errors)
	           	/* number of errors encountered in Make_Make */
{
	Fatal("%d error%s", errors, errors == 1 ? "" : "s");
}

/*
 * emalloc --
 *	malloc, but die on error.
 */
void *
emalloc(size_t len)
{
	void *p;

	if ((p = malloc(len)) == NULL)
		enomem();
	return(p);
}

/*
 * estrdup --
 *	strdup, but die on error.
 */
char *
estrdup(const char *str)
{
	char *p;

	if ((p = strdup(str)) == NULL)
		enomem();
	return(p);
}

/*
 * erealloc --
 *	realloc, but die on error.
 */
void *
erealloc(void *ptr, size_t size)
{
	if ((ptr = realloc(ptr, size)) == NULL)
		enomem();
	return(ptr);
}

/*
 * enomem --
 *	die when out of memory.
 */
void
enomem(void)
{
	(void)fprintf(stderr, "%s: %s.\n", progname, strerror(errno));
	exit(2);
}

/*
 * enunlink --
 *	Remove a file carefully, avoiding directories.
 */
int
eunlink(const char *file)
{
	struct stat st;

	if (lstat(file, &st) == -1)
		return -1;

	if (S_ISDIR(st.st_mode)) {
		errno = EISDIR;
		return -1;
	}
	return unlink(file);
}

/*
 * execError --
 *	Print why exec failed, avoiding stdio.
 */
void
execError(const char *af, const char *av)
{
#ifdef USE_IOVEC
	int i = 0;
	struct iovec iov[8];
#define IOADD(s) \
	(void)(iov[i].iov_base = UNCONST(s), \
	    iov[i].iov_len = strlen(iov[i].iov_base), \
	    i++)
#else
#define	IOADD (void)write(2, s, strlen(s))
#endif

	IOADD(progname);
	IOADD(": ");
	IOADD(af);
	IOADD("(");
	IOADD(av);
	IOADD(") failed (");
	IOADD(strerror(errno));
	IOADD(")\n");

#ifdef USE_IOVEC
	(void)writev(2, iov, 8);
#endif
}

/*
 * usage --
 *	exit with usage message
 */
static void
usage(void)
{
	(void)fprintf(stderr,
"usage: %s [-BeikNnqrstWX] [-C dir] [-D variable] [-d flags] [-f makefile]\n\
            [-I directory] [-J private] [-j max_jobs] [-T file]\n\
            [-V variable] [variable=value] [target ...]\n", progname);
	exit(2);
}

int
PrintAddr(ClientData a, ClientData b)
{
    printf("%lx ", (unsigned long) a);
    return b ? 0 : 0;
}

void
PrintOnError(const char *s)
{
    char tmp[64];

    if (s)
	    printf("%s", s);

    printf("\n%s: stopped in %s\n", progname, curdir);
    strncpy(tmp, "${MAKE_PRINT_VAR_ON_ERROR:@v@$v='${$v}'\n@}",
	    sizeof(tmp) - 1);
    s = Var_Subst(NULL, tmp, VAR_GLOBAL, 0);
    if (s && *s)
	printf("%s", s);
}

void
Main_ExportMAKEFLAGS(Boolean first)
{
    static int once = 1;
    char tmp[64];
    char *s;

    if (once != first)
	return;
    once = 0;

    strncpy(tmp, "${.MAKEFLAGS} ${.MAKEOVERRIDES:O:u:@v@$v=${$v:Q}@}",
	    sizeof(tmp));
    s = Var_Subst(NULL, tmp, VAR_CMD, 0);
    if (s && *s) {
#ifdef POSIX
	setenv("MAKEFLAGS", s, 1);
#else
	setenv("MAKE", s, 1);
#endif
    }
}
/* end main.c */
