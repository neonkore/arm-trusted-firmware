/*
 * Copyright (c) 2016-2023, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PARTITION_H
#define PARTITION_H

#include <stdint.h>

#include <lib/cassert.h>
#include <drivers/partition/efi.h>
#include <tools_share/uuid.h>

#if !PLAT_PARTITION_MAX_ENTRIES
# define PLAT_PARTITION_MAX_ENTRIES	128
#endif	/* PLAT_PARTITION_MAX_ENTRIES */

CASSERT(PLAT_PARTITION_MAX_ENTRIES <= 128, assert_plat_partition_max_entries);

#if !PLAT_PARTITION_BLOCK_SIZE
# define PLAT_PARTITION_BLOCK_SIZE	512
#endif /* PLAT_PARTITION_BLOCK_SIZE */

CASSERT((PLAT_PARTITION_BLOCK_SIZE == 512) ||
	(PLAT_PARTITION_BLOCK_SIZE == 4096),
	assert_plat_partition_block_size);

#define LEGACY_PARTITION_BLOCK_SIZE	512

#define LBA(n) ((unsigned long long)(n) * PLAT_PARTITION_BLOCK_SIZE)

typedef struct partition_entry {
	uint64_t		start;
	uint64_t		length;
	char			name[EFI_NAMELEN];
	struct efi_guid		part_guid;
	struct efi_guid		type_guid;
} partition_entry_t;

typedef struct partition_entry_list {
	partition_entry_t	list[PLAT_PARTITION_MAX_ENTRIES];
	int			entry_count;
} partition_entry_list_t;

int load_partition_table(unsigned int image_id);
const partition_entry_t *get_partition_entry(const char *name);
const partition_entry_t *get_partition_entry_by_type(
	const struct efi_guid *type_guid);
const partition_entry_t *get_partition_entry_by_guid(
	const struct efi_guid *part_guid);
const partition_entry_list_t *get_partition_entry_list(void);
void partition_init(unsigned int image_id);
int gpt_partition_init(void);

#endif /* PARTITION_H */
