#ifndef __PLINK2_LD_H__
#define __PLINK2_LD_H__

// This file is part of PLINK 2.00, copyright (C) 2005-2023 Shaun Purcell,
// Christopher Chang.
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "plink2_common.h"

#ifdef __cplusplus
namespace plink2 {
#endif

FLAGSET_DEF_START()
  kfLdPrune0,
  kfLdPruneWindowBp = (1 << 0),
  kfLdPrunePairwise = (1 << 1),
  kfLdPrunePairphase = (1 << 2),
  kfLdPrunePlink1Order = (1 << 3)
FLAGSET_DEF_END(LdPruneFlags);
// todo: old multicollinearity test

FLAGSET_DEF_START()
  kfClump0,
  kfClumpZs = (1 << 0),
  kfClumpUnphased = (1 << 1),
  kfClumpForceA1 = (1 << 2),
  kfClumpAllowOverlap = (1 << 3),
  kfClumpInputLog10 = (1 << 4),
  kfClumpOutputLog10 = (1 << 5),
  kfClumpNoA1 = (1 << 6),
  kfClumpNoTest = (1 << 7),

  kfClumpColChrom = (1 << 8),
  kfClumpColPos = (1 << 9),
  kfClumpColRef = (1 << 10),
  kfClumpColAlt1 = (1 << 11),
  kfClumpColAlt = (1 << 12),
  kfClumpColMaybeprovref = (1 << 13),
  kfClumpColProvref = (1 << 14),
  kfClumpColMaybeA1 = (1 << 15),
  kfClumpColA1 = (1 << 16),
  kfClumpColMaybeF = (1 << 17),
  kfClumpColF = (1 << 18),
  kfClumpColTotal = (1 << 19),
  kfClumpColBins = (1 << 20),
  kfClumpColSp2 = (1 << 21),
  kfClumpColDefault = (kfClumpColChrom | kfClumpColPos | kfClumpColMaybeprovref | kfClumpColMaybeA1 | kfClumpColMaybeF | kfClumpColTotal | kfClumpColBins | kfClumpColSp2)
FLAGSET_DEF_END(ClumpFlags);

FLAGSET_DEF_START()
  kfVcor0,
  kfVcorZs = (1 << 0),
  kfVcorBin8 = (1 << 1),
  kfVcorBin4 = (1 << 2),
  kfVcorEncodemask = (kfVcorZs | kfVcorBin8 | kfVcorBin4),
  kfVcorMatrixSq = (1 << 3),
  kfVcorMatrixSq0 = (1 << 4),
  kfVcorMatrixTri = (1 << 5),
  kfVcorMatrixShapemask = (kfVcorMatrixSq | kfVcorMatrixSq0 | kfVcorMatrixTri),
  kfVcorPhased = (1 << 6),
  kfVcorUnsquared = (1 << 7),
  kfVcorYesReally = (1 << 8),
  kfVcorInterChr = (1 << 9),

