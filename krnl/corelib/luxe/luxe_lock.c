/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <luxe/luxe_lock.h>

void lock_acquire(lock_t *lock)
{
	for (;;) {
		if (!__atomic_test_and_set(&lock->lock, __ATOMIC_ACQUIRE)) {
			return;
		}
		while (__atomic_load_n(&lock->lock, __ATOMIC_ACQUIRE)) {
			__asm__ volatile("pause" ::: "memory");
		}
	}
}

void lock_release(lock_t *lock)
{
	__atomic_clear(&lock->lock, __ATOMIC_RELEASE);
}