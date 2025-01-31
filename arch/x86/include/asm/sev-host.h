/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * AMD SVM-SEV Host Support.
 *
 * Copyright (C) 2023 Advanced Micro Devices, Inc.
 *
 * Author: Ashish Kalra <ashish.kalra@amd.com>
 *
 */

#ifndef __ASM_X86_SEV_HOST_H
#define __ASM_X86_SEV_HOST_H

#include <asm/sev-common.h>

#ifdef CONFIG_KVM_AMD_SEV
int snp_lookup_rmpentry(u64 pfn, bool *assigned, int *level);
void sev_dump_hva_rmpentry(unsigned long address);
int psmash(u64 pfn);
int rmp_make_private(u64 pfn, u64 gpa, enum pg_level level, int asid, bool immutable);
int rmp_make_shared(u64 pfn, enum pg_level level);
void snp_leak_pages(u64 pfn, unsigned int npages);

#else
static inline int snp_lookup_rmpentry(u64 pfn, bool *assigned, int *level) { return -ENXIO; }
static inline void sev_dump_hva_rmpentry(unsigned long address) {}
static inline int psmash(u64 pfn) { return -ENXIO; }
static inline int rmp_make_private(u64 pfn, u64 gpa, enum pg_level level, int asid,
				   bool immutable)
{
	return -ENXIO;
}
static inline int rmp_make_shared(u64 pfn, enum pg_level level) { return -ENXIO; }
static inline void snp_leak_pages(u64 pfn, unsigned int npages) {}
#endif

#endif
