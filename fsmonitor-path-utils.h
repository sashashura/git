#ifndef FSM_PATH_UTILS_H
#define FSM_PATH_UTILS_H

#include "strbuf.h"

struct alias_info
{
	char *alias;
	char *points_to;
};

struct fs_info {
	int is_remote;
	char *typename;
};

/*
 * Get some basic filesystem informtion for the given path
 *
 * Returns -1 on error, zero otherwise.
 */
int fsmonitor__get_fs_info(const char *path, struct fs_info *fs_info);

/*
 * Determines if the filesystem that path resides on is remote.
 *
 * Returns -1 on error, 0 if not remote, 1 if remote.
 */
int fsmonitor__is_fs_remote(const char *path);

/*
 * Get the alias in given path, if any.
 *
 * Sets alias to the first alias that matches any part of the path.
 *
 * If an alias is found, info.alias and info.points_to are set to the
 * found mapping.
 *
 * Returns -1 on error, 0 otherwise.
 *
 * The caller owns the storage that is occupied by set info.alias and
 * info.points_to and is responsible for releasing it with `free(3)`
 * when done.
 */
int fsmonitor__get_alias(const char *path, struct alias_info *info);

/*
 * Resolve the path against the given alias.
 *
 * Returns the resolved path if there is one, NULL otherwise.
 *
 * The caller owns the storage that the returned string occupies and
 * is responsible for releasing it with `free(3)` when done.
 */
char *fsmonitor__resolve_alias(const char *path,
	const struct alias_info *info);


#endif