  kfVcorColChrom = (1 << 10),
  kfVcorColPos = (1 << 11),
  kfVcorColId = (1 << 12),
  kfVcorColRef = (1 << 13),
  kfVcorColAlt1 = (1 << 14),
  kfVcorColAlt = (1 << 15),
  kfVcorColMaybeprovref = (1 << 16),
  kfVcorColProvref = (1 << 17),
  kfVcorColMaj = (1 << 18),
  kfVcorColNonmaj = (1 << 19),
  kfVcorColFreq = (1 << 20),
  kfVcorColD = (1 << 21),
  kfVcorColDprime = (1 << 22),
  kfVcorColDprimeAbs = (1 << 23),
  kfVcorColDefault = (kfVcorColChrom | kfVcorColPos | kfVcorColId | kfVcorColMaybeprovref),
  kfVcorUnsquaredColDefault = (kfVcorColDefault | kfVcorColMaj)
FLAGSET_DEF_END(VcorFlags);

CONSTI32(kClumpMaxBinBounds, 0x4000000);

FLAGSET_DEF_START()
  kfLdConsole0,
  kfLdConsoleHweMidp = (1 << 0)
FLAGSET_DEF_END(LdConsoleFlags);

typedef struct LdInfoStruct {
  NONCOPYABLE(LdInfoStruct);
  double prune_last_param;  // VIF or r^2 threshold
  LdPruneFlags prune_flags;
  uint32_t prune_window_size;
  uint32_t prune_window_incr;
  LdConsoleFlags ld_console_flags;
  STD_ARRAY_DECL(char*, 2, ld_console_varids);
} LdInfo;

typedef struct ClumpInfoStruct {
  NONCOPYABLE(ClumpInfoStruct);
  char* fnames_flattened;
  char* test_name;
  char* id_field;
  char* a1_field;
  char* test_field;
  char* p_field;
  double* ln_bin_boundaries;
  double ln_p1;
  double ln_p2;
  double r2;
  uint32_t bin_bound_ct;
  uint32_t bp_radius;
  ClumpFlags flags;
} ClumpInfo;

typedef struct VcorInfoStruct {
  NONCOPYABLE(VcorInfoStruct);
  char* ld_snp_list_fname;
  RangeList ld_snp_range_list;
  uint32_t var_ct_radius;
  uint32_t bp_radius;
  double cm_radius;
  double min_r2;
  VcorFlags flags;
} VcorInfo;

void InitLd(LdInfo* ldip);

void CleanupLd(LdInfo* ldip);

void InitClump(ClumpInfo* clump_ip);

void CleanupClump(ClumpInfo* clump_ip);

void InitVcor(VcorInfo* vcip);

void CleanupVcor(VcorInfo* vcip);

PglErr LdPrune(const uintptr_t* orig_variant_include, const ChrInfo* cip, const uint32_t* variant_bps, const char* const* variant_ids, const uintptr_t* allele_idx_offsets, const AlleleCode* maj_alleles, const double* allele_freqs, const uintptr_t* founder_info, const uintptr_t* sex_nm, const uintptr_t* sex_male, const LdInfo* ldip, const char* indep_preferred_fname, uint32_t raw_variant_ct, uint32_t variant_ct, uint32_t raw_sample_ct, uint32_t founder_ct, uint32_t nosex_ct, uint32_t max_thread_ct, PgenReader* simple_pgrp, char* outname, char* outname_end);

PglErr LdConsole(const uintptr_t* variant_include, const ChrInfo* cip, const char* const* variant_ids, const uintptr_t* allele_idx_offsets, const char* const* allele_storage, const AlleleCode* maj_alleles, const uintptr_t* founder_info, const uintptr_t* sex_nm, const uintptr_t* sex_male, const LdInfo* ldip, uint32_t variant_ct, uint32_t raw_sample_ct, uint32_t founder_ct, PgenReader* simple_pgrp);

PglErr ClumpReports(const uintptr_t* orig_variant_include, const ChrInfo* cip, const uint32_t* variant_bps, const char* const* variant_ids, const uintptr_t* allele_idx_offsets, const char* const* allele_storage, const uintptr_t* founder_info, const uintptr_t* sex_nm, const uintptr_t* sex_male, const ClumpInfo* clump_ip, uint32_t raw_variant_ct, uint32_t orig_variant_ct, uint32_t raw_sample_ct, uint32_t founder_ct, uint32_t nosex_ct, uint32_t max_variant_id_slen, uint32_t max_allele_slen, double output_min_ln, uint32_t max_thread_ct, uintptr_t pgr_alloc_cacheline_ct, PgenFileInfo* pgfip, PgenReader* simple_pgrp, char* outname, char* outname_end);

PglErr Vcor(const uintptr_t* orig_variant_include, const ChrInfo* cip, const uint32_t* variant_bps, const char* const* variant_ids, const double* variant_cms, const uintptr_t* allele_idx_offsets, const char* const* allele_storage, const AlleleCode* maj_alleles, const double* allele_freqs, const uintptr_t* founder_info, const uintptr_t* sex_nm, const uintptr_t* sex_male, const VcorInfo* vcip, uint32_t raw_variant_ct, uint32_t orig_variant_ct, uint32_t raw_sample_ct, uint32_t founder_ct, uint32_t max_variant_id_slen, uint32_t max_allele_slen, uint32_t parallel_idx, uint32_t parallel_tot, uint32_t max_thread_ct, PgenReader* simple_pgrp, char* outname, char* outname_end);

#ifdef __cplusplus
}  // namespace plink2
#endif

#endif  // __PLINK2_LD_H__
