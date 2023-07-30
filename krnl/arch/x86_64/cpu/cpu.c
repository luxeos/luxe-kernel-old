/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <cpu/cpu.h>

#include <luxe.h>

void backtrace(uintptr_t rbp)
{
	uintptr_t *base = (uintptr_t *)rbp;

	if (base == NULL) {
		__asm__ volatile("mov %%rbp, %0" : "=g"(base) :: "memory");
	}

	for (;;) {
		uintptr_t *current_rbp = (uintptr_t *)base[0];
		uintptr_t *return_addr = (uintptr_t *)base[1];
		
		if (current_rbp == NULL || return_addr == NULL) {
			break;
		}

		_klog("%.16lx\n", (uintptr_t)return_addr);
		base = current_rbp;
	}
}