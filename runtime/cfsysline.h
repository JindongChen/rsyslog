/* Definition of the cfsysline (config file system line) object.
 *
 * Copyright 2007 Rainer Gerhards and Adiscon GmbH.
 *
 * This file is part of the rsyslog runtime library.
 *
 * The rsyslog runtime library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The rsyslog runtime library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the rsyslog runtime library.  If not, see <http://www.gnu.org/licenses/>.
 *
 * A copy of the GPL can be found in the file "COPYING" in this distribution.
 * A copy of the LGPL can be found in the file "COPYING.LESSER" in this distribution.
 */

#ifndef CFSYSLINE_H_INCLUDED
#define CFSYSLINE_H_INCLUDED

#include "linkedlist.h"

#if 0
/* types of configuration handlers
 */
enum cslCmdHdlrType {
	eCmdHdlrInvalid = 0,		/* invalid handler type - indicates a coding error */
	eCmdHdlrCustomHandler,		/* custom handler, just call handler function */
	eCmdHdlrUID,
	eCmdHdlrGID,
	eCmdHdlrBinary,
	eCmdHdlrFileCreateMode,
	eCmdHdlrInt,
	eCmdHdlrSize,
	eCmdHdlrGetChar,
	eCmdHdlrFacility,
	eCmdHdlrSeverity,
	eCmdHdlrGetWord
};


/* the next type describes $Begin .. $End block object types
 */
enum cslConfObjType {
	eConfObjGlobal = 0,	/* global directives */
	eConfObjAction,		/* action-specific directives */
};
#endif

/* this is a single entry for a parse routine. It describes exactly
 * one entry point/handler.
 * The short name is cslch (Configfile SysLine CommandHandler)
 */
struct cslCmdHdlr_s { /* config file sysline parse entry */
	ecslConfObjType eConfObjType;		/* which config object is this for? */
	ecslCmdHdrlType eType;			/* which type of handler is this? */
	rsRetVal (*cslCmdHdlr)();		/* function pointer to use with handler (params depending on eType) */
	void *pData;				/* user-supplied data pointer */
};
typedef struct cslCmdHdlr_s cslCmdHdlr_t;


/* this is the list of known configuration commands with pointers to
 * their handlers.
 * The short name is cslc (Configfile SysLine Command)
 */
struct cslCmd_s { /* config file sysline parse entry */
	int bChainingPermitted;			/* may multiple handlers be chained for this command? */
	linkedList_t llCmdHdlrs;	/* linked list of command handlers */
};
typedef struct cslCmd_s cslCmd_t;

/* prototypes */
rsRetVal regCfSysLineHdlr(uchar *pCmdName, int bChainingPermitted, ecslCmdHdrlType eType, rsRetVal (*pHdlr)(), void *pData, void *pOwnerCookie, ecslConfObjType eConfObjType);
rsRetVal unregCfSysLineHdlrs(void);
rsRetVal unregCfSysLineHdlrs4Owner(void *pOwnerCookie);
rsRetVal processCfSysLineCommand(uchar *pCmd, uchar **p);
rsRetVal cfsyslineInit(void);
void dbgPrintCfSysLineHandlers(void);

#endif /* #ifndef CFSYSLINE_H_INCLUDED */
