/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __LUXE_LOCK_H_
#define __LUXE_LOCK_H_

#include <stdbool.h>

typedef struct {
	bool lock;
} lock_t;

void lock_acquire(lock_t *lock);
void lock_release(lock_t *lock);

#endif /* __LUXE_LOCK_H_ */